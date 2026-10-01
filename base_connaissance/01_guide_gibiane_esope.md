# Guide de travail : langage Gibiane, programmation ESOPE et développement dans Cast3M 2024

Synthèse rédigée à partir du corpus PCW_24 : notice `GIBI`, sources `pilot.eso`, `lirobj.eso`,
`nbno.eso`, includes, note de fabrication 2024. Quand un point est déduit de l'observation du code
plutôt que d'une documentation officielle, c'est signalé.

## 1. Architecture générale

Cast3M est un code éléments finis du CEA (DES/DM2S) composé de trois couches.

1. **Le noyau compilé** : environ 6 640 sources en ESOPE (Fortran 77 étendu), plus quelques sources C
   et un module Fortran 90 (`hhoc3m.F90`, méthode HHO). ESOPE est traduit en Fortran 77 par le
   traducteur `esope`, puis compilé avec gcc/gfortran (version 13.2.0 pour Cast3M 2024).
2. **Le langage Gibiane**, interprété par le sous-programme `PILOT`. Chaque mot du langage correspond
   à un opérateur ou à une directive implanté en ESOPE.
3. **Les procédures Gibiane** (`procedur/*.procedur`), écrites en Gibiane lui-même
   (`PASAPAS`, `TRANSNON`, `DYNAMIC`…), qui enchaînent des opérateurs pour former des algorithmes complets.

La documentation utilisateur est constituée des notices (`INFO NOM ;` les affiche), et la
vérification repose sur les cas tests `dgibi/*.dgibi`, exécutés après chaque fabrication
(`castem24 -test`).

## 2. Le langage Gibiane (points essentiels)

Ces règles viennent de la notice `GIBI` et de l'observation des jeux de données.

- **Instruction** : `resultat = operande1 OPERATEUR operande2 ... ;`. Chaque instruction se termine par `;`.
  La saisie est en format libre.
- **Commentaires** : les lignes avec `*` en première colonne sont ignorées.
- **Noms** : les opérateurs et directives sont reconnus par leurs **4 premiers caractères**
  (`ELIM` = `ELIMINATION`). Les noms d'objets et les mots-clés sont reconnus par leurs 8 premiers
  caractères, selon la notice GIBI.
- **Guillemets** : les mots-clés et les noms d'opérateurs sont souvent écrits entre apostrophes
  (`'OPTI' 'DIME' 2 'ELEM' QUA4 ;`). Cela garantit qu'ils sont lus comme des mots et non comme des
  variables utilisateur de même nom. C'est la pratique recommandée dans les procédures.
- **Chaînage de gauche à droite** : le résultat d'une opération devient le premier opérande de la
  suivante (`RESU = A ET B ET C ;`). Il n'y a donc **pas de priorité arithmétique** : `1 + 2 * 3`
  s'évalue `(1 + 2) * 3`. Il faut utiliser des parenthèses. Ce point est déduit de la règle de
  chaînage de la notice GIBI.
- **Ordre des opérandes** : l'ordre des objets de types différents est en principe indifférent
  (`TRAC OEIL GEOM` équivaut à `GEOM TRAC OEIL`). L'opérateur lit ses arguments par type sur la pile.
- **Création d'un point** sans opérateur : `P1 = 10. 0. 0. ;` (en 3D).
- **Options globales** : `OPTI 'DIME' 3 'ELEM' CUB8 'MODE' 'TRID' ;` fixe la dimension, l'élément et
  le mode de calcul (`PLAN` + `CONT`/`DEFO`, `AXIS`, `TRID`…).
- **Structures de contrôle** : `'SI' cond ; ... 'SINON' ; ... 'FINSI' ;` et
  `'REPE' BLOC n ; ... &BLOC ... 'FIN' BLOC ;` (`&BLOC` donne l'indice de boucle). `'QUIT' BLOC ;`
  sort de la boucle.
- **Procédures** : `'DEBP' NOM arg1*'TYPE' arg2/'TYPE' ... ;` ... `'FINP' resultats ;`.
  `*` indique un argument obligatoire, `/` un argument facultatif (voir les signatures dans le
  lot B, fichier 07).
- **Tables** : `T = 'TABL' ;` puis `T . 'CLE' = valeur ;` ou `T . 1 = ... ;`. Les tables d'entrée de
  `PASAPAS` sont le cas d'usage majeur.
- **Types d'objets courants** : `ENTIER`, `FLOTTANT`, `MOT`, `LOGIQUE`, `POINT`, `MAILLAGE`,
  `CHPOINT` (champ par points), `MCHAML` (champ par éléments), `MMODEL` (modèle), `RIGIDITE`,
  `EVOLUTION` (courbe), `LISTREEL`, `LISTENTI`, `LISTMOTS`, `TABLE`, `NUAGE`.
- **Fin** : `FIN ;`.

Une structure typique de cas test est la suivante : options, maillage, modèle (`MODE`), matériau
(`MATE`), conditions aux limites (`BLOQ`, `DEPI`), chargement (`CHAR`), résolution (`RESO` ou
`PASAPAS`), post-traitement et comparaison à une solution de référence avec `'ERRE' 5 ;` en cas
d'écart (`ERRE` provoque l'échec du test).

