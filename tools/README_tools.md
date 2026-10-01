# Outils

| Outil | Usage |
|---|---|
| `static_checks.py` | contrôles statiques Gibiane (SI/FINSI, REPETER/FIN, instructions à deux `=`, `>N` collé dans un `CHAI`, commentaires hors colonne 1 avec `--orig`). Code retour ≠ 0 si défaut |
| `gen_validation.py` | génère `valid_perf.dgibi` (variables d'environnement `DGIBI_DIR`, `OUT_DIR`) ; sortie vérifiée identique au fichier livré |
| `colorise_kate.py` + `gibiane.xml`, `esope.xml` | aperçu HTML coloré et contrôle des noms de variables (`ATTENTION ... ligne N`) |

Exemples :
```
python3 tools/static_checks.py --orig livraison/procedur_origine/unpas.procedur livraison/procedur/unpas.procedur
python3 tools/colorise_kate.py -s tools/gibiane.xml tools/esope.xml -o /tmp/apercu.html -t apercu livraison/procedur/*.procedur
DGIBI_DIR=PCW_24/dgibi OUT_DIR=livraison/validation python3 tools/gen_validation.py
```
Avertissements du script de coloration : 156 sont préexistants dans les 4 procédures d'origine ; comparer le nombre et l'ensemble avant/après toute modification.
| `bench_reso/refine_sp.f90` | banc Fortran (gfortran) : descente-remontée de RESO en simple précision et raffinement de MONDES (voir `bench_reso/README.md`) |

`gen_validation.py` : `NIV_PASSE3=3` génère `valid_perf3.dgibi` (3e passe au niveau 3).
