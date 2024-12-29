#ifndef SUPPRESSION_C_INCLUDED
#define SUPPRESSION_C_INCLUDED
#include <string.h>
#include"suppression.h"
#include"struct.h"
#include"fileHandle.h"
#include"insertion.h"

void deleteInformation(IndexTable *tabs, char *filename, int codeToDelete) {
    bool found = false;
    int blockNum = -1;
    int index = -1;

    for (int i = 0; i < tabs->NbrEID; i++) {
        int c = atoi(tabs->EID[i].cle);
        if (c == codeToDelete) {
            found = true;
            blockNum = tabs->EID[i].ad->i;
            index = i;
            break;
        }
    }

    if (found) {
        bloc_information block;
        if (read_blocInformation(filename, blockNum, &block) == 1) {
            for (int i = 0; i < block.nb; i++) {
                if (block.donne[i].code == codeToDelete) {
                    for (int j = i; j < block.nb - 1; j++) {
                        block.donne[j] = block.donne[j + 1];
                    }
                    block.nb--;

                    write_blocInformation(filename, blockNum, &block);

                    LOF *lof = OpenFile(filename , 'A') ;
                    if (block.nb == 0) {
                        for (int k = blockNum + 1; k <= lof->entete.nbBlok; k++) {
            bloc_information nextBlock;
            if (read_blocInformation(filename, k, &nextBlock) == 1) {
                write_blocInformation(filename, k - 1, &nextBlock);
                            }
                        }
                        lof->entete.nbBlok--;
                        writetete(filename, lof->entete);
                        fclose(lof->fichier);
                    }

                    for (int k = index; k < tabs->NbrEID - 1; k++) {
                        tabs->EID[k] = tabs->EID[k + 1];
                    }
                    tabs->NbrEID--;

                    writeIndexTableToFile("indexI.txt", tabs);

                    printf("information with code %d deleted.\n", codeToDelete);
                    return;
                }
            }
        }
    }

    printf("information  with code %d not found.\n", codeToDelete);
}



void suprition_phisique(char *filename , bl_index *Idx ,char fname[] ,char *indexF )
{
    TOF *tof;

     bloc_information found;

     blocfile bloc;
     bool Trouv;
     int y ;

     RechercherIndex(Idx,fname , &y , &Trouv);
     readbloc(filename ,Idx->idx[y].ad->i ,&bloc);

     for (int k = 0 ; k < bloc.nbfile ; k++)
     {
         if (strcmp(bloc.file[k].filename,fname)== 0)
         {
             for (int j = k; j < bloc.nbfile - 1;j++)
             {
                 bloc.file[j] = bloc.file[j+1];
             }
             bloc.nbfile--;
         }
     }
     writebloc(filename ,Idx->idx[y].ad->i , &bloc );
     tof = OpenFile(filename , 'A') ;
     if (bloc.nbfile == 0) {
        for (int k = Idx->idx[y].ad->i; k <= tof->entete.nbBlok; k++) {
            blocfile nextBlock;
            if (readbloc(filename, k, &nextBlock) == 1) {
                writebloc(filename, k - 1, &nextBlock);
            }
        }
        tof->entete.nbBlok--;
        writetete(filename, tof->entete);
        fclose(tof->fi);
     }
     for (int k = y ; k < Idx->nb_index - 1 ; k++)
     {
         Idx->idx[k] = Idx->idx[k+1];
     }
     Idx->nb_index--;
     WriteIndexToFile(&Idx,indexF) ;

}

void logicalDeleteInforamtion(IndexTable *tabs, char *filename, int codeToDelete) {
    bool found = false;
    int blockNum = -1;
    int index = -1;

    for (int i = 0; i < tabs->NbrEID; i++) {
        int c = atoi(tabs->EID[i].cle);
        if (c == codeToDelete) {
            found = true;
            blockNum = tabs->EID[i].ad->i;
            index = i;
            break;
        }
    }

    if (found) {

        bloc_information block;
        if (read_blocInformation(filename, blockNum, &block) == 1) {
            for (int i = 0; i < block.nb; i++) {
                if (block.donne[i].code == codeToDelete) {
                    block.donne[i].isDeleted= true;
                    write_blocInformation(filename, blockNum, &block);

                    printf("information with code %d logically deleted.\n", codeToDelete);
                    return;
                }
            }
        }
    }

    printf("information with code %d not found.\n", codeToDelete);
}





void updateField (char *fichs  , bl_index *Idx  , char fname[] , char fn[] , const char *field , char *filename )
{
    TOF *tof = OpenFilef(fichs , 'A');

    blocfile bloc;

    bloc_information blocf ;

    bool Trouv;
    int y ;

     RechercherIndex(Idx,fname , &y , &Trouv);

     if(Trouv){

     readbloc(fichs ,Idx->idx[y].ad->i ,&bloc);

     read_blocInformation(filename , Idx->idx[y].ad->i , &blocf);

     for (int k = 0 ; k < bloc.nbfile ; k++)
     {
         if (strcmp(bloc.file[k].filename,fname)== 0)
         {
             if (strcmp(field, "fname") == 0) {

                          sprintf(bloc.file[k].filename , "%s" , fn) ;

                          int n = strlen(fn);

                          sprintf (Idx->idx[y].key ," %d %s" , n , fn);


             }else if (strcmp(field, "ext") == 0) {

                    sprintf (bloc.file[k].extention , "%s" , fn);

             }
         }
         break;
     }
     writebloc(fichs ,Idx->idx[y].ad->i , &bloc );

     read_blocInformation(filename , Idx->idx[y].ad->i , &blocf);

     for (int k = 0 ; k < blocf.nb; k++)
     {
         if (strcmp(blocf.donne[k].f.filename,fname)== 0)
         {
             if (strcmp(field, "fname") == 0) {

                          sprintf(blocf.donne[k].f.filename , "%s" , fn) ;

             }else if (strcmp(field, "ext") == 0) {

                    sprintf (blocf.donne[k].f.extention , "%s" , fn);

             }
         }
     }

     write_blocInformation(filename , Idx->idx[y].ad->i , &blocf);
     }

     fclose(tof->fi);

}


#endif // SUPPRESSION_C_INCLUDED
