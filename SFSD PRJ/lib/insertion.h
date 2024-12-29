#ifndef INSERTION_H_INCLUDED
#define INSERTION_H_INCLUDED


int read_blocInformation(char *nomfichier, int i, bloc_information *bloc);
void write_blocInformation(char *nomfichier, int i, bloc_information *bloc);
void InsererInformation(IndexTable * tab ,char *nomfichier, int coder, char datearr[], char datedep[] ,Fichier f);
void RechercherInformation(char *nomfichier, int coder, bool *Trouv, int *i, int *j);
void SortAllBlocks(char* nomfichier);
void cerrefile(char *nomfi, char filename[], char extention[], bl_index *Idx ,Fichier *f ,int code) ;
void Rechercherfile(char *nomfichier, char filename[], bool *Trouv, int *i, int *j , int code );
int readbloc(char *nomfi, int i, blocfile *bloc);
void writebloc(char *nomfichier, int i, blocfile *bloc);
void SortAllBlockfiche(char* nomfichier , blocfile *bloc) ;
#endif // INSERTION_H_INCLUDED
