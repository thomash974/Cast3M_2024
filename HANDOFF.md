# HANDOFF : état du projet PERF-RAID au moment du transfert vers Claude Code

## 1. Objectif et résultat
**Objectif initial** : accélérer `PASAPAS` (procédure `UNPAS` appelée à chaque pas) en basculant un maximum de morceaux en Esope compilé.

**Constat** : l'interprétation Gibiane de `UNPAS` pèse < 1 % à 8 000 éléments ; les opérateurs lourds (`RESO`, `COMP`, `BSIG`, `RIGI`…) sont déjà compilés. Le temps est gaspillé par des recalculs inutiles : refactorisation de la raideur à chaque pas (`RECALCUL` posé par `PAS_VERM`, `RECARI` forcé pour l'endommagement, purge de `RRRR` en fin de pas), réévaluation du matériau (`VARI`) à chaque pas, `HOOK` à chaque itération.

**Livré (v5, état final)** : 4 procédures Gibiane modifiées (`UNPAS`, `PAS_MATE`, `PASAPAS`, `PAS_DEFA`), additives et gardées, interrupteur `'PERF_RAID'`, deux niveaux (1 exact par défaut, 2 approché optionnel). Aucune source Esope modifiée. Rapport complet : `livraison/RAPPORT_LIVRAISON.md`.

**Gains mesurés** (1 000 éléments, benchmark v2) : CHABOCHE E(T) T constante ×1,50 ; MAZARS ×1,27 (niveau 1) / ×1,45 (niveau 2) ; CHABOCHE rampe T ×1,18 (niveau 2) ; MAZARS E(T) rampe ×1,28 (niveau 2). À 8 000 éléments (versions intermédiaires) : ×2,4 à ×2,7 (CHABOCHE), ×1,5 à ×1,8 (MAZARS). Détail : `MESURES.md`.

**Validation** : 56 cas de la distribution sur 57 (cas 15 `FissVoil` écarté, cause indépendante) : tous OK, écart max 5E-17 (niveau 1), 3,4E-6 (niveau 2). Cube : niveau 1 identique, niveau 2 ≤ 1,8E-3.

## 2. Contenu de l'archive et mise en place dans le dépôt
```
CLAUDE.md                    conventions (à placer a la racine du depot)
HANDOFF.md                   ce fichier
HISTORIQUE_DECISIONS.md      chronologie des decisions et des erreurs corrigees
LECONS_CAST3M.md             pieges Gibiane / Cast3M et faits releves dans les sources
MESURES.md                   tous les resultats numeriques des campagnes
livraison/                   paquet de livraison complet (rapport, procedures, tests, logs)
  procedur/                  LES 4 PROCEDURES MODIFIEES (source de verite)
  procedur_origine/          originaux (retour arriere, base des diffs)
  diff/perf_raid.diff        differences exactes
  validation/                valid_perf.dgibi (genere) + procedures + mode d'emploi
  benchmark/                 bench_cube.dgibi + procedures + mode d'emploi
  resultats/ annexes/        logs executes par l'utilisateur, detail par cas
tools/
  static_checks.py           controles statiques Gibiane (blocs, '=', CHAI, colonnes)
  gen_validation.py          generateur de livraison/validation/valid_perf.dgibi
  colorise_kate.py + xml     coloration / controle des noms de variables
contexte/
  instructions_projet_origine.md   instructions initiales de la session Claude.ai
base_connaissance/           documentation Cast3M indexee (reprise du projet Claude.ai)
```
**À ajouter par l'utilisateur** : l'archive `PCW_24` (sources Cast3M 2024.1 : `procedur/`, `sources/`, `dgibi/`, `notice/`, `include/`) à la racine du dépôt, sous `PCW_24/`. `tools/gen_validation.py` en a besoin (`DGIBI_DIR`, défaut `../PCW_24/dgibi`). Les procédures d'origine sont aussi dans `livraison/procedur_origine/`.

