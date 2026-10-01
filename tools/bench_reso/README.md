# bench_reso : essais hors Cast3M sur la résolution RESO (MONDES)

`refine_sp.f90` (gfortran -O2) : une descente-remontée en simple précision (facteurs REAL*4)
suivie du raffinement itératif de MONDES atteint-elle le critère `crite = crit*sqrt(xzprec*xszpre)` ?
Matrice de test : Laplacien 2D 60x60 + décalage (valeur propre minimale ~ décalage), bande dense.
Banc synthétique, pas une matrice Cast3M : il ne mesure que le nombre de passes.

Résultats (exécutés ici) :
| décalage | passes simple précision | double précision |
|---|---|---|
| 1E+0 | 2 | 1 |
| 1E-2 | 2 | 1 |
| 1E-4 | 3 | 1 |
| 1E-6 | 31 (au-delà des 10 passes permises par MONDES : erreur 1128) | 1 |

Conclusion : avec le critère actuel, le simple précision coûte au moins 2 passes (2 demi-coûts de
descente-remontée + 2 produits K*U) soit pas de gain, et diverge sur matrice mal conditionnée.
