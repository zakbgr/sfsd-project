#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include"lib\struct.h"
#include"lib\insertion.h"
#include"lib\insertion.c"
#include"lib\index.c"
#include"lib\index.h"
#include"lib\displayFunc.h"
#include"lib\displayFunc.c"
#include"lib\fileHandle.c"
#include"lib\fileHandle.h"
#include"lib\suppression.h"
#include"lib\suppression.c"

void clearScreen() {
    #ifdef _WIN32 // For Windows

        system("cls");

    #else // For Unix-based systems
        system("clear");
    #endif
}
void read(IndexTable *tab , char * filename){
readIndexTableFromFile(filename , tab)  ;
}
int main ()
{

   char fname[20];
   char ext[10];
   char creation[20];
   char last [20];
   int code ;


    char name[20];
    char faeidl[10];
    int b ;

    bool Trouv ;
int i, j ;
    blocfile bloc ;
      char* fichs = "ficheFile.txt";
      char* filename = "information.txt";
      char* indexI = "indexI.txt";
      char* indexF = "indexF.txt";
      bl_index x ;
      x.nb_index = 0 ;

    information info;
    Fichier f ;
      IndexTable* tab = (IndexTable*)malloc(sizeof(IndexTable));

      LOF *lof = OpenFile(filename , 'N');
      TOF *tof = OpenFilef(fichs , 'N');

      ReadIndexFromFile(&x , indexF);
      readIndexTableFromFile(indexI , tab);
printf("tab %d ----  ", tab->NbrEID) ;
printf("x %d ",x.nb_index) ;

      int choice ;
    do{
      printf("0 - exite : \n 1 - insert File \n 2 - physical delete \n 3- logical delete \n 4- modify \n 5- recherche File \n 6 - display all File \n ENTRE YOU CHOICE ::");
      scanf("%d" , &choice);
      if (choice != 6 ) {
            clearScreen();
      }
   ReadIndexFromFile(&x , indexF);
   readIndexTableFromFile(indexI , tab);
   switch (choice) {
    case 0:
          printf ("Fin de programme !!");
        break;
    case 1:
            printf ("entre the file name ::");

   scanf("%s",fname);

   printf("entre the extention::");

   scanf("%s" , ext);

   printf ("entre the code::");

   scanf("%d" , &code);

   printf ("entre date de creation::");

   scanf("%s" , creation);

   printf ("entre date of last modification::");

   scanf("%s" , last);

   cerrefile(fichs , fname  , ext , &x ,&f , code);
   InsererInformation(tab , filename ,code , creation , last ,f);
   WriteIndexToFile(&x,indexF) ;
printf("tab %d ----  ", tab->NbrEID) ;
   writeIndexTableToFile(indexI,tab) ;

        break;
    case 2:
b=0 ;
    printf ("give me the name that you would delete ::");

    scanf("%s" , fname);

    RechercherIndex(&x , fname , &b , &Trouv);

if(b==0 )
    {
        b++;
    }

    readbloc(fichs ,b,&bloc);

    printf("\n b-----------------%d \n ",b) ;

    for (int i = 0 ; i < bloc.nbfile ; i++)
    {
        if (strcmp(bloc.file[i].filename , fname) == 0)
        {
            printf("\n-------------------------------------------i == %d \n ", i ) ;
              deleteInformation(tab ,filename ,bloc.file[i].code);
            suprition_phisique(fichs , &x , bloc.file[i].filename ,indexF) ;
        }

    }
       WriteIndexToFile(&x,indexF) ;
printf("tab %d ----  ", tab->NbrEID) ;
   writeIndexTableToFile(indexI,tab) ;


        break;
    case 3:

     printf ("give the code  for logical delete ::");

     scanf("%d" , &code);

     logicalDeleteInforamtion(tab , filename , code);
        break;
    case 4:
            printf (" you want modifiy file name  ( fname) or extention ( ext) ::") ;

    scanf("%s" ,faeidl );
    printf ("\n entre the file name to update::");
    scanf("%s" , fname);
    printf ("\n entre the new value::");
    scanf("%s" , name);
    updateField (fichs ,&x , fname , name , faeidl , filename );
        break;
    case 5:
             printf ("entre the name of the file for recherch::");
    scanf("%d" , code)  ;
    bloc_information ibc ;
    RechercherInformation(filename , code , &Trouv , &i , &j) ;
    write_blocInformation(filename , i, &ibc) ;
    for(int s = 0 ; s < ibc.nb ; s++){
        if(ibc.donne[s].code == code)
            {
                affichinformation(ibc.donne[s]) ;

    }
    break;
    }

        break;
    case 6:
          blocaffich(filename);
        break;
    default:
        printf("invalide ") ;
        break;
   }
    writeIndexTableToFile(indexI , tab);
    WriteIndexToFile(&x , indexF);
   }while(choice != 0);
   fclose(lof->fichier);
   fclose(tof->fi);
}
