# PERF-RAID : livraison

Accélération de `PASAPAS` / `UNPAS` par réutilisation de la raideur et du matériau, HOOK évité. Détails, validation et gains : `RAPPORT_LIVRAISON.md`.

## Installation
1. Copier les quatre fichiers de `procedur/` (`unpas.procedur`, `pas_mate.procedur`, `pasapas.procedur`, `pas_defa.procedur`) dans un répertoire lu **avant** l'installation de Cast3M :
   le répertoire courant, `./procedur`, ou un répertoire ajouté en tête de la variable d'environnement `CASTEM_PROCEDUR24` (les procédures sont lues dans des fichiers de même nom ; l'ordre de recherche est : répertoire courant, `./procedur`, installation).
2. Ne pas modifier l'installation tant que le pilote n'est pas terminé (§9 du rapport).

## Vérification
1. `validation/` : copier `valid_perf.dgibi` dans le répertoire d'exécution (les procédures sont déjà dans `validation/procedur/`) ; essai rapide avec `IFIN0 = 10`. Résultat attendu : `RESULTAT : niveau 1 OK ; niveau 2 OK` pour chaque cas. Mode d'emploi : `validation/LISEZMOI_validation.md`.
2. `benchmark/` : `bench_cube.dgibi` (une famille par session : `LSCE = LECT 1 2 3 ;`). Mode d'emploi : `benchmark/LISEZMOI_benchmark.md`.
3. Dans un calcul métier, lire en fin de `PASAPAS` les messages `raideur recalculee`, `raideur reutilisee`, `HOOK evite`, `caracteristiques reutilisees`.
4. À l'arrêt de Cast3M, le message « Utilisation de procedures personnelles » est normal.

## Utilisation
Par défaut (niveau 1) : aucun changement dans les fichiers de données. Options dans la table passée à `PASAPAS` :
`TAB1 . 'PERF_RAID' = FAUX ;` (comportement d'origine), `TAB1 . 'PERF_RAID_NIVEAU' = 2 ;` (réutilisation approchée, optionnelle). Liste complète : §4 du rapport.

## Retour arrière
Supprimer les quatre fichiers du répertoire utilisateur, ou les remplacer par ceux de `procedur_origine/`. Pour un seul calcul : `TAB1 . 'PERF_RAID' = FAUX ;`.

## Contenu
`RAPPORT_LIVRAISON.md` · `procedur/` · `procedur_origine/` · `diff/perf_raid.diff` · `validation/` · `benchmark/` · `resultats/` · `annexes/` · `MANIFESTE.txt`
