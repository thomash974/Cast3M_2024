# Historique des décisions (session Claude.ai d'origine)

## Phase 0 : faisabilité du portage de UNPAS en Esope
- Analyse de `UNPAS` (≈ 4 400 lignes Gibiane) et de son usage dans `PASAPAS`. Conclusion : orchestration d'opérateurs déjà compilés (`COMP`, `RESO`, `BSIG`, `RIGI`, `EPSI`) ; le gain d'un portage serait limité à l'interprétation ; **profiler d'abord**.
- Un appel de procédure Gibiane depuis Esope est impossible (confirmé par l'utilisateur) : un portage complet est exclu.

## Phase 1 : cas test chronométré
- Cube unité, CHABOCHE2 (316L, données `BIBLIO`), traction-compression cyclique (d'après `traction316L.dgibi`), puis MAZARS (d'après `mazars2.dgibi`). Maillages 1, 10, 20 divisions.
- Corrections successives du script : `PRECISION` dépendant du maillage (le critère de `UNPAS` décroît en 1/NDIV²), indices de table avec espaces (`TRES1 . 1 . 'HORL'`), pilotage par table de scénarios (procédure `PSCEN`), fichiers de log (voir `LECONS_CAST3M.md`), répétitions et temps minimal.

## Phase 2 : profilage
- À 1 000 éléments, 8 000 éléments (60 pas) : `RESO` 60 %, `VARI` 10 %, `MENA` 5 %, `COMP` 5 %, `FINSI`/`DETR`/`ENLE` 10 % ; interprétation `UNPAS` < 1 %.
- `RIGI` appelé à chaque pas : la raideur est reconstruite et refactorisée à chaque pas. Essai « matériau constant, sans chargement thermique » : RIGI 11 appels, temps divisé par 2,7 → piste confirmée.

## Phase 3 : recherche de la cause (archive PCW_24 fournie par l'utilisateur)
- `PAS_VERM` pose `WTAB . 'RECALCUL'` dès que `LDEVA` contient autre chose que `'ALPH'` ; `UNPAS` pose `RECARI` pour `IENDOM`/`IVIDOM`/`ICERAM` ; `PASAPAS` détruit `WTAB . 'RRRR'` quand `RECARI` est vrai.
- La raideur n'est qu'une matrice d'itération (méthode des résidus) : la conserver ne change pas la solution.

## Phase 4 : itérations du correctif
- **v1** : comparaison de l'état complet (`ETATRI` contre l'état stocké) : inopérante (l'état contient temps, déplacements, contraintes…).
- **v2** : comparaison des seules composantes de `WTAB . 'LDEVA'` : fonctionne pour CHABOCHE (59 réutilisations / 60 pas, écart nul) ; MAZARS : `'EPTI'` (déformation équivalente courante, source `cmazar.eso`) change à chaque pas, seule `'D'` pilote la raideur.
- **Endommagement** : comparaison de variables internes nommées → remplacée par la comparaison de la **diagonale** de la raideur reconstruite (erreur 552 : `MAXI` impossible sur la composante `MAHO` de type matrice de `HOOK`).
- **Cache `PAS_MATE`** (évite `VARI`), **HOOK évité** (la matrice de Hooke passée à `EPSI` n'est lue que par l'élément DST), option de menage espacée essayée puis **abandonnée** (`MENAGE` coûte proportionnellement au volume libéré : 12 appels au lieu de 60 ne changent pas le temps total).
- **v4** : HOOK évité pour tous les modèles sans coque (au lieu d'une liste blanche d'éléments massifs), réutilisation autorisée pour les structures, **niveau 2** (réutilisation approchée), compteurs `NB_HOOK_EVITE` et `NB_RAIDEUR_CALC`.
- **v5** : la raideur candidate construite pour une comparaison est reprise par la reconstruction (pas de HOOK + RIGI en double).

## Phase 5 : validation sur les cas de la distribution
- 57 cas du répertoire `dgibi` retenus (endommagement, matériau dépendant de T, lois, éléments coque / poutre / fibre / joint / tuyau, grands déplacements, dynamique, contact). Pilote généré (`tools/gen_validation.py`) : chaque cas dans une procédure, trois passes (origine / niveau 1 / niveau 2), comparaison d'empreintes (max, min, max abs de `DEPLACEMENTS`, `CONTRAINTES`, `TEMPERATURES`).
- Erreurs rencontrées et corrigées (toutes dans le pilote) : `TEMP 'HORL'` / `MATE` masqués par des variables d'un cas précédent → cas dans des procédures ; `TAB2 = PASAPAS TAB1 ;` mal injecté (deux signes `=`) ; messages `CHAI` mal séparés ; console rendue muette par `OPTI 'IMPR'` → `SORT 'CHAI'` ; ligne de synthèse vide.
- Cas 15 `FissVoil` : erreur 217 dans `INITOU` dès la passe 1 (numéros de nœuds globaux) : écarté.
- Résultat : 56 cas sur 56 OK.

## Phase 6 : benchmark et analyse du bruit
- Benchmark cube (4 familles × 3 variantes). Les premiers « gains négatifs » étaient du bruit : 39 cas témoins sans mécanisme actif donnent 0,31 à 2,17 ; l'ordre des passes (toujours origine d'abord) biaisait. Corrections : alternance de l'ordre, répétitions (temps minimal), **temps par opérateur** (`TEMP 'NOEC'`), qui expliquent les gains à ±1,5 s.

