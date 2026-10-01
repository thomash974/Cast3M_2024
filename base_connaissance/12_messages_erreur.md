# Messages d'erreur de Cast3M 2024 (fichier GIBI.ERREUR, partie française)

Correspondance entre le numéro passé à `CALL ERREUR(n)` dans les sources et le message affiché. Niveau entre crochets (0 = information/avertissement… 2 = erreur). Les champs `%i1`, `%r1`, `%m1:8` sont remplis depuis `INTERR`, `REAERR`, `MOTERR` du COMMON `CCOPTIO` avant l'appel.

-386 [0] Composante %M17:24 sous-modele %i1 constituant %M1:16
-385 [0] %M1:128
-384 [?] Liste des objets associes :
-383 [0] LISTOBJE de pointeur %i1 contenant %i2 objet(s)
-382 [0] LISTOBJE de pointeur %i1 contenant %i2 objet(s) de type %M1:8 de numero(s) :
-381 [0] LISTOBJE de pointeur %i1 contenant %i2 objet(s) de type %M1:8 de pointeur(s) :
-380 [0] Fichier notice incorrect : %M1:128
-379 [0] Notice surchargee: %M1:24
-378 [0] Temps horloge %i1 ms / Temps CPU %i2 ms (depuis le dernier APPEL)
-377 [0] **********     Attention: Utilisation de procedures personnelles **********
-376 [0] **********     Attention: Utilisation d'un executable modifiee   **********
-375 [0] **********     Arret du programme Cast3M. Niveau d'erreur: %i1     **********
-374 [0] Chargement constant
-373 [0] Le nom de la composante de longueur %i1 sera tronquee a %i2 caracteres (LOCOMP) : '%M1:8'
-372 [0] MPOVAL: %i1  -  Nombre de noeuds: %i2  -  Nombre de composantes: %i3
-371 [0] La longueur du 'MOT' %M1:10 est trop grande : / Elle est tronquee a %i1 caracteres.
-370 [?] Traitement inacheve zone %i1, %m1:8
-369 [0] %i1) type=ETIQ et pointeur=%i2 : "%M7:256" [MELEME %i3 ; Couleur=%M1:4 ; Position=%M5:6 ; Deport=%r1 ; Lien=%b1]
-368 [0] %i1) type=CATE et pointeur=%i2 : "%M5:256" [Couleur=%M1:4]
-367 [0] ANNOTATION de pointeur %i1 composee de %i2 annotation(s) elementaire(s) :
-366 [0] Ceci est un message de %M1:12 listant %i1 objets : / %i2, %i3, %i4, %i5 puis %r1, %r2 et %b1, %b2 mais aussi "%m13:16|%m17:20"
-365 [0] Rien n'a ete sorti, verifiez votre ligne de commande 'SORT' 'MED'
-364 [0] Attention, la matrice est vide apres elimination des conditions de Dirichlet
-363 [0] +--------------------------+------------------+------------------+------------------+------------------+
-362 [0] | %M1:10               |Duree Horloge(ms) |  Duree CPU (ms)  |  Efficacte (%)   | Nombre d'appels  |
-361 [0] inconnu %m1:4 en double au noeud %i1 dans une relation
-360 [0] %m1:24 => %m25:32
-359 [0] LE FORMAT DE SAUVEGARDE DE NIVEAU %i1 NE CONSERVE QUE LES 8 PREMIERS / CARACTERES DES NOMS DES VARIABLES : ATTENTION AUX CONFLITS POTENTIELS
-358 [0] La ligne est trop longue. Elle a ete tronque a : %m1:40
-357 [0] *** Notice %m1:4, page %i1
-356 [0] q : quitter, d : debut, s : sommaire, NUM1 : aller a la section NUM1, Entree : page suivante
-355 [0] SOMMAIRE DE LA NOTICE / ---------------------
-354 [0] %i1 %m1:4 elimines
-353 [0] Composante %m1:8 tronquee a %i1 caracteres
-352 [0] Importation terminee - Nombre de procedures creees : %i1
-351 [0] La procedure %M1:8 a ete ignoree
-350 [0] La procedure %M1:8 a ete importee avec succes
-349 [0] Pas de delimiteur $$$$ trouve : le fichier est constitue d'instructions / elementaires non encapsulees dans des procedures
-348 [0] Le fichier de procedures est au format standard
-347 [0] Le nom de la composante tracee est : %m1:8
-346 [0] Le pas de la progression a ete recalcule !!!!
-345 [0] Fin d'ecriture du label : %M1:512
-344 [0] Le fichier de restitution est de type XDR
-343 [0] Le fichier de restitution est de type non formatte
-342 [0] Le fichier de restitution est de type formatte
-341 [0] Navier-Stokes
-340 [0] Donnez l epaisseur du trait pour la sortie graphique
-339 [0] Point dont le numero est actuellement %i1 / Coordonnee : %r1 Densite : %r2
-338 [0] AVERTISSEMENT : Un element de degre 2 relie les "NODE" %i1, %i2 / ,%i3 alors qu'ils sont aussi relies par des elements de degre 1
-337 [0] AVERTISSEMENT :Le point "NODE" %i1 est relie au "NODE" %i2 par un ele / ment de degre 1 ET par un element de degre 2
-336 [0] AVERTISSEMENT : des fers se croisent au point n %i1
-335 [0] AVERTISSEMENT : %m1:8 est un noeud du contour du maillage qui est con- / -necte a %i1 noeuds : verifier votre maillage.
-334 [0] AVERTISSEMENT : Dans l'enveloppe l'element n %i1 de type %m1:4 est / supperpose a l'element n %i2 de type %m5:8
-333 [0] AVERTISSEMENT : Le contour est constitue d'elements lineaires et qua- / -dratiques : il peut y avoir des erreurs dans votre maillage
-332 [0] Procedure courante de Cast3M.
-331 [0] Cette procedure est definie par l'utilisateur dans le UTILPROC
-330 [0] Cette procedure est definie dans le fichier de donnees, impossible / de la lister.
-329 [0] %m1:6  %m7:15 %i1
-328 [0] Presence d'un constituant non specifie ou nombre
-327 [0] Valeur propre (omega**2) de rang %i1 : / convergence relative : %r1 borne sup de l erreur relative : %r2
-326 [0] SPON : pas de convergence pour la frequence %r1 ductilite calculee %r2
-325 [0] Trajectoire decrite par le CHPOINT
-324 [0] Description vitesse
-323 [0] Deplacement de type %m1:11 defini par :
-322 [0] Attention il y a %i1 noeud(s) hors support du champ initial
-321 [0] Objet de type OBJET de pointeur %i1
-320 [0] Les coefficients des matrices de blocages ont des ordres de grandeur / tres differents. La matrice cree est mal conditionnee.
-319 [0] Nombre de points accroches %i1  sur  %i2 proposes
-318 [0] Particule %i1 .On sort du domaine pour l'element %i2 . / Probablement CFL trop grand.
-317 [0] Particule %i1 .On s'est perdu dans l'element %i2 . / On arrete la cette trajectoire.
-316 [0] Particule %i1 .Probleme sur l'arete %i3 de l'element %i2 . / On arrete la cette trajectoire.
-315 [0] Particule %i1 .Probleme sur la face %i3 de l'element %i2 . / On arrete la cette trajectoire.
-314 [0] Nombre d'iterations superieur a %m1:8
-313 [0] Pas d'objet inclus pour ce maillage.
-312 [0] Attention, pour l'amortissement %r1, le maximum est atteint apres la fin / du signal %i1 fois sur l'ensemble des frequences.
-311 [0] Attention pour l'amortissment %r1 et la frequence %r2, le maximum est atteint / a la fin de la periode de calcul.
-310 [0] Abandon du MENAGE automatique : / la memoire est toujours utilisee a plus de 90%.
-309 [0] Plus de 90% de la memoire totale est utilisee : lancement de MENAGE.
-308 [0] Operateur -  nombre  - nbre de segments restes   -  taille correspondante / d'appels   actifs apres chaque appel   des segments actifs (K MOTS)
-307 [0] Matrice elementaire non-symetrique
-306 [0] *****     FIN DE LA PROCEDURE INITIALE    ******
-305 [0] *****  EXECUTION D'UNE PROCEDURE INITIALE ******
-304 [0] ATTENTION : On ne prend pas en compte la moyenne pour un bruit blanc / a distribution exponentielle (valeur lue : %r1 )
-303 [0] Impossible de regenerer l'element %i1 ayant deux fois le meme noeud.
-302 [0] Procedure surchargee: %M1:24
-301 [3] message inacceptable
-300 [0] Probleme de convergence dans %m1:8 au point situe en %r1 %r2 %r3 .
-299 [0] La particule %i1 de coordonnees %r1 %r2 %r3 / n'est pas dans le domaine. Elle est donc supprimee.
-298 [0] Particule %i1 .Probleme dans un coin de l'element %i2
-297 [0] Geometrie incompatible avec le CHPOINT
-296 [0] La sortie de ce dernier est annulee
-295 [0] Deuxieme table :
-294 [0] Chargement elementaire %i1 : nom %m1:4 , nature %m5:8, deplacement %m9:12 / Premiere table :
-293 [0] Nombre de noeuds elimines %i1
-292 [0] Attention le nuage de points est mal adapte a la methode de resolution. / La matrice du systeme est singuliere. Les resultats sont incoherents.
-291 [0] L'operateur %m1:4 n'est plus disponible.
-290 [0] Donnez la suite du %m1:8 sinon return
-289 [0] L'attribut de nature du CHPOINT est:  %m1:11
-288 [0] Composante %i1 de nom %m1:8 et de type %m9:16 / Liste  des valeurs associees
-287 [0] Objet de type NUAGE et de pointeurs associe : %i1 / Il contient %i3 n-uplets a %i2 composantes
-286 [0] Liste des notices contenant la chaine : %m1:8 / ************************************************
-285 [0] Attention: il n'y a pas de contrainte d'egalite
-284 [0] Attention: il n'y a pas de contrainte d'inegalite
-283 [0] Element %i1 Point de Gauss %i2 - depassement de capacite en  %m5:16
-282 [0] EXCELL : Convergence en %i1 iterations
-281 [0] le nombre de sinus  propose est a plus de 10 pour cent (%r1) / du nombre optimal
-280 [0] le nombre de points propose est a plus de 10 pour cent (%r1) / du nombre optimal
-279 [0] Rupture de l'element %i1 au point de Gauss %i2 apres un / intervalle de temps %r1 depuis le dernier instant calcule
-278 [0] Taille de la matrice: %i1 Facteur: %r1 Conditionnement: %r3 Performance (Gflop/s): %r2
-277 [0] Fin normale de la restitution
-276 [0] Fin normale de la sauvegarde
-275 [0] Matrice elementaire antisymetrique
-274 [0] Matrice elementaire symetrique
-273 [0] Premiere ligne = donnees : deuxieme ligne = type des donnees.
-272 [0] Choix de l'algorithme ?
-271 [0] Nombre de pas de calcul entre deux sorties ?
-270 [0] Valeur des pas de temps ?
-269 [0] Nombre de pas de temps ?
-268 [0] Table des inconnues et des points attendus ?
-267 [0] Table definissant les resultats attendus ?
-266 [0] Table donnant les conditions initiales ?
-265 [0] Table contenant les chargements ?
-264 [0] Table rassemblant la description des liaisons ?
-263 [0] Table contenant la matrice d'amortissement ?
-262 [0] Table contenant les matrices raideur et masse ?
-261 [0] Table representant une base modale ?
-260 [0] Quelle surface de la coque ?
-259 [0] Temps Horloge %i1 ms (depuis le dernier APPEL)
-258 [0] %m1:18 par OPERATEUR et par ASSISTANT
-257 [0] %m1:15  %i1 %m16:30  %i2
-256 [0] Objet de type ANNULE
-255 [0] Elle est dans la procedure %M1:512 dont l'appel en ligne %i1 est :
-254 [0] Elle est dans la procedure %M1:512 dont l'appel est :
-253 [0] Instruction numero %i1 executee au moment de l'erreur :
-252 [0] Precision ?
-251 [0] Increment de contraintes totales ?
-250 [0] Deformations inelastiques initiales ?
-249 [0] Variables internes initiales ?
-248 [0] Contraintes initiales ?
-247 [0] Nombre de resolutions simultanees ?
-246 [0] Grandes deformations ?
-245 [0] chpoint de deplacement ?
-244 [0] Champ de materiau ou de matrices de hooke ?
-243 [0] Chamelem de materiau (et de caracteristiques) ?
-242 [0] Type de symetrie ?
-241 [0] Premier point du %m1:4 de symetrie ?
-240 [0] Deuxieme point du %m1:4 de symetrie ?
-239 [0] Troisieme point du %m1:4 de symetrie ?
-238 [0] Donnez la nouvelle densite.
-237 [0] On attend un objet de type BLOC ou PROCEDURE.
-236 [0] Nombre de couches ?
-235 [0] Angle ?
-234 [0] Surcharge de la densite ?
-233 [0] Vecteur de la translation ?
-232 [0] Centre de la rotation ?
-231 [0] Point de l'axe ?
-230 [0] Type de surface ?
-229 [0] Contour ?
-228 [0] Premier point definissant la surface ?
-227 [0] Deuxieme point definissant la surface ?
-226 [0] Troisieme point definissant la surface ?
-225 [0] Premier objet a fusionner ?
-224 [0] Premier logique ?
-223 [0] Deuxieme logique ?
-222 [0] Premier %m1:8 ?
-221 [0] Deuxieme %m1:8 ?
-220 [0] Deuxieme maillage a fusionner ?
-219 [0] Choisissez un operateur
-218 [0] Choisissez une option
-217 [0] Donnez l'unite d'impression
-216 [0] Donnez le fichier d'impression
-215 [0] Indiquez la dimension
-214 [0] Donnez le type d'element
-213 [0] Indiquez l'unite de sortie
-212 [0] Donnez le fichier de sortie
-211 [0] Donnez le type des traces
-210 [0] Donnez l'unite de lecture
-209 [0] Donnez le fichier a lire
-208 [0] Indiquez l'echo
-207 [0] Indiquez le niveau d'erreur autorise
-206 [0] Indiquez l'unite des fichiers lire
-205 [0] Donnez le fichier de lecture
-204 [0] Indiquez l'unite des fichiers sgbd
-203 [0] Donnez le fichier de sgbd
-202 [0] Indiquez le niveau d'impression
-201 [0] Indiquez le mode de calcul
-200 [0] Donnez le cadre
-199 [0] Donnez la couleur
-198 [0] Donnez le niveau des sorties
-197 [0] Donnez la region memoire pour l'inversion
-196 [0] Donnez l'unite pour sauver
-195 [0] Donnez le fichier de sauvegarde
-194 [0] Donnez l'unite pour restituer
-193 [0] Donnez le fichier de restitution
-192 [0] Indiquez le type de trace d'isovaleurs
-191 [0] Ombrage ?
-190 [0] Nombre de points actuels ?
-189 [0] 0 pas de verif -1 verif
-188 [0] Nombre de zero consecutifs ?
-187 [0] Unite logique pour acquerir ?
-186 [0] Donnez le fichier d'acquisition
-185 [0] Ligne 0 - ecra 1
-184 [0] Place libre ?
-183 [0] On ne sait pas a quoi associer le nom : %m1:8
-182 [0] Formulation ?
-181 [0] Formulation couplee ?
-180 [0] Propriete du modele de materiau ?
-179 [0] Autre propriete du modele de materiau ?
-178 [0] Type d'element fini ?
-177 [0] Autre type d'element fini ?
-176 [0] Place memoire desiree ?
-175 [0] Autre coefficient ?
-174 [0] Coefficient ?
-173 [0] Donnez une TABLE de sous-type %m1:8
-172 [0] Indiquez le nombre d'elements
-171 [0] Vous pouvez surcharger la densite
-170 [0] Densite initiale ?
-169 [0] Densite finale ?
-168 [0] Premiere extremite de la ligne ?
-167 [0] Donnez le centre
-166 [0] Deuxieme extremite de la ligne ?
-165 [0] Centre de l'homothetie ?
-164 [0] Chpoint de flux ?
-163 [0] Valeur algebrique du flux ?
-162 [0] Direction du flux dans le repere global ?
-161 [0] Matrice de masse ?
-160 [0] Matrice de rigidite ?
-159 [0] Matrice de blocage ?
-158 [0] Forces exterieures au cours du temps ?
-157 [0] Valeurs imposees au cours du temps ?
-156 [0] Valeur du pas de temps ?
-155 [0] Nombre de pas de calcul ?
-154 [0] Un resultat tous les nins instants ?
-153 [0] Temps initial ?
-152 [0] Table des champs initiaux ?
-151 [0] Troisieme coordonnee ?
-150 [0] Deuxieme coordonnee ?
-149 [0] Premiere coordonnee ?
-148 [0] On attend un des objets : LISTCHPO CHPOINT CHAMELEM LISTREEL
-147 [0] Valeur de la temperature ?
-146 [0] Champ de temperature ?
-145 [0] Champ de caracteristiques ?
-144 [0] Chpoint de base ?
-143 [0] Chamelem de base ?
-142 [0] Coordonnee ?
-141 [0] Composante recherchee ?
-140 [0] Sous-type du champ par element resultat ?
-139 [0] Valeur de la source ?
-138 [0] CHPOINT de source ?
-137 [0] Objet de type '%M1:8' ?
-136 [0] TABLE de changement de phase ?
-135 [0] CHAMELEM de sous type caracteristique ?
-134 [0] Un objet de type CHPOINT, ENTIER ou FLOTTANT est attendu.
-133 [0] POINT de l'axe ?
-132 [0] Point invariant ?
-131 [0] Maillage de base ?
-130 [0] Rapport d'affinite ?
-129 [0] La RIGIDITE(CL1) %i1 appartient a la SOUS-STRUCTURE %i2
-128 [0] CL1(ddl bloque)-STRUCTURE de pointeur  %i1 / -128 0' / Il defini l(es) %i2 affectation(s) suivante(s)
-127 [0] Le maillage %i1 appartient a la SOUS_STRUCTURE %i2 / Liste des noeuds du maillage :
-126 [0] ELEMENT-STRUCTURE  de pointeur %i1 / il defini l(es) %i2 affectation(s) suivante(s)
-125 [0] Indice                          Objet / Type    Valeur                  Type   Valeur
-124 [0] TABLE de pointeur %i1
-123 [0] Type de comportement plastique : %m1:4
-122 [0] Type de comportement lineaire  : %m1:8
-121 [0] MODELE de pointeur %i1
-120 [0] Nombre de points : %i1
-119 [0] Variable en ordonnee ( %m1:4 )  %m5:16
-118 [0] Variable en abscisse %m1:12
-117 [0] Sous evolution numero %i1 de couleur %m1:4
-116 [0] EVOLUTION de pointeur %i1 composee de %i2 evolution(s) elementaire(s) / de sous type %m1:8
-115 [0] Listreel de la fonction de pointeur %i1 qui contient les %i2 valeurs  :
-114 [0] Listreel des temps de pointeur %i2 qui contient les %i1 temps suivant :
-113 [0] Description temporelle :
-112 [0] Chargement elementaire %i1 : nom %m1:4 , nature %m5:8, deplacement %m9:12 / ---------------------- / Description spatiale :
-111 [0] CHARGEMENT de pointeur %i1 qui contient %i2 chargement(s) elementaire(s)
-110 [0] LISTCHPO de pointeur %i1 qui contient %i2 chpoint(s)
-109 [0] LISTMOTS de pointeur %i1 qui contient %i2 mot(s) de %i3 caractere(s) / Liste des mots :
-108 [0] VECTDOUB de pointeur %i1 qui contient %i2 composante(s) / composante       valeur
-107 [0] Liste des noeuds de l'element :
-106 [0] Liste des noms de composantes :
-105 [0] Mode de calcul actuel %m1:32
-104 [0] Numero de l'harmonique %i1 : Mode de calcul du champ %m1:32
-103 [0] Sous references numero  %i1 : Nombre de composantes %i2 / Nombre d'elements %i3 : Nombre de points par element %i4
-102 [0] CHAMP PAR ELEMENT de sous type %m1:8 nombre de sous references %i1
-101 [0] La sous-base contient %i1 liaison(s) de type %m1:4
-100 [0] * Attache  *          * %i1
-99 [0] * Solution * %m1:8 *  %i1
-98 [0] Sous-base numero %i1 de pointeur %i2 qui contient : / *  Objet   *   Type   * Pointeur * Point *  Frequence    *  Liaison *
-97 [0] BASE MODALE de pointeur  : %i1
-96 [0] Parametres de Lagrange
-95 [0] Acceleration de translation
-94 [0] Vitesse de translation
-93 [0] Translation d'ensemble
-92 [0] Acceleration de rotation
-91 [0] Vitesse de rotation
-90 [0] Rotation d'ensemble
-89 [0] Champ de mouvement d'ensemble
-88 [0] Champ de forces de liaisons
-87 [0] Champ d'accelerations
-86 [0] Champ de vitesses
-85 [0] Temps  T = %r1
-84 [0] Correspondant a la liaison elementaire (mjonct) %i1
-83 [0] Pseudo mode de rang %i1
-82 [0] Solution statique de rang %i1
-81 [0] champ de Von Mises
-80 [0] Champ de contraintes
-79 [0] Champ de deplacements
-78 [0] Numero %i1 : Harmonique %i2     %m1:8
-77 [0] Frequence  %r1 : Masse generalisee %r2 / QX = %r3 : QY = %r4 : Qz = %r5
-76 [0] Mode de rang %i1
-75 [0] SOLUTION de pointeur msolut %i1 qui contient %i2 pas en temps
-74 [0] SOLUTION de pointeur msolut %i1 qui contient %i2 pseudo(s) mode(s)
-73 [0] SOLUTION de pointeur msolut %i1 qui contient %i2 solution(s) statique(s)
-72 [0] SOLUTION de pointeur msolut %i1 qui contient %i2 mode(s)
-71 [0] Objet SOLUTION vide.
-70 [0] caracteristique de l'asservissement en proportion : %r1 / caracteristique de l'asservissement en vitesse    : %r2
-69 [0] Consigne en proportion  : Objet LISTREEL %i1 / Consigne en vitesse     : Objet LISTREEL %i2
-68 [0] Inertie  : %r1
-67 [0] Rotor    : %r1
-66 [0] Stator   : %r1
-65 [0] Mecanisme = moteur asservi
-64 [0] Liste des inconnues concernees : %m1:4 %m5:8 %m9:12 %m13:16 %m17:20
-63 [0] Sous structure 2 : %i1
-62 [0] Structure 2      : %i1
-61 [0] Sous structure 1 : %i1
-60 [0] Structure 1      : %i1
-59 [0] Axe %r1 %r2 %r3
-58 [0] Liaison = charniere simple
-57 [0] Hauteur des asperites            : %r1
-56 [0] Epaisseur de lame fluide du bas  : %r1 / Coefficient de debit critique    : %r2
-55 [0] Debit critique en m3/s           : %r1 / Epaisseur de lame fluide du haut : %r2
-54 [0] Hauteur du deversoir             : %r1 / Rayon du deversoir               : %r2
-53 [0] Acceleration de la pesanteur     : %r1 / Masse volumique du fluide        : %r2
-52 [0] Deversoirs            :
-51 [0] Liste des couples de points definissant la liaison / deversoir du msouma : %i1
-50 [0] Frottement      : %r1
-49 [0] Amortissement   : %r1
-48 [0] Raideur de choc : %r1
-47 [0] Profil %i1 : objet %i2 : taille %r1 / Vecteur servant a definir le repere local : objet %i2
-46 [0] Mouvement de translation des structures suivant la normale au plan / de choc. Valeur du jeu associe : %r1
-45 [0] Choc dans un plan. configuration %m1:4 rne / normale au plan : objet %i1
-44 [0] Choc suivant une direction fixe : objet %i1 jeu %r1
-43 [0] Points                :
-42 [0] Points de la structure:
-41 [0] Structures            :
-40 [0] Chocs                 :
-39 [0] Liste des couples de points de choc du msouma %i1
-38 [0] Liaison elementaire numero %i1 : de pointeur %i2 : de type %m1:4 / Numero du point associe %i3 type de l'inconnue de liaison %m5:8
-37 [0] Descriptif des liaisons elementaires
-36 [0] Rigidite due a la liaison mixte : %i1
-35 [0] ATTACHE de pointeur mattac : %i1
-34 [0] STRUCTURE de pointeur mstruc : %i1
-33 [0] Matrice elementaire numero   : %i1 ( ligne1,ligne2,ligne3...)
-32 [0] Multiplicateurs de Lagrange  : %i1
-31 [0] Noeuds soumis a la condition :
-30 [0] Maillage %i1 associe a la condition
-29 [0] Liste des points associes aux matrices
-28 [0] Nature des matrices : "%m1:1" / Noeuds      Inconnue  : (les %i2 premieres sont primales)
-27 [0] Sous matrice %i1 : %i2 elements : %i3 x %i4 inconnue(s) par matrice / Coefficient multiplicateur %r1 : Harmonique %i5
-26 [0] Matrice de %m1:8 de pointeur %i1, formee de %i2 matrice(s) elementaire(s)
-25 [0] Points  Inconnue  .....
-24 [0] Points  Inconnue  Harmonique  .....
-23 [0] Option de calcul : %m1:18
-22 [0] Type  : %m1:8
-21 [0] CHPOINT de pointeur %i1 contenant %i2 sous-champ(s) / Titre : %M1:512
-20 [0] 1ere ligne  numero element : 2eme couleur : 3eme... noeud(s)
-19 [0] MAILLAGE %i1 : %i2 element(S) de type %m1:4 / %i3 sous-reference(s)
-18 [0] Liste de(s) sous-reference(s) :
-17 [0] Liste de(s) sous-objet(s) :
-16 [0] MAILLAGE  %i1 :    %i2 Sous-objet(s) :    %i3 Reference(s)
-15 [0] Liste des objets de type : %m1:8
-14 [0] Pas d''objet de type %m1:8 actuellement en memoire
-13 [0] Liste de la PROCEDURE / *********************
-12 [0] VECTEUR compose de %i1 vecteur(s) elementaire(s) / Amplification  Champoint Couleur Composante(s) selectionnee(s)
-11 [0] DEFORMEE composee de %i1 deformee(s) elementaire(s) / Amplification Geometrie Ch depl Vecteur Couleur Chp valeur cham valeur  modele
-10 [0] TEXTE de %i1 caractere(s) dont voici le contenu :
-9 [0] LISTREEL de pointeur %i2 contenant %i1 reel(s) que voici:
-8 [0] Point dont le numero est actuellement %i1 / Coordonnees: %r1 %r2 %r3 Densite: %r4
-7 [0] Point dont le numero est actuellement %i1 / Coordonnees: %r1 %r2 Densite: %r3
-6 [0] LISTENTI de pointeur %i2 contenant %i1 entier(s) que voici:
-5 [0] Logique valant: %m1:4
-4 [0] Reel valant: %r1
-3 [0] Entier valant: %i1
-2 [0] Chaine de %i1 caracteres de contenu : %M1:512
-1 [0] La lecture des donnees continue sur le terminal
0 [0] *****  ERREUR %i0 ***** dans l'operateur %m0:0
1 [2] Il manque un ")" . Le debut de la phrase est : / %M1:512
2 [2] Il manque un "(" . Le debut de la phrase est : / %M1:512
3 [2] Une directive ne peut pas faire plus 500 caracteres. Le debut est : / %M1:512
4 [1] Fin du fichier de donnees
5 [3] Erreur anormale. Contactez votre support
6 [2] On desire lire un mot
7 [2] On ne comprend pas le mot '%M1:512' On attendait:
8 [2] On desire lire un entier
9 [2] Objet inconnu %m1:8
10 [2] Table saturee. Eclatez la directive
11 [2] Il y a un resultat de type %m1:8 et de nom %M9:32 / en trop par rapport aux noms a affecter
12 [3] Tentative de changer de dimension
13 [2] On est deja en train de nommer un objet
14 [2] Dimension du probleme non definie
15 [2] On desire lire un nombre
16 [2] Type d'element incorrect
17 [2] Densite locale incorrecte
18 [2] Point non trouve
19 [2] Option indisponible
20 [2] On doit lire un point
21 [2] Donnees incompatibles
22 [0] Operation malvenue. Resultat douteux
23 [1] Erreur dans le module de trace
24 [2] Impossible de trouver le cote
25 [2] Operation interdite sur un objet complexe
26 [2] Tache impossible. Probablement donnees erronees
27 [2] Erreur generation de maillage. Il est neanmoins cree pour controle
28 [2] Le contour n'est pas reconnu ferme
29 [2] Type d'element non prevu dans CHANGER
30 [2] Pas d'angle superieur a 180 degres pour cette option
31 [2] Erreur de predimensionnement. Donnees probablement erronees
32 [2] Mot reserve %m1:8
33 [2] Les cotes opposes n'ont pas le meme nombre de points
34 [2] Operateur incompatible avec les options utilisees
35 [2] 2 cotes ne correspondent pas
36 [2] Nombre inacceptable %i1
37 [2] On ne trouve pas d'objet de type '%M1:8'
38 [2] Tentative de refus d'une donnee non lue
39 [2] On ne veut pas d'objet de type %m1:8
40 [2] Impossible de calculer l'intersection
41 [2] %m1:8 = %r1 inferieur a %r2
42 [2] %m1:8 = %r1 non compris entre %r2 et %r3
43 [2] %m1:8 = %r1 superieur a %r2
44 [2] Type d'element inconnu %m1:4
45 [2] On cherche %m1:4. Cette propriete n'appartient pas au materiau / de type %m5:8
46 [2] Vous n'avez pas defini '%m1:4 pour le materiau
47 [2] Erreur dans le module assemblage
48 [2] Pas assez de place memoire pour triangulariser
49 [2] Matrice singuliere. Numero de ligne =%i1
50 [2] On ne peut definir l'objet %m1:4 que si on lui a associe / l'objet %m5:8
51 [2] Dimension du type d'element %i1 non coherente avec / la dimension du maillage support %i2
52 [2] Nombre de noeuds du type d'element: %i1 non coherent / avec le nombre de noeud du maillage: %i2
53 [2] Un noeud du second membre n'existe pas dans la matrice : %i1
54 [2] Un type d'inconnue du second membre n'est pas / le dual d'une inconnue de la matrice : %m1:4 mode %i1 noeud %i2
55 [2] Il faut au moins un objet rigidite ou structure
56 [2] Le segment de travail %m1:8 n'est pas correctement initialise
57 [2] Une relation porte sur une structure non definie
58 [2] Dans la table %i1 on ne trouve pas l'objet de type %m1:8 / d'indice %i2
59 [2] Dans les modes de la %i1 ieme sous structure, on ne trouve pas / la composante %m1:4 pour le point %i2
60 [2] On veut que les champs de deplacement des objets solutions / portent sur les memes noeuds munis des memes composantes
61 [2] Dans l'objet solution de type %m1:8 on ne trouve pas les deplacements
62 [2] Il faut au moins la sous directive PONC ou MODE
63 [2] Il manque la sous directive %m1:4 pour definir l'objet %m1:8
64 [2] Le point %i1 n'existe pas dans l'objet %m1:8
65 [2] La composante %m1:4 n'existe pas pour le point %i1 dans l'objet %m5:12
66 [2] L'objet %m1:8 doit etre de type %m9:16
67 [2] L'element %m1:4 ne peut etre integre avec %i1 points de Gauss / Voir routine DONRED
68 [2] Pas de fonctions de forme pour l'element %m1:4. Voir routine SHAPE
69 [2] Attention l'element linespring %i1 a une profondeur de fissure superieure / a son epaisseur. Les contraintes sont mises a zero
70 [0] Attention dans l'element linespring %i1 le triedre defini / par v1 v2 v3 doit etre direct
71 [2] Le materiau %m1:4 n'est pas compatible avec l'element %m5:8
72 [2] L'element %m1:4 n'est pas compatible avec IFOUR=%i1
73 [2] Le NC = NOHARM(/1)nombre de champs %i1 prevu dans la routine REICLE differe du / nombre %i2 prevu dans la routine CRTYMA
74 [2] Element %m1:4 non prevu dans la routine DONOEU
75 [2] Le maillage a un point en double
76 [2] Le champ de nom '%M1:4' n'est pas compatible avec l'element '%M5:8'
77 [2] La composante '%m1:4' n'existe pas pour le champ %m5:30
78 [2] Il faut un mot decrivant le champ a creer
79 [2] Il faut specifier un objet de type %m1:8 et de sous type %m9:16
80 [2] Pas de champ cree: il manque le nom d'une composante et sa valeur
81 [2] Le materiau %m1:8 n'est pas utilisable avec la formulation %m9:16 / et l'option mode =%i1
82 [2] L'operation ET n'est pas prevue pour des SOLUTIONS de type %m1:8
83 [2] Les deux objets %m1:8 doivent etre de meme type
84 [2] L'element %m1:4 et l'element %m5:8 ont le meme support geometrique %m9:1
85 [0] Pas affecte d'element pour la zone geometrique de type %m1:4 / L'element %m1:4 est pris par defaut
86 [2] L'element %m1:4 n'est pas encore implante. Voir routine %m5:12
87 [2] L'element %m1:4 ne peut etre affecte car pas de support geometrique
88 [2] Le champ de materiau et le champ de caracteristiques ne se correspondent pas
89 [2] Le MELEME %i1 n'est pas de type 1
90 [2] La sous-structure %i1 doit etre elementaire (nstru=1)
91 [2] Un point du MELEME %i1 n'appartient pas a la sous-structure %i2
92 [2] Pas d'operande correct
93 [2] On n'encastre pas un objet RIGIDITE CL1 (noeuds bloques)
94 [2] On ne peut pas avoir plus d'un noeud libre dans une liaison mixte
95 [2] Un noeud fluide % i1 dans le MELEME %i2. Encastrement impossible
96 [2] Le point %i1 est donne deux fois dans l'encastrement
97 [2] Nombre de points d'intersection impair ou trop de points d'intersection / Il faut redefinir les profils de chocs
98 [2] Les sous-structures %i1 et %i2 n'ont pas les memes degres de liberte
99 [2] Impossible de faire ET sur des champs par element / de sous type %m1:8 et %m9:16
100 [2] Impossible de faire ET sur les champs par element / Car leurs supports geometriques se recoupent
101 [2] Le %i1 element cree a un point en double
102 [2] Impossible de faire ET sur les objets affectes car un support geometrique / commun avec des formulations elements finis differentes
103 [0] Attention, les sous zones geometriques ne se correspondent pas 2 a 2
104 [2] Probleme avec les dimensions des tableaux contenant les composantes / du champ voir routine ADCHEL
105 [2] %m1:4 n'est pas une bonne composante d'excitation pour le point %i1
106 [2] La composante duale de %m1:4 n'existe pas pour le point %i1
107 [2] Erreur dans les composantes bloquees
108 [2] %m1:4 composante inconnue dans CCHAMP
109 [2] On doit fournir en arguments un champ par element / de sous type %M1:24 ou %M25:48
110 [2] Le %m1:8 de pointeur %i1 n'est pas elementaire (n<>1)
111 [2] On ne peut pas avoir plus de deux noeuds libres dans une liaison libre
112 [2] La sous-structure de pointeur %i1 ne fait pas partie de la base
113 [2] On essaye d'additionner 2 champs par element qui ont une zone geometrique / commune mais une formulation element fini differente
114 [2] Erreur dans les dimensions des tableaux des champs-points voir routine ADCHPO
115 [2] L'element %m1:4 et le materiau %m5:12 ne sont pas compatibles / Voir routine REICLE
116 [2] Operateur LIER : oubli de la composante
117 [2] Operateur LIER : le nombre de coefficients n'est pas egal au nombre de points
118 [2] La sous-structure %i1 ne possede pas de composante %m1:4
119 [2] Operateur LIER : oubli du ou des coefficients
120 [2] Probleme de dimension dans le tableau MWORK : voir routine TRIAG1
121 [0] Attention, un point du champ par element a construire / ne se trouve pas dans le champ par points
122 [0] Attention, une composante du champ par element a / construire n'est pas presente dans le champ par points
123 [2] Il faut donner un vecteur orientant le tuyau fissure zone %i1 element %i
124 [2] Un champ par element de sous type %m1:8 est mal decrit, les points / supports ne coincidant pas avec ceux du modele ou des autres champs
125 [2] L'operation %m1:4 doit se faire sur des objets %m5:12 de meme dimension
126 [2] Erreur dans le maillage de surface initial / Pas plus de 12 facettes touchant un point
127 [2] Le maillage de surface n'est pas ferme
128 [2] Poutre de longueur nulle zone %i1 element %i2
129 [0] Attention, Jacobien negatif
130 [2] L'objet de type %m1:8 de sous-type %m9:16 a deja ete donne
131 [2] On n'attend pas un objet de type %m1:8 de sous-type %m9:16
132 [2] On veut un objet %m1:8 elementaire
133 [2] Dans une base modale on attend au moins des modes ou des liaisons
134 [2] Pas besoin d'objet %m1:8 quand il n'y a pas d'objet %m9:16
135 [2] Incompatibilite entre l'objet %m1:8 et l'objet %m9:16
136 [2] On essaie de detruire un objet reference 2 fois
137 [2] Le vecteur donnant la position de la fissure du tuyau fissure est / parallele a son axe zone %i1 element %i2
138 [2] Le vecteur orientant la poutre est parallele a l'axe de la poutre / zone %i1 element %i2
139 [2] Il n'y a pas de liaison sur la sous-structure %i1
140 [2] Incompatibilite entre les points et composantes des 2 CHPOINTs a multiples / Composante=%m1:4 Point=%i1
141 [2] Les 2 objets de type %m1:8 doivent etre l'un de sous-type %m9:16 / et l'autre de sous-type %m17:24
142 [0] Frequence proche de %r1 La valeur propre trouvee est negative / Elle est remplacee par sa valeur absolue. L'execution continue
143 [2] Resolution impossible detectee au noeud %i1 pour l'inconnue %m1:4
144 [2] 2 objets affectes pointent sur le meme objet geometrique / cad 2 formulations differentes pour la meme zone
145 [2] Il faut donner un champ par element de sous type %m1:8 / pour l'element %m9:12 dans l'operateur  %m13:20
146 [2] Erreur avec les tailles des champs par element voir routine %m1:8
147 [2] Le champ par element de sous type %m1:8 ne peut etre transforme / en un champ par point
148 [2] Le champ par element et l'objet geometrique correspondant n'ont pas le / meme nombre de points par element : contacter votre support
149 [2] Le systeme n'admet pas de solution, noeud : %i1 inconnue : %m1:4
150 [2] Chpoint nul. normalisation impossible
151 [0] Pas de convergence apres %i1 iterations. L'execution continue
152 [2] Operation impossible: il n''y a que des LX
153 [2] Operation illicite dans ce contexte
154 [2] Bloc %m1:23 non actif
155 [2] Erreur lors de la creation d'un LISTMOTS. La %i1ieme chaine de caracteres / existe deja en temps que nom d'objet. Changez le nom de l'objet
156 [2] Le chpoint donne est vide, ou bien son contenu est incompatible avec les noms / de composante imposes par le listmots et le mot-cle (donne ou sous-entendu)
157 [0] Attention l'element linespring %i1 relie 2 zones trop eloignees l'une de l'autre
158 [0] Attention l'element linespring %i1 a une profondeur de fissure superieure / a son epaisseur. La rigidite associee est mise a zero
159 [2] Les caracteristiques du choc sont erronees
160 [2] Il ne peut pas y avoir de choc entre deux appuis
161 [2] Les vecteurs definissant le repere local ne sont pas orthogonaux
162 [2] Le vecteur n'est pas unitaire
163 [2] Le contour doit etre decrit dans le plan xOy
164 [2] Le contour doit etre decrit avec des elements de type SEG2
165 [2] Les deux listes de points de chocs n'ont pas la meme longueur
166 [2] Le mot-cle %m1:4 n'est pas suivi de la donnee correspondante
167 [2] Le mot-cle %m1:4 ne devait plus apparaitre dans les donnees du choc
168 [2] L'operateur detruire ne fonctionne pas pour un objet de type %m1:8
169 [2] Dans %m1:8 on ne trouve pas la contribution modale correspondant / a l'indice %i1
170 [2] Dans %m1:8 le chpoint des contributions modales est nul
171 [2] L'objet de type %m1:8 et de valeur associee %i1 n'est pas un indice / de la table consideree.
172 [2] Les points de l'objet element ne sont pas tous inclus dans le chpoint
173 [2] Tous les points de liaisons n'appartiennent pas au support geometrique / des modes ou des solutions statiques
174 [2] L'objet-indice fourni existe deja dans la table consideree / changez d'objet-indice ou utilisez l'operateur REMPLACER
175 [2] Champs par elements de sous type %m1:8 et %m9:16 ayant des supports / geometriques ou des sous type ou des points supports incompatibles
176 [2] Impossible d'additionner des champs par elements de sous type %m1:8 / et %m9:16
177 [2] Impossible de diviser par le champ par element de sous type %m1:8 / car une composante est nulle
178 [2] Erreur avec les dimensions d'un champ par point voir routine: %m1:8
179 [2] Impossible de multiplier ou diviser ces 2 champs par point
180 [2] Il faut specifier un champ par point avec une seule composante
181 [2] La composante %m1:4 ne peut etre extraite du champ par point specifie / Car elle en est absente
182 [2] Les deux champs par point n'ont pas de support geometrique commun / multiplication impossible
183 [2] Probleme de dimension dans le tableau voir routine RESULT
184 [2] Le champ doit etre un champ de deplacement
185 [2] Erreur numerique probable (precision ?) dans la factorisation d'une raideur
186 [2] Recombinaison impossible: pas de choc dans la base
187 [2] On ne trouve pas la contribution modale correspondant / a l'indice %i1 point %i2
188 [2] On cherche un chpoint qui contient des contributions modales
189 [2] Pas de frequence propre dans l'intervalle fourni
190 [2] On veut lire un entier superieur ou egal a %i1 (on a lu : %i2)
191 [2] On veut lire un flottant superieur ou egal a %r1 (on a lu : %r2)
192 [2] Impossible d'orienter les forces de pression: direction donnee / perpendiculaire a la force de pression au point indique
193 [2] Impossible d'utiliser cet operateur pour la formulation %m1:8
194 [2] Impossible de calculer les contraintes pour la formulation %m1:8
195 [2] Changement de signe du jacobien dans l'element %i1. Maillage incorrect
196 [2] Le type d'un des operandes n'est pas compatible avec l'operateur %m1:8
197 [2] Le mot '%M1:8' n'est pas un nom de composante reconnu
198 [2] Il faut fournir soit 1 seul listmots, soit autant de listmots / qu'il y a de noeuds par element
199 [2] Le LISTREEL fourni n'a pas le bon nombre de reels / pour representer le rectangle (carre) de la matrice elementaire
200 [2] Donnee incorrecte des valeurs de la matrice elementaire: le 1er listreel doit / avoir une longueur de 1 et chaque suivant une longueur incrementee de 1
201 [2] Nombre de "LISTREEL" incorrect
202 [2] Vous fournissez 2 fois le meme parametre
203 [2] Operateur TIRE: n est superieur au nombre de %m1:8
204 [2] Incoherence dans les donnees de l'operateur %m1:6
205 [2] La liste des instants du calcul n'en contient qu'un seul
206 [2] La liste des instants du calcul conduit a un pas de temps negatif
207 [2] La variation du pas de temps est trop importante
208 [2] Le chargement n'est pas defini pour toute la duree du calcul
209 [2] Le nombre de coefficients d'amortissement n'est pas egal / au nombre de modes de l'objet solution
210 [2] Valeur en dehors de la plage de definition des donnees / precision de %r1 non atteinte
211 [2] La liste des valeurs doit etre croissante
212 [2] Les suites n'ont pas les memes longueurs
213 [2] On ne peut pas elever a une puissance reelle un nombre negatif ou nul
214 [2] Les CHPOINTs doivent avoir la meme structure
215 [2] La table est vide
216 [2] Incoherence entre la base et la structure
217 [2] Les listes fournies ne sont pas de meme longueur
218 [0] Attention: CHPOINTs non orthogonaux apres %i1 orthogonalisation(s)
219 [2] La dimension du probleme n'a pas ete definie / ou bien celle fournie n'est pas permise
220 [0] Attention: une des composantes du champ est negative ou nulle / sa puissance est mise a zero
221 [2] Pas de points dans le plan de symetrie / Aucune matrice de rigidite n'a ete cree
222 [2] Il n'y a pas d'element de cette couleur
223 [2] Erreur detectee au cours du processus
224 [2] La structure de l'objet maillage associe au chpoint dans le sous-programme / n'a pas ete prevue dans la programmation
225 [2] La table fournie n'est pas exclusivement une table de %m1:8
226 [2] Option IDEN impossible: les sous structures ne sont pas identiques
227 [2] Oubli des modes
228 [2] Operateur INSS: l'objet solution a inserer n'est pas elementaire
229 [2] Operateur INSS: l'objet solution a inserer / pointe sur un indice de l'objet solution final
230 [2] Deux objets affectes s'appuyant sur la meme geometrie ont des types differents
231 [2] Le point %i1 n'appartient pas au maillage de sortie. Avez vous fait TASSER
232 [2] Un element n'appartient pas au maillage de sortie. Avez vous fait TASSER
233 [2] Dans l'objet solution de type %m1:8 / on ne trouve pas le champ de deplacement associe a l'indice %i1
234 [2] Dans l'objet solution de type %m1:8 / on ne trouve pas le %m9:12 associe au rang %i1
235 [2] Dans l'objet %M1:8 de type %M9:26 on ne trouve pas la liste des %M30:38
236 [2] Impossible d'extraire la composante %m1:8 du champ par element
237 [2] Un axe ne peut etre defini par deux points confondus
238 [2] On ne peut pas bloquer en radial un point sur l'axe
239 [2] Une direction ne peut pas etre definie par un vecteur nul
240 [2] Un jacobien de l'element COQ8 numero %i1 est nul
241 [2] Le module d'un vecteur normal a l'element COQ8 numero %i1 est nul
242 [2] On ne sait pas sauver un objet de type %m1:8
243 [2] Le champ ne contient pas de composantes de type %m1:4
244 [2] Un point de l'objet rigidite n'est pas inclus dans le champ de scalaire
245 [2] L'objet rigidite ne contient pas que des bloquages
246 [2] Le vecteur permettant d'orienter l'element de raccord est nul ou / parallele a la frontiere du fluide
247 [2] Pas plus de 10 sous couches pour un element de plaque composite
248 [2] On ne trouve pas le support qui contient les points
249 [2] La suite de reels doit etre croissante
250 [2] La suite d'entiers doit etre croissante
251 [2] Tentative d'utilisation d'une option non implementee
252 [2] Impossible de remplacer ces objets car supports incompatibles
253 [2] Il faut n (n ltr1/e/(1-nu)
439 [2] Les donnees du modele beton sont erronees : / Deformation a rupture 2 est trop faible ept2 > ltr2/e/(1-nu)
440 [2] Les donnees du modele beton sont erronees : / Des fissures sont ouvertes et ifis = 0
441 [2] Les donnees du modele beton sont erronees : / Les limites en traction sont differentes alors que / le materiau n'est pas fissure.
442 [2] Les donnees du modele beton sont erronees : / Le cisaillement residuel est trop grand  0  1er parametre declare
949 [2] Loi non lineaire externe => pas de parametres redondants
950 [2] Les lois 'VISCO_EXTERNE' ne sont disponibles que pour les elements massifs / avec l'option de calcul tridimensionnel
951 [2] Lois externes incompatibles avec des coques DKT sans points / d'integration dans l'epaisseur
952 [2] Routine NOMATE : impossible de lire le ILOI d'une loi externe / Contactez l'assistance
953 [2] La liste des parametres de la composante %m1:8 n'est pas la meme / dans tout le maillage
954 [2] On n'a pas trouve le parametre %m1:4 pour evaluer la composante %m5:8
955 [2] Le parametre %m1:4 de la composante %m5:8 n'est pas du type FLOTTANT
956 [2] Pas de module externe COMPUT pour l'evaluation des composantes
957 [2] L'appel au module externe COMPUT s'est mal passe. Code retour %i1.
958 [2] Routine COML8 : type de loi externe non pris en charge
959 [2] Le rayon de l inducteur doit etre > 0
960 [2] B non calcule. Probleme integrale elliptique
961 [2] Vous devez entrer E pour la section de la surface plane (en m^2) / et I pour l'intensite (en A)
962 [2] Loi 'VISCO_EXTERNE' '%m5:20' : le code retour de CREEP vaut %i2
963 [2] Donnees incompatibles pour une loi de comportement externe
964 [2] Loi non lineaire externe : la liste des composantes materielles ne peut / pas etre vide
965 [2] Loi de comportement non lineaire externe '%m5:20' : / le code retour de UMAT vaut %i2
966 [2] On a deja lu un objet de type %m1:8
967 [2] Il faut avoir effectue une sauvegarde avant d'appeler FANTOME
968 [2] L'objet de type %m1:8 et de valeur associer %i1 n'etait pas deja sauve
969 [2] La matrice doit etre symetrique
970 [2] Mode de calcul %m1:4 incompatible avec la dimension courante (%i1)
971 [2] Option %m1:4 indisponible en DIMEnsion %i1
972 [2] Pas de caracteristiques materiaux etat final. Modele %i1
973 [2] Pas de contraintes modele %i1 maillage %i2
974 [2] Pas de maillage en %i1. Verifier les donnees.
975 [2] Type d'element fini incorrect.
976 [2] Le nombre d'element doit etre 1.
977 [2] On attend un element support de relations.
978 [2] Ne peut traduire la relation. Verifier donnees.
979 [2] Rigidite de blocage incorrecte. Verifier donnees.
980 [2] L'objet %m1:8 n'a pas le bon nombre de composantes
981 [2] L'object %m1:8 n'a pas le bon support geometrique
982 [2] Il ne faut pas d'elements quadratiques avec le changement de phase
983 [2] Parametre de taille trop grand pour l'element %i1 / de type %m1:4 au point de Gauss %i2 materiau UO2 %i3
984 [2] Modele UO2 disponible uniquement pour la formulation massive 3D et / 2D (sauf en mode FOURIER) et pour la formulation 3D en coques minces
985 [2] Modele UO2: definition incoherente des directions de pre-fissuration
986 [2] Non convergence par rapport aux bifurcations possibles pour / l'element %i1 de type %m1:4 au point de Gauss %i2 materiau UO2 %i3
987 [2] Modele UO2: incoherence des bifurcations ou des / directions de fissuration detectees
988 [2] Modele UO2 - cas 2D: contraintes de cisaillement hors plan non nulles
989 [2] Probleme avec le modele UO2
990 [2] La matrice n'est pas deja factorisee
991 [2] Operateur KONV probleme de pas de temps
992 [2] Valeur de prandtl turbulent erronee
993 [2] Impossible de multiplier un champs de %m1:16 et un champs de %m17:32
994 [2] Le chargement PSUI n'est plus valide, utilisez CHARMECA
995 [2] On ne sait pas changer des elements %m1:4 en elements %m5:8
996 [2] Nombre maximum de sous-pas atteint, arret de pasapas
997 [2] Pas de convergence, arret de %m1:8
998 [2] Trop de decoupage, arret de pasapas
999 [2] Pas de coherence  mecanique-thermique, arret de pasapas
1000 [2] Pilotage non converge apres nombre maximum de sous-pas, arret de pasapas
1001 [2] Tentative de dualise un multiplicateur de Langrange deja dualise: / multiplicateur: %i1 dual: %i2
1002 [2] On ne peut transformer que des QUA4 en CUB8
1003 [2] trop de fichiers suites dans SAUV
1004 [2] Le maillage SHB8 n'a pas de references aux surfaces interne et externe
1005 [2] En absence des mots interne ou externe il faut un CHPOINT de pression
1006 [2] orientation des differentes sous zones incoherentes
1007 [2] Pour les SHB8 il faut un CHPOINT de pression
1008 [2] Le nom de la variable d'environnement est vide ou incorrect. / (Caracteres acceptes : lettres majuscules/minuscules, chiffres et "_")
1009 [2] Nombre inacceptable %r1
1010 [2] Le temps n'a pas ete sauve dans la table des resultats.
1011 [0] tentative de suppression du segment : %i1 de type %m9:14 / qui appartient a un objet %m1:8
1012 [2] Operation interrompue: valeur NaN detectee dans l'objet %m1:8
1013 [2] La liste des temps sauves (ou sauvegardes) n'est pas incluses dans / la liste des temps calcules.
1014 [2] ATTENTION la syntaxe est mauvaise : deux signes = dans la phrase / Elle commence par : %m1:40
1015 [2] Les deux objets %M1:8 n'ont pas la meme longueur.
1016 [2] L'effort vertical norme dans le repere de l'element d'ISS V' / n'est pas compris entre 0 et 1.
1017 [2] Il y a decollement total de la fondation.
1018 [2] On attend un objet de type %M1:8 de dimension %i1
1019 [2] Une donnee de type %M1:8 contient des doublons
1020 [2] Procedure : %M1:24 Il n'y a pas de SI correspondant a ce SINON
1021 [2] Procedure : %M1:24 Il n'y a pas de SI correspondant a ce FINSI
1022 [2] Procedure : %M1:24 Il y a  un SI actif a la fermeture du bloc REPETE
1023 [2] Procedure : %M1:24 Il y a soit un bloc REPETER actif soit un SI actif / lors de l'instruction FINP
1024 [2] Procedure : %M1:24 Il manque un FINSI entre deux SINON
1025 [2] On attendait un %M1:8 de %m9:24
1026 [2] Inconnue primale: %m1:4 deja associe a la duale: %m5:8 / Nouvelle duale proposee dans la matrice: %m9:12
1027 [2] Une donnee de type %M1:8 est vide
1028 [2] Il manque le nom que l'on souhaite attribuer a l'objet de type %m1:8
1029 [2] '%M1:8' n'est pas un nom d'objet valide en GIBIANE
1030 [2] Une erreur est survenue lors de l'importation de la procedure %M1:24
1031 [2] Le nom de la procedure n'est pas le meme derriere $$$$ (%M1:8) et / derriere l'instruction DEBP correspondante (%M9:16)
1032 [2] L'intersection entre le segment %i1 du contour et la cellule / associee au point dont le numero est actuellement %i2 est vide.
1033 [2] L'intersection entre l'element %i1 de l'enveloppe et la cellule / associee au point dont le numero est actuellement %i2 est vide.
1034 [2] La cellule voisine a la cellule associee au point dont le numero est / actuellement %i1 par l'arete %i2 n'a pas ete trouvee.
1035 [2] Les points de la face %i1 de la cellule associee au point dont / le numero est actuellement %i2 sont alignes.
1036 [2] Le nombre d'aretes du polygone est different du nombre de sommets.
1037 [2] Incoherence dans le choix des deformations
1038 [2] Procedure EXEC: NITER>1 et noms d'inconnues au pas courant et precedent / identiques dans un DFDT.
1039 [3] Erreur anormale dans la subroutine %m1:8. Contactez votre support.
1040 [2] Les composantes variables ne peuvent etre creees que sur un maillage / constitue uniquement de POI1
1041 [2] Impossible de creer l'objet CHPOINT car le maillage de POI1 comporte / des noeuds multiples mais la nature est INDETERMINEE
1042 [2] Plusieurs valeurs differentes ont ete definies pour un meme noeud de / la composante %M1:8 alors que la nature est DIFFUSE
1043 [2] Il manque la donnee de l'indice de l'objet TABLE
1044 [2] Matrice declaree %M1:15 mais contenu invalide pour les valeurs : / %r1 %r2 difference: %r3
1045 [2] Incompatibilite dans une TABLE ESCLAVE entre un %m1:8 et un %m9:16
1046 [2] La fusion des %m1:8 n'est pas disponible
1047 [2] Il manque la donnee de l'accolade %m1:1 dans les 80 premiers caracteres / de la ligne %i1 de la notice
1048 [2] Donnees MATERIAUX incompatibles : %m1:40
1049 [0] Nan ou INF dans la matrice. Vecteur solution mis a 0.
1050 [2] Le MODELE 'THERMIQUE' 'CONVECTION' pour les elements finis '%m1:4' / doit comporter un 'MOT' supplementaire : 'INFERIEURE' ou 'SUPERIEURE'
1051 [2] La composante '%m1:4' est definie plusieurs fois dans le LISTMOTS %m5:12
1052 [2] Mot-cle incorrect "%M1:4". Voici la liste des valeurs admises : / %M5:40
1053 [2] Le CHPOINT contient a la fois des inconnues primales et duales
1054 [2] Recombinaison modale impossible car il manque le coefficient associe
1055 [2] %M1:4 n'est pas un nom de couleur valide
1056 [2] Syntaxe obsolete : %m1:40
1057 [2] La taille du LISTREEL %m1:8 doit etre un multiple du nombre de noeuds / pour les elements de type '%m9:12'
1058 [2] L'element numero %i1 n'existe pas dans le MAILLAGE de nom %m1:8
1059 [2] Operation irrealisable : %i1 '%m1:4' %i2
1060 [2] Operation irrealisable : %r1 '%m1:4' %i1
1061 [2] Operation irrealisable : %i1 '%m1:4' %r1
1062 [2] Operation irrealisable : %r1 '%m1:4' %r2
1063 [2] Operation impossible : / La matrice fournie n'est pas definie positive (%r1  %m25:32
1064 [2] (EN) Invalid NODE ID read : %i1
1065 [2] (EN) The MCHAML component '%m1:4' which type is '%m5:20' is expected to be / constant in each SUB-MODEL.
1066 [2] (EN) Error during dataset writing on unit %i1, file %M1:128
1067 [2] (EN) Error %i1 of the I/O status specifier on unit %i2, file %M1:128
1068 [2] (EN) The INTEGER index %i1 is not between %i2 and %i3
1069 [2] (EN) Error atempting to read the line %i1 in the CSV file
1070 [0] (EN) WARNING : %M1:40 soon obsolete
1071 [2] (EN) Error quote still opened at the end of the line
1072 [2] (EN) A mode is missing: the shape of POINT_REPERE %i1 is not given
1073 [2] (EN) The MCHAML fields are unusable. Check their contents
1074 [2] (EN) Orientation of a non massif mesh requires additionnal data
1075 [2] (EN) The '%M1:4' reagent must be different than '%M5:8' product
1076 [2] (EN) The number of reagent (%i1) must be strictly lower than %i2
1077 [2] (EN) A kind of Reaction must be define for each reaction
1078 [2] (EN) A reagent and a product must be specified for each reaction
1079 [2] (EN) Sum of the proportion of phases is not equal to 1, / The Sum is worth %r1 either an error of %r2
1080 [2] (EN) The component '%M1:4' is not present in the 'PHASES' list.
1081 [2] (EN) The 'TAU' parameter of the reaction number %i1 is equal to 0 locally
1082 [2] (EN) Kind of reaction '%M1:4' is not admitted
1083 [2] (EN) The size of the %M1:8 object is expected to be a power of 2
1084 [2] (EN) First frequency must be equal to %r1
1085 [2] (EN) The %i1 th real value must be equal to %r1
1086 [2] (EN) The %i1 th imaginary value must be equal to %r1
1087 [2] (EN) The deformation (LISTREEL) in the tensile stress-strain curve (EVOLUTION) is not strictly increasing
1088 [2] (EN) The slope of the tensile stress-strain curve (%r1) is higher than the Young modulus (%r2)
1089 [2] (EN) The elastic deformation corresponding to the yield stress value must be positive : %r1
1090 [2] (EN) The value of the Young modulus must be positive : %r1
1091 [2] (EN) The value of the yield stress must be positive : %r1
1092 [2] (EN) The first point of the tensile stress-strain curve must be {0;0} : %r1 and %r2
1093 [2] (EN) The definition of unknowns is mandatory withe a 'CHANGEMENT_PHASE' model / Add 'INCO' MOT1 MOT2 to the MODE operator arguments
1094 [2] (EN) WRITE is not possible, incorrect FORMAT
1095 [2] (EN) The type %i1 is not yet available. Please contact Cast3M support.
1096 [2] (EN) The indice %M1:32 in the TABLE is too long (%i1) for MED (Max = 32)
1097 [2] (EN) At least one of the given matrix should be symmetric positive definite
1098 [2] (EN) Treating a MESH of '%m1:4', the number of stress or strain component : %i1 / does not match the assumed number of component : %i2
1099 [2] (EN) The first point of the hardening curve must have a plastic strain equal to zero : %r1
1100 [2] (EN) The hardening curve must have at least 2 points
1101 [2] (EN) The deformation (LISTREEL) of the hardening curve (EVOLUTION) is not strictly increasing
1102 [2] (EN) The nitial slope of the hardening curve is equal to the Young modulus: tensile curve ?
1103 [2] (EN) The model %M1:16 %M17:32 is only available for massive finite elements
1104 [2] (EN) Model unavailable in dimension %i1
1105 [2] (EN) The keyword '%M1:4' cannot be given twice
1106 [2] (EN) The separator '%M1:1' is not a standard character
1107 [2] (EN) The begining of the datas must be greater or equal to 1
1108 [2] (EN) Error closing the file '%M1:48'...
1109 [2] (EN) The number of separators cannot change from one line to another ! / %i1 separators '%M1:1' on the line %i2, %i3 separators '%M1:1' on the line %i4
1110 [2] (EN) A message, title or string cannot contain more than 512 characters
1111 [2] (EN) String is too long after replacements. Please correct the input data.
1112 [2] (EN) Maximum number of shape functions exceeded for the node %i1.
1113 [2] (EN) The law "%M1:32" in the library "%M33:64" / from the directory "%M65:128" could not be loaded by PTRLOI.
1114 [2] (EN) The length of MOT %M1:10 is too long : / limit is %i1 characters.
1115 [2] (EN) the two LISTENTI have not the same length.
1116 [2] (EN) the abscissas or the ordinates of the object EVOLUTION are not of the right type.
1117 [2] (EN) the unknown %M1:4 is not %M5:10.
1118 [2] (EN) The norm of the dual field is incorrect: %r1. It must be between 1d-5 and 1d+5.
1119 [0] (EN) Non convergence in contacts
1120 [0] (EN) ... + %i1 messages similar to the previous one
1121 [2] (EN) An object of type '%m1:8' required in the procedure %M9:33 was not found
1122 [2] (EN) The componant '%M1:8' does not exist in the '%M9:16' type object
1123 [2] (EN) A new computation of the superelement is required after a retrieval
1124 [2] (EN) The slope at one boundary is not defined.
1125 [2] (EN) LX is not an unknown name allowed when defining a relation.
1126 [2] (EN) Unsupported option's mix: non symetric and iteratif
1127 [2] (EN) An error was detected in subroutine %M1:8
1128 [2] (EN) Not enough precise solution %r1 Free modes: %i2
1129 [0] (EN) %i1 residual corrections. Achieved precision: %r1 Free modes: %i2
1130 [2] (EN) The file '%M1:128' does not exist
1131 [2] (EN) The file '%M1:128' is already opened in an other software, it can't be closed
1132 [0] (EN) Beware, differents modes in the CHPOINTs: %i1 & %i2. Current mode: %i3
1133 [0] (EN) Error opening directory: %M1:128
1134 [2] (EN) Missing 'FINP' in procedur file: %M1:24
1135 [2] (EN) Notice not found: %M1:24
1136 [2] (EN) Obsolete directive: You can use directly procedures and notices in the current directory. / They must begin with a $$$$ markup.
1137 [2] (EN) The elementary loading number %i1 is not defined with a LISTOBJE.
1138 [2] (EN) The type of the results list elements is not compatible with a LISTOBJE object.
1139 [2] (EN) The number of shape functions %1 differs from the number of nodes in the field %2
1140 [2] (EN) A field by element of subtype %M1:16, %M17:32 or %M33:48 must be supplied / as an argument
1141 [2] (EN) Procedur %M1:24 was not found in it's file
1142 [2] (EN) Variable distance to cylinder axe
1143 [2] (EN) Invalid intructions set
