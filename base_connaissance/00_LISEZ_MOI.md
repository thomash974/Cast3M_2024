# Corpus de référence Cast3M 2024 (PCW_24) — mode d'emploi

Base de connaissances pour travailler sur le langage **Gibiane** et sur le code source **ESOPE** de Cast3M 2024,
extraite et compactée depuis l'archive `PCW_24.zip`. Le lot est en deux niveaux.

## Niveau A « noyau » : à charger en priorité (≈ 244 Ko, ≈ 75 k jetons estimés)
Dimensionné pour tenir dans le contexte avec de la marge. Chaque fichier est autonome.

| Fichier | Contenu | Taille | Jetons est. |
|---|---|---|---|
| `01_guide_gibiane_esope.md` | Règles du langage Gibiane, introduction à ESOPE (segments, API LIROBJ/ECRENT…), démarche pour ajouter un opérateur, conventions | 10 Ko | ~3 k |
| `02_operateurs_vers_sources.md` | Chaque opérateur Gibiane → sous-programme appelé par PILOT [fichier `.eso`] | 7 Ko | ~2 k |
| `03_includes_essentiels.md` | 16 includes clés : structures MELEME, MCHPOI, MCHAML, MRIGID, MMODEL, MTABLE…, COMMON CCOPTIO | 25 Ko | ~7 k |
| `05_sources_cles.md` | API de lecture/écriture des arguments (LIROBJ, LIRABJ, LIRENT, ECROBJ, ACCTAB…) et exemple d'opérateur complet (NBNO) | 24 Ko | ~7 k |
| `06_mini_notices_operateurs_courants.md` | 172 opérateurs et procédures les plus utilisés : titre, syntaxe, début de l'objet | 41 Ko | ~12 k |
| `06b_MODE_MATE_condense.md` | Syntaxe de MODE, noms de paramètres de MATE par type de matériau, options courantes d'OPTI | 52 Ko | ~16 k |
| `07_pasapas_procedure.md` | Texte compacté de la procédure PASAPAS | 29 Ko | ~9 k |
| `09_exemples_dgibi_choisis.md` | 9 cas tests commentés et variés (élasticité 3D, contact avec PASAPAS, fluides, langage, maillage…) | 47 Ko | ~14 k |
| `00_LISEZ_MOI.md` | Ce fichier | 6 Ko | ~2 k |

## Niveau B « complément » : pour la recherche documentaire seulement (≈ 4339 Ko, ≈ 1346 k jetons estimés)
Trop volumineux pour le contexte : à utiliser en mode recherche (RAG) du projet, ou à joindre ponctuellement à une conversation.
Ordre conseillé de retrait si le projet sature : 11, 10_2, 08, 04_2, 03b, 10_1, 07, 06_3, 06_2…

