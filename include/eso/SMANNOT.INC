*     -INC SMANNOT                                                      
*                                                                               
*     OBJET DE TYPE ANNOTATION (ANNOTATI)                                                     
*                      
*     SEGMENT CHAPEAU DE L'ANNOTATION
*      => ICLAS(I) : DESIGNE LA CLASSE DE LA I-EME ANNOTATION
*      => ISEGT(I) : DESIGNE LE POINTEUR VERS LE I-EME SEGMENT
      SEGMENT MANNOT                                           
          INTEGER ICLAS(NBANNO)
          INTEGER ISEGT(NBANNO)          
      ENDSEGMENT                                                                
      POINTEUR MANNO1.MANNOT,MANNO2.MANNOT,MANNO3.MANNOT                        
*
*     ICLAS(I)=1  --->  CLASSE "CATEGORIE"
*      => ICLRC : DESIGNE LE NUMERO DE LA COULEUR DANS LA LISTE NCOUL
*      => TXCAT : CONTIENT LE TEXTE AFFICHE DANS LA LEGENDE
      SEGMENT MCATEG                               
          INTEGER            ICLRC
          CHARACTER*(LOCHAI) TXCAT
      ENDSEGMENT            
      POINTEUR MCATE1.MCATEG,MCATE2.MCATEG,MCATE3.MCATEG
*
*     ICLAS(I)=2  --->  CLASSE "ETIQUETTE"
*      => INUPT : POINTEUR MELEME CONTENANT LE POINT SUPPORT DE L'ETIQUETTE 
*                 TRAC >> si le noeud est deplace, alors l'etiquette suivra
*                 DESS >> seules les coordonnees X et Y sont utiles
*      => ICLRE : DESIGNE LE NUMERO DE LA COULEUR DANS LA LISTE NCOUL
*      => KPOSI : INDIQUE OU EST DESSINEE L'ETIQUETTE PAR RAPPORT A INUPT
*                  1=SO 
*                  2=S 
*                  3=SE 
*                  4=O 
*                  5=C 
*                  6=E 
*                  7=NO 
*                  8=N 
*                  9=NE (cf pave numerique)
*      => DEPOR : INDIQUE LA DISTANCE ENTRE IPOIN ET LA POSITION
*                 DE L'ETIQUETTE (coin inf droit si KPOSI=NO, centre si KPOSI=C...)
*      => BLIEN : INDIQUE DE TRACER UN LIEN SI DEPOR>0
*      => TXETI : CONTIENT LE TEXTE DE L'ETIQUETTE
      SEGMENT METIQU                           
          INTEGER            INUPT
          INTEGER            ICLRE
          INTEGER            KPOSI
          REAL*8             DEPOR
          LOGICAL            BLIEN
          CHARACTER*(LOCHAI) TXETI
      ENDSEGMENT
      POINTEUR METIQ1.METIQU,METIQ2.METIQU,METIQ3.METIQU                        
*
