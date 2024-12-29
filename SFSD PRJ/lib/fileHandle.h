#ifndef FILEHANDLE_H_INCLUDED
#define FILEHANDLE_H_INCLUDED
#include "struct.h"

Entete readtete(FILE *fich);
void writetete(FILE *fich, Entete e);
LOF *OpenFile(char *nomfichier, char mode);
TOF *OpenFilef(char *nomfi, char mode) ;


#endif // FILEHANDLE_H_INCLUDED
