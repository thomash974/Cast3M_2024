# Sources ESOPE clés : API de lecture/écriture des arguments et exemple d'opérateur

Comme les autres extraits de sources, les espaces internes sont compactés et les cadres de commentaires supprimés.

## lirobj.eso
```fortran
C LIROBJ ( ITOPE , IRET , ICODE , IRETOU )
C CE SERVEUR FAIT PARTIE DU NOYAU DE GESTION DES OBJETS.(GIBI 1.00)
C IL A POUR BUT DE RAMENER UNE DONNEE DE TYPE ITYPE.
C LA LECTURE EST IMPERATIVE OU NON.
C LA LECTURE DES DONNEES EST EFFECTUEE JUSQU'A CE QUE LE SERVEUR
C RENCONTRE UNE DONNEE QUI N'EST PAS UN OBJET.DANS LE CAS DE LECTURE
C IMPERATIVE IL TOMBE EN ERREUR (MESSAGE: PAS D'OBJET DE CE TYPE )
C LISTE DES ARGUMENTS :
C ITYPE(2) - ENTREE : PRECISE LE TYPE DE L'OBJET. SI ITYPE(2)
C EST MIS A BLANC LE TYPE EST INDIFFERENT
C - SORTIE : DONNE EN RETOUR LE TYPE DE L'OBJET.
C IRET - SORTIE : VALEUR ATTACHEE A L'OBJET.
C ICODE - ENTREE : PRECISE PAR 1 OU 0 SI LA LECTURE EST
C IMPERATIVE OU NON.
C IRETOU - SORTIE : PRECISE PAR 1 OU 0 SI LA LECTURE A EU
C LIEU OU NON.
      SUBROUTINE LIROBJ( ITOPE , IRET , ICODE , IRETOU )
      IMPLICIT INTEGER(I-N)
-INC PPARAM
-INC CCOPTIO
      CHARACTER*(*) ITOPE
      CHARACTER*(8) ITYPE
      IRETOU=0
      IRET =0
      ITYPE =ITOPE
      ICOD =ICODE
      CALL LIRABJ(ITYPE,IRET,ICOD,IRETOU)
      IF(ITOPE.EQ.' ') ITOPE=ITYPE
C Activation de l'objet lu si possible
C IF (IRETOU .NE. 0) CALL ACTOBJ(ITYPE,IRET,1)
      RETURN
      END
```
## lirabj.eso
```fortran
      SUBROUTINE LIRABJ( ITYPE , IRET , ICODE , IRETOU )
      IMPLICIT INTEGER(I-N)
-INC PPARAM
-INC CCNOYAU
-INC CCOPTIO
-INC SMBLOC
-INC CCASSIS
-INC SMCOORD
-INC SMLOBJE
      LOGICAL JTYP
      CHARACTER*(*) ITYPE
      CHARACTER*(8) ITYP,INTERM,MOVID8
      CHARACTER*8 JTYOBI
C SAVE IPLAC
      LOGICAL LOMISA,ILOREMP
      integer desrev
      character*(8) desret
      MOVID8=' '
      IF(LEN(ITYPE).LT.8) THEN
        CALL ERREUR(5)
        RETURN
      ENDIF
      iextab=0
C initialisation de lotesc
      lotesc=.false.
      ith=0
      if (nbesc.ne.0) ith = oothrd
      if (ith .ne.0) lotesc=.true.
C write (6,*) ' dans lirabj ',ith
      if (lotesc) then
        call liresc(itype,iret,icode,iretou)
        return
      endif
      IF (NOMLU.EQ.0) CALL LIRNOM
      IRETOU=0
      IF (IERR.GT.1) RETURN
      INSTAB=0
      IF (ITYPE(1:5).EQ.'TEXTE') INTEXT=1
      ITYP=' '
      JTYP=.FALSE.
C DANS LE CAS DE LECTURE D'UN FLOTTANT ON ADMET DE LIRE UN ENTIER
      IF (ITYPE(1:8).EQ.'FLOTTANT') THEN
        ITYP='ENTIER'
        JTYP=.TRUE.
      ENDIF
C DANS LE CAS DE LECTURE D'UN MOT ON ADMET DE LIRE UNE PROCEDURE
      IF (ITYPE(1:4).EQ.'MOT ') THEN
        ITYP='PROCEDUR'
        JTYP=.TRUE.
      ENDIF
C if ( iimpi.eq.1876) THEN
C write(6,*) ' lirabj on demande  ',itype
C write(6,*) ' ibpile,ihpile ',ibpile,ihpile
C write(6,*) ' instab,lectab,iextab' ,instab,lectab,iextab
C endif
   5 L = IHPILE-IBPILE
      ILTTA = 0
      INSTAB= 0
      IF (L .lt. 0) goto 2
C ON CHERCHE SI UN OBJET DU TYPE DESIRE EST
C DEJA DANS LA PILE
   1 IBPILN=0
C write(6,*) ' apres 1  lectab instab iextab ibpile ihpile'
C write(6,*) lectab ,instab, iextab, ibpile,ihpile
      DO 10 I=IBPILE,IHPILE
C write(6,*) 'bcl 10 i jpoob1(i) iva' ,i,JPOOB1(I),jpoob4(i)
      IF(.NOT.JPOOB1(I)) THEN
C ON MET A 0 INSTAB CAR LA SPECIFICATION PRECISE QUE LA DONNEE INDICE
C DOIT IMMEDIATEMENT SUIVRE LA DONNEE DE LA TABLE
           INSTAB=0
           GO TO 10
      ENDIF
      IF (IBPILN.EQ.0) IBPILN=I
      IF (INSTAB.NE.0.AND.LECTAB.EQ.0 ) THEN
C LA DONNEE QUI PRECEDE EST UNE TABLE ou un objet ON REGARDE SI
C CELLE CI EST UN SEPARATEUR SUIVI D'UN INDICE
C DANS CE CAS ON SE CONTENTE DE REMPLACER CE NOUVEL OBJET PAR CELUI
C CONTENU DANS LA TABLE SINON ON REND CE NOUVEL OBJET
C DANS TOUS LES CAS ON POSITIONNE INSTAB A 0
         ISUCC=INSTAB
C write (6,*) ' lirabj appel a rempil '
         CALL REMPIL(I-1,ISUCC)
C write(6,*) ' apres rempil i isucc',i,isucc
         iextab=0
         if (i+1.le.ihpile) then
          if (jtyobj(i+1).eq.'TABLE   '.and.isucc.eq.1) iextab=1
         endif
C if( iimpi.eq.1876) call ecpil ('lirabj boucle')
         INSTAB=0
         IF(IERR.NE.0) RETURN
         IF(ISUCC.EQ.1.AND.ILTTA.EQ.I-1) ILTTA=0
         IF(ISUCC.EQ.1) GO TO 1
      ENDIF
C VECTORIZATION avec LISTOBJE
C Si LISTOBJE de contenu 'ESCLAVE' en sequentiel, remplace par les
C objets resultat lorsqu'ils sont disponibles et on met MLOBJE.TYPOBJ
C a jour
        IF ( jtyobj(I) .eq. 'LISTOBJE' .and. LUPARA .eq. 0) THEN
          MLOBJE = JPOOB4(I)
          segact, MLOBJE
          NOBJ1 =MLOBJE.LISOBJ(/1)
          if (MLOBJE.TYPOBJ .eq. 'ESCLAVE ' .and. NOBJ1 .GT. 0) then
            if (iimpi .eq. 1234) write(ioimp,*)
     & 'Liste d''objets esclaves utilisee en sequentiel !!',MLOBJE
            LOMISA = .FALSE.
            if (.not.lodesl.or.ith.ne.0) lomisa = .true.
            IF ( LOMISA ) THEN
              call oooeta(mcoord,ieta,imod)
              if (ieta.eq.1) segdes mcoord
C On attend que les NOBJ1 objets soient disponibles en partant du dernier
              DO 13 IOB1=NOBJ1,1,-1
                MESRES =MLOBJE.LISOBJ(IOB1)
                SEGACT MESRES
                if (.not.loremp) then
  130 continue
                  segdes mesres*record
                  SEGACT MESRES*(ECR=1,MOD)
                  if (.not.loremp) then
                   write(6,*) ' loremp pas vrai dans lirabj '
                   goto 130
                  endif
                endif
                if (ieta.eq.1) segact mcoord
                if (iimpi .eq. 1234)
     & write(ioimp,*) 'le segment a ete mis a jour ',MESRES
                call decesc(mesres,desret,desrev)
C Remplacement de l'objet et placement du type
                segact, MLOBJE*MOD
                MLOBJE.LISOBJ(IOB1) = desrev
                if(MLOBJE.TYPOBJ .eq.'ESCLAVE ') MLOBJE.TYPOBJ = desret
                SEGDES, MESRES
 13 continue
            ENDIF
          endif
          SEGACT, MLOBJE
          IF (LISOBJ(/1).NE.0) THEN
            CALL PLAMO8(LTYPOB,NTYPOB,IPLA,MLOBJE.TYPOBJ)
            IF (IPLA.EQ.0) THEN
              CALL ERREUR(1138)
              RETURN
            ENDIF
          ENDIF
        ENDIF
C Actualisation objet ESCLAVE
C JYY
        IF ( jtyobj(I) .eq. 'ESCLAVE ' ) then
          MESRES = JPOOB4(I)
          if (iimpi .eq. 1234)
     & write(ioimp,*) ' un objet esclave utilise !!!',mesres
          LOMISA = .FALSE.
          if (.not.lodesl.or.ith.ne.0) lomisa =.true.
C il faut faire la mise a jour pour continuer le travail
C mise a jour eventuelle et menage eventuel
          IF ( LOMISA ) THEN
C on essaye de recuperer un travail d'assistant. A priori mcoord est
C actif et le pauvre assistant risque d'etre bloque dessus
C on va donc desactiver mcoord puis le reactiver son etat
C de même pour la tétralogie ipflo...
            call oooeta(mcoord,ieta,imod)
            if (ieta.eq.1) segdes mcoord
            SEGACT MESRES
            if (.not. loremp) then
  15 continue
              segdes mesres*record
              SEGACT MESRES*(ECR=1,MOD)
              if (.not. loremp) then
                write(6,*) ' loremp pas vrai dans lirabj '
                goto 15
              endif
            endif
            if (ieta.eq.1) segact,mcoord
            if (iimpi .eq. 1234)
     & write(ioimp,*) 'le segment a ete mis a jour ',MESRES
            call decesc(mesres,desret,desrev)
            JPOOB4(I) = desrev
            JTYOBJ(I) = desret
C c'est un element d'une table on ne fais pas de mise a jour de celle ci
            indic1 = JPOOB2(I)
            if (indic1.eq.0) then
C write (6,*) 'lirabj esclave mais pas de nom '
            else
              iouep2(indic1)=desrev
              inoob2(indic1)=desret
            endif
            SEGDES MESRES
          ENDIF
        ENDIF
C JYYY
      JTYOBI=JTYOBJ(I)
C write(6,*) ' jtyobi itype iextab ',jtyobi,itype ,iextab
      IF(ITYPE(1:8).EQ.JTYOBI.and.iextab.eq.0) GO TO 11
      IF(JTYP) THEN
       IF(ITYP.EQ.JTYOBI.and.iextab.eq.0) GO TO 11
      ENDIF
      IF(INTEXT.EQ.0.AND.JTYOBI.EQ.'TEXTE   ') THEN
C ON VIENT DE TOMBER SUR UN OBJET DE TYPE TEXTE
         IIO=JPOOB4(I)
         CALL INSPIL(IIO,I)
         GO TO 5
      ENDIF
      IF(ITYPE(1:8).EQ.MOVID8) THEN
         IF(JTYOBI.NE.'SEPARATE'.AND.JTYOBI.NE.'TABLE   '.AND.
     $ JTYOBI.NE.'METHODOL' ) GO TO 11
      ENDIF
C write(6,*) ' iblqm ' , iblqm
      if (iblqm.eq.1) then
       IF (JTYOBI.EQ.'MOT     ') GOTO 20
       IF (JTYOBI.EQ.'PROCEDUR') GOTO 20
      endif
      IF(JTYOBI.EQ.'TABLE   '.OR.JTYOBI.EQ.'OBJET   ') THEN
          INSTAB=1
C write(6,*) ' on positionne instab à 1'
          IF(ILTTA.EQ.0) ILTTA=I
      ENDIF
      IF(JTYOBI.EQ.'METHODOL') THEN
          IF(MOBJCO.NE.0) THEN
             IF(ITYPE(1:6).EQ.'OBJET ') THEN
                JPOOB4(I) =MOBJCO
                 GO TO 11
             ENDIF
             INSTAB=2
             IF(ILTTA.EQ.0) ILTTA=I
          ELSE
             IF(ITYPE(1:8).EQ.MOVID8) GO TO 11
          ENDIF
      ENDIF
   10 CONTINUE
    2 CONTINUE
C IL N'EN EXISTE PAS
C ON VA LIRE DANS LA TABLE INTERMEDIAIRE
      IF(ISTOP.EQ.1) GO TO 20
      IPLAC=ITINTE(IINTPO)
C write (6,*) ' iplac dans lirabj apres 2 ',iplac
      IRAZ=IPLAC
      IF(IRAZ.LE.0) GO TO 28
      N= JTYOBJ(/2)
      IF( IHPILE.GE.N) THEN
         N=N+1
         SEGADJ JPOOB
         JTYOBJ(N)=' '
      ENDIF
      IIP=IOUEP2(IPLAC)
      IF(INOOB2(IPLAC).EQ.MOVID8) THEN
C ON MET INSTAB A ZERO
         INSTAB=0
         IINTPO=IINTPO+1
         GO TO 2
      ENDIF
      IHPILE=IHPILE+1
      interm=inoob2(iplac)
      JTYOBJ(IHPILE)=interm
      JPOOB1(IHPILE)=.TRUE.
      JPOOB2(IHPILE)=IPLAC
      JPOOB4(IHPILE)=IIP
      I=IHPILE
      IINTPO=IINTPO+1
C ON VIENT DE LIRE UN OBJET
      INSTAB=0
C write (6,*) ' lirabj iintpo itinte interm ',iintpo,itinte(iintpo),
C > interm
      if( interm.eq.ITYPE(1:8)) go to 1
      if (itinte(iintpo).gt.0.and.
     > (interm.eq.'TABLE   '.or.interm.eq.'SEPARATE')) goto 2
      if (jtyobj(ihpile-2).eq.'TABLE   '.AND.
     > jtyobj(ihpile-1).eq.'SEPARATE') iextab=1
C write (6,*) ' jtyobj instab ',jtyobj(ihpile-2),
C > jtyobj(ihpile-1),jtyobj(ihpile),instab
      GO TO 1
   11 CONTINUE
C ON A TROUVE L'INFORMATION DEMANDE
C write (6,*) ' ancien ibpile ',ibpile,' nouveau ',ibpiln
      IPLAC=JPOOB2(I)
C write (6,*) ' iplac dans lirabj apres 11 ',iplac,jtyobj(i)
      IF (IBPILN.NE.0) IBPILE=IBPILN
      IRETOU=1
      IF(ITYPE(1:8)
C ... (suite tronquée dans le lot noyau)
```
## lirent.eso
```fortran
      SUBROUTINE LIRENT(IVAL , ICODE , IRETOU )
      IMPLICIT INTEGER(I-N)
-INC PPARAM
-INC CCOPTIO
      CHARACTER*(8) IEN
      IEN='ENTIER  '
      CALL LIROBJ(IEN ,IRAT,ICODE,IRETOU)
      IF(IERR.NE.0) RETURN
      IF(IRETOU.EQ.0) RETURN
      IVAL=IRAT
      RETURN
      END
```
## lirree.eso
```fortran
      SUBROUTINE LIRREE(XVAL , ICODE , IRETOU )
      IMPLICIT INTEGER(I-N)
-INC CCNOYAU
-INC PPARAM
-INC CCOPTIO
-INC CCASSIS
      REAL*8 XVAL
      CHARACTER*(8) IFL
      ith=0
      if (nbesc.ne.0) ith=oothrd
      lotesc=.false.
      if (ith.ne.0) lotesc=.true.
      IFL ='FLOTTANT'
      ICOD=ICODE
      CALL LIRABJ(IFL,IRAT,ICOD,IRETOU)
      IF(IERR .NE.0) RETURN
      IF(IRETOU.EQ.0) RETURN
      IF(IFL.EQ.'FLOTTANT'.AND. (.not. lotesc)) THEN
         if(nbesc.ne.0) segact ipiloc
         XVAL=XIFLOT(IRAT)
         if(nbesc.ne.0) SEGDES,IPILOC
      ELSEIF(IFL.EQ.'FLOTTANT'.AND. lotesc) THEN
         mescla=imescl(ith)
         XVAL=ESOPRE(IRAT)
      ELSEIF(IFL.EQ.'ENTIER  ') THEN
         XVAL=IRAT
      ENDIF
      END
```
## lirmot.eso
```fortran
C CE PROGRAMME PERMET DE SIMULER UN SOUS-TYPAGE AU NIVEAU DES MOTS
      SUBROUTINE LIRMOT(MOTCLE,MOTDI ,IVAL,ICOND)
      IMPLICIT INTEGER(I-N)
      IMPLICIT REAL*8 (A-H,O-Z)
C MOTCLE TABLEAU DES MOTS CLES POSSIBLES
C MOTDI +/-DIMENSION DE MOTCLE
C si MOTDI<0, on souhaite utiliser des abreviations(#7969)
C IVAL POSITION DU MOT TROUVE DANS MOTCLE (0) SI ECHEC
C ICOND LECTURE IMPERATIVE (=1) OU NON (=0)
-INC PPARAM
-INC CCOPTIO
      CHARACTER*(*) MOTCLE(*)
      CHARACTER*(LOCHAI) MOT,MOTTOT
      EXTERNAL LONG
      MOT = ' '
      MOTTOT = ' '
C MOTDIM DIMENSION DE MOTCLE
      motdim=abs(motdi)
      IVAL=0
      IV=0
C LECTURE D'UNE CHAINE DE LMOT CARACTERES
      ICONDO=ICOND
      LMOT=LEN(MOTCLE(1))
      CALL LIRCHA(MOTTOT,ICONDO,IRETOU)
      IF(IERR .NE.0) RETURN
      IF(IRETOU.EQ.0) RETURN
      MOT=MOTTOT(1:LMOT)
C RECHERCHE DE CE MOT DANS LA LISTE DES MOTS-CLES
      DO 1 I=1,MOTDIM
        IF(MOT(1:LMOT).EQ.MOTCLE(I)) GOTO 2
   1 CONTINUE
      i=0
      IF(motdi.gt.0) goto 4
C CAS ABBREVATION : RECHERCHE DE CE MOT DANS LA LISTE DES MOTS-CLES
C ABBREGES A LA TAILLE DU MOT
      LLU=LONG(MOT(1:LMOT))
      ITROUV=0
      DO 5 I=1,MOTDIM
        LLIS=LONG(MOTCLE(I))
        IF( MOT(1:MIN(LLU,LLIS)).NE.
     & MOTCLE(I)(1:MIN(LLU,LMOT,LLIS)))GOTO 5
        ITROUV=ITROUV + 1
        IV=I
   5 CONTINUE
      I=IV
      IF(ITROUV.EQ.1)THEN
        GOTO 2
      ELSEIF(ITROUV.GT.1)THEN
C Le mot n'est pas discriminant dans la liste : plusieurs mots de la liste commencent par MOT(1:LLU)
C Je fais comme si j'avais lu '? '
        MOT='?'
      ENDIF
   4 CONTINUE
C MOT NON TROUVE DANS LA LISTE : ON TESTE SI IL S'AGIT DE "?"
      IF(MOT(1:2).NE.'? ') GOTO 3
C CAS "?" : ON ECRIT LA LISTE ET ON QUITTE
      WRITE (IOIMP,100) (MOTCLE(IM),IM=1,MOTDIM)
 100 FORMAT(/,' LISTE DES MOTS RECONNUS :',/,(8(1H ,A)))
      RETURN
      RETURN
C ECHEC : SI LECTURE OBLIGATOIRE, ON PRODUIT UNE ERREUR
C ET DANS TOUS LES CAS, ON QUITTE
   3 CALL REFUS
      MOTERR = MOTTOT
      IF(ICOND.EQ.1)THEN
       CALL ERREUR(7)
       WRITE(IOIMP,110) (MOTCLE(I),I=1,MOTDIM)
 110 FORMAT(8(1H ,A))
      ENDIF
      RETURN
C SUCCES : ON RETOURNE L'INDICE DANS LA LISTE
   2 CONTINUE
      IVAL=I
      RETURN
      END
```
## lirtab.eso
```fortran
      SUBROUTINE LIRTAB(ITYP,IRETA,ICODE,IRETOU)
      IMPLICIT INTEGER(I-N)
-INC PPARAM
-INC CCOPTIO
-INC CCNOYAU
      CHARACTER*(*)ITYP
      CHARACTER*8 TYPE,TAPIND,TYPOBJ,CHARIN
      CHARACTER*(LOCHAI) CHARRE
      CHARACTER*8 LETYPE
      REAL*8 XVALIN,XVALRE
      LOGICAL IV,LOGIN,LOGRE
      SEGMENT IVAL1
        INTEGER IVAL(NCLE)
        INTEGER NOVAL(NCLE)
        CHARACTER*8 TYVAL(NCLE)
      ENDSEGMENT
      IRET =0
      ireta =0
      iretou=0
      IFIN =0
      LE =LEN(ITYP)
      N =0
      NCLE =10
      SEGINI,IVAL1
      TYPE=ITYP
    1 CONTINUE
      MOTERR(1:8)=TYPE
      if (icode.ne.0) CALL MESLIR(-173)
      CALL LIROBJ ('TABLE',IRET,ICODE,IRETO)
C write(6,*) ' lecture de la table ' , iret
      IF(IERR.NE.0) GO TO 10
      IF(IRETO.EQ.0)GO TO 10
      TYPOBJ = ' '
      CALL ACCTAB(IRET,'MOT     ',IVALIN,XVALIN,'SOUSTYPE',LOGIN,
     $ IOBIN, TYPOBJ,IVALRE,XVALRE,CHARRE ,LOGRE,IOBRE)
      IF(TYPOBJ.EQ.'MOT     ') THEN
C write(6,*) ' le  ivalre ' , le , ivalre
        IF(IVALRE.EQ.LE) THEN
          IF(CHARRE(1:LE).EQ.ITYP) THEN
C ON A TROUVE LA TABLE RECHERCHEE IL FAUT METTRE A JOUR LA
C LECTURE DES TABLES PRECEDEMMENT LUES
             ireta=iret
             iretou=1
C write(6,*) ' c est celle la'
              GO TO 10
          ENDIF
        ENDIF
      ENDIF
C CE N EST PAS UNE BONNE TABLE ON REMPLIT IVAL ET ON RETOURNE EN
C LECTURE
      N = N + 1
      IF (N.GT.NCLE)THEN
        SEGADJ IVAL1
      ENDIF
      IVAL(N) =IMOTLU
      NOVAL(N)=INOOB1(IMOTLU)
      TYVAL(N)=INOOB2(IMOTLU)
      GO TO 1
C AVANT DE SORTIR ON REMET LES TABLES LUES PAS(DU BON SOUSTYPE) EN
C LECTURE
   10 CONTINUE
      IF(N.EQ.0) GO TO 20
      DO 2 J=1,N
      IV=.TRUE.
      imola= IVAL(J)
      IF(INOOB1(imola).NE.NOVAL(J)) IV=.FALSE.
      IF(INOOB2(imola).NE.TYVAL(J)) IV=.FALSE.
      IF(IV) THEN
           JPOOB1(imola)=.TRUE.
           IF(IBPILE.GT.imola) IBPILE=imola
           IF(IHPILE.LT.imola) IHPILE=imola
      ELSE
           NN = JPOOB1(/1)
           DO 5 KK=1,NN
             IF(INOOB1(KK).NE.NOVAL(KK)) GOTO 5
             IF(INOOB2(KK).NE.TYVAL(KK)) GOTO 5
             IF(JPOOB1(KK)) GOTO 5
             JPOOB1(KK)=.TRUE.
             GOTO 6
    5 CONTINUE
           CALL ERREUR(5)
    6 CONTINUE
      ENDIF
    2 CONTINUE
   20 CONTINUE
      SEGSUP IVAL1
      END
```
## quetyp.eso
```fortran
      SUBROUTINE QUETYP(ICHA , ICODE , IRETOU )
      IMPLICIT INTEGER(I-N)
-INC PPARAM
-INC CCOPTIO
      CHARACTER*(*) ICHA
      IF(LEN(ICHA).NE.8) CALL ERREUR (5)
      ICHA=' '
      ICOD=ICODE
      CALL LIRABJ(ICHA ,IRAT,ICOD,IRETOU)
      IF(IERR.NE.0) RETURN
      IF (IRETOU.EQ.0) RETURN
      CALL REFUS
      RETURN
      END
```
## ecrobj.eso
```fortran
      SUBROUTINE ECROBJ( MCH,IRET)
      IMPLICIT INTEGER(I-N)
-INC CCASSIS
      CHARACTER*(*) MCH
      CHARACTER*8 MTEM
      DIMENSION ITEMP(2)
C L'objet de type MCH et de pointeur IRET est rendu SEGACT
C actobj retire le status *MOD aux segments
C CALL actobj(MCH,IRET,1)
      ith=0
      if (nbesc.ne.0) ith=oothrd
      if (ith.eq.0) then
        MTEM=MCH
        ITEMP(2)=0
C LA VALEUR EXISTE-T-ELLE DEJA DANS LA PILE
        ITEMP(1)=IRET
        CALL ECPI(ITEMP,MTEM)
        RETURN
      else
C cas de l'esclave
        mescla=imescl(ith)
        call ecresc(i)
        esoplu(i)=.false.
        esopty(i)=mch
        esopva(i)=iret
      endif
      END
```
## ecrent.eso
```fortran
      SUBROUTINE ECRENT( IRET )
      IMPLICIT INTEGER(I-N)
-INC CCASSIS
      DIMENSION ITEMP(2)
      ith=0
      if (nbesc.ne.0) ith=oothrd
      if (ith.eq.0) then
C POUR INHIBER LA LECTURE DE CARTES
      ITEMP(2)=0
      ITEMP(1)=IRET
  60 CALL ECPI(ITEMP,'ENTIER  ')
      RETURN
      else
C cas de l'esclave
      ith=oothrd
      mescla=imescl(ith)
      call ecresc(i)
      esoplu(i)=.false.
      esopty(i)='ENTIER'
      esopva(i)=iret
      endif
      END
```
## nbno.eso
```fortran
C RAMENE LE NOMBRE DE NOEUDS D'UN OBJET (ELEMENT)
      SUBROUTINE NBNO
      IMPLICIT INTEGER(I-N)
-INC PPARAM
-INC CCOPTIO
-INC SMELEME
-INC SMCOORD
      SEGMENT ICPR(nbpts)
      CALL LIROBJ('MAILLAGE',MELEME,1,IRETOU)
      CALL ACTOBJ('MAILLAGE',MELEME,1)
      IF (IERR.NE.0) RETURN
      SEGINI ICPR
      DO 1 I=1,ICPR(/1)
      ICPR(I)=0
   1 CONTINUE
      IPT1=MELEME
      DO 3 I=1,MAX(1,LISOUS(/1))
        IF (LISOUS(/1).NE.0) IPT1=LISOUS(I)
        NBNN =IPT1.NUM(/1)
        NBELEM=IPT1.NUM(/2)
        DO 5 K=1,NBELEM
          DO 4 J=1,NBNN
            L=IPT1.NUM(J,K)
            ICPR(L)=1
   4 CONTINUE
   5 CONTINUE
   3 CONTINUE
      NBN=0
      DO 6 I=1,ICPR(/1)
        NBN=NBN+ICPR(I)
   6 CONTINUE
      SEGSUP ICPR
      CALL ECRENT(NBN)
      END
```
## acctab.eso
```fortran
      SUBROUTINE ACCTAB(MTABLE,TAPIND,IVALIN,XVALIN,CHARIN,LOGIN,IOBIN,
     $ TYPOBJ,IVALRE,XVALRE,CHARRE,LOGRE,IOBRE)
C DONNE ACCES A UN OBJET DANS UNE TABLE CONNAISSANT LE TYPE
C DE L'INDICE ( TAPIND ) ET LA VALEUR DE L'INDICE SUIVANT SON
C TYPE . ENTIER-IVAL;FLOTTANT-XVAL;MOT-CHARIN;LOGIQUE-LOGIN;
C AUTRE-IOBIN
C ON PEUT PRECISER LE TYPE D'OBJET ATTENDU DANS TYPOBJ CE
C QUI PROVOQUE UN MESSAGE D'ERREUR S'IL N'EXISTE PAS.
C EN SORTIE : TYPOBJ TYPE DE L'OBJET AU CAS OU TYPOBJ ETAIT = ' '
C VALEUR DE L'OBJET DANS IVALRE SI ENTIER; XVALRE SI
C FLOTTANT; CHARRE SI MOT ( DE LA LONGUEUR DE LA
C CHAINE ENVOYEE EN ARGUMENT);LOGRE SI LOGIQUE;
C IOBRE POUR TOUT AUTRE TYPE
      IMPLICIT INTEGER(I-N)
-INC PPARAM
-INC CCNOYAU
-INC CCOPTIO
-INC SMTABLE
-INC SMCOORD
-INC CCASSIS
      external long
      CHARACTER*(*) TAPIND,TYPOBJ,CHARIN,CHARRE
      REAL*8 XVALIN,XVALRE
      LOGICAL LOGRE,LOGIN
C character*72 motass
      logical iloremp,lomisa,LOLO
      CHARACTER*(8) CHARA,TYPIND,CHARTP
      character*(LOCHAI) charic
      nth=0
      ith=oothrd
      if (nbesc.ne.0) nth=oothrd
      call poscha(tapind,itypin)
      TYPIND=TAPIND
      CHARA=TYPOBJ
      IOBRE=0
      IF(CHARA.EQ.'        ') THEN
         IF(LEN(TYPOBJ).LT.8) THEN
         CALL ERREUR(5)
        if (iesc.eq.0.or.ith.ne.0) segdes mtable
         RETURN
         ENDIF
      ENDIF
      SEGACT MTABLE
      if(nbesc.ne.0) segact ipiloc
      iesc=0
          if (mlotab.ge.1) then
          if (mtabtv(1)(1:8).eq.'MOT     ') then
           IP=MTABIV(1)
           ID=IPCHAR(IP)
           IFI=IPCHAR(IP+1)
           CHARTP=ICHARA(ID:IFI-1)
           if (chartp.eq.'ESCLAVE ') iesc=1
          endif
          endif
      IN = MLOTAB
      IF(IN.EQ.0.AND.CHARA.NE.'        ') GO TO 1000
      IF(IN.EQ.0) then
        if(nbesc.ne.0) SEGDES,IPILOC
        if (iesc.eq.0.or.ith.ne.0) segdes mtable
        RETURN
      endif
      IF (TYPIND.EQ.'ENTIER  ') then
       IA=1
      ELSEIF(TYPIND.EQ.'FLOTTANT') then
       IA=2
      ELSEIF(TYPIND.EQ.'MOT     ') then
       IA=3
      ELSEIF(TYPIND.EQ.'LOGIQUE ') then
       IA=5
      ELSEIF(TYPIND.EQ.'METHODE ') then
       IA=3
      else
       IA=4
      endif
      IF(IA.EQ.3) THEN
       IL=LONG(CHARIN)
       CHARIC=CHARIN(1:il)
       call poscha(charic,ichari)
      endif
      DO 1 I=1,IN
      if (ia.eq.3) then
        if (mtabii(i).eq.ichari) then
C ne pas mettre chartp our ne pas que l'optimiseur le sorte du test
          IF(mtabti(i)(1:8).NE.TYPIND ) GO TO 1
          goto 20
        endif
      endif
      chartp=mtabti(i)(1:8)
      IF(chartp.NE.TYPIND ) GO TO 1
       GO TO (11,12,13,14,15),IA
   11 CONTINUE
        IF(MTABII(I).NE.IVALIN) GO TO 1
        GOTO 20
   12 CONTINUE
        IF(RMTABI(I).NE.XVALIN ) GO TO 1
        GO TO 20
   15 CONTINUE
        if(nbesc.ne.0) segact ipiloc
        IF(IPLOGI(MTABII(I)).NEQV.LOGIN ) GO TO 1
        GO TO 20
   14 CONTINUE
        IF(MTABII(I).NE.IOBIN) GO TO 1
        GOTO 20
   13 CONTINUE
   1 CONTINUE
C L'INDICE N'EXISTE PAS
1000 IF(CHARA.NE.'        ') THEN
        IF ( TYPIND.EQ.'FLOTTANT') THEN
           REAERR(1)= XVALIN
           CALL ERREUR ( 534)
        ELSEIF (TYPIND.EQ.'MOT     ') THEN
C WRITE(6,FMT='(A40)') CHARIN
           IOL=LEN(CHARIN)
           MOTERR=CHARIN
           IF(IOL.GT.8) MOTERR(9:11) = '...'
           CALL ERREUR (535)
        ELSE
           MOTERR(1:8) = TYPIND
           INTERR(1)= IOBIN
           IF(TYPIND.EQ.'ENTIER  ') INTERR(1) = IVALIN
           CALL ERREUR (171)
        ENDIF
C CALL ERREUR (314)
C WRITE(6,FMT='('' INDICE EXISTE PAS '') ')
C WRITE(6,FMT='('' TAPIND '',A8) ')TAPIND
C WRITE(6,FMT='('' CHARIN '',A8) ')CHARIN
C WRITE(6,FMT='('' CHARA  '',A8) ')CHARA
C WRITE(6,FMT='('' TYPIND '',A8) ')TYPIND
      ENDIF
      if(nbesc.ne.0) SEGDES,IPILOC
      if (iesc.eq.0..or.ith.ne.0) segdes mtable
      RETURN
C ON A TROUVE L'INDICE
  20 CONTINUE
      if(nbesc.ne.0) SEGDES,IPILOC
      TYPIND =MTABTV(I)(1:8)
C decodage des objets esclaves si necessaire
      if (typind.eq.'ESCLAVE ') then
        LOMISA = .FALSE.
        if (.not.lodesl.or.nth.ne.0) lomisa =.true.
        IF ( LOMISA ) THEN
          call oooeta(mcoord,ieta,imod)
          if (ieta.eq.1) segdes mcoord
          mesres = mtabiv(i)
          SEGACT MESRES
          if (.not.loremp) then
  10 continue
            segdes mesres*record
            SEGACT MESRES*(ECR=1,MOD)
            if (.not.loremp) then
              write(6,*) ' loremp pas vrai dans acctab '
              goto 10
            endif
          endif
          if (ieta.eq.1)segact mcoord
C call tabesc(mtable,i,mesres)
C segact mtable
          TYPOBJ=esrety
          IF (TYPOBJ(1:8) .EQ. 'LOGIQUE ') THEN
            LOGRE =esrelo
          ELSEIF (TYPOBJ(1:8) .EQ. 'ENTIER  ') THEN
            IVALRE=esreva
          ELSEIF (TYPOBJ(1:8) .EQ. 'MOT     ') THEN
            CHARRE=esrech
          ELSEIF (TYPOBJ(1:8) .EQ. 'FLOTTANT') THEN
            XVALRE=esrere
          ELSE
            IOBRE =esreva
          ENDIF
          segdes mesres
          if(nbesc.ne.0) SEGDES,IPILOC
        if (iesc.eq.0.or.ith.ne.0) segdes mtable
          return
        endif
      endif
      IF(CHARA.NE.'        ') THEN
         IF(TYPIND.NE.CHARA) THEN
             IF(TYPIND.NE.'ENTIER  '.OR.CHARA.NE.'FLOTTANT') THEN
C L'INDICE EXISTE MAIS LE TYPE NE CORRESPOND PAS
               IOL=LEN(CHARIN)
               MOTERR=CHARIN
               IF(IOL.GT.8) MOTERR(9:11) = '...'
               MOTERR(12:20)=CHARA
               CALL ERREUR(627)
        if (iesc.eq.0.or.ith.ne.0) segdes mtable
               RETURN
             ENDIF
          ENDIF
      ELSE
          TYPOBJ=TYPIND
      ENDIF
      if(nbesc.ne.0) segact ipiloc
      IF(TYPIND.EQ.'ENTIER  ') THEN
        IVALRE=MTABIV(I)
        IF(CHARA.EQ.'FLOTTANT' ) XVALRE=IVALRE
      ELSEIF(TYPIND.EQ.'FLOTTANT') THEN
        XVALRE=RMTABV(I)
      ELSEIF(TYPIND.EQ.'MOT     ') THEN
        IP=MTABIV(I)
        ID=IPCHAR(IP)
  
C ... (suite tronquée dans le lot noyau)
```
