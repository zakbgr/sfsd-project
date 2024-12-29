#ifndef INSERTION_C_INCLUDED
#define INSERTION_C_INCLUDED
#include "insertion.h"
#include "struct.h"
#include "fileHandle.h"
#include "index.h"

void RechercherInformation(char* nomfichier, int coder, bool* Trouv, int* i, int* j) {
    LOF* lof;
    *Trouv = false;

    lof = OpenFile(nomfichier, 'A');

    *i = 1;
    *j = -1;

    while (*i <= lof->entete.nbBlok && !*Trouv) {
        *j = -1;
        bloc_information bloc;

        if (read_blocInformation(nomfichier, *i, &bloc) == 1) {
            int x = 0;
            int y = bloc.nb - 1;

            while (x <= y) {
                *j = (x + y) / 2;

                if (bloc.donne[*j].code== coder) {
                    *Trouv = true;
                    fclose(lof->fichier);
                    return;
                } else {
                    if (bloc.donne[*j].code< coder) {
                        x = *j + 1;
                        if (x > y) {
                            *j = -1;
                        }
                    } else {
                        y = *j - 1;
                    }
                }
            }
        }

        (*i)++;
    }

    if (!lof->entete.nbBlok) {
        *i = 0;
    } else if (*i > lof->entete.nbBlok) {
        *i = lof->entete.nbBlok;
    }

    fclose(lof->fichier);
}

int read_blocInformation(char *nomfichier, int i, bloc_information *bloc){
    LOF *lof;
    lof = OpenFile(nomfichier, 'A');

    fseek(lof->fichier, sizeof(Entete) + (i - 1) * sizeof(bloc_information), SEEK_SET);

    fread(&(bloc->nb), sizeof(int), 1, lof->fichier);

    for (int j = 0; j < bloc->nb; j++)
    {
        fread(&(bloc->donne[j]), sizeof(information), 1, lof->fichier);
    }

    if (bloc->nb == 0)
    {
        fclose(lof->fichier);
        return 0;
    }

    fclose(lof->fichier);
    return 1;
}


void InsererInformation(IndexTable * tab ,char *nomfichier, int coder, char datearr[], char datedep[] ,Fichier f)

{
    bool Trouv;
    int i, j;
    LOF *lof;
    information r;
    r.code = coder;
    strcpy(r.datecreation, datearr);
    strcpy(r.datelast, datedep);
    r.isDeleted = false ;
    r.f =f ;


    RechercherInformation(nomfichier, coder, &Trouv, &i, &j);

    if (!Trouv)
    {
        lof = OpenFile(nomfichier, 'A');

        bloc_information bloc;
            // Read the existing block
            if(i>=0)
                {
                        read_blocInformation(nomfichier, i, &bloc);
                }

         if (bloc.nb < MAX && lof->entete.nbBlok !=0 )
        {
            if (j != -1)
            {
                // Shift elements to make space for the new reservation
                for (int x = bloc.nb; x > j; x--)
                {
                    bloc.donne[x] = bloc.donne[x - 1];
                }
                bloc.donne[j] = r;
                bloc.nb++;
            }
            else
            {
                // Insert the new reservation at the end of the block
                bloc.donne[bloc.nb] = r;
                j=bloc.nb ;
                i=lof->entete.nbBlok ;
                bloc.nb++;
            }
             fillIndexTable(tab,r.code,lof->entete.nbBlok) ;
            write_blocInformation(nomfichier, i, &bloc);
        }
        else
        {
            // Create a new block
            fclose(lof->fichier);
            lof = OpenFile(nomfichier, 'A');

            bloc_information newbloc;
            newbloc.donne[0] = r;
                            j=bloc.nb ;
                i=lof->entete.nbBlok ;
            newbloc.nb = 1;
            lof->entete.nbBlok++;

            printf("Creating a new block  %d \n",lof->entete.nbBlok);
            writetete(lof->fichier, lof->entete);

            fillIndexTable(tab,r.code,lof->entete.nbBlok) ;
            if (bloc.nb > 0)
            {
                // If there are existing blocks, write to the new block and update the header
                write_blocInformation(nomfichier, lof->entete.nbBlok, &newbloc);
                fclose(lof->fichier);
            }
            else
            {
                // If there are no existing blocks, write to the first block
                write_blocInformation(nomfichier, 1, &newbloc);
            }
        }
//  printf("\n [code i / j == %d %d / %d ]\n ",coder , i,j) ;
        fclose(lof->fichier);
    }
}



void write_blocInformation(char *nomfichier, int i, bloc_information *bloc)
{
    LOF *lof;
    lof = OpenFile(nomfichier, 'A');

    fseek(lof->fichier, sizeof(Entete) + (i - 1) * sizeof(bloc_information), SEEK_SET);
    fwrite(&bloc->nb, sizeof(int), 1, lof->fichier);

    for (int j = 0; j < bloc->nb; j++)
    {fwrite(&bloc->donne[j], sizeof(information), 1, lof->fichier);}
    fclose(lof->fichier);
}




