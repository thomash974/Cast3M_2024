*-INC SILICRE
* segment decrivant un stockage creu de la matrice
*
      segment ilicre
*  stockage matrice initiale en creux
*  ilideb position debut de ligne dans ligcre
        integer ilideb(nbinc+1)
        integer ligcrp
      endsegment
      segment ligcre
*  lmatr: longueur reelle ligne
*  posm: numero inconnue
*  valm: valeur terme
        integer posm(lmat)
        real*8 valm(lmat)
      endsegment
