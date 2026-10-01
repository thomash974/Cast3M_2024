c       nombre de parametres modele de base FLUENDO3D sans renforts
        integer NB_PARA_FLUENDO3D,NB_PARA_SUPP_FLUENDO3D       
        parameter(NB_PARA_FLUENDO3D=95)       
c       nombre de parametre supplementaires 
c       debut romain
        integer NB_PARA_FIBRE_U,NB_PARA_FIBRE_C,NB_PARA_FIBRE3D
c       nombre de param fibres utilisateur
        parameter (NB_PARA_FIBRE_U=27)      
c       nombre de param fibres calcules preconstruction cprefibr (appelé par matcar)
        parameter (NB_PARA_FIBRE_C=84)
        parameter (NB_PARA_FIBRE3D=NB_PARA_FIBRE_U+NB_PARA_FIBRE_C)
c       fin romain  
        parameter(NB_PARA_SUPP_FLUENDO3D=NB_PARA_FIBRE3D)

c       nombre de variables locales pour la matrice
        integer NB_VARI_FLUENDO3D,NB_VARI_SUPP_FLUENDO3D
        parameter(NB_VARI_FLUENDO3D=152) 
c       ROMAIN 
c       nombre de variables pour le modèle de fibres ( ce nombre doit
c       etre le meme dans cfluendo3 et egal nvarfib dans fluendo3d)
        integer NB_VARI_FIBRE3D
        parameter(NB_VARI_FIBRE3D=54)
c        fin ROMAIN       
c       nombre de variables internes rajoutees pour option du modele     
        parameter(NB_VARI_SUPP_FLUENDO3D=NB_VARI_FIBRE3D)  
