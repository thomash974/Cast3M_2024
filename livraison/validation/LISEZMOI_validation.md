# Validation des optimisations PERF-RAID sur les cas tests de la distribution

## Principe
`valid_perf.dgibi` exécute 57 cas du répertoire `dgibi`, chacun dans une procédure (variables locales), en **trois passes** :
- passe 1 : `'PERF_RAID'` FAUX (comportement d'origine) ;
- passe 2 : `'PERF_RAID'` VRAI, **niveau 1** (résultats identiques attendus, tolérance `TOLV0 = 1.E-8`) ;
- passe 3 : `'PERF_RAID'` VRAI, **niveau 2** (réutilisation approchée de la raideur, écart faible attendu, tolérance `TOLV3 = 5.E-3`). Désactivable par `IPASS3 = FAUX`.

Pour chaque appel de `PASAPAS`, une procédure d'empreinte relève, pour chaque pas stocké et pour `DEPLACEMENTS`, `CONTRAINTES` et `TEMPERATURES`, le maximum en valeur absolue, le maximum et le minimum. Les passes 2 et 3 sont comparées à la passe 1.
Les contrôles internes des cas (`ERRE`) sont neutralisés et comptés ; leur nombre d'échecs doit être identique dans toutes les passes.

**Benchmark.** Le chronométrage est activé (`ITEMPS0 = VRAI`) : le pilote affiche pour chaque cas les temps des trois passes et les accélérations, puis des temps cumulés. Les cas de la distribution sont courts (quelques ms à quelques secondes) : les accélérations par cas sont indicatives ; utiliser `NREP0 = 3` ou plus pour lisser. Pour un benchmark représentatif (maillage réaliste, rampe de température), utiliser `../benchmark/bench_cube.dgibi`.

## Mise en route
1. Copier dans le répertoire d'exécution de Cast3M : `valid_perf.dgibi` et les quatre procédures du dossier `procedur/`
   (`unpas.procedur`, `pas_mate.procedur`, `pasapas.procedur`, `pas_defa.procedur`).
2. Lancer `valid_perf.dgibi`. La fin de la session doit afficher « Utilisation de procedures personnelles ».
3. Suivre l'exécution (voir ci-dessous) puis récupérer les résultats dans le répertoire d'exécution.

## Isolation des cas (pourquoi chaque cas est une procédure)
Les deux erreurs 11 rencontrées (`endoaxi2` : `TEMP 'HORL'` ; `fluaendo` : `KK EVKK` dans `MATE`) avaient la même cause probable :
dans une même session, une variable créée par un cas précédent portait le nom d'un opérateur (`TEMP`) ou d'un mot-clé de `MATE` (`KK`, `N`, `M`, …)
et le remplaçait par sa valeur. Chaque cas est donc exécuté dans une procédure `VC<k>` dont les variables sont locales : il ne voit plus rien des cas précédents.
Les compteurs des `ERRE` neutralisés passent par une table (`VTCT`) fournie en argument. Le chronométrage (`ITEMPS0`) reste désactivé par défaut ; il peut être réactivé.
Si un cas échoue uniquement parce qu'il ne peut pas s'exécuter dans une procédure, le sauter par `TSKIP . <k> = VRAI ;` et me transmettre l'erreur.

## Reprendre sans tout relancer
Les cas déjà validés ont chacun leur fichier `valid_<cas>.log` : il n'est pas nécessaire de les refaire. Pour reprendre au cas k, régler `IDEB0 = k` en tête de `valid_perf.dgibi`.
Le fichier `valid_synthese.log` (et `valid_avancement.log`) ne listent que les cas exécutés pendant la session en cours : pour un bilan complet, rassembler les lignes `RESULTAT :` des fichiers `valid_<cas>.log`.

## Cas 15 (FissVoil) écarté
Son post-traitement (procédure `INITOU`, appelée après `PASAPAS`) parcourt les nœuds par leur **numéro global** (`NOEUD IBOUBE`, `IBOUBE` de 1 à `NBE`) : cela suppose que le maillage du cas soit le premier créé dans la session. Dès qu'un autre maillage existe (cas précédents, ou passe précédente du même cas), les listes construites n'ont plus la même longueur et l'erreur 217 apparaît, en passe 1 (optimisations inactives). Ce n'est donc pas lié aux optimisations ; le cas est écarté (`TSKIP . 15 = VRAI ;`). Pour le valider, l'exécuter seul dans une session neuve.

## Mesure des temps
- L'ordre des passes est alterné d'un cas à l'autre (1-2-3 puis 3-2-1), pour compenser la dérive des temps au cours d'une session.
- Sur la campagne précédente, les 39 cas où aucun mécanisme ne s'est déclenché (code exécuté identique dans les trois passes) donnent des « accélérations » de 0,31 à 2,17 : c'est la dispersion de mesure sur ce PC. Une accélération par cas n'est significative que si elle dépasse nettement cette dispersion ; utiliser `NREP0 = 3` et le benchmark cube pour mesurer le gain.

## Format des messages
Tous les messages sont construits avec l'opérateur `CHAI`, puis affichés par `MESS` et écrits par `SORT 'CHAI'`.
Règles retenues (essais de `CHAI aaa ' sur ' bbb`) :
- `CHAI` supprime les espaces **terminaux** d'une chaîne (`'sur '` donne `4sur5`) mais conserve les espaces **initiaux** (`' sur'` donne `4 sur5`) ;
- un objet `' '` isolé est conservé : les séparateurs sont donc des objets `' '` explicites (`CHAI aaa ' ' 'sur' ' ' bbb` donne `4 sur 5`) ;
- les options `>N` et `<N` ne sont reconnues que derrière une chaîne entre quotes : `K1>2` est lu comme le mot `K1>2` et n'est pas évalué. Elles ne sont plus utilisées ;
- l'option `*N` (objet cadré à droite sur la colonne absolue N) fonctionne derrière un entier, un flottant ou une chaîne entre quotes ; elle sert à aligner les tableaux (`valid_avancement.log`, `valid_synthese.log`). Les noms de cas, mots sans largeur fixe, sont placés en fin de ligne pour ne pas être alignés ;
- les flottants sont formatés par `'FORMAT' '(1PE10.3)'` ou `'FORMAT' '(F6.2)'`.

## Suivre l'avancement et repérer une erreur
Rien n'est plus redirigé par défaut : le calcul s'affiche dans la console.
- **Début d'un cas :** `>>> Cas k / N : nom`, puis `passe 1 / 2` (optimisations inactives) et `passe 2 / 2` (actives).
- **Fin d'un cas :** `<<< Cas k / N : nom : OK` (ou `ECART`) avec l'écart et le nombre de réutilisations de la raideur.
- **Fin normale :** `VALIDATION TERMINEE : N cas, dont x en ecart`.
- **Erreur :** message `ERREUR nn` en clair dans la console, suivi de `Arret du programme Cast3M`. Si ce texte apparaît **avant** `VALIDATION TERMINEE`, l'exécution s'est arrêtée : le dernier `>>> Cas` affiché désigne le cas en cause.
- **Fichier `valid_avancement.log`** (toujours écrit, rouvrable à tout moment) : cas et passe en cours, puis liste des cas terminés avec leur résultat. Après un arrêt, il indique où reprendre. Il est réécrit à chaque changement de cas ou de passe.
- **Fichiers de résultats :** `valid_<cas>.log` (un par cas), `valid_synthese.log` (à la fin). `valid_inutile.tmp` est un fichier vide qui sert à fermer les fichiers de sortie : il peut être supprimé.

Réglages en tête de `valid_perf.dgibi` :
| Variable | Défaut | Effet |
|---|---|---|
| `IECHO0` | 0 | verbosité : 0 = erreurs et avertissements, 1 = ajoute les instructions interprétées (très verbeux), −1 = erreurs seules |
| `ITRACE0` | FAUX | VRAI : tout l'affichage va dans `valid_trace.log` et la console reste muette (elle ne peut pas être rétablie) ; à réserver à l'analyse d'un seul cas (`IDEB0 = IFIN0 = k`). Le suivi passe alors par `valid_avancement.log` |
| `IDEB0`, `IFIN0` | 1, N | premier et dernier cas exécutés |
| `ITEMPS0` | FAUX | chronométrage des deux passes |

## Cas d'une erreur Cast3M
Une erreur arrête la lecture du fichier. La cause est affichée dans la console (nom de l'opérateur, ligne, procédure) ; copier ce texte, ou relancer le seul cas en cause avec `ITRACE0 = VRAI`, puis lire la fin de `valid_trace.log`.
Reprise : régler `IDEB0` sur le numéro du cas suivant (ou du cas en cause pour le relancer) (et `IFIN0` au besoin) puis relancer. Un cas trop long se saute avec
`TSKIP . <numéro> = VRAI ;` (ligne commentée en tête de fichier). Pour un essai rapide, lancer d'abord `IFIN0 = 10`.

## Lecture des résultats
| Indicateur | Attendu |
|---|---|
| `RESULTAT : OK` | écart ≤ 1E-8, mêmes échecs internes dans les deux passes |
| `Nombre de valeurs comparees` | non nul (sinon les résultats n'étaient pas stockés : cas non significatif) |
| `Classes` (somme) | 1 : matériau dépendant de paramètres externes (MATVAR), 10 : endommagement, 20 : viscodommage, 100 : grands déplacements |
| `Raideur reutilisee` / `caracteristiques reutilisees` | > 0 pour les cas de classe 1 ou 10 sans grands déplacements ; 0 pour les cas exclus (grands déplacements, contact, etc.) |
| Temps des deux passes | `ITEMPS0 = VRAI` pour activer le chronométrage (désactivé par défaut) ; information seulement (le calcul de la passe 2 n'est jamais plus coûteux qu'à quelques pour cent près) |

Un cas en écart n'est pas nécessairement un défaut des optimisations : vérifier d'abord si le nombre de réutilisations est nul.
Dans ce cas, la réutilisation n'a pas servi, et l'écart vient d'ailleurs (non-déterminisme du calcul parallèle, par exemple).

## Ce que la liste couvre
- **Endommagement** (classe UNPAS `IENDOM`) : MAZARS, lois 2D/axi/contraintes planes, avec thermique, avec dynamique, et structures (béton armé, voile, coque GLRC).
- **Matériau dépendant de T ou d'un paramètre externe** : cache de `PAS_MATE` et réutilisation de la raideur (classe `MATVAR`).
- **Lois de comportement** : plasticité, viscoplasticité, fluage, Gurson, poudre, béton.
- **Types d'éléments** : massifs (pris en charge par la suppression du HOOK), coques, poutres, fibres, tuyaux, joints.
- **Cas où les optimisations doivent rester inactives** : grands déplacements, hyperélasticité, contact, dynamique.

## Liste des cas
| N° | Cas | Classe visée |
|---|---|---|
| 1 | `mazars` | endommagement MAZARS, QUA4 CP |
| 2 | `mazars2` | endommagement MAZARS, cycles |
| 3 | `compression` | endommagement, compression |
| 4 | `endoaxi1` | endommagement, axisymetrique |
| 5 | `endoaxi2` | endommagement + thermique, axi |
| 6 | `endoaxi3` | endommagement + thermique, axi |
| 7 | `endocp1` | endommagement, contraintes planes |
| 8 | `fluaendo` | fluage + endommagement + thermique |
| 9 | `relaxendo` | relaxation + endommagement + thermique |
| 10 | `GTN_C20R` | endommagement ductile (GTN) |
| 11 | `mvm_bcn` | endommagement |
| 12 | `desmorat` | endommagement + dynamique |
| 13 | `betdynlmt` | endommagement + dynamique, beton |
| 14 | `ricbet_uni_1` | beton arme, endommagement (structure) |
| 15 | `FissVoil` | endommagement, voile (structure) |
| 16 | `GLRC_DM` | coque + endommagement (HOOK conserve) |
| 17 | `traction316L` | T uniforme, E(T) |
| 18 | `test_vari_props` | proprietes variables |
| 19 | `dilthe` | dilatation thermique |
| 20 | `char_constant` | chargement constant, thermique |
| 21 | `thgdep1` | thermique + grands deplacements |
| 22 | `ther_meca_coque` | thermomecanique coque |
| 23 | `dependance` | dependance parametres, coque |
| 24 | `thme1` | thermo-mecanique |
| 25 | `phase_03` | metallurgie/phases |
| 26 | `plas5` | plasticite |
| 27 | `plas_incomp` | plasticite incompressible |
| 28 | `chaboche1` | viscoplasticite Chaboche/Onera |
| 29 | `chaboche2` | viscoplasticite |
| 30 | `norton_tra1` | fluage Norton |
| 31 | `ddi` | visco |
| 32 | `tufi` | plasticite tuyau fibre |
| 33 | `fluage_maxwell_1` | fluage Maxwell |
| 34 | `poudre3` | poudre |
| 35 | `gurson` | Gurson |
| 36 | `beton` | beton |
| 37 | `ottovari_traction` | plasticite |
| 38 | `plas8` | coque plastique |
| 39 | `ohno2` | coque visco Ohno |
| 40 | `guionnet_tra` | coque visco |
| 41 | `g_c_etoile_coque_1` | coque visco |
| 42 | `PoutreConsole_Plas_EcrouCineLine` | poutre plastique |
| 43 | `fluage_fibre_norton_1` | poutre fibres fluage |
| 44 | `test_cisailnl` | poutre cisaillement non lineaire |
| 45 | `cou22` | joint |
| 46 | `testjoi1ani` | joint anisotrope |
| 47 | `joi_eli` | joint elastique |
| 48 | `jointsoft1` | joint adoucissant |
| 49 | `gdep2` | grands deplacements coque |
| 50 | `gdef2` | grandes deformations |
| 51 | `Mooney_LRGTreloar_Traction` | hyperelastique |
| 52 | `gdtract` | grands deplacements + endommagement (reutilisation exclue) |
| 53 | `newmark1` | dynamique Newmark poutre |
| 54 | `dyna_nl1` | dynamique non lineaire |
| 55 | `Contact2D` | contact 2D |
| 56 | `Coulomb3D` | contact frottant 3D |
| 57 | `contact2D-adhe` | contact adherent |

## Limites
- L'empreinte porte sur des extrema, pas sur les champs complets : un écart très localisé hors extrema passerait inaperçu.
- La passe 1 utilise les procédures modifiées avec l'interrupteur à FAUX. Le chemin d'origine a été vérifié sur la campagne cubique (mêmes compteurs d'appels que les procédures officielles),
  mais pas sur ces cas. Un contrôle complémentaire consiste à lancer une fois le fichier sans les procédures modifiées : les deux passes sont alors identiques par construction, ce qui valide le pilote lui-même.
- Les cas qui appellent `PASAPAS` dans une procédure, ou qui lisent/écrivent des fichiers, n'ont pas été retenus.

## Niveau 3 (rafraîchissement de la raideur en cas de stagnation)
`NIV_PASSE3=3 DGIBI_DIR=PCW_24/dgibi OUT_DIR=livraison/validation python3 tools/gen_validation.py` génère `valid_perf3.dgibi` : identique à `valid_perf.dgibi` mais la 3e passe utilise `'PERF_RAID_NIVEAU' = 3`. Même mode d'emploi ; les compteurs de `PASAPAS` incluent « raideur rafraichie ». Non exécuté.
