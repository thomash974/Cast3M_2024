# Documentation officielle Cast3M 2024 (extraits)

## Note de version de Cast3M 2024
Assurance Qualité CAST3M
Cast3M 2024
Note de version de
Cast3M 2024
NOTE DE VERSION DE CAST3M 2024
Cast3M est un logiciel de calcul par la méthode des éléments finis pour la
mécanique des structures et des fluides. Cast3M est développé au Département de
Modélisation des Systèmes et Structures (DM2S) de la Direction des Énergies
(DES) du Commissariat à l’Énergie Atomique et aux Énergies Alternatives (CEA).
Le développement de Cast3M entre dans le cadre d’une activité de recherche dans
le domaine de la mécanique dont le but est de définir un instrument de haut niveau,
pouvant servir de support pour la conception, le dimensionnement et l’analyse de
structures et de composants.
Dans cette optique, Cast3M intègre non seulement les processus de résolution
(solveur) mais également les fonctions de construction du modèle (pré-
processeur) et d’exploitation des résultats (post-traitement). Cast3M est un
logiciel « boîte à outils » qui permet à l’utilisateur de développer des fonctions
répondant à ses propres besoins.
Cast3M est notamment utilisé dans le secteur de l’énergie nucléaire, comme outil
de simulation ou comme plateforme de développement d’applications spécialisées.
En particulier, Cast3M est utilisé par l’Institut de Radioprotection et de Sûreté
Nucléaire (IRSN) dans le cadre des analyses de sûreté des installations nucléaires
françaises.
NOTE DE VERSION DE CAST3M 2024
SOMMAIRE
ASSURANCE QUALITE CAST3M
1. INTRODUCTION
PROCESSUS DE DEVELOPPEMENT DE CAST3M
PROCESSUS DE FABRICATION D’UNE VERSION ANNUELLE
DATES RELATIVES A LA FABRICATION DE LA VERSION 2024 DE CAST3M
OBJET DU DOCUMENT
2. PRÉSENTATION DES FICHES D’ANOMALIE
ANOMALIES CLOTUREES
ANOMALIES DEMEURANT OUVERTES
3. PRESENTATION DES FICHES DE DÉVELOPPEMENT
DEVELOPPEMENTS CLOTURES
DEVELOPPEMENTS DEMEURANT OUVERTS
4. DESCRIPTION DES NOUVELLES FONCTIONNALITES DE CAST3M 2024
PROCEDURES ERREUR ! SIGNET NON DEFINI.
LOIS EXTERNES ERREUR ! SIGNET NON DEFINI.
LANGAGE
MAILLAGE – POST-TRAITEMENT – VISUALISATION – AFFICHAGE
MODELES – CALCULS
FLUIDES
ENTREE/SORTIE
DOCUMENTATION – SITE WEB
5. DESCRIPTION DES NOUVELLES FONCTIONNALITES DES SCRIPTS
SCRIPT CASTEM23
SCRIPT COMPILCAST24
SCRIPT ESSAICAST24
SCRIPT SYNCHRONISATION_CAST3M24
NOTE DE VERSION DE CAST3M 2024
1. INTRODUCTION
PROCESSUS DE DEVELOPPEMENT DE CAST3M
Le développement de Cast3M est réalisé dans le cadre d’un processus d’amélioration continue constitué
d’évolutions. Ces évolutions sont de deux types : soit des développements, soit des corrections d’anomalie.
Chaque évolution est discutée en réunion de développement (tous les premiers mercredis ouvrés de
chaque mois), puis réalisée.
L’atelier logiciel de Cast3M en assure le contrôle, grâce à une fonction de verrouillage/déverrouillage des
sources, et la traçabilité, par la rédaction de fiches d’évolution, dont le référencement et l’horodatage sont
associés à ceux des fichiers.
Chaque évolution est validée par l’exécution automatique de la base des cas-tests de vérification et de
validation de Cast3M. La mise en défaut d’un cas-test génère automatiquement une fiche d’anomalie, donc
la nécessité d’une correction. Le versement de nouveaux cas-tests est intégré au processus d’évolution.
L’ensemble des fiches d’évolution est répertorié dans le fichier :
/home/castem-public/castem/hist.hist
sur le serveur de fichier Titania du CEA DM2S. Elles sont également consultables sur le site Cast3M
(https://www-cast3m.cea.fr/index.php?page=anomalies). Au 1er avril 2024, 11 649 fiches d’évolution ont
été émises depuis la mise en service de l’atelier logiciel le 28 juin 1988.
PROCESSUS DE FABRICATION D’UNE VERSION ANNUELLE
Les versions annuelles de Cast3M sont construites à partir de la version de développement de l’année
précédente. La version 2024 de Cast3M est ainsi fabriquée à partir des sources de la version de
développement figée au 31 décembre 2023.
Le processus de fabrication d’une version annuelle de Cast3M comporte au moins quatre phases. Pour la
version 2024, ces phases ont été :
- Phase 1, le 31/12/2023 :
Saisie de la version de développement de Cast3M. Les sources C, FORTRAN-ESOPE, les procédures,
les notices, les cas-tests et les fichiers d’erreurs sont figés à cette date.
- Phase 2, du 01/01/2024 au 31/03/2024 :
Intégration des corrections d’anomalies, les nouveaux développements sont omis.
- Phase 3, du 01/04/2024 au 15/04/2024 :
Portage sur les plateformes de distribution (Windows 64-bits et GNU/Linux 64-bits). Cette phase
est détaillée dans la Note de Fabrication de Cast3M 2024.
- Phase 4, du 15/04/2024 au 31/05/2024 :
Packaging et test des distributions de Cast3M (Windows 64-bits et GNU/Linux 64-bits).
Mise en ligne des paquets d’installation de Cast3M 2024 sur le site Cast3M :
https://www-cast3m.cea.fr/.
DATES RELATIVES A LA FABRICATION DE LA VERSION 2024 DE CAST3M
Fin des saisies de la version 2024 :
 La saisie des développements s’est terminée le 01/01/2024.
Certains développements importants ont été intégrés à la version 2024 après cette date. La liste
des fiches de développement correspondante est la suivante : 11811, 11839, 11851, 11889 11904.
Aucun autre développement n’a été pris en compte après cette date dans la version 2024.
 La saisie des corrections s’est terminée le 31/03/2024 (fiche de d’anomalie 11877).
NOTE DE VERSION DE CAST3M 2024
Certaines corrections ultérieures ont cependant été intégrées à la version 2024 après cette date, La
liste des fiches de correction d’anomalies correspondante est la suivante : 11889, 11896.
Aucune autre évolution n’a été prise en compte après cette date dans la version 2024.
OBJET DU DOCUMENT
Ce document recense les fiches d’anomalie et de développement relatives à la version 2024 de Cast3M.
Nous présentons tout d’abord les fiches d’anomalie, en distinguant celles ayant été clôturées
(paragraphe 2.1) de celles demeurant ouvertes (paragraphe 2.2). Puis, nous faisons de même pour les
fiches de développement (paragraphes 3.1 et 3.2).
Chaque fiche est référencée par son numéro. Toutes les fiches d’anomalies et de développement sont
accessibles sur le Site Cast3M, rubrique anomalies : https://www-
cast3m.cea.fr/index.php?page=anomalies
NOTE DE VERSION DE CAST3M 2024
2. PRÉSENTATION DES FICHES D’ANOMALIE
ANOMALIES CLOTUREES
Voici la liste des numéros des fiches d’anomalie clôturées dans la première révision de la version 2024 de
Cast3M :
10699, 11208, 11576, 11590, 11591, 11593, 11595, 11596, 11597, 11601, 11604, 11605, 11606, 11607,
11609, 11651, 11652, 11653, 11654, 11655, 11656, 11659,11661, 11662, 11663, 11664, 11665, 11667,
11668, 11670, 11671, 11673, 11674, 11675, 11676, 11677, 11678, 11679, 11680, 11681, 11682, 11683,
11684, 11685, 11686, 11687, 11688, 11689, 11690, 11691, 11692, 11693, 11694, 11695, 11699, 11700,
11701, 11702, 11703, 11704, 11705, 11707, 11711, 11712, 11713, 11714, 11718, 11719, 11720, 11721,
11723, 11724, 11725, 11726, 11727, 11728, 11729, 11730, 11733, 11735, 11737, 11740, 11741, 11742,
11743, 11746, 11748, 11749, 11750, 11754, 11756, 11757, 11762, 11763, 11765, 11771, 11772, 1173,
11774, 11776, 11778, 11779, 11780, 11781, 11782, 11786, 11788, 11792, 11793, 11797, 11801, 11803,
11805, 11806, 11812, 11814, 11815, 11816, 11818, 11820, 11821, 11828, 11832, 11833, 11834, 11835,
11836, 11837, 11840, 11842, 11844, 11850, 11852, 11853, 11860, 11861, 11862, 11866, 11868, 11877,
11896, 11904, 11923, 11948.
ANOMALIES DEMEURANT OUVERTES
De nombreuses anomalies demeurent ouvertes. La plupart sont aujourd’hui sans objet suite aux évolutions
du logiciel ; d’autres n’ont jamais été corrigées car elles sont anecdotiques ou sont juste des erreurs
d’évolution émises automatiquement et homologues à d’autres déjà fermées. Nous en donnons tout de
même la liste exhaustive car cela démontre la traçabilité du processus de développement. Voici donc la liste
des numéros des fiches d’anomalie demeurant ouvertes dans la version 2024 de Cast3M depuis la mise à
disposition de la version 2023 de Cast3M.
11669, 11715, 11716, 11732, 11734, 11737, 11751, 11752, 11753, 11758, 11761, 11766, 11767, 11768,
11775, 11777, 11787, 11788, 11791, 11794, 11796, 11802, 11804, 11923.
3. PRESENTATION DES FICHES DE DÉVELOPPEMENT
DEVELOPPEMENTS CLOTURES
Voici la liste des numéros des fiches de développement clôturées dans la première révision de la version
2024 de Cast3M :
8699, 10699, 11248, 11258, 11266, 11273, 11280, 11284, 11286, 11287, 11291, 11292, 11294, 11305,
11317, 11321, 11326, 11329, 11332, 11339, 11341, 11342, 11355, 11356, 11359, 11370, 11371, 11372,
11377, 11378, 11392, 11394, 11395, 11396, 11397, 11399, 11403, 11408, 11409, 11411, 11416, 11419,
11424, 11426, 11428, 11430, 11454, 11455, 11456, 11458, 11459, 11461, 11462, 11469, 11474, 11475,
11481, 11494, 11502, 11503, 11507, 11508, 11510, 11511, 11513, 11514, 11516, 11521, 11522, 11529,
11530, 11542, 11549, 11562, 11574, 11579, 11587, 11588, 11589, 11592, 11602, 11610, 11616, 11617,
11619, 11626.
DEVELOPPEMENTS DEMEURANT OUVERTS
Comme pour les fiches d’anomalie, de nombreuses fiches de développement demeurent ouvertes. Pour les
mêmes raisons que précédemment, nous en donnons tout de même la liste exhaustive. Voici donc la liste
des numéros des fiches de développement demeurant ouvertes dans la version 2024 de Cast3M depuis la
mise à disposition de la version 2023 de Cast3M.
Aucune fiche de développement n’est restée ouverte depuis la version 2023 de Cast3M.
NOTE DE VERSION DE CAST3M 2024
4. DESCRIPTION DES NOUVELLES FONCTIONNALITÉS DE CAST3M 2024
LANGAGE
 Procédures
Désormais, les variables d’environement permettant de lire les procédures/notices utilisateurs
sont renomé avec le numéro de version à la fin tel que CASTEM_PROCEDUR[version] et
CASTEM_NOTICE[version]. Dans la version 2024, Cela sera donc CASTEM_PROCEDUR24 et
CASTEM_NOTICE24.
 Généralités
Formalisme HHO
ETG (ET Généralisé) : extension aux objets LISTOBJE
Parallélisation automatique : vectorisation des opérations sur les objets LISTOBJE en GIBIANE
(dans le cas OPTI PARA VRAI;) voir : waam4.dgibi
TIRE : étendu aux CHARGEMENTS de LISTOBJE de POINT. Voir : waam4.dgibi
ENUM : création d'un LISTOBJE à partir d'une table indicée par des entiers. Voir : waam4.dgibi
ENUM : création d'un LISTOBJE composé de N fois le même objet. Voir : waam4.dgibi
PROG : création d'un LISTREEL àpartir d'une table indicée par des ENTIER. Voir : waam4.dgibi
MANU CHAM : création d'un champ par éléments nul sauf en un point pour tous les
modèles/formulations, pas seulement mécanique par des entiers. Voir : waam4.dgibi
UNIQ : renvoit le même objet qu'en entrée si ce dernier ne contient pas de doublons.
COUPe : fonctionne maintenant avec tout les types d'éléments. Voir : test_coupe.dgibi. On ne
garantit pas la qualité ni la conformité du maillage obtenu.
Meilleure gestion des noms de variables, procédures, mots-clés de plus de huit caractères (mais
moins de 24), notamment dans les messages d'erreurs.
 Nouveaux opérateur
GAMMA, BESSEL : sortis de FONC : voir gamma.dgibi
 USURE
Les procédures et leur notices, commençant par @us, ont été renommées sans le « @ »
Implementation dans les procedures d'usure des travaux de Q.Caradec permettant :
o D'utiliser un schema de resolution implicite pour appliquer l'usure
o D'utiliser un facteur de saut de cycle adaptatif (relie a l'elargissement de la zone de contact).
Fiche d’anomalie 11833
MAILLAGE – POST-TRAITEMENT – VISUALISATION – AFFICHAGE
 Généralités
