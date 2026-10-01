C      -INC PPARAM
C
C     Dans cet include se trouve les parametres fixes de Cast3M
C
C     Ameliorations a venir :
C      - Mettre la longueur des NOMS d'objets : LONOM  dans CCNOYAU
C      - Mettre la longueur des constituants  : NCONCH dans SMCHAML
C                                             : LCONMO dans SMMODEL
C      - Mettre la longueur des composantes   : *8     dans SMCHAML  (OK 2020)
C                                             : *4     dans SMCHPOI  (MSOUPO)
C                                             : *8     dans SMMODEL  (NOMID )
C                                             : *4     dans TMMTRAV  (MTRAV )
C                                             : *8     dans DECHE
C                                             : *4     pour les LISTMOTS (pas en dur dans l'include JGN=4 avant les SEGINI)
C      - Mettre la longueur des formulations  : *16    dans SMMODEL  (IMODEL)
C      - Mettre la longueur des erreurs       : *120   dans CCOPTIO
C

C     LOCHAI: Longueur des chaines de caractere
      PARAMETER (LOCHAI=512)

C     LOCOMP: Longueur des noms des composantes de chamelem
C     LOCHPO: Longueur des noms de composantes de champoin
      PARAMETER (LOCOMP=8)
      PARAMETER (LOCHPO=8)

C     FORMATS pour lire les chaines : 
C       FMCHAI : chaines de taille LOCHAI (initialisation dans bdata.eso)
C       FMCOMP : chaines de taille LOCOMP (initialisation dans bdata.eso)
      COMMON/CCHAIN/FMCHAI,FMCOMP
      save /cchain/
      CHARACTER*(6) FMCHAI
      CHARACTER*(4) FMCOMP