Regénérer le pilote : `DGIBI_DIR=PCW_24/dgibi OUT_DIR=livraison/validation python3 tools/gen_validation.py` (la sortie doit être identique au fichier livré : vérifié à l'octet près).

## 3. Architecture de la solution (résumé)
- `PAS_DEFA` : valeurs par défaut et lecture des indices (`'PERF_RAID'`, `'PERF_RAID_NIVEAU'`, `'TOLERANCE_RAIDEUR'`, `'TOLERANCE_RAIDEUR_ENDO'`, `'TOLERANCE_RAIDEUR_DIAG'`, `'TOLERANCE_MATERIAU'`, `'PERF_STRUCTURES'`).
- `PAS_MATE` : cache du champ de caractéristiques (`PMAT_MMM`, clé = `MA`, `MO`, composantes de `WTAB . 'LDEVA'`) ; renvoie le même objet quand rien n'a changé.
- `UNPAS` : (a) HOOK évité si aucun élément de coque DST/DSQ/DKT/DKQ/COQ2/3/4/8 ; (b) réutilisation exacte de la raideur factorisée (`RRRR_MAT`, `MAT_RRRR`, `ETAT_RRRR`, `DIAG_RRRR`) ; (c) niveau 2 : comparaison de la **diagonale** de la raideur élastique reconstruite (`EXTR RH 'DIAG'`), raideur candidate reprise par la reconstruction si refus ; exclusions : grands déplacements, FEFP, PICA (`LAG_TOT`), céramique, rigidité augmentée (`IRAUG`, `AUTAUG`), blocages variables (`CHAR_BLOM`), `LDEVA` absent, sous-pas après non-convergence (niveau 2) ; compteurs.
- `PASAPAS` : purge des objets conservés en fin d'appel, messages de diagnostic.
- Seules 9 lignes d'origine sont remplacées (1 condition + 2 sites `HOOK`/`EPSI` dans `UNPAS`, 1 appel `VARI` dans `PAS_MATE`) ; tout le reste est additif, repéré par `PERF-RAID`.

## 4. Comment reprendre le travail
1. Lire `CLAUDE.md` puis `LECONS_CAST3M.md` (évite de refaire les erreurs de syntaxe).
2. Vérifier l'état : `python3 tools/static_checks.py --orig livraison/procedur_origine/<f>.procedur livraison/procedur/<f>.procedur` pour les 4 fichiers (attendu : tout OK, 0 commentaire hors colonne 1) et le contrôle de coloration sans nouvel avertissement.
3. Toute modification d'une procédure : éditer `livraison/procedur/`, recopier dans `livraison/validation/procedur/` et `livraison/benchmark/procedur/` (les 3 emplacements doivent rester identiques : `cmp`), régénérer `livraison/diff/perf_raid.diff`, mettre à jour `livraison/MANIFESTE.txt` (sha256) et le rapport.
4. Aucune exécution Cast3M possible côté Claude Code : demander à l'utilisateur de lancer `validation/valid_perf.dgibi` (copie des 4 procédures dans le répertoire d'exécution ; `IFIN0 = 10` pour un essai rapide) et `benchmark/bench_cube.dgibi` (une famille par session sur PC modeste) et de renvoyer les logs.
5. Lecture des résultats : `RESULTAT : niveau 1 OK ; niveau 2 OK` par cas ; compteurs `raideur reutilisee / recalculee / HOOK evite / caracteristiques reutilisees`. Les accélérations des cas courts sont du bruit (39 cas témoins sans mécanisme : 0,31 à 2,17) ; juger sur les temps par opérateur du benchmark (RESO, RIGI, HOOK, VARI).

## 5. Backlog priorisé
| Priorité | Tâche | Remarque |
|---|---|---|
| 1 | **Pilote sur calculs métier** (béton armé, thermomécanique) : comparer `'PERF_RAID' = FAUX` et défaut, lire les compteurs | décision attendue sur la généralisation du niveau 1 |
| 1 | **Décider du niveau 2 par défaut** | écarts mesurés ≤ 1,8E-3 ; garder optionnel tant que non validé sur cas métier |
| 2 | **Notice PASAPAS** : documenter les nouvelles options (fichier `notice/pasapas.notice` de l'installation) | non fait ; contenu : §4 du rapport |
| 2 | **Compléter la validation** : pilotage indirect, THM, modal / fréquentiel, FEFP ; reprise d'un calcul (second appel de `PASAPAS` avec matériau modifié) | non couverts |
| 2 | **Gain à grande taille** avec les procédures v5 : `NDIV0 = 15` ou maillage réel | mesures à 8 000 éléments faites sur des versions intermédiaires |
| 3 | **FissVoil (cas 15)** : le valider seul en session neuve (son post-traitement `INITOU` utilise `NOEUD i`, numéros globaux) | écarté du pilote, sans lien avec les optimisations |
| 3 | **Niveau 2 adaptatif** : tolérance pilotée par le nombre d'itérations du pas précédent | idée, non étudiée |
| 3 | **Esope (non modifié)** : `RESO` (descente-remontée ≈ 60 à 90 ms par résolution à 8 000 éléments, 47 % du temps de MAZARS), opérateur fusionné `EPSI`/`COMP`/`BSIG` (5 à 10 %) | voir `LECONS_CAST3M.md` §4 ; mesurer d'abord avec `TEMP` autour de `MONDES`/`TRIANG` |

## 6. Hypothèses et points non vérifiés
- Les temps par opérateur du benchmark lisent `TEMP 'NOEC'` : `TEMPS_HORLOGE . <opérateur>` est une LISTENTI (un élément par assistant, plus un total ?) ; `TOPER` somme tous les éléments. Les valeurs obtenues sont cohérentes avec `TEMP 'IMPR' 'SOMM'` (RESO ≈ 5,6 s à 1 000 éléments), donc pas de double comptage apparent ; à confirmer si un nombre d'assistants différent change l'ordre de grandeur.
- Le niveau 2 compare la diagonale de la raideur, pas la matrice entière : un changement hors diagonale passerait inaperçu ; la solution reste imposée par le résidu (seule la convergence peut en pâtir).
- L'identité de deux champs par `EGA` (cache `PAS_MATE`, `UNPAS`) est supposée valoir pour l'objet lui-même ; confirmée indirectement par les compteurs (« caractéristiques réutilisées 61 fois »).
- La liste des éléments de coque exclus du HOOK évité (`DST DSQ DKT DKQ COQ2 COQ3 COQ4 COQ8`) est déduite des sources `epsi1.eso` / `epsi3.eso` ; un élément de structure absent de cette liste qui lirait la matrice de Hooke serait mal traité (aucun cas connu).
