# Benchmark PERF-RAID sur cube

`bench_cube.dgibi` mesure le gain des optimisations sur un cube (maillage unique, `NDIV0 = 10` : 1 000 éléments) sous chargement cyclique.

## Scénarios (12 calculs)
| Famille | Loi | Température | Variantes |
|---|---|---|---|
| CHABOCHE | acier 316L, E(T), 60 pas | uniforme constante | orig, perf1, perf2 |
| CHABOCHE_T | idem | rampe 20 à 100 °C (change à chaque pas) | orig, perf1, perf2 |
| MAZARS | béton, endommagement, 76 pas | sans | orig, perf1, perf2 |
| MAZARS_T | béton, E(T) (−0,05 %/°C) | rampe 20 à 100 °C | orig, perf1, perf2 |

Variantes : `orig` = `'PERF_RAID'` FAUX ; `perf1` = niveau 1 (résultats identiques) ; `perf2` = niveau 2 (raideur réutilisée de façon approchée, tolérance 1E-3 sur la diagonale).

## Mise en route
1. Copier dans le répertoire d'exécution de Cast3M : `bench_cube.dgibi` et les quatre procédures du dossier `procedur/`.
2. Lancer `bench_cube.dgibi` (quelques minutes sur un PC modeste).

## Suivi et résultats
- Console : `>>> Scenario k sur N : nom (...)` puis `<<< Scenario k sur N : nom : temps ms ; acceleration ...`. Fin normale : `BENCHMARK TERMINE`.
- `bench_avancement.log` : scénario en cours et scénarios terminés.
- `bench_<scenario>.log` : détail (temps, accélération, compteurs, écart de courbe F/S avec la variante `orig` de la famille).
- `bench_synthese.log` : tableau final (famille, PERF, niveau, temps, accélération, écart, compteurs, résultat).
- `bench_inutile.tmp` : fichier vide qui ferme les fichiers de sortie, supprimable.

Compteurs : `reut.` pas où la raideur est réutilisée, `calc.` pas où elle est recalculée, `hook` appels de `HOOK` évités, `mat.` caractéristiques réutilisées.

## Protocole de mesure (v2)
- `NREP0 = 2` : chaque scénario est calculé deux fois, en ordre aller puis retour ; le temps minimal est retenu.
- Pour chaque scénario, les temps passés dans `RESO`, `RIGI`, `HOOK`, `VARI` et `COMP` (lus dans `TEMP 'NOEC'`) sont donnés : ils montrent le travail réellement supprimé, indépendamment de la dispersion du temps total.
- Une famille par session sur un PC modeste : `LSCE = LECT 1 2 3 ;` (CHABOCHE), `4 5 6` (CHABOCHE_T), `7 8 9` (MAZARS), `10 11 12` (MAZARS_T).

## Réglages (en tête du fichier)
`NDIV0` (taille), `NREP0` (répétitions, temps minimal retenu), `TRAMF0` (température finale de la rampe), `TOLN1` / `TOLN2` (tolérances de comparaison des courbes), `LSCE` (scénarios exécutés ; la variante `orig` d'une famille doit précéder ses variantes `perf`).

## Lecture
- `perf1` : écart attendu nul (≤ 1E-8). Le gain vient des pas où la raideur est réutilisée exactement (T constante, endommagement stable) et du HOOK évité.
- `perf2` : accélération supplémentaire quand T ou l'endommagement varient doucement ; l'écart de courbe reste de l'ordre de la tolérance de convergence. Avec la rampe 20 à 100 °C, la diagonale change d'environ 0,04 % par pas : la raideur est recalculée tous les 2 à 3 pas environ. Avec une rampe plus rapide, le gain diminue.

## Profil complet des operateurs (piste Esope, `IPROF0`)
`IPROF0 = 1` (en tete de `bench_cube.dgibi`) affiche a la console, apres chaque calcul, `TEMP 'IMPR' 'SOMM'` (tous les operateurs) puis `TEMP 'IMPR' 'PROC'` (procedures). Usage : un seul scenario (`LSCE = LECT 9 ;` MAZARS perf2, ou `LECT 2 ;` CHABOCHE perf1) et `NREP0 = 1` ; renvoyer la sortie console. But : repartir le temps hors RESO/RIGI/HOOK/VARI (COMP = 41 % du total en MAZARS perf2) entre COMP, EPSI, BSIG, ELAS, operations sur champs et interpretation.

## Parallelisme et correction de la mesure par operateur
- `IPROC0` (en tete, entier) impose `'PROCESSEURS'` a PASAPAS : 0 = choix de PAS_DEFA (defaut), 1 = `'MONO_PROCESSEUR'`, 2 = `'COMPORTEMENT'`, 3 = `'AUTOMATIQUE'`. Un entier evite d'ecrire `COMPORTEMENT` dans le script : Cast3M ne lit que 4 caracteres des noms et le lit comme l'operateur `COMP`.
- `TOPER` retourne maintenant le **maximum** sur les assistants (temps ecoule) au lieu de la somme. Les colonnes `COMP` etc. des campagnes precedentes (somme) surestimaient les operateurs executes en parallele : a 1 000 elements PAS_DEFA choisit 2 assistants (`NBPART` = 1000/400), donc `COMP` etait compte deux fois (4 275 ms au lieu de 2 149 ms en CHABOCHE perf1). `RESO`, `RIGI`, `HOOK`, `VARI` (un seul assistant) ne changent pas.
