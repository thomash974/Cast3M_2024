# Mesures numériques (toutes campagnes)

Conditions : Cast3M 2024.1 Windows, PC de l'utilisateur (assistants parallèles : « Parallelisation automatique sur 11 assistants » à partir de ~1 000 éléments). Cube unité, CUB8, PRECISION = 1E-4 / NDIV², chargement CHABOCHE 60 pas (±1,5 %), MAZARS 76 pas (traction cyclique croissante 1E-3). Les temps varient d'un job à l'autre (même calcul : 104 s puis 151 s à 8 000 éléments) : comparer les scénarios **d'un même job**.

## 1. Benchmark v2 (v5 des procédures), 1 000 éléments, minimum de 2 répétitions (ms)
| Scénario | Total | Accél. | RESO | RIGI | HOOK | VARI | Raideur réutilisée / recalculée | HOOK évités | Mat. réutilisés | Écart courbe |
|---|---|---|---|---|---|---|---|---|---|---|
| chab_orig | 16 414 | 1,00 | 5 621 | 356 | 0 | 1 344 | 0 / 60 | 0 | 0 | — |
| chab_perf1 | 10 977 | 1,50 | 1 646 | 6 | 0 | 0 | 59 / 1 | 0 | 61 | 0 |
| chab_perf2 | 9 775 | 1,68 | 1 566 | 4 | 0 | 0 | 59 / 1 | 0 | 61 | 0 |
| chabT_orig (rampe T) | 15 900 | 1,00 | 5 715 | 371 | 0 | 1 359 | 0 / 60 | 0 | 0 | — |
| chabT_perf1 | 17 482 | 0,91 | 6 108 | 407 | 0 | 1 547 | 0 / 60 | 0 | 1 | 0 |
| chabT_perf2 | 13 446 | 1,18 | 2 920 | 388 | 0 | 1 540 | 40 / 20 | 0 | 1 | 3,1E-5 |
| maz_orig | 30 458 | 1,00 | 9 191 | 1 517 | 4 139 | 0 | 0 / 85 | 0 | 0 | — |
| maz_perf1 | 24 008 | 1,27 | 5 746 | 1 453 | 575 | 0 | 54 / 31 | 494 | 0 | 0 |
| maz_perf2 | 20 981 | 1,45 | 4 829 | 1 507 | 590 | 0 | 59 / 22 | 447 | 0 | 2,5E-4 |
| mazT_orig (E(T), rampe) | 34 539 | 1,00 | 9 104 | 1 356 | 4 333 | 1 049 | 0 / 81 | 0 | 0 | — |
| mazT_perf1 | 30 704 | 1,12 | 9 113 | 1 403 | 579 | 904 | 0 / 81 | 498 | 11 | 0 |
| mazT_perf2 | 27 063 | 1,28 | 6 935 | 1 352 | 554 | 969 | 29 / 52 | 478 | 11 | 1,8E-3 |

Le temps économisé est expliqué par les opérateurs évités à ±1,5 s (MAZARS niveau 1 : 6,5 s au total, 7,0 s sur RESO + HOOK). Dispersion sur travail identique : ≈ ±10 % (cas `chabT_perf1`).

## 2. 8 000 éléments, procédures intermédiaires (v2 / v3), mêmes mécanismes sans les raffinements v4-v5 (s)
| Famille | orig | niveau 1 | autre |
|---|---|---|---|
| CHABOCHE E(T), T constante (job A) | 150,9 (RESO 96, VARI 17, RIGI 660 appels) | 56,1 (×2,7 ; RESO 17, RIGI 11) | `matcst` (E interpolé à T0) 54,5 |
| CHABOCHE E(T), T constante (job B) | 103,6 (RESO 62, VARI 10) | 42,5 (×2,4) | — |
| MAZARS (job C) | 301,3 (RESO 158, HOOK 20,5, RIGI 979 appels) | 195,2 (×1,54 ; RESO 92, 54 réutilisations sur 76) | HOOK évité seul 260,8 (×1,16) ; tolérance 1E-2 sur la diagonale : 166,4 (×1,81, écart 3,5E-4) |

Décomposition de RESO à 8 000 éléments : factorisation ≈ 1,0 à 1,3 s (appelée à chaque reconstruction), descente-remontée ≈ 90 ms (MAZARS) et 60 ms (CHABOCHE) **par résolution** (726 résolutions MAZARS, 264 CHABOCHE) ; avec la raideur réutilisée la descente-remontée devient le poste dominant de RESO.

## 3. Premières campagnes (version d'origine, pour mémoire)
- À 1 000 éléments : orig CHABOCHE 16 à 24 s ; à 8 000 : 103 à 161 s.
- 8 000 éléments, procédures d'origine, jobs différents : E(T) avec chargement thermique constant (référence) 124 s ; E interpolé à T0 sans chargement thermique 57,7 s ; E interpolé à T0 avec chargement thermique 42,5 s (RIGI 11 appels dans les deux derniers : la raideur n'est plus recalculée ; l'écart 57,7 / 42,5 est la variabilité d'un job à l'autre).
- Profil à 8 000 éléments (orig) : RESO 60-64 %, VARI 9-12 %, MENA 5 %, COMP 5 %, FINSI 5 %.
- Interprétation Gibiane de `UNPAS` : ≈ 14 ms par pas à 1 élément (0,8 s sur 60 pas), soit < 1 % à 8 000 éléments.

## 4. Validation sur les 56 cas de la distribution
- 56 / 56 OK ; écart max 5,1E-17 (niveau 1, `newmark1`), 3,4E-6 (niveau 2, `GTN_C20R`).
- Raideur réutilisée : 11 cas au niveau 1, 17 au niveau 2 (`desmorat` 299 réutilisations, `GLRC_DM` 74, `dilthe` 20, `traction316L` 8) ; HOOK évité : 13 cas, 1 399 appels ; caractéristiques réutilisées : 6 cas.
- 11 cas en grands déplacements (dont 3 contacts, `dyna_nl1`) : aucune réutilisation.
- 39 cas témoins sans mécanisme actif : « accélérations » 0,31 à 2,17 (médiane 0,99) = dispersion de mesure.
- Détail par cas : `livraison/annexes/validation_detail_par_cas.md`.

## 5. Reprise Claude Code (1 octobre 2026, exécutions de l'utilisateur)
- **Profil CHABOCHE perf1, 1 000 éléments** (10,6 s) : COMP 2 149 ms (maximum sur 2 assistants ; la somme du benchmark donnait 4 275), RESO 1 508, FINS 2 115, BSIG 485, MENA 511, DETR 358, EPSI 206.
- **Profil CHABOCHE perf1, 8 000 éléments** (62,6 s, job lent) : RESO 17 854 (264 résolutions), COMP 6 809, FINS 6 793, MENA 4 400, BSIG 2 143, REDU 1 906 ; CPU 173,7 s soit 2,8 cœurs en moyenne.
- **Parallélisme** (CHABOCHE perf1) : 1 000 éléments : défaut 10 842 ms, mono 8 983, COMPORTEMENT 9 198, AUTOMATIQUE 18 161 ; 8 000 éléments : défaut 45 989, mono 58 429, COMPORTEMENT 49 531.
- **Itérations par pas** : voir `HISTORIQUE_DECISIONS.md` phase 8 (CHABOCHE 204 itérations ; MAZARS 494 au niveau 1 dont 353 dans 10 pas, 447 au niveau 2 dont 306).
- Les temps absolus varient d'un job à l'autre (maz_perf2 : 21,0, 22,1, 24,2 puis 30,4 s) ; comparer au sein d'un même job ou raisonner sur les itérations.
