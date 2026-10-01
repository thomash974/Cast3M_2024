# Sources ESOPE clés (complément)

## pilot.eso
```fortran
C Cette subroutine decode et fait executer les directives
C elementaires portant sur des objets
C Deux commandes ont un traitement special : CHAINE et MOT
C P. Manigot (le 21/08/85):
C Le "DATA" de "MDIR1" ayant atteint le maximum de 20 lignes,
C il a fallu creer "MDIR2" pour contenir les operateurs numeros
C 180 et suivants.
C il ne faut plus changer "NDIR1", ni allonger "MDIR1":
C il ne faut plus changer "NDIR2", ni allonger "MDIR2":
C c'est MDIR3 que l'on complete et "NDIR3" que l'on incremente, maintenant.
      SUBROUTINE PILOT
      IMPLICIT INTEGER(I-N)
      IMPLICIT real*8 (a-h,o-z)
-INC PPARAM
-INC CCOPTIO
-INC CCASSIS
      REAL*8 XPLTOT
      INTEGER OOOVAL,ittime,ITABS0,ITABSO,ITCPU0
      LOGICAL INITIAL
C external erf
      CHARACTER*4 MEGAL,locpr,locer2,locqr
      CHARACTER*8 TYPRET
      PARAMETER (NDIR3=160)
      PARAMETER (NDIR2=178)
      PARAMETER (NDIR1=179,NDIR1P=NDIR1+1,
     $ NDIR2P=NDIR1+NDIR2+1,NDIR=NDIR1+NDIR2+NDIR3)
      PARAMETER (NBASS=65)
      CHARACTER*4 MDIR(NDIR),MDIR1(NDIR1),MDIR2(NDIR2),MDIR3(NDIR3)
      DIMENSION IAPPEL(NDIR,NBASS),IELAPS(NDIR,NBASS),ICOHCO(NDIR),
     $ NACT(2,NDIR),ittime(4),ITCPU(NDIR,NBASS),
     $ ITEMP1(NDIR,NBASS),ITEMP2(NDIR,NBASS)
      EQUIVALENCE (MDIR(1),MDIR1(1)),(MDIR(NDIR1P),MDIR2(1)),
     $ (MDIR(NDIR2P),MDIR3(1))
C sauvegarde pour permettre des appels successifs a pilot
C inutile dans castem, mais tres utile pour pycastem
      SAVE MDIR
      SAVE IAPPEL,ITEMP1,ITEMP2,IELAPS,ITCPU,ITCPU0,ICOHCO
      SAVE NACT
      SAVE XPLTOT
      SAVE INITIAL
      SAVE ILOCE_MAIN
      SAVE ITABSO,ITABS0
      INTEGER NACTI
      INTEGER NTAACT
      INTEGER MACTIP
      INTEGER MTOTAP
      INTEGER MSEGMP
      INTEGER MACTI
      SAVE NACTI
      SAVE NTAACT
      SAVE MACTIP
      SAVE MTOTAP
      SAVE MSEGMP
      SAVE MACTI
      DATA ILOCE_MAIN/193/
      DATA NBNNPR/0/
      DATA NACTI/0/
      DATA NTAACT/0/
      DATA MACTIP/0/
      DATA MTOTAP/0/
      DATA MSEGMP/0/
      DATA MACTI/0/
      DATA ITABSO/0/
      DATA ITABS0/0/
-INC SMCOORD
      DATA INITIAL/.FALSE./
      DATA MEGAL/'=   '/
      DATA MDIR1/'OPTI','FIN ','BORN','DENS','DROI','LAPL','CERC','MOTA'
     >,'QUEL','INTE','PARA','SOUC','ET  ','POIN','PLUS','MOIN','TRAN',
     > 'ROTA','TRAC','INVE','COTE','ELEM','CONT','DIFF','CHAN','LIST',
     > 'SURF','CONF','INFO','TOUR','HOMO','AFFI','SYME','INCL','ELIM',
     > 'TITR','RACC','TASS','SORT','LIRE','BARY','DALL','ORIE','MANU',
     > 'OUBL','COMP','COUT','PAVE','COMM','NOEU','MOT ','NBEL','NBNO',
     > 'NOTI','FACE','COOR','NORM','TEMP','VOLU','LECT','SAUF','PROG',
     > '+   ','-   ','*   ','/   ','**  ','FLOT','ENTI','LOG ','EXP ',
     > 'DEPL','PSCA','PVEC','PMIX','LIAI','REGL','HOOK','SOLS','RESO',
     > 'DATE','RIGI','BLOQ','DEPI','HOTA','STRU','TEXT','PROJ','VENV',
     > 'ELST','JONC','RECO','MASS','CLST','SIGM','RELA','FORC','MOME',
     > 'VLOC','BASE','DIME','EXTR','VERS','VIBR','MAXI','XTMX','YTMX',
     > '>   ','<   ','>EG ','<EG ','OU  ','EGA ','NON ','NEG ','MULT',
     > 'PJBA','CRIT','DIAG','XTX ','UNIQ','BSIG','DEDA','MAX1','MOTS',
     > 'REPE','QUIT','SI  ','SINO','FINS','IPOL','ABS ','SIN ','COS ',
     > 'ATG ','ENVE','ISOV','DETR','ENLE','REMP','INSE','COLI','TRIA',
     > 'TABL','REDU','SYMT','ANTI','RESU','PRES','EXCO','NOMC','SAUT',
     > 'DEFO','APPU','INVA','PRIN','VMIS','KSIG','SIGN','SUIT','FREN',
     > 'VALP','ORDO','TIRE','REGE','DESS','AMOR','CHAR','COUL','CHPO',
     > 'AFCO','EVOL','ORTH','THET','COMB','DEVE','VECT','PICA','CAPI'/
      DATA MDIR2/'COPI','DIMN','SAUV','REST','CARA','MATE','GENE',
     > 'CAPA','ELFE','JACO','PLAS','GREE','MODE','....','FINP','XTY ',
     > 'DEBP','KTAN','FORM','MESS','NNOR','CUBP','CUBT','CER3','FDT ',
     > 'SEIS','ENER','EPSI','INTG','COUR','REAC','SUPE','ZERO','DEPB',
     > 'EXCI','KP  ','ACTI','ELAS','OPTO','ERRE','CONG','LUMP','OBTE',
     > 'VARI','MODI','MASQ','EXIS','MINI','GRAD','ENSE','IFRE','DFOU',
     > 'SIGS','MAPP','SOMM','BRUI','RTEN','DSPR','TFR ','DYNC','TOTE',
     > 'GRAF','TRES','TYPE','OSCI','SPO ','INDE','REMA','ENUM','CHSP',
     > 'TAGR','PERM','CABL','FOFI','WORK','QULX','DEBI','DIST','....',
     > 'CMOY','COMT','COND','FLUX','GAMM','....','RIMP','FILT','TFRI',
     > 'CONC','ITER','ACQU','SOUR','CONV','ACOH','PSMO','ASIH','ECOU',
     > 'MENA','SYNT','ARGU','ATAH','DYNE','....','FONC','RESP','PLAC',
     > '....','VALE','PROI','EXCE','ARET','CALP','INDI','ACT3','BIOT',
     > 'DEDU','CONN','NLOC','CHAI','COSI','CVOL','DIAD','HANN','INSI',
     > 'LSQF','LTL ','PERT','PRNS','PSRS','SIAR','SPON','VISA','CNEQ',
     > 'CCON','MESU','PILE','SIMP','UTIL','MENU','COSH','SINH','TANH',
     > 'DEG3','AIDE','RACP','REFE','BESS','KSOF','VERI','NSKE','KMAB',
     > 'NOEL','DOMA','FPU ','....','GMV ','EQPR','EQEX','VIBC','AVCT',
     > 'KDIA','KMTP','KMF ','MDIA','DFDT','TCRR','TCNM','SQTP','SOMT',
     > 'NLIN','CMCT','KCHT','LAPN','RAFT','KLOP','KRES','CSON','FIMP'/
      DATA MDIR3/'NUAG','WEIP','KHIS','KOPS','FSUR','FLAM','ELNO',
     > 'DBIT','NS  ','TOIM','FIMP','KMBT','KBBT','DUDW','FROT','TSCA',
     > 'KONV','KCHA','MHYB','MATP','HDEB','HVIT','HYBP','SMTP','DIVU',
     > 'MOCU','CHAU','TAIL','ERF ','SENS','IMPO','DANS','IMPF','NTAB',
     > 'FRON','FUIT','EPTH','FPT ','KFPT','FPA ','KFPA','ECHI','QOND',
     > 'KPRO','FFOR','RAYE','RAYN','VSUR','TRAJ','AJU1','AJU2','FRIG',
     > 'EXCF','NOMM','PREC','ERFC','ONDE','CFL ','DEDO','DCOV','PARC',
     > 'POLA','CHI1','CHI2','PENT','PRET','METH','XXT ','CBLO','GENJ',
     > 'ZLEG','MESM','FION','NEUT','LOGK','COAC','RESI','MUTU','SORE',
     > 'DIRI','LIGN','OBJE','DEBM','FINM','HERI','DECO','EXTE','DMMU',
     > 'DMTD','BMTD','SSCH','MREM','ASSI','FISS','PRIM','ANNU','PROB',
     > 'SAIS','CHOI','DETO','PART','CLMI','PMAT','EXCP','PROP','PHAJ',
     > 'ALEA','GNFL','MPRO','SSTE','ADVE','BGMO','ECFE','COUP','VERM',
     > 'DFER','GYRO','CORI','KENT','FANT','ITRC','RETO','IJET','IMPE',
     > 'MOCA','LEVM','RAVC','IDLI','RAFF','CFND','ADET','PSIP','ACOS',
     > 'ASIN','TAN ','TRIE','GANE','HIST','ETG ','OTER','XFEM','RFCO',
     > 'VIDE','VORO','PRRA','POSI','MISE','MISL','COLL','POD ','FATI',
     > 'ANNO','MIXE','MFIL','PROL','EXCC','MPMA','JPMA','JPMM','RAIN'/
      ICOHCO(1)=-1
      LDESCR = 200000
C initialisation de lotesc
      lotesc=.false.
      ith=0
      irt=0
      ith=oothrd
      if (ith.ne.0) lotesc=.true.
      ILOCE=0
C initialisation de l'horodatage (Valeur UNIQUE par THREAD)
      IHORO = ith
      IF(.NOT.INITIAL) then
         if(ith.ne.0) then
C dans castem 2014
            WRITE(IOIMP,*) 'erreur dans l initialisation de PILOT'
            CALL ERREUR(5)
         endif
C initialisation des tableaux de l'operateur TEMP
C Enregistrement de l'heure absolue par thread
      ittime(1) = 0
      ittime(2) = 0
      ittime(3) = 0
      ittime(4) = 0
      call timespv(ittime,oothrd)
      ITABS0 = ittime(1)+ittime(2)
      ITABSO = ittime(1)+ittime(2)
      ITCPU0 = ittime(3)+ittime(4)
C INTERT=0
      DO 25 II=1,NDIR
        DO J=1,NBASS
          IAPPEL(II,J) = 0
          IELAPS(II,J) = 0
          ITEMP1(II,J) = ittime(1)+ittime(2)
          ITCPU (II,J) = 0
          ITEMP2(II,J) = 0
        ENDDO
        NACT(1,II)=0
        NACT(2,II)=0
 25 CONTINUE
         NACTI = OOOVAL(2,3)
         NTAACT = OOOVAL(3,3)
C initialisations pour le menage automatique
         MACTIP = OOOVAL(3,3)
         MTOTAP = OOOVAL(3,1)
         MSEGMP = OOOVAL(2,1)
         MACTI = OOOVAL(1,1)
C fin de l'initialisation
         INITIAL=.TRUE.
      endif
C place totale disponible
      XPLTOT=(1.D0*OOOVAL(1,3) * OOOVAL(1,4))/2.D0+OOOVAL(1,1)
      IPLTOT=INT(MIN(XPLTOT,2.D9))
      MTOTA=IPLTOT
C CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
C debut de la boucle sur les operateurs
C CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
C SG 2018/11/07 : concernant les points de rebranchement :
C - Le point de rebranchement 1 est le point de rebranchement usuel
C qui permet de continuer a lire des operateurs sur la ligne en
C cours
C - Le point de rebranchement 2 concerne les operateurs ou on ne
C veut plus lire d'operateur apres : COMM, SI, SINON, FINSI
C - Le point de rebranchement 30 concerne les operateurs qui
C renvoient une chaine de caracteres que l'on NE VEUT PAS
C interpreter comme un nom d'operateur : MOT, EXTR, TYPE,
C ACQU 'BRUT', VALE, CHAINE, CHAN 'MAJU'
C Aussi : LIST, EXTR
   1 CONTINUE
C if (ith.eq.0) lodesl=.true.
      if (ith.eq.0) call setass(1)
C horodatage
      ihoro=ihoro+NBTHRS+1
      IF (ihoro .LT. 0) ihoro=ith
      call ooohor(ihoro)
      jerr=MAX(IERR,IERGLB)
      IF (jerr.EQ.623) THEN
       IERR =0
       IERGLB=0
       CALL ERREUR(623)
      ENDIF
      locpr=locerr
      LOCERR=MEGAL
      locer2=megal
      CALL MESLIR(-219)
C Calcul du temps passe dans l'operateur
      IF (ILOCE .NE. 0) THEN
        call timespv(ittime,oothrd)
C Temps Horloge
        IKT = (ittime(1) + ittime(2)) - ITEMP1(ILOCE,ITH+1)
        IAPPEL(ILOCE,ITH+1)= IAPPEL(ILOCE,ITH+1) + 1
        IELAPS(ILOCE,ITH+1)= IELAPS(ILOCE,ITH+1) + IKT
C Temps CPU
        IKT = (ittime(3) + ittime(4)) - ITEMP2(ILOCE,ITH+1)
        ITCPU (ILOCE,ITH+1)= ITCPU (ILOCE,ITH+1) + IKT
C Nombre de Segments ouverts et la taille correspondante
        NACT(1,ILOCE)=NACT(1,ILOCE) + OOOVAL(2,3) - NACTI
        NACT(2,ILOCE)=NACT(2,ILOCE) + OOOVAL(3,3) - NTAACT
      ENDIF
C Test pour appel d'une procedure ou d'une methode
      CALL LIROBJ('PROCEDUR',IRET,0,IRETOU)
      IF(IRETOU.NE.0) THEN
C on fixe ILOCE=193 a l'operateur '....' dans le cas des PROCEDURES
        ILOCE=193
C Remplissage des tableau de l'operateur TEMPS
C CALL GIBTEM(XKT)
        call timespv(ittime,oothrd)
        ITEMP1(ILOCE,ITH+1)=ittime(1) + ittime(2)
        ITEMP2(ILOCE,ITH+1)=ittime(3) + ittime(4)
        NACTI = OOOVAL(2,3)
        NTAACT = OOOVAL(3,3)
        CALL REFUS
C gestion de la procedure
        CALL PROCED
        if (ith.eq.0) call setass(0)
        GOTO 1
      ENDIF
C if (ith.ne.0.and.lodesl) WRITE(IOIMP,*) ' pilot 1 lodesl '
      CALL LIRMO2(MDIR,NDIR,II,0,ICOHCO)
      ILOCE = II
C if (ith.ne.0.and.lodesl) WRITE(IOIMP,*) ' pilot 2 lodesl '
      IF (II.NE.0) GOTO 100
      if (ith.eq.0) call setass(0)
  30 CONTINUE
      if (ith.eq.0) call setass(1)
C option verif ( opti veri 1 )
       IF (IOSPI.NE.0) WRITE (IOIMP,90001)
90001 FORMAT(' *',' ***** ***** FIN D''INSTRUCTION ELEMENTAIRE','/')
C ATTENTION : Il manque des decomptes des appels a POIN s'il est appele de maniere implicite
C on fixe ILOCE=14 a l'operateur 'POIN' dans le cas de l'appel implicite a CREPOI
C ILOCE=14
C Remplissage des tableau de l'operateur TEMPS
C CALL GIBTEM(XKT)
C call timespv(ittime,oothrd)
C ITEMP1(ILOCE,ITH+1)=ittime(1) + ittime(2)
C ITEMP2(ILOCE,ITH+1)=ittime(3) + ittime(4)
C NACTI = OOOVAL(2,3)
C NTAACT = OOOVAL(3,3)
C creation de point si il y a deux reels dans la pile intermediaire
      CALL CREPOI
C if (ith.ne.0.and.lodesl) WRITE(IOIMP,*) ' pilot 3 lodesl '
C synchronisation de nbpts si possible
      call oooeta(mcoord,ieta,imod)
      if (ieta.eq.1) then
       nbpts=xcoor(/1)/(idim+1)
       if (iimpi.ne.0) then
        nbnnac = nbpts
        if (nbnnpr.ne.nbnnac) then
          locqr = locerr
          WRITE(IOIMP,*)'pilot noeuds avant: ',nbnnpr,' apres: ',
     & nbnnac,' dans: ',locqr
          nbnnpr = nbnnac
        endif
       endif
      if (nbesc.ne.0) segdes mcoord
      endif
C call ooosur(mcoord) pour debugger
C if (ith.eq.0) call setass(0)
C cas esclave
      if (LOTESC) then
C CCCCCC if (imescl.ne.0) then
         if (ith.eq.0) call setass(0)
         call nouins2
C if (ith.ne.0.and.lodesl) WRITE(IOIMP,*) ' pilot 4 lodesl '
         GOTO 1
      endif
C gestion de la nouvelle instruction
      CALL NOUINS
C write(6,*) ' ierr lodesl dans pilot ',ierr,lodesl
      if (ith .eq. 0.and.lodesl) call setass(0)
   2 continue
      irt =0
      imena=1
      if(lupara .ne. 0) call chkesc(irt,imena)
      if(irt.eq.1) GOTO 550
C menage automatique (osons)
      if (ith.eq.0.and.imena.eq.1) then
C autres criteres de menage :
        IFMEN=0
C + de 20% de la memoire active depuis la derniere fois
        MACTIC=OOOVAL(3,3)
        IF (MACTIC-MACTIP.gt.MACTI*0.2) IFMEN=1
C + de 65% de la memoire totale depuis la derniere fois
        MTOTAC=OOOVAL(3,1)
        IF (MTOTAC-MTOTAP.gt.MTOTA*0.65) IFMEN=2
C + de 50% de la memoire active en memoire totale depuis la derniere fois
        IF (MTOTAC-MTOTAP.gt.MACTI*0.5) IFMEN=3
C + de 10% du nombre total de segments depuis la derniere fois
        MSEGMC=OOOVAL(2,1)
C write(6,*) ' nb segents ',msegmp,' nb descr ',ldescr
C IF (MSEGMC-MSEGMP.gt.32000*max(1,nbescr)) IFMEN=4
        IF (MSEGMC-MSEGMP.gt.LDESCR/10 ) IFMEN=4
C if (ifmen.eq.4) write(6,*) ' ldescr ',ldescr
        IF (IFMEN.NE.0) THEN
           ILOCE=277
C Remplissage des tableau de l'operateur TEMPS
C CALL GIBTEM(XKT)
           call timespv(ittime,oothrd)
           ITEMP1(ILOCE,ITH+1)=ittime(1) + ittime(2)
           ITEMP2(ILOCE,ITH+1)=ittime(3) + ittime(4)
           NACTI = OOOVAL(2,3)
           NTAACT = OOOVAL(3,3)
           iautom=1
           CALL MENAGE (iautom)
           LDESCR=max(OOOVAL(2,11),ldescr)
           if( iautom.eq.1) then
             MACTIP=OOOVAL(3,3)
             MTOTAP=OOOVAL(3,1)
             MSEGMP=OOOVAL(2,1)
             interr(1)=mactic-mactip
             interr(2)=mtotac-mtotap
             interr(3)=msegmc-msegmp
             interr(4)=ifmen
             moterr(1:4)=locpr
             call erreur(862)
           endif
        endif
      ENDIF
      GOTO 1
 100 continue
      LOCERR=MDIR(II)
      LOCER2=MDIR(II)
C pour etre sur que mcoord est actif( pv)
C Remplissage des tableau de l'operateur TEMPS
       IF(II .NE. 0 ) THEN
C CALL GIBTEM(XKT)
         call timespv(ittime,oothrd)
         ITEMP1(II,ITH+1)=ittime(1) + ittime(2)
         ITEMP2(II,ITH+1)=ittime(3) + ittime(4)
         NACTI = OOOVAL(2,3)
         NTAACT = OOOVAL(3,3)
       ENDIF
C option verif
       IF (IOSPI.NE.0) WRITE (IOIMP,90000) ith,locer2
90000 FORMAT(' *',' Assistant ',i2, ' Operateur appele : ',A4)
C DMY-WIN32 CALL SCROLLTEXT(6)
C branchement conditionnel vers les operateurs
C if (ith.eq.0) lodesl=.false.
      if (ith.eq.0) call setass(0)
C IF(IHORO .EQ. 156)THEN
C PRINT *,'OPERATEUR POUR HORODATAGE',IHORO,MDIR(II),oothrd,NBTHRS
C ENDIF
      IF (II.LE.100)
     >GOTO (101,102,103,104,105,106,107,108,109,110,111,112,113,114,
     > 115,116,117,118,119,120,121,122,123,124,125,126,127,128,129,
     > 130,131,132,133,134,135,136,137,138,139,140,141,142,143,144,
     > 145,146,147,148,149,150,151,152,153,154,155,156,157,158,159,
     > 160,161,162,163,164,165,166,167,168,169,170,171,172,173,174,
     > 175,176,177,178,179,180,181,182,183,184,185,186,187,188,189,
     > 190,191,192,193,194,195,196,197,198,199,200),II
      IF (II.LE.200)
     >GOTO (201,202,203,204,205,206,207,208,209,210,211,212,213,214,
     > 215,216,217,218,219,220,221,222,223,224,225,226,227,228,229,
     > 230,231,232,233,234,235,236,237,238,239,240,241,242,243,244,
     > 245,246,247,248,249,250,251,252,253,254,255,256,257,258,259,
     > 260,261,262,263,264,265,266,267,268,269,270,271,272,273,274,
     > 275,276,277,278,279,280,281,282,283,284,285,286,287,288,289,
     > 290,291,292,293,294,295,296,297,298,299,300),II-100
      IF (II.LE.300)
     >GOTO (301,302,303,304,305,306,307,308,309,310,311,312,313,314,
     > 315,316,317,318,319,320,321,322,323,324,325,326,327,328,329,
     > 330,331,332,333,334,335,336,337,338,339,340,341,342,343,344,
     > 345,346,347,348,349,350,351,352,353,354,355,356,357,358,359,
     > 360,361,362,363,364,365,366,367,368,369,370,371,372,373,374,
     > 375,376,377,378,379,380,381,382,383,384,385,386,387,388,389,
     > 390,391,392,393,394,395,396,397,398,399,400),II-200
      IF (II.LE.400)
     >GOTO (401,402,403,404,405,406,407,408,409,410,411,412,413,414,
     > 415,416,417,418,419,420,421,422,423,424,425,426,427,428,429,
     > 430,431,432,433,434,435,436,437,438,439,440,441,442,443,444,
     > 445,446,447,448,449,450,451,452,453,454,455,456,457,458,459,
     > 460,461,462,463,464,465,466,467,468,469,470,471,472,473,474,
     > 475,476,477,478,479,480,481,482,483,484,485,486,487,488,489,
     > 490,491,492,493,494,495,496,497,498,499,500),II-300
      IF (II.LE.500)
     >GOTO (501,502,503,504,505,506,507,508,509,510,511,512,513,514,
     > 515,516,517,518,519,520,521,522,523,524,525,526,527,528,529,
     > 530,531,532,533,534,535,536,537,538,539,540,541,542,543,544,
     > 545,546,547,548,549,550,551,552,553,554,555,556,557,558,559,
     > 560,561,562,563,564,565,566,567,568,569,570,571,572,573,574,
     > 575,576,577,578,579,580,581,582,583,584,585,586,587,588,589,
     > 590,591,592,593,594,595,596,597,598,599,600),II-400
      IF (II.LE.600)
     >GOTO (601,602,603,604,605,606,607,608,609,610,611,612,613,614,
     > 615,616,617),II-500
C on a lu option
101 CALL OPTION(1)
      GOTO 1
102 CALL FIN
      irt =0
      imena=1
      if(lupara.ne.0) call chkesc(irt,imena)
      if(irt .eq. 1) GOTO 550
      GOTO 1
103 CALL BORNER
      GOTO 1
104 CALL SUBDEN
      GOTO 1
105 CONTINUE
107 CONTINUE
111 CONTINUE
      IOPTG=II-4
C important ioptg est le numero du type de ligne a engendrer
C le tenir a jour et voir comment on le recupere dans ligne
      DEN1 = 0.
      DEN2 = 0.
      INBR = 0
      CALL LIGNE(IOPTG,1,DEN1,DEN2,INBR)
      GOTO 1
106 CALL LAPLAC
      GOTO 1
108 CALL MOTAN
      GOTO 1
109 CALL QUELQU
      GOTO 1
110 CALL INTERS
      GOTO 1
112 CALL SOUCI
      GOTO 1
113 CALL PRFUSE
      GOTO 1
114 CALL POIEXT
      GOTO 1
115 CONTINUE
116 IOPTG=II-14
      CALL PROPER(IOPTG)
      GOTO 1
117 CONTINUE
118 IOPTG=II-16
      CALL PRTRAN(IOPTG)
      GOTO 1
119 CALL PRTRAC
      GOTO 1
120 CALL PRINVE
      GOTO 1
121 CALL PRCOTE
      GOTO 1
122 CALL PREXTR
      GOTO 1
123 CALL PRCONT
      GOTO 1
124 CALL PRDIFF
      GOTO 1
C SG 2018/11/07 : on rebranche sur 30 pour CHAN MAJU sinon il y a
C interpretation du contenu de la chaine lorsque le resultat est un
C nom d'operateur
 125 CALL PRCHAN
      CALL QUETYP(TYPRET,0,IRETOU)
      IF( IRETOU.NE.0) THEN
         IF(TYPRET.EQ.'MOT     ') THEN
            GOTO 30
         ENDIF
      ENDIF
      GOTO 1
126 CALL PRLIST
      GOTO 30
127 CALL PRSURF
      GOTO 1
128 CALL CONFON
      GOTO 1
129 CALL INFORM
      GOTO 1
130 CALL TOURNE
      GOTO 1
131 CALL HOMOTH
      GOTO 1
132 CALL AFFINI
      GOTO 1
133 CALL SYMETR
      GOTO 1
134 CALL INCLUS
      GOTO 1
135 CALL PRELIM(0)
      GOTO 1
136 CALL LTITRE
      GOTO 1
137 CALL PRRACC
      GOTO 1
138 CALL PRTASS
      GOTO 1
139 CALL PRSORT
      GOTO 1
140 IONIVO=IONIVE
      CALL LIREFI
C on remet le niveau a sa valeur anterieure
      IONIVE=IONIVO
      GOTO 1
141 CALL BARYCE
      GOTO 1
142 CALL PRDALL
      GOTO 1
143 CALL PRORIE
      GOTO 1
144 CALL MANUEL
      GOTO 1
145 CALL OUBLIE
      GOTO 1
146 CALL COML
      GOTO 1
147 CALL COUTUR
      GOTO 1
148 CALL PRPAVE
      GOTO 1
149 CALL COMMEN
      GOTO 2
150 CALL NOEUD
      GOTO 1
151 CALL MOTSUB
      GOTO 30
152 CALL NBEL
      GOTO 1
153 CALL NBNO
      GOTO 1
154 CALL NOTICE(MDIR,NDIR)
      GOTO 1
155 CALL EXFACE
      GOTO 1
156 CALL EXCOOR
      GOTO 1
157 CALL CNORM
      GOTO 1
158 CALL TEMPOR(ITABS0,ITABSO,MDIR,IAPPEL,IELAPS,ITCPU,ITCPU0,
     & NACT,NDIR,ith)
      GOTO 1
159 CALL VOLUME
      GOTO 1
160 CALL LECTUR
      GOTO 1
161 CALL SAUF
      GOTO 1
162 CALL PROG
      GOTO 1
163 CALL OPERAD
      GOTO 1
164 CALL OPERSO
      GOTO 1
165 CALL OPERMU
      GOTO 1
166 CALL OPERDI
      GOTO 1
167 CALL OPERPU
      GOTO 1
168 CALL OPERFL
      GOTO 1
169 CALL OPERIN
      GOTO 1
170 CALL OPOBJE(13)
C 13 -> LOGARITHME NATUREL (LOG)
      GOTO 1
171 CALL OPOBJE(12)
C 12 -> EXP
      GOTO 1
172 CALL DEPLAC
      GOTO 1
173 CALL PSCALA
      GOTO 1
174 CALL PVECT
      GOTO 1
175 CALL PMIXT
      GOTO 1
176 CALL PRLIAI
      GOTO 1
177 CALL REGLE
      GOTO 1
178 CALL HOOKE
      GOTO 1
179 CALL SOLS
      GOTO 1
180 CALL RESOU
      GOTO 1
181 call DATE
      GOTO 1
182 CALL RIGI
      GOTO 1
183 CALL BLOQUE
      GOTO 1
184 CALL DEPIMP
      GOTO 1
185 CALL HOTAN
      GOTO 1
186 CALL STRUCT
      GOTO 1
187 CALL TEXTDE
      GOTO 1
188 CALL PROOBJ
      GOTO 1
189 CALL VENV
      GOTO 1
190 CALL ELSTRU
      GOTO 1
191 CALL JONCT
      GOTO 1
192 CALL RECOMB
      GOTO 1
193 CALL MASSE(0)
      GOTO 1
194 CALL CLSTRU
      GOTO 1
195 CALL SIGMA
      GOTO 1
196 CALL RELA
      GOTO 1
197 CONTINUE
      CALL FORCE(1)
      GOTO 1
198 CONTINUE
      CALL FORCE(2)
      GOTO 1
199 CONTINUE
      CALL VLOC
      GOTO 1
200 CALL BASEMD
      GOTO 1
201 CALL DIMENS
      GOTO 1
202 CALL EXTRAI
      GOTO 30
203 CALL VERSEN
      GOTO 1
204 CALL VIBRAT
      GOTO 1
205 JMIL=1
      CALL MAXIMU(JMIL)
      GOTO 1
206 CALL PRXTMX
      GOTO 1
207 CALL PRYTMX
      GOTO 1
208 CALL GRAND
      GOTO 1
209 CALL PETIT
      GOTO 1
210 CALL GRAEGA
      GOTO 1
211 CALL PETEGA
      GOTO 1
212 CALL OU
      GOTO 1
213 CALL EGA
      GOTO 1
214 CALL NON
      GOTO 1
215 CALL NEG
      GOTO 1
216 CALL MULT
      GOTO 1
217 CALL PJBA
      GOTO 1
218 CALL CRIT
      GOTO 1
219 CALL DIAGNE
      GOTO 1
220 CALL XTX
      GOTO 1
221 CALL UNIQUE
C Ancien appel a l'operateur CHOC devenu obsolete
      GOTO 1
222 CALL BSIGMA
      GOTO 1
223 CALL DEDA
      GOTO 1
224 CALL NORMAX
      GOTO 1
225 CALL MOTS
      GOTO 1
226 CALL REPETE(0)
      GOTO 1
227 CALL QUITTE
      GOTO 1
228 CALL SI
      GOTO 2
229 CALL SINON
      GOTO 2
230 CALL FINSI
      GOTO 2
231 CALL INTERP
      GOTO 1
232 CALL OPOBJE(14)
C 14 -> VALEUR ABSOLUE (ABS)
      GOTO 1
233 CALL OPOBJE(7)
C 7 -> SINUS (SIN)
      GOTO 1
234 CALL OPOBJE(6)
C 6 -> COSINUS (COS)
      GOTO 1
235 CALL OPOBJE(11)
C 11 -> ARCTAN (ATG)
      GOTO 1
236 CALL ENVELO
      GOTO 1
237 CONTINUE
      CALL ISOVAL
      GOTO 1
238 CALL DETRUI
      GOTO 1
239 CALL ENLEVE
      GOTO 1
240 CALL REMPLA
      GOTO 1
241 CALL INSERE
      GOTO 1
242 CALL COLI
      GOTO 1
243 CALL TRIA
      GOTO 1
244 CALL TABLE
      GOTO 1
245 CALL REDU
      GOTO 1
246 CONTINUE
      CALL SYMTRI(0)
      GOTO 1
247 CONTINUE
      CALL SYMTRI(1)
      GOTO 1
248 CALL RESU
      GOTO 1
249 CALL PRESSI
      GOTO 1
250 CALL EXCOMP
      GOTO 1
251 CALL NOMC
      GOTO 1
252 CALL SAUTER
      GOTO 1
253 CALL DEFO
      GOTO 1
254 CALL APPUI(1)
      GOTO 1
255 CALL INVARI
      GOTO 1
256 CALL PRINCI
      GOTO 1
257 CALL VMISES
      GOTO 1
258 CALL KSIGMA
      GOTO 1
259 CALL OPOBJE(23)
C 23 -> SIGN a un argument
      GOTO 1
260 CALL SUITE
      GOTO 1
261 CALL FRENET
      GOTO 1
262 CALL VALPRO
      GOTO 1
263 CALL ORDONN
      GOTO 1
264 CALL TIRE
      GOTO 1
265 CALL PRREGE
      GOTO 1
266 CALL DESSIN
      GOTO 1
267 CALL AMOR
      GOTO 1
268 CALL CHARGE
      GOTO 1
269 CALL COLOR
      GOTO 1
270 CALL CHPOIN
      GOTO 1
271 CALL AFCOUL
      GOTO 1
272 CALL EVOL
      GOTO 1
273 CALL ORTHOG
      GOTO 1
274 CALL THETA
      GOTO 1
275 CALL COMBTA
      GOTO 1
276 CALL DEVERS
      GOTO 1
277 CALL VECTE
      GOTO 1
278 CALL PIOCAU(0)
      GOTO 1
279 CALL PIOCAU(1)
      GOTO 1
280 CALL COPIER
      GOTO 1
281 CALL DIMNOY
      GOTO 1
282 CALL SAUV
      GOTO 1
283 IONIVO=IONIVE
      CALL REST
C on remet le niveau a sa valeur anterieure
      IONIVE=IONIVO
      GOTO 1
284 CALL CARAC
      GOTO 1
285 CALL MATER
      GOTO 1
286 CALL GENERA
      GOTO 1
287 CALL CAPA
      GOTO 1
288 CALL ELFE
      GOTO 1
289 CALL JACO
      GOTO 1
290 continue
C Appel a l'operateur PLAS (a debrancher)
      call ecoule
      GOTO 1
291 CALL GREEN
      GOTO 1
292 CALL MODELI
      GOTO 1
293 CALL PROCED
      GOTO 1
541 CONTINUE
294 CALL FINPRO
      GOTO 1
295 CALL XTY
      GOTO 1
540 CONTINUE
296 IOPRME=1
      IF(II.GT.400) IOPRME=2
      CALL MAPR(IOPRME)
      GOTO 1
297 CALL KTANGE
      GOTO 1
298 CALL FORM
      GOTO 1
299 CALL MESSAG
      GOTO 1
300 CALL NNOR
      GOTO 1
301 II=13
      GOTO 111
302 II=14
      GOTO 111
303 II=15
      GOTO 111
C ::::::::::::::::::::::::::::::::
304 CALL FDT
      GOTO 1
305 CALL SEISME
      GOTO 1
306 CALL ENERGI
      GOTO 1
307 CALL EPSI
      GOTO 1
308 CALL INTGRA
      GOTO 1
309 CALL COURBE
      GOTO 1
310 CALL REACTI
      GOTO 1
311 CALL SUPER
      GOTO 1
312 CALL ZERORO
      GOTO 1
313 CALL DEPB
      GOTO 1
314 CALL EXCITE
      GOTO 1
315 CALL KP
      GOTO 1
316 CALL ACTIVE
      GOTO 1
317 CALL ELASTI
      GOTO 1
318 continue
      CALL PROPTO
      GOTO 1
319 CALL ERRE
      GOTO 1
320 CALL CONGE
      GOTO 1
321 CALL MASSE(1)
      GOTO 1
322 CALL OBTENI
      GOTO 1
323 CALL VARI
      GOTO 1
324 CALL MODI
      GOTO 1
325 CALL MASQ
      GOTO 1
326 CALL EXIS
      GOTO 1
327 JMIL=-1
      CALL MAXIMU(JMIL)
      GOTO 1
328 CALL GRAD
      GOTO 1
329 CALL ENSE
      GOTO 1
330 CALL IFRE
      GOTO 1
331 CALL DFOURI
      GOTO 1
332 CALL SIGSOL
      GOTO 1
333 CALL MAPP
      GOTO 1
334 CALL SOMM
      GOTO 1
335 CALL BRUI
      GOTO 1
336 CALL RTEN
      GOTO 1
C 337 CALL DSPR
337 CALL TFOR(2)
      GOTO 1
338 CALL TFOR(1)
      GOTO 1
339 continue
      CALL DYNC
      GOTO 1
340 CALL TOTEMP
      GOTO 1
341 CALL GRAF
      GOTO 1
342 CALL TRESCA
      GOTO 1
343 CALL TYPE
      GOTO 30
344 CALL OSCI
      GOTO 1
345 CALL SPO
      GOTO 1
346 CALL INDETA
      GOTO 1
347 CALL REMAIL
      GOTO 1
348 CALL ENUMER
      GOTO 1
349 CALL CHSP
      GOTO 1
350 CALL TAGRAD
      GOTO 1
351 CALL PERMEA
      GOTO 1
352 CALL RICABL
      GOTO 1
353 CALL FOFISS
      GOTO 1
354 CALL WORK
      GOTO 1
355 CALL QULX
      GOTO 1
356 CALL DEBIT
      GOTO 1
357 CALL PRDIST
      GOTO 1
358 continue
C Appel a l'operateur FENE(TRE) debranche a ce jour
C call fenetr
      GOTO 1
359 CALL CHOMOY
      GOTO 1
360 CALL COMCHO
      GOTO 1
361 CALL CONDU
      GOTO 1
362 CALL FLUX
      GOTO 1
363 CALL OPOBJE(30)
C 30 -> Fonction GAMMA d'Euler
      GOTO 1
364 continue
C Ancien appel a l'operateur MATR devenu obsolete et redondant avec MATE
      GOTO 1
365 CALL CRIMP
      GOTO 1
366 CALL FILTRE
      GOTO 1
367 CALL TFRINV
      GOTO 1
368 CALL CONCAT
      GOTO 1
369 CALL ITERER
      GOTO 1
370 CALL ACQUER(IBRUT)
      IF (IBRUT.EQ.1) GOTO 30
      GOTO 1
371 CALL CHALEU
      GOTO 1
372 CALL CONVEC
      GOTO 1
373 CALL OPOBJE(20)
C 20 -> ARGCH
      GOTO 1
374 CALL PSMO
      GOTO 1
375 CALL OPOBJE(21)
C 21 -> ARGSH
      GOTO 1
376 continue
C Appel a l'operateur ECOU(LE) (a debrancher)
      call ecoule
      GOTO 1
377 iautom=0
      CALL MENAGE(iautom)
          if(iautom.eq.1) then
           MACTIP=OOOVAL(3,3)
           MTOTAP=OOOVAL(3,1)
           MSEGMP=OOOVAL(2,1)
          endif
      GOTO 1
378 CALL SYNTHE
      GOTO 1
379 CALL ARGU
      GOTO 1
380 CALL OPOBJE(22)
C 22 -> ARGTH
      GOTO 1
381 CALL DYNE
      GOTO 1
382 continue
C Ancien appel a l'operateur CRES(OL) devenu obsolete
      GOTO 1
383 CALL FONCTI
      GOTO 1
384 CALL RESPRO
      GOTO 1
385 CALL PLAC
      GOTO 1
386 continue
C Ancien appel a l'operateur .... devenu obsolete
      GOTO 1
387 CALL OPTION (2)
      GOTO 30
388 CALL PROIET
      GOTO 1
389 CALL EXCELL
      GOTO 1
390 CALL ARETE
      GOTO 1
391 CALL CALP
      GOTO 1
392 CALL INDIC
      GOTO 1
393 CALL ACT3
      GOTO 1
394 CALL BIOSAV
      GOTO 1
395 CALL DEDU(0)
      GOTO 1
396 CALL CONNEC
      GOTO 1
397 CALL NLOCAL
      GOTO 1
398 CALL CHAINE
      GOTO 30
399 CALL COSI
      GOTO 1
400 CALL CVOL
      GOTO 1
401 CALL DIAD
      GOTO 1
402 CALL HANN
      GOTO 1
403 CALL INSI
      GOTO 1
404 CALL LSQF
      GOTO 1
405 CALL LTL
      GOTO 1
406 CALL PERT
      GOTO 1
407 CALL PRNS
      GOTO 1
408 CALL PSRS
      GOTO 1
409 CALL SIAR
      GOTO 1
410 CALL SPON
      GOTO 1
411 CALL PRELIM(1)
      GOTO 1
412 CALL CNEQ
      GOTO 1
413 CALL CCON
      GOTO 1
414 CALL MESU
      GOTO 1
415 CALL PILEPS
      GOTO 1
416 CALL SIMPLE
      GOTO 1
417 CALL UTILIS
      GOTO 1
418 CALL MENUG
      GOTO 1
419 CALL OPOBJE(15)
C 15 -> COSH
      GOTO 1
420 CALL OPOBJE(16)
C 16 -> SINH
      GOTO 1
421 CALL OPOBJE(17)
C 17 -> TANH
      GOTO 1
422 CALL DEG3
      GOTO 1
423 CALL AIDE(MDIR,NDIR)
      GOTO 1
424 CALL RACPOL
      GOTO 1
425 CALL REFE
      GOTO 1
426 CALL BESS
      GOTO 1
427 CALL KSOF
      GOTO 1
428 continue
      CALL VERIFI
      GOTO 1
429 CALL YNSKE
      GOTO 1
430 CALL KMAC(1)
      GOTO 1
431 CALL KNOL
      GOTO 1
432 CALL KDOM
      GOTO 1
433 CALL YFPU
      GOTO 1
434 continue
C Ancien appel a l'operateur .... devenu obsolete
      GOTO 1
435 CALL YGMV
      GOTO 1
436 CALL EQPR
      GOTO 1
437 CALL EQEX
      GOTO 1
438 CALL VIBRAC
      GOTO 1
439 CALL CAAVCT
      GOTO 1
440 CALL CAKIZD
      GOTO 1
441 CALL KMTP
      GOTO 1
442 CALL KMF
      GOTO 1
443 CONTINUE
      CALL YDIAG
      GOTO 1
444 CONTINUE
      CALL YDFDT
      GOTO 1
445 CONTINUE
      CALL TCRR
      GOTO 1
446 CONTINUE
      CALL TCNM
      GOTO 1
447 CONTINUE
      CALL SQTP
      GOTO 1
448 CALL KSOMT
      GOTO 1
449 continue
C CALL KDTB
      CALL PRLIN
      GOTO 1
450 CONTINUE
      CALL CMCT
      GOTO 1
451 CALL KCHT
      GOTO 1
452 CALL YLAPL
      GOTO 1
453 CONTINUE
      CALL RAFT
      GOTO 1
454 CALL KLOP
      GOTO 1
455 CALL KRES
      GOTO 1
456 CONTINUE
      CALL CSON
      GOTO 1
457 CALL YFIMP
      GOTO 1
458 CALL NUAGE
      GOTO 1
459 CALL WEIPAR
      GOTO 1
460 CALL KHIS
      GOTO 1
461 CALL KOPS
      GOTO 1
462 CALL FSUR
      GOTO 1
463 CALL FLAM
      GOTO 1
464 CALL KLNO
      GOTO 1
465 CALL DBIT
      GOTO 1
466 CALL YNS
      GOTO 1
467 CALL YTOIMP
      GOTO 1
468 CALL YFIMP
      GOTO 1
469 CALL KMAC(2)
      GOTO 1
470 CALL KMAC(3)
      GOTO 1
471 CALL YDUDW
      GOTO 1
472 CALL YFROT
      GOTO 1
473 CALL YTSCAL
      GOTO 1
474 CALL KONV
      GOTO 1
475 CALL KCHA
      GOTO 1
476 CALL MHYBR
      GOTO 1
477 CALL MATP
      GOTO 1
478 CALL HDEBIT
      GOTO 1
479 CALL HVIT
      GOTO 1
480 CALL HYBP
      GOTO 1
481 CALL SMTP
      GOTO 1
482 CALL DIVU
      GOTO 1
483 CALL MOCUR
      GOTO 1
484 CALL CHAUSS
      GOTO 1
485 CALL TAILLE
      GOTO 1
486 CALL OPOBJE(18)
C 18 -> ERF
      GOTO 1
487 CALL SENSI0
      GOTO 1
488 CALL IMPOSE
      GOTO 1
489 CALL DANS
      GOTO 1
490 CALL IMPF
      GOTO 1
491 CALL TBMAIN
      GOTO 1
492 CALL FRON1
      GOTO 1
493 CALL FUITE1
      GOTO 1
494 CALL EPTH
      GOTO 1
495 CALL FPT
      GOTO 1
496 CALL KFPT
      GOTO 1
497 CALL FPA
      GOTO 1
498 CALL KFPA
      GOTO 1
499 CALL ECHIMP
      GOTO 1
500 CALL QOND
      GOTO 1
501 CALL KPRO
      GOTO 1
502 CALL PRFORM
      GOTO 1
503 CALL PRRAYE
      GOTO 1
504 CALL RAYN
      GOTO 1
505 CALL VSUR
      GOTO 1
506 CALL TRAJEC
      GOTO 1
507 CALL AJU1
      GOTO 1
508 CALL AJU2
      GOTO 1
509 CALL FRIG
      GOTO 1
510 CALL EXCFRO
      GOTO 1
511 continue
      CALL NOMMER
      GOTO 1
512 CALL PRECO
      GOTO 1
513 CALL OPOBJE(19)
C 19 -> ERFC
      GOTO 1
514 CALL ONDE
      GOTO 1
515 CALL CFL
      GOTO 1
516 CALL DEDOU
      GOTO 1
517 CALL DCOV
      GOTO 1
518 CONTINUE
C parabole approchant un arc de cercle
      II=16
      GOTO 111
519 CALL POLA
      GOTO 1
520 CALL CHIMI1
      GOTO 1
521 CALL CHIMI2
      GOTO 1
522 CALL PENT
      GOTO 1
523 CALL PRET
      GOTO 1
524 CALL METHOD
      GOTO 1
525 CALL XPXTRA
      GOTO 1
526 CALL COMBLO
      GOTO 1
527 CALL GENJOI
      GOTO 1
528 CALL ZLEGEN
      GOTO 1
529 CALL MENISM
      GOTO 1
530 CALL FIONI
      GOTO 1
531 CALL NEUTRE
      GOTO 1
532 CALL LOGK
      GOTO 1
533 CALL COAC
      GOTO 1
534 CALL RESI
      GOTO 1
535 CALL MUTU
      GOTO 1
536 CALL SORE
      GOTO 1
537 CALL DIRICH
      GOTO 1
538 CALL LIGN
      GOTO 1
539 CALL OBJET
      GOTO 1
542 CALL HERITE
      GOTO 1
543 CALL DECO
      GOTO 1
544 CALL EXTERN
      GOTO 1
545 CALL DMMU
      GOTO 1
546 CALL DMTD
      GOTO 1
547 CALL BMTD
      GOTO 1
548 CALL SSCH
      GOTO 1
549 CALL MREM
      GOTO 1
550 CALL ASSIST(irt)
      GOTO 1
551 CALL FISS
      GOTO 1
552 CALL PRIMIT
      GOTO 1
553 CALL ANNULE
      GOTO 1
554 CALL PROB
      GOTO 1
555 CALL SAIS
      GOTO 1
556 CALL CHOI
      GOTO 1
557 CALL DETO
      GOTO 1
558 CALL PART
      GOTO 1
559 CALL CLMI
      GOTO 1
560 CALL BLOPHA
      GOTO 1
561 CALL EXCPHA
      GOTO 1
562 CALL PROPHA
      GOTO 1
563 CALL JEUPHA
      GOTO 1
564 CALL ALEA
      GOTO 1
565 CALL GNFL
      GOTO 1
566 CALL TRPROF
      GOTO 1
567 CALL SSTE
      GOTO 1
568 CALL ADVE
      GOTO 1
569 CALL BGMO
      GOTO 1
570 CALL FEFP
      GOTO 1
571 CALL COUPE
      GOTO 1
572 CALL VERMAI
      GOTO 1
573 CALL DFER
      GOTO 1
574 CALL GYROS
      GOTO 1
575 CALL CORIOL
      GOTO 1
576 CALL KENTR
      GOTO 1
577 CALL FANTOM
      GOTO 1
578 CALL ITRC
      GOTO 1
C RETOUR
579 CONTINUE
      GOTO 9901
580 CALL IJET
      GOTO 1
581 CALL IMPED
      GOTO 1
582 CALL MOCA
      GOTO 1
583 CALL LEVMAR
      GOTO 1
 584 CALL RAVC
      GOTO 1
 585 CALL IDLIAI
      GOTO 1
 586 CALL RAFF
      GOTO 1
 587 CALL CFND
      GOTO 1
 588 CALL ADETAT
      GOTO 1
 589 CALL PSIPHI
      GOTO 1
 590 CALL OPOBJE(9)
C 9 -> ARCCOS (ACOS)
      GOTO 1
 591 CALL OPOBJE(10)
C 10 -> ARCSIN (ASIN)
      GOTO 1
 592 CALL OPOBJE(8)
C 8 -> TANGENTE (TAN)
      GOTO 1
 593 CALL TRIELE
      GOTO 1
 594 CALL GAUNEW
      GOTO 1
 595 CALL HISTOG
       GOTO 1
 596 CALL ETG
      GOTO 1
 597 CALL OTER
      GOTO 1
 598 CALL XPOST
      GOTO 1
 599 CALL RFCO
      GOTO 1
600 CALL VIDE
      GOTO 1
601 CALL VORO
      GOTO 1
602 CALL PRRAYO
      GOTO 1
603 CALL POSI
      GOTO 1
604 CALL MISE
      GOTO 1
605 CALL MISL
      GOTO 1
606 CONTINUE
      CALL COLL
      GOTO 1
607 CONTINUE
      CALL POD
      GOTO 1
608 CONTINUE
      CALL FATIG
      GOTO 1
609 CONTINUE
      CALL ANNO
      GOTO 1
610 CONTINUE
      CALL MIXE
      GOTO 1
611 CONTINUE
      CALL MFILTE
      GOTO 1
612 CONTINUE
      CALL PROLON
      GOTO 1
613 CONTINUE
      CALL EXCCAB
      GOTO 1
614 CONTINUE
      CALL MPMAGV
      GOTO 1
615 CONTINUE
      CALL JPMAGV
      GOTO 1
616 CONTINUE
      CALL JPMM
      GOTO 1
617 CONTINUE
      CALL RAINFLOW
      GOTO 1
C Je sors sur cette etiquette 9901: si on ajoute des operateurs,
C il faut les mettre au dessus
9901 CONTINUE
      CALL FLUSH(IOIMP)
      ILOCE_MAIN=ILOCE
      END
```
## erreur.eso
```fortran
C EDITION DES MESSAGES D'ERREURS
      SUBROUTINE ERREUR(ITYYP)
      IMPLICIT INTEGER(I-N)
      IMPLICIT REAL*8(A-H,O-Z)
-INC PPARAM
-INC CCOPTIO
-INC CCNOYAU
-INC SMBLOC
-INC CCASSIS
      EXTERNAL LONG
      CHARACTER*10 FMT
      CHARACTER*1000 CHERR(2),CHEN(2)
      CHARACTER*1000 CHLU(2)
      DATA FMT/'(1X,A...) '/
C ETAIT-ON DEJA EN ERREUR
C On positionne JERR au MAXI entre l'erreur par ASSISTANT et l'erreur GLOBALE
      jerr=MAX(IERR,IERGLB)
C EN TETE DE MESSAGE D'ERREUR
      ITYP = ITYYP
C NIVEAU=0
      CALL ERREU1(0,CHLU,NIVEAU,NBL)
C on n'emet qu'un seul message d'erreur avant nouvelle instruction
      IF(jerr .NE. 0.and.niveau.GT.0) RETURN
      IF (NBL.EQ.0) GOTO 10
      CALL ERREU2(CHLU,CHEN,NBL,ITYP)
C DANS LE CAS DE MESSAGE ISSU DE LIRE ON REGARDE SI MESLIR A ETE
C UTILISE.
      ITYPAN=ITYP
      IF( ITYP.EQ.37) THEN
         IF( MESERR.NE.0) ITYP= MESERR
         MESERR=0
      ENDIF
C MESSAGE D'ERREUR
      CALL ERREU1(ITYP,CHLU,NIVEAU,NBL)
C on n'emet qu'un seul message d'erreur avant nouvelle instruction
      IF(jerr .NE. 0.and.niveau.GT.0) RETURN
      IF(ITYPAN.EQ.37) NIVEAU=2
      IF (NBL.EQ.0) GOTO 10
      CALL ERREU2(CHLU,CHERR,NBL,ITYP)
      if (niveau.gt.3) return
      IERR =NIVEAU
      IERGLB=NIVEAU
C - pour les ASSISTANTS
        ith=0
          if (nbesc.ne.0) ith=oothrd
        if (ith.ne.0) then
          if ( (IERR .GT. 0) .and. (ierper.lt.3) ) then
            MERRES = ierres
            SEGACT MERRES*MOD
            LOSIER = .TRUE.
            IASSER = ith
            SEGDES MERRES
            mescla = imescl(ith)
            jjjerr = ITYYP
          end if
        end if
      IERMAX=MAX0(IERR,IERMAX)
C est on dans le mode erreur controle ??
      if (ierper.eq.4.and.ierr.ne.0) return
      IF (NIVEAU.NE.0) THEN
        ILON=LONG(CHEN(1))
        WRITE (FMT(6:8),FMT='(I3)') ILON
        WRITE (IOIMP,FMT=FMT) CHEN(1)
      ENDIF
      ILON=LONG(CHERR(1))
C Les Warnings ne sont pas affichés en OPTI ECHO -1
      IF ((IECHO .GT. -1) .OR. (ITYYP .GE. 0)) THEN
C Affichage du message d'erreur ici (Ligne 1)
        WRITE (FMT(6:8),FMT='(I3)') ILON
        WRITE (IOIMP,FMT=FMT) CHERR(1)
        IF (NBL.GE.2) THEN
C Affichage du message d'erreur ici (Ligne 2)
          ILON=LONG(CHERR(2))
          WRITE (FMT(6:8),FMT='(I3)') ILON
          WRITE (IOIMP,FMT=FMT) CHERR(2)
        ENDIF
      ENDIF
C CB : Entry dans depmac qui ne fait rien à ce jour (09/02/2015)
C IF (IIMPI.NE.0.AND.ITYP.GE.1) CALL GIBTRB
  10 CONTINUE
C CB : Entry dans depmac qui ne fait rien à ce jour (09/02/2015)
C if (ierr.gt.1) call GIBTRB
      IF (IERMAX.GT.2.AND.NIVEAU.GT.0) CALL FIN
C cas erreur fatale
      IF (IERR.GT.0.AND.IERPER.EQ.1.AND.NIVEAU.GT.0) CALL FIN
C cas ou on ignore les erreurs
      IF (IERPER.GE.3) RETURN
      IF (IERR.GT.0) THEN
       MBERR=MAX(IERR,MBERR)
       IF (IOLEC.NE.IOTER) THEN
        CALL ERREU1(-1,CHLU,NIVEAU,NBL)
        IF (NBL.EQ.0) RETURN
        CALL ERREU2(CHLU,CHERR,NBL,ITYP)
        ILON=LONG(CHERR(1))
        WRITE (FMT(6:8),FMT='(I3)') ILON
        WRITE (IOIMP,FMT=FMT) CHERR(1)
        IOLEC=IOTER
        CALL GINT2
       ENDIF
      ENDIF
      END
```
## actobj.eso
```fortran
      SUBROUTINE ACTOBJ(CTYPE,IPOIN,IKOD)
C OBJET : Cette SUBROUTINE permet d''activer/desactiver un OBJET
C de Cast3M contenu dans le DATA DTAOBJ
C ENTREES :
C °°°°°°°°°
C CTYPE Type d'objet a activer
C IPOIN Pointeur sur l'objet a activer
C IKOD ENTIER valant 0 pour SEGDES
C 1 pour SEGACT de l'objet
C SORTIE :
C °°°°°°°°
C R.A.S l'objet et son contenu sont actives
      IMPLICIT INTEGER(I-N)
      IMPLICIT REAL*8(A-H,O-Z)
-INC PPARAM
-INC CCOPTIO
-INC SMCHAML
-INC SMINTE
-INC SMCHPOI
-INC SMLCHPO
-INC SMMODEL
-INC SMEVOLL
-INC SMELEME
-INC SMNUAGE
-INC SMCHARG
-INC SMRIGID
-INC SMANNOT
-INC CCPRECO
C -INC CCASSIS
      SEGMENT JPOINT(0)
      SEGMENT IPOINT(0)
      SEGMENT ISEG(0)
      SEGMENT ITAB(NNN)
      PARAMETER(NBTYP=14)
      CHARACTER*(*)CTYPE
      CHARACTER*8 CTYP1,DTAOBJ(NBTYP),MOT8a
      CHARACTER*16 MOT16
      LOGICAL BCODE,BSEG
      DATA DTAOBJ/'MCHAML  ','CHPOINT ','MMODEL  ','MAILLAGE',
     & 'EVOLUTIO','LISTMOTS','LISTREEL','LISTENTI',
     & 'NUAGE   ','LISTCHPO','CHARGEME','ANNULE  ',
     & 'RIGIDITE','ANNOTATI' /
      MMODE2 = 0
      CTYP1 = CTYPE
      IF(IERR .NE. 0) RETURN
      CALL PLAMO8(DTAOBJ,NBTYP,IPLAC,CTYP1)
      IF(IPLAC.EQ.0 .OR. IPLAC.EQ.12)RETURN
C Les arguments optionnels dans les PROCEDURES sont de type ANNULE(12) s'ils sont absents
      IF(IPOIN .LE. 0) THEN
        PRINT *,'ACTOBJ POINTEUR INVALIDE - TYPE ''',CTYP1,
     & ''' - POINTEUR ',IPOIN
C J'essaye de declencher un GEMAT_ERROR pour la capturer avec gdb
        CALL TRBAC
        ISEG=IPOIN
        SEGACT,ISEG
        CALL ERREUR(5)
      ENDIF
      IPOI1 = IPOIN
      BCODE = IKOD .EQ. 0
C Portion a activer pour des recherches de SEGDES inutiles !
      IF(.FALSE.)THEN
C Verification rapide de l'etat du SEGMENT IPOI1
        CALL OOOETA(IPOI1,IETA,IMOD)
        IF(BCODE)THEN
C Il est inactif et on veut SEGDES ==> RETURN
          IF(IETA.EQ.2) RETURN
        ELSE
C Recherche de SEGMENT qui n'ont pas de raison d'etre desactives
C -Empecher le MENAGE dans PILOT pour ce test d'optimisation
C -Remettre l'include CCASSIS.INC
C IF(IETA.EQ.2 .AND. IMOD.NE.1) THEN
C CALL oooho1(IPOI1,IHO1)
C IF(MOD(IHO1,NBTHRS+1) .EQ. oothrd)THEN
C CALL OOOMES(IPOI1,'    ZARBI:'//CTYP1)
C STOP 16
C ENDIF
C ENDIF
C Il est actif *NOMOD et on veut SEGACT ==> RETURN
          IF(IETA.EQ.1 .AND. IMOD.EQ.0) RETURN
        ENDIF
      ENDIF
      IOBJ = 0
      IPOINT= 0
      JPOINT= 0
      BSEG =.FALSE.
C Initialisation des SEGMENTS de preconditionnement
      nth=oothrd+1
      ITAB=PACTOB(nth)
      IF(ITAB .EQ. 0)THEN
        NNN=50
        SEGINI,ITAB
        PACTOB(nth)=ITAB
      ELSE
        SEGACT,ITAB*MOD
      ENDIF
      ICOUNT =1
C En premiere case on met la taille utile du tableau
      ITAB(1)=1
 1 CONTINUE
      IF(IPLAC.EQ.0) THEN
C PRINT *,'ACTOBJ.ESO :',CTYP1,' NON TRAITE ENCORE'
        GOTO 9999
      ENDIF
      GOTO (100,200,300,400,500,600,600,600,700,600,800,9999,900
     & ,1000),IPLAC
      PRINT *,'ACTOBJ ERROR:',IPLAC
      CALL ERREUR(5)
      GOTO 9999
 100 CONTINUE
C CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
C OBJET DE TYPE MCHAML
C CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
        MCHEL1=IPOI1
        MELSAV=0
        CALL oooprl(1)
        SEGACT,MCHEL1
        DO 111 II=1,MCHEL1.ICHAML(/1)
          MCHAM1=MCHEL1.ICHAML(II)
          SEGACT,MCHAM1
 111 CONTINUE
        CALL oooprl(0)
        IF (BCODE) CALL PREACT(ITAB,MCHEL1)
        DO 110 II=1,MCHEL1.ICHAML(/1)
          MCHAM1=MCHEL1.ICHAML(II)
          IPT1=MCHEL1.IMACHE(II)
          CALL PREACT(ITAB,IPT1)
          IF(MCHEL1.INFCHE(/2) .GE. 4)THEN
            MINTE =MCHEL1.INFCHE(II,4)
            IF(MINTE .NE. 0) CALL PREACT(ITAB,MINTE)
          ENDIF
          IF (BCODE) CALL PREACT(ITAB,MCHAM1)
          DO 120 JJ=1,MCHAM1.IELVAL(/1)
            MOT16 =MCHAM1.TYPCHE(JJ)
            MELVA1=MCHAM1.IELVAL(JJ)
            IF(MELVA1 .EQ. MELSAV) GOTO 120
            MELSAV=MELVA1
            IF (MOT16(1:6) .EQ. 'REAL*8' .OR.
     & MOT16(1:13) .EQ. 'POINTEURPOINT' )THEN
              CALL PREACT(ITAB,MELVA1)
            ELSEIF(MOT16(1:12) .EQ. 'POINTEURLIST')THEN
              SEGACT,MELVA1
              IF (BCODE) CALL PREACT(ITAB,MELVA1)
              IPOI2 = 0
              DO 130 KK=1,MELVA1.IELCHE(/2)
                DO 140 LL=1,MELVA1.IELCHE(/1)
                  ISEG=MELVA1.IELCHE(LL,KK)
                  IF(ISEG .NE. IPOI2 .AND. ISEG.NE.0)THEN
                    CALL PREACT(ITAB,ISEG)
                    IPOI2 = ISEG
                  ENDIF
 140 CONTINUE
 130 CONTINUE
            ELSEIF(MOT16(1:16) .EQ. 'POINTEUREVOLUTIO')THEN
              SEGACT,MELVA1
              IF (BCODE) CALL PREACT(ITAB,MELVA1)
              IPOI2 = 0
              DO 150 KK=1,MELVA1.IELCHE(/2)
                DO 160 LL=1,MELVA1.IELCHE(/1)
                  MEVOL1=MELVA1.IELCHE(LL,KK)
                  IF(MEVOL1 .NE. IPOI2 .AND. MEVOL1.NE.0)THEN
                    IPOI2 = MEVOL1
                    SEGACT,MEVOL1
                    IF (BCODE) CALL PREACT(ITAB,MEVOL1)
                    DO 170 MM=1,MEVOL1.IEVOLL(/1)
                      KEVOL1=MEVOL1.IEVOLL(MM)
                      SEGACT,KEVOL1
                      IF (BCODE) CALL PREACT(ITAB,KEVOL1)
                      ISEG=KEVOL1.IPROGX
                      CALL PREACT(ITAB,ISEG)
                      ISEG=KEVOL1.IPROGY
                      CALL PREACT(ITAB,ISEG)
 170 CONTINUE
                  ENDIF
 160 CONTINUE
 150 CONTINUE
            ELSEIF(MOT16(1:8) .EQ. 'POINTEUR')THEN
C Cas des MCHAML de POINTEURS necessitant du travail
              SEGACT,MELVA1
              IF (BCODE) CALL PREACT(ITAB,MELVA1)
              IPOI2 = 0
              CTYP1 = MOT16(9:16)
              CALL PLAMO8(DTAOBJ,NBTYP,IPLAC,CTYP1)
              IF(IPLAC .NE. 0)THEN
                DO 180 KK=1,MELVA1.IELCHE(/2)
                  DO 190 LL=1,MELVA1.IELCHE(/1)
                    ISEG =MELVA1.IELCHE(LL,KK)
                    IF(ISEG.NE.IPOI2 .AND. ISEG.NE.0)THEN
                      IPOI2 = ISEG
                      IF(.NOT. BSEG)THEN
                        SEGINI,JPOINT,IPOINT
                        BSEG=.TRUE.
                      ENDIF
                      JPOINT(**)=MELVA1.IELCHE(LL,KK)
                      IPOINT(**)=IPLAC
                    ENDIF
 190 CONTINUE
 180 CONTINUE
C ELSE
C PRINT*,'ACTOBJ:MCHAML de TYPE',MOT16,' non traite'
              ENDIF
            ELSE
              CALL PREACT(ITAB,MELVA1)
            ENDIF
 120 CONTINUE
 110 CONTINUE
        GOTO 9999
 200 CONTINUE
C CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
C OBJET DE TYPE CHPOINT
C CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
      MCHPO1=IPOI1
      CALL oooprl(1)
      SEGACT,MCHPO1
      NSOUPO=MCHPO1.IPCHP(/1)
      DO 211 II=1,NSOUPO
        MSOUP1=MCHPO1.IPCHP(II)
        SEGACT,MSOUP1
 211 CONTINUE
      CALL oooprl(0)
      IF (BCODE) CALL PREACT(ITAB,MCHPO1)
      DO 210 II=1,NSOUPO
        MSOUP1=MCHPO1.IPCHP(II)
        IF (BCODE) CALL PREACT(ITAB,MSOUP1)
        IPT1=MSOUP1.IGEOC
        CALL PREACT(ITAB,IPT1)
        MPOVA1=MSOUP1.IPOVAL
        CALL PREACT(ITAB,MPOVA1)
 210 CONTINUE
      GOTO 9999
 300 CONTINUE
C CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
C OBJET DE TYPE MMODEL
C CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
      MMODE1=IPOI1
      SEGACT,MMODE1
      IF (BCODE) CALL PREACT(ITAB,MMODE1)
      NN1 = 0
      DO 310 II=1,MMODE1.KMODEL(/1)
        IMODE1=MMODE1.KMODEL(II)
        SEGACT,IMODE1
        IF (BCODE) CALL PREACT(ITAB,IMODE1)
        IPT1=IMODE1.IMAMOD
        CALL PREACT(ITAB,IPT1)
        NIVM = IMODE1.IVAMOD(/1)
        DO 320 JJ=1,NIVM
          CTYP1=IMODE1.TYMODE(JJ)
          CALL PLAMO8(DTAOBJ,NBTYP,IPLAC,CTYP1)
          IF(IPLAC .NE. 0)THEN
            IF(.NOT. BSEG)THEN
              SEGINI,JPOINT,IPOINT
              BSEG=.TRUE.
            ENDIF
            JPOINT(**)=IMODE1.IVAMOD(JJ)
            IPOINT(**)=IPLAC
          ELSEIF(CTYP1 .EQ. 'IMODEL  ')THEN
C Construction d'un MODELE AVEC les IMODEL (Cas des MODELES de melange)
            NN1 = NN1 + 1
            IF(MMODE2 .EQ. 0)THEN
              N1 = NIVM
              SEGINI,MMODE2
            ELSEIF(NN1 .GT. MMODE2.KMODEL(/1))THEN
              N1 = N1 + NIVM
              SEGADJ,MMODE2
            ENDIF
            MMODE2.KMODEL(NN1)=IMODE1.IVAMOD(JJ)
          ENDIF
 320 CONTINUE
        NBNOMI =IMODE1.LNOMID(/1)
        DO 330 INOM=1,NBNOMI
          IPT1=IMODE1.LNOMID(INOM)
          IF (IPT1 .GT. 0) CALL PREACT(ITAB,IPT1)
 330 CONTINUE
       DO 340 IINFMO=3,IMODE1.INFMOD(/1)
          IPT1=IMODE1.INFMOD(IINFMO)
          IF (IPT1 .GT. 0) CALL PREACT(ITAB,IPT1)
 340 CONTINUE
 310 CONTINUE
      IF (NN1 .GT. 0) THEN
C On a cree un MMODEL supplementaire
        IF(N1 .NE. NN1)THEN
          N1 = NN1
          SEGADJ,MMODE2
        ENDIF
C On ajoute MMODE2 dans la liste des pointeurs 'MMODEL  ' a traiter
        CTYP1 ='MMODEL  '
        CALL PLAMO8(DTAOBJ,NBTYP,IPLAC,CTYP1)
        IF(.NOT. BSEG)THEN
          SEGINI,JPOINT,IPOINT
          BSEG=.TRUE.
        ENDIF
        JPOINT(**)=MMODE2
        IPOINT(**)=IPLAC
      ENDIF
      GOTO 9999
 400 CONTINUE
C CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
C OBJET DE TYPE MAILLAGE
C CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
      IPT1=IPOI1
      SEGACT,IPT1
      IF (BCODE) CALL PREACT(ITAB,IPT1)
      DO 410 II=1,IPT1.LISOUS(/1)
        IPT2 =IPT1.LISOUS(II)
        CALL PREACT(ITAB,IPT2)
 410 CONTINUE
      GOTO 9999
 500 CONTINUE
C CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
C OBJET DE TYPE EVOLUTIO
C CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
      MEVOL1=IPOI1
      SEGACT,MEVOL1
      IF (BCODE) CALL PREACT(ITAB,MEVOL1)
      DO 510 II=1,MEVOL1.IEVOLL(/1)
        KEVOL1=MEVOL1.IEVOLL(II)
        SEGACT,KEVOL1
        IF (BCODE) CALL PREACT(ITAB,KEVOL1)
        ISEG=KEVOL1.IPROGX
        CALL PREACT(ITAB,ISEG)
        ISEG=KEVOL1.IPROGY
        CALL PREACT(ITAB,ISEG)
 510 CONTINUE
      GOTO 9999
 600 CONTINUE
C CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
C OBJET DE TYPE LISTXXXX
C CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
      IF(IPLAC .EQ. 10)THEN
C Cas des LISTCHPO
        MLCHPO=IPOI1
        SEGACT,MLCHPO
        IF (BCODE) CALL PREACT(ITAB,MLCHPO)
        CTYP1='CHPOINT '
        CALL PLAMO8(DTAOBJ,NBTYP,IPLAC,CTYP1)
        IF(.NOT. BSEG)THEN
          SEGINI,JPOINT,IPOINT
          BSEG=.TRUE.
        ENDIF
        DO 610 II=1,MLCHPO.ICHPOI(/1)
          JPOINT(**)=MLCHPO.ICHPOI(II)
          IPOINT(**)=IPLAC
 610 CONTINUE
      ELSE
C Cas des LISTENTI,LISTREEL,LISTMOTS
        CALL PREACT(ITAB,IPOI1)
      ENDIF
      GOTO 9999
 700 CONTINUE
C CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
C OBJET DE TYPE NUAGE
C CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
      MNUAG1=IPOI1
      SEGACT,MNUAG1
      IF (BCODE) CALL PREACT(ITAB,MNUAG1)
      DO 710 II=1,MNUAG1.NUAPOI(/1)
        CTYP1=MNUAG1.NUATYP(II)
        CALL PLAMO8(DTAOBJ,NBTYP,IPLAC,CTYP1)
        IF(IPLAC .NE. 0)THEN
          IF(.NOT. BSEG)THEN
            SEGINI,JPOINT,IPOINT
            BSEG=.TRUE.
          ENDIF
          NUAVIN=MNUAG1.NUAPOI(II)
          SEGACT,NUAVIN
          IF (BCODE) CALL PREACT(ITAB,NUAVIN)
          DO 720 JJ=1,NUAVIN.NUAINT(/1)
            JPOINT(**)=NUAVIN.NUAINT(JJ)
            IPOINT(**)=IPLAC
 720 CONTINUE
        ELSE
          ISEG=MNUAG1.NUAPOI(II)
          CALL PREACT(ITAB,ISEG)
        ENDIF
 710 CONTINUE
      GOTO 9999
 800 CONTINUE
C CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
C OBJET DE TYPE CHARGEMENT
C CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
      MCHAR1=IPOI1
      SEGACT,MCHAR1
      IF (BCODE) CALL PREACT(ITAB,MCHAR1)
      DO 810 II=1,MCHAR1.KCHARG(/1)
        ICHAR1=MCHAR1.KCHARG(II)
        SEGACT,ICHAR1
        IF (BCODE) CALL PREACT(ITAB,ICHAR1)
        CTYP1=ICHAR1.CHATYP
        CALL PLAMO8(DTAOBJ,NBTYP,IPLAC,CTYP1)
        IF(IPLAC .NE. 0)THEN
          IF(.NOT. BSEG)THEN
            SEGINI,JPOINT,IPOINT
            BSEG=.TRUE.
          ENDIF
          JPOINT(**)=ICHAR1.ICHPO1
          IPOINT(**)=IPLAC
        ENDIF
 810 CONTINUE
      GOTO 9999
 900 CONTINUE
C CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
C OBJET DE TYPE RIGIDITE
C Ne traite que la partie non assemblee des objets RIGIDITE
C CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
      MRIGID=IPOI1
      SEGACT,MRIGID
      IF (BCODE) CALL PREACT(ITAB,MRIGID)
      IMGEOD=MRIGID.IMGEO1
C PRINT *,' -- IMGEOD:',IMGEOD
      IF (IMGEOD.NE.0)CALL PREACT(ITAB,IMGEOD)
      MVECRI=MRIGID.IVECRI
C PRINT *,' -- MVECRI:',MVECRI
      IF (MVECRI.NE.0)CALL PREACT(ITAB,MVECRI)
      DO 910 II=1,MRIGID.COERIG(/1)
        IPT1 = MRIGID.IRIGEL(1,II)
C PRINT *,' -- IPT1  :',IPT1
        CALL PREACT(ITAB,IPT1)
        IPT2 = MRIGID.IRIGEL(2,II)
C PRINT *,' -- IPT2  :',IPT2
        IF(IPT2 .GT. 0)CALL PREACT(ITAB,IPT2)
        DESCR = MRIGID.IRIGEL(3,II)
C PRINT *,' -- DESCR :',DESCR
        CALL PREACT(ITAB,DESCR)
        XMATRI = MRIGID.IRIGEL(4,II)
C PRINT *,' -- XMATRI:',XMATRI
        CALL PREACT(ITAB,XMATRI)
 910 CONTINUE
      GOTO 9999
 1000 CONTINUE
C CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
C OBJET DE TYPE ANNOTATI
C CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
      MANNOT=IPOI1
      SEGACT,MANNOT
      IF (BCODE) CALL PREACT(ITAB,MANNOT)
      DO 1010 II=1,MANNOT.ICLAS(/1)
        IF(MANNOT.ICLAS(II) .EQ. 2)THEN
          METIQU = MANNOT.ISEGT(II)
          SEGACT,METIQU
          IF (BCODE) CALL PREACT(ITAB,METIQU)
          MELEME = METIQU.INUPT
          CALL PLAMO8(DTAOBJ,NBTYP,IPLAC,'MAILLAGE')
          IF(IPLAC .NE. 0)THEN
            IF(.NOT. BSEG)THEN
              SEGINI,JPOINT,IPOINT
              BSEG=.TRUE.
            ENDIF
            JPOINT(**)=MELEME
            IPOINT(**)=IPLAC
          ENDIF
        ENDIF
 1010 CONTINUE
      GOTO 9999
C CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
 9999 CONTINUE
      IF(BCODE)THEN
C Boucle a la main en attendant SEGDES par paquets !
        DO II=2,ICOUNT
          ISEG=ITAB(II)
          SEGDES,ISEG
        ENDDO
      ELSE
C Appel a SEGACT par paquet !
        CALL FINACT(ITAB)
      ENDIF
      IF(.NOT. BSEG) GOTO 9990
      IF(IOBJ .NE. JPOINT(/1))THEN
        IOBJ = IOBJ + 1
        IPLAC = IPOINT(IOBJ)
        IPOI1 = JPOINT(IOBJ)
        GOTO 1
      ENDIF
 9990 CONTINUE
      IF (BSEG) SEGSUP,JPOINT,IPOINT
      IF (MMODE2 .NE. 0) SEGSUP,MMODE2
      END
```
## lirlog.eso
```fortran
      SUBROUTINE LIRLOG(BVAL , ICODE , IRETOU )
      IMPLICIT INTEGER(I-N)
-INC CCNOYAU
-INC PPARAM
-INC CCOPTIO
-INC CCASSIS
      LOGICAL BVAL
      CHARACTER*(8) ILO
      ILO='LOGIQUE '
      CALL LIRABJ(ILO,IRAT,ICODE,IRETOU)
      IF(IERR.NE.0) RETURN
      IF(IRETOU.EQ.0) RETURN
      ith=0
      if (nbesc.ne.0) ith=oothrd
      if (ith.eq.0) then
        if(nbesc.ne.0) segact ipiloc
        BVAL=IPLOGI(IRAT)
        if(nbesc.ne.0) SEGDES,IPILOC
      else
        mescla=imescl(ith)
        BVAL=esoplo(irat)
      endif
      RETURN
      END
```
## lircha.eso
```fortran
      SUBROUTINE LIRCHA(ITYP , ICODE , IRETOU )
C EN RETOUR IRETOU EST NUL SI PAS DE MOT TROUVE SINON C'EST LA LONGUEU
C DU MOT
      IMPLICIT INTEGER(I-N)
-INC PPARAM
-INC CCNOYAU
-INC CCOPTIO
-INC CCASSIS
      external long
      CHARACTER*(*) ITYP
      CHARACTER*(8) ICHA
      ICHA='MOT'
      CALL LIRABJ(ICHA,IRAT,ICODE,IRETOU)
      IF(IERR .NE. 0) RETURN
      IF(IRETOU.EQ. 0) RETURN
C initialisation de lotesc
      lotesc=.false.
      ith = 0
      if (nbesc.ne.0) ith=oothrd
      if (ith.ne.0) lotesc=.true.
C write (6,*) ' dans lircha ',ith
      if (.not. lotesc) then
         if(nbesc.ne.0) SEGACT,IPILOC
         IL = LEN(ITYP)
         JF = IPCHAR(IRAT+1)
         ID = IPCHAR(IRAT)
         ILO = MIN(IL,JF-ID)
         ITYP = ICHARA(ID:JF-1)
         IRETOU= ILO
         if(nbesc.ne.0) SEGDES,IPILOC
      else
         mescla= imescl(ith)
         ityp = esopch(irat)
         iretou= long(ityp)
      endif
      END
```
## ecrree.eso
```fortran
      SUBROUTINE ECRREE( XXVA)
      IMPLICIT INTEGER(I-N)
-INC CCNOYAU
-INC CCASSIS
      REAL*8 XXVA
      DIMENSION ITEMP(2)
      ith=0
      if (nbesc.ne.0) ith=oothrd
      if (ith.eq.0) then
        ITEMP(2)=0
        call posree (xxva,itemp(1))
        CALL ECPI(ITEMP,'FLOTTANT')
        RETURN
      else
C cas de l'esclave
        mescla=imescl(ith)
        call ecresc(i)
        esoplu(i)=.false.
        esopty(i)='FLOTTANT'
        esopre(i)=xxva
        return
      endif
      END
```
## ecrcha.eso
```fortran
      SUBROUTINE ECRCHA(MCH)
      IMPLICIT INTEGER(I-N)
-INC CCNOYAU
-INC CCASSIS
      CHARACTER*(*) MCH
      DIMENSION ITEMP(2)
      ith=0
      if (nbesc.ne.0) ith=oothrd
      if (ith.eq.0) then
      IL=LEN(MCH)
      ITEMP(2)=0
       CALL POSCHA(MCH,IRET)
      ITEMP(1)=IRET
   60 CONTINUE
      CALL ECPI(ITEMP,'MOT     ')
      RETURN
      else
C cas de l'esclave
      mescla=imescl(ith)
      call ecresc(i)
      esoplu(i)=.false.
      esopty(i)='MOT'
      esopch(i)=mch
      endif
      END
```
## ecrlog.eso
```fortran
      SUBROUTINE ECRLOG(BRET)
      IMPLICIT INTEGER(I-N)
-INC CCNOYAU
-INC CCASSIS
      DIMENSION ITEMP(2)
      LOGICAL BRET
      ith=0
      if (nbesc.ne.0) ith=oothrd
      if (ith.eq.0) then
      ITEMP(2)=0
C LA VALEUR EXISTE-T-ELLE DEJA DANS LA PILE
      call poslog(bret,itemp(1))
  60 CALL ECPI(ITEMP,'LOGIQUE ')
      RETURN
      else
C cas de l'esclave
      mescla=imescl(ith)
      call ecresc(i)
      esoplu(i)=.false.
      esopty(i)='LOGIQUE'
      esoplo(i)=bret
      endif
      END
```
## ecctab.eso
```fortran
      SUBROUTINE ECCTAB(MTABLE,TAPIND,IVALIN,XVALIN,CHARIN,LOGIN,IOBIN,
     $ TAPOBJ,IVALRE,XVALRE,CHARRE,LOGRE,IOBRE)
C MET UN OBJET DANS UNE TABLE
C TAPIND TYPE DE L'INDICE  CHARACTER*(*)
C PUIS LA VALEUR DE L'INDICE  IVALIN SI ENTIER
C XVALIN SI FLOTTANT
C CHARIN SI MOT
C LOGIN SI LOGIQUE
C IOBIN POUR TOUT AUTRE TYPE
C TAPOBJ TYPE DE L'OBJET CHARACTER*(*)
C PUIS LA VALEUR DE L'INDICE  IVALRE SI ENTIER
C XVALRE SI FLOTTANT
C CHARRE SI MOT
C LOGRE SI LOGIQUE
C IOBRE POUR TOUT AUTRE TYPE
      IMPLICIT INTEGER(I-N)
-INC CCNOYAU
-INC SMTABLE
-INC PPARAM
-INC CCOPTIO
-INC CCASSIS
      external long
      REAL*8 XVALIN,XVALRE
      LOGICAL LOGRE,LOGIN
      CHARACTER*(*) TAPIND,TAPOBJ,CHARIN,CHARRE
      CHARACTER*(8) CHARA,TYPIND,TYPOBJ
      if(nbesc.ne.0) segact ipiloc
      TYPIND=TAPIND
      TYPOBJ=TAPOBJ
      SEGACT MTABLE*MOD
      IN = MLOTAB
C RECHERCHE DE L'INDICE S'IL EXISTE
      IA=4
      IF(TYPIND.EQ.'ENTIER  ') IA=1
      IF(TYPIND.EQ.'FLOTTANT') IA=2
      IF(TYPIND.EQ.'MOT     ') IA=3
      IF(TYPIND.EQ.'METHODE ') IA=3
      IF(TYPIND.EQ.'LOGIQUE ') IA=5
C dans le cas des mots on ignore les blancs situes a la fin
      IF(IA.EQ.3) IL=LONG(CHARIN)
      IF(IN.EQ.0) GOTO 10
      DO 1 I=1,IN
        MT=I
        IF(MTABTI(I).NE.TYPIND ) GOTO 1
        GOTO (11,12,13,14,15),IA
   11 CONTINUE
        IF(MTABII(I).NE.IVALIN) GOTO 1
        GOTO 20
   12 CONTINUE
        IF(RMTABI(I).NE.XVALIN ) GOTO 1
        GOTO 20
   15 CONTINUE
        IF(IPLOGI(MTABII(I)).NEQV.LOGIN ) GOTO 1
        GOTO 20
   14 CONTINUE
        IF(MTABII(I).NE.IOBIN) GOTO 1
        GOTO 20
   13 CONTINUE
        IP =MTABII(I)
        ID =IPCHAR(IP)
        IFI=IPCHAR(IP+1)
        IL1=LONG(ICHARA(ID:IFI-1))
        IF(IL1.NE.IL) GOTO 1
        IF(CHARIN(1:IL).NE.ICHARA(ID:ID+IL-1)) GOTO 1
        GOTO 20
   1 CONTINUE
  10 CONTINUE
C L'INDICE N'EXISTE PAS ON L'AJOUTE
      MLOTAB=MLOTAB+1
      M=MTABII(/1)
      IF (MLOTAB .GT. M) THEN
        M=MLOTAB + MAX(INT(REAL(MLOTAB)*0.2D0),50)
        SEGADJ,MTABLE
      ENDIF
      M=MLOTAB
      MT=M
      MTABTI(M)=TYPIND
      IF(IA.EQ.1) THEN
           IRET=IVALIN
      ELSEIF(IA.EQ.2) THEN
           RMTABI(MT)=XVALIN
           GOTO 20
      ELSEIF(IA.EQ.3) THEN
           CALL POSCHA( CHARIN(1:IL),IRET)
           GOTO 200
      ELSEIF(IA.EQ.5) THEN
           call poslog(login,iret)
           GOTO 200
      ELSEIF(IA.EQ.4) THEN
           IRET=IOBIN
      ENDIF
  200 MTABII(MT)=IRET
C if(nbesc.ne.0) segact ipiloc
   20 CONTINUE
C FINI POUR L'INDICE FAIRE LA VALEUR
      IA=4
      IF(TYPOBJ.EQ.'ENTIER  ') IA=1
      IF(TYPOBJ.EQ.'FLOTTANT') IA=2
      IF(TYPOBJ.EQ.'MOT     ') IA=3
      IF(TYPOBJ.EQ.'LOGIQUE ') IA=5
      IF(IA.EQ.3) IL=LEN(CHARRE)
      MTABTV(MT)= TYPOBJ
      IF(IA.EQ.1) THEN
           IRET=IVALRE
      ELSEIF(IA.EQ.2) THEN
           IRET=0
           RMTABV(MT)=XVALRE
           GOTO 300
      ELSEIF(IA.EQ.3) THEN
           CALL POSCHA(CHARRE,IRET)
           GOTO 300
      ELSEIF(IA.EQ.5) THEN
           call poslog(logre,iret)
           GOTO 300
      ELSEIF(IA.EQ.4) THEN
           IRET=IOBRE
      ENDIF
  300 MTABIV(MT)=IRET
      SEGDES,MTABLE
      If(nbesc.ne.0) SEGDES,IPILOC
      END
```
## acmo.eso
```fortran
      SUBROUTINE ACMO(ITABLE,MOTI,TYPI,IOBJ)
C Récupération de l'objet stocké à un indice de type MOT d'une TABLE.
C On peut préciser le type de l'objet souhaité dans TYPI.
C En retour, TYPI contient le type de l'objet effectivement lu.
C Le pointeur IOBJ n'est pas utilisable si TYPI est ENTIER, FLOTTANT
C ou MOT. Dans ce cas, utiliser ACME, ACMF ou ACMM.
C Opérandes et résultat :
C E/ ITABLE : Table
C E/ MOTI : Indice de type MOT indexant l'objet cherché
C E/S TYPI : Type de l'objet
C /S IOBJ : Objet contenu dans la table ITABLE à l'indice mot MOTI
C ATTENTION : L'indice de type MOT MOTI doit avoir au plus 8 caractères
C (sinon, utiliser ACCTAB) et les blancs en fin de mot sont
C ignorés ('mot sb  ' est transformé en 'mot sb').
      IMPLICIT INTEGER(I-N)
      IMPLICIT REAL*8(A-H,O-Z)
      LOGICAL LOGI
      CHARACTER*(*) MOTI,TYPI
      CHARACTER*8 BLAN,TYPE,MOTE
      DATA BLAN/'        '/
      TYPE = TYPI
      CALL ACCTAB(ITABLE,'MOT',0,0.D0,MOTI,LOGI,0,
     1 TYPE,IENT,XVAL,MOTE,LOGI,IOBJ)
      TYPI = TYPE
      RETURN
      END
```
## acme.eso
```fortran
      SUBROUTINE ACME(ITABLE,MOTI,IVAL)
C Récupération de l'ENTIER stocké à un indice de type MOT d'une TABLE
C Opérandes et résultat :
C E/ ITABLE : TABLE
C E/ MOTI : Indice de type MOT indexant l'objet cherché
C /S IVAL : ENTIER contenu dans la table ITABLE à l'indice MOT MOTI
C ATTENTION : L'indice de type MOT MOTI doit avoir au plus 8 caractères
C (sinon, utiliser ACCTAB) et les blancs en fin de mot sont
C ignorés ('mot sb  ' est transformé en 'mot sb').
      IMPLICIT INTEGER(I-N)
      IMPLICIT REAL*8(A-H,O-Z)
      LOGICAL XLOGI
      CHARACTER*(*) MOTI
      CHARACTER*8 BLAN,MOT,TYPE
      DATA BLAN/'        '/
      MOT = MOTI
      CALL LENCHA(MOT,LC)
      TYPE = 'ENTIER  '
      CALL ACCTAB(ITABLE,'MOT',0,0.D0,MOT(1:LC),.TRUE.,0,
     1 TYPE,IVAL,XVAL,BLAN,XLOGI,IRET)
      RETURN
      END
```
## acmf.eso
```fortran
      SUBROUTINE ACMF(ITABLE,MOTI,XVAL)
C Récupération d'un FLOTTANT stocké à un indice de type MOT d'une TABLE.
C Opérandes et résultat :
C E/ ITABLE : Table
C E/ MOTI : Indice de type MOT indexant l'objet cherché
C /S XVAL : FLOTTANT contenu dans la table ITABLE à l'indice MOT MOTI
C ATTENTION : L'indice de type MOT MOTI doit avoir au plus 8 caractères
C (sinon, utiliser ACCTAB) et les blancs en fin de mot sont
C ignorés ('mot sb  ' est transformé en 'mot sb').
      IMPLICIT INTEGER(I-N)
      IMPLICIT REAL*8(A-H,O-Z)
      LOGICAL XLOGI
      CHARACTER*(*) MOTI
      CHARACTER*8 BLAN,MOT,TYPE
      DATA BLAN/'        '/
      MOT = MOTI
      CALL LENCHA(MOT,LC)
      TYPE = 'FLOTTANT'
      CALL ACCTAB(ITABLE,'MOT',0,0.D0,MOT(1:LC),.TRUE.,0,
     1 TYPE,IENT,XVAL,BLAN,XLOGI,IRET)
      RETURN
      END
```
## crtabl.eso
```fortran
C CREATION D'UNE TABLE (VIDE)
      SUBROUTINE CRTABL(MTABLE)
      IMPLICIT INTEGER(I-N)
-INC SMTABLE
      M=0
      SEGINI MTABLE
      END
```
## nbel.eso
```fortran
C REND LE NOMBRE D'ELEMENTS D'UN OBJET
      SUBROUTINE NBEL
      IMPLICIT INTEGER(I-N)
-INC PPARAM
-INC CCOPTIO
-INC CCGEOME
-INC SMELEME
-INC SMLMOTS
-INC SMLENTI
      CHARACTER*4 LETYP
      CALL LIROBJ('MAILLAGE',MELEME,1,IRETOU)
      IF (IERR.NE.0) RETURN
      CALL LIROBJ('LISTMOTS',MLMOTS,0,ISPRA)
      SEGACT MELEME
      IF(ISPRA.NE.0) GO TO 3
      NBL=0
      IPT1=MELEME
      DO 2 I=1,MAX(1,LISOUS(/1))
      IF (LISOUS(/1).NE.0) THEN
       IPT1=LISOUS(I)
       SEGACT IPT1
      ENDIF
      NBL=NBL+IPT1.NUM(/2)
   2 CONTINUE
      CALL ECRENT(NBL)
      RETURN
   3 CONTINUE
      SEGACT MLMOTS
      JG=MOTS(/2)
      SEGINI MLENTI
      IPT1=MELEME
      DO 4 I=1,MAX(1,LISOUS(/1))
        IF (LISOUS(/1).NE.0) THEN
         IPT1=LISOUS(I)
         SEGACT IPT1
        ENDIF
        LETYP=NOMS(IPT1.ITYPEL)
        DO 5 IJ=1,JG
          IF(LETYP.NE.MOTS(IJ)) GO TO 5
          LECT(IJ)=LECT(IJ)+IPT1.NUM(/2)
          GO TO 4
   5 CONTINUE
   4 CONTINUE
      SEGACT MLENTI
      CALL ECROBJ('LISTENTI',MLENTI)
      END
```
## prelim.eso
```fortran
      SUBROUTINE PRELIM(ICLE)
      IMPLICIT INTEGER(I-N)
      IMPLICIT REAL*8 (A-H,O-Z)
C CE SOUS PROGRAMME PREPARE LES DONNEES POUR ELIM
C IL FORME LA TABLE DES POINTS A TESTER
C ICPR EST LA MOUVELLE NUMEROTATION
C ICPR(ANCIEN N°)= NOUVEAU N°
C ICPR(ANCIEN N°)= 0 SI LE NOEUDS N'APPARTIENT PAS AU MAILLAGE(S
C ) ARGUMENT(S)
C IAPOB1 EST UN TABLEAU SUR LA NOUVELLE NUMEROTATION
C =1 SI LE NOEUD EST DANS LE 1ER MAILLGE =0 SINON
C IAPOB2 EST UN TABLEAU SUR LA NOUVELLE NUMEROTATION
C =1 SI LE NOEUD EST DANS LE 2IEME MAILLGE =0 SINON
C ICLE=0 PRELIM APPELE PAR L'OPERATEUR ELIM
C ICLE=1 PRELIM APPELE PAR L'OPERATEUR VISAVIS
-INC PPARAM
-INC CCOPTIO
-INC SMELEME
      POINTEUR MELEM2.MELEME
-INC SMCOORD
      SEGMENT ICPR(nbpts)
      SEGMENT IAPOB1(nbpts)
      SEGMENT IAPOB2(nbpts)
      REAL*8 XXX,CRIT
-INC CCGEOME
-INC TMLCHA8
-INC TMCOLAC
-INC CCASSIS
      CHARACTER*8 TYPI,NOMI
C RECUPERE LES ARGUMENTS
      IF (ICLE.LE.0) THEN
          CALL QUETYP(TYPI,0,IRET)
          IF (IRET.EQ.0) THEN
C ERREUR => "Cet opérateur a encore besoin d'un opérande."
              CALL ERREUR(533)
              RETURN
          ENDIF
          IF (TYPI.NE.'MAILLAGE' .AND.
     & TYPI.NE.'ENTIER' .AND.
     & TYPI.NE.'FLOTTANT') THEN
C ERREUR => "On ne veut pas d'objet de type %m1:8"
              MOTERR(1:8)=TYPI
              CALL ERREUR(39)
              RETURN
          ENDIF
      ENDIF
      MELEME=0
      MELEM2=0
      CALL LIRREE(XXX,0,IRETOU)
      IF (IRETOU.NE.0)THEN
         CRIT=XXX
      ELSE
         CRIT=DBLE(DENSIT)/10.D0
      ENDIF
      CRIT=ABS(CRIT)
C Erreur 21 : Données incompatibles
      IF (CRIT.EQ.0.D0) CALL ERREUR(21)
      IF (IERR.NE.0) RETURN
      CALL LIROBJ('MAILLAGE',MELEME,1,IRETOU)
      IF (IERR.NE.0) RETURN
      CALL LIROBJ('MAILLAGE',MELEM2,0,IRETOU)
      IF(MELEM2.EQ.0) MELEM2=MELEME
C ON REMET DANS LA PILE LE DERNIER MAILLAGE LU (POUR DALLER QUEL)
      IF(ICLE.LE.0) CALL REFUS
      if( nbesc.ne.0) then
         mestra=imestr
         SEGACT MESTRA*MOD
          call ooofrc(1)
          call setass(1)
      endif
      SEGINI ICPR
      SEGINI IAPOB1
      SEGINI IAPOB2
C BOUCLE SUR LE PREMIER MAILLAGE REMPLI ICPR ET IAPOB1
      ITE=0
      SEGACT MELEME
      DO 2 I=1,MAX(1,LISOUS(/1))
         IF (LISOUS(/1).NE.0) THEN
            IPT1=LISOUS(I)
            SEGACT IPT1
         ELSE
            IPT1=MELEME
         ENDIF
         DO 5 K=1,IPT1.NUM(/1)
            DO 51 L=1,IPT1.NUM(/2)
               M=IPT1.NUM(K,L)
               IF (ICPR(M).EQ.0) THEN
                  ITE=ITE+1
                  ICPR(M)=ITE
               ENDIF
               IAPOB1(ICPR(M))=1
 51 CONTINUE
 5 CONTINUE
 2 CONTINUE
C BOUCLE SUR LE DEUXIEME MAILLAGE REMPLI IPCR ET IAPOB2
      SEGACT MELEM2
      DO 52 I=1,MAX(1,MELEM2.LISOUS(/1))
         IF (MELEM2.LISOUS(/1).NE.0)THEN
            IPT2=MELEM2.LISOUS(I)
            SEGACT IPT2
         ELSE
            IPT2=MELEM2
         ENDIF
         DO 45 K=1,IPT2.NUM(/1)
            DO 451 L=1,IPT2.NUM(/2)
               M=IPT2.NUM(K,L)
               IF (ICPR(M).EQ.0) THEN
                  ITE=ITE+1
                  ICPR(M)=ITE
               ENDIF
               IAPOB2(ICPR(M))=1
 451 CONTINUE
 45 CONTINUE
 52 CONTINUE
C ON DETERMINE LES POINTS SUPPORTS DES MULTIPLICATEURS DE LAGRANGE
      TYPI=' '
      K=-1
      CALL TYPFIL(TYPI,K)
      CALL CREPIL(ICOLAC,-K)
      M=1
      SEGINI MLCHA8
      MLCHAR(1)='MAILLAGE'
      CALL FILLPO(ICOLAC,MLCHA8)
      SEGSUP MLCHA8
      CALL FILLPI(ICOLAC)
      SEGACT ICOLAC
C BOUCLE SUR LES MAILLAGES ON CHERCHE LES ELEMENTS DE TYPE 22
C ("MULT")
C ON INDIQUE LEUR EXISTENCE DANS IAPOB1 AVEC LA VALEUR 2
      ITLACC=KCOLA(1)
      SEGACT ITLACC
      DO 70 L=1,ITLAC(/1)
         MELEME=ITLAC(L)
         IF (MELEME.NE.0) THEN
            SEGACT MELEME
            DO 60 LL=1,MAX(1,LISOUS(/1))
               IF (LISOUS(/1).NE.0)THEN
                  IPT1=LISOUS(LL)
                  SEGACT IPT1
               ELSE
                  IPT1=MELEME
               ENDIF
               IF (IPT1.ITYPEL .EQ. 22)THEN
                  DO 55 LLL=1,IPT1.NUM(/2)
C LE PREMIER NOEUD SUPPORTENT LES MULTIPLICATEURS
                     IF (ICPR(IPT1.NUM(1,LLL)) .NE. 0)
     $ IAPOB1(ICPR(IPT1.NUM(1,LLL)))=2
 55 CONTINUE
               ENDIF
 60 CONTINUE
         ENDIF
 70 CONTINUE
C Supprime icolac et tous ses sous-objets (ITLACC...)
      CALL SUPPIL(ICOLAC,-1)
      CALL ELIMIN(ICPR,CRIT,ITE,IAPOB1,IAPOB2,MELEME,MELEM2,ICLE)
      SEGSUP IAPOB2,IAPOB1,ICPR
      if(nbesc.ne.0) then
         mestra=imestr
         call ooofrc(0)
         call setass(0)
         SEGDES MESTRA
      endif
      END
```
## elimin.eso
```fortran
      SUBROUTINE ELIMIN(ICPR,CRIT,ITE,IAPOB1,IAPOB2,MELEME,MELEM2,ICLE)
      IMPLICIT INTEGER(I-N)
      IMPLICIT REAL*8 (A-H,O-Z)
C FUSION DES NOEUDS AYANT DES COORDONNEES TROP VOISINES
C UTILISE PAR L'OPERATEUR ELIM ICLE=0 ET PAR L'OPERATEUR VISA ICLE=1
C APPEL PRELIMINAIRE DE PRELIM QUI CREE LES TABLEAUX
C ICPR EST LA MOUVELLE NUMEROTATION
C ICPR(ANCIEN N°)= NOUVEAU N°
C ICPR(ANCIEN N°)= 0 SI LE NOEUDS N'APPARTIENT PAS AU MAILLAGE(S
C ) ARGUMENT(S)
C IAPOB1 EST UN TABLEAU SUR LA NOUVELLE NUMEROTATION
C =1 SI LE NOEUD EST DANS LE 1ER MAILLGE =0 SINON
C =2 SI LE NOEUD SUPPORTE UN MULTIPLICATEUR
C IAPOB2 EST UN TABLEAU SUR LA NOUVELLE NUMEROTATION
C =1 SI LE NOEUD EST DANS LE 2IEME MAILLGE =0 SINON
-INC PPARAM
-INC CCOPTIO
-INC SMCOORD
-INC SMLENTI
-INC SMELEME
      POINTEUR MELEM2.MELEME
      SEGMENT /STRAV/(NP1(ITF),NP2(ITF),NP3(ITF),NPI(ITF),IDCP(ITF),
     & NP4(ITF),NP5(ITF))
      SEGMENT ICPR(1)
      SEGMENT IAPOB1(1)
      SEGMENT IAPOB2(1)
      SEGMENT ITLAC(0)
      INTEGER TRUC,TRUC1,TRUC3
      G(A,B,C,D,E,F)=((A-D)*(A-D)+(B-E)*(B-E)+(C-F)*(C-F))
      SEGACT MCOORD*MOD
      IF (ITE.LE.1) RETURN
      ITF=ITE+3+1
      SEGINI STRAV
C IDCP = tableau reciproque de ICPR
      DO 250 I=1,ICPR(/1)
         IF (ICPR(I).NE.0) IDCP(ICPR(I))=I
 250 CONTINUE
      NUMNP=ITE
      PREC=CRIT
      PREC2=PREC*PREC
      NCO2=0
      DO 5 I=1,NUMNP
         NPI(I)=I
    5 CONTINUE
C APPEL DE TRISUP QUI CREE LES TABLEAUX CONTENUS DANS STRAV
      CALL TRISUP(NUMNP,PREC,NG,TRUC,TRUC1,CRIT,XMIN,YMIN,ZMIN,STRAV)
      IF (IIMPI.NE.0) WRITE (IOIMP,74) NUMNP,NG,TRUC,TRUC1
 74 FORMAT (1X,'NUMNP=',I5,2X,'NG=',I5,2X,'TRUC=',I8,2X,'TRUC1=',I8)
      KELI=0
      TRUC3=TRUC*TRUC1
      ID=NUMNP
      IA=1
      IB=ITE-1
      CRUT=1.D0/CRIT
      IF(ICLE.EQ.1) THEN
         JG=20
         SEGINI MLENTI,MLENT1
      ENDIF
      XI2=0.D0
      XI3=0.D0
C BOUCLE SUR LES POINTS DU(DES) MAILLAGE(S)
      DO 6 I=IA,IB
         IREF=IDCP(I)*(IDIM+1)-IDIM
         XI1=XCOOR(IREF)
         NX1=INT((XI1-PREC-XMIN)*CRUT+2.D0)
         NX2=INT((XI1+PREC-XMIN)*CRUT+2.D0)
         IF (IDIM.GE.2) THEN
            XI2=XCOOR(IREF+1)
            NY1=INT((XI2-PREC-YMIN)*CRUT+1.D0)*TRUC
            NY2=INT((XI2+PREC-YMIN)*CRUT+1.D0)*TRUC
         ELSE
C XI2=0
            NY1=INT(1.D0-PREC*CRUT)*TRUC
            NY2=INT(1.D0+PREC*CRUT)*TRUC
         ENDIF
         IF (IDIM.GE.3) THEN
            XI3=XCOOR(IREF+2)
            NZ1=INT((XI3-PREC-ZMIN)*CRUT+1.D0)*TRUC3
            NZ2=INT((XI3+PREC-ZMIN)*CRUT+1.D0)*TRUC3
         ELSE
C XI3=0
            NZ1=INT(1.D0-PREC*CRUT)*TRUC3
            NZ2=INT(1.D0+PREC*CRUT)*TRUC3
         ENDIF
         IC=I+1
C BOUCLE SUR LES ZONES CREE PAR TRISUP
         XJ2=0.D0
         XJ3=0.D0
         DO 7 II=NZ1,NZ2,TRUC3
            DO 71 JJ=NY1,NY2,TRUC
               NTEST1=II+JJ+NX1
               NTEST3=II+JJ+NX2
               NZON1=NTEST1/NG+1
               NZON3=NTEST3/NG+1
               ND=NP1(NZON1)+1
               NF=NP1(NZON3+1)
               IF(ND.GT.NF) GO TO 71
               DO 72 M=ND,NF
                  IF(NP3(M).LT.NTEST1) GO TO 72
                  IF(NP3(M).GT.NTEST3) GO TO 71
                  J=NP2(M)
                  IF(J.GT.ID.OR.J.LT.IC) GO TO 72
                  IREF=IDCP(J)*(IDIM+1)-IDIM
                  XJ1=XCOOR(IREF)
                  IF (IDIM.GE.2) XJ2=XCOOR(IREF+1)
                  IF (IDIM.GE.3) XJ3=XCOOR(IREF+2)
                  A=G(XI1,XI2,XI3,XJ1,XJ2,XJ3)
                  NCO2=NCO2+1
                  IF (A.GT.PREC2) GO TO 72
                  IF (NPI(J).LT.0.AND.ICLE.LE.0) GOTO 72
                  IF ((IAPOB1(I) .EQ. 2) .OR. (IAPOB1(J) .EQ. 2)) GOTO
     $ 72
                  IF (((IAPOB1(I).EQ.0).AND.(IAPOB1(J).EQ.0)).OR.
     # ((IAPOB2(I).EQ.0).AND.(IAPOB2(J).EQ.0))) GOTO
     $ 72
                  IF (IAPOB1(I).NE.0) THEN
                     IREF1=(IDCP(I)-1)*(IDIM+1)
                     IREF2=(IDCP(J)-1)*(IDIM+1)
                  ELSE
                     IREF1=(IDCP(J)-1)*(IDIM+1)
                     IREF2=(IDCP(I)-1)*(IDIM+1)
                  ENDIF
                  NPI(J)=-I
                  KELI=KELI+1
                  IF(ICLE.LE.0) THEN
C ON SOUDE LE PREMIER POINT SUR LE SECOND
                     DO 10 III=1,IDIM+1
                        XCOOR(IREF1+III)=XCOOR(IREF2+III)
 10 CONTINUE
                  ELSEIF(ICLE.EQ.1) THEN
                     IF(KELI.GT.JG) THEN
                        JG=JG+20
                        SEGADJ MLENTI,MLENT1
                     ENDIF
                     LECT(KELI)=IDCP(I)
                     MLENT1.LECT(KELI)=IDCP(J)
                  ENDIF
 72 CONTINUE
 71 CONTINUE
 7 CONTINUE
 6 CONTINUE
      IJ=0
      ICONT=0
      DO 101 I=1,NUMNP
 102 IF(NPI(I).GT.0) GOTO 101
         IJ=-NPI(I)
         NPI(I)=NPI(IJ)
         ICONT=ICONT+1
         GOTO 102
 101 CONTINUE
      IF(ICLE.LE.0) THEN
         INTERR(1) = ICONT
C Erreur -293 : Nombre de noeuds eliminés %i1
         CALL ERREUR(-293)
         DO 103 I=1,nbpts
            IPC=ICPR(I)
            IF (IPC.EQ.0)GOTO 103
            ICPR(I)=NPI(IPC)
 103 CONTINUE
         SEGSUP STRAV
         NUMNP=0
         DO 104 I=1,nbpts
            NUMNP=MAX(NUMNP,ICPR(I))
 104 CONTINUE
         SEGINI ITLAC
         IF (MELEME.NE.0) CALL AJOU(ITLAC,MELEME)
         IF (MELEM2.NE.0) CALL AJOU(ITLAC,MELEM2)
C il reste a renumeroter les coordonnes(tasser la pile des points)
C et a changer les references dans tous les objets qui pointent
C sur des noeuds
         IDONN=0
         IF(ICLE.EQ.-1) IDONN=1
         CALL TASSP2(ITLAC,ICPR,NUMNP,ICOLAC,0,IDONN)
C TASSP2 nous a cree un ICOLAC dont on n'a que faire.
C l'appel suivant supprime ICOLAC et ses sous-objets (donc ITLAC)
         CALL SUPPIL(ICOLAC,-1)
      ELSEIF(ICLE.EQ.1) THEN
         SEGSUP STRAV
         IF(KELI.NE.0) THEN
            NBELEM=KELI
            NBNN=1
            NBREF=0
            NBSOUS=0
            SEGINI IPT3,IPT2
            IPT2.ITYPEL=1
            IPT3.ITYPEL=1
            DO 105 I=1,KELI
               IPT2.NUM(1,I)=LECT(I)
               IPT3.NUM(1,I)=MLENT1.LECT(I)
 105 CONTINUE
            SEGDES IPT3,IPT2
            SEGSUP MLENTI,MLENT1
            CALL ECROBJ('MAILLAGE',IPT3)
            CALL ECROBJ('MAILLAGE',IPT2)
C Erreur 22 : Opération malvenue. Résultat douteux
            IF(ICONT.NE.KELI) CALL ERREUR(22)
         ELSE
C Erreur 26 : Tache impossible. Probablement données erronées
            CALL ERREUR(26)
         ENDIF
      ENDIF
      RETURN
      END
```