CONGE : ne fonctionnait plus sur les SEG3. Voir : conge_seg2_seg3.dgibi
 Nouveaux opérateurs
FREN calcule le repère de Frenet le long d’une ligne de SEG2 ou SEG3 cas test (frenet_1.dgibi)
 Visualisation
UNIQ ORDO : élimine deux éléments ayant les mêmes noeuds, uniquement si les noeuds sont décrits
de la même façon.
LEGENDE : aide à la création des légendes pour l'opérateur DESSIN.
o Extension aux objets EVOLUTION
Opérateur NTAB : affichage de tableaux de valeurs
o Donner des noms de lignes et de colonnes avec des LISTMOTS
PostScript : ajout de la police CourierBold
o OPTI POTR COURIERB_14
Shell-scripts (Rubrique Utilitaires du site Web)
NOTE DE VERSION DE CAST3M 2024
o Traitement des fichiers PostScript Cast3M : psjoin, pssplit, cast-post et pstogif (peut aussi
générer des vidéos au format MP4)
MODELES – CALCULS
 Généralités
Ajout des éléments à intégration réduite C20R et P15R. voir : GTN_C20R.dgibi
Ajout des éléments quadratiques complets (CU27, PR21, TE15, PY19) en mécanique des structures
(opérateurs BSIG, RIGI, et EPSI)
Travaux sur l'intégration sélective (option BBAR) éléments linéaires et quadratiques (opérateurs
RIGI, MASS et KSIG). Voir channeldie*.dgibi
 Modèles
