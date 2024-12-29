#ifndef SUPPRESSION_H_INCLUDED
#define SUPPRESSION_H_INCLUDED
#include "struct.h"


void suprition_phisique(char *filename , bl_index *Idx ,char fname[] ,char *indexF );
void deleteInformation(IndexTable *tabs, char *filename, int codeToDelete );
void logicalDeleteInforamtion(IndexTable *tabs, char *filename, int codeToDelete) ;
void updateField (char *fichs  , bl_index *Idx  , char fname[] , char fn[] , const char *field , char *filename ) ;
void updateF(int code , char* filename , Fichier bloc, int nbrbloc );
#endif // SUPPRESSION_H_INCLUDED
