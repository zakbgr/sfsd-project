#ifndef INDEX_H_INCLUDED
#define INDEX_H_INCLUDED
void freeIndexTable(IndexTable* table);
void readIndexTableFromFile(const char* filename, IndexTable* table)  ;
void TriIndexTable(IndexTable* table) ;
void fillIndexTable(IndexTable* table, int code, int nbrbloc) ;
void writeIndexTableToFile(const char* filename, IndexTable* table) ;
void reserchIndex(IndexTable * tab , char* namefile , int codeserch  ,information *ind , int *pose ) ;
void updateindex(char * filenameindex , int oldcode , char* newcode) ;
void InsererIndex(char filename[], int i, bl_index *Idx);
void recherchAvecIndeInFILE(IndexTable *tabs, char* infor, int k, information *foundinformation, int *b) ;
void RechercherIndex(bl_index *dx, char filename[], int *y, bool *Trouv);
Fichier rechfileIndex(char *nomfichier , char fn[] , bl_index *Idx);
void WriteIndexToFile(bl_index *x,  char *filename) ;
void ReadIndexFromFile(bl_index *x,  char *filename)  ;
#endif // INDEX_H_INCLUDED