Modèles de conditions aux limites variables, formulation CONTRAINTE : ROTATION,
DEPLACEMENT ou RELATION + maillage.
Matériau : valeur de la condition
Actualisation des Raideurs et Forces liées aux COntraintes/COntacts : RFCO
 Béton
Modèles FLUENDO3D ENDO3D INCLUSION3D (fluage-plasticité-endommagement)
Voir : fluendo_*.dgibi, inclusion3d_*.dgibi
 Fatigue
Opérateurs RAINFLOW et COMT : post-traitement de résultats fournis par DYNE, comptabilisation
du nombre de cycles et de leur amplitude par la méthode RAINflow et passage à la moyenne.
 Mécanique de la rupture
Modèles FLUENDO3D ENDO3D INCLUSION3D
Modèle de GURSON2 (plastique endommageable ductile) : ajout des paramètres Q2 et Q3
(auparavant fixés).
 Thermique / Diffusion
TRANSNON : Prise en charge automatique de la gestion de la cinétique thermique dans le cadre des
modèles métallurgiques. Voir : metallurgie_06.dgibi et metallurgie_07.dgibi
TRANSNON : réactions (flux thermiques) correctement calculés.
SOUR et ADVE : fonctionnement possible sur les modèles contenant plusieurs sous-modèles
(tuyaux, coques, massifs)
 Soudage
Possibilité de spécifier des évènements en cours de soudage/fabrication additive. Voir :
wamm5.dgibi
Fonctionnement du modèle de CHABOCHE2 avec l'option FUSION. Voir : fusion2.dgibi
RENDSOUR : utilitaire de calcul de rendement d'une source de chaleur.
 Electomagnétisme
Calcul du potentiel vecteur en 3D (Nikola Gérance), Opérateurs MPMA, JPMA, JPMM. Voir :
calcul_inductance_ppipede.dgibi
 PASAPAS
Corrections
PILOINDI : procédure utilisateur pour piloter le chargement mécanique de façon indirecte. Deux
nouveaux exemples : pilotage_indirect_1_cmep.dgibi et pilotage_indirect_1_cndi.dgibi.
Amélioration des reprises/poursuites de calcul. Documentation des mots clés REPRISE et
REEQUILIBRAGE. Voir: reprise_1.dgibi
Recalcul de la raideur si résolution impossible (UNPAS)
Améliorations dans le traitement de la stabilité et de l'augmentation (UNPAS)
NOTE DE VERSION DE CAST3M 2024
Correction d'un bug sur les calculs mécaniques coques avec chargement thermique. Voir :
ther_meca_coque.dgibi
Correction d'un bug sur les calculs thermo-mécaniques avec amilllages différents en thermique et
en mécanique. Voir thermo_meca_projection_1.dgibi
 Contact - Frottement
Diverses améliorations de robustesse et de résolution.
FLUIDES
 Modèles
Création d'un modèle en mécanique des fluides (NAVIER_STOKES) fonctionnant comme en
mécanique des structures. Voir oscicyl2.dgibi (EXPERIMENTAL)
 EXECRXT : modélisation accident grave enceinte de réacteur nucléaire.
CONDENS : amélioration de la procédure de modélisation de la condensation en paroi.
ENTREE/SORTIE
 Passage à MED 64-bit
 Opérateur SORT CSV
DEBU et FIN pour sauter les entêtes, lire jusqu'à une certaine ligne. Voir : lire_CSV.dgibi
 Opérateur SORT MED
Amélioration lecture-écriture format MED : écriture de la numérotation globale pour lecture //
 Lois de comportement externes
MFront (compatibilités avec les versions 4.x)
Gestion MacOS X arm
DOCUMENTATION – SITE WEB
 Formation Cast3M
Nouvelle formation à la simulation de la fabrication additive.
Actualisation des supports de formations et des cas-tests.
 Documentation
Actualisation des notices vis-à-vis des développements réalisés
Guide de validation de Cast3M en Mécanique des fluides.
 Support Cast3M : Adresse de contact support-cast3m@cea.fr
 Site Web : https://www-cast3m.cea.fr
NOTE DE VERSION DE CAST3M 2024
5. DESCRIPTION DES NOUVELLES FONCTIONNALITÉS DES SCRIPTS
SCRIPT CASTEM24
Manuel du script :
 castem24 --aide (manuel en français) ;
 castem24 --help (manuel en anglais).
SCRIPT COMPILCAST24
Manuel du script :
 compilcast24 --aide (manuel en français) ;
 compilcast24 --help (manuel en anglais).
Une source Esope ne peut être recompilée que si son numéro de version est supérieur ou égal à celui de la
version installée, sauf si l’option ‘--nodate’ est fournie au script.
Utilisation par défaut des compilateurs GCC distribués avec la version 2024 :
 Windows-x86_64 : winlibs-x86_64-posix-seh-gcc-13.2.0-llvm-18.1.1-mingw-w64msvcrt-
11.0.1-r6
 Linux-x86_64 : GCC 13.2.0
SCRIPT ESSAICAST24
Manuel du script :
 essaicast24 --aide (manuel en français) ;
 essaicast24 --help (manuel en anglais).
Utilisation par défaut des compilateurs GCC distribués avec la version 2024 :
 Windows-x86_64 : winlibs-x86_64-posix-seh-gcc-13.2.0-llvm-18.1.1-mingw-
w64msvcrt-11.0.1-r6
 Linux-x86_64 : GCC 13.2.0
 MacOS arm64 GCC 13.2.0
SCRIPT SYNCHRONISATION_CAST3M24
Ce script permet d’effectuer la synchronisation d’un répertoire d’installation de Cast3M avec un dépôt.
Manuel du script :
 synchronisation_Cast3M24 --aide (manuel en français) ;
 synchronisation_Cast3M24 --help (manuel en anglais).
Argument obligatoire
Un répertoire dépôt doit obligatoirement être indiqué à l'aide de l'option suivante :
 --repertoire_depot=VAL1 : Chemin absolu d'un dépôt pour Cast3M.
La structure du dépôt doit être la suivante :
o castem.arc (ou sources/) : archive (répertoire) contenant les sources (fichiers .eso ou .c)
o procedur/ : répertoire contenant les procédures (fichiers .procedur)
o dgibi/ : répertoire contenant les exemples (fichiers .dgibi)
o notice/ : répertoire contenant les notices (fichiers .notice)
o include/ : répertoire contenant les includes (fichiers .INC ou .h)
Arguments optionnels :
Les arguments présentés ci-dessous sont optionnels.
 -- repertoire_final=VAL2 : Chemin absolu du répertoire d'installation de la version synchronisée.
