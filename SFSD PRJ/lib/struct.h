#ifndef STRUCT_H_INCLUDED
#define STRUCT_H_INCLUDED

#define MAX 5

typedef struct adress
{
    int i;
} adress;

typedef struct index
{
    char *key;
    adress *ad;
} index;
typedef struct bl_index
{
    index idx[100];
    int nb_index;
} bl_index;

typedef struct Fichier
{
    char filename[20];
    char extention[20];
    int code;
} Fichier;

typedef struct blocfile
{
    Fichier file[MAX];
    int nbfile;
} blocfile;





typedef struct Entete {
    int nbBlok;
} Entete;

typedef struct TOF
{
    FILE *fi;
    Entete entete;
} TOF;


typedef struct LOF {
    FILE *fichier;
    Entete entete;
} LOF;

typedef struct information{
char datecreation[20] ;
char datelast[20] ;
int code ;
bool isDeleted ;
Fichier f ;
}information;

typedef struct bloc_information{
information donne[MAX] ;
int nb ;
}bloc_information;

typedef struct {
    int i;
} Address;

typedef struct {
    char* cle;
    Address* ad;
} IndexEntry;

typedef struct {
    IndexEntry EID[100];
    int NbrEID;
} IndexTable;

#endif // STRUCT_H_INCLUDED
