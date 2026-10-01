# Leçons Cast3M / Gibiane (pièges rencontrés) et faits relevés dans les sources

## 1. Syntaxe et interpréteur
| Piège | Symptôme | Parade |
|---|---|---|
| Variable homonyme d'un mot-clé ou d'un opérateur (`KK`, `N`, `M`, `TEMP`…) créée dans la même session | erreur 11 « résultat en trop » (`MATE … KK EVKK`, `VTH = TEMP 'HORL'`) | exécuter chaque cas dans une `DEBPROC` (variables locales) ; suffixer les noms |
| `TAB1.1.'X'` | lu comme le mot `'1'` (erreur 535) | `TAB1 . 1 . 'X'` avec espaces |
| `-1.` dans une liste d'arguments | lu comme soustraction | variable (`TOFF0 = -1. ;`) |
| `X = PASAPAS TAB1 ;` avec injection préalable `TAB1 . 'PERF_RAID' = … ;` collée | erreur 1014 « deux signes = » à la **lecture de la procédure** | l'injection doit précéder l'instruction entière (`TAB1 . … = … ; TAB2 = PASAPAS TAB1 ;`) |
| `'MAXI' 'ABS'` sur un MCHAML dont une composante est une matrice (`MAHO` de `HOOK`) | erreur 552 | comparer `EXTR RH 'DIAG'` (CHPOINT) de la raideur reconstruite |
| `OPTI 'IMPR' 'fichier'` puis `OPTI 'IMPR' 6` | la console n'est pas rétablie (le fichier garde l'unité 6) | `OPTI 'SORT'` + `SORT 'CHAI'` pour les fichiers ; fermer par un fichier vide |
| Écriture de messages avec `MESS` | textes et nombres collés (`passe1 / 2`, `origine0`) | `CHAI` + séparateurs `' '` (voir `CLAUDE.md`) |
| `K1>2` dans `CHAI` | lu comme un mot, jamais évalué | `' '` explicites ; `>N` seulement derrière un littéral entre quotes |
| Chaîne se terminant par un espace dans `CHAI` | espace supprimé | espace initial ou objet `' '` |
| Directive `temps;` dans un cas | affichage seul, mais voir variable `TEMP` | commentée dans le pilote |
| `ERRE n` dans les cas de test | arrête la session | neutralisé par compteur (table `VTCT`) dans le pilote |
| Cas tests qui créent le premier maillage de la session (`NOEUD i` globaux, `FissVoil` / `INITOU`) | erreur 217 dès que d'autres maillages existent | session neuve, ou cas écarté |
| Plusieurs appels `PASAPAS` / tableaux `TEMP` cumulés sur la session | le tableau des procédures n'est **pas** remis à zéro par `TEMP 'ZERO'` (celui des opérateurs l'est) | ne pas lire les temps de procédures par scénario |
| Dérive des temps en session (mémoire Esope remplie : `DETR` 8 ms → 227 ms) | calcul à 1 élément 0,8 s puis 1,4 à 2,1 s | comparer au sein d'un même job, alterner l'ordre, répéter |

