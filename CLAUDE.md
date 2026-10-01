# CLAUDE.md : projet PERF-RAID (accélération de PASAPAS / UNPAS, Cast3M 2024.1)

Ce fichier est lu automatiquement par Claude Code. Il reprend les conventions de travail de la session d'origine. Contexte complet : `HANDOFF.md`.

## Rôle et style de réponse
- Assistant Cast3M (Gibiane / Esope). Réponses **en français, concises**.
- Ne pas poser de question sauf blocage réel : choisir des valeurs standard et les indiquer.
- Réponse finale courte, trois points maximum : choix retenus, ce qui a été contrôlé, points à vérifier au premier lancement.
- Ne pas recopier le code dans la réponse quand il est livré dans un fichier.
- Ce qui n'est pas vérifié dans la documentation ou les sources est listé en « Points à vérifier » ; **ne jamais inventer une syntaxe**.

## Documentation (avant d'écrire du code)
1. Lire `base_connaissance/00_LISEZ_MOI.md`.
2. Ordre de recherche : cas test proche (`base_connaissance/09_catalogue_dgibi.md`, `10_exemples_dgibi_*.md`, ou le répertoire `PCW_24/dgibi`), notice de chaque opérateur utilisé (`06_notices_*`, `06c` pour MODE/MATE/OPTI, ou `PCW_24/notice`), puis sources (`PCW_24/sources`, `PCW_24/procedur`).
3. L'archive `PCW_24` (sources Cast3M 2024) n'est pas fournie ici : la placer à la racine du dépôt (`PCW_24/procedur`, `sources`, `dgibi`, `notice`). Voir `HANDOFF.md` §2.

## Règles d'écriture Gibiane
- Indentation de 4 espaces par niveau (SI/SINON/FINSI, REPETER/FIN, DEBPROC/FINPROC, lignes de continuation).
- Dans un fichier neuf : pas de quotes autour des opérateurs et directives (MODE, MATE, BLOQ, EVOL, PROG, SI, REPETER, EXP, <EG, ET…) ; quotes autour des mots-clés (`'MECANIQUE'`, `'YOUN'`, `'DIMP'`, `'PAS'`, `'TITR'`), des indices de table (`TAB1 . 'MODELE'`) et des textes.
- **Dans une procédure standard existante** (`UNPAS`, `PASAPAS`, `PAS_DEFA`, `PAS_MATE`) : suivre le style du fichier (opérateurs entre quotes) : cela protège contre une variable utilisateur homonyme d'un opérateur.
- Commentaires : ligne commençant par `*` en colonne 1 (jamais indentée). Fichier terminé par `FIN ;`.
- **Variables** : jamais le nom d'un mot-clé ou d'un opérateur (KTR0, ACOM, BCOM, ATRA, BTRA, BETA, YOUN, NU, EPSI, DEPL, SIGM, TEMP…). Une variable homonyme remplace le mot-clé de `MATE` par sa valeur (ou masque l'opérateur). Utiliser un suffixe (`YOUN0`, `EPST0`).
- **Entrées de table séparées par `" . "` avec espaces** : `TAB1 . 'CONTRAINTES' . 1 ;` (jamais `TAB1.'CONTRAINTES'.1` : `TRES1.1.'X'` est lu comme le mot `'1'`).
- Structure type d'un cas : paramètres physiques en tête (unités SI), interrupteur `GRAPH = VRAI/FAUX`, calcul, post-traitement, vérification contre la solution analytique si elle existe (`ERRE` en cas d'écart), tracés.
- Un `-1.` littéral dans une liste d'arguments est lu comme une soustraction : passer par une variable.

## Messages avec nombres : opérateur `CHAI` (et non `MESS` seul)
`MESS` concatène mal textes et nombres. Construire le message avec `CHAI`, puis `MESS` (console) et/ou `SORT 'CHAI'` (fichier) :
- `CHAI` supprime les espaces **terminaux** d'une chaîne, garde les espaces **initiaux** ; un objet `' '` isolé est conservé. Séparer donc par des objets `' '` explicites : `CHAI aaa ' ' 'sur' ' ' bbb` donne `4 sur 5`.
- Les options `>N` / `<N` ne marchent que derrière une chaîne entre quotes (`K1>2` est lu comme un seul mot) : ne pas les utiliser derrière une variable.
- `*N` derrière un entier ou un flottant (ou un littéral entre quotes) cadre à droite sur la colonne N (vérifié sur entiers). Mettre les noms (mots) en fin de ligne plutôt que de les aligner.
- Flottants : `'FORMAT' '(1PE10.3)'` ou `'FORMAT' '(F6.2)'`. Limite de 512 caractères par `CHAI`.

## Sorties de fichiers
- `OPTI 'IMPR' 'fichier'` redirige l'affichage **de façon définitive** (`OPTI 'IMPR' 6` ne rétablit pas la console). Pour écrire dans des fichiers en gardant la console : `OPTI 'SORT' 'fichier'` + `SORT 'CHAI' message`, puis fermer en passant à un fichier vide (`OPTI 'SORT' 'xxx_inutile.tmp'`).
- Chaque cas de test exécuté en séquence dans une même session doit l'être **dans une procédure** (variables locales), sinon les variables d'un cas masquent des mots-clés ou opérateurs du suivant (erreurs 11 constatées sur `TEMP` et `MATE`).

## Contrôles à faire avant de livrer (Cast3M n'est pas forcément disponible)
```
python3 tools/static_checks.py --orig livraison/procedur_origine/unpas.procedur livraison/procedur/unpas.procedur
python3 tools/static_checks.py livraison/validation/valid_perf.dgibi livraison/benchmark/bench_cube.dgibi
python3 tools/colorise_kate.py -s tools/gibiane.xml tools/esope.xml -o /tmp/apercu.html -t apercu <fichiers>
```
Le script de coloration contrôle les noms de variables (collisions avec mots-clés) et écrit `ATTENTION ... ligne N` sur stderr : 156 avertissements existent déjà dans les 4 procédures d'origine ; **tout nouvel avertissement est à corriger** (comparer avant/après). Les commentaires ajoutés dans les procédures sont repérés par `PERF-RAID`.

## Ce que Claude Code ne peut pas faire seul
Exécuter Cast3M (supposé indisponible) : les campagnes (validation `valid_perf.dgibi`, benchmark `bench_cube.dgibi`) sont lancées par l'utilisateur sur son PC (Windows, Cast3M 2024.1 EDURE) qui renvoie les logs. Toute affirmation sur un comportement à l'exécution doit être marquée « non exécuté » tant qu'elle n'est pas confirmée par un log.