## 3. ESOPE : ce qu'il faut savoir pour lire et écrire les sources

ESOPE ajoute à Fortran 77 une gestion dynamique de la mémoire par **segments** (structures
allouables, désignées par un pointeur entier). Les éléments ci-dessous sont observés dans les sources
et les includes du corpus.

### 3.1 Déclarations

```fortran
      SEGMENT MELEME
        INTEGER ITYPEL
        INTEGER NUM(NBNN,NBELEM)
        INTEGER LISOUS(NBSOUS),LISREF(NBREF)
        INTEGER ICOLOR(NBELEM)
      ENDSEGMENT
      POINTEUR IPT1.MELEME, IPT2.MELEME
```

- Les dimensions (`NBNN`, `NBELEM`…) sont des variables ordinaires. Leur valeur **au moment de
  `SEGINI`** fixe la taille du segment.
- Le nom du segment (`MELEME`) est aussi une variable pointeur par défaut. `POINTEUR IPT1.MELEME`
  déclare d'autres pointeurs vers le même type.
- Accès aux membres : `IPT1.NUM(J,K)`, `IPT1.LISOUS(I)`. Sans préfixe, l'accès se fait via le
  pointeur par défaut (`NUM(J,K)` correspond à `MELEME`).
- Dimension courante d'un tableau : `NUM(/1)` (première dimension), `NUM(/2)` (deuxième).
  C'est très utilisé, par exemple `DO I=1,LISOUS(/1)`.