## Phase 7 : livraison
- Paquet `livraison/` (rapport, procédures, diff, tests, résultats, manifeste), puis cette archive de reprise.

## Phase 8 : reprise sous Claude Code (pistes Esope, profil, niveau 3)
- **Piste RESO simple précision** : abandonnée. Banc Fortran `tools/bench_reso/refine_sp.f90` : avec le critère de `MONDES` (`crite = crit*sqrt(xzprec*xszpre)`), la descente-remontée en simple précision demande >= 2 passes (gain nul) et 31 passes sur matrice mal conditionnée (au-delà des 10 permises : erreur 1128). Seule variante viable : critère relâché sous option (non faite).
- **Opérateur fusionné EPSI/COMP/BSIG** : abandonné après profil (`IPROF0`, `TEMP 'IMPR' 'SOMM'`). À 8 000 éléments : RESO 28 %, COMP+FINS 22 %, chaîne fusionnable 18 %, MENA 7 %, temps non attribué 21 % ; gain réaliste de la fusion <= 7 à 8 %.
- **Correction de mesure** : `TEMP 'NOEC'` renvoie un temps par assistant ; la somme comptait COMP deux fois à 1 000 éléments (2 assistants). `TOPER` du benchmark prend maintenant le maximum. Les anciennes colonnes COMP sont à diviser par 2 à cette taille.
- **Parallélisme** (`IPROC0` du benchmark, indice `'PROCESSEURS'`) : CHABOCHE à 1 000 éléments, défaut 10,8 s, mono 9,0 s, COMPORTEMENT 9,2 s, AUTOMATIQUE 18,2 s ; à 8 000 éléments, défaut 46,0 s, mono 58,4 s, COMPORTEMENT 49,5 s (une seule mesure chacune, 11 assistants imposés contre 2 au défaut à 1 000 éléments). Point d'équilibre estimé vers 2 500 éléments ; non traité.
- **Itérations** (consoles 1 000 éléments) : CHABOCHE 204 itérations (47 pas à 3, 2 à 4, 11 à 5), pas d'itération évitable ; la « première résolution » de chaque pas (60 RESO sur 264) sert à la norme `XDENO` et n'est pas un doublon (RESIDU modifié par l'initialisation à partir de la solution précédente). MAZARS : 10 pas sur 76 (23, 24, 49 à 56) = 353 itérations sur 494 au niveau 1 (chemin de l'original) et 306 sur 447 au niveau 2 : stagnation due à la raideur gelée quand l'endommagement progresse.
- **Niveau 3** (livré, non exécuté) : rafraîchissement de la raideur en cas de stagnation, voir `livraison/RAPPORT_LIVRAISON.md` §13.