void SortAllBlocks(char* nomfichier) {
    LOF* lof;
    lof = OpenFile(nomfichier, 'A');

    int numBlocks = lof->entete.nbBlok;

    for (int i = 1; i <= numBlocks; i++) {
        bloc_information bloc;

        if (read_blocInformation(nomfichier, i, &bloc) == 1) {
            // Use insertion sort to sort the reservations within the block
            for (int j = 1; j < bloc.nb; j++) {
                information key = bloc.donne[j];
                int k = j - 1;

                while (k >= 0 && bloc.donne[k].code > key.code) {
                    bloc.donne[k + 1] = bloc.donne[k];
                    k--;
                }

                bloc.donne[k + 1] = key;
            }

            // Write the sorted block back to the file
            write_blocInformation(nomfichier, i, &bloc);
        }
    }

    fclose(lof->fichier);
}


//// @ fichier codes



void cerrefile(char *nomfi, char filename[], char extention[], bl_index *Idx ,Fichier *f ,int code)
{
    bool existe;
    int i, j;
    TOF *tof;
    Fichier fch;
    strcpy(fch.filename, filename);
    strcpy(fch.extention, extention);
    fch.code = code ;

    Rechercherfile(nomfi, filename, &existe, &i, &j , code);

    if (!existe)
    {
        tof = OpenFilef(nomfi, 'A');
        blocfile bloc;

        if (i >= 0)
        {
            readbloc(nomfi, i, &bloc);

        }
        if (bloc.nbfile < MAX &&  tof->entete.nbBlok !=0)
        {

            if (j != -1)
            {
                for (int x = bloc.nbfile; x > j; x--)
                {
                    bloc.file[x] = bloc.file[x - 1];
                }
                bloc.file[j] = fch;
                bloc.nbfile++;
                *(f) = fch;
            }
            else
            {
                bloc.file[bloc.nbfile] = fch;
                bloc.nbfile++;
                *f = fch;
            }

            //InsererInformation(tab,informationf, coder,datearr, datedep ,fch);
            InsererIndex(filename,tof->entete.nbBlok, Idx);
            writebloc(nomfi, i, &bloc);
        }
        else
        {
            fclose(tof->fi);
            tof = OpenFilef(nomfi, 'A');
            blocfile newbloc;
            newbloc.file[0] = fch;
            newbloc.nbfile = 1;
            *f = fch;
            tof->entete.nbBlok++;
            writetete(tof->fi, tof->entete);

            //InsererInformation(tab,informationf, coder,datearr, datedep , fch);
            InsererIndex(filename,tof->entete.nbBlok, Idx);
            if (bloc.nbfile > 0)
            {
                writebloc(nomfi, 1, &newbloc);
            }
            else
            {
                writebloc(nomfi, tof->entete.nbBlok, &newbloc);
                fclose(tof->fi);
            }
        }
        fclose(tof->fi);
    }
}



void Rechercherfile(char *nomfichier, char filename[], bool *Trouv, int *i, int *j , int code)
{
    TOF *tof;
    *Trouv = false;

    tof = OpenFilef(nomfichier, 'A');

    *i = 1; //
    *j = -1; //

    while (*i <= tof->entete.nbBlok && !*Trouv)
    {
        *j = -1; //
        blocfile bloc;

        if (readbloc(nomfichier, *i, &bloc) == 0)
        {
            break;
        }

        for (int x = 0; x < bloc.nbfile; x++)
        {
            *j = x ;
            if (strcmp(filename , bloc.file[x].filename) == 0 || bloc.file[x].code == code )
            {
                *Trouv = true;
                fclose(tof->fi);
                return;
            }
        }
        (*i)++;
    }

    if (!tof->entete.nbBlok)
        *i = 1;/////
    else if (*i > tof->entete.nbBlok)
        *i = tof->entete.nbBlok;

    fclose(tof->fi);
}





int readbloc(char *nomfichier, int i, blocfile *bloc)
{
    TOF *tof;
    tof = OpenFilef(nomfichier, 'A');

    fseek(tof->fi, sizeof(Entete) + (i - 1) * sizeof(blocfile), SEEK_SET);

    fread(&bloc->nbfile, sizeof(int), 1, tof->fi);

    for (int j = 0; j < bloc->nbfile; j++)
    {
        fread(&bloc->file[j], sizeof(Fichier), 1, tof->fi);
    }

    if (bloc->nbfile == 0)
    {
        fclose(tof->fi);
        return 0;
    }

    fclose(tof->fi);
    return 1;
}

void writebloc(char *nomfi, int i, blocfile *bloc)
{
    TOF *tof;
    tof = OpenFilef(nomfi, 'A');

    fseek(tof->fi, sizeof(Entete) + (i - 1) * sizeof(blocfile), SEEK_SET);
    fwrite(&bloc->nbfile, sizeof(int), 1, tof->fi);

    for (int j = 0; j < bloc->nbfile; j++)
    {
        fwrite(&bloc->file[j], sizeof(Fichier), 1, tof->fi);
    }

    fclose(tof->fi);
}




void SortAllBlockfiche(char* nomfichier , blocfile *bloc) {

    for (int j = 0 ; j < bloc->nbfile - 1 ; j++)
    {
         for (int k = 0 ; k < bloc->nbfile - j ; k++)
         {
             if (strcmp(bloc->file[k].filename , bloc->file[k+1].filename) == 0)
             {
                 Fichier f = bloc->file[k];
                 bloc->file[k] = bloc->file[k+1];
                 bloc->file[k+1]=f;
             }
         }
    }
}

#endif // INSERTION_C_INCLUDED
