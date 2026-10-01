# Livraison PERF-RAID : accélération de PASAPAS / UNPAS en Gibiane

Cast3M 2024.1 (archive de sources PCW_24) — procédures `UNPAS`, `PAS_MATE`, `PASAPAS`, `PAS_DEFA`

## 1. Résumé

**Objectif.** Réduire le temps de calcul de `PASAPAS` sans changer les résultats, en s'attaquant d'abord au portage en Esope de `UNPAS` envisagé initialement.

**Constat clé.** Le portage de `UNPAS` en Esope n'aurait rien apporté : le temps passé dans l'interprétation de `UNPAS` est inférieur à 1 % à 8 000 éléments. Le temps est consommé par des opérations répétées inutilement : refactorisation de la raideur à chaque pas, réévaluation du matériau et appel de `HOOK` à chaque itération.

**Livré.** Quatre procédures Gibiane modifiées (`UNPAS`, `PAS_MATE`, `PASAPAS`, `PAS_DEFA`), sans recompilation ni modification des sources Esope. Les modifications sont additives (425 lignes ajoutées, commentaires compris ; 9 lignes d'origine remplacées).

**Gains mesurés** (même calcul avec les optimisations inactives, puis actives) :

| Classe de calcul | Maillage 1 000 éléments | Maillage 8 000 éléments |
|---|---|---|
| Matériau dépendant de T, T constante (CHABOCHE, E(T)) | ×1,5 | ×2,4 à ×2,7 |
| Endommagement (MAZARS), niveau 1 exact | ×1,27 | ×1,5 |
| Endommagement, niveau 2 (approché, 1E-2 à 1E-3) | ×1,45 | ×1,8 |
| T variable à chaque pas, niveau 2 | ×1,18 (CHABOCHE) à ×1,28 (MAZARS) | non mesuré |
| Plasticité, viscoplasticité sans T variable, grands déplacements, contact | ×1,0 (inchangé) | ×1,0 |

**Sécurité.** Le comportement par défaut (niveau 1) donne des résultats strictement identiques à l'original : écart maximal 5E-17 sur 56 cas tests de la distribution, 0 sur le cube. Un interrupteur (`'PERF_RAID' = FAUX`) restaure à tout moment le comportement d'origine. Le niveau 2 (réutilisation approchée) est optionnel et désactivé par défaut.

**Recommandation.** Déployer le niveau 1 par défaut. Ne proposer le niveau 2 qu'après validation sur les calculs métier (§9).

## 2. Démarche

1. **Profilage.** `TEMP 'IMPR'` (par procédure et par opérateur) sur un cube sous chargement cyclique (CHABOCHE et MAZARS, 1 à 8 000 éléments) : la part de l'interprétation Gibiane de `UNPAS` est inférieure à 1 % à 8 000 éléments. Les postes dominants sont `RESO` (60 %), `VARI`, `HOOK`, `MENA`, `COMP`.
2. **Recherche des causes** dans les sources Gibiane et Esope :
   - `PAS_VERM` pose `WTAB . 'RECALCUL'` dès que le matériau dépend d'un paramètre externe autre que `ALPH` ; `UNPAS` force `RECARI` pour les lois d'endommagement ; `PASAPAS` détruit alors `WTAB . 'RRRR'` à chaque pas : la raideur est reconstruite et refactorisée à chaque pas, même si elle n'a pas changé ;
   - `PAS_MATE` réévalue le matériau (`VARI`) à chaque pas, même à T constante ;
   - `UNPAS` appelle `HOOK` à chaque itération pour fournir à `EPSI` une matrice que seul l'élément de coque DST lit (sources `epsi1.eso`, `epsi3.eso` : `IMAT = 2` ne sert que pour `MELE = 93`).
3. **Principe de correction.** À géométrie et blocages fixes, la raideur d'itération ne dépend que du champ de caractéristiques et, pour l'endommagement, de la matrice de Hooke endommagée. `UNPAS` résout par la méthode des résidus : la raideur n'est qu'une matrice d'itération, la solution est imposée par le résidu. Conserver la raideur tant qu'elle est identique ne change donc rien au résultat, et la conserver approximativement ne change que le chemin d'itération.
4. **Essais successifs sur cas contrôlés** (cube) puis sur 57 cas de la distribution (répertoire `dgibi`), avec comparaison systématique « optimisations inactives / actives ». Les essais ont corrigé plusieurs défauts de conception (comparaison de l'état complet inopérante, `MAXI` impossible sur la matrice de Hooke, variables d'un cas masquant des mots-clés du suivant) ; la version livrée est celle qui a passé toutes les campagnes.
5. **Choix retenus** : modifications Gibiane additives et gardées (désactivation automatique dès qu'une condition n'est pas satisfaite), diagnostic intégré (compteurs), retour arrière par un seul interrupteur.

## 3. Modifications par fichier

Volume : `UNPAS` +247 / −8 lignes, `PAS_MATE` +93 / −1, `PASAPAS` +35 / −0, `PAS_DEFA` +50 / −0. Toutes les lignes ajoutées sont repérées par le mot `PERF-RAID` dans un commentaire. Les 9 lignes d'origine remplacées sont : la condition de reconstruction de la raideur dans `UNPAS` (1 instruction), les deux appels `HOOK` + `EPSI` par itération dans `UNPAS` (2 sites), l'appel `VARI` dans `PAS_MATE`.

### 3.1 `UNPAS`
| Réf. | Modification | Se désactive si |
|---|---|---|
| U1 | Interrupteur général `IPERFRD` (indice `'PERF_RAID'`) et valeurs par défaut des options et compteurs absents de `WTAB` (reprise d'un calcul créé avec les anciennes procédures) | `'PERF_RAID' = FAUX` |
| U2 | **HOOK évité** : l'appel `HOOK` à chaque itération, qui fournit à `EPSI` une matrice inutilisée, est supprimé pour tout modèle sans élément de coque (`DST`, `DSQ`, `DKT`, `DKQ`, `COQ2`, `COQ3`, `COQ4`, `COQ8`). Test mis en cache par modèle (`HOOK_MOD`, `HOOK_INUTILE`) | présence d'un élément de coque |
| U3 | **Réutilisation exacte de la raideur** : une copie de la raideur factorisée est conservée d'un pas à l'autre (`RRRR_MAT`) avec le matériau (`MAT_RRRR`), l'état (`ETAT_RRRR`) et la diagonale de la raideur (`DIAG_RRRR`). Elle est réutilisée si le champ de caractéristiques est le même objet (cache de `PAS_MATE`) ou si les paramètres externes (`WTAB . 'LDEVA'`) sont inchangés à 1E-12 près ; pour l'endommagement, si la diagonale de la raideur élastique endommagée reconstruite (`HOOK` + `RIGI`) est identique à celle de la raideur factorisée | grands déplacements, FEFP, PICA (`LAG_TOT`), céramique, rigidité augmentée (`IRAUG`, `AUTAUG`), blocages variables (`CHAR_BLOM`), éléments de structure si `'PERF_STRUCTURES' = FAUX`, liste `LDEVA` absente ou vide, aucune composante comparable |
| U4 | **Niveau 2 (réutilisation approchée)** : réutilisation si la diagonale de la raideur reconstruite diffère de la diagonale stockée de moins de la tolérance (1E-3 relatif au niveau 2), y compris quand T ou l'endommagement ont varié. Après une non-convergence (sous-pas), la raideur est toujours reconstruite exactement. La raideur candidate construite pour la comparaison est reprise telle quelle par la reconstruction si la réutilisation est refusée (pas de calcul en double) | niveau 1 (défaut), exclusions de U3, après une non-convergence (`KNOCONV > 1`) |
| U5 | Compteurs de diagnostic `NB_RAIDEUR_REUT`, `NB_RAIDEUR_CALC`, `NB_HOOK_EVITE` | — |

### 3.2 `PAS_MATE`
| Réf. | Modification | Se désactive si |
|---|---|---|
| M1 | **Cache du champ de caractéristiques** : le résultat de `VARI` est conservé (`PMAT_MMM`) avec `MA`, `MO` et les composantes de `LDEVA` de l'état ; il est réutilisé (même objet) tant que ces composantes sont inchangées à `TOL_MATERIAU` près (1E-12). `UNPAS` s'en sert pour détecter l'égalité des matériaux par simple comparaison d'identité | `MATVAR` faux, modal, fréquentiel, béton HT, `MO` recomposé à chaque appel, composante absente de l'état, `LDEVA` absent ou vide, `'TOLERANCE_MATERIAU' < 0` |
| M2 | Compteur `NB_MAT_REUT` | — |

### 3.3 `PASAPAS`
| Réf. | Modification |
|---|---|
| P1 | En fin d'appel, purge des objets conservés par `UNPAS` et `PAS_MATE` (`RRRR_MAT`, `ETAT_RRRR`, `MAT_RRRR`, `DIAG_RRRR`, `PMAT_*`, `HOOK_*`) : un nouvel appel avec un matériau ou un modèle modifié force le recalcul. Les compteurs ne sont pas purgés |
| P2 | Messages de diagnostic en fin de calcul : raideur recalculée / réutilisée, HOOK évité, caractéristiques réutilisées |

### 3.4 `PAS_DEFA`
| Réf. | Modification |
|---|---|
| D1 | Valeurs par défaut des options et compteurs dans `WTAB` |
| D2 | Lecture des indices utilisateur (ci-dessous) et préréglage du niveau 2 |

## 4. Options utilisateur (table passée à `PASAPAS`)
| Indice | Défaut | Effet |
|---|---|---|
| `'PERF_RAID'` | VRAI | FAUX : comportement strictement identique à l'original |
| `'PERF_RAID_NIVEAU'` | 1 | 2 : réutilisation approchée de la raideur (tolérance 1E-3 sur la diagonale, pour tous les cas matériau variable et endommagement) |
| `'PERF_RAID_NIVEAU'` = 3 | — | niveau 2 + rafraîchissement de la raideur en cas de stagnation de la convergence (modèles d'endommagement, petits déplacements) : voir §13 |
| `'RAFRAICHISSEMENT_RAIDEUR'` | FAUX | VRAI : active le rafraîchissement du niveau 3 indépendamment du niveau |
| `'TOLERANCE_RAIDEUR_DIAG'` | 0 | tolérance relative (> 0 : active) de la réutilisation approchée, indépendamment du niveau |
| `'TOLERANCE_RAIDEUR_ENDO'` | 0 | tolérance relative sur la diagonale endommagée ; 0 = identique ; < 0 désactive la réutilisation en endommagement |
| `'TOLERANCE_RAIDEUR'` | 1E-12 | tolérance relative sur les paramètres externes ; < 0 désactive la réutilisation pour matériau variable |
| `'TOLERANCE_MATERIAU'` | 1E-12 | tolérance du cache des caractéristiques ; < 0 désactive |
| `'PERF_STRUCTURES'` | VRAI | FAUX : exclut la réutilisation pour les éléments de structure |

## 5. Impacts visibles pour les utilisateurs
- Messages supplémentaires en fin de `PASAPAS` (par exemple `PASAPAS : raideur recalculee 26 fois (PERF-RAID)`) : à prévoir si des outils analysent les sorties.
- Cast3M affiche « Utilisation de procedures personnelles » à l'arrêt : attendu tant que les procédures sont installées dans un répertoire utilisateur.
- Nouvelles entrées dans `PRECED . 'WTABLE'` (compteurs et copies de travail, purgées en fin d'appel sauf les compteurs).
- Aucun changement des résultats par défaut, aucun changement des formats de sortie ni des indices existants.

## 6. Validation

Les calculs ont été exécutés par le client (Cast3M 2024.1, Windows). Aucune de ces campagnes n'a été exécutée par le développeur.

### 6.1 Cube sous chargement cyclique (1 000 et 8 000 éléments)
12 scénarios (CHABOCHE, CHABOCHE avec rampe de T, MAZARS, MAZARS avec E(T) et rampe) × trois variantes (origine, niveau 1, niveau 2). Courbes force/section comparées à l'origine :

| Variante | Écart maximal sur la courbe |
|---|---|
| Niveau 1, 4 familles | 0 (identique) |
| Niveau 2, CHABOCHE avec rampe de T | 3,1E-5 |
| Niveau 2, MAZARS | 2,5E-4 |
| Niveau 2, MAZARS avec E(T) | 1,8E-3 |

L'écart entre maillages pour MAZARS (9E-3) est supérieur à tous ces écarts : il vient de la localisation numérique, pas des optimisations.

### 6.2 56 cas de la distribution (`dgibi`)
Chaque cas est exécuté trois fois dans la même session (origine, niveau 1, niveau 2) ; extrema de `DEPLACEMENTS`, `CONTRAINTES`, `TEMPERATURES` comparés à chaque pas. Détail par cas : `annexes/validation_detail_par_cas.md`, logs : `resultats/validation/`.

- **56 cas sur 56 : résultat OK**, aucune erreur Cast3M, mêmes contrôles internes des cas (neutralisés et comptés) dans les trois passes ; écart maximal 5E-17 au niveau 1, 3,4E-6 au niveau 2.
- **Activité des mécanismes** : raideur réutilisée dans 11 cas au niveau 1 et 17 au niveau 2 (endommagement 2D, axisymétrique, contraintes planes, dynamique : `desmorat` 299 réutilisations ; matériau dépendant de T constante ; coque endommageable `GLRC_DM` 74 réutilisations) ; HOOK évité dans 13 cas (1 399 appels) ; caractéristiques réutilisées dans 6 cas.
- **Exclusions vérifiées** : les 11 cas en grands déplacements (dont les 3 cas de contact et `dyna_nl1`) n'ont aucune réutilisation.
- **Cas témoins** : 39 cas où aucun mécanisme ne s'est déclenché. Leurs « accélérations » apparentes vont de 0,31 à 2,17 : c'est la dispersion de mesure du poste (charge de fond, dérive en session). Une accélération par cas n'est significative que si elle dépasse nettement cette dispersion.
- **Cas écarté** : `FissVoil` (cas 15). Son post-traitement `INITOU` désigne les nœuds par leur numéro global et suppose que le maillage du cas soit le premier de la session : il échoue dès la passe 1 (comportement d'origine) dès qu'un autre maillage existe. Sans lien avec les optimisations ; à valider seul dans une session neuve si nécessaire.

### 6.3 Couverture et limites de la validation
- Non couverts : pilotage indirect, THM, modal / fréquentiel (le cache de `PAS_MATE` s'en exclut explicitement), FEFP (exclu par construction).
- Niveau 2 : validé sur le cube et sur les 56 cas à la tolérance 1E-3 uniquement.
- L'empreinte de comparaison porte sur des extrema, pas sur les champs complets : un écart très localisé hors extrema passerait inaperçu.
- Cas de la distribution trop petits pour mesurer un gain (factorisation de quelques ms).

## 7. Gains

### 7.1 Mesures (maillage 1 000 éléments, benchmark v2, minimum de 2 répétitions)
Temps (ms) passés dans les opérateurs concernés, pour le calcul le plus rapide :

| Scénario | Temps total | Accél. | RESO | HOOK | VARI | Raideur réutilisée / recalculée | Écart |
|---|---|---|---|---|---|---|---|
| CHABOCHE, origine | 16 414 | 1,00 | 5 621 | 0 | 1 344 | 0 / 60 | — |
| CHABOCHE, niveau 1 | 10 977 | **1,50** | 1 646 | 0 | 0 | 59 / 1 | 0 |
| CHABOCHE, niveau 2 | 9 775 | 1,68 | 1 566 | 0 | 0 | 59 / 1 | 0 |
| CHABOCHE rampe T, origine | 15 900 | 1,00 | 5 715 | 0 | 1 359 | 0 / 60 | — |
| CHABOCHE rampe T, niveau 1 | 17 482 | 0,91 | 6 108 | 0 | 1 547 | 0 / 60 | 0 |
| CHABOCHE rampe T, niveau 2 | 13 446 | **1,18** | 2 920 | 0 | 1 540 | 40 / 20 | 3,1E-5 |
| MAZARS, origine | 30 458 | 1,00 | 9 191 | 4 139 | 0 | 0 / 85 | — |
| MAZARS, niveau 1 | 24 008 | **1,27** | 5 746 | 575 | 0 | 54 / 31 | 0 |
| MAZARS, niveau 2 | 20 981 | **1,45** | 4 829 | 590 | 0 | 59 / 22 | 2,5E-4 |
| MAZARS E(T), origine | 34 539 | 1,00 | 9 104 | 4 333 | 1 049 | 0 / 81 | — |
| MAZARS E(T), niveau 1 | 30 704 | 1,12 | 9 113 | 579 | 904 | 0 / 81 | 0 |
| MAZARS E(T), niveau 2 | 27 063 | **1,28** | 6 935 | 554 | 969 | 29 / 52 | 1,8E-3 |

**Lecture.** Le temps économisé est expliqué par les opérateurs évités à ±1,5 s près (par exemple MAZARS niveau 1 : 6,5 s économisées au total, 7,0 s sur RESO + HOOK). Les cas « ×0,91 » (CHABOCHE rampe T niveau 1) correspondent à un travail identique à l'origine (aucun mécanisme actif, mêmes temps d'opérateurs) : la dispersion de mesure est de l'ordre de ±10 % sur ces mesures répétées. Pour l'endommagement, le temps de `RIGI` reste inchangé : chaque pas coûte la construction de la raideur candidate (comparaison), qui est reprise gratuitement si elle est finalement utilisée.

### 7.2 Mesures (maillage 8 000 éléments, campagnes antérieures, versions intermédiaires des procédures)
Mêmes mécanismes, sans les raffinements v4 et v5 :

| Famille | Origine | Niveau 1 | Niveau 2 / tolérance |
|---|---|---|---|
| CHABOCHE, E(T), T constante | 150,9 s (RESO 96 s, VARI 17 s, RIGI 660 appels) | 56,1 s (**×2,7** ; RESO 17 s, RIGI 11 appels) | — |
| MAZARS | 301,3 s (RESO 158 s, HOOK 20,5 s) | 195,2 s (**×1,54**) ; HOOK seul 260,8 s (×1,16) | 166,4 s (**×1,81**, tolérance 1E-2, écart 3,5E-4) |

### 7.3 Gains attendus selon la classe de calcul
| Classe | Comportement | Gain attendu | Base |
|---|---|---|---|
| Plasticité, viscoplasticité sans paramètre externe variable, sans endommagement | inchangé (l'original conserve déjà la raideur) | ×1,0 | validé (39 cas témoins) |
| Matériau dépendant de T, T constante ; propriétés dépendant d'un champ constant | niveau 1 : raideur et matériau réutilisés | ×1,5 à ×2,7 selon la taille | mesuré |
| Matériau dépendant de T, T variable à chaque pas | niveau 1 : aucun gain (exact) ; niveau 2 : raideur réutilisée par intervalles | niveau 2 : ×1,2 à ×1,5 | mesuré à 1 000 éléments (×1,18), extrapolé aux grands maillages |
| Endommagement (éléments massifs), T absente ou constante | HOOK évité + raideur réutilisée quand l'endommagement est stable | ×1,3 (1 000 él.) à ×1,5 (8 000 él.) | mesuré |
| Endommagement avec T variable | niveau 1 : HOOK évité seul ; niveau 2 en plus | ×1,1 ; niveau 2 ×1,3 | mesuré |
| Structures (coques, poutres, joints) avec endommagement ou matériau variable | réutilisation autorisée | comme ci-dessus | `GLRC_DM` : 74 réutilisations sur 80 pas, gain non significatif à cette taille |
| Grands déplacements, FEFP, PICA (dont les 3 cas de contact testés, en grands déplacements) | exclus | ×1,0 | validé (11 cas) |
| Modèles < 500 éléments | factorisation de quelques ms | < ×1,1 | validation |

**Facteur taille.** Le gain croît avec le maillage car la part de `RESO` (factorisation) augmente : environ 30 à 35 % du temps à 1 000 éléments (mesuré), 50 à 60 % à 8 000.

**Estimer le gain sur un calcul réel.** Lire en fin de calcul les messages de `PASAPAS` : le rapport « raideur réutilisée / (réutilisée + recalculée) » donne la fraction de pas sans factorisation ; chaque factorisation évitée économise de l'ordre de 1 s à 8 000 éléments (CHABOCHE, MAZARS) ; chaque réévaluation de matériau évitée de l'ordre de 0,3 s.

## 8. Risques et parades
| Risque | Parade |
|---|---|
| Écart de résultat dû à une raideur réutilisée à tort | Niveau 1 : réutilisation uniquement si les champs sont identiques (`TOL` 1E-12 ou diagonale identique). Validé : écart ≤ 5E-17 sur 56 cas, 0 sur le cube |
| Mauvaise convergence au niveau 2 | Niveau 2 optionnel ; raideur reconstruite exactement après une non-convergence ; écarts mesurés ≤ 1,8E-3 |
| Cas non couvert | Interrupteur `'PERF_RAID' = FAUX`, ou dossier `procedur_origine/` pour retour arrière |
| Reprise d'un calcul créé avec les anciennes procédures | Valeurs par défaut des options et compteurs ajoutées dans `UNPAS` |
| Objets de travail conservés après modification du modèle ou du matériau | Purge en fin de `PASAPAS` |
| Sorties analysées par des outils | Messages supplémentaires en fin de calcul (§5) |

## 9. Déploiement recommandé
1. **Pilote (1 à 2 semaines)** : installer les procédures dans un répertoire utilisateur ; sur 3 à 5 calculs métier représentatifs, lancer une fois avec `'PERF_RAID' = FAUX` et une fois avec le défaut ; comparer les résultats et lire les compteurs.
2. **Généralisation du niveau 1** si les écarts sont nuls.
3. **Niveau 2** : à proposer en option aux utilisateurs de calculs thermomécaniques ou d'endommagement lourds, après comparaison sur leurs cas (tolérance de 1E-3 sur la diagonale ; écart attendu de l'ordre de la précision de convergence).
4. **Installer dans l'installation** (au lieu d'un répertoire utilisateur) uniquement après le pilote.

## 10. Limites et suites possibles
- **Le poste restant est `RESO`** (15 à 47 % du temps après optimisation, 47 % pour MAZARS à 8 000 éléments) : sa descente-remontée coûte environ 60 à 90 ms par résolution à 8 000 éléments. Pistes en Esope (sources `resou1`, `triang`, `mondes`, non modifiées) : solveur creux à dissection emboîtée, descente-remontée en simple précision, renumérotation ; gain potentiel élevé, effort et risque élevés.
- **Création et destruction d'objets** (`MENA`, `FINSI`, `DETR`) : ≈ 10 à 15 % du temps. Espacer les appels à `MENAGE` ne rapporte rien (coût proportionnel au volume libéré) ; la piste est de produire moins d'objets intermédiaires (opérateur Esope fusionnant `EPSI` / `COMP` / `BSIG`, gain estimé 5 à 10 %).
- Niveau 2 et cas de petite taille : la comparaison par pas a un coût du même ordre que la factorisation économisée.
- Validation à compléter : pilotage, THM, modal, FEFP ; `FissVoil` en session neuve.

## 11. Installation, vérification, retour arrière
Voir `LISEZMOI.md` : copier les quatre fichiers de `procedur/` dans un répertoire lu avant l'installation, vérifier avec `validation/valid_perf.dgibi` (`IFIN0 = 10` pour un essai rapide) et `benchmark/bench_cube.dgibi`. Retour arrière : retirer les fichiers ou restaurer `procedur_origine/`.

## 12. Contenu de la livraison
| Élément | Rôle |
|---|---|
| `procedur/` | les 4 procédures modifiées à installer |
| `procedur_origine/` | les 4 procédures d'origine (retour arrière) |
| `diff/perf_raid.diff` | différences exactes avec l'original |
| `validation/` | pilote de validation 3 passes (`valid_perf.dgibi`) et mode d'emploi |
| `benchmark/` | benchmark sur cube (`bench_cube.dgibi`) et mode d'emploi |
| `resultats/` | logs du benchmark et de la validation exécutés par le client |
| `annexes/validation_detail_par_cas.md` | résultat par cas de la validation |
| `MANIFESTE.txt` | empreintes SHA-256 de tous les fichiers |

## 13. Niveau 3 : rafraîchissement de la raideur en cas de stagnation (ajout, non exécuté)
**Origine.** Le profil à 1 000 éléments (MAZARS, console `IPROF0 = 1`) montre que 10 pas sur 76 (23, 24, 49 à 56) consomment 353 itérations sur 494 au niveau 1 (donc dans l'original, dont le chemin d'itération est identique) et 306 sur 447 au niveau 2. La raideur gelée en début de pas est trop raide quand l'endommagement progresse : critère qui décroît lentement, accélération `ACT3` annulée (« retrograde »), puis non-convergence et sous-pas.

**Mécanisme (`UNPAS`, bloc `PERF-RAID niveau 3` en fin d'itération).** Si le critère `XCONV` a décru de moins de 30 % en 3 itérations (`XCONV > 0,7 × XCONV(IT-3)`), reste supérieur à 10 fois la précision, à partir de l'itération 5, la raideur est reconstruite avec les variables internes de l'itération courante (`HOOK`, `RIGI`, comme en début de pas) puis `ZRAID = RH ET ZCLIM0`. Au plus 3 fois par pas, à 4 itérations d'intervalle ; l'accélération est suspendue 4 itérations (`ITACC = 4`). Le résidu et les critères d'arrêt ne changent pas : la solution convergée vérifie les mêmes critères. En fin de pas, la raideur du début de pas est restaurée pour l'estimation de `FNONL`, et `WTAB . 'RRRR'` et le cache du niveau 1/2 ne sont pas modifiés.

**Domaine.** Actif seulement si `'PERF_RAID_NIVEAU'` >= 3 (ou `'RAFRAICHISSEMENT_RAIDEUR'` VRAI), modèle d'endommagement/viscoendommagement/céramique (`IENDOM`, `IVIDOM`, `ICERAM`) et ni grands déplacements, dynamique, `K_TANGENT`, FEFP, rigidité constante, augmentation de rigidité, pilotage, contact, consolidation, fréquentiel, `NVSTNL`, adhérence, frottement, `MAN`, blocages variables. Hors de ce domaine, le comportement est celui du niveau 2.

**Diagnostic.** Compteur `NB_RAFRAICH` (message de fin de `PASAPAS`), message `PERF-RAID : stagnation a l'iteration N` à chaque rafraîchissement.

**Statut : non exécuté.** Gain attendu (hypothèse) : jusqu'à environ −40 % du temps de MAZARS (353 itérations ramenées à environ 120) ; sans effet sur CHABOCHE. À valider : `benchmark/bench_cube.dgibi` scénarios 13 et 14 (`LSCE = LECT 7 13 ;` puis `LECT 10 14 ;`), `validation/valid_perf3.dgibi` généré par `NIV_PASSE3=3 DGIBI_DIR=... OUT_DIR=... python3 tools/gen_validation.py`. Critère d'acceptation : écart de la courbe force/section avec l'original <= 10 × `PRECISION` relative, 56 cas du pilote sans écart au-delà de la tolérance du niveau 2, nombre d'itérations par pas inférieur ou égal.

**Premier essai (1 octobre 2026, `maz_perf3`, 1 000 éléments).** Résultat : « raideur rafraichie 0 fois » ; les itérations de chaque pas sont identiques à celles du niveau 2 (même écart de courbe 2,5E-4, accélération 1,62 par rapport à `maz_orig` de la même session : 30,4 s contre 49,2 s). Le rafraîchissement n'a donc jamais été déclenché : soit des procédures anciennes étaient chargées, soit une condition d'activation est fausse. Un message de diagnostic (« rafraichissement actif » ou « inactif, motifs : ... ») est maintenant affiché une fois par table. `maz_orig` confirme que le chemin d'itération du niveau 1 est celui de l'original (494 itérations, mêmes pas difficiles).