## 2. Faits sur UNPAS / PASAPAS (version 2024)
- `PAS_VERM` (ligne ≈ 40) : `WTAB . 'RECALCUL' = VRAI` et `WTAB . 'MATVAR' = VRAI` si `EXTR MA 'DEVA'` contient autre chose que `'ALPH'` seul ; `PAS_DEFA` définit `WTAB . 'LDEVA'` (≈ ligne 1667).
- `UNPAS` (≈ lignes 180-196) : `'SI' WTAB . 'RECALCUL'` pose `RECARI`, `RECADET`, `REA_GEOM` ; `'SI' ('OU' ('OU' IENDOM IVIDOM) ICERAM)` pose `RECARI` ; la reconstruction de `RRRR` (HOOK + RIGI pour les lois d'endommagement, RIGI sinon, PICA si `LAG_TOT = 1`) est conditionnée par `RECARI`, `IRAUG`, absence de `RRRR`, `AA4` (condition de l'original dont le rôle exact n'a pas été relu).
- `PASAPAS` (≈ lignes 871-873) : en fin de pas, si `WTAB . 'RECARI'` : `ENLEVER WTAB 'RRRR'`.
- Classes d'endommagement détectées dans `PAS_DEFA` (≈ ligne 1612) : `PLASTIQUE_ENDOM`, `ENDOMMAGEMENT`, `ENDOMMAGEABLE`, `VISCODOMMAGE`.
- Le `ITCAR` local d'`UNPAS` (ligne ≈ 623) désigne la présence de caractéristiques de structure (`EPAI`, `INRY`, `MODS`, joints) : il n'implique pas de grands déplacements.
- Les cas non convergents créent des sous-pas (`knoconv > 1`) ; l'augmentation de rigidité (`IRAUG`, `AUTAUG`) utilise `RH` et `RIG_AUG` calculés lors de la reconstruction.

## 3. Faits sur les sources Esope
- **EPSI** (`epsi.eso`, `epsi1.eso`, `epsi3.eso`) : l'argument « matrice de Hooke » ne sert (`IMAT = 2`) que pour l'élément `MELE = 93` (coque DST) ; pour les massifs (`EPSI2`) il est ignoré. D'où le HOOK évité hors éléments de coque.
- **MAZARS** (`cmazar.eso`, `idvar5.eso`) : variables internes `EPTI` (déformation équivalente **courante**) et `D` ; seule `D` pilote la raideur endommagée.
- **TEMP 'NOEC'** (`tempor.eso`) : table `TEMPS_HORLOGE`, `TEMPS_CPU`, `TEMPS_ATTENTE`, `APPELS`, `EFFICACITE`, indexée par nom d'opérateur, valeurs = LISTENTI (un élément par assistant) ; entrées `INITIAL` et `DERNIER_APPEL`.
- **RESO** : `resou.eso` → `resou1.eso` → `triang.eso` (assemblage + factorisation `CHOLE`, solveur à profil LDLt) puis `mondes.eso` / `monde1/2.eso` (descente-remontée). Pas d'OpenMP dans les sources lues ; le parallélisme observé (CPU / horloge ≈ 2,5) vient du mécanisme des assistants. La boucle sur les seconds membres est la seule parallélisable directement ; PASAPAS n'en a qu'un par résolution.
- **MENAGE** (`menage.eso`, `menag1..7.eso`) : coût proportionnel au volume d'objets libérés et non au nombre d'appels : espacer les `MENA` ne rapporte rien.

## 4. Pistes Esope identifiées (non réalisées)
1. `RESO` : descente-remontée en simple précision (la raideur n'est qu'une matrice d'itération), renumérotation (`RENU`) sur maillages réels, solveur creux à dissection emboîtée ; mesurer d'abord avec `TEMP` autour de `MONDES` / `TRIANG`.
2. Opérateur fusionné `EPSI` / `COMP` / `BSIG` + critère de convergence : moins d'objets intermédiaires (création/destruction ≈ 10-15 % du temps), gain estimé 5 à 10 %. Ajout d'un opérateur : guide `base_connaissance/01_guide_gibiane_esope.md` §3.4 (`MDIR3`/`NDIR3`, étiquette `100+II` dans `pilot.eso`).
3. `VARI` (évaluation du matériau en T variable à chaque pas, ≈ 0,29 s par appel à 8 000 éléments) : interpolation des courbes une fois par valeur distincte de paramètre.

## 5. Particularités du pilote de validation (`tools/gen_validation.py`)
- Chaque cas = procédure `VC<k>` (arguments `VPSW` logique, `VNIV` entier, `VTFPR` table d'empreintes, `VTCT` table de compteurs `ERRE`, `IECHO0`) ; injections : `TAB . 'PERF_RAID' = VPSW ; TAB . 'PERF_RAID_NIVEAU' = VNIV ; [X =] PASAPAS TAB ; FPREC TAB VTFPR ;`.
- Neutralisations dans les corps de cas : `FIN ;` final commenté, `ERRE 0|n|'texte'` → compteurs, `ECHO n` → `ECHO IECHO0`, `TRAC 'X'` → `'PSC'`, `@EXCEL1`, `temps;` commentés.
- Cas exclus de la génération : ceux qui définissent des procédures (`DEBPROC`) ou lisent/écrivent des fichiers (`LIRE`, `ACQU`, `REST`, `SAUV`).
- Ordre des passes alterné d'un cas à l'autre (1-2-3 / 3-2-1) ; suivi : console (`>>> Cas k` / `<<< Cas k`) + `valid_avancement.log` ; sorties : `valid_<cas>.log`, `valid_synthese.log`.

## 6. Compléments (reprise Claude Code)
- **`EGA` sur des mots** : forme préfixe obligatoire, `EGA MPROC0 'DEFAUT'` (la forme infixe `MPROC0 EGA 'DEFAUT'` ne marche que pour les nombres).
- **Troncature à 4 caractères** : `COMPORTEMENT` est lu comme l'opérateur `COMP`. Éviter ce mot dans un script (utiliser un entier) ; dans `PAS_DEFA` il est protégé par `'MOT' 'COMPORTEMENT'`.
- **`TEMP 'IMPR' 'SOMM'` / `TEMP 'NOEC'`** : maximum de l'horloge sur les assistants (le texte de la notice le dit) ; sommer les `LISTENTI` de `TEMPS_HORLOGE` double-compte les opérateurs parallèles.
- **`FINS` dans le profil** : le temps entre un `FINSI` et la lecture de l'instruction suivante est imputé à `FINS` (pilote : `GOTO 2` ; `CHKESC` fusion des objets parallèles, ménage automatique, interprétation). Il inclut du travail des assistants (CPU >> horloge).
- **Parallélisme de PAS_DEFA** : `NBPART` = min(assistants, éléments / 400) ; `b_PARA` = 2 (automatique) si éléments par partie > 200 ; un `'PROCESSEURS'` imposé saute cette réduction (11 partitions à 1 000 éléments).
- **Mesure sans exécution** : un banc Fortran (gfortran) suffit pour vérifier un comportement numérique hors Cast3M (`tools/bench_reso`).
