*=======================================================================        
*                                                                               
*     -INC SMLOBJE
*
*     OBJET "LISTOBJE" : LISTE D'OBJETS DE MEME TYPE
*                                                                               
*     DATA DES TYPES D'OBJET POSSIBLES
      PARAMETER   (NTYPOB = 37)
      CHARACTER*8 LTYPOB(NTYPOB)
      DATA LTYPOB /'--------','ENTIER  ','--------','--------',
     $             'MAILLAGE','LISTENTI','POINT   ','LISTREEL',
     $             'CHPOINT ','RIGIDITE','        ','STRUCTUR',
     $             'ATTACHE ','SOLUTION','BASEMODA','LISTOBJE',
     $             '--------','VECTDOUB','LISTMOTS','DEFORME ',
     $             'LISTCHPO','CHARGEME','EVOLUTIO','--------',
     $             'VECTEUR ','TABLE   ','--------','ELEMSTRU',
     $             'BLOQSTRU','MCHAML  ','MMODEL  ','--------',
     $             'NUAGE   ','MATRIK  ','OBJET   ','ESCLAVE ',
     $             'ANNOTATI'/
* 
      SEGMENT,MLOBJE
         CHARACTER*8 TYPOBJ
         INTEGER     LISOBJ(NOBJ)
      ENDSEGMENT                                                                
      POINTEUR MLOBJ1.MLOBJE, MLOBJ2.MLOBJE, MLOBJ3.MLOBJE                      
*                                                                               
*     TYPOBJ : TYPE DES OBJETS CONTENUS DANS LA LISTE
*     LISOBJ : POINTEURS SUR DES OBJETS DE TYPE "TYPOBJ"
*                                                                               
*=======================================================================        
