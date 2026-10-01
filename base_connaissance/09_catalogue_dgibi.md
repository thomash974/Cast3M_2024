# Catalogue des cas tests dgibi

Une ligne par cas (nom sans `.dgibi`) : `(taille Ko)` description d'en-tête ; `P:` procédures Gibiane appelées ; `ext:` fichiers externes de `divers/`. Pour savoir quels cas utilisent un opérateur : fichier 09b.


## (sans section) (411)
15wedge (57K) CALCUL DE L'ECOULEMENT SUPERSONIQUE STATIONNAIRE DANS UN CANAL AVEC RAMPE INCLINEE A 15deg. POWELL AND DEZEEUW, AIAA-91-1542-CP FORMULATION VF COMPRESSIBLE…
@solvmec_01 (5K) Test du mini solveur mecanique (procedure @SOLVMEC) - eprouvette entaillee en traction - comportement elastique - calcul en grands deplacements - calcul avec… P:@SOLVMEC,@TOTAL,PASAPAS
@solvmec_02 (4K) Test du mini solveur mecanique (procedure @SOLVMEC) - eprouvette entaillee en traction - comportement elasto-plastique - calcul en grands deplacements - calcul avec… P:@SOLVMEC,@TOTAL,PASAPAS
@solvmec_03 (4K) Test du mini solveur mecanique (procedure @SOLVMEC) - eprouvette entaillee en traction - comportement visco-elastique - calcul en petits deplacements On compare les… P:@SOLVMEC,@TOTAL,PASAPAS
@solvmec_04 (4K) Test du mini solveur mecanique (procedure @SOLVMEC) - eprouvette entaillee en traction - comportement elastique avec endommagement On compare les resultats a ceux de la… P:@SOLVMEC,@TOTAL,PASAPAS
acqulatb (1K)  P:JEU
ajout1 (5K) fichier ajout1.dgibi Calcul du champ de temperature apres ajout de matiere. Une 1ere partie d'un maillage est a la temperature de 1000. On lui ajoute une 2e partie a la…
back_impl_1 (12K) CAS TEST : back_impl_1.dgibi Ce test permet de vérifier le bon fonctionnement des opérateurs utilisés pour la résolution des équations de NAVIER_STOKES en EF par un… P:EXEC
back_impl_2 (12K) CAS TEST : back_impl_2.dgibi Ce test permet de vérifier le bon fonctionnement des opérateurs utilisés pour la résolution des équations de NAVIER_STOKES en EF par un… P:EXEC
back_impl_3 (12K) CAS TEST : back_impl_3.dgibi Ce test permet de vérifier le bon fonctionnement des opérateurs utilisés pour la résolution des équations de NAVIER_STOKES en EF par un… P:EXEC
back_impl_4 (12K) CAS TEST : back_impl_4.dgibi Ce test permet de vérifier le bon fonctionnement des opérateurs utilisés pour la résolution des équations de NAVIER_STOKES en EF par un… P:EXEC
back_pression_1 (12K)  P:EXEC
back_pression_2 (12K)  P:EXEC
back_proj_1 (12K) CAS TEST : back_proj_1.dgibi Ce test permet de vérifier le bon fonctionnement des opérateurs utilisés pour la résolution des équations de NAVIER_STOKES en EF par un… P:EXEC
back_proj_2 (12K) CAS TEST : back_proj_2.dgibi Ce test permet de vérifier le bon fonctionnement des opérateurs utilisés pour la résolution des équations de NAVIER_STOKES en EF par un… P:EXEC
back_proj_3 (12K) CAS TEST : back_proj_3.dgibi Ce test permet de vérifier le bon fonctionnement des opérateurs utilisés pour la résolution des équations de NAVIER_STOKES en EF par un… P:EXEC
back_proj_4 (12K) CAS TEST : back_proj_4.dgibi Ce test permet de vérifier le bon fonctionnement des opérateurs utilisés pour la résolution des équations de NAVIER_STOKES en EF par un… P:EXEC
back_proj_5 (12K) CAS TEST : back_proj_5.dgibi Ce test permet de vérifier le bon fonctionnement des opérateurs utilisés pour la résolution des équations de NAVIER_STOKES en EF par un… P:EXEC
back_proj_6 (12K) CAS TEST : back_proj_6.dgibi Ce test permet de vérifier le bon fonctionnement des opérateurs utilisés pour la résolution des équations de NAVIER_STOKES en EF par un… P:EXEC
back_proj_7 (12K) CAS TEST : back_proj_7.dgibi Ce test permet de vérifier le bon fonctionnement des opérateurs utilisés pour la résolution des équations de NAVIER_STOKES en EF par un… P:EXEC
back_proj_8 (12K) CAS TEST : back_proj_8.dgibi Ce test permet de vérifier le bon fonctionnement des opérateurs utilisés pour la résolution des équations de NAVIER_STOKES en EF par un… P:EXEC
basmachQ (17K)  P:EXEC,FILTREKE,H_B
basmachT (16K)  P:EXEC,FILTREKE,H_B
bgmo_bcn (1K) TESTING FILE FOR THE OPERATOR BGMO EVALUATING THE FUNCIONS INVOLVED IN THE BRUNO GERARD MODEL
blasius (5K)  P:EXEC
bo2 (3K) Utilisation des opérateurs CHI1 et CHI2 test avec échange repertoire des fichiers "divers" ext:COMPOM
bobiproc (5K) CALCUL DE LA MUTUELLE INDUCTANCE ENTRE UN INDUCTEUR DECRIT ANALYTIQUEMENT PAR LA TABLE TBIOT ET UN INDUIT DE TYPE MAILLAGE. TBIOT.'SOUSTYPE' = INDUCTEUR TBIOT.1 = TABLE… P:@TOTAL
boobj (3K) Utilisation des opérateurs CHI1 et CHI2 test avec échange Ce test est identique à bo2.dgibi mais les entrées sont des OBJETS repertoire des fichiers "divers" P:DONCHI1,DONCHI2,LIESPECE,LINVCOMP,PARMCHI2 ext:COMPOM
calcul_inductance_ppipede (3K) example pour MPMA + JPMA calcul d'inductance d'un parallélépipède dans CAST3M et comparaison avec la formule analytique l'intérêt de MPMA + JPMA : on peut calculer…
calp1 (1K) Cas-test du calcul de VMIS dans le cas des poutres. On soumet l'extremite d'une poutre orientee suivant l'axe Ox a un deplacement suivant Oy, l'autre extremite etant…
calp2 (5K) Cas-test du calcul de VMIS et des contraintes en peau des poutres avec CALP. On soumet l'extremite d'une poutre orientee suivant l'axe Ox a un deplacement suivant Oy+Oz,… P:@PALETTE
canal-Chien (23K) Ce cas teste le modèle K-epsilon Bas Reynolds de Chien sur l'écoulement turbulent dans un canal plan. P:EXEC,KEPSILON
canal-Sharma (22K) Ce cas teste le modèle K-epsilon Bas Reynolds de Launder-Sharma sur l'écoulement turbulent dans un canal plan. P:EXEC,KEPSILON
canalBu (14K) Ce cas teste le modèle longueur de melange de Buleev sur l'écoulement turbulent dans un canal plan. P:EXEC,PRODT
canalKL (10K) Ce cas teste le modèle K-L bas Reynolds (Wolfshtein Yap) sur l'écoulement turbulent dans un canal plan. P:EXEC,KEPSILON
canalKLbr (21K) Ce cas teste le modèle K-L bas Reynolds (Wolfshtein Yap) sur l'écoulement turbulent dans un canal plan. P:EXEC,KEPSILON
carre (34K) ECOULEMENT AUTOUR D'UNE CYLINDRE DE SECTION CAREE Gregory Turbelin 29/12/1998 P:EXEC,FILTREKE,VNIMP
chaboche1 (5K) CHABOCHE1.DGIBI Objet : Test de validation d'une loi de comportement de materiau. Loi de comportement elastoviscoplastique de Chaboche. Description : Essai de… P:PASAPAS
chaboche2 (5K) CHABOCHE2.DGIBI Objet : Test de validation d'une loi de comportement de materiau. Loi de comportement elastoviscoplastique de Chaboche. Description : Essai de… P:PASAPAS
chaboche3 (5K) repertoire des fichiers "divers" CHABOCHE3.DGIBI Objet : Test de validation d'une loi de comportement de materiau. Loi de comportement elastoviscoplastique de Chaboche.… P:PASAPAS ext:chaboche3.txt
char_constant (4K) Test de fonctionnement des CHARGEMEnts constants Calcul thermo-mecanique d'une portion de cylindre en dilatation avec PASAPAS en grands deplacements - comparaison du… P:PASAPAS
choctvf (4K) choctvf.dgibi Thermique transitoire : Choc thermique, test élémentaire pour de l'opérateur LAPN en formulation Volumes Finis. Référence : J.F.Saccadura, Initiation aux… P:EXEC
clim (60K) VF, CLIM 2D BECCANTINI A., DM2S/SFME/LTMF, JANVIER 2002
clim3d (65K) VF, CLIM 3D BECCANTINI A., DM2S/SFME/LTMF, JANVIER 2002
clim3dj (55K) VF, CLIM 3D Jacobians in a rotated mesh BECCANTINI A., DM2S/SFME/LTMF, JANVIER 2002
clmult2D (108K) VF, Condition Limites en 2D pour les Equations d'Euler multiespeces Kudriakov S., DM2S/SFME/LTMF, FEVRIER 2003 Beccantini A., DM2S/SFME/LTMF, FEVRIER 2006: BC of…
clorite (10K) repertoire des fichiers "divers" Utilisation des modules CHI1 et CHI2 Jeu de données pour tester la chlorite d'Aspe ext:COMPSM
colline (15K) ECOULEMENT AUTOUR D'UNE COLLINE G. TURBELIN 14/12/99 P:EXEC,FILTREKE,VNIMP
colline_expl (17K) ECOULEMENT AUTOUR D'UNE COLLINE G. TURBELIN 14/12/99 P:EXEC,FILTREKE,VNIMP
comb (24K) NOM : comb.dgibi DESCRIPTION : We compute the AICC (Adiabatic Isochoric Complete Combustion), the AIBCC, (Adiabatic IsoBaric Complete Combustion), the CJ (Chapman -…
Comte-Bellot (14K) Ecoulement entre deux plaques planes infinies (Symétrie) Penser a augmenter YP qd Rey diminue Rey = 4.E6 -> YP = 1.e-3 Rey = 4.e4 -> YP=1.E2 Nu = 1.e-7 Rey=4.e6 P:EXEC,KEPSILON,PRODT,VNIMP
condmass (8K) CAS TEST : condmass.dgibi Test de la prise en compte de la condensation en masse dans la procédure métier execrxt. On considère une enceinte de 100 m3 isolée… P:EXECRXT,PSATT
conge_seg2_seg3 (2K) Petit test de l'opérateur CONG avec des éléments SEG2 et SEG3 Il convient de vérifier "à l'oeil" la qualité des congés de raccordement produits
consistence1_Godunov (7K) APPROCHE VF "Cell-Centred Formulation" pour la solution des Equations d'Euler pour un gaz parfait Gaz monoespece "calorically perfect" Consistence, methode GODUNOV A.…
consistence1_HUSVL (7K) APPROCHE VF "Cell-Centred Formulation" pour la solution des Equations d'Euler pour un gaz parfait Gaz monoespece "calorically perfect" Consistence, methode HUSVL A.…
consistence1_HUSVLH (7K) APPROCHE VF "Cell-Centred Formulation" pour la solution des Equations d'Euler pour un gaz parfait Gaz monoespece "calorically perfect" Consistence, methode HUSVLH A.…
consistence1_VanLeer (7K) APPROCHE VF "Cell-Centred Formulation" pour la solution des Equations d'Euler pour un gaz parfait Gaz monoespece "calorically perfect" Consistence, methode VanLeer A.…
consistence1_VLH (7K) APPROCHE VF "Cell-Centred Formulation" pour la solution des Equations d'Euler pour un gaz parfait Gaz monoespece "calorically perfect" Consistence, methode VLH A.…
contact2D-adhe (2K) TEST du MODELE CONTACT AVEC COMPOSANTE MATERIAU ADHE Maillage P:PASAPAS
Contact2Djeu (9K) Ce cas-test est une adaptation du cas-test Contact2D avec l'ajout d'un jeu entre les deux objets. Il permet de tester la gestion du contact fort par PASAPAS. Il simule… P:JEU,PASAPAS
Contact2Djeufaible (9K) Ce cas-test est une adaptation du cas-test Contact2D avec l'ajout d'un jeu entre les deux objets. Il permet de tester la gestion du contact faible par PASAPAS. Il simule… P:JEU,PASAPAS
Contact3Djeu (10K) Cas-test adapté de Contact3D.dgibi avec présence d'un jeu. test du Contact fort en 3D Ce cas-test permet de tester la gestion du contact par PASAPAS. Il simule la mise… P:JEU,PASAPAS
contactd_fmm (41K) Propagatrion d'une discontinuité de contact. Methode implicite sans matrice BECCANTINI A., SFME/LTMF, Fevrier 2003 Boundary conditions imposed on the border without…
continu_gdep1 (12K) continu_gdep1.dgibi = cas test basé sur gdep1.dgibi (de la base cast3m), mais avec une comparaison avec la procedure de CONTINUation Mots-clé : flambage, grand… P:AUTOPILO,CONTINU,FLAMBAGE,PASAPAS,PECHE
continu_snap (9K) continu_snap.dgibi = cas test basé sur snap.dgibi (de la base cast3m), mais avec une comparaison avec la procedure de CONTINUation Mots-clé : flambage, grand… P:AUTOPILO,CONTINU,PASAPAS
CORF1 (2K) CONSTITUTION DU SYSTEME DONNEE DU CHAMP INUCTEUR : 100T/s P:RAY
cormasse (2K) Tests de la procédure cormasse qui corrige un chpo afin que ses valeurs soient positives et inférieures à Maxrho, et que que son intégrale soit égale à une valeur cible. P:CORMASSE
coude (4K) DISCR='QUAF'; DISCR='LINE'; P:EXEC,VNIMP
coudep (4K) Ecoulement dans un Coude Test 3D pression continue methode de projection teste en 3D VNIMP FPU NS Ce test pose des problemes en QUAF ?? Il faut un minimum de mailles… P:EXEC,VNIMP
couette (6K) 1/Ecoulement de Couette engendré par la rotation de 2 cylindres concentriques. Comparaison à la solution analytique pour la vitesse. 2/Conducion de la chaleur dans un… P:EXEC
dcov2 (11K) 
dcov3 (12K) 
dhldp (3K) -------------- VARI option DHLDP ------------------------------- Test de l'opérateur VARI DHLDP(P,T) dervivee partielle de l'enthalpie specifique liquide par rapport a…
dhvdp (3K) -------------- VARI option DHVDP ------------------------------- Test de l'opérateur VARI DHVDP(P,T) dervivee partielle de l'enthalpie specifique vapeur par rapport a la…
dhvdt (3K) -------------- VARI option DHVDT ------------------------------- Test de l'opérateur VARI DHVDT(P,T) dervivee partielle de l'enthalpie specifique liquide par rapport a…
difasyk2D (32K) CAS TEST DIPHASIQUE LIQUIDE-LIQUIDE 2D PLAN Présentation: Ce cas test permet la simulation de la sédimention de gouttes sphériques de liquide immergé dans un milieu… P:EXEC,RAY
difasyk2Dax (32K) CAS TEST DIPHASIQUE LIQUIDE-LIQUIDE 2D PLAN Présentation: Ce cas test permet la simulation de la sédimention de gouttes sphériques de liquide immergé dans un milieu… P:EXEC,MONTAGNE,RAY
dpressu (7K) Containment depressurization (Phebus size) 3D mesh of a 14.5 m3 cylindrical containment with a 10cm in depth vertical wall. It the same than the one of the pressu family… P:EXECRXT
dpressupp (7K) Containment depressurization (Phebus size) 3D mesh of a 14.5 m3 cylindrical containment with a 10cm in depth vertical wall. It the same than the one of the pressu family… P:EXECRXT
dpsat (3K) -------------- VARI option DPSAT ------------------------------- Test de l'opérateur VARI DPSAT(T) dervivee partielle de la pression de saturation de la vapeur par… P:PSATT
drvdp (3K) -------------- VARI option DRVDP ------------------------------- Test de l'opérateur VARI DRVDP(P,T) dervivee partielle de la densite de la vapeur d'eau par rapport a la…
drvdt (3K) -------------- VARI option DRVDT ------------------------------- Test de l'opérateur VARI DRVDT(P,T) dervivee partielle de la densite de la vapeur d'eau par rapport a la…
drx_grd_defo_cisail_elplas2 (11K) CAS TEST POUR LES GRANDES DÉFORMATIONS ref Rapport DMT 96/359 A de Gayffier "Les lois de comportement des matériaux solides en grandes déformations dans Castem2000 et… P:DREXUS
dvispassiLM (8K) CAVITE CARREE ­ VAHL­DAVIS Methode de projection implicite Malvina Renesson Aout 1999 P:EXEC
dvispassiMM (8K) CAVITE CARREE ­ VAHL­DAVIS Methode de projection implicite Malvina Renesson Aout 1999 P:EXEC
dvispassiQM (8K) CAVITE CARREE ­ VAHL­DAVIS Methode de projection implicite Malvina Renesson Aout 1999 P:EXEC
dvispp (8K) CAVITE CARREE ­ VAHL­DAVIS Methode de projection implicite Malvina Renesson Aout 1999 P:EXEC
dync01 (13K) RÉPONSE FORCEE D'UN OSCILLATEUR DE DUFFING P:@PALETTE,FLOQUET
dync02 (10K) Calcul d'un rotor de type Jeffcott avec contact frottant avec la methode HBM (DYNC) ___ ^ Z _|_ kc,mu |__ _______ jeu |_ \_ | k,c | | | \ \ |----------| m |----------|… P:BALOURD,FLOQUET,JEU
dyne04 (5K) VALIDATION DE L'OPTION LIAISON CONDITIONNELLE DE DYNE DYNE04.DGIBI ref : test1 du Rapport DMT/94.483 de De Langre reimporte dans la base des cas-test par BP en 2019… P:JEU
dyne05 (10K) DYNE05 : Calcul d'un oscillateur frottant en contact permanent en situation de "Stick and Slip" | Fn ___v___ | k | |--> x(t) |-----|/|/|/|-----| m | | |_______| µd=µs… P:JEU
dyne06 (13K) DYNE06 : Calcul d'un rotor de type Jeffcott avec contact frottant ___ ^ Z _|_ kc,mu |__ _______ jeu |_ \_ | k,c | | | \ \ |----------| m |----------| +--|--|-----> Y |… P:JEU
dy_dev12 (14K) Cas-Test de la liaison palier de l'operateur DYNE Masse ponctuelle sur 1 squeeze-film (NL) Chargement statique = poids propre = -m*g --> Wcharg + Chargement tournant =…
dy_devo1 (14K) VALIDATION DE LA LIAISON COUPLAGE_DEPLACEMENT base A modele GRANGER PAIDOUSSIS (UTILISEE POUR LE CALCUL DES FORCES FLUIDELASTIQUES) EXEMPLE INSPIRE DU TEST38 de GERBOISE P:POSTVIBR
dzvdp (4K) -------------- VARI option DZVDP ------------------------------- Test de l'opérateur VARI DZVDP(P,T) dervivee partielle du facteur de compressibilite de la vapeur d'eau…
dzvdt (4K) -------------- VARI option DZVDT ------------------------------- Test de l'opérateur VARI DZVDT(P,T) dervivee partielle du facteur de compressibilite de la vapeur par…
eauacti (4K) repertoire des fichiers "divers" Test de bon fonctionnement des operateurs LOGK COAC FION et NEUT eau + temperature 80. + pression CO2 ext:COMPSM
eautemp (9K) repertoire des fichiers "divers" Test de validation des operateurs CHI1 et CHI2 eau + gradient thermique + pression CO2 ext:COMPSM
echi_som (2K) test de non-regression concernant l'operateur ECHI
effmarti (4K) Test sur la procedure de EFFMARTI pour tester la projection des efforts globaux sur un element coque vers le modele à trois couches de MARTI. On teste un seul element… P:EFFMARTI
elas21 (5K) test de la rigidite BAEX avec 2 directions d'excentrement BL le 25.07.2017 (correction erreurs dans MAPAEX) RAPPEL: une barre excentree est pilotee en allongement par…
elas_hook_endom (4K) Petit test des operateurs ELAS et HOOK dans les cas des modeles endommageables avec fourniture d'un MCHAML de variables internes. On verifie que la matrice de Hooke…
elimrela (7K) NOM : elimrela DESCRIPTION : Test de l'élimination des relations dans RESO et KRES LANGAGE : GIBIANE-CAST3M AUTEUR : Stephane GOUNAND (CEA/DEN/DM2S/SEMT/LTA) mel :…
elno (7K) TEST ELNO On teste l'operateur 'ELNO' sur un champ lineaire Le maillage est fait de TRI3 'ET' QUA4 On teste l'operateur 'ELNO' dans le cas VF A. BECCANTINI TTMF NOVEMBRE…
enc2D-therco (6K) 2D axisymetric air containment with convective heat transfer and heat losses with implicit wall coupling P:EXECRXT
enc2d (5K) Adiabatic and 2D axisymetric containment H2, He and CO injections P:EXECRXT
enc2dFP (7K) Adiabatic and 2D axisymetric containment H2, He and CO injections We check MACRO-MSOMMET (instead of LINE-MSOMMET in enc2d). With wall functions, QUAF-MSOMMET and… P:EXECRXT
enc2dke (7K) formulation (semi explicit EFM1) and wall functions Adiabatic and 2D axisymetric containment He and steam injections With wall functions, QUAF-MSOMMET and QUAF-CENTREP1… P:EXECRXT,KEPSILON
enc2dpp (5K) Adiabatic and 2D axisymetric containment H2, He and CO injections P:EXECRXT
enc2dQ (5K) Adiabatic and 2D axisymetric containment H2, He and CO2 injections P:EXECRXT
enc2d_therm1 (6K) 2D axisymetric air containment with convective heat transfer and heat losses Same as enc2D-therco but without implicit wall coupling P:EXECRXT
equ_chaleurVF2_dirneuvfsym (14K) NOM : equ_chaleurVF2_dirneummixte.dgibi DESCRIPTION : Solution stationnaire de l'équation de la chaleur (2D) GEOMETRIE : Un carré y ^ y=1 |------------ | | | | | | |x =… P:@POMI
exemple_nommer (1K) Fichier "exemple_nommer.dgibi" test est un mot contenant 'c3m' ;
Ex_HHO (3K) TRAC (SbasC et SbasG) ; TRAC (MFuel et MClad) 'FACE' ;
fatigue (3K) operateur FATIGUE exemples critere DANG VAN : JL FAYART P:PASAPAS
fatigue_BL (12K) Simulation de torsion et/ou traction d'un cylindre en fatigue stage Bowen LIU (ENSTAPARISTECH) ete 2022 P:EXPLORER,PASAPAS
fcourant (6K) NOM : FCOURANT DESCRIPTION : Teste la procédure calculant la fonction de courant sur un ecoulement de Poiseuille en 2D et 2D axi LANGAGE : GIBIANE-CAST3M AUTEUR :… P:EXEC,FCOURANT
fcourant2 (8K) NOM : FCOURANT2 DESCRIPTION : Teste la procédure calculant la fonction de courant sur des solutions analytiques en 2D et 2D axi LANGAGE : GIBIANE-CAST3M AUTEUR :… P:FCOURANT
fefp_rhmc_bcn (470K)  P:PASAPAS
fefp_vmt_bcn (3K) NECKING EXAMPLE VMT model: MSHAPE = 1. => Von Mises MSHAPE = 20. => Tresca FORMULATION: Lagrangian (Total or Update) OPCIONES GENERALES P:PASAPAS
fimpvf (6K) APPROCHE VF "Cell-Centred Formulation" pour la solution des Equations d'Euler pour un gaz parfait OPERATEUR FIMP Test de la gravité A. BECCANTINI DEN/DM2S/SFME/LTMF JANV…
flam4 (4K) Flambage d'une plaque carree sous deformation de cisaillement Y ^ | | p2+----------------+ ^ F >| | | | | >| | ^ F | | | >| | | | ^ F >| | |… P:POSTVIBR
flslic4 (11K) test de validation de l' élément de raccord fluide - structure LIC4. calcul du mode n=3 m=1 d'un système de coques concentriques. La coque exterieure est supposée… P:ACIER
fluage_fibre_blackburn2_1 (5K) Test du modele de fluage de Blackburn 2 pour les modeles de section (appeles aussi modeles de poutre a fibre) --> chargement uniaxial en traction --> comparaison a la… P:PASAPAS,POUT2MAS
fluage_fibre_blackburn_1 (5K) Test du modele de fluage de Blackburn pour les modeles de section (appeles aussi modeles de poutre a fibre) --> chargement uniaxial en traction --> comparaison a la… P:PASAPAS,POUT2MAS
fluage_fibre_lemaitre_1 (4K) Test du modele de fluage de Lemaitre pour les modeles de section (appeles aussi modeles de poutre a fibre) --> chargement uniaxial en traction --> comparaison a la… P:PASAPAS,POUT2MAS
fluage_fibre_norton_1 (4K) Test du modele de fluage de Norton pour les modeles de section (appeles aussi modeles de poutre a fibre) --> chargement uniaxial en traction --> comparaison a la… P:PASAPAS,POUT2MAS
fluage_fibre_norton_2 (5K) Comparaison du modele de fluage de Norton : - modele poutre a fibre VS modele massif - chargement uniaxial, traction puis compression - en force imposee P:PASAPAS,POUT2MAS
fluage_fibre_norton_3 (5K) Comparaison du modele de fluage de Norton : - modele poutre a fibre VS modele massif - chargement uniaxial, traction puis compression - en deplacement impose P:PASAPAS,POUT2MAS
fluage_fibre_polynomial_1 (4K) Test du modele de fluage polynomial pour les modeles de section (appeles aussi modeles de poutre a fibre) --> chargement uniaxial en traction --> comparaison a la… P:PASAPAS,POUT2MAS
fluage_fibre_polynomial_2 (6K) Comparaison du modele de fluage polynomial : - modele poutre a fibre VS modele massif - chargement uniaxial, traction puis compression - en force imposee P:PASAPAS,POUT2MAS
fluage_fibre_polynomial_3 (6K) Comparaison du modele de fluage polynomial : - modele poutre a fibre VS modele massif - chargement uniaxial, traction puis compression - en deplacement impose P:PASAPAS,POUT2MAS
fluechnak (9K) CAS TEST : fluechnak.dgibi TRANSPORT GEOCHIMIE ECHANGE IONIQUE AVEC BILAN DE FLUX P:CHITRNSP,DESTRA,DONCHI1,DONCHI2,LIESPECE,LINVCOMP,PARMCHI2,TRACHIS,TRACHIT ext:COMPOM
fluxtotalEFMH (12K) CAS TEST : transport1.dgibi TEST TRANSPORT1 CALCUL DARCY ISOTROPE TRANSPORT. Transport d'un front. dT -- + div (uT - Kgrad(T)) = 0 dt Ce test permet de vérifier le bon… P:TRANSGEN
fluxtotalVF (12K) CAS TEST : transport1.dgibi TEST TRANSPORT1 CALCUL DARCY ISOTROPE TRANSPORT. Transport d'un front. dT -- + div (uT - Kgrad(T)) = 0 dt Ce test permet de vérifier le bon… P:TRANSGEN
forgeage (8K) fichier forgeage.dgibi F O R G E A G E . D G I B I Objet : Exemple de simulation du forgeage d'un tube en compression simple. On applique un effort sur le bord superieur… P:ADAPTE,BOITE,PASAPAS
formation_debutant_1_maillage (4K) FORMATION DEBUTER AVEC CAST3M - CALCULS THERMO-MECANIQUES Modelisation du comportement thermo-mecanique d'une structure avec une cavite Ce fichier est la partie 1 sur 3…
formation_debutant_2_thermique (10K) FORMATION DEBUTER AVEC CAST3M - CALCULS THERMO-MECANIQUES Modelisation du comportement thermo-mecanique d'une structure avec une cavite Ce fichier est la partie 2 sur 3… P:PASAPAS,RAY
formation_debutant_3_mecanique (15K) FORMATION DEBUTER AVEC CAST3M - CALCULS THERMO-MECANIQUES Modelisation du comportement thermo-mecanique d'une structure avec une cavite Ce fichier est la partie 3 sur 3… P:PASAPAS
formation_pasapas_1_initial (2K) FORMATION AVANCEE SUR LA PROCEDURE PASAPAS Flexion d'une poutre en grands deplacements avec chargemet suiveur Ce fichier constitue la mise donnee initiale du probleme et… P:PASAPAS
formation_pasapas_1_solution (4K) FORMATION AVANCEE SUR LA PROCEDURE PASAPAS Flexion d'une poutre en grands deplacements avec chargemet suiveur Ce fichier constitue la mise donnee solution du probleme et… P:PASAPAS
formation_pasapas_2_initial (3K) FORMATION AVANCEE SUR LA PROCEDURE PASAPAS Rupture d'une plaque trouee en traction Comportement elastique lineaire Ce fichier constitue la mise donnee initiale du… P:PASAPAS
formation_pasapas_2_solution (3K) FORMATION AVANCEE SUR LA PROCEDURE PASAPAS Rupture d'une plaque trouee en traction Comportement elastique lineaire Ce fichier constitue la mise donnee solution du… P:PASAPAS
formation_pasapas_2_solution_bis (4K) FORMATION AVANCEE SUR LA PROCEDURE PASAPAS Rupture d'une plaque trouee en traction Comportement elastique lineaire Ce fichier constitue la mise donnee solution du… P:PASAPAS
formation_pasapas_3_initial (3K) FORMATION AVANCEE SUR LA PROCEDURE PASAPAS Chauffage d'une plaque par une source de chaleur variable dependante de la temperature Ce fichier constitue la mise donnee… P:PASAPAS
formation_pasapas_3_solution (5K) FORMATION AVANCEE SUR LA PROCEDURE PASAPAS Chauffage d'une plaque par une source de chaleur variable dependante de la temperature Ce fichier constitue la mise donnee… P:CHARTHER,PASAPAS
formation_pasapas_4_initial (4K) FORMATION AVANCEE SUR LA PROCEDURE PASAPAS Variation d'un jeu sous l'action d'une sollicitation thermique en regime transitoire Ce fichier constitue la mise donnee… P:JEU,PASAPAS
formation_pasapas_4_solution (5K) FORMATION AVANCEE SUR LA PROCEDURE PASAPAS Variation d'un jeu sous l'action d'une sollicitation thermique en regime transitoire Ce fichier constitue la mise donnee… P:JEU,PASAPAS
formation_pasapas_4_solution_bis (6K) FORMATION AVANCEE SUR LA PROCEDURE PASAPAS Variation d'un jeu sous l'action d'une sollicitation thermique en regime transitoire Ce fichier constitue la mise donnee… P:JEU,PASAPAS
format_msg (1K) TEST DES TABULATIONS DANS L'OPERATEUR CHAINE TEST DE LA SYNTAXE 'AVEC' DE L'OPERATEUR ERRE
fusion (9K) fichier fusion.dgibi Test de validation de l'option FUSION du modele. Cette option permet de mettre a zero les variables internes du modele lorsque la temperature… P:PASAPAS,PECHE
fusion2 (6K) --------------------- F U S I O N 2 . D G I B I --------------------- Cas-test de validation de l'option FUSION avec modele de Chaboche. Simulation d'une essai de… P:BIBLIO,PASAPAS
fvol (36K) NOM : FVOL DESCRIPTION : Cas test : gravité : comparaison de deux méthodes de projection VPI1 et VPI2 éléments P2/P1 ou Q2/Q1 LANGAGE : GIBIANE-CAST3M AUTEUR : Stéphane… P:@STBL,ANIME,EXEC
gatt_dpg (13K) Test gatt_dpg.dgibi: Jeux de données TEST DE VALIDATION MODELE GATT_MONERIE AFA3GLAA INCOMPRESSIBLE AVEC COUPLAGE DYNAMIQUE MAILLAGE: EPROUVETTE CARRE CHARGEMENT:… P:@GATTPAR,PASAPAS ext:fichier_gatt
gdep2_boucle (2K) anneau sous pression non uniforme position du probleme il s agit de determiner la deformee d un anneau sous pression non uniforme suiveuse en grands deplacements… P:PASAPAS,PECHE
gdtract3d (11K) MODELE HYPERELASTIQUE GORNET-DESMORAT QUASI-INCOMPRESSIBLE EN GRANDES TRANSFORMATIONS TEST DE VALIDATION DU MODELE : TRACTION (3D) SIMPLE SELON AXE Z COMPARAISON AVEC LA… P:PASAPAS
gonfl2Dex (25K) Jeu de données MISTRA pour le maillage 2D de l enceinte Il a été choisi de mailler tous les volumes à charge ensuite à l utilisateur de ne retenir que ce qui l intéresse… P:ACIER,CALCP,ENCEINTE,EXECRXT
gravite (11K) NOM : GRAVITE DESCRIPTION : Cas-test gravité servant à tester la méthode méthode de projection incrémentale. On doit trouver vitesse nulle et pression hydrostatique… P:EXEC
hbm_duffing (14K) Systeme a un degre de liberte Oscillateur de Duffing calcule en k harmoniques : m*x'' + c*x' + k*x + a*x^3 = f*cos(w*t) Continuation + HBM + AFT CHARMECA.PROCEDUR Calcul… P:AFT,CONTINU,HBM,HBM_POST
hbm_duffing_mu (14K) Systeme a un degre de liberte Oscillateur de Duffing calcule en k harmoniques : m*x'' + c*x' + k*x + a*x^3 = f*cos(w*t) Continuation + HBM + AFT CHARMECA.PROCEDUR Calcul… P:AFT,CONTINU,HBM,HBM_POST
hbm_jeffcott_contact (17K) Systeme a deux ddl ROTOR JEFFCOTT AVEC CONTACT ROTOR-STATOR m x + c x + k x = Fbal*cos wt + Fchoc_x m y + c y + k y = Fbal*sin wt + Fchoc_y modele de contact : Fn =… P:AFT,CALCULER,CONTINU,HBM,HBM_POST,ORBITE
hbm_jeffcott_contact_alfa (17K) Systeme a deux ddl ROTOR JEFFCOTT AVEC CONTACT ROTOR-STATOR m x + c x + k x = Fbal*cos wt + Fchoc_x m y + c y + k y = Fbal*sin wt + Fchoc_y modele de contact : Fn =… P:AFT,CALCULER,CONTINU,HBM,HBM_POST,ORBITE
hbm_vanderpol_force (19K) Systeme a un degre de liberte Oscillateur Van der Pol force calcule en k harmoniques m*x'' - c (1-x^2) *x' + k*x = f cos wt m=1; k=1; c=1; w=1; f = [ 0.1 ... 2 ]… P:AFT,CONTINU,HBM,HBM_POST,ORBITE
Henc2d (3K) Enceinte 2D Axisymetrique Relachement d'un melange d'hydrogene et d'helium P:EXECRXT
Hertz-cylindre-plan-2D (8K) Modelisation d'un contact cylindre-plan en 2D Comparaison du champ de pression calcule a celui issu de la theorie developpee par Hertz. P:PASAPAS
HHO_Membrane_Cook_HPP_Elas (10K) Test : Membrane de Cook - Elasticite - HPP - Deformations/contraintes Planes Unites utilisees : S.I. (m, N, kg, Pa)
hotan (3K) Parametres geometriques Maillage DENmail0 = R1 / 15. ; DENS2 = L1 / 15. ; P:PASAPAS
hy2 (3K) --- 2 JUIN 1993 --- PERTES DE CHARGE et GMV (Groupe Moto Ventilateur) CANAL LONGUEUR 10. LARGEUR 1. test cas isotherme NS FROT ET GMV On considre l'coulement dans un… P:EXEC,VNIMP,VTIMP
indi (10K) Petit test de l'operateur INDI options 'ASPE' et 'SKEW' Exemple en 2D
inj (12K) INJ.DGIBI (Cataldo Caroli) Mai 99 Teste la procedure ENCEINTE P:ENCEINTE
injair (9K) Air injection inside a non adiabatic axisymetric cavity Comparaison in average with an analytic solution Analytical solution Mean pressure, temperature and density are… P:CALCP,EXECRXT
injairA (8K) Air injection inside an adiabatic axisymetric cavity Comparaison in average with an analytic solution Analytical solution Mean pressure, temperature and density are… P:CALCP,EXECRXT
injN2 (9K) N2 injection inside a non adiabatic axisymetric cavity Comparaison in average with an analytic solution Analytical solution Mean pressure, temperature and density are… P:CALCP,EXECRXT
injN2A (9K) N2 injection inside an adiabatic axisymetric cavity Comparaison in average with an analytic solution Analytical solution Mean pressure, temperature and density are… P:CALCP,EXECRXT
injxx (12K) INJ.DGIBI (Cataldo Caroli) Mai 99 Teste la procedure ENCEINTE P:ENCEINTE
INTLIN (1K) EXEMPLE INTLIN.dgibi Entrée : Sans objet Sortie : Sans objet Commentaire : Test de la procedure @INTLIN.PROCEDUR Developpeur : Benjamin Richard CEA, DEN, DANS, DM2S,… P:@INTLIN
ipol_pid (6K) Test de l'operateur IPOL option 'PID' interpolation multi-dimensionnelle par Ponderation Inverse a la Distance Application a l'interpolation d'une fonction de 1…
joi1_decol (29K) Objet : controler le probleme (solution non physique) observé lors de la re-ouverture du JOI1 dans la simulation avec Cast3M 2019 de la compression du modele simplife du… P:JEU,PASAPAS
joi1_NaN (5K) TEST RESSORT - JOINT Mohr Coulomb - RESSORT en série pour vérification plan contact yOz <=> direction normale = Ux -| -|_________.__________._________.<= Uimposé en… P:@CARTOON,JEU,PASAPAS
jointsoft1 (8K) J O I N T S O F T 1 . D G I B I Objet : Cas-test de validation du modele de joint "JOINT_SOFT" (JOI2). Le modele est valide en : - compression simple - traction simple -… P:PASAPAS
konmsp_impl2D (71K) APPROCHE VF "Cell-Centred Formulation" pour la solution des Equations d'Euler pour un gaz parfait multiespes Implicit: calcul du jacobien du residu Cas gaz multiespes,…
konv_impl (25K) APPROCHE VF "Cell-Centred Formulation" pour la solution des Equations d'Euler pour un gaz parfait OPERATEURS PRIM, PRET, KONV Implicit: calcul du jacobien du residu Cas…
konv_impl2ord2 (36K) APPROCHE VF "Cell-Centred Formulation" pour la solution des Equations d'Euler pour un gaz parfait OPERATEURS PRIM, PRET, KONV Implicit: calcul du jacobien du residu (2nd…
konv_impl2ord_murs (26K) APPROCHE VF "Cell-Centred Formulation" pour la solution des Equations d'Euler pour un gaz parfait OPERATEURS PRIM, PRET, KONV Implicit: calcul du jacobien du residu (2nd…
kopscmct2 (19K) NOM : KOPSCMCT2 DESCRIPTION : On vérifie que KOPS CMCT donne des résultats corrects avec des RIGIDITES et de MATRIKS LANGAGE : GIBIANE-CAST3M AUTEUR : Stéphane GOUNAND… P:ININLIN
kopsrot2D (4K) CAS TEST : kopsrot2D.dgibi TEST kopsrot2D Ce test permet de vérifier le bon fonctionnement de l'option ROT de KOPS en 2D PLAN et 2D AXIS pour les trois familles…
kopsrot3D (3K) CAS TEST : kopsrot3D.dgibi TEST kopsrot3D Ce test permet de vérifier le bon fonctionnement de l'option ROT de KOPS en 3D pour les trois familles d'éléments compatibles…
kops_rima (13K) NOM : KOPS_RIMA DESCRIPTION : On vérifie que KOPS RIMA donne des résultats corrects LANGAGE : GIBIANE-CAST3M AUTEUR : Stéphane GOUNAND (CEA/DEN/DM2S/SFME/LTMF) mél :… P:ININLIN
kres_cd1 (27K) BEGINPROCEDUR glapn NOM : GLAPN DESCRIPTION : Un laplacien scalaire LANGAGE : GIBIANE-CAST3M AUTEUR : Stéphane GOUNAND (CEA/DEN/DM2S/SFME/LTMF) mél :… P:@STBL,ININLIN
kres_cd2 (27K) BEGINPROCEDUR glapn NOM : GLAPN DESCRIPTION : Un laplacien scalaire LANGAGE : GIBIANE-CAST3M AUTEUR : Stéphane GOUNAND (CEA/DEN/DM2S/SFME/LTMF) mél :… P:@STBL,ININLIN
lapn_impl1 (36K) APPROCHE VF "Cell-Centred Formulation" pour la solution des Equations de 'NS' pour un gaz parfait OPERATEURS PRIM, PENT, LAPN Implicit: calcul du jacobien du residu Cas…
lapn_impl3D_mel (75K) ; Préambule ;; Description du cas-test APPROCHE VF "Cell-Centred Formulation" pour la solution des Equations de Navier-Stokes pour un gaz parfait OPERATEURS PRIM, PENT,…
lapn_impl_mel (85K) ; Préambule ;; Description du cas-test APPROCHE VF "Cell-Centred Formulation" pour la solution des Equations de Navier-Stokes pour un gaz parfait OPERATEURS PRIM, PENT,…
latliw (45K) $$$$ EXEC EXEC PROCEDUR MAGN 03/03/31 21:15:04 4631 X EXEC (Procedure) Procedure EXEC Objet : Execute un algorithme décrit dans une table RV de type EQEX. Cette table… P:EXAC,EXEC,VERTYTAB,VNIMP
latw (45K) $$$$ EXEC EXEC PROCEDUR MAGN 03/03/31 21:15:04 4631 X EXEC (Procedure) Procedure EXEC Objet : Execute un algorithme décrit dans une table RV de type EQEX. Cette table… P:EXAC,EXEC,VERTYTAB,VNIMP
lbdaliq (7K) Conductivité thermique de l'eau Valeurs de référence : tables VDI Comparaisons de différentes formules et tests de 'VARI' 'LBDALIQ' P:PSATT
lignecourant (4K) CALCUL DES LIGNES DE COURANT : ON TESTE LES OPERATEURS LAPN ET FIMP ON VERIFIE QUE L'ERREUR ENTRE PSI_NUM ET PSI_EXACT EVOLUE DE FACON QUADRATIQUE H.… P:EXEC
lire_CSV (3K) Presentation : Ce cas-test permet de lire directement des fichiers au format 'CSV'. Le resultat est un objet de type TABLE indice de 1 a N. Chaque indice est un LISTREEL… ext:fichier_ACQ.txt
Marangoni1 (11K) CAS TEST EFFET MARANGONI UTILISATION DE LA LOI DE CHAN, CHEN, MAZUMDER Journal of Heat Transfert, vol 110, 1988 DESCRIPTION DU TEST : Ce test a pour but d'étudier… P:EXEC
Marangoni2 (12K) CAS TEST EFFET MARANGONI UTILISATION DE LA LOI DE CHAN, CHEN, MAZUMDER Journal of Heat Transfert, vol 110, 1988 DESCRIPTION DU TEST : Ce test a pour but d'étudier… P:EXEC
Marangoni3 (12K) CAS TEST D'UN ECOULEMENT SOUS UN FLUX D'ENERGIE CONCENTRE UTILISATION DE LA LOI DE CHAN, CHEN, MAZUMDER Journal of Heat Transfert, vol 110, 1988 DESCRIPTION DU TEST :… P:EXEC
mdiavf2 (16K) Utilisation de l'operateur MDIA pour creér un jacobien analytique dans le cas d'injection subsonic d'air dans l'air A. Beccantini, SFME/LTMF
mfil (1K) fichier mfil.dgibi Filtering of a field using a rigidity matrix genrated by MFIL. Author: Guenhael Le Quilliec (LaMe - Polytech Tours) Version: 1.0 2021/01/04 Original…
MODTRI (2K) EXEMPLE MODTRI.dgibi Entrée : Sans objet Sortie : Sans objet Commentaire : Test de la procedure @MODTRI.PROCEDUR Developpeur : Benjamin Richard CEA, DEN, DANS, DM2S,… P:@MODTRI
mrcframe_test (21K) Test sur la procedure MRCFRAME, fonction pour determiner la marge de securité d'un element type POUT et TIMO soumis à un chargement sismique. Les effort sont calculées… P:MRCFRAME
mrcshell (25K) Test sur la procedure de MRCSHELL pour calculer les marges de securites pour les elements en beton arme de type coque. On cosidere deux cas: Cas1 CAS_1 = 1; On considere… P:@TOTAL,EFFMARTI,MRCSHELL,SISSIB
mrsl_bcn (4K) TRIAXIAL TEST WITH A NON-HOMOGENEOUS SAMPLE TEST: MRS-Lade model P:PASAPAS
muchamevol (32K) Cas-test de l'operateur '*' et '/' Ce cas-test verifie la multiplication (la division) de MCHAMLs de composante de type EVOLUTIOn : 1. Multiplication et division par un…
muliq (7K) Viscosité dynamique de l'eau Valeurs de référence : tables VDI Comparaisons de différentes formules et tests de 'VARI' 'MULIQ' P:DYNAMIC,PSATT
mulmatflo (4K) OPERATEUR 'KOPS' OPERATEUR 'MDIA' Multiplication MATRIK FLOTTANT et MATRIK CHPOINT
nlin_burger (17K) NOM : nlin_burger.dgibi DESCRIPTION : We compute the 2D Burger problem. Scalar numerical viscosity is added. LANGAGE : GIBIANE-CAST3M AUTEUR : Alberto BECCANTINI… P:ININLIN
nlin_cavity (25K) NOM : nlin_cavity.dgibi DESCRIPTION : We compute the flow governed by the incompressible Navier-Stokes equations in a lid driven cavity. LANGAGE : GIBIANE-CAST3M AUTEUR… P:ININLIN
nlsb_operateur (5K) Simulation COMPACT TENSION TEST ^ ^ ^ ^ ^ ^ | | | | | | | | | | | | | | | | | | >|________________| ^^^^^^^^^ Analyse de la description du champs nonlocal en pointe…
ns1 (9K) NOM : NS1 DESCRIPTION : Ecoulement de Navier-Stokes dans une tete de Mickey avec force tangente sur le bord On utilise bloq depl dire pour imposer u.n = 0 Le test… P:EXEC,FCOURANT,ININLIN,MONTAGNE,POINTCYL
NSmchaml_nonreg (4K) Jeu de données permettant de tester les spg des chaml suivant le type d'élément fini (vitesse/pression) choisi (option navi) Date de création : 16/03/2005 Auteur : A.…
ns_kreso (44K) NOM : NS_KRESO DESCRIPTION : Cas-test équations de Navier-Stokes incompressibles. Cavité carrée entrainee On utilise KRES et RESO et on vérifie que les résultats obtenus… P:DEADUTIL,ININLIN
ns_ouvert (14K) CAS-test permettant de vérifier la conservation des débits volumiques dans le cas d'un ouvert Date de création : Juillet 2007 (A. Bleyer) correction du bug dans… P:EXEC,PRODT,VNIMP
ntableau (1K) NOM : NTABLEAU DESCRIPTION : Le but de ce cas-test est de tester le trace d'un tableau de chiffres pour les diverses options et sorties. Malheureusement, on ne peut…
ODWp (6K) Fluide PSEUDOPLASTIQUE : Ecoulement de POISEUILLE loi d'OSTWALD de WAELE nn= 0.8, 0.6 , 0.4 CANAL LONGUEUR 10. LARGEUR 4. Algorithme semi - implicite Auteur : Isabelle… P:EXEC,VNIMP,VTIMP
onera3 (5K) ONERA3.DGIBI Objet : Test de validation d'une loi de comportement de materiau. Loi de comportement elastoviscoplastique ONERA (Chaboche unifie). Validation de la loi de… P:PASAPAS ext:chaboche3.txt
operquaf (15K) NOM : OPERQUAF DESCRIPTION : Tester le fonctionnement de certains operateurs de maillage avec les QUAFs suite aux
ordo_2 (5K) TEST DE L OPERATEUR ORDO 'COUT' POUR LE CALCUL DE LA PERMUTATION OPTIMISANT UN COUT BP, 2016-06-24 mot-cles : mathematiques, permutation, arrangement petite procedure… P:FACTORIE
orieelem (7K) NOM : ORIEELEM DESCRIPTION : On teste ORIE et INVE pour les elements massifs sur des maillages à 1 element. Egalement, on peut tracer les elements pour savoir comment…
oscicyl2 (4K) NOM : OSCICYL2 DESCRIPTION : Cylindre oscillant dans une cavité fermée Deux paramètres : le nombre de Reynolds (convection/viscosité) le nombre de Keulegan-Carpenter… P:PASAPAS
ottovari_compression (3K) Test du modele OTTOVARI en compression DEFINITION DE LA GEOMETRIE P:PASAPAS
ottovari_compression_traction (3K) Test du modele OTTOVARI en compression puis traction DEFINITION DE LA GEOMETRIE P:PASAPAS
ottovari_traction (2K) Test du modele OTTOVARI en traction DEFINITION DE LA GEOMETRIE P:PASAPAS
ottovari_tritraction (3K) Test du modele OTTOVARI en tri-traction DEFINITION DE LA GEOMETRIE P:PASAPAS
ouglova_1D (3K) Cas test de l'implantation numerique du modele OUGLOVA 1D Developpe par : Romili PAREDES Benjamin RICHARD Contact : Romili.Paredes@cea.fr Benjamin.Richard@cea.fr… P:@GLOBAL,PASAPAS
ouglova_3D (3K) Cas test de l'implantation numerique du modele OUGLOVA 3D Developpe par : Romili PAREDES Benjamin RICHARD Contact : Romili.Paredes@cea.fr Benjamin.Richard@cea.fr… P:@GLOBAL,PASAPAS
ouglova_CP (3K) Cas test de l'implantation numerique du modele OUGLOVA 2D en contraintes planes Developpe par : Romili PAREDES Benjamin RICHARD Contact : Romili.Paredes@cea.fr… P:@GLOBAL,PASAPAS
ouglova_DP (3K) Cas test de l'implantation numerique du modele OUGLOVA 2D en deformations planes Developpe par : Romili PAREDES Benjamin RICHARD Contact : Romili.Paredes@cea.fr… P:@GLOBAL,PASAPAS
ouglova_fibre (3K) Cas test de l'implantation numerique du modele OUGLOVA 1D MULTIFIBRES Developpe par : Romili PAREDES Benjamin RICHARD Contact : Romili.Paredes@cea.fr… P:@GLOBAL,PASAPAS
ouvfiss2D (1K) TEST DE l'OPERATEUR OUVFISS EN 2D ON TIRE SUR UN BARREAU ENDOMMAGEABLE UN DEFAUT EST P:@GLOBAL,OUVFISS,PASAPAS
panach1 (14K)  P:EXEC,FILTREKE
panachekei (17K) JET/PANACHE 2D - SEMI-INFINI Comparaison K - Epsilon / RNG K - Epsilon il suffit pour cela d'enlever ou remettre l'option RNG Mode axisymetrique Le Richardson est… P:EXEC,KEPSILON,PRODT
partition (7K) NOM : partition.dgibi DESCRIPTION : Teste les options de partitionnement de maillage de l'operateur PART P:TRACPART
pent3D1 (10K) Finite Volume, "Cell-Centred Formulation". PENT, operator to compute gradients and limiters A. BECCANTINI, TTMF JANUARY 2001
pent3D2 (11K) APPROCHE VF "Cell-Centred Formulation". OPÉRATEUR PENT, pour le calcul des gradients et de limiteurs Cas test: calcul du limiteur en 3D A. BECCANTINI, TTMF MAI 1998
pent3D3 (9K) APPROCHE VF "Cell-Centred Formulation". OPÉRATEUR PENT, pour le calcul des gradients et des limiteurs Cas test: calcul du gradient en 3D avec condition de 'TYPE' mur A.…
pentaxi (5K) Finite Volume, "Cell-Centred Formulation". 'MODE' 'AXIS' We check that 3D axis-symmetrical = 2D 'MODE' 'AXIS' Operateur 'PENTE' A. BECCANTINI, LTMF FEBRUARY 2004…
pente (41K) Finite Volume, "Cell-Centred Formulation". PENT, operator to compute gradients and limiters A. BECCANTINI, TTMF JANUARY 2001
pilotage_indirect_1 (10K) Problem description: In the example below, we study the effects caused by the progressive strain localization. The structure consists of a bar under uniform tension in… P:@EXCEL1,PASAPAS
pilotage_indirect_1_cmep (16K) Problem description: In the example below, we study the effects caused by the progressive strain localization. The structure consists of a bar under uniform tension in… P:@EXCEL1,PASAPAS,PILOINDI
pilotage_indirect_1_cndi (13K) Problem description: In the example below, we study the effects caused by the progressive strain localization. The structure consists of a bar under uniform tension in… P:@EXCEL1,PASAPAS,PILOINDI
pilotage_indirect_2 (18K) Problem description: In the example below, we study the behaviour of a holed plate under tensile loading. The mesh is irregular and the load is applied at the right edge… P:@EXCEL1,PASAPAS
plaque_gurson2 (11K) Dans la note CEA DMT 96-566, le rapport de densite est deduit de l'expression lineaire de la variation de volume: trace(epsilon)=dV/V0 avec: V le volume total, V0 le… P:PASAPAS
plas13 (7K) Test Plas13.dgibi: Jeux de données COMPARAISON ETUDE AMBROIS AVEC ELEMENT GLOBAL OLARIU DEFINITION VALEURS ET ELEMENTS GRAPHIQUES MATERIAU DU TYPE POTEAU AMBROIS POTEAU… P:PASAPAS
pod_flui_cyl (32K) NOM : pod_flui_cyl DESCRIPTION : Determination de bases POD issues d'un calcul CFD d'ecoulement fluide autour d'un cylindre fixe puis projection des resultats CFD sur… P:@ARR,@HISTOGR,EXEC,LEGENDE,TABLO2D,TABLO3D
pod_pout_elas (24K) Calcul complet ? (si FAUX: test de non-regression rapide) Affichage graphique ? P:@ARR,@HISTOGR,@MOD,DYNAMIC,EXPLORER,LEGENDE,TABLO2D,TABLO3D
pointcylsph (1K) Petit test simple sur les procedures POINTCYL et POINTSPH Precision pour les comparaisons de POINTs (critere de distance) P:POINTCYL,POINTSPH
poiseuille2D (16K) NOM : poiseuille2D.dgibi DESCRIPTION : Ecoulement de poiseuille 2D classique ___________ (écoulement parallèle en conduit bidimensionnel infini) GEOMETRIE (problème… P:@POMI,EXEC
PoutreConsole_Plas_EcrouCineLine (3K) POUTRE CONSOLE EN FLEXION MATERIAU ELASTOPLASTIQUE A ECROUISSAGE CINEMATIQUE LINEAIRE P:PASAPAS
pq1-lref (15K) Cas test de non régression basé sur pq1 Pressurisation d'une enceinte type Phébus On ajoute LREF pour prise en compte convection forcée Pour lref = 0. on doit retrouver… P:EXECRXT
pq1 (13K) Cas test de non régression sur le controle des maillages Pressurisation d'une enceinte type Phébus Le maillage correspond à une enceinte cylindrique d'environ 10 m3 avec… P:EXECRXT
pq1xx (12K) Cas test de non régression sur le controle des maillages Pressurisation d'une enceinte type Phébus Le maillage correspond à une enceinte cylindrique d'environ 10 m3 avec… P:EXECRXT
precmat (13K) OPERATEUR 'KOPS' Matrice de preconditionnement écoulements bas mach divisé par le pas de temps locale. A. BECCANTINI, S. V. KUDRIAKOV, LTMF NOVEMBRE 2001
pressu (7K) Containment pressurization (Phebus size) 3D mesh of a 14.5 m3 cylindrical containment with a 10cm in depth vertical wall. Initial pressure and temperature are 1bar and… P:EXECRXT
pressu2 (7K) Containment pressurization (Phebus size) 3D mesh of a 14.5 m3 cylindrical containment with a 10cm in depth vertical wall. Initial pressure and temperature are 1bar and… P:EXECRXT
pressugQ (7K) Containment pressurization (Phebus size) 3D mesh of a 14.5 m3 cylindrical containment with a 10cm in depth vertical wall. Initial pressure and temperature are 1bar and… P:EXECRXT
pressuhx1 (12K) Containment pressurization (Phebus size) with heat losses. 3D mesh of a 14.5 m3 cylindrical containment with a 10cm in depth vertical wall. Initial pressure and… P:EXECRXT,PROCHEXT,PSATT
pressuhx2 (12K) Containment pressurization (Phebus size) with heat losses. 3D mesh of a 14.5 m3 cylindrical containment with a 10cm in depth vertical wall. Initial pressure and… P:EXECRXT,PROCHEXT,PSATT
pressupp (7K) Containment pressurization (Phebus size) 3D mesh of a 14.5 m3 cylindrical containment with a 10cm in depth vertical wall. Initial pressure and temperature are 1bar and… P:EXECRXT
pressutq (7K) Containment pressurization (Phebus size) 3D mesh of about 14.5 m3 cylindrical containment with a 100oC vertical wall. Initial pressure and temperature are 1.3bar and… P:EXECRXT
pressutq2 (7K) Containment pressurization (Phebus size) 3D mesh of about 14.5 m3 cylindrical containment with a 100oC vertical wall. Initial pressure and temperature are 1.3bar and… P:EXECRXT
pressuw (8K) Containment pressurization (Phebus size) 3D mesh of a 14.5 m3 cylindrical containment with a 10cm in depth vertical wall. Initial pressure and temperature are 1bar and… P:ACIER,EXECRXT
pret_ther (11K) APPROCHE VF "Cell-Centred Formulation" pour la solution des Equations d'Euler pour un gaz parfait. OPERATEUR PRET Operateur qui 'recontruit les variables primitives aux…
primtest3_3D (6K) APPROCHE VF "Cell-Centred Formulation" pour la solution des Equations d'Euler pour un gaz parfait OPERATEUR PRIM Cas: gaz multiespece "calorically perfect" Cas 3D A.…
proi3 (2K) NOM : PROI3 DESCRIPTION : Cas-test de la gestion des soucis et du critere de rattrapage dans PROI. LANGAGE : GIBIANE-CAST3M AUTEUR : Stephane GOUNAND…
projgril_1 (5K) Test de la procedure PROJGRIL Projection dans 2 dimensions d'un nuage representant une grille de n dimensions utilise dans le cas de l'operateur IPOL option 'GRILL' -… P:PROJGRIL
raff01 (10K) raff01.dgibi Calcul en mecanique de la rupture avec un maillage raffine par l'opérateur RAFF. d'une plaque elastique en traction en 2D déformations planes avec fissure… P:@EXCEL1,G_THETA
raff02 (27K) raff02.dgibi TEST de la procedure de raffinement en cour de calcul RAFF - PASAPAS - PROI en 3D avec plasticite un seul raffinements Calcul sur une CT comparaison avec… P:PASAPAS
raff03 (8K) raff03.dgibi Calcul en mecanique de la rupture avec un maillage raffine par l'operateur RAFF et des elements X-FEM. d'une plaque elastique en traction en 2D déformations… P:G_THETA
raff04 (7K) raff04.dgibi Calcul elasitique 3D des facteurs d'intencité de contraintes pour une fissure circulaire sous un chargempent de traction à l'infini incliné de 45 deg par… P:G_THETA
raff05 (8K) raff05.dgibi Calcul elastique 2D avec un changement de niveau de raffinement dans une zonne X-FEM Test : Raff , MODLI, FPMASS, RIGI1, RIGIX, RIGIXR, RUSRUR, RIGSUX,… P:PASAPAS
raff06 (1K) RAFF06.DGIBI Objet : Test de validation de l'operateur RAFF dans le cas du raffinement d'un LISTRELL. Description : On teste differents cas de raffinement de LISTREELs.…
Random_Set_Theory_01 (3K) RSTHS.dgibi Random Set Theory analysis with a single trivial analytic function @PB(A,B,C,D) ==> (A*B) + (C*D) P:@RSTH
Random_Set_Theory_02 (4K) RSTHM.dgibi Random Set Theory analysis with three trivial analytic functions @PA(A,B,C,D) ==> A + (B*C*D) @PB(A,B,C,D) ==> (A*B) + (C*D) @PC(A,B,C,D) ==> (A*B*D) + D P:@RSTH
Random_Set_Theory_03 (8K) RSTHF.dgibi Random Set Theory analysis with Finite Elements (RS-FEM) P:@MOD,@RSTH
recirc (4K) Exemple test : recirculation dans une cavite semi circulaire Eclt laminaire incompressible On impose une vitesse tg sur la surface libre V normale nulle sur le fond Post… P:EXEC,VNIMP
recircp (8K) GRAPH=VRAI ; 1/ Exemple test : canal courbe Eclt laminaire incompressible On impose une vitesse a un bout V normale nulle sur les parois On indique comment imposer une… P:EXEC,VNIMP
recircpp (9K) tests ajustes par PV le 12/10/08 sur les valeurs obtenues en linux32 GRAPH=VRAI ; P:EXEC,VNIMP
rela (3K) NOM : RELA DESCRIPTION : Cas-test elementaire RELA où un des maillages est un point (nouvelle syntaxe du 2019/01) LANGAGE : GIBIANE-CAST3M AUTEUR : Stephane GOUNAND…
rela_non_associee (1K) test d'utilisation d'une relation non associee on veut controler le deplacement d'un point intermediaire d'une barre en appliquant une force a l'extremite juste pour le…
rela_non_associee_2 (10K) Exemple: perforated plate under traction Several elements with MAZARS model in the middle Testing non associated condition -> Maximum damage zone opening incremental… P:PASAPAS
remp_motifs (1K) CET EXEMPLE DECLENCHE UNE ERREUR 1111 (CHAINE TROP LONGUE APRES REMPLACEMENTS) CHA6_I = 'oooooooooooooooooooooooooooooooooooooooooooooooooooo' ; CHA6_O = REMP CHA6_I 'o'…
reprise_1 (3K) Cas test d'une reprise de calcul avec PASAPAS Objectif : tester la reprise/poursuite de calcul avec PASAPAS. Il s'agit d'un calcul mecanique en elasticite lineaire avec… P:PASAPAS
rigi_ic_2d (2K) Petit test sur les elements 2D incompressibles (ICT3, ICQ4, ICT6, ICQ8) Verification du calcul de la rigidite Calculs en 2D : deformations et contraintes planes,…
rotor_laval_poutre (12K) Rotor de Laval Etude dans le repere inertiel (ou fixe) avec elements poutre de TIMO p2 kpal z=L +--/\/\/\--| | | | p1a| =======+======= Mdisc, Ixyz p1b| | | | z=0… P:@PALETTE,CAMPBELL,ORDOVIBC,POSTVIBR,RECOVIBC
satnsathoriz (20K) K0 = H0 * ALF EXP * KS ; MESS 'DHDT0' DHDT0; P:DARCYSAT,DESTRA,HT_PRO,TRACHIS
shearkei (13K) COMPLET = VRAI ; GRAPH = VRAI; P:EXEC,KEPSILON
shock2d (16K) NOM : shock2d.dgibimain2D DESCRIPTION : file to solve 2D tests: two-fluid shock tube LANGAGE : GIBIANE-CAST3M AUTEUR : Jose R. Garcia-Cascales, Universidad Politecnica…
shock3d (17K) NAME : main3d.dgibi DESCRIPTION : file to solve 3D tests: 2. shock tube LANGUAGE : GIBIANE-CAST3M AUTHOR : José R. Garcia Cascales Universidad Politecnica de Cartagena,…
sinebump (59K) CALCUL DE L'ECOULEMENT SUBSONIQUE STATIONNAIRE DANS UN CANAL AVEC SINE-SHAPED BUMP FORMULATION VF COMPRESSIBLE EXPLICITE/IMPLICIT H. PAILLERE/P. GALON TTMF AOUT 1997
sinebum_fmm (15K) SINE-SHAPED BUMP CALCUL DE L ECOULEMENT SUBSONIQUE ISENTROPIQUE STATIONNAIRE DANS UN CANAL Methode implicite sans matrice Boundary conditions imposed via ghost cells…
sinebum_fmm2 (16K) SINE-SHAPED BUMP CALCUL DE L ECOULEMENT SUBSONIQUE ISENTROPIQUE STATIONNAIRE DANS UN CANAL Methode implicite sans matrice BECCANTINI A., SFME/LTMF, MAI 2002 JANVIER…
sinebum_fmm4 (27K) SINE-SHAPED BUMP CALCUL DE L'ECOULEMENT SUBSONIQUE ISENTROPIQUE STATIONNAIRE DANS UN CANAL Methode implicite sans matrice pour les equations d'Euler (bas Mach)…
sine_bumpBM (59K) CALCUL DE L'ECOULEMENT SUBSONIQUE STATIONNAIRE DANS UN CANAL AVEC SINE-SHAPED BUMP FORMULATION VF COMPRESSIBLE EXPLICITE/IMPLICIT H. PAILLERE/P. GALON TTMF AOUT 1997
sissib_cov (23K) Test sur la procedure SISSIB, suite à la P:SISSIB
sissib_cov2 (82K) Test sur la procedure SISSIB, suite à la P:SISSIB
sol-asym+rela-unil (1K) Points ... Champ test ...
sormat (5K) NOM : SORMAT DESCRIPTION : Test basique de la sortie d'une matrice. On teste avec une matrice symétrique et une non-symétrique LANGAGE : GIBIANE-CAST3M AUTEUR : Stephane…
soudage18 (15K) donnees geometriques qu il faudrait sauver surface symetrie P:PASAPAS
soudage4 (10K) S O U D A G E 4 . D G I B I Objet : Exemple d'utilisation d'un modele de SOURCE THERMIQUE GAUSSIENNE pour la simulation d'une ligne de fusion en soudage sur une plaque… P:CHARTHER,PASAPAS
soudage5 (8K) S O U D A G E 5 . D G I B I Objet : Exemple d'utilisation d'un modele de SOURCE THERMIQUE GAUSSIENNE pour la simulation d'une ligne de fusion en soudage sur une plaque… P:PASAPAS,PECHE
soudage6 (17K) fichier soudage6.dgibi S O U D A G E 6 . D G I B I Objet : Exemple de simulation thermique du soudage d'un raidisseur sur une plaque avec apport de matiere (4 passes).… P:BOITE,PASAPAS,SOUDAGE,WAAM
soudage7 (23K) fichier soudage7.dgibi S O U D A G E 7 . D G I B I Objet : Exemple de simulation thermomecanique du soudage d'un raidisseur sur une plaque avec apport de matiere (4… P:BOITE,PASAPAS,SOUDAGE,WAAM
source1 (10K) SOURCE1.DGIBI Objet : Verfication / validation d'un modele de source de chaleur. Formulation generale (THERMIQUE SOURCE). Description : Comparaison des flux nodaux…
source2 (10K) SOURCE2.DGIBI Objet : Verfication / validation d'un modele de source de chaleur. Cas d'une SOURCE GAUSSIENNE ISOTROPE. Description : Comparaison des flux nodaux…
source3 (18K) SOURCE3.DGIBI Objet : Verfication / validation d'un modele de source de chaleur. Cas d'une SOURCE GAUSSIENNE ISOTROPE-TRANSVERSE. Description : Comparaison des flux…
spal_canalperiod (62K) NOM : spal_canalperiod.dgibi DESCRIPTION : Calcule l'écoulement turbulent d'un fluide dans un canal plan grâce au modèle de Spalart-Allmaras. Pour obtenir un régime… P:@ARR,@MOD,EXEC,SPAL
ssch (1K) test elementaire de l'operateur ssch repertoire des fichiers "divers" ext:COMPOM
stationary_discontinuity (31K) CALCUL DU TUBE A CHOC; CAS MULTIESPECE GAZ multi-especes "THERMALLY PERFECT" FORMULATION VF COMPRESSIBLE EXPLICITE Colella-Glaz, discontinuité de contact stationnaire A.…
stationary_shock (31K) CALCUL DU TUBE A CHOC; CAS MULTIESPECE GAZ mono-especes "THERMALLY PERFECT" FORMULATION VF COMPRESSIBLE EXPLICITE DIFFERENTS SOLVEURS Choc stationnaire A. BECCANTINI…
statique1 (3K) Illustration de la methode de resolution d'un equilibre mecanique par minimisation iterative du residu. On calcul la flexion simple d'une poutre au comportement elasto-…
sudden_expansion (63K) NOM : SUDDEN_EXPANSION DESCRIPTION : Ecoulement dans un tube débouchant dans un autre de plus gros diamètre en 2D plan et en 2D axisymétrique. Références :… P:@STBL,DEADUTIL,FCOURANT,ININLIN
super3 (5K) S U P E R 3 . D G I B I Objet : Exemple d'utilisation du SUPERELEMENT en thermique stationnaire sur un probleme avec conduction & convection. Resolution du probleme de…
super4 (4K) S U P E R 4 . D G I B I Objet : Exemple d'utilisation du SUPERELEMENT, option MASSE, en thermique transitoire sur un probleme avec conduction & convection. En… P:PASAPAS
tassins1 (1K) 
tc3bired (7K) test snap back dans autopilot on verifie principalement que le pilotage fonctionne correctement on peut accessoirement verifier que la liste des temps calcules n'est pas… P:PASAPAS
test-aspH (20K) KTEST: changement de phase sur gouttes vers un régime permanent - pas de gravité - pas d'injection - option COMPLET régime permanent - (rapport de Stage Antoine BOUQUET… P:EXECRXT
test-coller1 (2K) CAS TEST DE VERIFICATION DE COLLER1 ----------------------------- MAILLAGE ------------------------------ Maillage poutre P:@REPERE,COLLER1,PASAPAS
test1fpu (9K) Ce cas vise à tester la fonction de paroi intégrée dans le maillage sur l'écoulement turbulent dans un canal plan. On utilise le modèle de Buleev. - opti trace 'PSC'; P:EXEC
test1_fun_gultifr (4K) Test sur la procedure G_ULTIFR (fonction pour determiner la position de l'etat de contraint courant par rapport à la surface de capacité Test pour l'option pouteau court… P:G_ULTIFR
test2_fun_gultifr (3K) Test sur la procedure G_ULTIFR (fonction pour determiner la position de l'etat de contraint courant par rapport à la surface de capacité Test pour l'option poutre courte… P:G_ULTIFR
test3_fun_gultifr (7K) Test sur la procedure G_ULTIFR (fonction pour determiner la position de l'etat de contraint courant par rapport à la surface de capacité Test pour l'option pouteau long… P:G_ULTIFR
test4_fun_gultifr (6K) Test sur la procedure G_ULTIFR (fonction pour determiner la position de l'etat de contrainte courant par rapport à la surface de capacité Test pour l'option poutre… P:G_ULTIFR
testchamlapn (1K) Cet exemple montre et teste comment utiliser les CHAMELEMs avec l'opérateur LAPN (mais ce serait la même chose avec NS TSCA ou KONV) pour définir des propriétés…
testfis (9K) ----- GEOMETRIE ------ CHOIX DU MAILLAGE P:@FIS_3DS
testkfpt (1K) DISCR= MACRO;
testlqm (4K) Ce jdd teste les changement LINE -> QUAF -> MACRO COMPLET = VRAI ;
test_coupe (1K) Un petit cas test de l'operateur COUP Maillage
test_et (3K) NOM : test_et.dgibi DESCRIPTION : test le bon fonctionnement de l'opérateur 'ET' LANGAGE : GIBIANE-CAST3M AUTEUR : Pascal Maugis (CEA/DSM/LSCE) mail : pmaugis@cea.fr…
test_fimp_dual2DQ (5K) Ce test vérifie l'égalité discrète Div U - q = 0 ou q est la discrétisation via l'opérateur FIMP de la divergence continue. U = (u,v,w) avec u=x**2. , v=y**2. q=2(x+y)…
test_fimp_dual2DT (5K) Ce test vérifie l'égalité discrète Div U - q = 0 ou q est la discrétisation via l'opérateur FIMP de la divergence continue. U = (u,v,w) avec u=x**2. , v=y**2. q=2(x+y)…
test_fimp_dual3DQ (5K) Ce test vérifie l'égalité discrète Div U - q = 0 ou q est la discrétisation via l'opérateur FIMP de la divergence continue. U = (u,v,w) avec u=x**2. , v=y**2. , w=z**2.…
test_fimp_dual3DT (5K) Ce test vérifie l'égalité discrète Div U - q = 0 ou q est la discrétisation via l'opérateur FIMP de la divergence continue. U = (u,v,w) avec u=x**2. , v=y**2. , w=z**2.…
test_iwprd3D_sol (37K) Test pour la loi de comportement IWPR3D_SOL On considere un essai numerique cyclique en imposant un tensuer de deformation donne: eps = gam1[(ex^ez)+(ez^ex)] avec… P:GAM1,PASAPAS
test_junc_1 (282K) repertoire des fichiers "divers" $$$$ TO_DATA1 P:PSATT ext:test_junc_1.data
test_kres_lapn (17K) NOM : TEST_KRES_LAPN DESCRIPTION : Test d'options de KRES sur un laplacien - Scaling ou pas - solveurs itératifs : CG; BiCGStab, GMRES - préconditionneurs ilu0, ilut,…
test_lapn (2K) AX AY
test_norm_env (3K) ** 2D LINE
test_pres_cham (5K) Utilisation de l'operateur PRES avec un MCHAML Une comparaison est faite entre les utilisation dans PRES - d'un CHPOINT (CHAR1) - d'un MCHAML (CHAR2) Calcul mecanique… P:PASAPAS
test_repr_modl_ther (4K) Cas test : test_repr_modl_ther.dgibi Categorie : Verification en cas de changement de modele Description : plaque 2D sur laquelle on applique 2 ou 3 modeles selon etapes… P:PASAPAS
test_thermique_1D (2K) Cas test THERMIQUE 1D : test des operateurs en 1D - a completer ! 'TRACER' D1; DONNEES DU PB
Th1D-T3D-mono (48K) NOM DE FICHIER : Th1D-T3D-mono.dgibi DESCRIPTION : Modelisation thermique 3D - thermohydraulique 1D monophasique CAS TEST CORRESPONDANT AU RAPPORT… P:EXEC
thermo_meca_projection_1 (15K) Exemple de calcul thermo-mécanique avec des maillages différents pour la mécanique et la thermique Projection des champs termiques/mécaniques via PASAPAS Diffusion de la… P:PASAPAS
ther_meca_coque (2K) Exemple de calcul thermo-mécanique avec des coques On modélise une plaque trouée encastrée sur les bords et soumise à une élévation de température sur le trou. La… P:PASAPAS,RAY
thgdep1 (4K) Cas-test de calcul thermomecanique en grands deplacements, avec convergence thermique-mécanique. On teste egalement la reprise en fournissant une liste des temps… P:PASAPAS
thgdep2 (4K) Cas-test de calcul thermomecanique en grands deplacements, avec convergence thermique-mécanique. On teste egalement la reprise en prolongeant la liste des temps. Dans ce… P:PASAPAS
thm1 (18K) Cas-test du modele THERMOHYDRIQUE SCHREFLER Description : Simulation d'une structure composite constituee d'un ------------- modele THM et d'un modele THERMIQUE… P:@MATETHM,LEGENDE,PASAPAS
thme1 (5K) Test Thme1.dgibi: Jeux de données pour calcul complet mettre complet à : vrai; Calcul thermo-mécanique ( mécanique et thermique linéaire ). Utilisation de la procédure… P:PASAPAS,PECHE
th_boucle (5K) SI (EXISTE TB 'TT') ; TTTTT = TB. 'TT' . 'T_PREC' ; SINON ; TTTTT = 0. ; FINSI ; P:PASAPAS
th_non_boucle (4K) SI (EXISTE TB 'TT') ; TTTTT = TB. 'TT' . 'T_PREC' ; SINON ; TTTTT = 0. ; FINSI ; P:PASAPAS
timp_echanp (2K) cavité soumise à une différence de température fluide/paroi avec une stratification thermique initiale P:EXECRXT
TirantLAB2 (2K) CAS TEST DU 07/09/17 PROVENANCE : TEST Test Case of Cyclic Loading for liaison_acbe model on an interface element. Pr: AK & CT P:PASAPAS
tliqu (2K) CAS TEST : tliqu.dgibi Test de l'opérateur VARI TLIQUID(P,H) Les données sont un FLOTTANT, un LISTREEL ou un CHPO
tokaflu (897K) @ACBLM Procedure de changement de base. On passe de la base cartesienne locale de l'objet modelise a la base cartesienne du maillage. L' axe Y de la base locale est… P:@COUTOR1,@COUTOR2,@FRENET,@REPERE,DDFOUR,DESCOUR,DUPONT2,FORBLOC,FOR_CONT,F_S2PI,H_B,INDUCTIO,INT_COMP,IN_MINI,MAG_NLIN,POT_SCAL,POT_VECT,RESEAU,TRANSFER,TRANSIT1
topoptim_01 (1K) fichier topoptim_01.dgibi Topology optimization of a simple 2D structure subjected to a mechanical loading. Author: Guenhael Le Quilliec (LaMe - Polytech Tours) Version:… P:TOPOPTIM
topoptim_02 (1K) fichier topoptim_02.dgibi Topology optimization of a simple 2D structure subjected to a mechanical loading, with penalty factor and GSF. Author: Guenhael Le Quilliec… P:TOPOPTIM
topoptim_03 (1K) fichier topoptim_03.dgibi Topology optimization of a simple 2D structure subjected to a thermal loading. Author: Guenhael Le Quilliec (LaMe - Polytech Tours) Version:… P:TOPOPTIM
topoptim_04 (1K) fichier topoptim_04.dgibi Topology optimization of a simple 2D structure subjected to a multicase mechanical loading. Author: Guenhael Le Quilliec (LaMe - Polytech… P:TOPOPTIM
topoptim_05 (2K) fichier topoptim_05.dgibi Topology optimization of a simple 2D structure subjected to a mechanical loading, with penalty factor, GSF, a hole and an frozen area. Author:… P:TOPOPTIM
topoptim_06 (1K) fichier topoptim_06.dgibi Topology optimization of of a simple 2D structure subjected to a mechanical loading, with a symmetry restriction. Author: Guenhael Le Quilliec… P:TOPOPTIM
topoptim_07 (1K) fichier topoptim_07.dgibi Topology optimization of of a simple 2D structure subjected to a mechanical loading, with a circular periodicity restriction. Author: Guenhael… P:TOPOPTIM
topoptim_08 (2K) fichier topoptim_08.dgibi Topology optimization of a simple 2D structure subjected to a mechanical loading, with an axial periodicity restriction. Author: Guenhael Le… P:TOPOPTIM
topoptim_09 (2K) fichier topoptim_09.dgibi Topology optimization of a simple 2D structure subjected to a mechanical loading, with imposed initial topology and remeshing. Author: Guenhael… P:TOPOPTIM
topoptim_10 (2K) fichier topoptim_10.dgibi Non-linear topology optimization of a simple 2D structure in contact with a rigid sphere with prescribed displacement. Author: Guenhael Le… P:TOPOPTIM
topoptim_11 (1K) fichier topoptim_11.dgibi Topology optimization of a simple 2D compliant mechanism: inverter (maximization of the output displacements in the opposite direction to the… P:TOPOPTIM
toposurf_01 (1K) fichier toposurf_01.dgibi Extraction of the 2D smoothed surface from a simple 2D topology Author: Guenhael Le Quilliec (LaMe - Polytech Tours) Version: 3.0 2018/01/29… P:TOPOSURF
toposurf_02 (1K) fichier toposurf_02.dgibi Extraction of the 3D smoothed surface from a simple 2D topology Author: Guenhael Le Quilliec (LaMe - Polytech Tours) Version: 3.0 2018/01/29… P:TOPOSURF
toposurf_03 (1K) fichier toposurf_03.dgibi Extraction of the 3D smoothed surface from a simple 3D topology Author: Guenhael Le Quilliec (LaMe - Polytech Tours) Version: 3.0 2018/01/29… P:TOPOSURF
trac (21K) NOM : TRAC DESCRIPTION : Tester TRAC avec les QUAFs compares aux autres elements suite aux P:BOITE
traction (13K) TRACTION Objet : Simulation d'un essai de traction simple. On se donne une courbe de traction force-deplacement de reference. On simule l'essai de traction en petits et… P:PASAPAS
traction316L (4K) Essai de traction cyclique sur de l'acier 316L a 20 degC. Validation des donnees materiaux integrees dans la procedure BIBLIO. Reproduction de la courbe de traction… P:BIBLIO,PASAPAS
trac_anno (2K) DESCRIPTION DES PARTIES D'UN MAILLAGE VIA UNE LEGENDE AJOUT D'ETIQUETTES EN CERTAINS POINTS D'INTERET P:@MOD,BOITE
trac_chpoint (1K) Maillage Champs de coordonnees et trace
trainee_2d (51K) BEGINPROCEDUR calcul NOM : CALCUL DESCRIPTION : LANGAGE : GIBIANE-CAST3M AUTEUR : Stéphane GOUNAND (CEA/DEN/DM2S/SFME/LTMF) mél : gounand@semt2.smts.cea.fr VERSION : v1,… P:@POMI,@STBL,ININLIN
trainee_3d (57K) BEGINPROCEDUR calcul3d NOM : CALCUL3D DESCRIPTION : LANGAGE : GIBIANE-CAST3M AUTEUR : Stéphane GOUNAND (CEA/DEN/DM2S/SFME/LTMF) mél : gounand@semt2.smts.cea.fr VERSION :… P:@POMI,@STBL,ININLIN
trajec (14K) = HYDROCOIN 7B = Cas isotrope avec une permeabilite p1 a l'interieur d'un cercle de = rayon RAY0, et une permeabilite p2 a l'exterieur. = Les dimensions sont…
transport1 (11K) CAS TEST : transport1.dgibi TEST TRANSPORT1 CALCUL DARCY ISOTROPE TRANSPORT. Transport d'un front. dT -- + div (uT - Kgrad(T)) = 0 dt Ce test permet de vérifier le bon… P:DARCYTRA
transport1EFMH (11K) CAS TEST : transport1.dgibi TEST TRANSPORT1 CALCUL DARCY ISOTROPE TRANSPORT. Transport d'un front. dT -- + div (uT - Kgrad(T)) = 0 dt Ce test permet de vérifier le bon… P:TRANSGEN
transport1VF (11K) CAS TEST : transport1.dgibi TEST TRANSPORT1 CALCUL DARCY ISOTROPE TRANSPORT. Transport d'un front. dT -- + div (uT - Kgrad(T)) = 0 dt Ce test permet de vérifier le bon… P:TRANSGEN
transport1VF_vs_EFMH (20K) CAS TEST : transport1.dgibi TEST TRANSPORT1 CALCUL DARCY ISOTROPE TRANSPORT. Transport d'un front. dT -- + div (uT - Kgrad(T)) = 0 dt Ce test permet de verifier le bon… P:CHTITR,TRANGEOL,TRANSGEN
transport2 (27K) CAS TEST : transport2.dgibi Petit programme testant le transport en milieu poreux avec - limite de solubilité diminuant exponentiellement vers l'aval. équilibre chimique… P:DARCYTRA,DESTRA,TRACHIS,TRACHIT
transport2EFMH (25K) CAS TEST : transport2.dgibi Petit programme testant le transport en milieu poreux avec - limite de solubilité diminuant exponentiellement vers l'aval. équilibre chimique… P:DESTRA,TRACHIS,TRACHIT,TRANSGEN
transport2VF (25K) CAS TEST : transport2.dgibi Petit programme testant le transport en milieu poreux avec - limite de solubilité diminuant exponentiellement vers l'aval. équilibre chimique… P:DESTRA,TRACHIS,TRACHIT,TRANSGEN
transport3 (29K) CAS TEST : transport3.dgibi Petit programme testant le transport en milieu poreux avec - décroissance radioactive implicite - limite de solubilité (équilibre instantané)… P:DARCYTRA,DESTRA,TRACHIS,TRACHIT
transport4 (30K) CAS TEST : transport4.dgibi Petit programme testant le transport en milieu poreux avec - limite de solubilité diminuant linéairement vers l'aval. l'équilibre chimique… P:DARCYTRA,DESTRA,TRACHIS,TRACHIT
transport5 (27K) CAS TEST : transport5.dgibi Petit programme testant le transport en milieu poreux avec - dissolution du précipité imposée. - terme source - coefficient de retard… P:DARCYTRA,DESTRA,TRACHIS,TRACHIT
transport6 (29K) CAS TEST : transport6.dgibi Petit programme testant le transport en milieu poreux avec - Retard non linéaire suivant une isotherme de type Langmuir. pour un cas test 2D… P:DARCYTRA,DESTRA,TRACHIS,TRACHIT
transport6EFMH (29K) CAS TEST : transport6.dgibi Petit programme testant le transport en milieu poreux avec - Retard non linéaire suivant une isotherme de type Langmuir. pour un cas test 2D… P:DESTRA,TRACHIS,TRACHIT,TRANSGEN
transport6VF (29K) CAS TEST : transport6.dgibi Petit programme testant le transport en milieu poreux avec - Retard non linéaire suivant une isotherme de type Langmuir. pour un cas test 2D… P:DESTRA,TRACHIS,TRACHIT,TRANSGEN
transsat (12K) CAS TEST : transsat.dgibi Test de fonctionnement de DARCYSAT sur un probleme multizone. Infiltration d'eau dans une barrière ouvragée dans son site d'acceuil. -… P:@ARR,DARCYSAT,DESTRA,HT_PRO,TRACHIS
trkgpp (4K) Enceinte 2D Axisymetrique Cas de Torrance et Rockett echl=5.e-1; echl=1.e-1; P:EXECRXT
tubesrc (4K) $$$ TUBESRC Exemple TUBESRC --- 2 JUIN 1998 --- Tube cylindrique Rayon R0=0.25 Longueur L0=16*R0 test cas isotherme NS,FIMP KBBT en Implicite On teste aussi un puits de… P:EXEC
tubesrc1 (2K) $$$ TUBESRC Exemple TUBESRC1 --- 2 JUIN 1998 --- Tube cylindrique Rayon R0=0.25 Longueur L0=16*R0 test cas isotherme NS,FIMP KBBT en Implicite On teste aussi un puits de… P:EXEC
tubesrc2 (2K) Exemple TUBESRC2 --- 2 JUIN 1998 --- Tube cylindrique Rayon R0=0.25 Longueur L0=16*R0 test cas isotherme NS,FIMP KBBT en Implicite On teste aussi un puits de masse… P:EXEC
tube_multi_ther (40K) Calcul du tube a choc; CAS MULTIESPECE GAZ multi-especes "calorically perfect", avec le modele "thermally perfect" FORMULATION VF COMPRESSIBLE EXPLICITE SOLVEUR: Van…
tube_scalpass_multi (44K) Calcul du tube a choc; CAS MULTIESPECE GAZ multi-especes "calorically perfect", avec le modele "thermally perfect" FORMULATION VF COMPRESSIBLE EXPLICITE SOLVEURS: Van…
ucanal_data (24K) Ce jeux de données est associé aux jeux de données faisant référence à un profil de vitesse pour un écoulement turbulent dans un canal plan. Il a été obtenu par…
uferdx (7K) Utilisation des modules CHI1 et CHI2 avec presence de redox repertoire des fichiers "divers" ext:COMPOM
verfdg (1K) Ce test vérifie les matrices masses diagonales modèle NAVIER_STOKES
vibr15 (1K) test elementaire de VIBC syntaxe : [ A - \lambda I ] . X = 0 avec A = rigidite elementaire réelle symetrique
vortex (6K)  P:EXEC
waam0 (5K) fichier waam0.dgibi W A A M 0 . D G I B I Objet : Ce Dgibi a pour but de tester le fonctionnement des procedures : - SOUDAGE : definition d'une sequence de fabrication… P:SOUDAGE,WAAM
waam1 (14K) fichier waam1.dgibi W A A M 1 . D G I B I Objet : Exemple de simulation thermique d'un depot de matiere par WAAM. L'exemple simule la realisation d'un "mur" sur la… P:BIBLIO,PASAPAS,PECHE,RENDSOUR,SOUDAGE,WAAM
waam2 (19K) fichier waam2.dgibi W A A M 2 . D G I B I Objet : Exemple de simulation thermomecanique d'un depot de matiere WAAM. L'exemple simule la realisation d'un "mur" sur la… P:BOITE,LEGENDE,PASAPAS,SOUDAGE,WAAM
waam3 (16K) fichier waam3.dgibi W A A M 3 . D G I B I Objet : Exemple de simulation thermique d'un depot de matiere par WAAM. L'exemple simule la realisation d'un "mur" sur la… P:ADAPTE,BIBLIO,PASAPAS,PECHE,SOUDAGE,WAAM
waam4 (16K) fichier waam4.dgibi W A A M 4 . D G I B I Objet : Exemple de simulation thermique d'une fabrication additive en WAAM. L'exemple simule la realisation d'un piquage a 45… P:BIBLIO,BOITE,PASAPAS,PECHE,SOUDAGE,WAAM
waam5 (13K) fichier waam5.dgibi W A A M 5 . D G I B I Objet : Exemple issu de waam1.dgibi. Exemple de gestion d'evenements survenant au cours d'une sequence de fabrication par les… P:BIBLIO,PASAPAS,PECHE,SOUDAGE,WAAM

## Changement_De_Phase Changement_De_Phase (4)
phase_01 (6K) Cas test : phase01.dgibi Categorie : Verification & Validation (Formule Analytique) Description : plaque 2D sur laquelle on applique 3 modeles 1- Diffusion de la chaleur… P:PASAPAS
phase_02 (4K) Cas test : phase2d.dgibi barreau ayant une temperature variant de 0 à 250 jusqu'a son milieu puis de 250 à 0°C à son extremité. On suppose une température de fusion à… P:PASAPAS,PECHE
phase_03 (3K) Cas test : phase2d_02.dgibi Type : Verification & Validation analytique Barreau ayant un materiau constant et un changement de phase a 100°C Il est chauffe uniformement… P:PASAPAS
solubilite_01 (5K) Cas test : solubilite_01.dgibi Categorie : Verification Description : Teste le MODELE 'CHANGEMENT_PHASE' 'SOLUBILITE' developpe en 2021 Plaque 2D constituee de 2… P:PASAPAS

## Chimie Combustion (16)
cube_CJDF3D (33K) APPROCHE VF "Cell-Centred Formulation" pour la combustion. MODELE RDEM OPERATEURS 'PRIM', PRET, KONV PROPAGATION D'UNE DEFLAGRATION DANS UN CUBE We check some symmetry…
flamarrh (11K) OPERATEUR FLAM Combustion Hydrogene-Oxygene, cinetique de type Arrhenius A. BECCANTINI DRN/DMT/SEMT/LTMF FEVRIER 1999
flamcat (23K)  P:EXEC,FILTREKE
flamcrebcom (2K) OPERATEUR FLAM Critere CREBCOM A. BECCANTINI DEN/DM2S/SFME/LTMF JUIN 2001
flamcrebcom2 (8K) OPERATEUR 'FLAM' Modele 'CREBCOM2' A. BECCANTINI DM2S/SFME/LTMF NOVEMBER 2001
flamhms (13K) COMBUSTION EN REGIME LAMINAIRE - MODELE TRAVIS ON TESTE LES VALEURS DE PRESSION ET DE TEMPERATURE AICC P:EXEC
rdem_surf1Daxi (31K) APPROCHE VF "Cell-Centred Formulation" pour la combustion. MODELE RDEM OPERATEURS 'PRIM', PRET, KONV PROPAGATION D'UNE FLAMME DANS UN TUBE We verify that S_flame =…
rut_tg_1 (41K) CAS-TEST RUT Date de
rut_tg_2 (41K) CAS-TEST RUT Date de
tube1D_deto_C2H2 (45K) APPROCHE VF "Cell-Centred Formulation" pour la combustion. MODELE RDEM OPERATEURS 'PRIM', PRET, KONV PROPAGATION D'UNE CJDT DANS UN TUBE Cas de l'acetylene A.…
tubedeto2d1 (23K) PROPAGATION D UNE DETONATION DANS UN TUBE MODELE CREBCOM A. BECCANTINI, SFME/LTMF, 15.01.02 The file is divided into 5 parts 1) mesh 2) initial conditions and gas…
tubedeto2d2 (20K) PROPAGATION D UNE DETONATION DANS UN TUBE MODELE COMBUSTION H2-air de PLEXUS A. BECCANTINI, SFME/LTMF, 15.01.02 The file is divided into 5 parts 1) mesh 2) initial…
tubedeto3d1 (25K) PROPAGATION D UNE DETONATION DANS UN TUBE MODELE CREBCOM A. BECCANTINI, SFME/LTMF, 15.01.02 The file is divided into 5 parts 1) mesh 2) initial conditions and gas…
tubedeto3d2 (21K) PROPAGATION D UNE DETONATION DANS UN TUBE MODELE COMBUSTION H2-air de PLEXUS A. BECCANTINI, SFME/LTMF, 15.01.02 The file is divided into 5 parts 1) mesh 2) initial…
tube_CJDF (58K) APPROCHE VF "Cell-Centred Formulation" pour la combustion. MODELE RDEM OPERATEURS 'PRIM', PRET, KONV PROPAGATION D'UNE CJDF DANS UN TUBE A. BECCANTINI, SFME/LTMF,…
tube_CJDF3D (58K) APPROCHE VF "Cell-Centred Formulation" pour la combustion. MODELE RDEM OPERATEURS 'PRIM', PRET, KONV PROPAGATION D'UNE CJDF DANS UN TUBE Cas 3D. A. BECCANTINI,…

## Chimie Melange (5)
deto (3K) Validation de l'opérateur DETO : Comparaison de la pression, de la température et de la vitesse de Chapman-Jouguet pour deux mélanges H2/O2/N2 entre des données…
solsoltest (16K) UTILISATION DES OPERATEURS CHI1 ET CHI2 EN PRESENCE DE SOLUTIONS SOLIDES repertoire des fichiers "divers" ext:COMPSM
test_met (5K) Tracé des courbes (T;pA) en fonction de V Mettre GRAPH a VRAI si trace en interactif, sinon trace en Postscript
trkg (4K) Enceinte 2D Axisymetrique Cas de Torrance et Rockett echl=5.e-1; echl=1.e-1; P:EXECRXT
trkg2 (5K) Enceinte 2D Axisymetrique Cas de Torrance et Rockett GRAPH = VRAI ; P:EXECRXT

## Diffusion Advection (3)
adve_04 (4K) Cas-test de l'operateur ADVEction dans la formulation DIFFUSION Comparaison a une solution analytique. On calcule la concentration d'un fluide qui s'ecoule dans un tuyau…
adve_05 (2K) Cas-test de l'operateur ADVEction dans la formulation DIFFUSION Ce cas-test verifie que le produit de la rigidite d'advection avec un champ de concentration : v.gradC…
adve_06 (2K) Cas-test de l'operateur ADVEction dans la formulation DIFFUSION On resout : v.gradC = 4, Avec : vx=1, vy=1 on a : dC/dx + dC/dy = 4 De + : C(1,0)=0, C(0,1)=0 Sur 1…

## Diffusion Fick (6)
diffu1 (7K) diffu1.dgibi : exemple d'utilisation du modele de DIFFUSION (FICK) On modelise la diffusion simulatee de 2 especes (C6, C8) dans un massif semi-infini en imposant leur… P:PASAPAS
diffu2 (9K) diffu2.dgibi : exemple d'utilisation du modele de DIFFUSION (FICK) Diffusion COUPLEE de deux especes (C6 / C8) On modelise la diffusion simulatee de 2 especes (C6, C8)… P:PASAPAS
diffu3 (8K) diffu3.dgibi : exemple d'utilisation du modele de DIFFUSION (FICK) On modelise la diffusion simulatee de 2 especes (C6, C8) dans un massif semi-infini en imposant leur… P:PASAPAS
diffu4 (7K) Ce Cas-Test Vérifie le bon fonctionnement du modele de DIFFUSION dans les éléments finis suivants : COQ3,COQ4,COQ6,COQ8,MASSIFS(3D) - MODE - MATE - COND - BLOQ - CAPA Le…
diffusion_sous_contraintes_01 (4K) CAS TEST diffusion_sous_contraintes_01.dgibi NOTA : Ce cas-test ne valide aucun resultat analytique Il permet d'enrichir la base des cas-tests pour les utilisateurs Il… P:CHARTHER,PASAPAS
Oxydation_Chimique_01 (13K) JEU DE DONNEES : DESCRIPTION : - Simule la diffusion chimique d'une espece conduisant a la formation d'une couche d'oxyde L'espece diffuse a travers l'oxyde et passe… P:CHARTHER,PASAPAS

## Diffusion Soret (15)
soret_1 (3K) CAS TEST soret_1.dgibi test effet Soret sur un disque plan avec trou central en modéle axisymetrique le potentiel agissant sur la concentration donne un gradient radial…
soret_10 (4K) CAS TEST soret_10.dgibi Test effet Soret - 2D AXIS - ELEMENTS FINIS TESTES : 'QUA8' - Regime permanent - C(R0) = C0 - C(R1) = C1 - GRAD(T) choisi en 1/R (T=A*ln(|R|) ==>…
soret_11 (4K) CAS TEST soret_11.dgibi Test effet Soret - 3D TRID - ELEMENTS FINIS TESTES : 'TET4' - Regime permanent - C(Z0) = C0 - C(Z1) = C1 - GRAD(T) choisi lineaire (T=A*(Z**2) /…
soret_12 (4K) CAS TEST soret_13.dgibi Test effet Soret - 3D TRID - ELEMENTS FINIS TESTES : 'PRI6' - Regime permanent - C(Z0) = C0 - C(Z1) = C1 - GRAD(T) choisi lineaire (T=A*(Z**2) /…
soret_13 (4K) CAS TEST soret_13.dgibi Test effet Soret - 3D TRID - ELEMENTS FINIS TESTES : 'PR15' - Regime permanent - C(Z0) = C0 - C(Z1) = C1 - GRAD(T) choisi lineaire (T=A*(Z**2) /…
soret_14 (4K) CAS TEST soret_14.dgibi Test effet Soret - 3D TRID - ELEMENTS FINIS TESTES : 'CUB8' - Regime permanent - C(Z0) = C0 - C(Z1) = C1 - GRAD(T) choisi lineaire (T=A*(Z**2) /…
soret_15 (4K) CAS TEST soret_15.dgibi Test effet Soret - 3D TRID - ELEMENTS FINIS TESTES : 'CU20' - Regime permanent - C(Z0) = C0 - C(Z1) = C1 - GRAD(T) choisi lineaire (T=A*(Z**2) /…
soret_2 (4K) CAS TEST soret_2.dgibi Test effet Soret - 2D PLAN - ELEMENTS FINIS TESTES : 'QUA8' - Regime permanent - C(X0) = C0 - C(X1) = C1 - GRAD(T) choisi constant (T=GT*X ==>…
soret_3 (4K) CAS TEST soret_3.dgibi Test effet Soret - 2D PLAN - ELEMENTS FINIS TESTES : 'QUA4' - Regime permanent - C(X0) = C0 - C(X1) = C1 - GRAD(T) choisi lineaire (T=A*(X**2) /…
soret_4 (4K) CAS TEST soret_4.dgibi Test effet Soret - 2D PLAN - ELEMENTS FINIS TESTES : 'QUA8' - Regime permanent - C(X0) = C0 - C(X1) = C1 - GRAD(T) choisi lineaire (T=A*(X**2) /…
soret_5 (4K) CAS TEST soret_5.dgibi Test effet Soret - 2D PLAN - ELEMENTS FINIS TESTES : 'TRI3' - Regime permanent - C(X0) = C0 - C(X1) = C1 - GRAD(T) choisi lineaire (T=A*(X**2) /…
soret_6 (4K) CAS TEST soret_6.dgibi Test effet Soret - 2D PLAN - ELEMENTS FINIS TESTES : 'TRI6' - Regime permanent - C(X0) = C0 - C(X1) = C1 - GRAD(T) choisi lineaire (T=A*(X**2) /…
soret_7 (4K) CAS TEST soret_7.dgibi Test effet Soret - 2D AXIS - ELEMENTS FINIS TESTES : 'TRI3' - Regime permanent - C(R0) = C0 - C(R1) = C1 - GRAD(T) choisi en 1/R (T=A*ln(|R|) ==>…
soret_8 (4K) CAS TEST soret_8.dgibi Test effet Soret - 2D AXIS - ELEMENTS FINIS TESTES : 'TRI6' - Regime permanent - C(R0) = C0 - C(R1) = C1 - GRAD(T) choisi en 1/R (T=A*ln(|R|) ==>…
soret_9 (4K) CAS TEST soret_9.dgibi Test effet Soret - 2D AXIS - ELEMENTS FINIS TESTES : 'QUA4' - Regime permanent - C(R0) = C0 - C(R1) = C1 - GRAD(T) choisi en 1/R (T=A*ln(|R|) ==>…

## Entree-Sortie (2)
lire_CSV_entete (1K) TEST DE LECTURE DE FICHIERS CSV AVEC EN-TETE ON A MIS EXPRES : - 2 LIGNES BIDONS AU DEBUT DU FICHIER POUR VERIFIER L'OPTION 'DEBU' - DES VIRGULES A LA PLACE DU POINT A… ext:lire_csv.csv
lire_CSV_espaces (1K) TEST DE LECTURE DE FICHIERS CSV AVEC COMME SEPARATEUR ' ' ON A MIS EXPRES DES ' ' SUPPLEMENTAIRES EN DEBUT ET FIN DE CERTAINES LIGNES AINSI QU'ENTRE CERTAINES VALEURS… ext:lire_csv_espaces.csv

## Entree-Sortie Entree-Sortie (16)
acqulata (34K) NOM : ACQULATA DESCRIPTION : Lecture de fichiers au format LATA v2.1 (Trio_U) en GIBI On utilise ACQU BRUT et d'autres évolutions (fiches 7922-7928) LANGAGE :… P:JEU
elements_vtk (2K) repertoire des fichiers "divers"
exis_01 (2K) Test exis_01.dgibi: Jeux de données Presentation : Test de la 1ere syntaxe de EXIS : LOG1 ='EXIS' Nom(*'TYPE') LOG1 ='EXIS' Nom(*'FICHIER') Verification & Validation Les…
exte (1K) NOM : EXTE DESCRIPTION : Teste l'operateur EXTE (Non portable...) LANGAGE : GIBIANE-CAST3M AUTEUR : CB215821 (CEA/DEN/DM2S/SEMT/LM2S) mel : clement.berthinier@cea.fr…
lireproc1 (4K) CAS-TEST DE LA DIRECTIVE : LIRE 'PROC' TESTS POUR LE FICHIER "MAPROC1" P:PASAPAS ext:MAPROC3,MAPROC2,MAPROC1
lire_fem (4K) PRESENTATION Ce cas-test permet de LIRE des MAILLAGES au format FEM - Generated by HyperMesh Version : 12.0 13.0 14.0 - Generated using HyperMesh-Optistruct Template… ext:Unitaire.fem,Unitaire_v14.fem,Unitaire_long.fem,Unitaire_long_v14.fem
lire_med_01 (9K) Presentation : Ce cas-test permet de 'LIRE' des fichiers au format MED fournis par le LGLS pour validation - v3.0.7 - v3.2.1 Ameliorations a prevoir : - 'LIRE' les… ext:Mesh_sphere_h_quad_arc.med,Mesh_structelem.med,Mesh_plan_3D.med,Mesh_2D_biquadratic_arc.med,Mesh_mechanic_tetra.med,Mesh_2D_quadratic_arc.med,ForMEDReader10.med,Mesh_pyramids_quadratic.med,Mesh_mechanic_t_quad_arc.med,ForMEDReader33.med,Mesh_mechanic_t_quad.med,ForMEDReader17.med,ForMEDReader29.med,Mesh_sphere_hexa.med,Mesh_2D_quadratic.med,ForMEDReader13.med,ForMEDReader25.med,testNodeFieldOnPart.med,ForMEDReader11.med,Mesh_pyramids.med,testNodeFieldOnAll.med,Mesh_sphere_h_quad_arc.med,Mesh_structelem.med,Mesh_plan_3D.med,Mesh_2D_biquadratic_arc.med,Mesh_mechanic_tetra.med,Mesh_2D_quadratic_arc.med,Mesh_pyramids_quadratic.med,Mesh_mechanic_t_quad_arc.med,Mesh_mechanic_t_quad.med,Mesh_sphere_hexa.med,Mesh_2D_quadratic.med,testNodeFieldOnPart.med,Mesh_pyramids.med,testNodeFieldOnAll.med
lire_med_02 (17K) Presentation : Ce cas-test permet de : SORTIR des MAILLAGES, CHPOINT, MCHAML et TABLE PASAPAS au format MED LIRE les fichiers MED generes VERIFIE et VALIDE les echanges… P:PASAPAS ext:nastran_long.nas
lire_nas (3K) PRESENTATION Ce cas-test permet de LIRE des MAILLAGES au format NASTRAN - En simple et double precision Ameliorations a prevoir : - Changement de repere pour les FORCES… ext:nastran_long.nas,nastran_simple.nas
lire_STL (3K) Test lire_STL.dgibi: Jeux de données Presentation : Ce cas-test permet de lire des MAILLAGES de 'TRI3' au format 'STL'. Le resultat est un objet de type TABLE. Chaque… ext:Thenatarius.stl,Multi_Solid.stl,Bear_Voronoi_fine.stl
Petit_Exemple (11K) NOM : EXTE DESCRIPTION : Teste l'operateur EXTE (Non portable...) LANGAGE : GIBIANE-CAST3M
soravs (2K) Test du fonctionnement de la directive SORT 'AVS' et de l'opérateur LIRE 'AVS'. On effectue les deux opérations et on vérifie que le CHPOINT lu est égal à celui qui a…
sort_MAILLAGE (3K) Test sort_MAILLAGE.dgibi: Jeux de données TEST sort_MAILLAGE.dgibi Sortie d'un MAILLAGE avec SORT Relecture avec LIRE (Option non testee a-priori) Cas-Test de…
sort_nas (1K) Test sort_nas.dgibi: Jeux de données SI GRAPH = N PAS DE GRAPHIQUE AFFICHE SINON SI GRAPH DIFFERENT DE N TOUS LES GRAPHIQUES SONT AFFICHES ext:nastran_long.nas
tasse (1K) Test tasse.dgibi: Jeux de données Presentation : Ce cas-test de verification permet de lire un fichier au format 'STL' representant une tasse avec le logo Cast3M dessus. ext:tasse.stl
testfer (3K) Test testfer.dgibi: jeux de données Toit cylindrique soumis à son propre poids affichage

## Fluides Ale (2)
centrif (17K) Date : 19/3/97 Version 1 Objet : Le but de ce test est de valider la mise en place sous CASTEM 2000 de calculs en "vrai axi-symétrique", c'est à dire pour lesquels la… P:EXEC
tube_GFMP (208K) SHOCK TUBE GFMP Liquid-water test case A. BECCANTINI, SFME/LTMF, 05.11.10 See Luo, Baum, Lohner. On the computation of multi-material ﬂows using ALE formulation. JCP 194… P:GAM1

## Fluides Convection (9)
allee (8K)  P:EXEC
BINGHAMp (5K) Fluide de BINGHAM : Ecoulement de POISEUILLE Comparaison à une solution analytique CANAL LONGUEUR 10. LARGEUR 4. Algorithme implicite (dans ce cas beaucoup plus rapide)… P:EXEC
burgerC (6K) EQUATION DE CONVECTION NON-LINEAIRE Ut + div (F(U)) = 0 TSCAL OPTION CONS (conservatif) SUPGDC (par défaut) PROCEDURE POUR TRACER COUPES P:EXEC
burgerNC (6K) EQUATION DE CONVECTION NON-LINEAIRE Ut + div (F(U)) = 0 RESOLUE SOUS FORME NON-CONSERVATIVE dU/dt + lambda . nabla U = 0 avec lambda = dF/dU AVEC OPTION SUPGDC (par… P:EXEC
burgerpsi (8K) EQUATION DE CONVECTION NON-LINEAIRE Ut + div (F(U)) = 0 RESOLUE SOUS FORME NON-CONSERVATIVE dU/dt + lambda . nabla U = 0 avec lambda = dF/dU AVEC L'OPTION PSI (POSITIVE… P:EXEC
cvry-2D-1 (11K) CONVECTION-RAYONNEMENT ************************* Couplage convection naturelle laminaire/rayonnement milieu absorbant Il s'agit du test de De Vahl&Davis -cavité carrée-… P:EXEC
tp4 (17K)  P:EXEC
tubturb (12K)  P:EXEC,FILTREKE,RAY
villers_platten (25K) NOM : villers_platten.dgibi DESCRIPTION : fiche de validation CASTEM2000 Mécanique des Fluides Convection naturelle laminaire + convection thermocapillaire (Marangoni)… P:@POMI,BOITE,EXEC,EXIC

## Fluides Darcy (95)
darcy1 (17K) CAS TEST : darcy1.dgibi TEST DARCY1 CALCUL DARCY ISOTROPE Résolution par une méthode d'éléments finis mixtes hybrides. Ce test permet de vérifier le bon fonctionnement…
darcy2 (10K) CAS TEST : darcy2.dgibi TEST DARCY2 CALCUL DARCY ORTHOTROPE Résolution par une méthode d'éléments finis mixtes hybrides. Ce test permet de vérifier le bon fonctionnement…
darcy3 (12K) CAS TEST : darcy3.dgibi TEST DARCY3 CALCUL DARCY ORTHOTROPE 3D Résolution par une méthode d'éléments finis mixtes hybrides. Ce test permet de vérifier le bon…
darcy3EFMH (10K) CAS TEST : darcy3.dgibi TEST DARCY3 CALCUL DARCY ORTHOTROPE 3D TEST TRANGEOL en EFMH staionnaire comme limite d'un transitoire On effectue trois calculs sur un cube,… P:TRANGEOL
darcy3VF (10K) CAS TEST : darcy3.dgibi TEST DARCY3 CALCUL DARCY ORTHOTROPE 3D TEST de TRANGEOL en VF On effectue trois calculs sur un cube, maillé par des cubes réguliers. Les… P:TRANGEOL
darcy3_hexaedre_EFMH (15K) CAS TEST : darcy3.dgibi TEST DARCY3 CALCUL DARCY ORTHOTROPE 3D Résolution par une méthode d'éléments finis mixtes hybrides. Ce test permet de vérifier le bon… P:TRANGEOL
darcy3_hexaedre_VF (14K) CAS TEST : darcy3.dgibi TEST DARCY3 CALCUL DARCY ORTHOTROPE 3D Résolution par une méthode d'éléments finis mixtes hybrides. Ce test permet de vérifier le bon… P:TRANGEOL
darcy3_prisme_EFMH (15K) CAS TEST : darcy3.dgibi TEST DARCY3 CALCUL DARCY ORTHOTROPE 3D Résolution par une méthode d'éléments finis mixtes hybrides. Ce test permet de vérifier le bon… P:TRANGEOL
darcy3_prisme_VF (14K) CAS TEST : darcy3.dgibi TEST DARCY3 CALCUL DARCY ORTHOTROPE 3D Résolution par une méthode d'éléments finis mixtes hybrides. Ce test permet de vérifier le bon… P:TRANGEOL
darcy3_pyra_VF (14K) CAS TEST : darcy3.dgibi TEST DARCY3 CALCUL DARCY ORTHOTROPE 3D Résolution par une méthode d'éléments finis mixtes hybrides. Ce test permet de vérifier le bon… P:TRANGEOL
darcy3_tetraedre_EFMH (15K) CAS TEST : darcy3.dgibi TEST DARCY3 CALCUL DARCY ORTHOTROPE 3D R�solution par une m�thode d'�l�ments finis mixtes hybrides. Ce test permet de v�rifier le bon… P:TRANGEOL
darcy3_tetraedre_VF (14K) CAS TEST : darcy3.dgibi TEST DARCY3 CALCUL DARCY ORTHOTROPE 3D Résolution par une méthode d'éléments finis mixtes hybrides. Ce test permet de vérifier le bon… P:TRANGEOL
darcy4 (22K) CAS TEST : darcy4.dgibi TEST DARCY4 CALCUL DARCY ISOTROPE TRANSITOIRE AVEC TERME SOURCE Résolution par une méthode d'éléments finis mixtes hybrides. Ce test permet de… P:DARCYTRA
darcy5 (7K) CAS TEST : darcy5.dgibi GRAPH = VRAI ;
darcy6 (17K) CAS TEST : darcy1.dgibi TEST DARCY1 CALCUL DARCY ISOTROPE Résolution par une méthode d'éléments finis mixtes hybrides. Ce test permet de vérifier le bon fonctionnement…
darcy7 (12K) CAS TEST : darcy3.dgibi TEST DARCY3 CALCUL DARCY ORTHOTROPE 3D Résolution par une méthode d'éléments finis mixtes hybrides. Ce test permet de vérifier le bon…
darcy8 (22K) CAS TEST : darcy4.dgibi TEST DARCY4 CALCUL DARCY ISOTROPE TRANSITOIRE AVEC TERME SOURCE Résolution par une méthode d'éléments finis mixtes hybrides. Ce test permet de… P:DARCYTRA
darcy9 (12K) CAS TEST : darcy1.dgibi TEST DARCY9 C'est une reprise de DARCY1 avec utilisation de conditions aux limites d'inégalité - 1 premier calcul comme DARCY1 pour vérifier que…
decroissanceEFMH (6K) On test en 0D la décroissance radioactive en partant d'une concentration initiale T0 (unité). FLux nul aux bords du domaine. Plusieurs mailles car cela ne coute rien… P:TRANSGEN
decroissanceVF (6K) On test en 0D la décroissance radioactive en partant d'une concentration initiale T0 (unité). FLux nul aux bords du domaine. Plusieurs mailles car cela ne coute rien… P:TRANSGEN
gacul (9K) CAS TEST : gacul.dgibi Test de fonctionnement de DARCYSAT en 2D avec effet de gravite Infiltration d'eau dans une colonne verticale de sable uniformément désaturé. -… P:DARCYSAT,DESTRA,HT_PRO,TRACHIS
gaculVF (9K) CAS TEST : gacul.dgibi Test de fonctionnement de DARCYSAT en 2D avec effet de gravite Infiltration d'eau dans une colonne verticale de sable uniformément désaturé. -… P:DARCYSAT,DESTRA,HT_PRO,TRACHIS
konv_impl3D (39K) APPROCHE VF "Cell-Centred Formulation" pour la solution des Equations d'Euler pour un gaz parfait OPERATEURS PRIM, PRET, KONV Implicit: calcul du jacobien du residu Cas…
konv_impl3D1 (39K) APPROCHE VF "Cell-Centred Formulation" pour la solution des Equations d'Euler pour un gaz parfait OPERATEURS PRIM, PRET, KONV Implicit: calcul du jacobien du residu Cas…
konv_impl3Dbm (52K) APPROCHE VF "Cell-Centred Formulation" pour la solution des Equations d'Euler pour un gaz parfait OPERATEURS PRIM, PRET, KONV Implicit: calcul du jacobien du residu Cas…
konv_implbm (35K) APPROCHE VF "Cell-Centred Formulation" pour la solution des Equations d'Euler pour un gaz parfait OPERATEURS PRIM, PRET, KONV Implicit: calcul du jacobien du residu Cas…
konv_impl_centre (23K) APPROCHE VF "Cell-Centred Formulation" pour la solution des Equations d'Euler pour un gaz parfait OPERATEURS PRIM, PRET, KONV Implicit: calcul du jacobien du residu Cas…
konv_impl_centre2 (23K) APPROCHE VF "Cell-Centred Formulation" pour la solution des Equations d'Euler pour un gaz parfait OPERATEURS PRIM, PRET, KONV Implicit: calcul du jacobien du residu Cas…
konv_impl_murs (14K) APPROCHE VF "Cell-Centred Formulation" pour la solution des Equations d'Euler pour un gaz parfait OPERATEURS PRIM, PRET, KONV Implicit: calcul du jacobien du residu Cas…
konv_resi_dem3D_constant_state (25K) APPROCHE VF "Cell-Centred Formulation" pour la solution des Equations d'Euler pour un gaz parfait Approche DEM pour la combustion OPERATEURS PRET, KONV 3D Consistency…
konv_resi_dem3D_stationaryshock_12 (23K) APPROCHE VF "Cell-Centred Formulation" pour la solution des Equations d'Euler pour un gaz parfait Approche DEM pour la combustion OPERATEURS PRET, KONV 3D Stationary…
konv_resi_dem3D_stationaryshock_21 (23K) APPROCHE VF "Cell-Centred Formulation" pour la solution des Equations d'Euler pour un gaz parfait Approche DEM pour la combustion OPERATEURS PRET, KONV 3D Stationary…
konv_resi_dem_constant_state_11 (18K) APPROCHE VF "Cell-Centred Formulation" pour la solution des Equations d'Euler pour un gaz parfait Approche DEM pour la combustion OPERATEURS PRET, KONV Consistency Left…
konv_resi_dem_contact_discontinuty_11 (18K) APPROCHE VF "Cell-Centred Formulation" pour la solution des Equations d'Euler pour un gaz parfait Approche DEM pour la combustion OPERATEURS PRET, KONV Consistency in…
konv_resi_dem_contact_discontinuty_22 (19K) APPROCHE VF "Cell-Centred Formulation" pour la solution des Equations d'Euler pour un gaz parfait Approche DEM pour la combustion OPERATEURS PRET, KONV Consistency in…
konv_resi_dem_shocktube_12 (19K) APPROCHE VF "Cell-Centred Formulation" pour la solution des Equations d'Euler pour un gaz parfait Approche DEM pour la combustion OPERATEURS PRET, KONV We verify the…
konv_resi_dem_shocktube_21 (19K) APPROCHE VF "Cell-Centred Formulation" pour la solution des Equations d'Euler pour un gaz parfait Approche DEM pour la combustion OPERATEURS PRET, KONV We verify the…
konv_resi_dem_stationaryshock_12 (21K) APPROCHE VF "Cell-Centred Formulation" pour la solution des Equations d'Euler pour un gaz parfait Approche DEM pour la combustion OPERATEURS PRET, KONV Consistency in…
konv_resi_dem_stationaryshock_21 (20K) APPROCHE VF "Cell-Centred Formulation" pour la solution des Equations d'Euler pour un gaz parfait Approche DEM pour la combustion OPERATEURS PRET, KONV Consistency in…
konv_resi_gfmp_consist (13K) APPROCHE VF "Cell-Centred Formulation" pour la solution des Equations d'Euler pour un gaz parfait Approche GFMP OPERATEURS 'PRIM', PRET, KONV Consistency Methodes:…
konv_resi_ther_cons (12K) APPROCHE VF "Cell-Centred Formulation" pour la solution des Equations d'Euler pour un gaz parfait OPERATEURS PRET, KONV Cas gaz monoespece "thermally perfect"…
konv_resi_ther_cons2 (15K) APPROCHE VF "Cell-Centred Formulation" pour la solution des Equations d'Euler pour un gaz parfait OPERATEURS PRET, KONV Cas gaz multi-especes "thermally perfect"…
konv_scal_cons (5K) APPROCHE VF "Cell-Centred Formulation" pour le transport des scalaires OPERATEURS PRET, KONV Consistence A. BECCANTINI DM2S/SFME NOVEMBRE 2001
konv_scal_cons3d (5K) APPROCHE VF "Cell-Centred Formulation" pour le transport des scalaires OPERATEURS PRET, KONV Consistence A. BECCANTINI DM2S/SFME NOVEMBRE 2001
konv_scal_impl (10K) APPROCHE VF "Cell-Centred Formulation" pour le transport des scalaires OPERATEURS PRET, KONV Implicit: calcul du jacobien du residu Methodes: UPWIND, CENTERED A.…
konv_scal_impl3d (11K) APPROCHE VF "Cell-Centred Formulation" pour le transport des scalaires OPERATEURS PRET, KONV Implicit: calcul du jacobien du residu Methodes: UPWIND, CENTERED A.…
konv_ther_cons (12K) APPROCHE VF "Cell-Centred Formulation" pour la solution des Equations d'Euler pour un gaz parfait OPERATEURS PRET, KONV Cas gaz monoespece "thermally perfect" Transport…
konv_ther_cons2 (12K) APPROCHE VF "Cell-Centred Formulation" pour la solution des Equations d'Euler pour un gaz parfait OPERATEURS PRET, KONV Cas gaz multi-especes "thermally perfect"…
konv_ther_cons3 (7K) APPROCHE VF "Cell-Centred Formulation" pour la solution des Equations d'Euler pour un gaz parfait OPERATEURS PRET, KONV Cas gaz monoespece "calorically perfect" Modele…
konv_ther_sup (7K) APPROCHE VF "Cell-Centred Formulation" pour la solution des Equations d'Euler pour un gaz parfait OPERATEURS PRET, KONV Cas gaz monoespece "thermally perfect"…
lapn_impl (33K) APPROCHE VF "Cell-Centred Formulation" pour la solution des Equations d'Euler pour un gaz parfait OPERATEURS PRIM, PENT, LAPN Implicit: calcul du jacobien du residu Cas…
lapn_impl3D (60K) APPROCHE VF "Cell-Centered Formulation" pour la solution des Equations d'Euler pour un gaz parfait OPERATEURS PRIM, PRET, LAPN Implicit: calcul du jacobien du residu Cas…
lapn_impl_centre (30K) APPROCHE VF "Cell-Centred Formulation" pour la solution des Equations d'Euler pour un gaz parfait OPERATEURS PRIM, PENT, LAPN Implicit: calcul du jacobien du residu Cas…
precipite1EFMH (9K) CAS TEST : transport1.dgibi TEST TRANSPORT1 uniquement de la précipitation cinétique ordre 1 tout uniforme - pas de vitesse revient à resoudre Rw dC/dt = codis w (limsol… P:TRANSGEN
precipite1VF (9K) CAS TEST : transport1.dgibi TEST TRANSPORT1 uniquement de la précipitation cinétique ordre 1 tout uniforme - pas de vitesse revient à resoudre Rw dC/dt = codis w (limsol… P:TRANSGEN
precipite4EFMH (10K) CAS TEST : precipite4.dgibi TEST PRECIPITE4 precipité uniforme initial de 1 (par unité de volume solide) partout. vitesse vx = 1 vy = 0 uniforme maillage 2D pseudo 1D.… P:TRANSGEN
precipite4VF (10K) CAS TEST : precipite4.dgibi TEST PRECIPITE4 precipité uniforme initial de 1 (par unité de volume solide) partout. vitesse vx = 1 vy = 0 uniforme maillage 2D pseudo 1D.… P:TRANSGEN
pret1 (19K) APPROCHE VF "Cell-Centred Formulation" pour la solution des Equations d'Euler pour un gaz parfait. OPERATEUR PRET Operateur qui 'recontruit les variables primitives aux…
pret2 (16K) APPROCHE VF "Cell-Centred Formulation" pour la solution des Equations d'Euler pour un gaz parfait. OPERATEUR PRET Operateur qui 'recontruit les variables primitives aux… P:GAM1
pret3D1 (22K) APPROCHE VF "Cell-Centred Formulation" pour la solution des Equations d'Euler pour un gaz parfait. OPERATEUR PRET Operateur qui 'recontruit les variables primitives aux…
pret3D2 (17K) APPROCHE VF "Cell-Centred Formulation" pour la solution des Equations d'Euler pour un gaz parfait. OPERATEUR PRET Operateur qui 'recontruit les variables primitives aux… P:GAM1
pret3D_dem (37K) APPROCHE VF "Cell-Centred Formulation" pour la solution des Equations d'Euler pour un gaz parfait. "Discrete Equation Method". OPERATEUR PRET Operateur qui 'recontruit…
pret_dem (29K) APPROCHE VF "Cell-Centred Formulation" pour la solution des Equations d'Euler pour un gaz parfait. "Discrete Equation Method". OPERATEUR PRET Operateur qui 'recontruit…
pret_gfmp (19K) APPROCHE VF "Cell-Centred Formulation" pour la solution des Equations d'Euler. "Ghost Fluid Method for the Poor" OPERATEUR PRET Operateur qui 'recontruit les variables…
pret_scal1 (3K) APPROCHE VF OPERATEUR PRET Operateur qui reconstruit les variables primitives aux faces A. BECCANTINI SFME/LTMF NOVEMBRE 01
pret_ther2 (12K) APPROCHE VF "Cell-Centred Formulation" pour la solution des Equations d'Euler pour un gaz parfait. OPERATEUR PRET Operateur qui 'recontruit les variables primitives aux…
pret_ther3 (15K) APPROCHE VF "Cell-Centred Formulation" pour la solution des Equations d'Euler pour un gaz parfait. OPERATEUR PRET Operateur qui 'recontruit les variables primitives aux… P:GAM1
pret_ther4 (29K) APPROCHE VF "Cell-Centred Formulation" pour la solution des Equations d'Euler pour un gaz parfait. OPERATEUR PRET Operateur qui 'recontruit les variables primitives aux… P:GAM1
pret_wall (4K) APPROCHE VF "Cell-Centred Formulation" pour la solution des Equations d'Euler pour un gaz parfait OPERATEURS PRIM et PRET Gaz monoespece "calorically perfect" Etat mur…
primtest1 (7K) APPROCHE VF "Cell-Centred Formulation" pour la solution des Equations d'Euler pour un gaz parfait OPERATEUR PRIM Gaz monoespece "calorically perfect" A. BECCANTINI…
primtest1_3D (3K) APPROCHE VF "Cell-Centred Formulation" pour la solution des Equations d'Euler pour un gaz parfait OPERATEUR PRIM Gaz monoespece "calorically perfect" Cas 3D A.…
primtest3 (5K) APPROCHE VF "Cell-Centred Formulation" pour la solution des Equations d'Euler pour un gaz parfait OPERATEUR PRIM Cas: gaz multiespece "calorically perfect" A. BECCANTINI…
prim_errord (4K) APPROCHE VF "Cell-Centred Formulation" pour la solution des Equations d'Euler pour un gaz parfait OPERATEUR PRIM Test erreur ordre composantes vitesse-fractions…
prim_gfm (4K) APPROCHE VF "Cell-Centred Formulation" pour la solution des Equations d'Euler, GFMP OPERATEUR 'PRIM', GFMP Stiffened gas A. BECCANTINI DRN/DMT/SEMT/TTMF MAI 2011
prim_ther_2es (12K) APPROCHE VF "Cell-Centred Formulation" pour la solution des Equations d'Euler pour un gaz parfait OPERATEUR PRIM Gaz multi-especes (deux especes) "thermally perfect" A.…
prim_ther_dem (15K) FV "Cell-Centred Formulation" for the solution of the Euler equations for a thermally perfect gas. Discrete Equation Method for the propagation of infinitely thin flames…
prim_ther_dem3D (14K) FV "Cell-Centred Formulation" for the solution of the Euler equations for a thermally perfect gas. Discrete Equation Method for the propagation of infinitely thin flames…
prim_ther_mono (12K) APPROCHE VF "Cell-Centred Formulation" pour la solution des Equations d'Euler pour un gaz parfait OPERATEUR PRIM Gaz monoespece "thermally perfect" A. BECCANTINI…
prim_ther_mono_3D (11K) APPROCHE VF "Cell-Centred Formulation" pour la solution des Equations d'Euler pour un gaz parfait OPERATEUR PRIM Gaz monoespece "thermally perfect" Cas 3D A. BECCANTINI…
prim_ther_multi (37K) APPROCHE VF "Cell-Centred Formulation" pour la solution des Equations d'Euler pour un gaz parfait OPERATEUR PRIM Gaz multi-especes "thermally perfect" A. BECCANTINI…
shearfmm (57K) Shear layer. Methode implicite sans matrice BECCANTINI A., SFME/LTMF, Juin 2006 This file is divided into several parts I) PROCEDURES II) MESH III) INITIAL CONDITIONS…
shearlayer (13K) APPROCHE VF "Cell-Centred Formulation" pour la solution des Equations d'Euler pour un gaz parfait OPERATEURS PRET, KONV Gaz monoespece "calorically perfect" HUSVL,…
srivastava1VF (16K) CAS TEST : srivastava.dgibi Test de fonctionnement de DARCYSAT en 1D avec effet de gravité en regime transitoire. A. GENTY - DM2S/SFME/MTMS - 10/2007 Infiltration d'eau… P:DARCYSAT
transsatVF (12K) CAS TEST : transsat.dgibi Test de fonctionnement de DARCYSAT sur un probleme multizone. Infiltration d'eau dans une barrière ouvragée dans son site d'acceuil. -… P:@ARR,DARCYSAT,DESTRA,HT_PRO,TRACHIS
tube2D (12K) CALCUL DU TUBE A CHOC 2D FORMULATION VF COMPRESSIBLE EXPLICITE DIFFERENTS SOLVEURS A. BECCANTINI TTMF MARS 1998
tube3D (16K) CALCUL DU TUBE A CHOC FORMULATION VF COMPRESSIBLE EXPLICITE DIFFERENTS SOLVEURS A. BECCANTINI TTMF MARS 1998 Remise à jours : JUIILETT 2001 Remise à jours : SEPTEMBRE…
tube3Daxi (11K) CALCUL DU TUBE A CHOC FORMULATION VF COMPRESSIBLE EXPLICITE DIFFERENTS SOLVEURS 3DAXIS A. BECCANTINI LTMF FEVRIER 2004
tube3D_multi_ther (29K) CALCUL DU TUBE A CHOC FORMULATION VF COMPRESSIBLE EXPLICITE DIFFERENTS SOLVEURS A. BECCANTINI TTMF MARS 1998 Remise à jours : JUIILETT 2001 Remise à jours : SEPTEMBRE…
tubeaxi (11K) CALCUL DU TUBE A CHOC FORMULATION VF COMPRESSIBLE EXPLICITE DIFFERENTS SOLVEURS 'MODE' 'AXIS' A. BECCANTINI TTMF FEVRIER 2004
tube_multi (29K) CALCUL DU TUBE A CHOC; CAS MULTIESPECE FORMULATION VF COMPRESSIBLE EXPLICITE DIFFERENTS SOLVEURS A. BECCANTINI TTMF NOVEMBRE 1998
unsat_lindiriEFMH (17K) CAS TEST : unsat_lindiri.dgibi Test de fonctionnement de DARCYSAT en 1D avec effet de gravité en regime transitoire. A. GENTY - DM2S/SFME/LSET - 03/2009 Infiltration… P:DARCYSAT
vecoul2D (2K) CAS TEST : vecoul.dgibi --------------------- Création du maillage 3D --------------------- P:@VECOUL
vecoul3D (2K) CAS TEST : vecoul.dgibi --------------------- Création du maillage 3D --------------------- P:@VECOUL
warrickEFMH (20K) CAS TEST : warrick.dgibi Test de fonctionnement de DARCYSAT en 2D avec effet de gravité en regime permanent. A. GENTY, G. BERNARD-MICHEL - DM2S/SFME/MTMS - 02/2006… P:DARCYSAT,KR_PRO,PECHE
warrickVF (20K) CAS TEST : warrick.dgibi Test de fonctionnement de DARCYSAT en 2D avec effet de gravité en regime permanent. A. GENTY, G. BERNARD-MICHEL - DM2S/SFME/MTMS - 02/2006… P:DARCYSAT,KR_PRO,PECHE

## Fluides Diffusion (1)
Dynasp (33K)  P:BIF,EXEC,FILTREKE,PPRE

## Fluides Euler (16)
comp_perfmult_perftemp (9K) APPROCHE VF "Cell-Centred Formulation" pour la solution des Equations d'Euler pour un gaz parfait OPERATEURS PRIM, PRET, KONV Cas gaz multi-especes: Comparaison…
crebe12 (53K) GIBIANE file for the HDR test E12.3.2 in 2D We make 100 iterations on the coarse mesh and compare the overpressure in the room R1904 with earlier computed values CREBCOM…
domall (57K) Compatibility check CHECKERR to see the error messages.
domaxi (18K) Finite Volume, "Cell-Centred Formulation". 'MODE' 'AXIS' We check that 3D axis-symmetrical = 2D 'MODE' 'AXIS' Operateur 'DOMA' A. BECCANTINI, LTMF FEBRUARY 2004…
flux_wall (5K) APPROCHE VF "Cell-Centred Formulation" pour la solution des Equations d'Euler pour un gaz parfait OPERATEURS PRIM, PRET, KONV Gaz monoespece "calorically perfect" Flux…
kbmmsp_impl2D (73K) APPROCHE VF "Cell-Centred Formulation" pour la solution des Equations d'Euler pour un gaz parfait multiespes Implicit: calcul du jacobien du residu Cas gaz multiespes,…
konmsp_impl3D (118K) APPROCHE VF "Cell-Centred Formulation" pour la solution des Equations d'Euler pour un gaz parfait multiespecies OPERATEURS PRIM, PRET, KONV Implicit: calcul du jacobien…
konvaxi (7K) Finite Volume, "Cell-Centred Formulation". 'MODE' 'AXIS' We check that 3D axis-symmetrical = 2D 'MODE' 'AXIS' Operateurs 'KONV' et ('FIMP' 'VF' 'AXIS) A. BECCANTINI,…
konv_cons (14K) APPROCHE VF "Cell-Centred Formulation" pour la solution des Equations d Euler pour un gaz parfait OPERATEURS PRIM, PRET, KONV Cas gaz monoespece, "calorically perfect"…
konv_fmm_test (17K) 'KONV' OPERATOR FREE MATRIX METHOD implicitation. VF "cell-centered" discretization of the Euler equations. Unknowns : U (density, momentum, total energy per volume…
konv_fmm_test2 (8K) 'KONV' OPERATOR FREE MATRIX METHOD implicitation. VF "cell-centered" discretization of the Euler equations. Unknowns : U (density, momentum, total energy per volume…
konv_gamma (4K) APPROCHE VF "Cell-Centred Formulation" pour la solution des Equations d Euler pour un gaz parfait OPERATEURS PRIM, PRET, KONV Computation of preconditioned jacobians Cas…
konv_impl2 (25K) APPROCHE VF "Cell-Centred Formulation" pour la solution des Equations d'Euler pour un gaz parfait OPERATEURS PRIM, PRET, KONV Implicit: calcul du jacobien du residu Cas…
konv_impl2ord (36K) APPROCHE VF "Cell-Centred Formulation" pour la solution des Equations d'Euler pour un gaz parfait OPERATEURS PRIM, PRET, KONV Implicit: calcul du jacobien du residu (2nd…
konv_impl3 (24K) APPROCHE VF "Cell-Centred Formulation" pour la solution des Equations d'Euler pour un gaz parfait OPERATEURS PRIM, PRET, KONV Implicit: calcul du jacobien du residu Cas…
lapn (4K) CALCUL DU LAPLACIAN EN VF LAPL(T)=0 On controlle que l'algorithme est lineaire exact A. BECCANTINI LTMF JUILLET 2001

## Fluides Non Stationnaire (2)
cyltest (13K) Ecoulement autour d'un cylindre circulaire Résolution des équations de Navier Stokes laminaires instationnaires P:EXEC
cyltest6 (13K) Ecoulement autour d'un cylindre circulaire Résolution des équations de Navier Stokes laminaires instationnaires Pompé sur cyltest.dgibi Ajouts Stéphane GOUNAND… P:EXEC

## Fluides Permanent (18)
cd_clim (5K) NOM : CD_CLIM DESCRIPTION : Calcul d'un problème de convection-diffusion illustrant l'importance de l'intégration par parties sur les conditions aux limites. 2D… P:EXEC
cl_B_2 (9K) C C* C* PROJET : Opérateur CLMI C* NOM : profil_B_2.dgibi C* DESCRIPTION : Jeu de données pour le calcul d'un écoulement en C* fluide visqueux entre 2 plaques C* LANGAGE… P:EXEC
cl_B_3 (10K) C C* C* PROJET : Opérateur CLMI C* NOM : cl_B_3.dgibi C* DESCRIPTION : Jeu de données pour le calcul d'une couche limite C* laminaire par la méthode à 2 équations C*… P:EXEC
cl_D_3 (9K) C C* C* PROJET : Opérateur CLMI C* NOM : cl_D_3 .dgibi C* DESCRIPTION : Jeu de données pour le calcul de la couche limite C* turbulente en utilisant les relations de… P:EXEC
cl_D_4 (9K) C C* C* PROJET : Opérateur CLMI C* NOM : cl_D_4 .dgibi C* DESCRIPTION : Jeu de données pour le calcul de la couche limite C* turbulente en utilisant les relations de… P:EXEC
cl_D_6 (12K) C C* C* PROJET : Opérateur CLMI C* NOM : cl_D_6 .dgibi C* DESCRIPTION : Jeu de données pour le calcul de la couche limite C* turbulente en utilisant les relations de… P:EXEC
cl_D_7 (10K) C C* C* PROJET : Opérateur CLMI C* NOM : cl_D_6 .dgibi C* DESCRIPTION : Jeu de données pour le calcul de la couche limite C* turbulente en utilisant les relations de… P:EXEC
cl_E_3 (11K) C C* C* PROJET : Opérateur CLMI C* NOM : cl_E_3 .dgibi C* DESCRIPTION : Jeu de données pour le calcul de la couche limite C* turbulente en utilisant les relations de… P:EXEC
cl_E_4 (11K) C C* C* PROJET : Opérateur CLMI C* NOM : cl_E_4 .dgibi C* DESCRIPTION : Jeu de données pour le calcul de la couche limite C* turbulente en utilisant les relations de… P:EXEC
cl_E_6 (11K) C C* C* PROJET : Opérateur CLMI C* NOM : cl_E_6 .dgibi C* DESCRIPTION : Jeu de données pour le calcul de la couche limite C* turbulente en utilisant les relations de… P:EXEC
cl_E_7 (11K) C C* C* PROJET : Opérateur CLMI C* NOM : cl_E_7.dgibi C* DESCRIPTION : Jeu de données pour le calcul d'une couche limite C* turbulente dans un écoulement accéléré C*… P:EXEC
conv2d-2 (8K) NOM : CONV2D-2 DESCRIPTION : 2D pure convection equation Similar to conv2d.dgibi but more complex: + interactive GUI (interact = vrai) + slide generation for the lecture… P:EXEC
conv2d (5K) NOM : CONV2D DESCRIPTION : 2D pure convection equation See: ENSTA Lecture Notes 2021 Introduction to the finite element method applied to incompressible fluid mechanics… P:EXEC
convdif1d-2 (6K) NOM : CONVDIF1D-2 DESCRIPTION : 1D convection-diffusion equation Similar to convdif1d.dgibi but more complex: + interactive GUI (interact = vrai) + slide generation for… P:EXEC
convdif1d (3K) NOM : CONVDIF1D DESCRIPTION : 1D convection-diffusion equation See: ENSTA Lecture Notes 2021 Introduction to the finite element method applied to incompressible fluid… P:EXEC
infsup (7K) NOM : INFSUP DESCRIPTION : Calcul du problème de Stokes illustrant l'importance de la condition inf-sup Simple Stokes problem in a cavity with a focus on the inf-sup… P:EXEC
ns_clim (8K) NOM : NS_CLIM DESCRIPTION : Calcul du problème de Navier-Stokes illustrant l'importance de l'intégration par parties sur les conditions aux limites. Navier-Stokes… P:EXEC
paraton (6K) NOM : PARATON.DGIBI DESCRIPTION : Laplacian on a domain with a spike See: ENSTA Lecture Notes 2021 Introduction to the finite element method applied to incompressible… P:EXEC

## Fluides Poreux (2)
jpor1 (6K) TEST SUR UN JOINT POREUX BIDIMENSIONNEL (ELEMENT JOP3) UN JOINT POREUX 2D EST BLOQUE EN BAS ET CHARGE EN HAUT AVEC UNE FORCE TANGENTIELLE ET UNE FORCE DE COMPRESSION. UN… P:PASAPAS
tbsrc1 (3K) $$$ TBSRC1 Test de non regression --- 2 JUIN 1998 --- Tube cylindrique Rayon R0=0.25 Longueur L0=16*R0 test cas isotherme NS,FIMP KBBT en Implicite coefficient de FIMP… P:EXEC

## Fluides Statique (1)
condens (33K) condens.dgibi : bas Mach + condensation en paroi MODELE MISTRA AVEC CONDENSEURS INJECTION DE VAPEUR DANS UNE ENCEINTE FERMEE CONTENANT DE L'AIR TEMPERATURE DE PAROI… P:EXEC,FILTREKE

## Fluides Stokes (2)
stokes_lagaug (49K) fichier stokes_lagaug.dgibi NOM : STOKES_LAGAUG DESCRIPTION : Cas-test équation de Stokes incompressible Méthode directe et de Lagrangien augmenté pour les contraintes… P:DEADUTIL,ININLIN
stokes_rima (38K) fichier stokes_rima.dgibi NOM : STOKES_RIMA DESCRIPTION : Cas-test équation de Stokes incompressible Méthode directe et pénalisation des contraintes Cavité carrée… P:DEADUTIL,ININLIN

## Fluides Thermique (23)
bc30 (10K) $$$ BC30 X BC30 (Jeux de donnees) BC30 CANAL CHAUFFE INCLINE ANGL = 30. LONGUEUR H0=10 LARGEUR 1. K-E PLAN --- RE=2.E+5 teste NSKE(SUPG) TSCAL(PSI) LAPN FPU ECHI et… P:EXEC,VNIMP,VTIMP
cavitefmm (33K) CAVITE CARRE A PAROI DEFILANTE Methode implicite sans matrice pour les equations de Navier-Stokes (bas Mach) BECCANTINI A., SFME/LTMF, DEC 2003 The real file starts…
cav_ray_proj (14K) Couplage Rayonnement/Convection/Conduction Test d'un cavité rayonnante en 2D plan Le mélange gazeux est transparent Rayleigh = 1e6 Résolution par la méthode de… P:EXEC
ccar_cond (8K) NOM : CCAR_COND DESCRIPTION : Cavité chauffée contenant un carré conducteur centré. Refs biblio: @article{Lee20053308, title = "A numerical study of natural convection… P:EXEC
ccaxi (16K) CAS TEST : CCAXI.DGIBI Convection naturelle dans un cylindre différentiellement chauffé (Thot en bas, Tcold en haut, Flux nul sur la paroi verticale) (Navier-Stokes… P:EXEC
couplage_TH1D_Th3D (132K) From ~/nlin/sources_dev_new/util_proc : BEGINPROCEDUR append NOM : APPEND DESCRIPTION : Rajoute : - un entier à un listentier - un réel à un listreel - un objet (liste,… P:@STBL,EXEC
couplage_TH1D_Th3D_1 (30K) NOM : couplage_TH1D_Th3D_1.dgibi DESCRIPTION : Voir rapport DM2S/SFME/LTMF/RT/03-012/B Modélisation couplée thermique 3D-thermohydraulique 1D d'un coeur de réacteur à… P:EXEC
couplage_TH1D_Th3D_2 (38K) NOM : couplage_TH1D_Th3D_2.dgibi DESCRIPTION : Voir rapport DM2S/SFME/LTMF/RT/03-012/B Modélisation couplée thermique 3D-thermohydraulique 1D d'un coeur de réacteur à… P:EXEC
dvisp (7K) CAVITE CARREE ­ VAHL­DAVIS Methode de projection implicite Malvina Renesson Aout 1999 P:EXEC
dvispassi (8K) CAVITE CARREE ­ VAHL­DAVIS Methode de projection implicite Malvina Renesson Aout 1999 P:EXEC
dvispassi2 (8K) CAVITE CARREE ­ VAHL­DAVIS Methode de projection implicite Malvina Renesson Aout 1999 P:EXEC
dvispassi3 (8K) CAVITE CARREE ­ VAHL­DAVIS Methode de projection implicite Malvina Renesson Aout 1999 P:EXEC
dvispassic (8K) CAVITE CARREE ­ VAHL­DAVIS Methode de projection implicite Malvina Renesson Aout 1999 P:EXEC
dvispqt (7K) CAVITE CARREE ­ VAHL­DAVIS Methode de projection implicite Malvina Renesson Aout 1999 P:EXEC
dvispw (51K) CAVITE CARREE ­ VAHL­DAVIS Methode de projection implicite Malvina Renesson Aout 1999 Version utilisant l'option EQUA de EQEX le terme de flottabilite est traite dans la… P:EXAC,EXEC,VERTYTAB,VNIMP
mistra (22K) mistra.dgibi : bas Mach avec Condensation en Paroi JEU DE DONNEES POUR TESTER LE BON FONCTIONNEMENT DES OPERATEURS NSKE, PRESSION, TSCAL, QOND, FIMP, LAPN. INJECTION DE… P:ACIER,EXEC,FILTREKE,H_B
nlin_te_unstat (68K) NOM : nlin_te_unstat.dgibi DESCRIPTION : We compute the flow governed by the Navier-Stokes equations, in a T jonction with high temperature difference. Both Boussinesq… P:ININLIN
slotevol (22K) Jeu de données GIBIANE: Description : Ce jeu de données permet la discrétisation éléments finis d'un écoulement dans une hypothèse de bas Mach. Il s'agit ici de comparer… P:EXEC
soudage1 (11K) NOM : soudage1.dgibi ___ pb. d'advection-diffusion avec rayonnement par une méthode d'éléments finis Equation de l'energie + modèle de plaque plane Biblio : Rapport DM2S… P:EXEC
soudage2 (37K) NOM : ERRREL DESCRIPTION : Calcul d'une erreur relative LANGAGE : GIBIANE-CAST3M AUTEUR : Stéphane GOUNAND (CEA/DEN/DM2S/SFME/LTMF) mél : gounand@semt2.smts.cea.fr… P:@STBL,ANIME,EXEC,SOUDAGE
test-asp2D (12K) Jeu de données - maillage 2D injection de gouttes à 40°C dans une enceinte remplie d'air à 24°C modèle à 7 équations (diphasique-1 phase dispersée) Date : L. Blumenfeld… P:ENCEINTE,EXECRXT
vahldavis (5K)  P:EXEC
vahldavis3D (6K)  P:EXEC

## Fluides Transitoire (53)
aerosol1 (9K) AEROSOL1.DGIBI NATURE DU PROBLEME : TRANSPORT DE PARTICULES AVEC DEPOT CONVECTION FORCEE CALCUL DE L'ECOULEMENT DANS UN PREMIER TEMPS CALCUL DU TRANSPORT DANS UN… P:EXEC,VNIMP
aerosol2 (8K) AEROSOL2.DGIBI NATURE DU PROBLEME : TRANSPORT DE PARTICULES AVEC DEPOT CONVECTION FORCEE TRANSITOIRE SIMULTANE SUR LES PARTICULES ET L'ECOULEMENT TURBULENT OPERATEURS :… P:EXEC,VNIMP
aerosol3 (7K) AEROSOL3.DGIBI Exemple d'utilisation des FONCTIONS DE PAROI AEROSOL LAMINAIRES. Ce jeu de données teste les operateurs TSCA, ECHI, KUET et FPAL. On résoud une équation… P:EXEC,FPAL,KUET
aitr_2D (10K) ----------------------- aitr_2D.dgibi Scénario de type LOVA dans ITER P:EXECRXT
ale_mecaflu (50K) NOM : ale_mecaflu.dgibi DESCRIPTION : fiche de validation CASTEM2000 Mécanique des Fluides Equations de Navier-Stokes en description ALE (Arbitraire Lagrange-Euler)… P:@STBL,ANIME,BOITE,EXEC
asp (10K)  P:EXECRXT
aspxx (10K)  P:EXECRXT
benchmark_imst (19K) NOM : benchmark_imst.dgibi DESCRIPTION : fiche de validation CASTEM2000 Mecanique des Fluides Convection naturelle laminaire en cavite rectangulaire (2D) FONCTIONS… P:BOITE,EXEC
burgers1d-2 (7K) NOM : BURGERS1D-2.DGIBI DESCRIPTION : Exemple équation de Burgers 1D 1D Burgers equation Similar to burgers1d.dgibi but more complex: + interactive GUI (interact = vrai)… P:EXEC
burgers1d (5K) NOM : BURGERS1D.DGIBI DESCRIPTION : 1D Burgers equation See: ENSTA Lecture Notes 2021 Introduction to the finite element method applied to incompressible fluid mechanics… P:EXEC
cacul (19K) LA SOLUTION ANALYTIQUE TS = 1.D0; P:DARCYSAT,DESTRA,HT_PRO,TRACHIS
cacultrace (19K) LA SOLUTION ANALYTIQUE TS = 1.D0; P:DARCYSAT,DESTRA,HT_PRO,TRACHIS
caculVF (19K) LA SOLUTION ANALYTIQUE TS = 1.D0; P:DARCYSAT,DESTRA,HT_PRO,TRACHIS
caculVFconservatif (19K) Mettre GRAPH a VRAI si les traces sont a effectuer Mettre COMPLET a VRAI si calcul complet a effectuer P:DARCYSAT,DESTRA,HT_PRO,TRACHIS
carre_expl (24K)  P:EXEC,FILTREKE,VNIMP
cc2d1 (4K) --- 10 Novembre 1999 --- TEST CAVITE CARREE A PAROI DEFILANTE RE=400 teste LAPL KONV (CENTREE) KBBT pression continue Algorithme de projection Elements P1-P1 Q1-Q1 2D… P:EXEC
cc2d2 (4K) --- 10 Novembre 1999 --- TEST CAVITE CARREE A PAROI DEFILANTE RE=400 teste LAPL KONV (CENTREE) KBBT pression continue Algorithme de projection Elements P1-P1 Q1-Q1 2D… P:EXEC
cc2d3 (4K) --- 10 Novembre 1999 --- TEST CAVITE CARREE A PAROI DEFILANTE RE=400 teste LAPL KONV (CENTREE) KBBT pression continue Algorithme de projection Elements P1-P1 Q1-Q1 2D… P:EXEC
cc3d1 (3K) --- 08 Novembre 1999 --- TEST CAVITE CUBIQUE teste KBBT NS en 3D + le Bi CG cc2d1.dgibi teste les elements a pression continue sur des tetrahedres et pyramides P1-P1 et… P:EXEC
cc3d2 (4K) --- 08 Novembre 1999 --- TEST CAVITE CUBIQUE teste KBBT NS en 3D + le Bi CG teste les elements a pression continue sur des hexahedres et prisme P1-P1 et Q1-Q1 algorithme… P:EXEC
cc3d3 (4K) --- 08 Novembre 1999 --- TEST CAVITE CUBIQUE teste KBBT NS en 3D + le Bi CG teste les elements a pression continue sur des hexahedres et prisme P2 + bulle - P1 et Q2 -… P:EXEC
ccar1 (4K) --- 10 OCTOBRE 1997 --- TEST CAVITE CARRE teste NS(SUPG) DUDW en IMPL Formulation QUADR P0 et P1 P:EXEC
ccar2 (4K) --- 10 OCTOBRE 1997 --- TEST CAVITE CARRE teste NS(SUPG) DUDW en IMPL Formulation MACRO P0 et P1 P:EXEC
ccar3 (8K) --- 10 OCTOBRE 1997 --- TEST CAVITE CARRE teste LAPL KONV(SUPG) KMAB KMBT en IMPL et DFDT (centrep0 et p1) Formulation MACRO P0 et P1 Formulation QUADR P0 et P1 P:EXEC
ccar3d (2K) --- 12 OCTOBRE 1998 --- TEST CAVITE CUBIQUE teste KCCT NS en 3D + le Bi CG P:EXEC
ccar4 (5K) --- 10 OCTOBRE 1998 --- TEST CAVITE CARRE teste LAPL KONV(SUPG) KCCT en IMPL Formulation MACRO CENTREP1 Formulation QUADR CENTREP1 P:EXEC
ccar5 (9K) --- 6 JUIN 1999 --- TEST CAVITE CARRE A PAROI DEFILANTE RE=400 Comparaison des algorithmes Implicite, projection et semi explicite. teste LAPL KONV NS (CENTREE) KBBT… P:EXEC
ccar5w (47K) --- 4 AVRIL 2001 --- TEST CAVITE CARRE A PAROI DEFILANTE RE=400 Algorithme projection implicite teste LAPL KONV NS (CENTREE) KBBT Formulation MACRO CENTRE… P:EXAC,EXEC,VERTYTAB,VNIMP
ccar6 (4K) --- 10 Juin 2000 --- TEST CAVITE CARREE A PAROI DEFILANTE RE=400 teste V normale et algo de projection teste LAPL KONV (CENTREE) KBBT FPU VNIMP pression continue et… P:EXEC,VNIMP
ccar7 (5K) --- 10 Juin 2000 --- TEST CAVITE CARREE A PAROI DEFILANTE RE=400 teste V normale et algo de projection teste LAPL KONV (CENTREE) KBBT FPU VNIMP pression continue et… P:EXEC,VNIMP
ccar_forc1 (8K) NOM : VALREL DESCRIPTION : Calcul d'une valeur relative LANGAGE : GIBIANE-CAST3M AUTEUR : Stéphane GOUNAND (CEA/DEN/DM2S/SFME/LTMF) mél : gounand@semt2.smts.cea.fr… P:EXEC
consmasse (9K) TESTE LA CONSERVATION DE LA MASSE POUR L'EQUATION SOUS FORME CONSERVATIVE : dC/dt + div ( U C ) = 0 AVEC U CHAMP DE VITESSE A DIVERGENCE NON NULLE COMPARAISON AVEC… P:EXEC
convnonlin1 (5K) EQUATION DE CONVECTION NON-LINEAIRE Ut + div (F(U)) = 0 AVEC F(U) = U*U/2 1_x + ln U 1_y U > 0 RESOLUE SOUS FORME NON-CONSERVATIVE dU/dt + U dU/dx + 1/U dU/dy = 0 AVEC… P:EXEC
defila (157K) NOM : DEFILA DESCRIPTION : Ecoulement sous une surface libre soumise à une pression LANGAGE : GIBIANE-CAST3M AUTEUR : Stéphane GOUNAND (CEA/DEN/DM2S/SFME/LTMF) mél :… P:@STBL,DEADUTIL,ININLIN
defila2 (174K) NOM : DEFILA2 DESCRIPTION : Ecoulement sous une surface libre soumise à une pression On a tenté de simplifier par rapport à defila : - plus de MATRIK - procédures de… P:@STBL,DEADUTIL,FCOURANT,ININLIN
diff1d-2 (6K) NOM : DIFF1D-2 DESCRIPTION : Exemple diffusion 1D en temporel Non stationary 1D diffusion equation Similar to diff1d.dgibi but more complex: + interactive GUI (interact… P:EXEC
diff1d (4K) NOM : DIFF1D DESCRIPTION : Non stationary 1D diffusion equation See: ENSTA Lecture Notes 2021 Introduction to the finite element method applied to incompressible fluid… P:EXEC
dvisi (6K) $$$ DVISI X DVISI(Jeux de donnees) -- DVISI -- Cavite carrée De Vahl Davis RA=1.E6 Algorithme implicite Teste en IMPLICITE NS TSCA DUDW DFDT LAPN éléments MACRO et… P:EXEC
fsckei (12K) Maillage d'un sous-canal d'un faisceau de tube à pas carré P:EXEC,KEPSILON,VNIMP
gridturb (7K) GRID TURBULENCE : convection of homogeneous turbulence Analysis of the K-Epsilon TURBULENCE MODEL Mohammadi/Pironneau p. 74 (Wiley) H. PAILLERE/TTMF/AVRIL 1997 (à… P:EXEC,KEPSILON
gridturb_expl (6K) GRID TURBULENCE : convection of homogeneous turbulence Analysis of the K-Epsilon TURBULENCE MODEL Mohammadi/Pironneau p. 74 (Wiley) H. PAILLERE/TTMF/AVRIL 1997 P:EXEC
gtkl (8K) GRID TURBULENCE : voir aussi gridturb.dgibi Analysis of the K-Epsilon TURBULENCE MODEL Mohammadi/Pironneau p. 74 (Wiley) H. PAILLERE/TTMF/AVRIL 1997 (à l'origine 1/2… P:EXEC,KEPSILON
hy1 (6K) $$$ HY1 Exemple HY1 --- 2 OCTOBRE 1990 --- CANAL LONGUEUR 10. LARGEUR 1. test cas isotherme NS et TOIMP On considère l'ecoulement de poiseuille dans un canal plan… P:EXEC,VNIMP,VTIMP
hy4 (5K) $$$ HY4 Exemple HY4 --- 2 FEVRIER 2002 --- CANAL LONGUEUR 3 X 10. LARGEUR 1. test cas isotherme NS et FROT (Faisceau de tube) Sur le tronçon du milieu on impose une… P:EXEC
injection (30K) NOM : Injection Air/Air (Air chaud dans Air froid sur 6 secondes) dans une cavité carrée 2D plan DESCRIPTION : Cas test du modèle asymptotique à bas nombre de Mach pour… P:EXEC
jet1p (15K)  P:EXEC,FILTREKE
jetaxi (10K) JETAXI.DGIBI : jet turbulent monophasique axisymétrique FICHE DE VALIDATION DU K-EPSILON INCOMPRESSIBLE + FILTRE FORMULATION EF QUA8 P. CORNET SEMT/TTMF DECEMBRE 1998 P:EXEC,FILTREKE
jetkei (13K) jetkei.dgibi jet 2D axi monophasique incompressible pour fiche de validation du K-epsilon Pierre Cornet , sept 97 jpm , mars 06 : adaptation pour K-epsilon implicite… P:EXEC,KEPSILON
jetplankei (11K) jetplankei.dgibi jet 2D Plan monophasique incompressible pour fiche de validation du K-epsilon Pierre Cornet , sept 97 jpm , mars 06 : adaptation pour K-epsilon… P:EXEC,KEPSILON
mdiavf (4K) cas test mdiavf.dgibi Test élémentaire des opérateurs DFDT et MDIA en Volumes Finis et en formulation EFM1. On résoud dc/dt + ac = 0 avec a coefficient de décroissance… P:EXEC
rayo-2D-1-trans (7K) pour calcul complet mettre complet à : vrai; test 2D couplage conduction-rayonnement REFERENCE: SPARROW CESS "Radiation Heat Transfer" 1978 p.189 DONNEES cas de 2… P:PASAPAS
tp3 (11K) Cours MF307 - Tp3 Diffusion d'un champ scalaire Solution stationnaire de l'équation de la chaleur Pour la non-regression, on vérifie que dans le cas d'une solution… P:EXEC,MONTAGNE
tran2 (6K) CAS TEST DU 91/06/24 PROVENANCE : DELA Test tran2.dgibi: jeux de données SI GRAPH = N PAS DE GRAPHIQUE AFFICHE SINON SI GRAPH DIFFERENT DE N TOUS LES GRAPHIQUES SONT… P:PASAPAS

## Fluides Transport (13)
chimsour1d (11K) repertoire des fichiers "divers" CAS TEST : chimsour1d.dgibi TRANSPORT GEOCHIMIE AVEC SOURCE ( CAS 1D) la partie post-traitement avec graphique contient des exemples… P:CHITRNSP,DESTRA,NOCOMCHI,NOESPCHI,TRACHIS,TRACHIT ext:COMPOM
condmixtesEFMH (12K) CAS TEST : transport1.dgibi TEST TRANSPORT - conditions mixtes CALCUL DARCY ISOTROPE TRANSPORT. Transport d'un front. dT -- + div (uT - Kgrad(T)) = 0 dt Ce test permet… P:TRANSGEN
condmixtesVF (12K) CAS TEST : transport1.dgibi TEST TRANSPORT - conditions mixtes CALCUL DARCY ISOTROPE TRANSPORT. Transport d'un front. dT -- + div (uT - Kgrad(T)) = 0 dt Ce test permet… P:TRANSGEN
cone (10K) = Transport d'un cone par un champ de vitesse à rotationnel constant. = Comparaison de schéma en temps EF implicites P:EXEC,MONTAGNE
conem (10K) = Transport d'un cone par un champ de vitesse à rotationnel constant. = Comparaison de schéma en temps EF implicites P:EXEC,MONTAGNE
coneq (10K) = Transport d'un cone par un champ de vitesse à rotationnel constant. = Comparaison de schéma en temps EF implicites P:EXEC,MONTAGNE
conew (51K) = Transport d'un cone par un champ de vitesse à rotationnel constant. = Comparaison de schéma en temps EF implicites $$$$ EXEC EXEC PROCEDUR MAGN 03/03/31 21:15:04 4631… P:EXAC,EXEC,MONTAGNE,VERTYTAB,VNIMP
linekman (13K) Date : 19/3/97 Description: Cas test simulant l'écoulement dans une région limitée par une plaque horizontale infinie en rotation autour d'un axe perpendiculaire.… P:EXEC
linekmanimp (9K) Date : 06/01/99 Description: Cas test simulant l'écoulement dans une région limitée par une plaque horizontale infinie en rotation autour d'un axe perpendiculaire.… P:EXEC
smithhutton (9K) Convection/Diffusion : CAS SMITH ET HUTTON REFERENCE : NUMERICAL HEAT TRANSFER, VOL.5, p.439, 1982 Les faces latérales et supérieure d'une boite rectangulaire sont… P:EXEC
smithhutton_cvg (15K) NOM : SMITHHUTTON_CVG DESCRIPTION : Une variante du cas-test de convection-diffusion d'un scalaire dû à Smith et Hutton [1] (voir aussi smithhutton.dgibi) On cherche à… P:@POMI,EXEC
smithhutton_impl (7K) Convection/Diffusion : CAS SMITH ET HUTTON REFERENCE : NUMERICAL HEAT TRANSFER, VOL.5, p.439, 1982 Les faces latérales et supérieure d'une boite rectangulaire sont… P:EXEC
tube_scal_complet (10K) Transport d'un scalaire dans un tube FORMULATION VF COMPRESSIBLE EXPLICITE/IMPLICITE SOLVEURS: UPWIND/CENTERED A. BECCANTINI LTMF NOVEMBRE 2001

## Fluides Vibration (7)
fsi1 (5K) CAS TEST DU 91/10/16 PROVENANCE : PETI Test fsi1.dgibi: Jeux de données Test fsi1.dgibi: jeux de données SI GRAPH = N PAS DE GRAPHIQUE AFFICHE SINON SI GRAPH DIFFERENT…
fsi2 (4K) CAS TEST DU 91/10/04 PROVENANCE : PETI Test fsi2.dgibi: jeux de données SI GRAPH = N PAS DE GRAPHIQUE AFFICHE SINON SI GRAPH DIFFERENT DE N TOUS LES GRAPHIQUES SONT…
fsi3 (5K) CAS TEST DU 91/10/04 PROVENANCE : PETI Test fsi3.dgibi: jeux de données SI GRAPH = N PAS DE GRAPHIQUE AFFICHE SINON SI GRAPH DIFFERENT DE N TOUS LES GRAPHIQUES SONT…
fsi4 (5K) Test Fsi4.dgibi: Jeux de données CAS TEST DU 91/10/04 PROVENANCE : PETI Test fsi4.dgibi: jeux de données SI GRAPH = N PAS DE GRAPHIQUE AFFICHE SINON SI GRAPH DIFFERENT…
fsi5 (5K) CAS TEST DU 91/10/04 PROVENANCE : PETI Test fsi5.dgibi: jeux de données SI GRAPH = N PAS DE GRAPHIQUE AFFICHE SINON SI GRAPH DIFFERENT DE N TOUS LES GRAPHIQUES SONT…
fsi6 (5K) CAS TEST DU 91/10/04 PROVENANCE : PETI Test fsi6.dgibi: jeux de données SI GRAPH = N PAS DE GRAPHIQUE AFFICHE SINON SI GRAPH DIFFERENT DE N TOUS LES GRAPHIQUES SONT…
fsi7 (6K) Cas test FSI7 Calcul d'une masse ajoutee en mode de Fourier (lame fluide) P:FOUR2TRI

## Langage (1)
INTG_test_integration_reduite (2K) Cas-test de calculs d'integrales avec les elements a integration reduite C20R et P15R

## Langage Base (2)
evol_comp (1K) PRESENTATION Ce cas-test permet de tester 1- le bon fonctionnement des differentes combinaisons de l'operateur 'EVOL' avec l'option 'COMP' 2- le bon fonctionnement de…
evol_manu (1K) PRESENTATION Ce cas-test permet de tester 1- le bon fonctionnement des differentes combinaisons de l'operateur 'EVOL' avec l'option 'MANU' 2- le bon fonctionnement de…

## Langage Fonctionnement (1)
chan2 (7K) SI GRAPH = N PAS DE GRAPHIQUE AFFICHE SINON SI GRAPH DIFFERENT DE N TOUS LES GRAPHIQUES SONT AFFICHES

## Langage Objets (69)
ASSI_01 (4K) Test ASSI_01.dgibi: Jeux de données CAS TEST DU 05/11/2018 PROVENANCE : TEST TEST ASSI_01 Verification & Validation TEST SUR L'OPERATEUR ASSI qui lance des commandes…
chan1 (4K) NOM : CHAN1 DESCRIPTION : Teste le changement des QUAFs en TRI3 ou QUA4 ou TET4 ou CUB8 ou PYR5 LANGAGE : GIBIANE-CAST3M AUTEUR : Stéphane GOUNAND…
cinema1 (3K) Example of use of the cinema procedure A mesh is made of 4 arches: we want to pass under the 3 first arches, go around the 4th and go under the 4 arches. P.PEGON… P:CINEMA
cinemb1 (2K) Example of use of the cinemb procedure A mesh is made of 1 arches: we want to pass under turning and rising the head. P.PEGON JRC-ISPRA 01/10/95 P:CINEMB
coul_deformee (3K) Verification du comportement de l'operateur COUL Changement de couleur des objets de type : - maillage - evolutions - deformees - vecteurs Indicateur de trace
crit_pplan (2K) Test du critere d'ecart a la planeite de l'operateur 'SURF', option 'PLAN' : (S1 = SURF GEO1 PLAN CRIT ;)
deda (6K) Cas test pour l'operateur DEDAns On test le resultat de l'operateur DEDA sur des points sur des points situes a l'exterieur et a l'interieur d'un contour (2D) et d'une…
deduad1d (6K) NOM : DEDUAD1D DESCRIPTION : cas-test élémentaire 1D pour 'DEDU' 'ADAP' LANGAGE : GIBIANE-CAST3M AUTEUR : Stéphane GOUNAND (CEA/DEN/DM2S/SFME/LTMF) mél :… P:DEADUTIL
deduad2d (20K) NOM : DEDUAD2D DESCRIPTION : cas-test 2d pour 'DEDU' 'ADAP' LANGAGE : GIBIANE-CAST3M AUTEUR : Stéphane GOUNAND (CEA/DEN/DM2S/SFME/LTMF) mél : gounand@semt2.smts.cea.fr… P:DEADUTIL
deduad3d (12K) NOM : DEDUAD3D DESCRIPTION : cas test 3d pour deduadap LANGAGE : GIBIANE-CAST3M AUTEUR : Stéphane GOUNAND (CEA/DEN/DM2S/SFME/LTMF) mél : gounand@semt2.smts.cea.fr… P:DEADUTIL
dedu_cerc (7K) NOM : DEDU_CERC DESCRIPTION : Utilisation de 'DEDU' 'ADAP' pour construire le maillage le plus "régulier" possible d'un quart de cercle homéomorphe à un maillage… P:DEADUTIL
dedu_cl1d (41K) NOM : DEDU_CL1D DESCRIPTION : Adaptation de maillage avec 'DEDU' 'ADAP' sur une couche limite exponentielle 1D (équation de convection-diffusion à fort Péclet) LANGAGE :… P:ININLIN
dessin (13K) dessin.dgibi PROCEDURE WATERFALL (experimentale) tracé Waterfall Cast3M (experimental) ____ /\ . _______/ \_/\____.-.._/ \__.---------._____ /\ _____/\_/\____.-.._/… P:@HISTOGR
ET_LISTMOTS (3K) Test ET_LISTMOTS.dgibi: Jeux de données TEST ET_LISTMOTS Permet de realiser la verification et validation du 'ET' dans les cas suivants : LISTMOTS 'ET' MOT MOT 'ET'…
explochar (1K) Verifie le fonctionnement de la procedure EXPLORER avec la donnee d'un CHARGEMENT P:EXPLORER
extrevoletiq (1K) Test elementaire : EV2 = 'EXTR' EV1 'COUR' MOT1 ; MOT1 = Nom etiquette d'une des listes d'abscisses ou d'ordonnees.
ex_proper (2K) TEST PLUS, MOINS, DEDU, TOUR OPERANDES MCHAML, MMODEL, CHPO, MAILLAGE (RIGIDITE)
inclusions (5K) Maillage d'un echantillon cubique de particules spheriques en inclusion dans une matrice -------------------- Parametres de la realisation -------------------- NBG1 :… P:@INCLUSI,@POINTIR,@P_BOIT2,@P_VORO
INTG_test (8K) Ce Cas-Test permet de tester l'operateur INTG dans differentes configurations d'options
isp472d_cond_Fick (23K) Cas test de non-régression pour la bas de jdd de CAST3M Test de non régression du modèle de Fick Jeu de données MISTRA pour le maillage 2D de l enceinte Il a été choisi… P:EXECRXT
ktest_io1 (4K) But : Tester le fonctionnement de la sauvegarde Jeu de donnees qui
ktest_io2 (1K) restitutions succésives ... sg 2014/11 : nouveaux noms d'inconnues
nlin_japg (1K) NOM : NLIN_JAPG DESCRIPTION : Teste jacobien et points de Gauss de NLIN LANGAGE : GIBIANE-CAST3M AUTEUR : Stéphane GOUNAND (CEA/DEN/DM2S/SFME/LTMF) mél :…
nlin_lapn (7K) BEGINPROCEDUR coptab NOM : COPTAB DESCRIPTION : copie la table arguments pour NLIN LANGAGE : GIBIANE-CAST3M AUTEUR : Stéphane GOUNAND (CEA/DEN/DM2S/SFME/LTMF) mél :… P:ININLIN
nlin_lapncer (25K) BEGINPROCEDUR gmass NOM : GMASS DESCRIPTION : Une matrice de masse LANGAGE : GIBIANE-CAST3M AUTEUR : Stéphane GOUNAND (CEA/DEN/DM2S/SFME/LTMF) mél :… P:@POMI,@STBL,ININLIN,POINTCYL
nlin_lapnssphe_3d (21K) BEGINPROCEDUR gmass NOM : GMASS DESCRIPTION : Une matrice de masse LANGAGE : GIBIANE-CAST3M AUTEUR : Stéphane GOUNAND (CEA/DEN/DM2S/SFME/LTMF) mél :… P:@POMI,@STBL,ININLIN,POINTSPH
nlin_lapnssphe_axi (20K) BEGINPROCEDUR gmass NOM : GMASS DESCRIPTION : Une matrice de masse LANGAGE : GIBIANE-CAST3M AUTEUR : Stéphane GOUNAND (CEA/DEN/DM2S/SFME/LTMF) mél :… P:@POMI,@STBL,ININLIN,POINTCYL
nlin_tailmail (5K)  P:ININLIN
nloc1 (4K) construction de connectivites sur des domaines differents mesh12=1/4 de disque, mesh1 et mesh2=1/2 disque et mesh=disque complet, avec ou sans symetrie de tel facon que…
nloc2 (4K) construction de connectivites sur des domaines differents mesh12=1/4 de cylindre, mesh1 et mesh2=1/2 cylindre et mesh=cylindre complet, avec ou sans symetrie de tel…
notice (1K) vérification que tous les opérateurs ont bien une notice. idem pour les procédures.
objet (2K) 
operad (2K) Cas test pour la deuxième syntaxe de l'operateur + list chpr;
optidens (1K) NOM : OPTIDENS DESCRIPTION : Test de 'OPTI' 'DENS' (fiche 7995). LANGAGE : GIBIANE-CAST3M AUTEUR : Stéphane GOUNAND (CEA/DEN/DM2S/SFME/LTMF) mél :…
ordo_1 (7K) CAS-TEST DE VERIFICATION DU FONCTIONNEMENT DE L'OPERATEUR ORDO ET DE TOUTES SES OPTIONS (HORS 'COUT' => VOIR ORDO_2.DGIBI) GRAINE POUR LE GENERATEUR ALEATOIRE
plexus1 (3K) CAS TEST DU 92/01/16 PROVENANCE : PLA2 Test plexus1.dgibi: jeux de données SI GRAPH = N PAS DE GRAPHIQUE AFFICHE SINON SI GRAPH DIFFERENT DE N TOUS LES GRAPHIQUES SONT… ext:plexus1.couplage
posi (1K) NOM : POSI DESCRIPTION : Non regression pour l'operateur POSI LANGAGE : GIBIANE-CAST3M AUTEUR : Stéphane GOUNAND (CEA/DEN/DM2S/SFME/LTMF) mél : stephane.gounand@cea.fr…
proi (4K) Projection de champs Syntaxe : 1) Champ par point aux noeuds du maillage GEO2 2) Champ par element aux noeuds ou pt d'integration de MOD2 3) Projection au sens des…
puevol (7K) Cas-test de l'operateur '**' Ce cas-test verifie l'elevation a la puissance d'un objet de type EVOLUTION : 1. Elevation a la puissance ENTIERE POSITIVE ; 2. Elevation a…
redumode (4K) démonstration pour reduire le nombre de modèles trac sig motot matot; P:PASAPAS
relamili (5K) Cas-test de l'operateur 'RELA', option 'MILI'. On deplace le coin sup. droit d'un carre (cube en 3D) decrit par un un element quadratique. Le deplacement des noeuds…
relaunil (6K) test de trois poutres parralleles encastrées a une extremite ayant des relations de contact unilaterales avec jeux P | |________________\|/_________________________ | |…
sens (1K) FICHIER DGIBI POUR TESTER L'OPERATEURR SENS Arnaud de Gayffier
sochamevol (8K) Cas-test de l'operateur '-' Ce cas-test verifie la soustraction de MCHAMLs dont les composantes sont de type EVOLUTIOn. Pour avoir les messages, mettre IMES1 a VRAI :
super1 (1K) definition of the mesh points and of the element |2 1 0| definition of the K matrix K=|1 2 1| |0 1 2|
super2 (1K) automatic normalization definition of the mesh points and of the elements
temps (3K) Presentation : Ce cas-test de Verification permet de tester les differentes syntaxes de la directive / operateur TEMP qui mesure des duree.
testkcha (3K) CAS TEST : testkcha.dgibi Cas-Test vérifiant le bon fonctionnement de l'opérateur 'KCHA' dans les deux sens.
test_@deslis (1K) NOM : test_@deslis DESCRIPTION : teste le bon fonctionnement de la procédure @DESLIS LANGAGE : GIBIANE-CAST3M AUTEUR : Pascal Maugis (CEA/DSM/LSCE) mél : pmaugis@cea.fr… P:@DESLIS
test_addition_LIST (8K) Auteur : C. BERTHINIER Date : Novembre 2014 Ce Cas-Test permet de vérifier que les opérations '+' et '-' sur les {LISTENTI, LISTREEL} avec {LISTENTI, LISTREEL, ENTIER,…
test_dess (4K) Teste quelques fonctionnalités décoratives de DESSIN Mettre GRAPH a VRAI pour tracer a l'ecran, sinon tracer dans un .ps
test_diff (4K) Ce Cas-Test vérifie le bon fonctionnement de l'opérateur DIFF Cas de MELEME SIMPLE de TYPE identiques
test_extr (1K) CAS TEST : test_extr.dgibi Ce test permet de vérifier le bon fonctionnement de l'operateur EXTR dans le cas des OBJETS MMODEL et MCHAML vides. Ces opérations…
test_intgeo (11K) teste l'option GEOM de l'operateurINTE
test_point_supe (5K) TEST TEST_POINT_SUPE Type : Verification & Validation (solution analytique) Description : Ce JDD verifie et valide la syntaxe 3 de l'operateur POIN qui permet d'extraire…
test_trac (2K) Teste TRAC avec les nouvelles couleurs Mettre GRAPH a VRAI si trace en interactif, sinon trace en Postscript P:ANIME
test_trachist (2K) CAS TEST : test_trachist.dgibi Test des procédures TRACHIT et TRACHIS P:DESTRA,TRACHIS,TRACHIT
test_verm (2K) Teste l'opérateur VERM TEST DES DOUBLONS en 2D :
tracisov (3K) NOM : TRACISOV DESCRIPTION : Le but de ce cas-test est de tester le trace d'isovaleurs pour les diverses options et sorties. Malheureusement, on ne peut tester le bon…
tria (10K) tria.dgibi : CAS TEST de l'operateur TRIA Triangulation de Delaunay d'un maillage de points (type POI1). On teste plusieurs cas : en 1D, 2D et 3D, avec, a chaque fois :… P:@REPERE
trj_met (7K) NOM : TRJ_MET DESCRIPTION : Test élémentaire Résidu et Jacobien avec métrique pour 'DEDU' 'ADAP' LANGAGE : GIBIANE-CAST3M AUTEUR : Stéphane GOUNAND… P:DEADFONC,DEADKTAN,DEADRESI
trj_regu (7K) NOM : TRJ_REGU DESCRIPTION : Test élémentaire Résidu et Jacobien pour méthode de régularisation de maillage en toute dimension d'espace (opérateur 'DEDU' option 'ADAP')… P:DEADFONC,DEADKTAN,DEADRESI
t_char (2K) TEST CHAR, TIRE, LIST, EXTR, EXIS extension CHARGEMENT LIE / LIBRE, STAT/ROTA,TRAN,TRAJ
vide (3K) NOM : VIDE DESCRIPTION : Quelques tests sur les objets vides suite à la fiche 7810 (Bug de RESULT, POIN et CHAN 'CHAM') LANGAGE : GIBIANE-CAST3M AUTEUR : Stéphane…
voro2d (3K) fichier voro2d.dgibi voro3d.dgibi est un exemple d'utilisation dans un cas bidimensionel de la procedure MAILVORO de maillage d'agregats cubiques de polyedres de… P:@POINTIR,MAILVORO
voro2dp (8K) fichier voro2dp.dgibi voro3d.dgibi est un exemple d'utilisation dans un cas bidimensionel de la procedure MAILVORO de maillage d'agregats cubiques de polyedres de… P:MAILVORO
voro3d (5K) voro3d.dgibi est un exemple d'utilisation dans un cas tridimensionel de la procedure MAILVORO de maillage d'agregats cubiques de polyedres de Voronoi. Cette procedure… P:@POINTIR,MAILVORO
voro3dp (6K) voro3d.dgibi est un exemple d'utilisation dans un cas tridimensionel de la procedure MAILVORO de maillage d'agregats cubiques de polyedres de Voronoi ponderes. Cette… P:MAILVORO
xpetit_xgrand_xzprec (1K) Teste les OPTIONS suivantes : Recuperation de XGRAND,XPETIT et XZPREC (Voir CCOPTIO.INC) qui sont des valeurs dependant machine Ces valeurs peuvent être redefinies avec…

## Magnetodynamique Magnetodynamique (5)
c2d93 (11K) 2D AXISYMMETRIC MAGNETIC FIELD COMPUTATION Formulation : VECTOR POTENTIAL NON LINEAR MATERIAL P:DESCOUR,H_B,INDUCTIO,MAG_NLIN,POT_VECT,RAY
c3d93 (13K) 3D MAGNETIC FIELD COMPUTATION 2 POTENTIALS METHOD REDUCED POTENTIAL (VOLUME CONTAINING INDUCTORS) TOTAL POTENTIAL (VOLUME WHITHOUT CURRENTS ) P:H_B,MAG_NLIN,POT_SCAL
cfpflu (899K) repertoire des fichiers "divers" @ACBLM P:@COUTOR1,@COUTOR2,@FRENET,@REPERE,DDFOUR,DESCOUR,DUPONT2,FORBLOC,FOR_CONT,F_S2PI,H_B,INDUCTIO,INT_COMP,IN_MINI,MAG_NLIN,POT_SCAL,POT_VECT,RESEAU,TRANSFER,TRANSIT1 ext:champbred,flux1mwmo
rotplaq (2K) SAUV S3; CAS ROTATION P:RAY
symplaq (2K) SAUV S3; CAS SYMETRIE : CHANGEMENT D'ORIENTATION P:RAY

## Maillage Autres (16)
chan_poi1_lenti (1K) Test manu_lenti.dgibi : Jeux de données CAS TEST DU 2016/06/09 Cas-test de Verification pour la syntaxe : MAIL2 = CHAN 'MOT1' MAIL1 LENTI1 ; Le LISTENTI LENTI1 contient…
cont (4K) NOM : CONT DESCRIPTION : Quelques cas-tests pour l'operateur CONT Cas 1 : avant la fiche 9607, le résultat contenait des noeuds nuls. Cas 2 : avant la fiche ????,…
dedu_ghia (69K) NOM : DEDU_GHIA DESCRIPTION : Calcul de la cavité carrée à paroi défilante (Navier-Stokes incompressible) pour plusieurs nombres de Reynolds et comparaison avec les… P:DEADUTIL,ININLIN
dedu_vahl (60K) NOM : DEDU_VAHL DESCRIPTION : Calcul de la cavité carrée différentiellement chauffée (Navier-Stokes incompressible + Energie) pour plusieurs nombres de Rayleigh et… P:DEADUTIL,ININLIN
ETG_MELEME (3K) Test ETG_MELEME.dgibi: Jeux de données CAS TEST DU 2017/03/29 SI GRAPH = N PAS DE GRAPHIQUE AFFICHE SINON SI GRAPH DIFFERENT DE N TOUS LES GRAPHIQUES SONT AFFICHES
isov (14K) NOM : ISOV DESCRIPTION : Cas-test élémentaire pour l'opérateur ISOV LANGAGE : GIBIANE-CAST3M AUTEUR : Stéphane GOUNAND (CEA/DEN/DM2S/SFME/LTMF) mél :… P:@ISOSURF
joi1_lie_1 (8K) Cas test sur la mise a jour des vecteurs orientant les elements JOI1 avec FORM Un element JOI1 est considere, ses 6 ddl sont soumis a une serie de deplacements et…
mato-2d1 (10K) NOM : MATO-2D1 DESCRIPTION : Test du MAilleur TOpologique pour mailler un simple carré 10x10 de manière régulière. On teste la qualité des éléments obtenus. On améliore… P:DEDUADAP,MAILTOPO,MATOUTIL
mato-2d2 (13K) NOM : MATO-2D2 DESCRIPTION : Test du MAilleur TOpologique pour mailler un carré avec raffinement isotrope dans un coin. On teste la qualité des éléments obtenus dans la… P:DEDUADAP,MAILTOPO,MATOUTIL
mato-2d3 (9K) NOM : MATO-2D3 DESCRIPTION : Test du MAilleur TOpologique pour mailler un carré de avec une métrique anisotrope constante en espace dans le but d'obtenir 10x20 mailles,… P:DEDUADAP,MAILTOPO,MATOUTIL
mato-2d4 (6K) NOM : MATO-2D4 DESCRIPTION : Test du MAilleur TOpologique pour mailler un carré avec une métrique isotrope constante en espace dans le but d'obtenir 10x10 mailles. Au… P:MATOUTIL
q4ri_bcn (2K) TEST Q4RI BCN Verification of element Q4RI (QUA4 with 1x1 Gauss points) Elastic analysis of a square subjected to biaxial extension
raft1 (4K) NOM : RAFT1 DESCRIPTION : Exemple d'utilisation de RAFT : Maillage d'un carré avec un fort raffinement dans un des coins. On teste les tailles de mailles obtenues par…
testlgQUAF (1K) On teste le bon fonctionnement de l'option ARETE de DOMA. Ceci necessite la bonne description des lignes et des faces des elements QUAF EN 2D QUA9 et TRI7
test_para (5K) NOM : test_para DESCRIPTION : Test de "PARA N1 P1 P2 P3" avec N1 > 0 Verification & Validation (analytique) LANGAGE : GIBIANE-CAST3M AUTEUR : kk2000 mél : kk2000@cea.fr…
volu (3K) NOM : VOLU DESCRIPTION : Cas-test pour l'operateur VOLU. Cas 1 : On cherche à mailler en tétraèdres un cube moins un cylindre. Avec les paramètres nx = 3 ; rcyl = 0.88 ;…

## Mathematiques Autres (1)
frenet_1 (7K) VERIFICATION DE L'OPERATEUR FRENET LIGNE DROITE, CERCLE, ELLIPSE, CYCLOIDE, SPIRALE HELICE VERIFICATION EN DIMENSION 2

## Mathematiques Elementaires (2)
adchamevol (8K) Cas-test de l'operateur '+' Ce cas-test verifie l'addition de MCHAMLs dont les composantes sont de type EVOLUTIOn. Pour avoir les messages, mettre IMES1 a VRAI :
proi-parallele (2K) NOM : PROI-PARALLELE DESCRIPTION : On teste le parallélisme avec les assistants pour faire un PROI en parallèle LANGAGE : GIBIANE-CAST3M AUTEUR : Stephane GOUNAND…

## Mathematiques Fonctions (88)
ajuste1 (2K) exemple d'utilisation de la procedure AJUSTE on cherche a identifier les parametres a,b,c,d de la fonctions y = a * (log ( (b*x) + c) ) + (exp (d*x)) on part d'un jeu de… P:AJUSTE
ajuste2 (3K) EXEMPLE : On cherche a interpoler un nuage de points avec la fonction suivante: the given sets of points ( x , f(x)) must be adjusted with a function as follows : f(x)… P:AJUSTE
bruipois (5K) Cas test de l'operateur 'BRUI', option 'POIS' Ce cas-test verifie la valeur moyenne de variables distribuees suivant une disribution de Poisson que fournit l'operateur…
cmct1 (6K) CAST TEST PORTANT SUR L'OPÉRATEUR CMCT et l'opérateur Principe : On considère une matrice formée de l'assemblage de matrice de blocage nuls cl1 et cl2 d'une matrie de…
condense1 (4K) CAST TEST PORTANT SUR L'OPÉRATEUR SUPE Principe : On considère une matrice formée de l'assemblage d'une matrice de rigidité rig1 de matrice de blocage nuls cl1 et cl2…
conversion_enti (9K) NOM : conversion_enti.dgibi DESCRIPTION : Comparaison entre les differentes fonctions pour convertir un reel en entier MOTS-CLÉS : troncature,partie…
cpliq (2K) CAS TEST : cpliq.dgibi Test de l'opérateur 'VARI' 'CPLIQ'(P,H) Les données sont un FLOTTANT, un LISTREEL ou un CHPO
excel1 (4K) excel1.dgibi deux methode sont proposees dans l'opérateur exce : la methode standard ( minimisation convexe) avec t0 = 0.6; la methode move limite; on trace aussi sur…
excel2 (5K) excel2.dgibi deux methode sont proposees dans l'opérateur exce : la methode standard ( minimisation convexe) avec t0 = 0.6; la methode move limite; analyse de fiabilite.…
excel3 (10K) Test de l'opérateur EXCE : Méthode des Asymptotes Mobiles Reproduction d'un cas test de l'article originel de Svanberg Krister Svanberg: The method of moving asymptotes…
excel4 (10K) Test de l'opérateur EXCE : Méthode des Asymptotes Mobiles Reproduction d'un cas test de l'article originel de Svanberg Krister Svanberg: The method of moving asymptotes…
excel5 (9K) Test de l'opérateur EXCE : Méthode des Asymptotes Mobiles On considère une boite de conserve cylindrique de rayon r et de hauteur h et devant contenir un volume de 1000…
exemple_borner (3K) EXEMPLES D'UTILISATION DE L'OPERATEUR BORNER : EVOLUTION :
ffor-axi (5K) ......../........./........./........./........./........./........./72 Calcul de facteurs de forme en axisymétrique pour une cavite comportant un jeu Comparaison a des…
fiabi1 (10K) Test fiabi1.dgibi: Jeux de données CAS TEST DU 01/04/10 PROVENANCE : TEST P:FIABILI,INDIBETA,PARASTAT,QUADRATU
fiabi2 (10K) Test fiabi1.dgibi: Jeux de données CAS TEST DU 01/04/10 PROVENANCE : TEST P:FIABILI,INDIBETA,PARASTAT,QUADRATU
filc_test (1K) Cas test de la procedure FILC Developpe par : Alberto FRAU (alberto.frau[at]cea.fr) Benjamin RICHARD (benjamin.richard[at]cea.fr) Institution :… P:FILC
Fonction_Parallele (10K) OPERATION '**' OPERATION '*'
ftran_test (3K) Cas test de la procedure FTRAN Developpe par : Alberto FRAU (alberto.frau[at]cea.fr) Benjamin RICHARD (benjamin.richard[at]cea.fr) Institution :… P:FTRAN
gamma (3K) Cas-test de VERIFICATION et VALIDATION pour les operateurs GAMM (Fonction Gamma d'Euler) BESS (Fonction Bessel)
grad_01 (10K) Cas-test de l'operateur GRADient pour les elements finis 'BARR' 'TUY2' 'TUY3' Avec les formulations : 'DIFFUSION' 'THERMIQUE' Verification & Validation (non analytique)… P:PASAPAS
hls (2K) CAS TEST : hls.dgibi Test de l'opérateur VARI HLS(P,T) Les données sont un FLOTTANT, un LISTREEL ou un CHPO
hlsat (2K) CAS TEST : hlsat.dgibi Test de l'opérateur VARI HLS(P,TSAT(P)) Les données sont un FLOTTANT, un LISTREEL ou un CHPO
hvs (2K) CAS TEST : hvs.dgibi Test de l'opérateur VARI HVS(P,T) Les données sont un FLOTTANT, un LISTREEL ou un CHPO
hvsat (2K) CAS TEST : hvsat.dgibi Test de l'opérateur VARI HVS(P,TSAT(P)) Les données sont un FLOTTANT, un LISTREEL ou un CHPO
identifi (8K) soit le polynome du 3eme degre y=a*x*x*x + b*x*x + c*x + d on suppose connue la valeur d'une fonction G pour les abscisses x= 1, 2, 3, 4 et 5 .On recherche les… P:AJUSTE
invdiag (9K) OPERATEURS 'KOPS' et 'KRES' P:DEDANS
invide (8K) OPERATEURS 'KOPS' et 'KRES' P:DEDANS
ipol1 (1K) Fichier DGIBI pour tester l'operateur 'IPOL' avec un nuage la methode utilisée est celle des éléments finis diffus avec des polynomes d'ordre 1 l'interpolation de toutes…
ipol2 (4K) NOM : IPOL2 DESCRIPTION : Tester IPOL sur un réel. LANGAGE : GIBIANE-CAST3M AUTEUR : Stéphane GOUNAND (CEA/DEN/DM2S/SFME/LTMF) mél : gounand@semt2.smts.cea.fr VERSION :…
ipolspli (2K) NOM : IPOLSPLI DESCRIPTION : Compare les différentes interpolations d'une fonction Linéaire et Spline. LANGAGE : GIBIANE-CAST3M AUTEUR : Stéphane GOUNAND…
ipol_muli_1 (9K) Test de l'operateur IPOL option GRILL interpolation multi-lineaire d'une fonction de n parametres definie sur une grile de points - test avec fonction de 1, 2, 3 et 4…
ipol_muli_2 (5K) Test de l'operateur IPOL option GRILL interpolation multi-lineaire d'une fonction de n parametres definie sur une grile de points Application a l'interpolation d'un…
isosurf (5K) CAS TEST : isosurf.dgibi TEST @ISOSURF ISOSURFACES POUR MAILLAGE DE TETRAHEDRES Test de la procedure qui extrait les isosurfaces dont les valeurs sont listées dans une… P:@ISOSURF
latent (2K) CAS TEST : latent.dgibi Test de l'opérateur VARI LATENT(P) Les données sont un FLOTTANT, un LISTREEL ou un CHPO
mat_carrees_exce (8K) TONUS - multicompartiments Version 0.0 - décembre 95 MATRICES ELEMENTAIRES CARREES (avec pénalisation de la diagonale) CAS-TEST 1 3 compartiments - 2 jonctions 3 O / X…
maxi (4K) Mots-clés : MAXI, MANU 'CHPO' Test de verification de les operateurs MAXI et MANU 'CHPO'
mucham (7K) NOM : MUCHAM DESCRIPTION : Cas-test de l'operateur '*' (et '/') Ce cas-test verifie la multiplication et la division de MCHAMLs Suite aux fiches anomalie 9461, 9474 on…
nlin_lapnpara (4K) NOM : NLIN_LAPNPARA DESCRIPTION : Test tout simple sur un laplacien construit en parallèle ou en séquentiel On vérifie l'écart à la solution analytique dans les deux… P:ININLIN
normalisation-1 (1K) Points ... Raideurs ...
normalisation-2 (1K) Points ... Raideurs ...
parallelisation_CHPOINT (10K) Cas-Test de Verification : Operations Elementaires CHPOINTS Ce cas test permet de verifier le bon fonctionnement de la parallelisation des operations elementaires…
pente1 (4K) APPROCHE VF "Cell-Centred Formulation". OPÉRATEUR PENT, pour le calcul des gradients et des limiteurs Cas test: calcul du gradient reconstruction linéaire exacte A.…
pente2 (9K) APPROCHE VF "Cell-Centred Formulation". OPÉRATEUR PENT, pour le calcul des gradients et de limiteurs Cas test: calcul du limiteur A. BECCANTINI, TTMF MAI 1998
pente3 (4K) APPROCHE VF "Cell-Centred Formulation". OPÉRATEUR PENT, pour le calcul des gradients et des limiteurs Cas test: calcul du gradient avec conditions de typr mur A.…
pente3D (24K) Finite Volume, "Cell-Centred Formulation". PENT, operator to compute gradients and limiters 3D VALIDATION T. KLOCZKO, LTMF JULY 2005 Choix du type d'élément
plus1 (2K) NOM : PLUS1 DESCRIPTION : Test de non-régression de '+' sur les CHPOINTs Avant la fiche 5834, ce test donnait une erreur. LANGAGE : GIBIANE-CAST3M AUTEUR : Stéphane…
Pres_Mass (1K) Test Pres_Mass.dgibi: Jeux de données Auteur : CB215821
probdef (4K) CAS TEST PROBDEF CALCUL IDEALISE D UNE PROBABILITE DE DEFAILLANCE Probabilite qu une resistance (R) soit inferieure a une sollicitation (S) R et S sont des variables… P:INDIBETA,PARASTAT,PROBABRS,QUADRATU
prodt (1K) Teste la procedure PRODT production d'energie turbulente Cas ou dt/dz >0 est de meme signe que gb Stratification instable => G=0. P:PRODT
prod_CHPOINT (7K) SI GRAPH = N PAS DE GRAPHIQUE AFFICHE SINON SI GRAPH DIFFERENT DE N TOUS LES GRAPHIQUES SONT AFFICHES
proi1 (4K) NOM : PROI1 DESCRIPTION : Vérifie que PROI OBJ1 = PROI | GEO2 CHEL1 | redonne presque la valeur exacte pour un champ linéaire et un champ quadratique interpolé sur un…
proi2 (5K) NOM : PROI2 DESCRIPTION : Petit cas-test qui ne fonctionnait pas avant la fiche 5791. Pour l'élément linéaire et quadratique, OK Pour l'élément QUAF, la subroutine qsijs…
prot (3K) Test de la procedure PROT : Projection de Temperature d'un massif sur une coque
prot1 (3K) Test de la procedure PROT : Projection de Temperature d'un massif sur une coque
psatt (2K) CAS TEST : psatt.dgibi Test de l'opérateur VARI PSATT(P) Les données sont un FLOTTANT, un LISTREEL ou un CHPO P:PSATT
puchamevol (10K) Cas-test de l'operateur '**' Ce cas-test verifie l'elevation a la puissance de MCHAMLs dont les composantes sont de type EVOLUTION. 1. Elevation a la puissance ENTIERE…
pvap (2K) CAS TEST : pvap.dgibi Test de l'opérateur VARI PVAP(P,T) Les données sont un FLOTTANT, un LISTREEL ou un CHPO
pvec (3K) NOM : PVEC DESCRIPTION : Cas-test pour l'opérateur PVEC avec des CHPOs On vérifie en 2D : | PVEC A |^2 = | A | ^ 2 | PSCA A (PVEC A) |^2 = 0 et en 3D l'égalité : | PVEC…
pvec2 (5K) NOM : PVEC2 DESCRIPTION : Cas-test pour l'opérateur PVEC avec des MCHAMLs On vérifie en 2D : | PVEC A |^2 = | A | ^ 2 | PSCA A (PVEC A) |^2 = 0 et en 3D l'égalité : |…
pvec3 (3K) NOM : PVEC3 DESCRIPTION : Cas-test pour l'opérateur PVEC avec des POINTS, des CHPOINTS et des CHAMLS On vérifie en 2D : PVEC (1. 0.) = (0. 1.) POUR LES 3 TYPES D'OBJETS…
reso1 (1K) On résoud un petit système linéaire 2x2 avec une relation Ceci a pour but de tester la résolution, y compris lorsque les noms de primales et duales sont égales (noms…
reso_asy (2K) CAS TEST DU 91/06/18 PROVENANCE : PLAF si GRAPH = N, les graphiques ne sont pas affich{s si GRAPH diff{rent de N, tous les graphiques sont affich{s
roliq (2K) CAS TEST : roliq.dgibi Test de l'opérateur VARI ROLIQ(P,H) Les données sont un FLOTTANT, un LISTREEL ou un CHPO
rovap (2K) CAS TEST : rovap.dgibi Test de l'opérateur VARI ROVAP(P,T) Les données sont un FLOTTANT, un LISTREEL ou un CHPO
rovapsat (2K) CAS TEST : rovapsat.dgibi Test de l'opérateur VARI ROVAP(P,TSAT(P)) Les données sont un FLOTTANT, un LISTREEL ou un CHPO
rten (4K) TEST RTEN.DGIBI CAS TEST DE L'OPERATEUR RTENS
simpl1 (1K) Example de maximisation de "Numerical recipes" p 313 maximiser z=x1+x2+3x3-0.5x4 avec x1+2x3 inferieur ou egal a 740 2x2-7x4 inferieur ou egal a 0 x2-x3+2x4 superieur ou…
simpl2 (2K) test du simplex sur un treillis de 3 barres (avec utilisation de la procedure ANLIMTRE) on considere 3 barres pouvant suportees une contrainte limite egale a condlim.… P:ANLIMTRE
testalea (13K) CAS TEST : testalea.dgibi Cas-Test vérifiant le bon fonctionnement de l'opérateur 'ALEA' avec différentes options. Test de la bonne statistique du champ résultat.… P:@ARR,AJUSTE
test_@mod (2K) NOM : test_@mod DESCRIPTION : test le fonctionnement de la procédure @mod LANGAGE : GIBIANE-CAST3M AUTEUR : Pascal Maugis (CEA/DSM/LSCE) mail : pmaugis@cea.fr VERSION :… P:@MOD
test_acos (3K) Teste le bon fonctionnement des opérateurs ACOS, ASIN, ATG et TAN Auteur : P. Maugis, 26/09/2007 Teste ACOS, ASIN, ATG
test_enle (8K) fichier test_enle.dgibi Cas test : test_enle.dgibi Classe : Verification et Validation Teste le bon fonctionnement de l'operateur ENLE sur les objets de type - LISTREEL…
test_fsur (11K) PETIT TEST DE VERIFICATION DE L'OPERATEUR FSUR Mettre IGRAPH a VRAI pour avoir les quelques traces
test_inter (1K) Teste l'opérateur INTER en 2D :
test_kops_cmct (17K) NOM : TEST_KOPS_CMCT DESCRIPTION : On vérifie que KOPS CMCT donne des résultats corrects LANGAGE : GIBIANE-CAST3M AUTEUR : Stéphane GOUNAND (CEA/DEN/DM2S/SFME/LTMF) mél… P:ININLIN
test_kops_ninc (4K) NOM : TEST_KOPS_NINC DESCRIPTION : On vérifie que KOPS donne des résultats corrects avec les options extrninc et extrinco LANGAGE : GIBIANE-CAST3M AUTEUR : Stéphane…
test_uniq (1K) DGIBI test_uniq.dgibi 2013/02/01 Le mot-cle NOCA est ignore (pas d'erreur) meme si mal utilise
tsatp (2K) CAS TEST : tsatp.dgibi Test de l'opérateur VARI TSATP(P) Les données sont un FLOTTANT, un LISTREEL ou un CHPO
t_@PASHIST (3K) Test Procedure @PASHIST IDESS1 = VRAI : dessin actifs : P:@PASHIST
t_HISTOG (37K) Cas-test de l'operateur 'HIST' : Description : HIST renvoie une EVOLUTIOn de type HISTogramme repre- sentant la densite de distribution des valeurs d'un MCHALM sur un…
valitraj (6K) Test de validation de l'opérateur TRAJ on considère un domaine carré dans lequel on se donne un champ de vitesse circulaire. En chaque point le module de la vitesse est… P:@ARR
vari-youn-1 (9K) C'est un k-test dont le but est de tester le fonctionnement de PASAPAS avec la variation des données matérielles. Il s'agit d'une barre en traction simple. Son module de… P:PASAPAS
vari-youn-2-auto (4K) C'est un k-test dont le but est de tester le fonctionnement de PASAPAS avec la variation des données matérielles. Il s'agit d'une barre en traction simple. Son module de… P:PASAPAS
vari-youn-2 (4K) C'est un k-test dont le but est de tester le fonctionnement de PASAPAS avec la variation des données matérielles. Il s'agit d'une barre en traction simple. Son module de… P:PASAPAS
vari-youn-3 (4K) C'est un k-test dont le but est de tester le fonctionnement de PASAPAS avec la variation des données matérielles. Il s'agit d'une barre en traction simple. Son module de… P:PASAPAS
vari-youn-4 (5K) C'est un k-test dont le but est de tester le fonctionnement de PASAPAS avec la variation des données matérielles. Il s'agit d'une barre en traction simple. Son module de… P:PASAPAS
zvap (2K) CAS TEST : zvap.dgibi Test de l'opérateur 'VARI' 'ZVAP'(P,T) Les données sont un FLOTTANT, un LISTREEL ou un CHPO

## Mathematiques Traitement du signal (1)
tfr (4K) Transformee de Fourier rapide (FFT via operateur TFR) et transformee inverse (FFT-1 via operateur TFRI) BP, 2018-10-04 Test de plusieurs signaux nombre de points…

## Mecanique Contact (9)
Contact2D (9K) Ce cas-test permet de tester la gestion du contact par PASAPAS. Il simule la mise en contact, en deplacements imposes, d'un carre sur une surface rigide. Le probleme est… P:PASAPAS
Contact3D (10K) Ce cas-test permet de tester la gestion du contact par PASAPAS. Il simule la mise en contact, en deplacements imposes, d'un cube sur une sol rigide. On impose le… P:PASAPAS
corrig (5K) chute d une structure sur une autre graph = VRAI ; opti trac PSC; P:PASAPAS
cou21 (8K) ----------DEFINITION DE LA GEOMETRIE DU CUBE ---------- ---------- LIGNE ---------- P:JEU,PASAPAS
cou31 (7K) ----------DEFINITION DE LA GEOMETRIE DU CUBE SUPERIEUR---------- ---------- MAILLAGE ---------- P:PASAPAS
Coulomb3D (11K) Ce cas-test permet de tester la gestion du frottement de Coulomb par PASAPAS. Il calcule la mise en contact d'un lopin parallelipedique sur une surface rigide, puis sa… P:PASAPAS
dy_devo2 (7K) VALIDATION DE LA LIAISON POINT-POINT-FROTTEMENT DE DYNE DY_DEVO2.DGIBI ref : Rapport DMT/92.056 de Vare, De Langre reimporte dans la base des cas-test par BP en 2015 P:JEU,LEGENDE,TRADUIRE
frocable (4K) === GEOMETRIES=== P5 = 0 2.5; P6 = 5 2.5; P:PASAPAS
supore (10K) Ce cas-test permet de verifier la gestion du contact La valeur de la densite a mis en evidence des problemes dans le superelement le 13/10/22 P:ANIME

## Mecanique Dynamique (64)
1ddl (2K) Etude d'un système 1 ddl Exemple d'utilisation de OSCI, SPO et SPON D. Combescure aout 2006 GRAPH = VRAI; P:@EXCEL1
A1DDL (4K) EXEMPLE A1DDL.dgibi Entrée : Chargement sismique Sortie : Sans objet Commentaire : Test de la procedure @A1DDL.PROCEDUR Developpeur : Benjamin Richard CEA, DEN, DANS,… P:@A1DDL ext:21time.txt,21axtab.txt
amor (4K) Test de frontiere LYSMER et KULHEMEYER Dans ce test, une onde de compression est generee par une impulsion a une extremite d'une barre maille en elements massifs 3D.… P:DYNAMIC
castest_lse2_litu (3K) Graph = VRAI ; DONNEES GENERALES DU MAILLAGE
drx_flexion_elas (8K) Cas test de la procédure EXPLICIT Calcul de la réponse dynamique d'une plaque axisymétrqiue à une force de type impact sur son centre La réponse est comparée à un calcul… P:DREXUS
drx_impact_anneau (2K) chute et rebond d'un anneau dans un cone rigide calcul drexus explicite avec impact ligne-ligne hypotheses : - materiau elastique lineaire - grandes deformations * | * |… P:ANIME,DREXUS
dyna10 (5K) Test Dyna10.dgibi: Jeux de données Test dyna10.dgibi: jeux de données SI GRAPH = N PAS DE GRAPHIQUE AFFICHE SINON SI GRAPH DIFFERENT DE N TOUS LES GRAPHIQUES SONT…
dyna11 (4K) Test Dyna11.dgibi: Jeux de données REPONSE TRANSITOIRE A UNE PRESSION INTEREN DESCRIPTION DU PROBLEME UN CYLINDRE A PAROIS EPAISSES EST SOUMISE BRUTALEMENT A UNE… P:DYNAMIC
dyna12 (2K) Test Dyna12.dgibi: Jeux de données REPONSE TRANSITOIRE D 'UNE FUSEE -METHODE DIRECT DESCRIPTION DU PROBLEME UNE FUSEE EST SOUMISE A UN CHARGEMENT AXIAL POUR UNE DUREE… P:DYNAMIC
dyna13 (8K) TEST POUR LA SOUS-STRUCTURATION UTILISATION DE BASE (OSCAR...) ASSEMBLAGE DE 2 PLAQUES D. COMBESCURE 30/09/2005 GRAPH = 'O';
dyna14 (11K) Mots-clés : Vibrations, calcul modal, sous-structuration, Craigh-Brampton, dynamique TEST POUR LA SOUS-STRUCTURATION SANS UTILISATION DE BASE Etude d'un ASSEMBLAGE DE 2…
dyna15 (4K) Poteau soumis à une charge concentré Contribution statique des modes négligés D. Combescure aout 2006 AFFICH = VRAI; P:ANIME,DYNAMIC
dyna16 (8K) Portique soumis à un déplacement différentiel des appuis Calcul sur un mode dynamique et les modes statiques D. Combescure aout 2006 GRAPH = VRAI; P:ANIME,DYNAMIC,TRADUIRE
dyna5 (24K) Test Dyna5.dgibi: Jeux de données CAS TEST DU 01/07/92 PROVENANCE : PHIL P:TRADUIRE
dyna6 (5K) Test Dyna6.dgibi: Jeux de données Test dyna6.dgibi: jeux de données SI GRAPH = N PAS DE GRAPHIQUE AFFICHE SINON SI GRAPH DIFFERENT DE N TOUS LES GRAPHIQUES SONT AFFICHES
dyna7 (7K) Test Dyna7.dgibi: Jeux de données Test dyna7.dgibi: jeux de données SI GRAPH = N PAS DE GRAPHIQUE AFFICHE SINON SI GRAPH DIFFERENT DE N TOUS LES GRAPHIQUES SONT AFFICHES
dyna8 (3K) Test Dyna8.dgibi: Jeux de données Test dyna8.dgibi: jeux de données SI GRAPH = N PAS DE GRAPHIQUE AFFICHE SINON SI GRAPH DIFFERENT DE N TOUS LES GRAPHIQUES SONT AFFICHES
dyna9 (3K) Test Dyna9.dgibi: Jeux de données Test dyna9.dgibi: jeux de données SI GRAPH = N PAS DE GRAPHIQUE AFFICHE SINON SI GRAPH DIFFERENT DE N TOUS LES GRAPHIQUES SONT AFFICHES
dynacontact (4K) maillage, modele et matrices appel a dynamic (schema de Newmark acceleration moyenne) P:DYNAMIC,PASAPAS
dyna_nl1 (3K) Test Dyna_nl1.dgibi: Jeux de données pour calcul complet mettre complet à : vrai; dynamique non lineaire geometrique oscillations libres d'un oscillateur de type Duffing… P:PASAPAS
dyna_nl2 (4K) pour calcul complet mettre complet à : vrai; dynamique non lineaire geometrique reponse forcee d'un oscillateur de type Duffing comparaison avec calcul explicite P:PASAPAS
dyna_nl3 (7K) Test Dyna_nl3.dgibi: Jeux de données pour calcul complet mettre complet à : vrai; TEST DES LA PRESSION SUIVEUSE EN DYNAMIQUE FLOTTEMENT D'UNE POUTRE ENCASTREE-LIBRE On… P:ANIME,PASAPAS
dyna_nl4 (5K) CALCUL DU REBOND D'UNE BARRE AVEC PASAPAS ET RELA D. COMBESCURE AOUT 2006 GRAPH = VRAI; COMPLET = VRAI; P:PASAPAS
dyne01 (6K) Test Dyne01.dgibi: Jeux de données Test dyne01.dgibi P:JEU
dyne02 (8K) Impact d'une barre elastique sur un plan rigide : p1 p2 p2b -> <-> P=M*g JeuLiai=0.01 Calcul sur base modale via l'operateur DYNE P:JEU
dyne03 (6K) EXEMPLE D'UTILISATION DE L'OPERATEUR DYNE Rupture de tuyauterie avec impact Calcul sur base modale avec raideur de choc Opérateur Dyne D. Combescure Aout 2006 GRAPH =… P:ANIME,JEU
dy_dev10 (13K) Cas-Test de la liaison palier de l'operateur DYNE Arbre rigide L=1m sur 2 paliers cylindriques Chargement statique des paliers Fz = 1000 N Auteur : Inconnu P:PASAPAS
dy_dev11 (12K) Cas-Test de la liaison palier de l'operateur DYNE Masse ponctuelle sur 1 palier a 3 lobes Chargement statique des paliers Fz = -784 N Auteur : Inconnu
dy_devo5 (6K) Test Dy_devo5.dgibi: Jeux de donn�es REPONSE TRANSITOIRE D'UNE POUTRE -METHODE MODALE DESCRIPTION DU PROBLEME UNE POUTRE EST MONTEE SUR DES APPUIS ELASTIQUES . SUPPOSANT… P:PASAPAS,PECHE
dy_devo6 (7K) Test Dy_devo6.dgibi: Jeux de donn�es DYNE LIAISON POIN_PLAN avec plastification du ressort de choc il s'agit d'une grande masse anim�e d'un mouvement sinusoidale (avec… P:JEU,PASAPAS
dy_devo7 (8K) poutre sous charge mobile barre P:PASAPAS
dy_devo8 (12K) Test Dy_devo8.dgibi: Jeux de donn�es PROBL�ME Test de Comparaison entre les liaisons point_cercle_mobile et point_ligne . Impact d'une but�e sur un cercle mobile . P:PASAPAS
dy_devo9 (9K) TEST DE VALIDATION DE LA LIAISON LIGNE_LIGNE DE DYNE Un disque chute sur le sol sous l'action de la pesanteur Comparaison des vitesses apres le choc avec la solution… P:ANIME,PASAPAS
newmark1 (2K) Ce cas test verifie que le bilan energetique en dynamique est correct Verification en comportement et en choc P:PASAPAS
newmod (22K) chute d'une barre dans un conduit uniforme comparaison liaison point_plan_frottement et calcul analytique ; ==> exploitation nombre de choc et temps de chute P:JEU,NEWMARK,PASAPAS,POSTVIBR
reacdyna (2K) calcul d'un ressort avec une masse au bout par la procedur dynamic k=2000 m=100 v0=100 P:DYNAMIC
rotor1 (9K) Mots-clés : Vibrations, calcul modal, machines tournantes, poutre, modes complexes, reponse frequentielle Test de GYROSCOPIQUE et CAMPBELL pour les elements de poutre… P:CAMPBELL,LEGENDE,POUT2MAS
rotor2 (8K) Mots-clés : Vibrations, calcul modal, machines tournantes, poutre, modes complexes, reponse frequentielle Test de GYROSCOPIQUE, CAMPBELL et BALOURD pour les elements de… P:BALOURD,CAMPBELL,POUT2MAS
rotor3 (9K) Mots-clés : Vibrations, calcul modal, machines tournantes, poutre, modes complexes, reponse frequntielle Test de GYROSCOPIQUE, CAMPBELL et BALOURD pour les elements de… P:BALOURD,CAMPBELL,POUT2MAS
rotor4 (13K) Mots-clés : Vibrations, calcul modal, machines tournantes, poutre, modes complexes Test de GYROSCOPIQUE, AMOR, CAMPBELL pour les elements de poutre Etude d'une machine… P:CAMPBELL,POUT2MAS
rotor5 (20K) Mots-cl�s : Vibrations, calcul modal, machines tournantes, poutre, condensation statique, dynamique reconstruction 3D, modes complexes Etude d'une machine tournante dans… P:BALOURD,CAMPBELL,DYNAMIC,POUT2MAS
rotor6 (9K) Mots-clés : Vibrations, calcul modal, machines tournantes, 3D, flambage, precontrainte rotor6.dgibi Cas test basé sur rotor2.dgibi [Exemple Lalanne P.13] Modélisation 3D… P:@REPERE,EXPLORER
rotor7 (28K) rotor7.dgibi Cas test basé sur rotor2.dgibi et rotor6.dgibi [Ex. Lalanne p.13] Modélisation 3D : rotor dans le repère tournant stator dans le repere fixe B. Prabel,… P:@REPERE,PASAPAS
sissi (7K) Test sissi.dgibi: jeux de données SI GRAPH = N PAS DE GRAPHIQUE AFFICHE SINON SI GRAPH DIFFERENT DE N TOUS LES GRAPHIQUES SONT AFFICHES P:SISSIB
spectral (10K) Mots-clés : Vibrations, calcul modal, modes statiques, poutre reponse frequentielle calcul spectral sans/avec amortissement, base modale seule. auteur : JK / a parfaire P:PASAPAS
sta2d (7K) PROGRAMMME STATIONNAIRE 2D 29/11/1998 Marta DRAGON/LMS-Ecole Polytechnique RAIL SOUMIS AU PASSAGE D'UNE ROUE : chargement mobile, de type Hertz on cherche l'etat… P:@STATIO
test_deconv1 (100K) Test pour la procedure DECONV On procede a deconvoluer une onde S sur une colonne de sol jusqu'à la profonduer de 20 metres. Le signal est imposé au free field Les… P:DECONV
test_deconv2 (101K) Test pour la procedure DECONV On procede a convoluer une onde S sur une colonne de sol jusqu'à la surface libre. Le signal est imposé à -20 metres de profonduer Les… P:DECONV
trac3d (5K) Mots-clés : Vibrations, calcul modal, coque, 2D Fourier, Reconstruction 3D TEST TRAC3D P3 | | | | | | | ______________| P1 P2 Soit un cylindre dont on calcule la… P:CREER_3D
tristru (11K) Mots-clés : Vibrations, calcul modal, modes statiques, poutre test sous-structuration 3 poutres auteur : JK
vibr10 (3K) Mots-clés : Vibrations, calcul modal, machines tournantes, reponse frequentielle Calcul de la reponse au balourd
vibr11 (7K) VIBR11.dgibi Objectif : Calcul des modes propres d'un tube mince isotrope axisymetrique encastre - encastre Elements : solide-coque SHB8 et coque mince DKT + coque… P:POSTVIBR
vibr12 (14K) Mots-cles : Vibrations, calcul modal, modes complexes, interaction fluide-structure, instabilite TEST : VIBR12 CALCUL D INSTABILITE FLUIDE-ELASTIQUE SOUS ECOULEMENT… P:LEGENDE,POSTVIBR
vibr13 (5K) Mots-clés : Vibrations, calcul modal, precontrainte, poutre, 3D CALCUL DES FREQUENCES D UNE POUTRE EN FLEXION ENCASTREE-LIBRE SOUMISE A UNE EFFORT DE TRACTION DE 150 N…
vibr14_3d (5K) VIBR14_3D.dgibi Objectif : Calcul des modes propres d'un tube mince orthotrope axisymetrique encastre - encastre Elements : coque mince DKT P:POSTVIBR
vibr14_fourier (8K) VIBR14_FOURIER.dgibi Objectif : Calcul des modes propres d'un tube mince orthotrope axisymetrique encastre - encastre Elements : coque mince COQ2, et massif QUA8 P:FOUR2TRI,POSTVIBR
vibr2 (6K) Test vibr2.dgibi: Jeux de données Test vibr2.dgibi: jeux de données SI GRAPH = N PAS DE GRAPHIQUE AFFICHE SINON SI GRAPH DIFFERENT DE N TOUS LES GRAPHIQUES SONT AFFICHES
vibr3 (5K) Test vibr3.dgibi: Jeux de données Test vibr3.dgibi: jeux de données SI GRAPH = N PAS DE GRAPHIQUE AFFICHE SINON SI GRAPH DIFFERENT DE N TOUS LES GRAPHIQUES SONT AFFICHES
vibr4 (8K) Test vibr4.dgibi: jeux de données SI GRAPH = N PAS DE GRAPHIQUE AFFICHE SINON SI GRAPH DIFFERENT DE N TOUS LES GRAPHIQUES SONT AFFICHES P:EXPLORER
vibr5 (5K) Test vibr5.dgibi: jeux de données SI GRAPH = N PAS DE GRAPHIQUE AFFICHE SINON SI GRAPH DIFFERENT DE N TOUS LES GRAPHIQUES SONT AFFICHES
vibr6 (9K) Mots-clés : Vibrations, calcul modal, modes complexes, interaction fluide-structure, instabilite , tuyau, 3D TEST : VIBR6 Modele de PAIDOUSSIS & ORTOJA-STARZEWSKI On…
vibr7 (9K) Mots-clés : Vibrations, calcul modal, modes complexes, interaction fluide-structure, tuyau, 3D TEST : VIBR7 Modele de CONNORS - BLEVINS Calcul des modes propres…
vibr8 (9K) Mots-clés : Vibrations, calcul modal, flambage, modes complexes, forces suiveuses, flottement, tuyau, 3D TEST : VIBR8 Calcul des modes propres complexes d'un arbre… P:FLAMBAGE
vibr9 (5K) Mots-clés : flambage, modes complexes, forces suiveuses, flottement TEST : VIBR9 Calcul des modes propres complexes d'une structure soumise a une force suiveuse (la…

## Mecanique Elastique (101)
beton (5K) Test Beton.dgibi: Jeux de données CAS TEST DU 93/01/19 PROVENANCE : NAH P:PASAPAS
bide2tract (10K) MODELE HYPERELASTIQUE BIDERMAN INCOMPRESSIBLE EN GRANDES TRANSFORMATIONS - CONTRAINTES PLANES TEST DE VALIDATION DU MODELE : TRACTION BIAXIALE DANS LE PLAN X,Y… P:PASAPAS
bidecis (10K) MODELE HYPERELASTIQUE BIDERMAN INCOMPRESSIBLE EN GRANDES TRANSFORMATIONS - CONTRAINTES PLANES TEST DE VALIDATION DU MODELE : CISAILLEMENT DANS LA DIRECTION X COMPARAISON… P:PASAPAS
bidetract (10K) MODELE HYPERELASTIQUE BIDERMAN INCOMPRESSIBLE EN GRANDES TRANSFORMATIONS - CONTRAINTES PLANES TEST DE VALIDATION DU MODELE : TRACTION SELON LA DIRECTION Y COMPARAISON… P:PASAPAS
Cast_test_RelaCoq (2K) Tranfert of load for shell elements - load known for a solid model D. COMBESCURE F4E - 6th January 2014 P:COQ2MAS,TRANSFER
Cast_test_RelaPout (3K) Tranfert of load for beam elements - load known for a solid model D. COMBESCURE F4E - 6th January 2014 P:POUT2MAS,TRANSFER
cham_vari (1K) exemple d'utilisation de REDU gén&éralisé pour créer un grand champ associé à un modèle
channeldie1 (6K) C H A N N E L D I E 1 . D G I B I Objet : Cas-test de validation des elements BBAR pour les CUB8 et PRI6. Calcul elastique de la compression d'un lopin de metal place…
channeldie2 (6K) C H A N N E L D I E 2 . D G I B I Objet : Cas-test de validation des elements BBAR pour les CU20 et PR15. Calcul elastique de la compression d'un lopin de metal place…
channeldie3 (7K) C H A N N E L D I E 3 . D G I B I Objet : Cas-test de validation des elements BBAR pour les elements tetra- edre, pyramide et hexaerdre lineaires. Calcul elastique de la…
channeldie4 (6K) C H A N N E L D I E 4 . D G I B I Objet : Cas-test de validation des elements BBAR pour l'element tetraedre quadratique. Calcul elastique de la compression d'un lopin de…
channeldie5 (6K) C H A N N E L D I E 4 . D G I B I Objet : Cas-test de validation des elements BBAR pour les elements tetra- - edre, pyramide et hexaerdre quadratiques. Calcul elastique…
comp1 (5K) CYLINDRE COMPOSITE BICOUCHE FIBRES ENROULEES -45/+45 AUTOUR DE L'AXE PRESSION INTERNE Un cylindre bloqué à sa base en déplacement suivant l'axe Z est soumis à une…
comp1_fourier (4K) CYLINDRE COMPOSITE BICOUCHE FIBRES ENROULEES -45/+45 AUTOUR DE L'AXE PRESSION INTERNE Un cylindre bloqué à sa base en déplacement suivant l'axe Z est soumis à une…
comp2 (3K) Test Comp2.dgibi: Jeux de données SI GRAPH = N PAS DE GRAPHIQUE AFFICHE SINON SI GRAPH DIFFERENT DE N TOUS LES GRAPHIQUES SONT AFFICHES
cou22 (4K) ----------DEFINITION DE LA GEOMETRIE DU JOINT ---------- ---------- LIGNE ---------- P:PASAPAS
drop (100K) NOM : DROP DESCRIPTION : Une goutte plane ou axi soumise à la gravité et à la tension de surface. Contraintes : on fixe le Delta P ou le Volume on fixe la position des… P:@STBL,DEADJACO,DEADUTIL,ININLIN,TENSION
drx_grd_defo_cisail_elas (3K) CAS TEST POUR LES GRANDES DÉFORMATIONS on considère un test de traction sur un rectangle en 2D deformation planes comparaison avec plexus P:DREXUS
dy_devo3 (20K) Test Dy_devo3.dgibi: Jeux de donn�es si GRAPH = N, les graphiques ne sont pas affich�s si GRAPH diff�rent de N, tous les graphiques sont affich�s P:JEU,PASAPAS,USURE
dy_devo4 (14K) Test Dy_devo4.dgibi: Jeux de donnees si GRAPH = N, les graphiques ne sont pas affiches si GRAPH different de N, tous les graphiques sont affiches P:JEU,PASAPAS
elas1 (3K) Test elas1.dgibi: Jeux de données SI GRAPH = N PAS DE GRAPHIQUE AFFICHE SINON SI GRAPH DIFFERENT DE N TOUS LES GRAPHIQUES SONT AFFICHES
elas10 (9K) Test elas10.dgibi: Jeux de données CAS TEST DU 91/06/13 PROVENANCE : TEST SI GRAPH = N PAS DE GRAPHIQUE AFFICHE SINON SI GRAPH DIFFERENT DE N TOUS LES GRAPHIQUES SONT…
elas11 (7K) Test elas11.dgibi: Jeux de données CAS TEST DU 91/06/13 PROVENANCE : TEST SI GRAPH = N PAS DE GRAPHIQUE AFFICHE SINON SI GRAPH DIFFERENT DE N TOUS LES GRAPHIQUES SONT…
elas12 (6K) Test elas12.dgibi: Jeux de données CAS TEST DU 91/06/13 PROVENANCE : TEST SI GRAPH = N PAS DE GRAPHIQUE AFFICHE SINON SI GRAPH DIFFERENT DE N TOUS LES GRAPHIQUES SONT…
elas13 (6K) Test elas13.dgibi: Jeux de données CAS TEST DU 91/06/13 PROVENANCE : TEST SI GRAPH = N PAS DE GRAPHIQUE AFFICHE SINON SI GRAPH DIFFERENT DE N TOUS LES GRAPHIQUES SONT…
elas14 (11K) SI GRAPH = N PAS DE GRAPHIQUE AFFICHE SINON SI GRAPH DIFFERENT DE N TOUS LES GRAPHIQUES SONT AFFICHES
elas15 (5K) Etude d'une poutre a un element, encastree d'un cote encastrement sollicitation |------------------------------------- p1 p2 verification de solutions elementaires en…
elas16 (3K) Etude d'une poutre sur appuis simple chargee de facon repartie (on en etudie que la demi-longueur) symetrie appuis simple |------------------------------------- ^ p1 p2…
elas17 (4K) ANALYSE D'UN TREILLIS AVEC LE CHARGEMENT THERMIQUE DESCRIPTION DU PROBLEME UN TREILLIS ARTICULE EST CHARGE PAR UNE FORCE A SON EXTREMITE LIBRE ET SOUMIS A UN…
elas18 (2K) Etude d'une poutre encastree a une extremite et chargee a l'autre on néglige l'énergie associée à l'effort tranchant La flexion se fait dans le plan xoy encastrement…
elas19 (5K) CAS TEST DU 93/11/4 TEST ELAS19 modelisation de la section rectangulaire d'une poutre soumise a 2 moments de flexion mfx et mfy et a un effort normal le calcul est…
elas2 (3K) Test elas2.dgibi: Jeux de données GRAPH = FAUX => PAS DE GRAPHIQUE AFFICHE GRAPH = VRAI => LES GRAPHIQUES SONT AFFICHES dans un postscript
elas20 (6K) Test Elas20.dgibi: Jeux de données TEST TUYAU DROIT ET COUDE SOUS PRESSION description : Test en statique lineaire, chargement pression. La structure est modelisee en…
elas3 (3K) Test elas3.dgibi: Jeux de données SI GRAPH = N PAS DE GRAPHIQUE AFFICHE SINON SI GRAPH DIFFERENT DE N TOUS LES GRAPHIQUES SONT AFFICHES
elas4 (6K) Test elas4.dgibi: Jeux de données SI GRAPH = N PAS DE GRAPHIQUE AFFICHE SINON SI GRAPH DIFFERENT DE N TOUS LES GRAPHIQUES SONT AFFICHES
elas5 (7K) Test elas5.dgibi: Jeux de données CAS TEST DU 91/06/13 PROVENANCE : TEST SI GRAPH = N PAS DE GRAPHIQUE AFFICHE SINON SI GRAPH DIFFERENT DE N TOUS LES GRAPHIQUES SONT…
elas6 (7K) Test elas6.dgibi: Jeux de données CAS TEST DU 91/06/13 PROVENANCE : TEST SI GRAPH, LES GRAPHIQUES SONT AFFICHES
elas7 (7K) Test elas7.dgibi: Jeux de données CAS TEST DU 91/06/13 PROVENANCE : TEST SI GRAPH = N PAS DE GRAPHIQUE AFFICHE SINON SI GRAPH DIFFERENT DE N TOUS LES GRAPHIQUES SONT…
elas8 (5K) Test elas8.dgibi: Jeux de données CAS TEST DU 91/06/13 PROVENANCE : TEST SI GRAPH = N PAS DE GRAPHIQUE AFFICHE SINON SI GRAPH DIFFERENT DE N TOUS LES GRAPHIQUES SONT…
elas9 (6K) Test elas9.dgibi: Jeux de données CAS TEST DU 91/06/13 PROVENANCE : TEST POUR CALCUL COMPLET METTRE COMPLET = VRAI;
elasp (5K) TEST ELASP MEMBRANE ELLIPTIQUE (Contraintes planes) cas-test NAFEMS : test numero LE1 Une membrane elliptique obtenue par projection d'arcs de cercles sur un plan, est…
elas_ani (2K) Cas test pour l'operateur ELAS avec un modele mecanique elastique anisotrope (correction d'anomalie 8036)
gdef1 (7K) TEST GDEF1 CISAILLEMENT PUR EN GRANDES DEFORMATIONS ELASTIQUES On compare avec les valeurs obtenues a la solution analytique P:PASAPAS
gdep2 (2K) anneau sous pression non uniforme position du probleme il s agit de determiner la deformee d un anneau sous pression non uniforme suiveuse en grands deplacements… P:PASAPAS,PECHE
gdep2co (2K) portes tournant autour d'un axe tb . automatique = vrai; tb . autocrit = 100000; P:PASAPAS
gdep2ma (2K) portes tournant autour d'un axe maillé en massif tb . automatique = vrai; tb . autocrit = 100000; P:PASAPAS
gdtract (10K) MODELE HYPERELASTIQUE GORNET-DESMORAT INCOMPRESSIBLE EN GRANDES TRANSFORMATIONS - CONTRAINTES PLANES TEST DE VALIDATION DU MODELE : TRACTION SELON LA DIRECTION Y… P:PASAPAS
gdtractdp (10K) MODELE HYPERELASTIQUE GORNET-DESMORAT QUASI INCOMPRESSIBLE EN GRANDES TRANSFORMATIONS - DEFORMATIONS PLANES TEST DE VALIDATION DU MODELE : TRACTION SELON LA DIRECTION Y… P:PASAPAS
grandksi (5K) pour calcul complet mettre complet à : vrai; calcul fleche d'une plaque sous son propre poids la plaque est horizontale : on joue sur inclinaison de G et de la Force de… P:PASAPAS,PECHE
huittra3d (12K) MODELE HYPERELASTIQUE 8Chaines QUASI-INCOMPRESSIBLE EN GRANDES TRANSFORMATIONS TEST DE VALIDATION DU MODELE : TRACTION (3D) SIMPLE SELON AXE Z COMPARAISON AVEC LA… P:PASAPAS
joi22 (4K) Test Joi22.dgibi: Jeux de données ------- DEFINITION DE LA SURFACE TOP DU JOINT -------
joi23 (5K) ---------- DEFINITION DE LA SURFACE TOP DU JOINT ---------- ---------- MAILLAGE ----------
joi24 (6K) ---------- DEFINITION DE LA SURFACE TOP DU JOINT ---------- ---------- MAILLAGE ----------
joi25 (5K) ---------- DEFINITION DE LA SURFACE TOP DU JOINT ---------- ---------- MAILLAGE ----------
joi41 (9K) Test Joi41.dgibi: Jeux de données TEST JOI41 2 CUBES SUPERPOSES AVEC UN JOINT JOI4 AU MILIEU ( JOI4 3D ISOTROPE ) Deux CUB8 sont superposes. On place un joint JOI4 entre…
joi42 (8K) TEST JOI42 ESSAI DE TRACTION SUR UN JOINT 3D Un joint 3D JOI4 a sa surface inferieure encastree. Sa surface superieure est libre. Un effort de traction est exercee sur…
joi43 (8K) TEST JOI43 ESSAI DE CISAILLEMENT SUR UN JOINT 3D Un joint 3D JOI4 a sa surface inferieure encastree. Sa surface superieure est libre. Un effort de cisaillement est…
ktest-calp (8K) ktest-calp.dgibi Test de fonctionnement de l'opérateur CALP sur un simple exemple de plaque carrée en flexion pure. Plusieurs types de coques sont testées en même temps.… P:PASAPAS
ktest_lump_dkt (5K) ktest pour tester l'opérateur LUMP elem DKT3
lispel (6K) PLAQUE AVEC FISSURE SEMI-ELLIPTIQUE DEBOUCHANTE a/c = a/t = 0.2 Comparaison des valeurs du facteur d'intensite de contrainte avec la solution de Raju-Newman tirée de…
lispnl (4K) PLAQUE FISSUREE SOLLICITEE EN TRACTION PURE PLASTICITE PARFAITE P:PASAPAS
mooneydp (10K) ù fichier : mooneydp.dgibi MODELE HYPERELASTIQUE MOONEY RIVLIN QUASI-COMPRESSIBLE EN GRANDES TRANSFORMATIONS - DEFORMATIONS PLANES TEST DE VALIDATION DU MODELE :… P:PASAPAS
moontrac3d (11K) MODELE HYPERELASTIQUE MOONEY RIVLIN QUASI-INCOMPRESSIBLE EN GRANDES TRANSFORMATIONS TEST DE VALIDATION DU MODELE : TRACTION (3D) SIMPLE SELON AXE Z COMPARAISON AVEC LA… P:PASAPAS
motr2tra (10K) MODELE HYPERELASTIQUE MOONEY-RIVLIN INCOMPRESSIBLE EN GRANDES TRANSFORMATIONS - CONTRAINTES PLANES TEST DE VALIDATION DU MODELE : TRACTION BIAXIALE DANS LE PLAN X,Y… P:PASAPAS
motrtrac (9K) MODELE HYPERELASTIQUE MOONEY-RIVLIN INCOMPRESSIBLE EN GRANDES TRANSFORMATIONS - CONTRAINTES PLANES TEST DE VALIDATION DU MODELE : TRACTION SELON LA DIRECTION Y… P:PASAPAS
motrtracdp (10K) MODELE HYPERELASTIQUE MOONEY RIVLIN QUASI-COMPRESSIBLE EN GRANDES TRANSFORMATIONS - DEFORMATIONS PLANES TEST DE VALIDATION DU MODELE : TRACTION SELON LA DIRECTION Y… P:PASAPAS
nafems-le3-ortho (2K) Paramètres ... Points ...
nafems-le3 (2K) Paramètres ... Points ...
NeoHookeen_Traction3D (11K) MODELE HYPERELASTIQUE NEOHOOKEEN COMPRESSIBLE EN GRANDES TRANSFORMATIONS TEST DE VALIDATION DU MODELE : TRACTION (3D) SIMPLE SELON AXE Z COMPARAISON AVEC LA SOLUTION… P:PASAPAS
nonconforme (6K) utilisation de maillage non conforme crée par raff mettre igraph='O' ; pour avoir les dessins P:G_THETA
orth6 (7K) CAS TEST DU 91/06/13 PROVENANCE : TEST TEST ORTH6 PLAQUE CARREE ORTHOTROPE ENCASTREE Test V.P.C.S. numero SSLS33/90 Groupe : Statique lineaire Structure assemblee
ortho-coq4 (4K) TEST ORTHOTROPIE : PLAQUE EN FLEXION Michel BULIK (inspiré d'un test d'Alain MOAL (octobre 1996)) Il s'agit d'une plaque carrée, encastrée sur les bords et soumise à une…
ortho-cu20 (3K) TEST ORTHOTROPIE : PLAQUE EN FLEXION - MAILLAGE VOLUMIQUE Michel BULIK (inspiré d'un test d'Alain MOAL (octobre 1996)) Il s'agit d'une plaque carrée, encastrée sur les…
ortho-vari-2D (4K) Paramètres ... Coefficients de la matrice de Hooke en repère d'orthotropie ...
ortho-vari-coq4 (4K) Paramètres ... Coefficients de la matrice de Hooke en repère d'orthotropie ...
pecker_f (6K) etude frequentielle chargement structure avec impedance P:PASAPAS
pecker_t (12K) etude propagation dans sol approche interaction sol structure Pecker 1973 temporel grandeurs numériques arbitraires !!! attention mo1 reaffecte P:PASAPAS
phasage (6K) nca2=10;nca=nca2*2;nd1=2; nd2=4; trac su; P:DEPOU,PHASAGE,RETRAIT,TENSION
precont4 (3K) Calcul de la perte de précontrainte d'un cable circulaire tendu a une seule de ses extremités.
q8ri_bcn (2K) TEST Q8RI BCN Verification of element Q8RI (QUA8 with 2x2 Gauss points) Elastic analysis of a square subjected to biaxial extension
relacori (1K) poutre maillée en coques et en massifs test de la relation de corps rigide
rousselier (15K) TEST DE VALIDATION DE LA LOI D'ENDOMMAGEMENT DUCTILE DE ROUSSELIER TEST: UN BARREAU EST CHARGE EN TRACTION LE CHARGEMENT EST DES DEPLACEMENTS IMPOSES CALCUL EN MASSIF 3D… P:PASAPAS
sphere (8K) Sphere sous pression interne R0 rayon interne aleatoire LogNormale(50 , 2.5) R1 rayon externe aleatoire LogNormale(100 , 5 ) P0 pression interne aleatoire LogNormale(130… P:INDIBETA,PARASTAT,PROBDENS,QUADRATU
testIC20 (4K) Test TestIC20.dgibi: Jeux de données FICHIER GIBIANE POUR TESTER LES ELEMENTS INCOMPRESSIBLES volumiques quadratiques Maillage d'un cube avec les éléments IC On soumet… P:PASAPAS
testICQ4 (4K) Test TestICQ4.dgibi: Jeux de données FICHIER GIBIANE POUR TESTER LES ELEMENTS INCOMPRESSIBLES ICQ4 Maillage d'une plaque de forme carrée avec les éléments ICQ4. Cas…
testICQ8 (4K) FICHIER GIBIANE POUR TESTER LES ELEMENTS INCOMPRESSIBLES ICQ8 Maillage d'une plaque de forme carrée avec les éléments ICQ8. Cas déformation plane. On soumet la plaque à…
testICT3 (4K) FICHIER GIBIANE POUR TESTER LES ELEMENTS INCOMPRESSIBLES ICT3 Maillage d'une plaque de forme carrée avec les éléments ICT3. Cas déformation plane. On soumet la plaque à…
testICT6 (4K) FICHIER GIBIANE POUR TESTER LES ELEMENTS INCOMPRESSIBLES ICT6 Maillage d'une plaque de forme carrée avec les éléments ICT6. Cas déformation plane. On soumet la plaque à…
testjoi1ani (2K) SOLUTION ANALYTIQUE P:PASAPAS
testjoi1orth (1K) SOLUTION ANALYTIQUE
test_AMITEX (7K) 23456789123456789123456789123456789123456789123456789123456789123456789 CAS TESTS POUR L'UTILISATION DES PROCEDURES D'APPLICATION DES CONDITIONS AUX LIMITES ET DE CALCUL… P:@CLCH,@CLDH,@CLDHC,@CLIM,@CLMI1C,@CLMI2C,@CLPC,@CLPD,@KEFF
test_jointsoft (3K) Cas test joint_soft Ancrage d'une barre d'acier Essai push-pull D. COMBESCURE - EMSI 1999 P:PASAPAS
timf1 (3K) Etude d'une poutre sur appuis simple chargee de facon repartie (on en etudie que la demi-longueur) symetrie appuis simple |------------------------------------- ^ p1 p2…
umat01 (16K) CAS TEST DE VALIDATION DE LA PRISE EN COMPTE D'UNE LOI DE COMPORTEMENT MECANIQUE NON LINEAIRE EXTERNE Modele 'NON_LINEAIRE' 'UTILISATEUR', integrateur specifique UMAT… P:PASAPAS
umat01_ortho (10K) repertoire des fichiers "divers" TEST DE VALIDATION DE L'ORTHOTROPIE POUR UN MODELE DE COMPORTEMENT "UTILISATEUR" DEFINI A L'EXTERNE VIA UMAT MODELE DEFINI VIA UMAT… P:@MISTPAR,PASAPAS ext:mimatD3d_par
umat02 (65K) CAS TEST DE VALIDATION DE LA PRISE EN COMPTE D'UNE LOI DE COMPORTEMENT MECANIQUE NON LINEAIRE EXTERNE Modele 'NON_LINEAIRE' 'UTILISATEUR', integrateur specifique UMAT… P:PASAPAS
visucoq (2K) Exemple d'utilisation de coq2mas Visualisation 3D de résultats de calcul coque multicouche D. Combescure - Juillet 2007 Laboratoire DYN - CEA Saclay FLAGVISU = VRAI;… P:COQ2MAS
vsur1 (1K) Test Vsur1.dgibi: Jeux de données vsur1.dgibi : Test de l'opérateur VSUR en coq2
vsur2 (2K) vsur2.dgibi : Test de VSUR en coq3, DKT, DST et coq4 Définition de la géométrie
vsur3 (1K) vsur3.dgibi : Test de VSUR en coq6 et coq8 Définition de la géométrie
weib (7K) TRAVE CARICATA PER FLESSIONE A QUATTRO PUNTI ; DETERMINAZIONE DELLA PROBABILITA' DI ROTTURA SECONDO LA STATISTICA DI WEIBULL: CARATTERISTICHE GEOMETRICHE DELLA TRAVE P:WEIBULL

## Mecanique Elastique Grands_deplacements (1)
gdep5 (5K) Description : Traction simple en deplacement impose. Eprouvette en forme de pave droit, 3 elements Calcul lineaire elastique en Grands deplacements, Validation : La… P:PASAPAS

## Mecanique Endommagement (75)
betdynlmt (1K) essai de traction uniaxiale Defintion du maillage cube à 8 noeuds P:PASAPAS
compression (2K) Type & Elements de representation Caracteristiques geometriques P:PASAPAS
compression_nloc (2K) Type & Elements de representation Caracteristiques geometriques P:PASAPAS
concyc (5K) Cas test de l'implantation numérique du modele RICRAG 3D LOCAL/NON LOCAL Développé par : Maxime VASSAUX Benjamin RICHARD Les cas de charges sont entrés : - 1 : Traction… P:@GLOBAL,PASAPAS
damage_tc_3d (4K) Cas test de l'implantation numérique du modele DAMAGE_TC 3D Développé par : Benjamin Richard Contact : Benjamin.Richard@lmt.ens-cachan.fr Institution :… P:@GLOBAL,PASAPAS
ddi (4K) Test Ddi.dgibi: Jeux de données TEST DE VALIDATION MATERIAU VISCO-PLASTIQUE ENDOMMAGEABLE MODELE A DEUX DEFORMATIONS INELASTIQUES (DDI) MAILLAGE: EPROUVETTE CYLINDRIQUE… P:PASAPAS
desmorat (2K) -------------------définition de la géométrie-------------------- -----------MODELE------------------ P:PASAPAS
dragon (8K) Modèle de comportement : DRAGON 'MODE' maillage 'ELASTIQUE' 'ISOTROPE' 'PLASTIQUE_ENDOM' 'DRAGON' ; Validation en traction et en compression sur un élément P:PASAPAS
endoaxi1 (7K) Test Endoaxi1.dgibi: Jeux de données pour calcul complet mettre complet à : vrai; TEST; MATERIAU ELASTO-PLASTIQUE ENDOMMAGEABLE EPROUVETTE EN TRACTION AVEC DEPLACEMENTS… P:PASAPAS
endoaxi2 (7K) Test Endoaxi2.dgibi: Jeux de données TEST; MATERIAU ELASTO-PLASTIQUE ENDOMMAGEABLE MATERIAU DEPENDANT DE LA TEMPERATURE : COURBE DE TRACTION COEFFICIENT DE DILATATION… P:PASAPAS
endoaxi3 (5K) Test Endoaxi3.dgibi: Jeux de données pour calcul complet mettre complet à : vrai; TEST; MATERIAU ELASTO-PLASTIQUE ENDOMMAGEABLE MATERIAU DEPENDANT DE LA TEMPERATURE :… P:PASAPAS,PECHE
endocp1 (8K) Test Endocp1.dgibi: Jeux de données pour calcul complet mettre complet à : vrai; TEST; MATERIAU ELASTO-PLASTIQUE ENDOMMAGEABLE EPROUVETTE EN TRACTION AVEC DEPLACEMENTS… P:PASAPAS
fatsin-1d (6K) TEST MATERIAU ENDOMMAGEMENT EN FATIGUE SINUSOIDALE EPROUVETTE EN FATIGUE UNIAXIALE PILOTE en DEPLACEMENT CONTRAINTES PLANES. LES RESULTATS OBTENUS SONT COMPARES A LA… P:@TOTAL,PASAPAS
fron1 (2K) FICHIER GIBIANE POUR TESTER L'OPERATEUR FRONT sur un disque de rayon 100 la vitesse vaut 2 - (r/100)**2 la position du front 100(-1+exp(t/100)) r = 100 est atteint pour…
fuite_fissure (1K) Test fuite_fissure.dgibi: Jeux de données CALCUL DU DEBIT DE FUITE D'UN MELANGE D'AIR SEC A TRAVERS UNE FISSURE TRAVERSANTE POUR UNE DIFFERENCE DE PRESSION IMPOSEE…
GLRC_DM (12K) Cas test de l'implantation numérique du modele GLRC_DM Développé par : Benjamin Richard Contact : Benjamin.Richard@lmt.ens-cachan.fr Institution :… P:@EXCEL1,@GLOBAL,@TOTAL,IDENTI,PASAPAS
HHO_Mooney_LRGTreloar_Traction (10K) MODELE HYPERELASTIQUE MOONEY-RIVLIN INCOMPRESSIBLE EN GRANDES TRANSFORMATIONS - CONTRAINTES PLANES TEST DE VALIDATION DU MODELE : TRACTION SELON LA DIRECTION Y… P:PASAPAS
mazars (2K) TEST; MATERIAU ENDOMMAGEMENT MAZARS EPROUVETTE EN TRACTION AVEC DEPLACEMENTS IMPOSES CONTRAINTES PLANES, DEFO. LINEAIRES LES RESULTATS OBTENUS SONT COMPARES A LA… P:@GLOBAL,PASAPAS
mazars2 (3K) Christian La Borderie 20 janvier 2010 TESTE LA VERSION MAZARS P:@GLOBAL,PASAPAS
Mooney_LRGTreloar_Bitraction (10K) MODELE HYPERELASTIQUE MOONEY-RIVLIN INCOMPRESSIBLE EN GRANDES TRANSFORMATIONS - CONTRAINTES PLANES TEST DE VALIDATION DU MODELE : TRACTION BIAXIALE DANS LE PLAN X,Y… P:PASAPAS
Mooney_LRGTreloar_Cisaillementsimple (9K) MODELE HYPERELASTIQUE MOONEY-RIVLIN INCOMPRESSIBLE EN GRANDES TRANSFORMATIONS - CONTRAINTES PLANES TEST DE VALIDATION DU MODELE : CISAILLEMENT DANS LA DIRECTION X… P:PASAPAS
Mooney_LRGTreloar_Traction (9K) MODELE HYPERELASTIQUE MOONEY-RIVLIN INCOMPRESSIBLE EN GRANDES TRANSFORMATIONS - CONTRAINTES PLANES TEST DE VALIDATION DU MODELE : TRACTION SELON LA DIRECTION Y… P:PASAPAS
mvm_bcn (5K) TEST : P:PASAPAS
nlsb_pasapas (5K) Cas test de l'implantation Nonlocal Stress Based (NLSB) Description du cas test : Chargement uniaxial sur un cube L'objectif de l'essai est de verifier le bon… P:@GLOBAL,PASAPAS
psury (8K) TEST DE VALIDATION DE LA LOI D'ENDOMMAGEMENT TRIAXIAL P/Y TEST: UN BARREAU EST CHARGE EN TRACTION LE CHARGEMENT EST DES DEPLACEMENTS IMPOSES CALCUL EN MASSIF 3D… P:PASAPAS
ricbet_3d (5K) Cas test de l'implantation numerique du modele RICBET LOCAL/NON LOCAL 3D Développé par : Benjamin Richard Contact : Benjamin.Richard@lmt.ens-cachan.fr Institution :… P:@EXCEL1,@GLOBAL,GAM1,PASAPAS
ricbet_uni_1 (5K) DESCRIPTION Local test - Multifiber analysis Loading path considered: - 1 : Monotonic tension test - 2 : Monotonic compression test - 3 : Cyclic tension test - 4 :… P:GAM1,PASAPAS
ricbet_uni_2 (5K) DESCRIPTION Local test - Multifiber analysis Loading path considered: - 1 : Monotonic tension test - 2 : Monotonic compression test - 3 : Cyclic tension test - 4 :… P:GAM1,PASAPAS
riccoq (10K) Cas test de l'implantation numerique du modele RICCOQ - Formulation COQUE Mince Développé par : Benjamin Richard Contact : Benjamin.Richard@lmt.ens-cachan.fr Institution… P:@GLOBAL,@TOTAL,PASAPAS
ricjoi_2d (5K) Cas test de l'implantation numérique du modele RICJOI 2D LOCAL Développé par : Benjamin Richard Contact : Benjamin.Richard@lmt.ens-cachan.fr Les cas de charges sont… P:PASAPAS
ricjoi_3d (6K) Cas test de l'implantation numérique du modele RICJOI_3D LOCAL Développé par : Benjamin Richard Contact : Benjamin.Richard@lmt.ens-cachan.fr Les cas de charges sont… P:PASAPAS
ricrag_2d (3K) Cas test de l'implantation numérique du modele RICRAG 2D LOCAL/NON LOCAL Développé par : Benjamin Richard Contact : Benjamin.Richard@lmt.ens-cachan.fr Les cas de charges… P:@GLOBAL,GAM1,PASAPAS
ricrag_3d (3K) Cas test de l'implantation numérique du modele RICRAG 3D LOCAL/NON LOCAL Développé par : Benjamin Richard Les cas de charges sont entrés : - 1 : Traction monotone - 2 :… P:@GLOBAL,GAM1,PASAPAS
rupt1 (4K) Test Rupt1.dgibi: Jeux de données QUALIFICATION DU CALCUL DE K EN ELASTICITE LINEAIRE SUR UN CYLINDRE AVEC UNE FISSURE DEBOUCHANTE CIRCONFERENTIELLE Le calcul est… P:G_THETA
rupt10 (12K) VALIDATION DE LA METHODE DES DFEPLACEMENTS DANS LE CAS D'UNE PLAQUE EN FLEXION PURE. SOLUTION DE REFERENCE : Compendium of STRESS INTENSITY FACTORS by Rooke &… P:SIF
rupt11 (7K) VALIDATION DES PROCEDURES GTHETA ET T_PITETA PAR UNE PLAQUE EN TRACTION PURE. SOLUTION DE REFERENCE : ISIDA, On the tension of a strip with a central elliptical hole.… P:G_THETA
rupt12 (6K) complet = vrai; pour calcul complet mettre complet à : vrai; I VALIDATION DE LA PROCEDURE I G_THETA EN DYNAMIQUE. I I PLAQUE EN TRACTION PURE AVEC I CHARGEMENT 'f(t)' I… P:@RAYO,G_THETA,PASAPAS
rupt13 (16K) ; LE TAUX G DANS L'EPAISSEUR DE COQUE : NOUVELLE TECHNIQUE ICOQU = 1 ELEMENTS 'DKT' ICOQU = 2 ELEMENTS 'DST' ICOQU = 3 ELEMENTS 'COQ6' ICOQU = 4 ELEMENTS 'COQ4' ICOQU =… P:G_THETA,PASAPAS,SIF
rupt14-weib (16K) Test du critère de Weibull pour un cylindre en traction modelisé en axisymétrique et en 3D P:CRITLOC,PASAPAS,WEIBULL
rupt15-rice (16K) Test du critère de Rice pour un cylindre en traction modelisé en axisymétrique et en 3D P:CRITLOC,PASAPAS
rupt16-weib (10K) Test du critère de Weibull pour un cylindre en traction modelisé en axisymétrique sigu constante ou évolution constante P:CRITLOC,PASAPAS,WEIBULL
rupt17 (10K) rupt17.dgibi CAS TEST SUR LE CALCUL DE J EN THERMOPLASTICITE POUR FISSURE PROCHE (ou SUR) INTERFACE LIAISON BIMETALLIQUE P:G_THETA,PASAPAS
rupt2 (7K) Test Rupt2.dgibi: Jeux de données ; ; ; ; QUALIFICATION DU CALCUL DE G ; EN THERMO-ELASTICITE LINEAIRE ; SUR UNE PLAQUE A FISSURE LATERALE ; EVALUATION DU FACTEUR DE… P:G_THETA
rupt26 (5K) Test rupt26.dgibi: Jeux de données Cas test de validation pour le calcul de J sous plusieurs chargement avec les procedures g_theta.procedur et g_calcul.procedur -… P:G_THETA
rupt27 (13K) Données paramètriques : a : profondeur de la fissure t : epaisseur du tube ri, re : rayon interne/externe h : hauteur du tube P:G_THETA,PASAPAS
rupt28 (14K) Données paramètriques : a : profondeur de la fissure t : epaisseur du tube ri, re : rayon interne/externe h : hauteur du tube P:G_THETA,PASAPAS
rupt29 (6K) Test rupt29.dgibi: Jeux de données Cas test de validation pour le calcul de J sous plusieurs chargement avec les procedures g_theta.procedur et g_calcul.procedur -… P:G_THETA
rupt3 (6K) Test Rupt3.dgibi: Jeux de données ; ; ; ; QUALIFICATION DU CALCUL DE G ; EN ELASTICITE LINEAIRE SUR ; UNE PLAQUE A FISSURE INTERNE ; ; ; le calcul est compare a celui… P:G_THETA
rupt4 (7K) Test Rupt4.dgibi: Jeux de données ; ; ; ; QUALIFICATION DU CALCUL DE G ; EN ELASTICITE LINEAIRE SUR ; UNE PLAQUE A FISSURE INTERNE ; SOUMISE A UNE PRESSION CONSTANTE ; ;… P:G_THETA
rupt5 (7K) Test Rupt5.dgibi: Jeux de données ; ; ; ; QUALIFICATION DU CALCUL DE G ; EN ELASTICITE LINEAIRE SUR ; UN TUBE A FISSURE INTERNE ; SOUMISE A UNE PRESSION LINEAIRE ; ; ;… P:G_THETA
rupt6 (11K) Test Rupt6.dgibi: Jeux de données CALCUL DU FACTEUR D'INTENSITE DE CONTRAINTES PAR LA METHODE DES DEPLACEMENTS ET PAR LA METHODE G_THETA POUR UNE FISSURE CIRCULAIRE… P:G_THETA,SIF
rupt7 (8K) Test Rupt7.dgibi: Jeux de données CALCUL DU FACTEUR D'INTENSITE DE CONTRAINTES D'UNE PLAQUE AVEC FISSURE RECTILIGNE INCLINEE CHARGEE EN TRACTION UNIFORME PAR SIF… P:G_THETA,SIF
rupt8 (8K) Test Rupt8.dgibi: Jeux de données VALIDATION DE LA METHODE G_THETA EN CAS D'UNE PLAQUE EN TRACTION PURE. SOLUTION DE REFERENCE : Compendium of STRESS INTENSITY FACTORS… P:G_THETA
rupt9 (6K) Test Rupt9.dgibi: Jeux de données VALIDATION DE LA PROCEDURE G_THETA SUR UNE PLAQUE EN TRACTION PURE SOLUTION DE REFERENCE : COMPENDIUM OF STRESS INTENSITY FACTORS, by… P:G_THETA
sic1 (10K) VALIDATION DU MODELE SIC/SIC AU CHARGHEMENT EN TRACTION graph = 'O' ou 'N' pour voir le maillage et la courbe des contraintes. P:PASAPAS
sic2 (21K) VALIDATION DU MODELE SIC/SIC AU CHARGHEMENT EN TRACTION graph = 'O' ou 'N' pour voir le maillage et la courbe des contraintes. P:PASAPAS
sicfsic (14K) POUR UN CALCUL COMPLET METTRE À VRAI CAS TEST DE VALIDATION DES LOIS DE COMPORTEMENT ONERA SCALAIRE ET PSEUDO-TENSORIEL POUR LE COMPOSITE TISSE SICf/SIC. Paramètres pris… P:PASAPAS
stru1 (7K) CAS TEST DU 91/06/13 PROVENANCE : TEST TEST STRU1 PLAQUE RAIDIE SUR APPUIS SIMPLES, SOUS CHARGE UNIFORMEMENT REPARTIE La plaque rectangulaire de 2 metre de long, de 1…
stru2 (14K) Test Stru2.dgibi: Jeux de données Pour visualiser les traces, mettre GRAPH a 'O' : P:AFFICHE
stru3 (9K) TEST : SSLS34/91 DE LA COMMISSION "STRUCTURES ASSEMBLEES" DESCRIPTION : PLAQUE ORTHOTROPE RAIDIE SUR APPUIS SIMPLES, SOUS UNE CHARGE UNIFORMEMENT REPARTIE. Elements DKT…
stru4 (3K) Test Stru4.dgibi: Jeux de données TEST DE STATIQUE POUR L'ELEMENT TUYAU Un tuyau encastre et courbe est soumis a des efforts de flexion dans son plan. Ref: Guide VPCS,…
tufi (4K) TUYAU FISSURE SOLLICITE EN FLEXION PURE COURBE DE TRACTION RENTREE = LOI MOMENT-COURBURE DE L ESSAI P:PASAPAS
uo2s_cas1 (32K) Test uo2s_cas1.dgibi: Jeux de donnees repertoire des fichiers "divers" P:@GATTPAR,PASAPAS ext:fichier_gatt
uo2s_cas2 (23K) Test uo2s_cas2.dgibi: Jeux de donnees repertoire des fichiers "divers" P:@GATTPAR,PASAPAS ext:fichier_gatt
uo2_cas1 (36K) Test uo2_cas1.dgibi: Jeux de donnees repertoire des fichiers "divers" P:@GATTPAR,PASAPAS ext:fichier_gatt
uo2_cas2 (26K) Test uo_cas2.dgibi: Jeux de donnees repertoire des fichiers "divers" P:@GATTPAR,PASAPAS ext:fichier_gatt
uo2_cas3 (14K) Test uo2_cas3.dgibi: Jeux de données repertoire des fichiers "divers" P:@GATTPAR,PASAPAS ext:fichier_gatt
uo2_cas4 (7K) Test uo2_cas4.dgibi: Jeux de données repertoire des fichiers "divers" P:@GATTPAR,PASAPAS ext:fichier_gatt
xfem01 (15K) xfem01.dgibi calcul avec elements xfem (XQ4R) d'une plaque elastique en traction avec fissure inclinée création : bp, le 24.09.2009 ajout g_theta : bp, 08.06.2010… P:G_THETA
xfem02 (11K) xfem02.dgibi calcul avec elements xfem (XQ4R) d'une plaque elasto plastique en traction avec fissure droite création : bp, le 24.09.2009 ajout g_theta : bp, 08.06.2010… P:G_THETA,PASAPAS
xfem03 (9K) xfem03.dgibi calcul avec elements xfem (XQ4R) d'une plaque en traction modele de Rousselier avec fissure droite création : as, le 24.11.2009 : Résultats moyens à cause… P:PASAPAS
xfem04 (56K) Mots-clés : Mécanique de la rupture, XFEM, contact, frottement, LATIN Etude de reponse d'une plaque en compression avec fissure inclinee via une formulation mixte a… P:@FRENET,G_THETA
xfem3d_01 (15K) graph = vrai ; Maillage : cube sain 1 x 1 x 1 finesse de la discretisation n1 = 36; n1 = 24; n1 = 12; P:G_THETA,SIF
xfem3d_02 (13K) maillage trac cach (vol1 et (liab coul vert) et (liah coul rouge)); mess (nbno vol1) (nbel vol1) ; P:PASAPAS
xfem_gd (10K) xfemcapipica.dgibi Test de l'opérateur de passage des contraintes(déformations) PK2 aux contraintes de Cauchy pour la XFEM d'une plaque elastique en traction avec… P:ENRICHIS,PASAPAS

## Mecanique Fatigue (1)
rccmtest (3K) TEST DES ROUTINES INTERNES DE @RCCM CALCUL EN AXISYMETRIQUE ET EN 3D SUR UN SEGMENT D APPUI COMPARAISON DES RESULTATS P:@RCCMCO2

## Mecanique Flambage (8)
flam1 (3K) Test Flam1.dgibi: Jeux de données TEST FLAM1 FLAMBAGE EULERIEN D'UNE POUTRE ENCASTREE A UNE EXTREMITE Dans cet exemple on se propose d'étudier le flambage d'une poutre… P:FLAMBAGE
flam2 (5K) COMPARAISON DES CALCULS DE FLAMBAGE D'UN TUBE SOUS PRESSION EXTERNE (D'APRèS R.J. GIBERT) ------------------- OPTIONS ----------------------- P:FLAMBAGE
flam3 (4K) COMPARAISON DES CALCULS DE FLAMBAGE D'UN TUBE SOUS PRESSION INTERNE (TUBE DE SACLAY) P:FLAMBAGE
gdep1 (4K) pour calcul complet mettre complet à : vrai; GRAND ROTATION D' UNE POUTRE DESCRIPTION DU PROBLEME IL S'AGIT DE TROUVER LA POSITION POST FLAMBAGE D 'UN POTEAU CHARGE… P:AUTOPILO,FLAMBAGE,PASAPAS,PECHE
gdep3 (4K) taa.'ADDI_MATRICE'=?? pour calcul complet mettre complet à : vrai; flambage d'une poutre avec encastrement glissant et rotule sous force axiale suiveuse similaire à… P:AUTOPILO,PASAPAS,PECHE
kp2_test (1K) test de la matrice de rigidité associée à un champ de pression linéaire. Il s'agit de calculer la variation de la composante verticale des forces de pression d'un…
kp_test (4K) flambage d'une poutre encastree-libre sous poids propre dans un champ de pression hydrostatique le probleme est equivalent au flambage d'une poutre sous poids propre,…
kreslap2 (26K) BEGINPROCEDUR glapn NOM : GLAPN DESCRIPTION : Un laplacien scalaire LANGAGE : GIBIANE-CAST3M AUTEUR : Stéphane GOUNAND (CEA/DEN/DM2S/SFME/LTMF) mél :… P:@STBL,ININLIN

## Mecanique Fluage (27)
creep01_cisXY (40K) CAS TEST DE VALIDATION DE LA PRISE EN COMPTE D'UNE LOI DE COMPORTEMENT MECANIQUE NON LINEAIRE EXTERNE Modele 'VISCO_EXTERNE' 'GENERAL', integre par CCREEP (schema… P:PASAPAS
creep01_cisXZ (40K) CAS TEST DE VALIDATION DE LA PRISE EN COMPTE D'UNE LOI DE COMPORTEMENT MECANIQUE NON LINEAIRE EXTERNE Modele 'VISCO_EXTERNE' 'GENERAL', integre par CCREEP (schema… P:PASAPAS
creep01_cisYZ (40K) CAS TEST DE VALIDATION DE LA PRISE EN COMPTE D'UNE LOI DE COMPORTEMENT MECANIQUE NON LINEAIRE EXTERNE Modele 'VISCO_EXTERNE' 'GENERAL', integre par CCREEP (schema… P:PASAPAS
creep01_traXX (40K) CAS TEST DE VALIDATION DE LA PRISE EN COMPTE D'UNE LOI DE COMPORTEMENT MECANIQUE NON LINEAIRE EXTERNE Modele 'VISCO_EXTERNE' 'GENERAL', integre par CCREEP (schema… P:PASAPAS
creep01_traYY (40K) CAS TEST DE VALIDATION DE LA PRISE EN COMPTE D'UNE LOI DE COMPORTEMENT MECANIQUE NON LINEAIRE EXTERNE Modele 'VISCO_EXTERNE' 'GENERAL', integre par CCREEP (schema… P:PASAPAS
creep01_traZZ (40K) CAS TEST DE VALIDATION DE LA PRISE EN COMPTE D'UNE LOI DE COMPORTEMENT MECANIQUE NON LINEAIRE EXTERNE Modele 'VISCO_EXTERNE' 'GENERAL', integre par CCREEP (schema… P:PASAPAS
creep02_cisXY (41K) CAS TEST DE VALIDATION DE LA PRISE EN COMPTE D'UNE LOI DE COMPORTEMENT MECANIQUE NON LINEAIRE EXTERNE Modele 'VISCO_EXTERNE' 'GENERAL', integre par CCREEP (schema… P:PASAPAS
creep03_cisXY (50K) CAS TEST DE VALIDATION DE LA PRISE EN COMPTE D'UNE LOI DE COMPORTEMENT MECANIQUE NON LINEAIRE EXTERNE Modele 'VISCO_EXTERNE' 'GENERAL', integre par CCREEP (schema… P:PASAPAS
creep04_cisXY (51K) CAS TEST DE VALIDATION DE LA PRISE EN COMPTE D'UNE LOI DE COMPORTEMENT MECANIQUE NON LINEAIRE EXTERNE Modele 'VISCO_EXTERNE' 'GENERAL', integre par CCREEP (schema… P:PASAPAS
flua1t (11K) pour calcul complet mettre complet à : vrai; ------------------------------------------------------------------; ; P:AFFICHE,PASAPAS
fluage_maxwell_1 (3K) Test fluage_maxwell_1.dgibi: Jeux de données TEST DE VERIFICATION D'UNE LOI DE COMPORTEMENT DE MATERIAU LOI DE COMPORTEMENT DE FLUAGE DE : MAXWELL TEST POUR DES ELEMENTS… P:PASAPAS
fluage_maxwell_thve (2K) Maillage Modele P:PASAPAS
flurevi (5K) TEST DU MODELE DE FLUAGE DE N.REVIRON parametre de fluage propre fluage propre P:PASAPAS
norton_cis1 (6K) Test Norton_cis1.dgibi: Jeux de données TEST DE VALIDATION D'UNE LOI DE COMPORTEMENT DE MATERIAU LOI DE COMPORTEMENT DE FLUAGE DE : NORTON TEST POUR DES ELEMENTS MASSIFS… P:PASAPAS
norton_cis2 (9K) TEST DE VALIDATION D'UNE LOI DE COMPORTEMENT DE MATERIAU LOI DE COMPORTEMENT DE FLUAGE DE : NORTON COMPARAISON DE CALCULS SUR DES ELEMENTS: - COQUE EPAISSE ( MFR=5 ) -… P:PASAPAS
norton_tra1 (6K) TEST DE VALIDATION D'UNE LOI DE COMPORTEMENT DE MATERIAU LOI DE COMPORTEMENT DE FLUAGE DE : NORTON TEST POUR DES ELEMENTS MASSIFS MAILLAGE: UNE CUBE DE COTE L=1 M… P:PASAPAS
norton_tra2 (9K) TEST DE VALIDATION D'UNE LOI DE COMPORTEMENT DE MATERIAU LOI DE COMPORTEMENT DE FLUAGE DE : NORTON COMPARAISON DE CALCULS SUR DES ELEMENTS: - COQUE EPAISSE ( MFR=5 ) -… P:PASAPAS
te35 (9K) D4 S1 D2 P1 D1 P2 P:PASAPAS
tufi_relax (2K) COMPARAISON A LA SOLUTION ANALYTIQUE P:PASAPAS
umat03_cisXY (63K) CAS TEST DE VALIDATION DE LA PRISE EN COMPTE D'UNE LOI DE COMPORTEMENT MECANIQUE NON LINEAIRE EXTERNE Modele 'NON_LINEAIRE' 'UTILISATEUR', integrateur specifique UMAT… P:PASAPAS
umat03_cisXY_2122 (70K) CAS TEST DE VALIDATION DE LA PRISE EN COMPTE D'UNE LOI DE COMPORTEMENT MECANIQUE NON LINEAIRE EXTERNE Modele 'NON_LINEAIRE' 'UTILISATEUR', integrateur specifique UMAT… P:PASAPAS
umat03_cisXY_2122b (69K) CAS TEST DE VALIDATION DE LA PRISE EN COMPTE D'UNE LOI DE COMPORTEMENT MECANIQUE NON LINEAIRE EXTERNE Modele 'NON_LINEAIRE' 'UTILISATEUR', integrateur specifique UMAT… P:PASAPAS
umat03_cisXZ (63K) CAS TEST DE VALIDATION DE LA PRISE EN COMPTE D'UNE LOI DE COMPORTEMENT MECANIQUE NON LINEAIRE EXTERNE Modele 'NON_LINEAIRE' 'UTILISATEUR', integrateur specifique UMAT… P:PASAPAS
umat03_cisYZ (63K) CAS TEST DE VALIDATION DE LA PRISE EN COMPTE D'UNE LOI DE COMPORTEMENT MECANIQUE NON LINEAIRE EXTERNE Modele 'NON_LINEAIRE' 'UTILISATEUR', integrateur specifique UMAT… P:PASAPAS
umat03_traXX (63K) CAS TEST DE VALIDATION DE LA PRISE EN COMPTE D'UNE LOI DE COMPORTEMENT MECANIQUE NON LINEAIRE EXTERNE Modele 'NON_LINEAIRE' 'UTILISATEUR', integrateur specifique UMAT… P:PASAPAS
umat03_traYY (63K) CAS TEST DE VALIDATION DE LA PRISE EN COMPTE D'UNE LOI DE COMPORTEMENT MECANIQUE NON LINEAIRE EXTERNE Modele 'NON_LINEAIRE' 'UTILISATEUR', integrateur specifique UMAT… P:PASAPAS
umat03_traZZ (63K) CAS TEST DE VALIDATION DE LA PRISE EN COMPTE D'UNE LOI DE COMPORTEMENT MECANIQUE NON LINEAIRE EXTERNE Modele 'NON_LINEAIRE' 'UTILISATEUR', integrateur specifique UMAT… P:PASAPAS

## Mecanique Fourier (4)
four1 (3K) Test Four1.dgibi: Jeux de données Test four1.dgibi: Jeux de données SI GRAPH = N PAS DE GRAPHIQUE AFFICHE SINON SI GRAPH DIFFERENT DE N TOUS LES GRAPHIQUES SONT AFFICHES
four2 (3K) Test Four2.dgibi: Jeux de données Test four2.dgibi: Jeux de données SI GRAPH = N PAS DE GRAPHIQUE AFFICHE SINON SI GRAPH DIFFERENT DE N TOUS LES GRAPHIQUES SONT AFFICHES
four3 (10K) Mots-clés : Dynamique, calcul fréquentiel, reponse harmonique, 2D Fourier Etude de la flexion d'un cylindre sollicité par une excitation harmonique en mode de Fourier…
visufour1 (4K) Exemple d'utilisation de four2tri Visualisation 3D de résultats de calcul Fourier avec possibilité de recombinaison des harmoniques D. Combescure - Janvier 2007… P:FOUR2TRI

## Mecanique Interaction Fluide Structure (3)
fronabs (2K) test des frontieres absorbantes on teste la reultante pour un champ de vitesses donne
fronabs2 (3K) test des frontieres absorbantes pour les fluides on compare la reponse d'une ligne infinie d'eau soumise à une impulsion avec la reponse d'une ligne identique mais plus… P:DYNAMIC
fronabs3 (5K) Test des frontières absorbantes Barre en cisaillement D. COMBESCURE 30/09/2005 GRAPH = 'O'; P:ANIME,DYNAMIC

## Mecanique Interaction_Sol_Structure (4)
iss2D_x (7K) REPONSE SISMIQUE DU SOL EN ABSENCE DE STRUTURE DESCRIPTION DU PROBLEME IL S'AGIT D'UN PROBLEME D'INTERACTION SOL-STRUCTURE. EN ABSENCE DE STRUCTURE, IL N'Y PAS… P:DECONV,DYNAMIC,SIGNSYNT
iss2D_z (7K) REPONSE SISMIQUE DU SOL EN ABSENCE DE STRUTURE DESCRIPTION DU PROBLEME IL S'AGIT D'UN PROBLEME D'INTERACTION SOL-STRUCTURE. EN ABSENCE DE STRUCTURE, IL N'Y PAS… P:DECONV,DYNAMIC,SIGNSYNT
iss3D_xyz (10K) REPONSE SISMIQUE DU SOL EN ABSENCE DE STRUCTURE DESCRIPTION DU PROBLEME IL S'AGIT D'UN PROBLEME D'INTERACTION SOL-STRUCTURE. EN ABSENCE DE STRUCTURE, IL N'Y PAS… P:DECONV3D,DYNAMIC,SIGNSYNT
issleq1 (24K) Cas test de la procedure ISSLEQ La procedure permet d'effectuer des calculs de propagations d'ondes et ISS avec la methode le calcul lineaire equivalent Developpe par :… P:DECONV3D,DYNAMIC,FTRAN,ISSLEQ

## Mecanique Non-lineaire (3)
grota-coq2 (7K) Le but de ce k-test est de vérifier que les contraintes et les déformations ne varient pas dans un élément COQ2 en grandes rotations. Auteur : M. Bulik Date : Janvier '97 P:PASAPAS
snap (4K) TEST SNAP EXEMPLE D UTILISATION DE LA PROCEDURE PASAPAS ( ET INCREME) PROBLEME DE GRANDS DEPLACEMENTS PROBLEME DU SNAP une seule barre est maillee et calculee || || \/ F… P:AUTOPILO,PASAPAS
snap_non_associe (5K) TEST SNAP EXEMPLE D UTILISATION DE LA PROCEDURE PASAPAS ( ET INCREME) PROBLEME DE GRANDS DEPLACEMENTS PROBLEME DU SNAP une seule barre est maillee et calculee… P:PASAPAS

## Mecanique Nonlineaire (1)
FissVoil (5K) CAS TEST DU 13/11/14 PROVENANCE : TEST TEST PROCEDURE OUVCOR POUR UN PANEL EN CISSAILEMENT 4. * 1. * 0.2 Le maillage est en 3D a l'aide d'elements massif CUB8. L'acier… P:INITOU,PASAPAS,ZONFIS

## Mecanique Plastique (73)
alonso (13K) Modèle d'ALONSO: argile Un cube d'argile de 50 cm de cote est soumis à des deplacements imposes de 10.cm sur 3 de ses faces. L'état de contraintes est volumique. Ce… P:PASAPAS
ba1d (3K) DESCRIPTION Local test - BA1D model Loading path considered: - : Cyclic bending AUTHOR Developped by : Benjamin RICHARD CEA-DEN/DANS/DM2S/SEMT/EMSI… P:@GLOBAL,PASAPAS
cas_test_dp2 (2K) essai de traction simple Cas test Type & Elements de representation P:PASAPAS
cube (14K) CUBE EN TRACTION UNIAXIALE TEST ELEMENTAIRE DU GROUPE DE TRAVAIL 'STATIQUE NON LINEAIRE' COMMISSION VPCS LE CALCUL MARCHE ET DONNE EXACTEMENT LES RESULTATS THEORIQUES LE… P:PASAPAS
dependance (8K) TEST DE CONDENSATION poutre des section rectangulaire en appui simples face inferieure renforcee par une plaque en acier un renfort interne de type poutre un renfort… P:PASAPAS
dp_sol_2Daxis (286K) Test dp_soil_2Daxis.dgibi Test sur la loi non lienaire DP_SOL en 2D MODE AXIS modele d'une test traixial sur une erpouvette numerique solution de reference MATLAB… P:PASAPAS
dp_sol_3D (286K) Test dp_soil_3D.dgibi Test sur la loi non lineaire DP_SOL en 3D MODE TRID modele d'une test traixial sur une erpouvette numerique solution de reference MATLAB Contact:… P:PASAPAS
drx_grd_defo_cisail_elplas (5K) CAS TEST POUR LES GRANDES DÉFORMATIONS ref Rapport DMT 96/359 A de Gayffier "Les lois de comportement des matériaux solides en grandes déformations dans Castem2000 et… P:DREXUS
fefp_powcap_bcn (3K) COMPACTION OF A FLANGED COMPONENT ------------- OPCIONES GENERALES -------------------------------- P:PASAPAS
fefp_powder_bcn (3K) COMPACTION OF A FLANGED COMPONENT ------------- OPCIONES GENERALES -------------------------------- P:PASAPAS
fibre1 (10K) CAS TEST fibre1.dgibi Exemple d'utilisation du modèle à fibre Poutre avec un déplacement imposé L=1800 mm D. Combescure - Décembre 2006 Laboratoire DYN - CEA Saclay… P:PASAPAS,POUT2MAS
gdef2 (6K) TEST GDEF2 CISAILLEMENT PUR EN GRANDES DEFORMATIONS PLASTIQUES ( MODELE DE PLASTICITE ISOTROPE ) On compare avec les valeurs obtenues a une solution analytique P:PASAPAS
gdep4 (5K) fichier gdep4.dgibi Exemple de la donnée d'un état mécanique initial avec : - Comportement mécanique non linéaire (élasto-plastique) ; - Grands déplacements. On simule 2… P:PASAPAS
grot1 (2K) grandes rotations sur un element 2D-DP calcul elastique lineaire P:PASAPAS
guionnet_cis (5K) TEST DE VALIDATION D'UNE LOI DE COMPORTEMENT DE MATERIAU LOI DE COMPORTEMENT VISCOPLASTIQUE DE : GUIONNET COMPARAISON DE CALCULS SUR DES ELEMENTS: - COQUE EPAISSE (… P:PASAPAS
guionnet_tra (6K) Test Guionnet_tra.dgibi: Jeux de données TEST DE VALIDATION D'UNE LOI DE COMPORTEMENT DE MATERIAU LOI DE COMPORTEMENT VISCOPLASTIQUE DE : GUIONNET COMPARAISON DE CALCULS… P:PASAPAS
gurson (3K) Dilatation uniforme d'un cub8 Test sur l'implementation de GURSON Date 16/02/94 Auteur A de Gayffier Reference rapport DMT/94-108 Le test consiste à imposer une… P:PASAPAS
gurson2 (21K) TEST DE VALIDATION DE LA LOI D'ENDOMMAGEMENT DUCTILE DE GURSON TVERGAARD TEST: UN BARREAU EST CHARGE EN TRACTION LE CHARGEMENT EST DES DEPLACEMENTS IMPOSES CALCUL EN… P:PASAPAS
gurson3 (21K) TEST DE VALIDATION DE LA LOI D'ENDOMMAGEMENT DUCTILE DE GURSON TVERGAARD TEST: UN BARREAU EST CHARGE EN TRACTION LE CHARGEMENT EST DES DEPLACEMENTS IMPOSES CALCUL EN… P:PASAPAS
hart2trac (11K) MODELE HYPERELASTIQUE HART-SMITH INCOMPRESSIBLE EN GRANDES TRANSFORMATIONS - CONTRAINTES PLANES TEST DE VALIDATION DU MODELE : TRACTION BIAXIALE DANS LE PLAN X,Y… P:@EXCEL1,PASAPAS
hartcis (10K) MODELE HYPERELASTIQUE HART-SMITH INCOMPRESSIBLE EN GRANDES TRANSFORMATIONS - CONTRAINTES PLANES TEST DE VALIDATION DU MODELE : CISAILLEMENT DANS LA DIRECTION X… P:PASAPAS
harttrac (10K) MODELE HYPERELASTIQUE HART-SMITH INCOMPRESSIBLE EN GRANDES TRANSFORMATIONS - CONTRAINTES PLANES TEST DE VALIDATION DU MODELE : TRACTION SELON LA DIRECTION Y COMPARAISON… P:@EXCEL1,PASAPAS
harttrac3d (12K) MODELE HYPERELASTIQUE HART-SMITH QUASI-INCOMPRESSIBLE EN GRANDES TRANSFORMATIONS TEST DE VALIDATION DU MODELE : TRACTION (3D) SIMPLE SELON AXE Z COMPARAISON AVEC LA… P:PASAPAS
harttracdp (10K) MODELE HYPERELASTIQUE HART-SMITH QUASI-INCOMPRESSIBLE EN GRANDES TRANSFORMATIONS - DEFORMATIONS PLANES TEST DE VALIDATION DU MODELE : TRACTION SELON LA DIRECTION Y… P:PASAPAS
huit2cis (10K) MODELE HYPERELASTIQUE 8 Chaines INCOMPRESSIBLE EN GRANDES TRANSFORMATIONS - CONTRAINTES PLANES TEST DE VALIDATION DU MODELE : CISAILLEMENT DANS LA DIRECTION X… P:PASAPAS
huit2tract (10K) MODELE HYPERELASTIQUE 8 Chaines INCOMPRESSIBLE EN GRANDES TRANSFORMATIONS - CONTRAINTES PLANES TEST DE VALIDATION DU MODELE : TRACTION BIAXIALE DANS LE PLAN X,Y… P:PASAPAS
huittrac (10K) MODELE HYPERELASTIQUE 8 Chaines INCOMPRESSIBLE EN GRANDES TRANSFORMATIONS - CONTRAINTES PLANES TEST DE VALIDATION DU MODELE : TRACTION SELON LA DIRECTION Y COMPARAISON… P:PASAPAS
intimp (5K) Cas test de l'implantation numérique du modele INTIMP permettant de prendre en compte le caractére imparfait de l'interface acier/béton dans un calcul multifibre (fondée… P:PASAPAS,POUT2MAS
isotro_cis (14K) TEST DE VALIDATION D'UNE LOI DE COMPORTEMENT DE MATERIAU LOI DE COMPORTEMENT ELASTO-PLASTIQUE ISOTROPE COMPARAISON DE CALCULS SUR DES ELEMENTS: - COQUE EPAISSE ( MFR=5 )… P:PASAPAS
j2_bcn (3K) PERFORATED STRIP UNDER TRACTION TEST: J2 perfect plasticity model ------------- OPCIONES GENERALES -------------------------------- P:@CARTOON,PASAPAS
joi1_coulomb (12K) Début: MODELE Fin: MODELE Début: MATERIAU P:PASAPAS
joi1_coul_plas (12K) Début: MODELE Fin: MODELE Début: MATERIAU P:PASAPAS
joi1_lie_2 (10K) Cas test sur la mise a jour des vecteurs orientant les elements JOI1 avec FORM On modelise le contact entre deux poutres a section annulaires lorsque l'une d'elles est… P:JEU,PASAPAS
joi_ama (8K) --------- DEFINITION DE LA GEOMETRIE ---------- -------------- DEFINITION DU MAILLAGE -------------- P:PASAPAS
joi_eli (8K) --------- DEFINITION DE LA GEOMETRIE ---------- -------------- DEFINITION DU MAILLAGE -------------- P:PASAPAS
liai_ar1 (15K) Test liai_ar1.dgibi: Jeux de donnees TEST DE VALIDATION MODELE PLASTIQUE BILIN_EFFX SIMULATION DE LA LIAISON CRAYON/GRILLE MAILLAGE: CRAYON = POUTRES ELASTIQUES 1… P:PASAPAS
maj_epaicoq2 (11K) Exemple de calcul elastoplastique avec des coques prenant en compte la diminution de l'epaisseur des coques au cours du calcul. Pour cela, on fait appel a la procedure… P:PASAPAS
melange (5K) l2 = l1 d 2 (p0 plus e2) d 3 p0 ; s1 = surf plan l2 ;
pakzad1 (9K) Modèle de PAKZAD: argile Un cube d'argile de 50 cm de cote est soumis à des deplacements imposes de 10.cm sur 3 de ses faces. L'état de contraintes est volumique. Ce… P:PASAPAS
pakzad2 (11K) Modèle de PAKZAD: argile Un cube d'argile de 50 cm de cote est soumis à des deplacements imposes de 2.5cm sur 3 de ses faces. L'état de contraintes est volumique. Ce… P:PASAPAS
plas1 (7K) Test Plas1.dgibi: Jeux de données CAS TEST DU 91/10/24 PROVENANCE : MILL CAS TEST DU 91/10/15 PROVENANCE : STRU Test plas1.dgibi: Jeux de données SI GRAPH = N PAS DE… P:EXPLORER,PASAPAS
plas10 (6K) Test Plas10.dgibi: Jeux de données TEST PLAS10 Sortie du domaine élastique et phase plastique (comportement élasto-plastique modèle CAM-CLAY). Un parallelépipède est… P:PASAPAS,PECHE
plas11 (9K) Test Plas11.dgibi: Jeux de données TEST : PLAS11 DEFORMATIONS PLANES GENERALISEES une poutre de section rectangulaire est soumise à une rotation imposée RX : Hauteur:4… P:PASAPAS,PECHE
plas14 (13K) Test Plas14.dgibi: Jeux de données EXEMPLE OF A CONCRETE SQUARE SECTION WITH 4 STEEL 20mm BARS CONCRETE DIMENSIONS: (0.25*0.25)m2 - ALL SECTION (0.20*0.20)m2 - CORE… P:PASAPAS
plas15 (5K) TEST PLAS15 Essai de compression simple d'un cube en beton comportement élasto-plastique modèle OTTOSEN Un parallelogramme est soumis à un déplacement imposé sur une de… P:PASAPAS
plas2 (4K) Test Plas2.dgibi: Jeux de données Test plas2.dgibi: Jeux de données SI GRAPH = N PAS DE GRAPHIQUE AFFICHE SINON SI GRAPH DIFFERENT DE N TOUS LES GRAPHIQUES SONT AFFICHES P:PASAPAS
plas4 (7K) Test Plas4.dgibi: Jeux de données Test plas4.dgibi: Jeux de données SI GRAPH = N PAS DE GRAPHIQUE AFFICHE SINON SI GRAPH DIFFERENT DE N TOUS LES GRAPHIQUES SONT AFFICHES P:PASAPAS
plas5 (4K) Test Plas5.dgibi: Jeux de données Test plas5.dgibi: Jeux de données SI GRAPH = N PAS DE GRAPHIQUE AFFICHE SINON SI GRAPH DIFFERENT DE N TOUS LES GRAPHIQUES SONT AFFICHES P:PASAPAS,PECHE
plas6 (9K) Test Plas6.dgibi: Jeux de données CAS TEST DU 91/07/23 PROVENANCE : BIRET Test plas6.dgibi: Jeux de données SI GRAPH = N PAS DE GRAPHIQUE AFFICHE SINON SI GRAPH… P:PASAPAS
plas7 (10K) Test Plas7.dgibi: Jeux de données CAS TEST DU 91/06/13 PROVENANCE : TEST Test plas7.dgibi: Jeux de données SI GRAPH = N PAS DE GRAPHIQUE AFFICHE SINON SI GRAPH DIFFERENT… P:PASAPAS
plas8 (5K) Test Plas8.dgibi: Jeux de données Test plas8.dgibi: Jeux de données POUR CALCUL COMPLET METTRE COMPLET À : VRAI; P:PASAPAS,PECHE
plas9 (7K) Test Plas9.dgibi: Jeux de données TEST PLAS9 Sortie du domaine élastique et phase plastique (comportement élasto-plastique modèle DRUCKER-PRAGER à écrouissage négatif).… P:PASAPAS
plas_coufdp (9K) ESSAIS COUDE EN FLEXION DANS LE PLAN COUDE MINCE ( e = 2.15 mm dext = 179.0 mm ) P:GAM1,PASAPAS
plas_incomp (3K) CUBE EN TRACTION UNIAXIALE Plastique parfait verification de l'incompressibilite de l'ecoulement plastique P:PASAPAS
pore1 (8K) Test Pore1.dgibi: Jeux de données TEST PORE1 CYLINDRE EPAIS EN MILIEU POREUX REFERENCE : Benchmark INTERCLAY 1.1 Variante 2 Le milieu est elastoplastique, modele… P:PASAPAS,PECHE
pore3 (9K) Test Pore3.dgibi: Jeux de données pour calcul complet mettre complet à : vrai; TEST PORE3 CONSOLIDATION UNIDIMENSIONNELLE REFERENCE : Probleme de Terzaghi Le milieu est… P:PASAPAS,PECHE
preston1 (12K) Test Preston1.dgibi: Jeux de données pour calcul complet mettre complet à : vrai; TEST DE VALIDATION D'UNE LOI DE COMPORTEMENT DE MATERIAU LOI DE COMPORTEMENT DE:… P:PASAPAS
preston2 (12K) pour calcul complet mettre complet à : vrai; TEST DE VALIDATION D'UNE LOI DE COMPORTEMENT DE MATERIAU LOI DE COMPORTEMENT DE: PRESTON TONKS WALLACE CAS NON CUBIQUE… P:PASAPAS
rhmc_bcn (2K) VERTICAL MOVEMENT OF A PILE TEST: Rounded Hyperbolic Mohr-Coulomb model ------------- OPCIONES GENERALES -------------------------------- P:PASAPAS
soudage3 (49K) Debut du jeu de donnees de soudage multipasse H. Pommier 12/03/2017 - 3D - Grande Deformations THERMIQUE - Source de chaleur volumique (Goldak) dépendant du temps -… P:@MOD,@REPERE,CHARTHER,PASAPAS,SOUDAGE
sste1_bcn (2K) VERTICAL MOVEMENT OF A PILE TEST: Rounded Hyperbolic Mohr-Coulomb model ------------- OPCIONES GENERALES -------------------------------- P:PASAPAS
sste2_bcn (4K) TRIAXIAL TEST WITH A NON-HOMOGENEOUS SAMPLE TEST: MRS-Lade model ------------- OPCIONES GENERALES -------------------------------- P:PASAPAS
test_cisailnl (2K) Cas test modele global cisail_nl D. COMBESCURE - EMSI 1999 P:PASAPAS
test_infill (2K) Cas test modele global infill_uni D. COMBESCURE - EMSI 1999 P:PASAPAS
thpl1 (6K) Test Thpl1.dgibi: Jeux de données CAS TEST DU 92/03/20 PROVENANCE : TC1 Test thpl1.dgibi: jeux de données SI GRAPH = N PAS DE GRAPHIQUE AFFICHE SINON SI GRAPH DIFFERENT… P:PASAPAS
thpl2 (6K) CAS TEST DU 91/06/13 PROVENANCE : TEST Test thpl2.dgibi: jeux de données SI GRAPH = N PAS DE GRAPHIQUE AFFICHE SINON SI GRAPH DIFFERENT DE N TOUS LES GRAPHIQUES SONT… P:PASAPAS
thpl3 (22K) CAS TEST DU 92/03/20 PROVENANCE : TC1 CAS TEST DU 92/03/19 PROVENANCE : PHIL P:PASAPAS
thpl4 (45K) pour calcul complet mettre complet à : vrai; CAS TEST DU 92/03/20 PROVENANCE : TC1 CAS TEST DU 92/03/19 PROVENANCE : PHIL P:PASAPAS
thpl5 (28K) pour calcul complet mettre complet à : vrai; CAS TEST DU 92/03/20 PROVENANCE : TC1 CAS TEST DU 92/03/19 PROVENANCE : PHIL P:PASAPAS
umat04 (26K) CAS TEST DE VALIDATION DE LA PRISE EN COMPTE D'UNE LOI DE COMPORTEMENT MECANIQUE NON LINEAIRE EXTERNE Modele 'NON_LINEAIRE' 'UTILISATEUR', integrateur specifique UMAT… P:PASAPAS
umat05 (46K) CAS TEST DE VALIDATION DE LA PRISE EN COMPTE D'UNE LOI DE COMPORTEMENT MECANIQUE NON LINEAIRE EXTERNE Modele 'NON_LINEAIRE' 'UTILISATEUR', integrateur specifique UMAT… P:PASAPAS
zeril1 (7K) Test Zeril.dgibi: Jeux de données TEST DE VALIDATION D'UNE LOI DE COMPORTEMENT DE MATERIAU LOI DE COMPORTEMENT DE: ZERILLI-ARMSTRONG CAS CUBIQUE CENTRE ( C.C. )… P:PASAPAS
zeril2 (7K) TEST DE VALIDATION D'UNE LOI DE COMPORTEMENT DE MATERIAU LOI DE COMPORTEMENT DE: ZERILLI-ARMSTRONG CAS CUBIQUE A FACE CENTRE ( C.F.C. ) MAILLAGE: UNE BARRE DE SECTION… P:PASAPAS

## Mecanique Rupture (22)
GTN_C20R (3K) Verification du modele GURSON2 (GTN) avec des elements 3D a integration reduite P:PASAPAS
GTN_degenere (5K) Verification du modele GURSON2 (GTN) dans des cas degeneres ou on doit retrouver de la simple plasticite Verification que par defaut on a bien : - Q2 = 1. - Q3 = Q**2 P:PASAPAS
g_c_etoile_3D_1 (7K) VALIDATION DE LA PROCEDURE G_THETA POUR UN DEFAUT CIRCONFERENTIEL DANS UN TUYAU SOLUTION DE REFERENCE : Ductile Fracture Handbook, A. Zahoor GEOMETRIE : tube rayon… P:G_THETA,PASAPAS
g_c_etoile_axis_1 (5K) VALIDATION DE LA PROCEDURE G_THETA POUR UN DEFAUT CIRCONFERENTIEL DANS UN TUYAU SOLUTION DE REFERENCE : Ductile Fracture Handbook, A. Zahoor GEOMETRIE : tube rayon… P:G_THETA,PASAPAS
g_c_etoile_coque_1 (8K) VALIDATION DE LA PROCEDURE G_THETA POUR UN DEFAUT CIRCONFERENTIEL TRAVERSANT DANS UN TUYAU MODELISE AVEC DES ELEMENTS COQUES SOLUTION DE REFERENCE : Ductile Fracture… P:G_THETA,PASAPAS
g_decouplage_1 (7K) VERIFICATION DE LA PROCEDURE G_THETA POUR LE CALCUL DES FIC POUR UNE FISSURE PENNY-SHAPED DANS UN CYLINDRE VERIFICATION DU CALCUL DE KI VIA DECOUPLAGE EN 3D ET 2D… P:G_THETA
g_decouplage_2 (5K) VERIFICATION DE LA PROCEDURE G_THETA POUR LE CALCUL DES FIC POUR UNE FISSURE PENNY-SHAPED DANS UN CYLINDRE VERIFICATION DU CALCUL DE KII ET KIII VIA DECOUPLAGE EN 3D… P:G_THETA
g_decouplage_3 (4K) VERIFICATION DE LA PROCEDURE G_THETA POUR LE CALCUL DES FIC POUR UNE FISSURE DROITE DANS UNE PLAQUE COMPARAISAON DU CALCUL DE KI ET KII ENTRE ELEMENTS STANDARDS ET XFEM… P:G_THETA
g_decouplage_7 (6K) VERIFICATION DE LA PROCEDURE G_THETA POUR LE CALCUL DE KIII POUR UNE FISSURE PENNY-SHAPED DANS UN CYLINDRE COMPARAISON ENTRE LE RESULTAT DE DECOUPLAGE EN 3D ET UNE… P:G_THETA
g_decouplage_8 (7K) VERIFICATION DE LA PROCEDURE G_THETA POUR LE CALCUL DE KIII POUR UNE FISSURE PENNY-SHAPED DANS UN CYLINDRE COMPARAISON ENTRE LE RESULTAT DE DECOUPLAGE EN 3D ET UNE… P:G_THETA
g_defaut_circonferentiel_1 (4K) VERIFICATION DE LA PROCEDURE G_THETA POUR UN DEFAUT CIRCONFERENTIEL DEBOUCHANT DANS UN TUYAU (FRONT FERME, 2 LEVRES MODELISEES) COMPARAISON ENTRE LE CALCUL 3D ET UN… P:G_THETA
g_defaut_circonferentiel_2 (3K) VERIFICATION DE LA PROCEDURE G_THETA POUR UN DEFAUT CIRCONFERENTIEL DEBOUCHANT DANS UN TUYAU (FRONT FERME, 1 LEVRE MODELISEE COMPARAISON ENTRE LE CALCUL 3D ET UN CALCUL… P:G_THETA
g_defaut_circonferentiel_3 (5K) VERIFICATION DE LA PROCEDURE G_THETA POUR UN DEFAUT CIRCONFERENTIEL DEBOUCHANT DANS UN TUYAU (FRONT DEBOUCHANT, 2 LEVRES MODELISEES) COMPARAISON ENTRE LE CALCUL 3D ET UN… P:G_THETA
g_defaut_circonferentiel_4 (4K) VERIFICATION DE LA PROCEDURE G_THETA POUR UN DEFAUT CIRCONFERENTIEL DEBOUCHANT DANS UN TUYAU (FRONT DEBOUCHANT, 1 LEVRE MODELISEE) COMPARAISON ENTRE LE CALCUL 3D ET UN… P:G_THETA
g_fissure_circulaire_1 (5K) VERIFICATION DE LA PROCEDURE G_THETA POUR LE CALCUL DE G POUR UNE FISSURE CIRCULAIRE DANS UNE GEOMETRIE PLANE COMPARAISON ENTRE LE RESULTAT EN 2D DEFORMATIONS PLANES… P:G_THETA
g_rotation_tuyauterie_droite_1 (5K) VERIFICATION DE LA PROCEDURE G_THETA POUR LE CALCUL DE G POUR UNE FISSURE DANS UNE SECTION DE TUYAU DROIT COMPARAISON ENTRE LE RESULTAT 3D AVEC ET SANS LES OPTIONS… P:G_THETA
g_thermique_coque_1 (15K) VALIDATION DE LA PROCEDURE G_THETA POUR UNE FISSURE DANS UNE PLAQUE SOUMISE A UN CHARGEMENT THERMIQUE DANS L'EPAISSEUR VALIDATION DE LA MODELISATION COQUE PAR… P:G_THETA
J_el_TUB_CDAI_divers_chargements (15K) Cas-test de validation pour le calcul de Jel en 2D et en 3D pour un Cylindre avec un Defaut Axisymetrique en peau Interne (CDAI) soumis a 3 types de chargements : -… P:G_THETA,PASAPAS
rupt30 (7K) ancien nom de fichier : test_sif_3d.dgibi Verification & Validation des procedures SIF et G_THETA Geometrie 3D : fissure en forme de disque de rayon l2 (penny-shaped… P:BOITE,G_THETA,SIF
rupt31 (2K) Cas test pour la procedure SIF 2D, plaque semi-infinie de taille l1 avec fissure interne de taille l2 Soumise a une contrainte sig, dans la direction orthogonale a la… P:SIF
xfem3d_03 (13K) Cas-test propose par F. MERAY, P:G_THETA
xfem_ecrouissage_cinematique (2K) Cas-test de fonctionnement du comportement elastoplastique avec ecrouissage isotrope en combinaison avec des elements XQ4R Verification dans un cas trivial :… P:PASAPAS

## Mecanique Transitoire (1)
TirantLAB (3K) CAS TEST DU 13/11/14 PROVENANCE : TEST TEST ELEMENT COAXIAL COS2 POUR MODELE DE LIAISON ACIER-BETONEN REGIME LINEAIRE TIRANT 3 m SECTION CARRE 0.1 * 0.1 Le tirant est… P:PASAPAS

## Mecanique Usure (1)
usure (18K) Presentation du cas-test: Modelisation 2D du contact-frottement (de type Coulomb) entre un cylindre et un plan. et prise en compte du profil d'usure. Comparaison code a… P:PASAPAS,USURE

## Mecanique Viscoendommagement (2)
fluaendo (5K) pour calcul complet mettre complet à : vrai; MAILLAGE AXISYMETRIQUE EPROUVETTE CYLINDRIQUE MATERIAU VISCO-PLASTIQUE ENDOMMAGEABLE DEPENDANT DE LA TEMPERATURE POUR N M KK… P:PASAPAS,PECHE
relaxendo (5K) pour calcul complet mettre complet à : vrai; MAILLAGE AXISYMETRIQUE EPROUVETTE CYLINDRIQUE MATERIAU VISCO-PLASTIQUE ENDOMMAGEABLE AVEC MATERIAU DEPENDANT DE LA… P:PASAPAS,PECHE

## Mecanique Viscoplastique (47)
chab_cis1 (14K) pour calcul complet mettre complet à : vrai; TEST DE VALIDATION D'UNE LOI DE COMPORTEMENT DE MATERIAU LOI DE COMPORTEMENT VISCOPLASTIQUE : ONERA (CHABOCHE unifie)… P:PASAPAS
chab_cis2 (12K) pour calcul complet mettre complet à : vrai; TEST DE VALIDATION D'UNE LOI DE COMPORTEMENT DE MATERIAU LOI DE COMPORTEMENT VISCOPLASTIQUE DE: ONERA (CHABOCHE unifie)… P:PASAPAS
compar_syco_plast (5K) maillage MODELE & MATERIAU P:PASAPAS
fluendo3d_beton_arme (5K) test de la formulation beton_arme du mdele fluendo3d Alain Sellier, Stephane Multon, Pierre Morenon, Daniela Vo mercredi 4 janvier 2023 Exemple de calcul d un element… P:@GLOBAL,PASAPAS
fluendo3d_def_rag_thcm (31K) test de la formulation RAG(AAR) et RSI(DEF) du modele fluendo3d Alain Sellier, Stephane Multon, Pierre Morenon mercredi 4 janvier 2023 Exemple de calcul d un element en… P:AFT1,AFT2,PASAPAS
fluendo3d_fibre (8K) test du modele de beton fibre (these de Romain Gontero, 2022) Romain Gontero, Alain Sellier, Alain Millard, Thierry Vidal mercredi 4 janvier 2023 Exemple de calcul d un… P:@GLOBAL,PASAPAS
fluendo3d_fluage_biaxial (7K) test de la formulation fluage du mdele fluendo3d Alain Sellier, Thierry Vidal, Laurie Lacarriere, Stephane Multon mercredi 4 janvier 2023 Exemple de calcul d un element… P:PASAPAS
fluendo3d_helmholtz (6K) test de la formulation non-locale differentielle avec fluendo3d Alain Sellier, Alain Millard mercredi 4 janvier 2023 Exemple de calcul non local avec une formulation… P:@GLOBAL,PASAPAS
gatt_3d (17K) Test gatt_3d.dgibi: Jeux de données TEST DE VALIDATION MODELE GATT_MONERIE UO2 STANDARD COMPRESSIBLE AVEC COUPLAGE STATIQUE MAILLAGE: EPROUVETTE PART DE CAMEMBERT… P:@GATTPAR,PASAPAS ext:fichier_gatt
gatt_axi (17K) Test gatt_axi.dgibi: Jeux de données TEST DE VALIDATION MODELE GATT_MONERIE UO2 DOPE CHROME Cr=0.15% TAILLE DE GRAIN=7 µm COMPRESSIBLE AVEC COUPLAGE STATIQUE MAILLAGE:… P:@GATTPAR,PASAPAS ext:fichier_gatt
gatt_cp (17K) Test gatt_cp.dgibi: Jeux de données TEST DE VALIDATION MODELE GATT_MONERIE UO2 STANDARD COMPRESSIBLE AVEC COUPLAGE STATIQUE MAILLAGE: EPROUVETTE RECTANGULAIRE… P:@GATTPAR,PASAPAS ext:fichier_gatt
gatt_dp (17K) Test gatt_dp.dgibi: Jeux de données TEST DE VALIDATION MODELE GATT_MONERIE UO2 STANDARD COMPRESSIBLE AVEC COUPLAGE STATIQUE MAILLAGE: EPROUVETTE RECTANGULAIRE… P:@GATTPAR,PASAPAS ext:fichier_gatt
gd2trac (10K) MODELE HYPERELASTIQUE GORNET-DESMORAT INCOMPRESSIBLE EN GRANDES TRANSFORMATIONS - CONTRAINTES PLANES TEST DE VALIDATION DU MODELE : TRACTION BIAXIALE DANS LE PLAN X,Y… P:PASAPAS
gdcis (10K) MODELE HYPERELASTIQUE GORNET-DESMORAT INCOMPRESSIBLE EN GRANDES TRANSFORMATIONS - CONTRAINTES PLANES TEST DE VALIDATION DU MODELE : CISAILLEMENT DANS LA DIRECTION X… P:PASAPAS
inclusion3d_thm (22K) test de la formulation du mdele inclusion3d Alain Sellier, Elsa Anglade, Aurelie Papon, Clement Lacombe, Thierry Vidal mercredi 4 janvier 2023 Exemple de calcul d un… P:PASAPAS,RETRAIT
mistral_axi (7K) Test mistral_axi.dgibi: Jeux de donnees repertoire des fichiers "divers" P:@MISTPAR,PASAPAS ext:mimataxi_par
mistral_axi2 (7K) Test mistral_axi2.dgibi: Jeux de donnees repertoire des fichiers "divers" P:@MISTPAR,PASAPAS ext:mimataxi2_par
mistral_cp (6K) Test mistral_cp.dgibi: Jeux de donnees repertoire des fichiers "divers" P:@MISTPAR,PASAPAS ext:mimatcp_par
mistral_D3d (6K) Test mistral_D3d.dgibi: Jeux de donnees repertoire des fichiers "divers" P:@MISTPAR,PASAPAS ext:mimatD3d_par
mistral_D3r (9K) Test mistral_D3r.dgibi: Jeux de donnees repertoire des fichiers "divers" P:@MISTPAR,PASAPAS ext:mimatD3r_par
mistral_dpg (6K) Test mistral_dpg.dgibi: Jeux de donnees TEST DE VALIDATION MODELE MISTRAL ELASTICITE ET PLASTICITE INSTANTANE MAILLAGE: EPROUVETTE RECTANGULAIRE CHARGEMENT: DEPLACEMENT… P:@MISTPAR,PASAPAS ext:mimatdpg_par
nouailhas_a1 (6K) fait par PLG le 03-09-97 But : ktest pour la loi viscoplastique NOUAILHAS_A P:PASAPAS
nouailhas_b1 (4K) fait par PLG le 03-09-97 But : ktest pour la loi viscoplastique NOUAILHAS_B P:PASAPAS
nouailhas_b2 (5K) fait par PLG le 03-09-97 But : ktest pour la loi viscoplastique NOUAILHAS_B P:PASAPAS
ohno1 (11K) pour calcul complet mettre complet à : vrai; TEST DE VALIDATION D'UNE LOI DE COMPORTEMENT DE MATERIAU LOI DE COMPORTEMENT VISCOPLASTIQUE DE: OHNO ( CHABOCHE P:PASAPAS
ohno2 (7K) Test Ohno2.dgibi: Jeux de données TEST DE VALIDATION D'UNE LOI DE COMPORTEMENT DE MATERIAU LOI DE COMPORTEMENT VISCOPLASTIQUE DE: OHNO (CHABOCHE P:PASAPAS
ohno_cis1 (14K) TEST DE VALIDATION D'UNE LOI DE COMPORTEMENT DE MATERIAU LOI DE COMPORTEMENT VISCOPLASTIQUE DE: OHNO ( CHABOCHE P:PASAPAS
ohno_cis2 (12K) pour calcul complet mettre complet à : vrai; TEST DE VALIDATION D'UNE LOI DE COMPORTEMENT DE MATERIAU LOI DE COMPORTEMENT VISCOPLASTIQUE DE: OHNO ( CHABOCHE P:PASAPAS
ohno_tra (14K) pour calcul complet mettre complet à : vrai; TEST DE VALIDATION D'UNE LOI DE COMPORTEMENT DE MATERIAU LOI DE COMPORTEMENT VISCOPLASTIQUE DE: OHNO ( CHABOCHE P:PASAPAS
onera1 (11K) pour calcul complet mettre complet à : vrai; TEST DE VALIDATION D'UNE LOI DE COMPORTEMENT DE MATERIAU LOI DE COMPORTEMENT VISCOPLASTIQUE DE: ONERA (CHABOCHE unifie) TEST… P:PASAPAS
onera2 (14K) Test onera2.dgibi: Jeux de données pour calcul complet mettre complet à : vrai; TEST DE VALIDATION D'UNE LOI DE COMPORTEMENT DE MATERIAU LOI DE COMPORTEMENT… P:PASAPAS
onera4 (14K) pour calcul complet mettre complet à : vrai; TEST DE VALIDATION D'UNE LOI DE COMPORTEMENT DE MATERIAU LOI DE COMPORTEMENT VISCOPLASTIQUE : ONERA (CHABOCHE unifie)… P:PASAPAS
onera5 (12K) pour calcul complet mettre complet à : vrai; TEST DE VALIDATION D'UNE LOI DE COMPORTEMENT DE MATERIAU LOI DE COMPORTEMENT VISCOPLASTIQUE DE: ONERA (CHABOCHE unifie)… P:PASAPAS
poudre1 (7K) pour calcul complet mettre complet à : vrai; Cas test pour la loi poudre_A par Christophe DELLIS (CEREM) cas isotrope un cylindre est densifié par mise en pression la… P:PASAPAS
poudre2 (7K) pour calcul complet mettre complet à : vrai; Cas test pour la loi poudre_A par Christophe DELLIS (CEREM) cas oedometrique un cylindre est densifié par mise en pression… P:PASAPAS
poudre3 (6K) Cas test pour la loi poudre_A par Christophe DELLIS (CEREM) cas dense P:PASAPAS
poudre4 (7K) pour calcul complet mettre complet à : vrai; Cas test pour la loi poudre_A par Christophe DELLIS (CEREM) cas isotrope log(A) un cylindre est densifié par mise en… P:PASAPAS
poudre5 (9K) Cylindre de poudre Programme test numero 5 de la loi poudre_A - le 14/03/1997 Laurent Sanchez loi a 3 parametres log A Un cylindre de poudre seul en TA6V est densifie.… P:PASAPAS
poudre6 (9K) Cylindre de poudre Programme test numero 6 de la loi poudre_A - le 14/03/1997 Laurent Sanchez loi a 3 parametres log A,Vitesse de deplacement imposee Un cylindre de… P:PASAPAS
soudage (39K) calcul simplifie du depot d'un cordon de soudure : on realise litteralement des depots de matiere chaude le long d 'un chanfrein. Le materiau est de l inox. ce jeu de… P:PASAPAS
syco_3D_contpla (12K) maillage MODELE & MATERIAU P:PASAPAS
syco_3D_defpla (12K) maillage MODELE & MATERIAU P:PASAPAS
test_CHAB_SINH_X (5K) Nouvelle loi de comportement mécanique Données longueur de la plaque P:@EXCEL1,GAM1,PASAPAS
t_visk2 (3K) test loi visk2 ATTENTION le cas faux appelle un peu de travail de l operateur ! P:PASAPAS
visco2d (5K) Test visco2d.dgibi Exemple de simulation d'essai de fluage sur une eprouvette axisymetrique entaillee en 16MND5. Utilisation de la loi de comportement VISCODD: loi… P:PASAPAS
vpla3 (6K) Test vpla3.dgibi: jeux de données Test vpla3.dgibi: jeux de données POUR CALCUL COMPLET METTRE COMPLET À : VRAI; P:PASAPAS,RAY
vpparf1 (12K) pour calcul complet mettre complet à : vrai; FICHIER GIBIANE POUR TESTER L'IMPLANTATION DU MODELE VISCO PLASTIQUE PARFAIT On impose une force sur l'extremite d'un… P:PASAPAS

## Mecanique rupture (5)
g_decouplage_4 (6K) VERIFICATION DE LA PROCEDURE G_THETA POUR LE CALCUL DES FIC POUR UNE FISSURE PLANE A FOND DROIT DANS UN CUBE VERIFICATION DU CALCUL DE KI, KII ET KIII VIA DECOUPLAGE EN… P:G_THETA
g_decouplage_5 (6K) VERIFICATION DE LA PROCEDURE G_THETA POUR LE CALCUL DES FIC POUR UNE FISSURE PLANE A FOND DROIT DANS UN CUBE VERIFICATION DU CALCUL DE KI, KII ET KIII VIA DECOUPLAGE EN… P:G_THETA
g_decouplage_6 (5K) VERIFICATION DE LA PROCEDURE G_THETA POUR LE CALCUL DES FIC POUR UNE FISSURE DROITE DANS UN CARRE VERIFICATION DU CALCUL DE KI ET KII VIA DECOUPLAGE EN 2D AVEC ELEMENTS… P:G_THETA
g_theta_utilisateur_1 (5K) VERIFICATION DE LA PROCEDURE G_THETA POUR LE CALCUL DE G POUR UNE FISSURE DROITE DANS UN CARRE VERIFICATION DU CALCUL DE G VIA EN 2D AVEC ELEMENTS STANDARDS ET… P:G_THETA
g_theta_utilisateur_2 (5K) VERIFICATION DE LA PROCEDURE G_THETA POUR LE CALCUL DE G POUR UNE FISSURE PLANE A FOND DROIT DANS UN CUBE VERIFICATION DU CALCUL DE G VIA EN 2D AVEC ELEMENTS STANDARDS… P:G_THETA

## Metallurgie (5)
metallurgie_01 (6K) TEST METALLURGIE_01 CALCUL DE l'ERREUR ANALYTIQUE - CAST3M POUR KOISTINEN Le calcul est fait pour 15 pas de temps Vitesse de refroidissement : 10 C/s - Transformation…
metallurgie_02 (6K) TEST METALLURGIE_02 CALCUL DE l'ERREUR ANALYTIQUE - CAST3M POUR LEBLOND Le calcul est fait pour 15 pas de temps Vitesse de refroidissement : 10 C/s - Transformation…
metallurgie_03 (7K) TEST METALLURGIE_03 CALCUL DE l'ERREUR ANALYTIQUE - CAST3M POUR LEBLOND Le calcul est fait pour 15 pas de temps Vitesse de refroidissement : 10 C/s - Transformation…
metallurgie_04 (7K) TEST METALLURGIE_04 CALCUL DE l'ERREUR ANALYTIQUE - CAST3M POUR LEBLOND Le calcul est fait pour 15 pas de temps Vitesse de refroidissement : 10 C/s - Transformation…
metallurgie_05 (4K) TEST METALLURGIE_05 CALCUL D'UN DIAGRAMME T.R.C. SUR UNE MISE EN DONNEES METALLURGIQUE COMPLETE : ACIER 16MND5 REF : A. Bonaventure, « Évaluation expérimentale et… P:TRC

## Nautilus (2)
dp3 (11K) Cas test de performace EXECRXT // RESOU et RÃ©olutions Depressurisation d'une enceinte type Phébus Le maillage correspond à une enceinte cylindrique d'environ 10 m3 avec… P:EXECRXT
dp3xx (11K) Cas test de performace EXECRXT // RESOU et RÃ©olutions Depressurisation d'une enceinte type Phébus Le maillage correspond à une enceinte cylindrique d'environ 10 m3 avec… P:EXECRXT

## Poreux (1)
test_debi (1K) Test tedebi.dgibi: Jeux de données SI GRAPH = N PAS DE GRAPHIQUE AFFICHE SINON SI GRAPH DIFFERENT DE N TOUS LES GRAPHIQUES SONT AFFICHES

## Thermique Advection (4)
adve_01 (4K) Cas-test de l'operateur ADVEction dans la formulation THERMIQUE Comparaison a une solution analytique. On calcule la temperature d'un fluide qui s'ecoule dans un tuyau…
adve_02 (2K) Cas-test de l'operateur ADVEction dans la formulation THERMIQUE Ce cas-test verifie que le produit de la rigidite d'advection avec un champ de temperature donne :…
adve_03 (2K) On resout : v.gradT = 4, Avec : vx=1, vy=1 on a : dT/dx + dT/dy = 4 De + : T(1,0)=0, T(0,1)=0 Sur 1 element QUA4 de geometrie carree et de cote 1. La solution analytique…
adve_07 (3K) Test adve_07.dgibi: Jeux de données TEST ADVE_07 COMPARAISON NUMERIQUE ENTRE LES MODELES THERMIQUE ADVECTION ET DIFFUSION ADVECTION - Maillage 2D rectangulaire - Les…

## Thermique Conduction (17)
carre3D_therper (12K) CALCUL DU CUBE A CHOC Modele: gaz multi-especes "thermally perfect" Gaz multi-especes "thermally perfect" Controle de la symetrie A. BECCANTINI, SEMT/LTMF, MARS 1999
carre3D_therper_scalpass (13K) CALCUL DU CUBE A CHOC Modele: gaz mono-espece "thermally perfect" Gaz mono-espece "thermally perfect" Splitting de scalaire passifs Controle de la symetrie A.…
carre_calper (10K) CALCUL DU QUARRE A CHOC Modele: gaz multi-especes "thermally perfect" Gaz multi-especes "calorically perfect" Controle de la symetrie A. BECCANTINI, SEMT/LTMF, MARS 1999
carre_therper (10K) CALCUL DU QUARRE A CHOC Modele: gaz multi-especes "thermally perfect" Gaz multi-especes "thermally perfect" Controle de la symetrie A. BECCANTINI, SEMT/LTMF, MARS 1999
carre_therper_scalpass (11K) CALCUL DU QUARRE A CHOC Modele: gaz mono-espece "thermally perfect" Gaz mono-espece "thermally perfect" Splitting de scalaire passifs Controle de la symetrie A.…
fabbadd1 (32K) Debut du jeu de donnees fabbrication additive SLM - 3D THERMIQUE - Source de chaleur volumique (Goldak) dépendant du temps (CHARTHER) avec trajectoire personnalisee… P:CHARTHER,PASAPAS
lapq (3K) Comparaison a la solution analytique en regime permanent de la conduction dans un massif avec source volumique. La temperature de paroi est imposee (Tw) En 2D et 3D Lapn… P:EXEC
multilayer (6K) Cas test de non-régression CAST3M Propriétés physiques de murs multicouches auteur G.bonic 19/04/05 Procédure d'affichage P:EXECRXT
rayo-axi-3 (9K) Calcul d'un cylindre infini (de rayon L) soumis à de la convection et du rayonnement. Modélisation axisymétrique. Auteurs : Michel Bulik & Nadia Coulon Date : Octobre… P:PASAPAS,PECHE
Th1D-T3D-Ebul (170K) NOM DE FICHIER : Th1D-T3D-Ebul.dgibi DESCRIPTION : Modelisation thermique 3D - thermohydraulique 1D avec possibilite d'ebullition nucleee sur la paroi chauffante en… P:EXEC,INT_COMP,JEU
ther9 (11K) NOM : THER9 DESCRIPTION : Cas-test du p-laplacien (p>=1) inspiré par \cite[chapitre 8]{saramito}. Teste la thermique en massif 2D conduction anisotrope. Il s'agit de…
thme2 (5K) Réduction d'un jeu sous l'action d'une sollicitation thermique en régime transitoire Calcul thermo-mécanique ( mécanique et thermique linéaire ) Utilisation de la… P:PASAPAS
thme3 (5K) Copie du cas-test thme2.dgibi mais appel à la procedure NONLINEAIRE au lieu de DUPONT. Réduction d'un jeu sous l'action d'une sollicitation thermique en régime… P:PASAPAS
tran12 (5K) Copie du cas-test "tran10.dgibi" pour tester la donnee a PASAPAS d'une : - CAPACITE_CONSTANTE - CONDUCTIVITE_CONSTRANTE et resolution par la procedure NONLINEAIRE Calcul… P:PASAPAS,PECHE
tran13 (5K) Copie du cas-test "tran8.dgibi" pour tester la donnee a PASAPAS d'une : - CAPACITE_CONSTANTE - CONDUCTIVITE_CONSTRANTE et resolution par la procedure LINEAIRE Calcul… P:PASAPAS,PECHE
tran14 (5K) Copie du cas-test "tran8.dgibi" pour tester la donnee a PASAPAS d'une : - CAPACITE_CONSTANTE - CONDUCTIVITE_CONSTRANTE et resolution par la procedure DUPONT Calcul avec… P:PASAPAS,PECHE
tran15 (3K) Calcul avec des elements 'JOI1' (support 'SEG2') et 'POI1' Test tran15.dgibi: jeux de données THERMIQUE TRANSITOIRE LINEAIRE EN 2D CONDUCTION CONVECTION - Verification… P:PASAPAS

## Thermique Convection (21)
convection_axi (6K) DESCRIPTION DE CONVECTION_AXI.DGIBI Ce cas-test unitaire permet de VERIFIER et VALIDER le fonctionnement de l'operateur 'CONV' dans les conditions suivantes : MODE :…
echang (4K) Echange par convection bilatéral Calcul 3D (ou 2D-plan) linéaire permanent on considère 3 plaques parallèles -------- T3 face à face -------- T2 face à face --------…
Effet_Joule_01 (6K) TEST Effet_Joule_01 Cas-test de Verification uniquement (Pas de valeurs testees) Dimension du probleme : 2D Elements finis utilises :'QUA4' Modeles utilises :'THERMIQUE'… P:CHARTHER,PASAPAS,TENSION
exemple_parather (8K) FRA Exemple simple d'utilisation de la procedure utilisateur PARATHER Simulation axisymetrique d'une trempe sur un cylindre avec echange convectif avec l'air ambient. La… P:PASAPAS
ray (13K) CAVITE RECTANGULAIRE - Couplage Convection Naturelle_Rayonnement DEN/DM2S/SFME/LTMF Juillet2002 A.Stietel / G.Forestier (méthode 1: avec calcul de la matride de… P:EXEC,RAY
steinb (10K) TEST DE VALIDATION D'UNE LOI DE COMPORTEMENT DE MATERIAU LOI DE COMPORTEMENT DE: STEINBERG-COCHRAN-GUINAN MAILLAGE: UNE BARRE DE SECTION CARREE LONGUEUR L=.5 M LARGEUR… P:PASAPAS
ther-perm (4K) Test Ther-perm.dgibi: Jeux de données Calcul d'une plaque infinie (de largeur 2L) avec une source volumique et température imposéé sur les bords. Conductivité dépend… P:THERMIC
ther1 (6K) Test ther1.dgibi: jeux de données SI GRAPH = N PAS DE GRAPHIQUE AFFICHE SINON SI GRAPH DIFFERENT DE N TOUS LES GRAPHIQUES SONT AFFICHES
ther1bis (3K) Test ther1bis.dgibi: jeux de données SI GRAPH = N PAS DE GRAPHIQUE AFFICHE SINON SI GRAPH DIFFERENT DE N TOUS LES GRAPHIQUES SONT AFFICHES
ther2 (9K) Test ther2.dgibi: jeux de données SI GRAPH = N PAS DE GRAPHIQUE AFFICHE SINON SI GRAPH DIFFERENT DE N TOUS LES GRAPHIQUES SONT AFFICHES
ther3 (8K) Test ther3.dgibi: jeux de données SI GRAPH = N PAS DE GRAPHIQUE AFFICHE SINON SI GRAPH DIFFERENT DE N TOUS LES GRAPHIQUES SONT AFFICHES
ther4 (10K) Test ther4.dgibi: jeux de données SI GRAPH = N PAS DE GRAPHIQUE AFFICHE SINON SI GRAPH DIFFERENT DE N TOUS LES GRAPHIQUES SONT AFFICHES
ther4m (23K) TEST DES CL DE TEMPERATURE POUR PY13 CU20 TE10 PR15 TRIDIM: TEMPERATURE IMPOSEE + CONVECTION + FLUX + SOURCE Cet exemple permet de tester les conditions aux limites de…
ther51 (10K) TEST THER51 TEST DES CL DE TEMPERATURE POUR L'ELEMENT COQ2 TEMPERATURE IMPOSEE + CONVECTION + FLUX + SOURCE Ce test permet de v{rifier le bon fonctionnement des divers…
ther62 (11K) TEST THER62 TEST DES CL DE TEMPERATURE POUR coq4 ET coq3 TEMPERATURE IMPOSEE + CONVECTION + FLUX + SOURCE Ce test permet de v{rifier le bon fonctionnement des divers…
ther71 (11K) TEST THER7 TEST DES CL DE TEMPERATURE POUR COQ8 ET COQ6 TEMPERATURE IMPOSEE + CONVECTION + FLUX + SOURCE Ce test permet de v{rifier le bon fonctionnement des divers…
ther7or (8K) Test Ther7or.dgibi: Jeux de données TEST THER7OR TEST DES CL DE TEMPERATURE POUR COQ8 ET COQ6 ORTHOTROPE TEMPERATURE IMPOSEE + CONVECTION + FLUX + SOURCE Ce test permet…
ther8 (12K) CAS TEST DU 91/06/13 PROVENANCE : TEST TEST THER8 TRANSFERT DE CHALEUR AVEC CONVECTION EN 2D Test NAFEMS numero T4 description <- 0.6 m -> D C _____ .----------. | /| |…
tran11 (12K) Copie du cas-test tran9.dgibi mais appel a la procedure NONLINEAIRE au lieu de DUPONT. pour calcul complet mettre complet à : vrai; P:PASAPAS
tran9 (12K) pour calcul complet mettre complet à : vrai; TEST TRAN9 --- Probl}me : Cylindre soumis a un choc froid sur la peau interne --- Description de la g{om{trie : LI2 | 1| 2 |… P:PASAPAS
wsgg (18K) CONVECTION-RAYONNEMENT + VAPEUR D'EAU ********** Couplage convection naturelle laminaire/rayonnement milieu absorbant Convection naturelle horizontale dans une cavite… P:EXEC

## Thermique Diffusion (10)
lapnef2 (4K) cas test lapnvf2.dgibi Cas Test pour l'operateur LAPN version EF avec primal<>dual On cherche la solution stationnaire d'un problème de diffusion thermique sur un disque… P:EXEC
lapnvf (4K) cas test lapnvf.dgibi Cas Test pour l'operateur LAPN version VF On cherche la solution stationnaire d'un problème de diffusion thermique sur un disque où on impose une… P:EXEC
lapnvf2 (5K) cas test lapnvf2.dgibi Cas Test pour l'operateur LAPN version VF On cherche la solution stationnaire d'un problème de diffusion thermique sur un disque où on impose une… P:EXEC
lapnvf3 (4K) cas test lapnvf3.dgibi Cas Test pour l'operateur LAPN version VF On cherche la solution stationnaire d'un problème de diffusion thermique sur un disque où on impose une… P:EXEC
rayo_abs-2D-1 (9K) Calcul de la température d'une cavité carrée contenant un milieu absorbant (Tg,k_abs) DONNEES cavité cylindrique de cote 1. 1000K e=1.0 e=0.5 | | e=0.5 | | 2000K e=0.1… P:HRCAV
rayo_abs-2D-2 (6K) pour calcul complet mettre complet à : vrai; Rayonnement thermique en milieu absorbant dans une cavité cylindrique (pas de couplage avec d'autres modes de transfet… P:HRCAV
rayo_abs-3D-1 (6K) pour calcul complet mettre complet à : vrai; Rayonnement thermique en milieu absorbant dans une cavité sphérique (pas de couplage avec d'autres modes de transfert… P:HRCAV
rayo_abs-axi-1 (5K) Rayonnement thermique en milieu absorbant dans une cavité sphérique (pas de couplage avec d'autres modes de transfet d'énergie) Comparaison à un calcul analytique Ref:… P:HRCAV
rayo_abs-axi-2 (9K) Calcul de la température d'une cavité contenant un milieu absorbant (Tg,k_abs) DONNEES cavité cylindrique de cote 1. 1000K e=1.0 axe | | e=0.5 | | 2000K e=0.1 RESULTATS:… P:HRCAV
tran4 (5K) Test tran4.dgibi: jeux de données SI GRAPH = N PAS DE GRAPHIQUE AFFICHE SINON SI GRAPH DIFFERENT DE N TOUS LES GRAPHIQUES SONT AFFICHES P:PASAPAS

## Thermique Hydraulique (5)
nlin_cavity_HP (64K) NOM : nlin_cavity_HP.dgibi DESCRIPTION : We compute the flow governed by the Navier-Stokes equations, in a square cavity with high temperature difference. Both… P:ININLIN,RAY
nlin_decent1d (41K) BEGINPROCEDUR gmass NOM : GMASS DESCRIPTION : Une matrice de masse LANGAGE : GIBIANE-CAST3M AUTEUR : Stéphane GOUNAND (CEA/DEN/DM2S/SFME/LTMF) mél :… P:@POMI,@STBL,ININLIN
nlin_decent2d (42K) BEGINPROCEDUR gmass NOM : GMASS DESCRIPTION : Une matrice de masse LANGAGE : GIBIANE-CAST3M AUTEUR : Stéphane GOUNAND (CEA/DEN/DM2S/SFME/LTMF) mél :… P:@POMI,@STBL,ININLIN,MONTAGNE
nlin_int_surface (7K) _cmt = 'CONTOUR' _mt ; _mt = 'CHANGER' mt 'QUAF' ; _cmt = 'DOMA' ('MODELISER' _mt 'NAVIER_STOKES' 'LINE') 'ENVELOPPE' ; P:ININLIN
palier_stationnaire_coq4 (11K) Mots-clés : machines tournantes, palier, hydrodynamique, lubrification equation de Reynolds ETUDE DU CHAMP DE PRESSION D'UNE LAME FLUIDE ENTRE 2 CYLINDRES CONCENTRIQUES…

## Thermique Mecanique (6)
dilthe (4K) fichier dilthe.dgibi NOM : DILTHE DESCRIPTION : Dilatation thermique d'un cube encastre sur deux faces opposees Ce cas-test sortait en erreur de non-convergence dans les… P:PASAPAS
joi44 (7K) Test Joi44.dgibi: Jeux de données TEST JOI44 CALCUL DES CONTRAINTES THERMIQUES SUR UN JOINT 3D Un joint 3D JOI4 a sa surface inferieure encastree. Sa surface superieure…
joi45 (11K) Test Joi45.dgibi: Jeux de données TEST JOI45 ESSAI DE CISAILLEMENT SUR UN JOINT 3 ORTHOTROPE Un joint 3D JOI4 a sa surface inferieure encastree. Sa surface superieure…
lyre3 (6K) CAS TEST DU 91/06/13 PROVENANCE : TEST Test lyre3.dgibi: jeux de données SI GRAPH = N PAS DE GRAPHIQUE AFFICHE SINON SI GRAPH DIFFERENT DE N TOUS LES GRAPHIQUES SONT…
plas12 (8K) Test Plas12.dgibi: Jeux de données TEST PLAS12 Un tuyauderie encastré en deux extremités soumis à un choc thermique. GEOMETRIE : Longueur du tuyau l : 1000. mm Rayon… P:PASAPAS
pore2 (14K) Test Pore2.dgibi: Jeux de données pour calcul complet mettre complet à : vrai; TEST PORE2 CYLINDRE EPAIS EN MILIEU POREUX AVEC EFFETS THERMIQUES REFERENCE : Benchmark… P:PASAPAS,PECHE

## Thermique Metallurgie (3)
metallurgie_06 (20K) TEST METALLURGIE_06 CALCUL DES PROPORTIONS DE PHASE METALLURGIQUE Un MODELE thermo-metallurgique est P:@MOD,@REPERE,PASAPAS
metallurgie_07 (28K) TEST METALLURGIE_07 CALCUL DES PROPORTIONS DE PHASE METALLURGIQUE CALCUL DE LA DEFORMATION THERMIQUE METALLURGIQUE TEMPERATURE IMPOSEE DURANT TOUT LE CALCUL Un modele… P:@MOD,@REPERE,PASAPAS
simtrc (11K) simtrc.dgibi Simulation du trc avec l'operateur comp Prise en compte de la concentration en carbone (cte) version initiale : Martinez le 30/07/98 mettre complet = vrai… P:TRC

## Thermique ProprietesVariables (1)
test_vari_props (7K) FRA Exemple simple de definition d'une proriete thermique variable fonction de 1 parametre (EVOL) ou plusieurs parametres (NUAGE) Simulation axisymetrique d'une trempe… P:PASAPAS

## Thermique Rayonnement (13)
rayo-2D-1 (5K) test 2D couplage conduction-rayonnement REFERENCE: SPARROW CESS "Radiation Heat Transfer" 1978 p.189 DONNEES cas de 2 ailettes angle entre les ailettes : 45 degres…
rayo-2D-2 (8K) test 2D couplage conduction-rayonnement REFERENCE: cas TPNP 01/89 du guide VPCS DONNEES cavité carrée de cote 1. 1000K e=1.0 e=0.5 | | e=0.5 | | 2000K e=0.1 RESULTATS… P:HRCAV
rayo-2D-3 (7K) Rayonnement thermique en milieu transparent: vérification du bon fonctionnement de l'opérateur FFOR dans le cas général (traitement des parties cachées) sur un cas…
rayo-2D-4-bis (10K) Calcul d'une plaque infinie (de largeur 2L) soumise à de la convection et du rayonnement. Modélisation plane. Auteurs : Michel Bulik & Nadia Coulon Date : Octobre 1995… P:PASAPAS,PECHE
rayo-2D-4 (10K) Calcul d'une plaque infinie (de largeur 2L) soumise à de la convection et du rayonnement. Modélisation plane. Auteurs : Michel Bulik & Nadia Coulon Date : Octobre 1995… P:PASAPAS,PECHE
rayo-2D-5 (6K) Calcul d'une plaque infinie (de largeur 2L) avec tempé- rature imposée au milieu et soumise au rayonnement. Il s'agit de trouver la température au bord en régime… P:PASAPAS
rayo-3D-1 (8K) test 3D couplage conduction-rayonnement REFERENCE: cas TPNV 02/89 du guide VPCS DONNEES cavité cubique de cote 1. 1000K e=1.0 e=0.5 | | e=0.5 | | 2000K e=0.1 RESULTATS… P:PASAPAS
rayo-3D-2 (7K) pour calcul complet mettre complet à : vrai; Rayonnement thermique en milieu transparent: vérification du bon fonctionnement de l'opérateur FFOR dans le cas général…
rayo-axi-1 (5K) CONDUCTION-RAYONNEMENT 2D- axisymetrique permanent facteurs de forme : option convexe Reference : Engelman Int.J.for Num.Fluids 1991 Vol.13 Le domaine est un cylindre…
rayo-axi-2 (7K) pour calcul complet mettre complet à : vrai; Rayonnement thermique en milieu transparent: vérification du bon fonctionnement de l'opérateur FFOR dans le cas général…
rayo-axi-4 (4K) Ce jeu de données permet la vérification du calcul des facteurs de forme dans le cas axisymétrique. On calcule le flux dû au rayonnement entre 2 sphères concentriques,…
rayoh-2D (7K) Rayonnement thermique en milieu transparent: Test de bon fonctionnement de la procédure HRAYO permettant de traiter le rayonnement face à face ou avec un milieu infini.… P:HRAYO
rayoh-3D (8K) Rayonnement thermique en milieu transparent: Test de bon fonctionnement de la procédure HRAYO permettant de traiter le rayonnement face à face par comparaison à une… P:HRAYO

## Thermique Statique (14)
arcgau (3K) pour calcul complet mettre complet à : vrai; Test de la procedure ARCGAU : Calcul du champ de température créé par le déplacement d'un arc de soudure, de la largeur de… P:ARCGAU
equ_chaleur2D (12K) NOM : equ_chaleur2D.dgibi DESCRIPTION : Solution stationnaire de l'équation de la chaleur (2D) GEOMETRIE : Un carré ! (il sera translaté et tourné) y ^ y=1 |------------… P:EXEC
equ_chaleur2D_tenseur_VF2 (13K) NOM : equ_chaleur2D_VF2_tenseur.dgibi DESCRIPTION : Solution stationnaire de l'équation de la chaleur (2D) GEOMETRIE : Un carré y ^ y=1 |------------ | | | | | | |x = 0… P:@POMI
equ_chaleur2D_tenseur_VF2vfsym (13K) NOM : equ_chaleur2D_VF2_tenseur.dgibi DESCRIPTION : Solution stationnaire de l'équation de la chaleur (2D) GEOMETRIE : Un carré y ^ y=1 |------------ | | | | | | |x = 0… P:@POMI
equ_chaleur2D_VF (14K) NOM : equ_chaleur2D_VF.dgibi DESCRIPTION : Solution stationnaire de l'équation de la chaleur (2D) GEOMETRIE : Un carré y ^ y=1 |------------ | | | | | | |x = 0 |x=1 | |… P:@POMI
equ_chaleur2D_VF2 (15K) NOM : equ_chaleur2D_VF2.dgibi DESCRIPTION : Solution stationnaire de l'équation de la chaleur (2D) GEOMETRIE : Un carré y ^ y=1 |------------ | | | | | | |x = 0 |x=1 | |… P:@POMI
equ_chaleur2D_VFcyl (14K) NOM : equ_chaleur2D_VFcyl.dgibi DESCRIPTION : Solution stationnaire de l'équation de la chaleur (3D) dans un doamine cylindrique GEOMETRIE : 1 < r < 2 EQUATIONS : -… P:@POMI
equ_chaleur3Dtet (9K) NOM : equ_chaleur3Dtet.dgibi DESCRIPTION : Solution stationnaire de l'équation de la chaleur (3D) GEOMETRIE : Un cube de côté 1 (il sera translaté et ---------- tourné)… P:EXEC
equ_chaleur3D_VF (17K) NOM : equ_chaleur3D_VF.dgibi DESCRIPTION : Solution stationnaire de l'équation de la chaleur (3D) GEOMETRIE : Un cube de côté 1 maillé avec 'VOLU'. EQUATIONS : EQUATIONS… P:@POMI
equ_chaleur3D_VF2 (14K) NOM : equ_chaleur3D_VF2.dgibi DESCRIPTION : Solution stationnaire de l'équation de la chaleur (3D) GEOMETRIE : Un cube de côté 1 maillé avec 'VOLU'. EQUATIONS : -… P:@POMI
equ_chaleur3D_VFconv (17K) NOM : equ_chaleur3D_VFconv.dgibi DESCRIPTION : Solution stationnaire de l'équation de la chaleur (3D) GEOMETRIE : Un cube de côté 1 maillé avec 'VOLU'. EQUATIONS :… P:@POMI
equ_chaleur3D_VFcyl (15K) NOM : equ_chaleur3D_VFcyl.dgibi DESCRIPTION : Solution stationnaire de l'équation de la chaleur (3D) dans un doamine cylindrique GEOMETRIE : 1 < r < 2 EQUATIONS : -… P:@POMI
equ_chaleur3D_VFSYM (13K) NOM : equ_chaleur3D_VF.dgibi DESCRIPTION : Solution stationnaire de l'équation de la chaleur (3D) GEOMETRIE : Un cube de côté 1 maillé avec 'VOLU'. EQUATIONS : EQUATIONS… P:@POMI
equ_chaleurVF2_dirneummixte (14K) NOM : equ_chaleurVF2_dirneummixte.dgibi DESCRIPTION : Solution stationnaire de l'équation de la chaleur (2D) GEOMETRIE : Un carré y ^ y=1 |------------ | | | | | | |x =… P:@POMI

## Thermique Transitoire (11)
b52c (7K) D3 D4 S1 D2 P1 D1 P2 Tube P:PASAPAS
couplage_thermique (12K) ------------ Cas test couplage_thermique.dgibi -------------------- Tests des opérateurs de Castem-fluide - Options générales P:EXEC
couplage_thermique2 (9K) ------------ Cas test couplage_thermique2.dgibi ------------------- Tests des opérateurs de Castem-fluide - Options générales P:EXEC
couplage_thermique3 (13K) ------------ Cas test couplage_thermique3.dgibi ------------------- Tests des opérateurs de Castem-fluide - Options générales
dfdtsour (8K) cas test dfdtsour.dgibi Test élémentaire de l'opérateur DFDT (discrétisation temporelle). On résoud dc/dt = s avec s densité de source ([c]/s/m3) : L'opérateur DFDT… P:EXEC
faceaface (9K) ......../........./........./........./........./........./........./72 test de cacul FACE a FACE avec PASAPAS Echange thermique entre deux faces proches (L/e>>10) , en… P:JEU,PASAPAS
faceaface2 (10K) Rayonnement thermique en milieu transparent: Test du rayonnement face à face Comparaison avec une solution analytique en régime permanent. Calcul par 2 méthodes: 1.… P:HRAYO,PASAPAS
faceaface3 (10K) ......../........./........./........./........./........./........./72 test de calcul FACE a FACE avec PASAPAS Echange thermique entre deux faces proches (L/e>>10) , en… P:JEU,PASAPAS
murh (48K) Thermique Conduction dans un mur avec source et échange thermique. Comparaison à la solution analytique en régime permanent. Teste les opérateurs LAPN ECHI FIMP DFDT La… P:EXAC,EXEC,VERTYTAB,VNIMP
tran10 (5K) Copie du cas-test "tran8.dgibi" mais appel a la procedure de resolution NONLINEAIRE (meme si pb. lineaire). Test tran10.dgibi: jeux de données SI GRAPH = N PAS DE… P:PASAPAS,PECHE
tran8 (5K) CAS TEST DU 91/06/13 PROVENANCE : TEST Test tran8.dgibi: jeux de données SI GRAPH = N PAS DE GRAPHIQUE AFFICHE SINON SI GRAPH DIFFERENT DE N TOUS LES GRAPHIQUES SONT… P:PASAPAS,PECHE