| Fichier | Contenu | Taille | Jetons est. |
|---|---|---|---|
| `02b_index_thematique_notices.md` | Notices classées par section thématique | 8 Ko | ~2 k |
| `03b_includes_autres.md` | Les 78 autres includes | 151 Ko | ~46 k |
| `04_index_sources_1_A1RE3D-RESOU1.md` | Index des sources ESOPE (1 ligne par fichier : sous-programme, opérateur appelant, rôle, routines appelées), partie 1 | 605 Ko | ~188 k |
| `04_index_sources_2_RESOUC-ZZOIMP.md` | Index des sources ESOPE, partie 2 (et liste des routines LAPACK omises) | 163 Ko | ~50 k |
| `05b_sources_cles_complement.md` | PILOT, ERREUR, ACTOBJ, accès aux tables, ELIM/PRELIM/ELIMIN… | 72 Ko | ~22 k |
| `06_notices_completes_1_A1DDL-ELST.md` | Notices complètes (français, compactées, tronquées à 4 500 caractères), partie 1 | 544 Ko | ~168 k |
| `06_notices_completes_2_ENCEIN-PMPB.md` | Notices complètes, partie 2 | 544 Ko | ~169 k |
| `06_notices_completes_3_POD-ZONFIS.md` | Notices complètes, partie 3 | 413 Ko | ~128 k |
| `06c_MODE_MATE_OPTI_notices_completes.md` | Notices MODE, MATE et OPTI en entier (paramètres de tous les modèles de comportement) | 363 Ko | ~112 k |
| `07_index_procedures.md` | Index des 517 procédures Gibiane : signature, en-tête, appels | 90 Ko | ~27 k |
| `08_procedures_centrales.md` | PAS_DEFA, PAS_INIT, TRANSNON, UNPAS (texte compacté) | 276 Ko | ~85 k |
| `09_catalogue_dgibi.md` | Catalogue des 1 473 cas tests par section | 251 Ko | ~78 k |
| `09b_index_inverse_operateurs.md` | Opérateur/procédure → cas tests qui l'utilisent | 40 Ko | ~12 k |
| `10_exemples_dgibi_1.md` | 178 cas tests en texte compacté, partie 1 | 586 Ko | ~181 k |
| `10_exemples_dgibi_2.md` | 178 cas tests en texte compacté, partie 2 | 121 Ko | ~37 k |
| `11_documentation_officielle.md` | Note de version et note de fabrication 2024 | 50 Ko | ~15 k |
| `12_messages_erreur.md` | Numéro d'erreur → message (FR, EN si absent) | 53 Ko | ~16 k |

Les estimations de jetons supposent ≈ 3,3 caractères par jeton (à ±20 %).

## Traitements appliqués (compression)
- Suppression des cadres de commentaires (`*****`, `-----`), des lignes vides, des espaces de fin et des alignements d'espaces
  (hors chaînes entre apostrophes). Le code est inchangé : seule la mise en forme est compactée. **Ne pas recompiler à partir de ces extraits.**
- Notices : partie française seulement ; sans colonne « Voir aussi », sans sections anglaises, sans décorations, indentation réduite ;
  notices très longues tronquées à 4 500 caractères (sauf MODE, MATE, OPTI, conservées en entier dans le fichier 06c).
- Index des sources : une ligne par fichier, sans auteur ni date ; routines LAPACK/BLAS (84) omises ; appels courants (`ERREUR`, `LIROBJ`…) masqués.
- Cas tests : noms sans extension `.dgibi`, listes d'opérateurs retirées du catalogue (l'index inverse les remplace).
- Fichiers `divers/` (STL, MED, Nastran, CSV…) et sources non repris : à joindre à la demande.

## Méthode de navigation
- **Syntaxe d'un opérateur** : mini-notice (06, niveau A) ; notice complète dans le lot B (06).
- **Paramètres d'un matériau** : `06b` (noms), notice MATE complète dans `06c`.
- **Où est implanté X** : `02`, puis index des sources (lot B, 04) pour suivre les appels.
- **Structure d'un objet en mémoire** : includes `SM*` (`03`). MAILLAGE→SMELEME, CHPOINT→SMCHPOI, MCHAML→SMCHAML, RIGIDITE→SMRIGID, MMODEL→SMMODEL, TABLE→SMTABLE.
- **Écrire un jeu de données** : `09` (exemples) + mini-notices ; cas supplémentaires : lot B (09b puis 10).
- **Calcul non linéaire incrémental** : mini-notice PASAPAS (06) et texte de la procédure (`07`).
- **Fichier absent du lot** : demander à l'utilisateur de joindre le fichier ou l'archive `PCW_24.zip`.

## Limites
- La détection des opérateurs utilisés par les cas tests est automatique (4 premières lettres) et approximative.
- Les résumés de l'index des sources reprennent les commentaires d'en-tête tels quels ; leur qualité varie.
- 411 cas tests n'ont pas de champ `Section`.
- Cette version remplace un premier lot dans lequel 142 notices (dont OPTI, MATE, DEBP, DALL, CHAN) avaient leur texte français tronqué.
