C
C-INC CCPRECO
C

C   NBASMA : Nombre d'assistants MAXI
      PARAMETER (NBASMA=64)


C   PRENUM : tableau de pointeurs sur des maillages stockant la numerotation
      INTEGER PRENUM
      parameter (npreco=128)
      COMMON/CPRECO/PRENUM(NPRECO)

C
      INTEGER PREORI,PREPRE
      COMMON/CMPREC/PREORI(30),PREPRE(30)
      COMMON/CMPCLE/PRECLE(30)
      CHARACTER*16 PRECLE
C
C CMPREC : preconditionnement pour COMP
C associer 2 segments pour eviter de refaire certains traitements
C PREORI pointeur objet initial, PREPRE pointeur ad hoc, PRECLE etiquette
C
      parameter (nbemel=100)
      integer premel,hash1,hash2,hash3,nbso
      COMMON/CCRECH/premel(nbemel,0:NBASMA),
     &              hash1(nbemel,0:NBASMA),
     &              hash2(nbemel,0:NBASMA),
     &              hash3(nbemel,0:NBASMA),
     &              nbso(nbemel,0:NBASMA)
C
C CCRECH preconditionnement pour crechp
C premel liste des maillages, hash1 hash2 et hash3 les hash codes associes
C


C CPART6 preconditionnement pour part6 (Partitionnement des MMODEL)
C   NMOPAR : Nombre de pointeurs que l'on conserve en memoire
C   PARMOD : POINTEURS vers les MMODEL qui ont ete partitionnes
C   PESCLA : POINTEURS vers les TABLES ESCLAVES equivalentes
      PARAMETER (NMOPAR=5)
      INTEGER PARMOD,PESCLA
      COMMON/CPART6/PARMOD(NMOPAR),PESCLA(NMOPAR)


C CREDUA preconditionnement pour reduaf (Reduction de MCHAML deja fait)
C   NPREDU : Nombre de triples de pointeurs que l'on conserve en memoire par ASSISTANT
C   PRECMO : POINTEURS vers les MMODEL en entree de REDU
C   PRECM1 : POINTEURS vers les MCHELM en entree de REDU
C   PRECM2 : POINTEURS vers les MCHELM en sortie de REDU
C   PRECM3 : option de redu STRICT ou non
C   PRECM4 : Horodatage des     MMODEL en entree de REDU
C   PRECM5 : Horodatage des     MCHELM en entree de REDU
C   NBPRRE : Nombre de preconditionnements deja sauves
      PARAMETER (NPREDU=30)
      INTEGER PRECMO,PRECM1,PRECM2,PRECM3,PRECM4,PRECM5,NBPRRE
      COMMON/CREDUA/PRECMO(NPREDU,NBASMA+1),
     &              PRECM1(NPREDU,NBASMA+1),
     &              PRECM2(NPREDU,NBASMA+1),
     &              PRECM3(NPREDU,NBASMA+1),
     &              PRECM4(NPREDU,NBASMA+1),
     &              PRECM5(NPREDU,NBASMA+1),
     &              NBPRRE(NBASMA+1)


C CMOMOD preconditionnement pour extension de MMODEL (modete.eso pour l'instant)
C   NBMOMO : Nombre de MMODEL preconditionnes
C   PMOMO1 : POINTEUR MMODEL d'entree
C   PMOMO2 : POINTEUR MMODEL etendu (MODELE MELANGE PARALLELE)
      INTEGER NBMOMO,PMOMO1,PMOMO2
      COMMON/CMOMOD/NBMOMO(NBASMA+1),
     &              PMOMO1(NPREDU,NBASMA+1),
     &              PMOMO2(NPREDU,NBASMA+1)


C CREDIN preconditionnement pour reduaf (intersection des MAILLAGES)
C   NTRIPL : Nombre de triples de pointeurs que l'on conserve en memoire par ASSISTANT
C   PMAMOD : POINTEURS vers les MAILLAGES des IMODEL
C   PMAMOH : HORODATAGE     des MAILLAGES des IMODEL
C   PMACHA : POINTEURS vers les MAILLAGES des MCHAML
C   PMACHH : HORODATAGE     des MAILLAGES des MCHAML
C   PMLENT : POINTEURS vers les MLENTI    des intersections
C   NINTSA : Nombre d'intersections deja sauvees
      PARAMETER (NTRIPL=NBASMA)
      INTEGER NINTSA,PMAMOD,PMACHA,PMLENT,PMACHH,PMAMOH
      COMMON/CREDIN/NINTSA(NBASMA+1), PMAMOD(NTRIPL,NBASMA+1),
     &              PMAMOH(NTRIPL,NBASMA+1),PMACHA(NTRIPL,NBASMA+1),
     &              PMACHH(NTRIPL,NBASMA+1),PMLENT(NTRIPL,NBASMA+1)

C CACTOB preconditionnement pour ACTOBJ
      INTEGER PACTOB
      COMMON/CACTOB/PACTOB(NBASMA+1)
C CCHAME1 preconditionnement pour CHAME1
      PARAMETER (NPRCHA=5)
      CHARACTER*8 IPRCHA
      COMMON/CCHAME1/IPRMA(nprcha,0:nbasma),IPRHOA(nprcha,0:nbasma),
     >               IPRMO(nprcha,0:nbasma),IPRHOM(nprcha,0:nbasma),
     >               IPRCHP(nprcha,0:nbasma),IPRHOC(nprcha,0:nbasma),
     >               IPRSU(nprcha,0:nbasma),IPRCHL(nprcha,0:nbasma),
     >               IPRCHA(nprcha,0:nbasma)
      save /cpreco/,/cmprec/,/cmpcle/,/ccrech/,/cpart6/,/credua/
      save /cmomod/,/credin/,/cactob/,/cchame1/

