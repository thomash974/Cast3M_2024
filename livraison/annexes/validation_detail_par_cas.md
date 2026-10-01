| N° | Cas | Description | Classes détectées | Écart niv.1 | Écart niv.2 | Raideur réutilisée (n1 / n2) | Raideur recalculée (n1 / n2) | HOOK évités (n1) | Matériau réutilisé (n1) |
|---|---|---|---|---|---|---|---|---|---|
| 1 | `mazars` | endommagement MAZARS, QUA4 CP | endomm. | 0.000E+00 | 0.000E+00 | 1 / 1 | 16 / 16 | 50 | 0 |
| 2 | `mazars2` | endommagement MAZARS, cycles | endomm. | 0.000E+00 | 4.443E-13 | 7 / 8 | 104 / 103 | 320 | 0 |
| 3 | `compression` | endommagement, compression | endomm. | 0.000E+00 | 0.000E+00 | 10 / 19 | 10 / 1 | 96 | 0 |
| 4 | `endoaxi1` | endommagement, axisymetrique | endomm. | 0.000E+00 | 0.000E+00 | 1 / 2 | 2 / 1 | 12 | 0 |
| 5 | `endoaxi2` | endommagement + thermique, axi | MATVAR, endomm. | 0.000E+00 | 2.781E-06 | 0 / 2 | 18 / 16 | 43 | 1 |
| 6 | `endoaxi3` | endommagement + thermique, axi | MATVAR, endomm. | 0.000E+00 | 4.073E-08 | 0 / 1 | 7 / 6 | 15 | 1 |
| 7 | `endocp1` | endommagement, contraintes planes | endomm. | 0.000E+00 | 0.000E+00 | 1 / 3 | 3 / 1 | 24 | 0 |
| 8 | `fluaendo` | fluage + endommagement + thermique | MATVAR, viscodomm. | 0.000E+00 | 1.013E-08 | 0 / 11 | 12 / 1 | 24 | 1 |
| 9 | `relaxendo` | relaxation + endommagement + thermique | MATVAR, viscodomm. | 0.000E+00 | 5.321E-11 | 0 / 5 | 6 / 1 | 20 | 1 |
| 10 | `GTN_C20R` | endommagement ductile (GTN) | endomm. | 0.000E+00 | 3.444E-06 | 0 / 18 | 20 / 2 | 102 | 0 |
| 11 | `mvm_bcn` | endommagement | endomm. | 0.000E+00 | 0.000E+00 | 2 / 2 | 18 / 18 | 58 | 0 |
| 12 | `desmorat` | endommagement + dynamique | endomm. | 0.000E+00 | 0.000E+00 | 299 / 299 | 1 / 1 | 583 | 0 |
| 13 | `betdynlmt` | endommagement + dynamique, beton | endomm. | 0.000E+00 | 0.000E+00 | 19 / 19 | 1 / 1 | 52 | 0 |
| 14 | `ricbet_uni_1` | beton arme, endommagement (structure) | - | 0.000E+00 | 0.000E+00 | 0 / 0 | 1 / 1 | 0 | 0 |
| 16 | `GLRC_DM` | coque + endommagement (HOOK conserve) | endomm. | 0.000E+00 | 0.000E+00 | 74 / 79 | 6 / 1 | 0 | 0 |
| 17 | `traction316L` | T uniforme, E(T) | MATVAR | 0.000E+00 | 0.000E+00 | 8 / 8 | 1 / 1 | 0 | 10 |
| 18 | `test_vari_props` | proprietes variables | - | 0.000E+00 | 0.000E+00 | 0 / 0 | 0 / 0 | 0 | 0 |
| 19 | `dilthe` | dilatation thermique | MATVAR | 0.000E+00 | 0.000E+00 | 20 / 38 | 19 / 1 | 0 | 20 |
| 20 | `char_constant` | chargement constant, thermique | GD | 0.000E+00 | 0.000E+00 | 0 / 0 | 51 / 51 | 0 | 0 |
| 21 | `thgdep1` | thermique + grands deplacements | GD | 0.000E+00 | 0.000E+00 | 0 / 0 | 6 / 6 | 0 | 0 |
| 22 | `ther_meca_coque` | thermomecanique coque | - | 0.000E+00 | 0.000E+00 | 0 / 0 | 1 / 1 | 0 | 0 |
| 23 | `dependance` | dependance parametres, coque | - | 0.000E+00 | 0.000E+00 | 0 / 0 | 1 / 1 | 0 | 0 |
| 24 | `thme1` | thermo-mecanique | - | 0.000E+00 | 0.000E+00 | 0 / 0 | 1 / 1 | 0 | 0 |
| 25 | `phase_03` | metallurgie/phases | - | 0.000E+00 | 0.000E+00 | 0 / 0 | 0 / 0 | 0 | 0 |
| 26 | `plas5` | plasticite | - | 0.000E+00 | 0.000E+00 | 0 / 0 | 1 / 1 | 0 | 0 |
| 27 | `plas_incomp` | plasticite incompressible | GD | 0.000E+00 | 0.000E+00 | 0 / 0 | 20 / 20 | 0 | 0 |
| 28 | `chaboche1` | viscoplasticite Chaboche/Onera | - | 0.000E+00 | 0.000E+00 | 0 / 0 | 1 / 1 | 0 | 0 |
| 29 | `chaboche2` | viscoplasticite | - | 0.000E+00 | 0.000E+00 | 0 / 0 | 1 / 1 | 0 | 0 |
| 30 | `norton_tra1` | fluage Norton | - | 0.000E+00 | 0.000E+00 | 0 / 0 | 1 / 1 | 0 | 0 |
| 31 | `ddi` | visco | - | 0.000E+00 | 0.000E+00 | 0 / 0 | 1 / 1 | 0 | 0 |
| 32 | `tufi` | plasticite tuyau fibre | - | 0.000E+00 | 0.000E+00 | 0 / 0 | 1 / 1 | 0 | 0 |
| 33 | `fluage_maxwell_1` | fluage Maxwell | MATVAR | 0.000E+00 | 0.000E+00 | 0 / 35 | 36 / 1 | 0 | 0 |
| 34 | `poudre3` | poudre | - | 0.000E+00 | 0.000E+00 | 0 / 0 | 1 / 1 | 0 | 0 |
| 35 | `gurson` | Gurson | - | 0.000E+00 | 0.000E+00 | 0 / 0 | 1 / 1 | 0 | 0 |
| 36 | `beton` | beton | - | 0.000E+00 | 0.000E+00 | 0 / 0 | 1 / 1 | 0 | 0 |
| 37 | `ottovari_traction` | plasticite | - | 0.000E+00 | 0.000E+00 | 0 / 0 | 1 / 1 | 0 | 0 |
| 38 | `plas8` | coque plastique | - | 0.000E+00 | 0.000E+00 | 0 / 0 | 1 / 1 | 0 | 0 |
| 39 | `ohno2` | coque visco Ohno | - | 0.000E+00 | 0.000E+00 | 0 / 0 | 1 / 1 | 0 | 0 |
| 40 | `guionnet_tra` | coque visco | - | 0.000E+00 | 0.000E+00 | 0 / 0 | 1 / 1 | 0 | 0 |
| 41 | `g_c_etoile_coque_1` | coque visco | - | 0.000E+00 | 0.000E+00 | 0 / 0 | 1 / 1 | 0 | 0 |
| 42 | `PoutreConsole_Plas_EcrouCineLine` | poutre plastique | - | 0.000E+00 | 0.000E+00 | 0 / 0 | 1 / 1 | 0 | 0 |
| 43 | `fluage_fibre_norton_1` | poutre fibres fluage | - | 0.000E+00 | 0.000E+00 | 0 / 0 | 1 / 1 | 0 | 0 |
| 44 | `test_cisailnl` | poutre cisaillement non lineaire | - | 0.000E+00 | 0.000E+00 | 0 / 0 | 1 / 1 | 0 | 0 |
| 45 | `cou22` | joint | - | 0.000E+00 | 0.000E+00 | 0 / 0 | 1 / 1 | 0 | 0 |
| 46 | `testjoi1ani` | joint anisotrope | - | 0.000E+00 | 0.000E+00 | 0 / 0 | 1 / 1 | 0 | 0 |
| 47 | `joi_eli` | joint elastique | - | 0.000E+00 | 0.000E+00 | 0 / 0 | 1 / 1 | 0 | 0 |
| 48 | `jointsoft1` | joint adoucissant | - | 0.000E+00 | 0.000E+00 | 0 / 0 | 1 / 1 | 0 | 0 |
| 49 | `gdep2` | grands deplacements coque | GD | 0.000E+00 | 0.000E+00 | 0 / 0 | 240 / 240 | 0 | 0 |
| 50 | `gdef2` | grandes deformations | GD | 0.000E+00 | 0.000E+00 | 0 / 0 | 50 / 50 | 0 | 0 |
| 51 | `Mooney_LRGTreloar_Traction` | hyperelastique | GD | 0.000E+00 | 0.000E+00 | 0 / 0 | 100 / 100 | 0 | 0 |
| 52 | `gdtract` | grands deplacements + endommagement (reutilisation exclue) | GD | 0.000E+00 | 0.000E+00 | 0 / 0 | 100 / 100 | 0 | 0 |
| 53 | `newmark1` | dynamique Newmark poutre | - | 5.094E-17 | 5.094E-17 | 0 / 0 | 1 / 1 | 0 | 0 |
| 54 | `dyna_nl1` | dynamique non lineaire | GD | 0.000E+00 | 0.000E+00 | 0 / 0 | 138 / 138 | 0 | 0 |
| 55 | `Contact2D` | contact 2D | GD | 0.000E+00 | 0.000E+00 | 0 / 0 | 1 / 1 | 0 | 0 |
| 56 | `Coulomb3D` | contact frottant 3D | GD | 0.000E+00 | 0.000E+00 | 0 / 0 | 8 / 8 | 0 | 0 |
| 57 | `contact2D-adhe` | contact adherent | GD | 0.000E+00 | 0.000E+00 | 0 / 0 | 17 / 17 | 0 | 0 |