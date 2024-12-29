#ifndef FILEHANDLE_C_INCLUDED
#define FILEHANDLE_C_INCLUDED
#include "struct.h"
#include"fileHandle.h"

Entete readtete(FILE *fich)
{
    Entete e;
    rewind(fich);
    fread(&(e), sizeof(Entete), 1, fich);
    rewind(fich);
    return e;
}

void writetete(FILE *fich, Entete e)
{
    rewind(fich);
    fwrite(&e, sizeof(Entete), 1, fich);
    rewind(fich);
}

LOF *OpenFile(char *nomfichier, char mode)
{
    LOF *fich = (LOF *)malloc(sizeof(LOF));
    if (mode == 'A')
    {
        fich->fichier = fopen(nomfichier, "rb+");

        if (fich->fichier == NULL)
        {
            perror("Error opening the file in read/write mode");
            free(fich);
            return NULL;
        }

        fich->entete = readtete(fich->fichier);
    }
    else if (mode == 'N')
    {
        fich->fichier = fopen(nomfichier, "ab+");

        if (fich->fichier == NULL)
        {
            perror("Error opening the file in write mode");
            free(fich);
            return NULL;
        }

        fich->entete.nbBlok = 0;
        writetete(fich->fichier, fich->entete);
        fclose(fich->fichier);
    }
    else
    {
        printf("Incorrect open mode\n");
        free(fich);
        return NULL;
    }

    return fich;
}

TOF *OpenFilef(char *nomfi, char mode)
{
    TOF *fich = (TOF *)malloc(sizeof(TOF));

    if (mode == 'A')
    {
        fich->fi = fopen(nomfi, "rb+");

        if (fich->fi == NULL)
        {
            perror("Error opening file in read/write mode");
            free(fich);
            return NULL;
        }

        fich->entete = readtete(fich->fi);
    }
    else if (mode == 'N')
    {
        fich->fi = fopen(nomfi, "wb+");

        if (fich->fi == NULL)
        {
            perror("Error opening file in write mode");
            free(fich);
            return NULL;
        }

        fich->entete.nbBlok = 0;
        writetete(fich->fi, fich->entete);
    }
    else
    {
        printf("Incorrect opening mode\n");
        free(fich);
        return NULL;
    }

    return fich;
}
#endif // FILEHANDLE_C_INCLUDED