L'installation ne pourra pas être effectuée si le répertoire VAL2 existe déjà, à moins que '--
reprise=1' soit fourni.
Par défaut, l’installation est effectuée dans le répertoire :
NOTE DE VERSION DE CAST3M 2024
o ${HOME}/CASTEM (sur GNU/Linux)
o C:\Cast3M\PCW (sur Windows)
 --repertoire_initial=VAL3 : Chemin absolu du répertoire de la version de Cast3M à synchroniser.
Par défaut, il s’agit du répertoire d'installation Cast3M de ce script.
 --fichiers_modifies=VAL4 : Pour considérer uniquement certains répertoires du dépôt.
La synchronisation sera effectuée uniquement pour les répertoires du dépôt indiqués dans la liste
VAL4 (nom des répertoires séparés par une virgule).
Par défaut, la synchronisation est effectuée pour tous les répertoires du dépôt.
Si VAL4 est défini à "0", la synchronisation avec le dépôt ne sera pas effectuée.
 --etapes_construction=VAL5 : Pour effectuer seulement certaines étapes de la construction.
Les étapes de construction à effectuer peuvent être indiquées dans la liste VAL5 :
o compilcast :
Si des fichiers '.eso' ou '.c' ont étés synchronisés, alors il seront compilés.
o essaicast :
Le binaire et la librairie Cast3M seront mis à jour. Cette option n'a aucun impact si aucun
fichiers '.eso' ou '.c' n'a été compilé.
Si VAL5 est défini à "0", alors aucune étape de construction ne sera effectuée.
 --compile_fichiers_c=1 : indique que l'on souhaite compiler les fichiers '.c' qui auront étés
synchronisés.
Par défaut, ces fichiers ne sont pas compilés.
Cette option n'a aucun impact si 'compilcast' ne fait pas partie des étapes de construction spécifiées
dans VAL5.
 --reprise=1 : Indique que l'on souhaite continuer une synchronisation dans un répertoire déjà
synchronisé.
Utile, par exemple, si l’on souhaite faire dans un premier temps le rapatriement des sources depuis
le dépôt, puis dans un second temps (reprise) les compilation et édition des liens.
 --verbeux=1 : Des informations supplémentaires seront affichées durant l'exécution.
Exemples d’utilisation :
 La commande suivante permet la synchronisation des sources (fichiers Esope et C) de Cast3M 2024
avec le dépôt /home/castem-public/castem/ dans le répertoire /home/user/CASTEM :
synchronisation_Cast3M24 --repertoire_depot=/home/castem-public/castem/
--repertoire_final=/home/user/CASTEM
--fichiers_modifies=sources
--etapes_construction=0
Détail des opérations effectuées :
o Une copie initiale du répertoire d’installation de Cast3M 2024 est faite dans le répertoire
final (/home/user/CASTEM).
o Les nouvelles sources ainsi que les sources qui présentent des différences avec le dépôt sont
récupérées dans le dossier sources ainsi que dans le dossier synchronisation/AAAA_MM_JJ
du répertoire final.
o Aucune étape de construction n’est effectuée (--etapes_construction=0).
 Dans un second temps, les sources précédemment synchronisées peuvent être compilées à l’aide
de la commande suivante :
synchronisation_Cast3M24 --repertoire_depot=/home/castem-public/castem
NOTE DE VERSION DE CAST3M 2024
--repertoire_final=/home/user/CASTEM
--fichiers_modifies=0
--etapes_construction=compilcast
--reprise=1
 Détail des opérations effectuées :
o Rien à copier puisque le répertoire « /home/user/CASTEM » existe déjà.
o Aucune synchronisation n’est effectuée (--fichiers_modifies=0)
o Les fichiers Esope qui ont été synchronisés dans le dossier synchronisation/AAAA_MM_JJ
du répertoire final sont compilés. Les fichiers C ne sont quant à eux pas compilés puisque
l’option --compile_fichiers_c=1 n’a pas été fournie.
 Dans un troisième temps, le binaire et la librairie Cast3M peuvent être mis à jour à l’aide de la
commande suivante :
synchronisation_Cast3M24 --repertoire_depot=/home/castem-public/castem
--repertoire_final=/home/user/CASTEM
--fichiers_modifies=0
--etapes_construction=essaicast
--reprise=1
 Les trois étapes précédentes peuvent être effectuées en une seule fois à l’aide de la commande
suivante :
synchronisation_Cast3M24 --repertoire_depot=/home/castem-public/castem
--repertoire_final=/home/user/CASTEM
--fichiers_modifies=sources
--etapes_construction="compilcast,essaicast"
NOTE DE VERSION DE CAST3M 2024
Annexe A : Tracabilité
Coller ici une copie de la page des signatures