- Forme courte pour un tableau de travail : `SEGMENT ICPR(NBPTS)`.
- `-INC NOM` insère l'include `NOM.INC` (déclarations de segments et COMMON). On trouve presque
  toujours `-INC PPARAM` et `-INC CCOPTIO` : ce dernier contient `IERR` (code d'erreur courant),
  `IIMPI` (niveau d'impression) et `IOIMP` (unité d'impression).

### 3.2 Instructions de gestion des segments

| Instruction | Effet |
|---|---|
| `SEGINI S` | Crée le segment avec les dimensions courantes. Il est alors actif et modifiable. |
| `SEGACT S` / `SEGACT S*MOD` | Active le segment en lecture, ou en modification avec `*MOD`. |
| `SEGDES S` | Désactive le segment. |
| `SEGSUP S` | Supprime le segment. |
| `SEGADJ S` | Réajuste la taille après modification des variables de dimension. |

Remarque : environ 2 040 sources utilisent `SEGDES`, contre 2 150 pour `SEGACT`. Parmi les sources
modifiées en 2023-2024, seul un petit tiers contient `SEGDES`. Les opérateurs récents s'appuient
plutôt sur `ACTOBJ` pour activer les objets lus (voir `nbno.eso`). Il est prudent de s'inspirer des
sources récentes du même domaine.

### 3.3 Squelette d'un opérateur (API de la pile Gibiane)

Exemple réel : `nbno.eso`, l'opérateur `NBNO` qui renvoie le nombre de noeuds d'un maillage.

```fortran
      SUBROUTINE NBNO
      IMPLICIT INTEGER(I-N)
-INC PPARAM
-INC CCOPTIO
-INC SMELEME
      CALL LIROBJ('MAILLAGE',MELEME,1,IRETOU)   ! lecture impérative (ICODE=1)
      CALL ACTOBJ('MAILLAGE',MELEME,1)          ! activation des segments de l'objet
      IF (IERR.NE.0) RETURN                     ! toujours tester IERR après une lecture
      ...                                       ! calcul
      CALL ECRENT(NBN)                          ! résultat ENTIER remis sur la pile
      END
```

- **Lecture** : `LIROBJ(type, pointeur, ICODE, IRETOU)`. `ICODE=1` signifie une lecture obligatoire
  (erreur si l'objet est absent), `ICODE=0` une lecture facultative. `IRETOU` vaut 1 si l'objet a été
  lu. Il existe des variantes typées : `LIRENT` (entier), `LIRREE` (flottant), `LIRCHA` (chaîne),
  `LIRMOT` (mot-clé choisi dans une liste, renvoie son rang), `LIRLOG`, `LIRTAB` (table d'un
  sous-type donné). `QUETYP` donne le type du prochain objet sans le consommer.
- **Écriture du résultat** : `ECROBJ(type, pointeur)`, `ECRENT`, `ECRREE`, `ECRCHA`, `ECRLOG`.
- **Tables** : `ACCTAB` (lecture) et `ECCTAB` (écriture), plus les raccourcis `ACMO`, `ACME`, `ACMF`
  pour lire un objet, un entier ou un flottant à un indice MOT. `CRTABL` crée une table.
- **Erreurs** : `CALL ERREUR(n)` affiche le message `n` du fichier GIBI.ERREUR (lot B, fichier 12). Il faut
  préparer auparavant `INTERR(i)`, `REAERR(i)` et `MOTERR` (COMMON `CCOPTIO`) pour les champs
  `%i`, `%r` et `%m` du message, puis faire `RETURN`. `IERR` devient non nul.

Les sources de ces routines sont dans le fichier 05 (compactées : cadres de commentaires supprimés, espaces internes réduits).

### 3.4 Ajouter un opérateur (démarche déduite de `pilot.eso`)

1. **Déclarer le nom** : l'ajouter à la fin de `DATA MDIR3/.../` dans `pilot.eso` et incrémenter
   `PARAMETER (NDIR3=...)`. Le commentaire d'en-tête de PILOT indique que seul `MDIR3` doit être
   complété désormais.
2. **Brancher** : le rang de l'opérateur est `II`, et le traitement se fait à l'étiquette `100+II`.
   Le dernier `GOTO` calculé (`IF (II.LE.600) GOTO (601,...,617),II-500`) doit être prolongé d'une
   étiquette, et le bloc correspondant ajouté :
   ```fortran
   618   CALL MONOPE
         GOTO 1
   ```
3. **Écrire la sous-routine** `monope.eso` en suivant le squelette ci-dessus. L'en-tête d'une source
   suit le format `C MONOPE    SOURCE    AUTEUR    AA/MM/JJ ...`.
4. **Écrire la notice** `monope.notice` : en-tête `$$$$ MONO     NOTICE ...`, syntaxe, ligne
   `Section : ...`, puis les sections `FRAN====` et `ANGL====`.
5. **Écrire un cas test** `dgibi/monope.dgibi` : en-tête `* Section : ...`, comparaison à une valeur
   de référence et `'ERRE' 5 ;` en cas d'écart.
6. **Compiler et lier** : selon la note de fabrication, on utilise `compilcast24 fichier.eso`
   (traduction ESOPE puis compilation), puis `essaicast24` pour l'édition de liens. En cas d'erreur
   de traduction, un fichier `.lst` est produit. En cas d'erreur de compilation, un `.txt`.

Pour **modifier un opérateur existant**, on cherche son nom dans le fichier 02 (sous-programme appelé
par PILOT), puis on descend dans l'arbre d'appel grâce aux flèches `→` de l'index des sources
(lot B, fichier 04).

## 4. Conventions du corpus

- **Encodage** : les fichiers d'origine sont en Latin-1 (ISO-8859-1) ou en ASCII. Ce lot est converti
  en UTF-8 et les sources y sont compactées : pour recompiler, il faut repartir des fichiers d'origine (encodage et colonnes
  Fortran conservés).
- **En-tête des fichiers** : `C NOM SOURCE AUTEUR AA/MM/JJ HH:MM:SS NNNNN` pour les sources,
  `* NOM PROCEDUR AUTEUR AA/MM/JJ ...` pour les procédures, `$$$$ NOM NOTICE AUTEUR AA/MM/JJ ...`
  pour les notices. La date est celle de la dernière modification et le nombre final est un numéro
  d'évolution.
- **Notices de procédures** : elles ont le même nom que la procédure. Les procédures préfixées par
  `@` sont des utilitaires.
- **Fichier des messages** : GIBI.ERREUR contient des blocs `numéro niveau` suivis du texte. Les
  langues présentes sont FRAN et ANGL.
