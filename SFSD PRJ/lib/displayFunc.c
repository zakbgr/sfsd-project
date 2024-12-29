#ifndef DISPLAYFUNC_C_INCLUDED
#define DISPLAYFUNC_C_INCLUDED
#include"displayFunc.h"
#include "struct.h"
#include"fileHandle.c"


void affchTabindex(char* indexfile){
 IndexTable* tab = (IndexTable*)malloc(sizeof(IndexTable));
 readIndexTableFromFile(indexfile,tab) ;
         printf("affichage bloc index :\n") ;
    for(int s= 0 ; s<tab->NbrEID ; s++){
        printf( "\n  [code :  %s       bloc:  %d ]  ",tab->EID[s].cle , tab->EID[s].ad->i) ;
    }
freeIndexTable(tab) ;
}


void blocaffich(char* filename){
LOF* lof =OpenFile(filename, 'A') ;

    int numBlocks = lof->entete.nbBlok;

    for (int i = 1; i <= numBlocks; i++)
    {
        bloc_information bloc;

        if (read_blocInformation(filename, i, &bloc) == 1)
        {
            printf("Block %d:\n", i);
            affich_blocinformation(bloc);
        }
    }
    fclose(lof->fichier) ;

}
void affichinformation(information r)
{
    printf("\n [ %d %s %s %s %s %s]", r.code, r.datelast, r.datecreation,r.isDeleted ? "true" : "false" ,r.f.filename , r.f.extention);
}

void affich_blocinformation(bloc_information bloc)
{
    printf("information  block::\n");
printf("\n code  dateC  dateL IsDeleted      \n ") ;
    for (int j = 0; j < bloc.nb; j++)
    {
        affichinformation(bloc.donne[j]);
    }

    printf("\n");
}



void affichfile(Fichier fich)
{
    printf("file:[ %s %s ]\n", fich.filename, fich.extention);
}

void affichbloc(blocfile bloc)
{
    printf("file block:\n");

    for (int j = 0; j < bloc.nbfile; j++)
    {
        affichfile(bloc.file[j]);
    }

    printf("\n");
}


#endif // DISPLAYFUNC_C_INCLUDED