## Note de fabrication de Cast3M 2024
Assurance Qualité CAST3M
Cast3M 2024
Notes de fabrication de Cast3M
2024
NOTE DE FABRICATION DE CAST3M 2024
Cast3M est un logiciel de calcul par la méthode des éléments finis pour la
mécanique des structures et des fluides. Cast3M est développé au Département de
Modélisation des Systèmes et Structures (DM2S) de la Direction des Énergies
(DES) du Commissariat à l’Énergie Atomique et aux Énergies Alternatives (CEA).
Le développement de Cast3M entre dans le cadre d’une activité de recherche dans
le domaine de la mécanique dont le but est de définir un instrument de haut niveau,
pouvant servir de support pour la conception, le dimensionnement et l’analyse de
structures et de composants.
Dans cette optique, Cast3M intègre non seulement les processus de résolution
(solveur) mais également les fonctions de construction du modèle (pré-
processeur) et d’exploitation des résultats (post-traitement). Cast3M est un
logiciel « boîte à outils » qui permet à l’utilisateur de développer des fonctions
répondant à ses propres besoins.
Cast3M est notamment utilisé dans le secteur de l’énergie nucléaire, comme outil
de simulation ou comme plateforme de développement d’applications spécialisées.
En particulier, Cast3M est utilisé par l’Institut de Radioprotection et de Sûreté
Nucléaire (IRSN) dans le cadre des analyses de sûreté des installations nucléaires
françaises.
NOTE DE FABRICATION DE CAST3M 2024
SOMMAIRE
ASSURANCE QUALITE CAST3M
1. PRESENTATION DE CAST3M 2024
2. PLATEFORMES DE PRODUCTION DE CAST3M
2.2 PC – GNU/LINUX (64 BITS)
2.3 PC – WINDOWS (64 BITS)
2.3 PC – MACOS (64 BITS)
3. ÉLABORATION DE LA VERSION 2024 DE CAST3M
3.1 OBJET
3.2 ÉTAPES DE L’ELABORATION DE LA VERSION
3.3 SCHEMA DE PRINCIPE DE LA PREPARATION DES VERSIONS ANNUELLES DE CAST3M
NOTE DE FABRICATION DE CAST3M 2024
1. PRESENTATION DE CAST3M 2024
Cast3M est un logiciel développé au Commissariat à l'Énergie Atomique et aux Énergies Alternatives (CEA)
qui a pour objet la résolution d’équations aux dérivées partielles par la méthode des éléments finis.
Les domaines d'applications sont la mécanique des structures, la mécanique des fluides, la thermique et la
magnétostatique.
En mécanique des structures, le logiciel permet la résolution de problèmes métier tels que la plasticité, le
flambage, le fluage, l’analyse sismique, la thermo(visco)plasticité, la mécanique de la rupture, le post-
flambage, l’endommagement, la fatigue et la ruine des structures. Les structures étudiées sont 1D, 2D ou
3D et de nombreuses lois de comportement des matériaux sont implémentées.
En mécanique des fluides, de nombreux modèles physiques sont disponibles, notamment des modèles
d’écoulements (écoulements incompressibles ou dilatables, écoulements à faible nombre de Mach,
écoulements compressibles, écoulements multi-espèces réactifs ou non, modèles de turbulence, diphasique
homogène équilibré ou diphasique bi-fluide), des modèles homogénéisés (Navier-Stockes en milieu chargé,
équations d’énergie), des modèles de combustion (cinétique d’Arrhenius, modèles EBU ou corrélations,
modèles de recombineur catalytique), et des modèles de condensation (condensation en paroi – corrélation
Chilton-Colburn, condensation en masse).
En magnétostatique, les possibilités sont les analyses linéaires d'un champ magnétique en 2D ou 3D, les
analyses non linéaires pour des matériaux avec des caractéristiques dépendant du champ magnétique, le
calcul du champ de Biot et de Savart, et en électrostatique les calculs des potentiels scalaire et vecteur.
Cast3M est un code muni d'un langage de mise en données appelé GIBIANE.
L'utilisateur développe des jeux de données GIBIANE appelant des opérateurs qui agissent sur des
opérandes dans le but de créer un résultat. Cast3M peut être considéré comme une boite à outils
comprenant plus de 500 opérateurs mis à la disposition des utilisateurs. Il comprend notamment des
fonctionnalités de maillage et de post-traitement.
Cast3M est disponible sous 2 licences : « éducation et recherche » et « industrielle ».
- La licence « éducation et recherche » est réservée aux organismes de recherche, aux enseignants
ainsi qu’aux étudiants. Elle est gratuite et se décline en version « utilisateur » ou en version
« développeur ». Pour les versions développeur, un exécutable Esope est fourni avec l’exécutable de
Cast3M dans le but de traduire les programmes Esope vers des programmes en Fortran 77. Des
scripts de compilation et d’édition des liens sont également fournis afin de pouvoir construire une
version modifiée de Cast3M.
- La licence « industrielle » est, quant à elle, payante et ne se décline qu’en version « utilisateur ».
NOTE DE FABRICATION DE CAST3M 2024
2. PLATEFORMES DE PRODUCTION DE CAST3M
Les plates-formes sur lesquelles est fabriquée la version annuelle de Cast3M sont les suivantes :
2.1 PC – GNU/LINUX (64 BITS)
Plateforme de compilation :
Modèle de système : CentOS Linux release 6.10 (Final) 2.6.32-754.35.1.el6.centos.plus.x86_64
Type de processeur : Intel(R) Xeon(R) Silver 4214 CPU @ 2.20GHz
Mémoire Vive : 16 Go
Plateforme de test :
Modèle de système : Debian Linux Squeeze 6.0.10 for x86_64
Type de processeur : Intel(R) Xeon(R) Silver 4214 CPU @ 2.20GHz
Mémoire Vive : 4 Go
2.2 PC – WINDOWS (64 BITS)
Plateforme de compilation et de test :
Modèle de système : Windows 10.0.19041.2673
Type de processeur : Intel(R) Core(TM) i7-8850H CPU @ 2.60GHz 2.59 GHz
Mémoire Vive : 32 Go
2.3 PC – MACOS (64 BITS)
Plateforme de compilation :
Modèle de système : Mac mini Apple M2 Pro macOS Sonoma 14.5
Type de processeur : arm 64
Mémoire Vive : 16 Go
NOTE DE FABRICATION DE CAST3M 2024
3. ÉLABORATION DE LA VERSION 2024 DE CAST3M
3.1 OBJET
L’objectif est de produire une version annuelle de Cast3M en vue d’une large diffusion par téléchargement,
notamment sur le site internet (https://www-cast3m.cea.fr), ainsi que ses programmes d’installation
automatisés pour différentes plates-formes informatiques :
 Windows (64 bits)
 GNU/Linux (64 bits)
 MacOS (64 bits)
3.2 ÉTAPES DE L’ELABORATION DE LA VERSION
Pour produire la version de l’année « N » de Cast3M, les actions suivantes sont réalisées par ordre
chronologique.
3.2.1 Phase 1 : le 31/12 de l’année « N-1 »
Cette phase consiste à figer l’état des développements de Cast3M sur le réseau scientifique du DM2S dans
le répertoire de fichier Titania à la date du 31/12 de l’année N-1. Pour cela, une branche est créée sur le
dépôt « castem » du réseau Tuleap du CEA (https://codev-tuleap.intra.cea.fr). Elle prend le nom de la forme
BR_Cast3M_<année_de_la_version> et comprend des sources C, des sources Esope, des procédures, des
notices, des cas-tests et un fichier d’erreurs GIBI.ERREUR.
L’ensemble des manipulations décrites pour la préparation de la version de l’année N de Cast3M se fait à
l’aide du script create_castem.sh. Il organise l’installation de Cast3M au sein d’un répertoire portant comme
nom castem_workdir. Le script create_castem.sh est issu du dépôt Git castem_products, possédant une
branche avec le même nom que celle du dépôt castem (BR_Cast3M_<année_de_la_version>) qui constitue
un projet dédié à la construction de Cast3M. La Figure 1 décrit l’arborescence du répertoire
castem_workdir.
Figure 1. Arborescence des répertoires pour la préparation de Cast3M 2024
NOTE DE FABRICATION DE CAST3M 2024
Le répertoire est créé avec les sous-répertoires ARCHIVES, SOURCES, BUILD et INSTALL.
· Le répertoire ARCHIVES permet de stocker les sources de CASTEM et de ses dépendances
téléchargées à partir du git tuleap ou de leur site respectif. Il est possible de récupérer séparément
les sources et de les y placer dans ARCHIVES afin de pouvoir les utiliser par la suite sans avoir
besoin d’être connecté à Internet ou à l’intranet du CEA.
· Dans le répertoire SOURCES, les sources de castem et de ces dépendances y sont copiées depuis
ARCHIVES. Si des patchs sont nécessaires, ils seront appliqués, puis l’installation se fera à partir des
répertoires contenus dans SOURCES.
· Le répertoire BUILD est le répertoire de travail depuis lequel la fabrication de castem est pilotée. Le
script create_castem.sh y lance la commande « cmake » avec les arguments précisés à l’execution
du script.
· Le répertoire INSTALL est destiné à recevoir les installations de castem et de ses dépendances.
Figure 2. Branche BR_Cast3M_2024 du dépôt Git castem (Tuleap)
 Le répertoire castem de la branche BR_Cast3M_2024 contient la saisie de la version de
développement de Cast3M vierge de toutes corrections au 31/12 telle que présente sous l’atelier
de développement présent sur le serveur de fichiers Titania. Cette branche ne contient aucun
développement poussé au-delà de cette date. Le contenu de ce répertoire est constitué de fichiers
et de dossiers à récupérer dans le répertoire /home/castem-public/castem/ du serveur
Titania. La liste des répertoires à récupérer est donnée sur la Figure 3.
Figure 3. Liste des répertoires à récupérer dans castem/ du serveur Titania
- dgibi : cas tests de la version de développement de Cast3M
- divers : fichiers de données externes nécessaires pour l’exécution de la base des cas tests
- header : fichiers d’entête (pour la sortie de fichiers .mif au format Adobe FrameMaker)
- include : comprend l’ensemble des Includes Esope nécessaires
NOTE DE FABRICATION DE CAST3M 2024
- notice : comprend l’ensemble des notices disponibles dans Cast3M
- procedur : comprend l’ensemble des procédures disponibles dans Cast3M
- data : répertoire supplémentaire créé pour y placer le fichier d’erreur de Cast3M à
récupérer sur Titania à l’adresse suivante :
/home/castem-public/castem/GIBI.ERREUR
- sources : répertoire supplémentaire créé pour y placer l’ensemble des sources .c, .eso,
.h. Ces fichiers sont extraits à l’aide de la commande
arc –eon /home/castem-public/castem/ castem.arc ‘*.*’
 Le répertoire castem_workdir/SOURCES/castem (voir Figure 1 et 4) contient l’ensemble des
répertoires communs à toutes les plates-formes et mis à jour de toutes les corrections d’anomalies.
Figure 4. Arborescence des répertoires du dépôt castem
 La construction de Cast3M s’effectue dans un répertoire BUILD, créé à la racine du projet
castem_products (Figure 1).
- La construction de Cast3M se fait via des commandes CMake (voir 3.2.3)
- Sous Windows, l’équivalent de ces commandes est envoyé sous forme de commandes MinGW.
- Les répertoires licence_EDURE et licence_INDUS contiennent les sources spécifiques
permettant de différencier la version sous licence « éducation & recherche » de la version sous
licence « industrielle » de Cast3M. La source perm.c diffère entre les deux répertoires.
- Le répertoire bin contient tous les scripts et exécutables. La liste des fichiers présents dans le
répertoire bin avant la construction de Cast3M est la suivante :
NOTE DE FABRICATION DE CAST3M 2024
Figure 5. Arborescence du répertoire « bin » du dépôt castem
Ces fichiers et exécutables permettent la construction de Cast3M pour l’ensemble des plateformes
(Windows, Linux et MacOS).
Chaque script est renommé avec l’année en cours dans son nom pour assurer la cohabitation de
différentes versions annuelles.
3.2.2 Phase 2 : du 01/01 au 31/03 de l’année « N »
Durant cette phase, les corrections d’anomalies qui ont lieu dans la version du jour de Cast3M sont
intégrées à la branche BR_Cast3M_2024.
L’ensemble des évolutions de Cast3M est répertorié dans le fichier /home/castem-
public/castem/hist.hist sur le réseau Titania et est consultable en ligne sur le site Cast3M
(http://www-cast3m.cea.fr/index.php?page=anomalies).
Les fichiers impactés par une évolution sont récupérés le lendemain dans la branche master (version du
jour) en créant un commit par évolution.
Les évolutions à inclure dans la version 2024 de Cast3M sont décidées lors des réunions Cast3M
développeurs mensuelles. Les commits des évolutions à inclure sont versés dans la branche
BR_Cast3M_2024. Les nouveaux développements sont omis et seront intégrés à la version de Cast3M de
l’année suivante.
3.2.3 Phase 3 : du 01/04 au 31/05 de l’année « N »
Cette phase consiste à porter Cast3M sur l’ensemble des plates-formes supportées (Windows 64-bits,
GNU/Linux 64-bits et MacOS 64-bits).
Afin de réaliser cette tâche, la première étape consiste à installer le compilateur gcc.
L’installation du compilateur gcc à la version 13.2.0 se fait de différentes manières suivant la plateforme.
NOTE DE FABRICATION DE CAST3M 2024
· Sous Linux, nous utilisons une machine virtuelle CentOS6 pour la fabrication de la version annuelle.
Le compilateur gcc 13.2.0 a été construit à l’aide du compilateur gcc à la version 12.2.0 contenu
dans le répertoire GCC de la version 2023 de Cast3M. gcc 13.2.0 a besoin, pour fonctionner avec
Cast3M, des dépendances :
 gmp : la version utilisée pour Cast3M 2024 est la version 6.2.1 disponible sur
https://gcc.gnu.org/pub/gcc/infrastructure/gmp-6.2.1.tar.bz2.
 mpfr : la version utilisée pour Cast3M 2024 est la version 4.1.0 disponible sur
https://gcc.gnu.org/pub/gcc/infrastructure/mpfr-4.1.0.tar.bz2.
 mpc : la version utilisée pour Cast3M 2024 est la version 1.2.1 disponible sur
https://gcc.gnu.org/pub/gcc/infrastructure/mpc-1.2.1.tar.gz.
 isl : la version utilisée pour Cast3M 2024 est la version 0.24 disponible sur
https://gcc.gnu.org/pub/gcc/infrastructure/isl-0.24.tar.bz2.
 zlib : la version utilisée pour Cast3M 2024 est la version 1.3.1 disponible sur
https://zlib.net/zlib-1.3.1.tar.gz.
 zstd : la version utilisée pour Cast3M 2024 est la version 1.4.5 disponible sur
https://www.github.com/facebook/zstd/archive/v1.4.5.tar.gz.
 libiconv: la version utilisée pour Cast3M 2024 est la version 1.17 disponible sur
https://gcc.gnu.org/pub/gcc/infrastructure/libiconv-1.17.tar.gz.
Un linker « ld » est aussi compilé à partir des sources de binutils à la version 2.41 disponible sur
https://ftp.gnu.org/pub/gnu/binutils/binutils-2.41.tar.gz. Les dépendances ainsi que les
bibliothèques sont installées dans un même répertoire « GCC » qui sera utilisé pour construire
Cast3M.
gcc 13.2.0 a été compilé avec les options de compilation « --disable-bootstrap --with-cloog -
-with-ppl --enable-cloog-backend=isl --enable-languages=c,c++,fortran,lto --enable-
lto --enable-gold --disable-libquadmath --disable-libquadmath-support --with-
isl=$GCC_DIR --with-mpfr=$GCC_DIR --with-gmp=$GCC_DIR --with-mpc=$GCC_DIR ».
Sous Linux, on installe dans un autre répertoire mpi à la version 4.1.6 disponible sur
https://download.open-mpi.org/release/open-mpi/v4.1/openmpi-4.1.6.tar.gz et hwloc à la
version 2.9.3 disponible sur https://download.open-mpi.org/release/hwloc/v2.9/hwloc-
2.9.3.tar.gz.
 Sous Windows, la fabrication de version se fait en utilisant mingw64 téléchargé à partir de
https://www.msys2.org/. Le compilateur gcc n’est pas construit à partir des sources. Nous
récupérons une version standalone gcc-13.2.0-x86_64-posix-seh-llvm-18.1.1-mingw-w64msvcrt-
11.0.1-r6 délivrée par le site https://winlibs.com/.
 Sous MacOS, nous utilisons xPack pour installer gcc avec les instructions données sur ce site
https://xpack.github.io/dev-tools/arm-none-eabi-gcc/install/. L’installation se fait avec le linker
et le « ar » local de la machine MacOS.
Le contenu du répertoire d’installation (de gcc et de ses dépendances) sera copié dans le répertoire GCC de
castem 2024. Ce répertoire sert à construire la version annuelle et sera fourni avec.
3.2.3.1 Construction de Cast3M 2024
Avant de lancer le script create_castem.sh qui compile les bibliothèques externes ainsi que Cast3M lui-
même, il faut s’assurer que l’on utilise le compilateur voulu :
export GCC_DIR="chemin_du/repertoire_du/compilateur_telecharge"
export CC=$GCC_DIR/bin/gcc
export FC=$GCC_DIR/bin/gfortran
export CXX=$GCC_DIR/bin/g++
export LD_LIBRARY_PATH="$GCC_DIR/lib"
export PATH="$GCC_DIR/bin:$PATH"
NOTE DE FABRICATION DE CAST3M 2024
La variable d’environnement GCC_DIR est associé au chemin du répertoire GCC.
La construction de Cast3M commence par la génération des Makefiles pour la construction de Cast3M 2024.
Pour cela, le script create_castem.sh génère tout d’abord le script castem_cmake.sh exécutant la commande
CMake. Les options nécessaires à CMake doivent être fournies au préalable au lancement de
create_castem.sh :
# Sous Linux
./create_castem.sh --login [login_tuleap] --tag BR_Cast3M_2024 --advanced "\
-DMPI_ROOT=/chemin/du/repertoire/mpi \
-DGCC_ROOT=$GCC_DIR "
# Sous Windows
./create_castem.sh --login [login_tuleap] --tag BR_Cast3M_2024 --advanced "\
-G \"MinGW Makefiles\" \
-DMPI=NO \
-DGCC_ROOT=$GCC_DIR "
# Sous MacOS
./create_castem.sh --login [login_tuleap] --tag BR_Cast3M_2024 --advanced "\
-DMPI=NO \
-DGCC_ROOT=$GCC_DIR "
- L’option login permet d’entrer son login pour récupérer les dépôts de castem, castem_product et
d’autres librairies externes stockées sur tuleap.
- Le tag indique quel branche récupérer sur tuleap.
- Les variables MPI_ROOT et GCC_ROOT indiquent les répertoires mpi et gcc utilisés à la compilation
de Cast3M et qui seront copiés dans CASTEM2024. Sous Windows et MacOS, mpi n’est pas utilisé.
- L’option « -G "MinGW Makefiles" est nécessaire sur Windows afin de générer un Makefile
compatible avec mingw64.
Après l’exécution de la commande CMake, la construction est lancée via la commande « make » sur Linux
et MacOS et « mingw32-make » sur Windows. Une fois cela fait, il ne reste plus qu’à faire une version
distribuable respectivement avec les commandes « make dist » sur Linux et MacOS et « mingw32-make
dist » sur Windows.
3.2.3.2 Bibliothèques externes
On utilise toujours la version statique des bibliothèques (fichier « .a ») lorsque cela est possible, placée
dans le répertoire lib.
La liste exhaustive des bibliothèques est :
 XDR – (eXternal Data Representation)
Pour Linux, différentes implémentations existent. On utilise l’implémentation fournie par la
bibliothèque libtirpc.
Pour Windows, on utilise l’implémentation fournie par la bibliothèque « xdr_windows » (dépôt
dans Tuleap). Il s’agit d’un fork de https://sourceforge.net/projects/oncrpc-windows/, adapté aux
besoins de Cast3M. L’installation de cette bibliothèque fournit les fichiers :
o ${CMAKE_INSTALL_PREFIX}/lib/libxdr.a : bibliothèque XDR qui doit être utilisée lors de
l’édition des liens de Cast3M ;
o ${CMAKE_INSTALL_PREFIX}/include/* : fichiers de développement pour la bibliothèque
XDR ainsi que des fichiers de la libC qui sont nécessaires.
NOTE DE FABRICATION DE CAST3M 2024
 FXDR – Binding Fortran pour XDR. Il s’agit d’un fork de
https://meteora.ucsd.edu/~pierce/fxdr_home_page.html , adapté aux besoins de Cast3M.
L’installation de cette bibliothèque fournit les fichiers :
o ${CMAKE_INSTALL_PREFIX}/lib/libfxdr.a : bibliothèque FXDR qui doit être utilisée lors de
l’édition des liens de Cast3M ;
o ${CMAKE_INSTALL_PREFIX}/include/fxdr.inc : non utilisé
o ${CMAKE_INSTALL_PREFIX}/local/fxdr.3f : non utilisé
 Les bibliothèques pour l’interface graphique (opérateurs TRAC et DESS) de Cast3M.
Cast3M dispose de deux interfaces graphiques, dont l’implémentation dépend de la plateforme :
o L’interface “X” (activable en faisant « OPTI TRAC X ; », activée par défaut) :
 Linux : utilisation directe de la bibliothèque X11 ;
 Windows : utilisation de l’API Win32 ;
o L’interface “OPEN” (activable en faisant « OPTI TRAC OPEN ; ») :
 Linux et Windows : Utilisation des bibliothèques OpenGL et FreeGLUT (la version
utilisée est la 3.2.1 disponible sur https://sourceforge.net/projects/freeglut/ )
 Les bibliothèques pour le parallélisme :
o Linux : OpenMPI utilisé par l’opérateur COLL (la version utilisée est la 4.1.0 disponible
sur https://www.open-mpi.org)
o Linux et Windows : libpthread (les fonctions pour le multi-threading sont définies dans
threadid.c).
 La bibliothèque CMake fournie par «castem_products » (uniquement pour la construction).
 JPEG – La version utilisée pour Cast3M 2024 est la version 2.0.4 disponible sur
https://github.com/libjpeg-turbo/libjpeg-turbo/ .
 HDF5 - La version utilisée pour Cast3M 2024 est la version 1.10.3 disponible sur
https://support.hdfgroup.org
 MED - La version utilisée pour Cast3M 2024 est la version 4.1.1 .
 MFRONT - La version utilisée pour Cast3M 2024 est la version 4.2.1 disponible sur
https://github.com/thelfer/tfel/.
 esope : - Bibliothèque et exécutable Esope pour Cast3M. L’installation d’esope fournit les fichiers :
o ${CMAKE_INSTALL_PREFIX}/bin/esope : traducteur Esope vers Fortran ;
o ${CMAKE_INSTALL_PREFIX}/lib/libesope.a : définition des symboles utilisés lors de la
traduction + gestion mémoire Esope (GEMAT) ;
o ${CMAKE_INSTALL_PREFIX}/include/esope.h : nécessaire pour compiler la source
threadid.c de Cast3M. C’est dans threadid.c que sont définies les fonctions pour l’utilisation
des threads dans Cast3M.
 esope_bootstrap - les bibliothèques et l’exécutable Esope sont déjà construits, pour Linux,
Windows et MacOS. Ce dépôt permet d’obtenir une version prête à l’emploi d’Esope, nécessaire
pour pouvoir construire une autre version d’Esope. L’installation d’esope_bootstrap avec CMake
fournit les mêmes fichiers que l’installation d’esope.
 hho - Bibliothèque pour l’implémentation de la méthode HHO (Hybrid High-Order) dans Cast3M.
L’installation de la bibliothèque hho fournit les fichiers :
o ${CMAKE_INSTALL_PREFIX}/lib/* : bibliothèques hho qui doivent être utilisées lors de
l’édition des liens de Cast3M ;
o ${CMAKE_INSTALL_PREFIX}/include/*.mod : modules Fortran. Le module castem_hho est
utilisé dans la source hhoc3m.F90 de Cast3M.
 Eigen – Bibliothèque necessaire pour HHO. La version utilisée pour Cast3M 2024 est la version
3.4.0 disponible sur https://gitlab.com/libeigen/eigen.
3.2.3.3 Traducteur Esope vers FORTRAN77
Les sources du traducteur Esope doivent être compilées avec la version de GCC utilisée pour Cast3M. Pour
cela, il est nécessaire de disposer d’un traducteur Esope fonctionnel (repris de l’année précédente).
NOTE DE FABRICATION DE CAST3M 2024
 Compilation des sources avec la commande compilcast24 –ESOPE *.eso *.c
 Edition des liens avec la commande essaicast24 –ESOPE
Afin de vérifier que l’exécutable généré est fonctionnel, on effectue l’opération une deuxième fois, mais avec
le traducteur fraîchement créé (« bootstrap »). La comparaison de l’exécutable généré et de l’exécutable
utilisé pour le générer (ils doivent être identiques) permet de s’assurer que la traduction puis la
compilation donne le même résultat.
3.2.3.4 Compilation de Cast3M
Le Makefile compile les sources (eso et C) de façon similaire à compilcast24 (GNU/Linux, Windows et
MacOS).
 En cas d’erreur de traduction un fichier .lst portant le préfixe de la source est généré. Une analyse
préliminaire de l’erreur permettra d’amorcer la discussion avec les développeurs de Cast3M afin
que la correction appropriée soit apportée.
 En cas d’erreur de compilation, un fichier .txt portant le préfixe de la source est généré. Une
analyse préliminaire de l’erreur permettra d’amorcer la discussion avec les développeurs de
Cast3M afin que la correction appropriée soit apportée.
 Toute erreur doit être signalée par l’émission d’une fiche d’anomalie dans l’atelier logiciel de
Cast3M. Celle-ci comprendra le nom de la source, la ou les plates-formes ainsi que l’architecture en
question.
 Les fichiers .o sont archivés dans la bibliothèque libcastem_EDUR.a qui sera copiée dans le
répertoire CASTEM2024/lib. L’édition des liens à l’aide du script essaicast24, selon
l’architecture en cours de la compilation.
 Durant l’édition des liens, il se peut que certaines erreurs surviennent. Le cas échéant, un fichier
link_cast_24.txt est généré et contient les messages d’erreurs. Les plus classiques sont listées
ci-dessous :
- undefined reference to `flush_`
 Mauvais depmac.eso
- undefined reference to `std::ios_base::Init::~Init()'
 Ajouter la bibliothèque standard c++ dans les directives : -lstdc++
- undefined reference to `crt1.o'
 Ajouter le chemin « système » où se trouve l’objet crt1.o dans la variable
d’environnement LIBRARY_PATH
Une fois le portage effectué, Cast3M est vérifié et validé. Ceci consiste à exécuter l’ensemble des cas-tests
du répertoire dgibi et ce pour toutes les plates-formes et toutes les architectures supportées. Le script
castem24 -test permet d’effectuer cette manipulation.
 En cas d’erreur d’exécution d’un cas test, un fichier .err portant le préfixe du cas test est généré.
Une analyse préliminaire de l’erreur permettra d’amorcer la discussion avec les développeurs de
Cast3M afin que la correction appropriée soit apportée.
 Toute erreur doit être signalée par l’émission d’une fiche d’anomalie dans l’atelier logiciel de
Cast3M : dial20 (sur Titania). Celle-ci comprendra le nom du cas-test, la plate-forme ainsi que
l’architecture en question.
NOTE DE FABRICATION DE CAST3M 2024
3.3 SCHEMA DE PRINCIPE DE LA PREPARATION DES VERSIONS ANNUELLES DE CAST3M
La Figure 6 schématise les points précédents et met en évidence la manière dont est gérée l’élaboration
d’une version annuelle de Cast3M.
Figure 6. Organigramme de la préparation des versions annuelles de Cast3M.
NOTE DE FABRICATION DE CAST3M 2024
Annexe A : Documentation Cast3M
1. Liens sur le site Cast3M
- http://www-cast3m.cea.fr/index.php?xml=maj2011
- http://www-cast3m.cea.fr/index.php?xml=complements
- http://www-cast3m.cea.fr/index.php?xml=supportcours
2. Dépôts Tuleap
https://codev-tuleap.intra.cea.fr/plugins/git/castem/
Liste des dépôts utiles pour la construction et la distribution de Cast3M 2024 :
 castem
 esope
 esope_bootstrap
 castem_products
 fxdr
 hho
 xdr_windows
 packager
3. Documentation principale
Utiliser Cast3M
- Présentation et utilisation de castem2000 (Auteur E. Le Fichoux)
- Maillage (Auteur F. Di Paola)
- La procédure PASAPAS (Auteur T. Charras, F. Di Paola)
- Liste des modèles en mécanique non linéaire (Auteur F. Di Paola)
- Gibiane - Castem 2000 (Auteur T. Charras)
- Classification thématique des objets, opérateurs et procédures de Cast3M
- Post-traitement (Auteur F. Di Paola)
Exemples Cast3M :
- Annotated Testing Files (Auteur E. Le Fichoux)
- Exemples d’utilisation de la procédure PASAPAS (Auteur F. Di Paola)
Développer dans Cast3M :
- Développer dans Cast3M (Auteur T. Charras, J. Kichenin)
Assurance Qualité Cast3M
- Classification des cas tests de Cast3M 2024
- Note de fabrication de Cast3M 2024
- Note de version de Cast3M 2024
- Guide de validation de Cast3M
NOTE DE FABRICATION DE CAST3M 2024
4. Compléments :
- Le procedure di castem 2000 per l'analisi meccanica di strutture in materiale composito
laminato (Auteur A. Miliozzi)
- Modélisation des structures de génie civil sous chargement sismique à l'aide de Castem
2000 (Auteur D. Combescure)
- Présentation des joints dilatants (Auteur P. Pegon)
- Dynamique du solide : modification du schéma de Newmark aux cas non linéaires
(Auteur P. Verpeaux, T. Charras)
- Optimisation dans Cast3M (Auteur T. Charras, J. Kichenin)
- Un manuel d’utilisation de Cast3M (Auteur P. Pasquet)
- Initiation à la simulation numérique en mécanique des fluides à l’aide de Castem2000,
Recueil d’exemples commentés (Auteur F. Dabbene, H. Paillère)
- Initiation à la simulation numérique en mécanique des fluides : Eléments d’analyse
numérique (Auteur F. Dabbene, H. Paillère)
- Tutorial Cast3M pour la mécanique des fluides (Auteur F. Dabbene)
5. Supports de cours :
- Méthodes numériques avancées en Mécanique non linéaire (Auteur P. Verpeaux)
- Algorithmes et méthodes (Auteur P. Verpeaux)
- Frottement (Auteur P. Verpeaux)
- Non linéarités liées à la thermique (Auteur P. Verpeaux)
- Non convergence (Auteur P. Verpeaux)
- Eléments de dynamique des structures. Illustrations à l’aide de Cast3M (Auteur
D. Combescure)
- Introduction à la méthode des éléments finis en mécanique des fluides incompressibles
(Auteur S. Gounand).
NOTE DE FABRICATION DE CAST3M 2024
Annexe B. Traçabilité

