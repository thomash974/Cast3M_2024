C        -INC CCREDLE
C
C    BUFFER,POINTEUR COURANT,FIN DIRECTIVE
C     Cet include fonctionne avec redlec.eso (inired.eso eventuellement)
      COMMON/CREDLE/IREDLE
      SAVE  /credle/

C     LOCHAI dans PPARAM.INC
      SEGMENT SREDLE
       CHARACTER*(LOCHAI) TEXT,MOT
       REAL*8 FLOT
       LOGICAL BOOL,SEPARA
       INTEGER IRE,NFIX,NCAR,NRAN,ICOUR
       INTEGER IPREC,IPOS,IDPAR,IFPAR,ILU,IFINAN
C      INTEGER NBCART

C      Entrees a definir
C        TEXT    : Chaine de caratere contenant ce qui doit etre analyse
C        SEPARA  : Si VRAI on considere + et - et . comme des mots
C                  Si FAUX ils sont interpretes pour les FLOTTANTS (ex : 1.0E+03)
C        NRAN    : 1 caractere avant le premier caractere de TEXT a analyser
C        ICOUR   : dernier caractere de TEXT a analyser
C
C      Resultats en sortie
C        IRE     : Entier donnant le type a recuperer 0 si on n'a rien lu
C                  Lire dans les variables suivantes en fonction de la valeur de IRE
C          IRE=0 : Rien n'a ete lu
C          IRE=1 : Lire NFIX (Type 'ENTIER')
C          IRE=2 : Lire FLOT (Type 'FLOTTANT')
C          IRE=3 : Lire MOT  (Type 'MOT')
C          IRE=4 : Lire MOT  (Type 'TEXTE')
C          IRE=5 : Lire BOOL (Type 'LOGIQUE')
C          IRE=6 : Lire MOT  (Separateur '.' dans les objets de type 'MOT')
C          IRE=7 : Lire MOT  (Separateur '%' dans les objets de type 'OBJETS')
C
C        NCAR   : Nombre de caracteres dans MOT
C
C      Utile pour le lecteur GIBIANE
C        IPREC  : Sert dans le lecteur gibiane
C        IPOS   : Sert dans le lecteur gibiane
C        IDPAR  : Sert dans le lecteur gibiane
C        IFPAR  : Sert dans le lecteur gibiane
C        ILU    : Sert dans le lecteur gibiane
C        IFINAN : Sert dans le lecteur gibiane

C      Plus utile
C        NBCART : Plus utile
      ENDSEGMENT

