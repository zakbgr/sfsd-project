#ifndef INDEX_C_INCLUDED
#define INDEX_C_INCLUDED
#include "index.h"
#include "struct.h"
#include "insertion.h"
#include "fileHandle.h"




void fillIndexTable(IndexTable* table, int code, int nbrbloc) {
    // Allocate memory for cle and ad
    table->EID[table->NbrEID].cle = (char*)malloc(code); // Assuming a fixed size for simplicity
    table->EID[table->NbrEID].ad = (Address*)malloc(sizeof(Address));
    sprintf(table->EID[table->NbrEID].cle, "%d", code);
    table->EID[table->NbrEID].ad->i = nbrbloc;
    // Increment the index table size
    table->NbrEID++;

}


// Function to read the index table from a file
void readIndexTableFromFile(const char* filename, IndexTable* table)
{
    FILE* file = fopen(filename, "rb");
    if (file != NULL) {
        fread(&table->NbrEID, sizeof(int), 1, file);  // Read the number of entries
        for (int i = 0; i < table->NbrEID; i++) {
            // Read the size of cle, cle, nbrbloc,
            int cleSize;
            fread(&cleSize, sizeof(int), 1, file);
            // Allocate memory for cle and ad
            table->EID[i].cle = (char*)malloc(cleSize + 1); // Add 1 for null terminator
            table->EID[i].ad = (Address*)malloc(sizeof(Address));
            fread(table->EID[i].cle, sizeof(char), cleSize, file);
            table->EID[i].cle[cleSize] = '\0';  // Add null terminator
            fread(&table->EID[i].ad->i, sizeof(int), 1, file);
        }
        fclose(file);
    } else {
        // Handle file opening error
        printf("Error opening file %s for reading.\n", filename);
    }
}

// Function to free the allocated memory for cle and ad
void freeIndexTable(IndexTable* table) {
    for (int i = 0; i < table->NbrEID; i++) {
        free(table->EID[i].cle);
        free(table->EID[i].ad);
    }
}
void reserchIndex(IndexTable * tab , char* namefile , int codeserch  ,information *ind , int *pose ){
bloc_information *info ;
for(int i=0 ; i < tab->NbrEID ;i++){
        if(atoi(tab->EID[i].cle )== codeserch){
            read_blocInformation(namefile,atoi(tab->EID[i].ad->i) +1, &info) ;
            if(info != NULL){
                for(int s =0 ; s<info->nb ; s++ )
                    if(info->donne[s].code == codeserch)
                        {
                                *ind = info->donne[s] ;
                                *pose = s ;
                                break;
                        }
            }
        }

}


}


void TriIndexTable(IndexTable* table) {
    int n = table->NbrEID;
    int i, j;
    IndexEntry temp;

    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            // Compare reservation codes and swap if needed
            int code1 = atoi(table->EID[j].cle);
            int code2 = atoi(table->EID[j + 1].cle);

            if (code1 > code2) {
                // Swap entries
                temp = table->EID[j];
                table->EID[j] = table->EID[j + 1];
                table->EID[j + 1] = temp;
            }
        }
    }
}






void InsererIndex(char filename[],int i, bl_index *Idx)
{
    int y;
    bool Trouv;
    index x;
    int s = strlen(filename);

    x.key = (char *)malloc((s + 5) * sizeof(char));
    sprintf(x.key, "%d %s", s, filename);

    x.ad = (adress *)malloc(sizeof(adress));
    x.ad->i = i;

    if (Idx->nb_index == 0)
    {
        Idx->idx[0] = x;
        Idx->nb_index++;
    }
    else
    {
        RechercherIndex(Idx, filename, &y, &Trouv);
        if (Trouv)
        {
             printf ("404!!!!\n");
             return;
        }
        else
        {
            for (int k = Idx->nb_index; k > y; k--)
            {
                Idx->idx[k] = Idx->idx[k - 1];
            }
            Idx->idx[y] = x;
            Idx->nb_index++;
        }
    }
}

void RechercherIndex(bl_index *dx, char filename[], int *y, bool *Trouv)
{
    printf("IN REACHH ") ;
    *Trouv = false;
    for (*y = 0; *y < dx->nb_index; (*y)++)
    {
        char fnome[50];
        sscanf(dx->idx[*y].key, "%*d %s %*d", fnome);
        int cmp = strcmp(filename, fnome);
        if (cmp == 0)
        {
            *Trouv = true;
            break;
        }
        else if (cmp < 0)
        {
            break;
        }
    }
}




void recherchAvecIndeInFILE(IndexTable *tabs, char* infor, int k, information *foundinformation, int *b) {
    int left = 0;
    int right = tabs->NbrEID - 1;
*b= -1 ;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int currentCode = atoi(tabs->EID[mid].cle);
        if (currentCode == k) {
            int blockNumber = tabs->EID[mid].ad->i;
            bloc_information bc;
            read_blocInformation(infor, blockNumber, &bc);
            for (int s = 0; s < bc.nb; s++) {
                if (bc.donne[s].code == k) {
                    *foundinformation = bc.donne[s];
                    *b=1 ;
                    return;
                }
            }
            break; // Reservation code found in index but not in block
        } else if (currentCode < k) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
printf("code not found " ) ;
}




// Function to write the index table to a file
void writeIndexTableToFile(const char* filename, IndexTable* table) {
    FILE* file = fopen(filename, "wb");
    if (file != NULL) {
        fwrite(&table->NbrEID, sizeof(int), 1, file);  // Write the number of entries
        for (int i = 0; i < table->NbrEID; i++) {
            // Write the size of cle, cle, nbrbloc, and positionINbloc
            int cleSize = strlen(table->EID[i].cle);
            fwrite(&cleSize, sizeof(int), 1, file);
            fwrite(table->EID[i].cle, sizeof(char), cleSize, file);
            fwrite(&table->EID[i].ad->i, sizeof(int), 1, file);
        }
        fclose(file);
    } else {
        // Handle file opening error
        printf("Error opening file %s for writing.\n", filename);
    }
}



Fichier rechfileIndex(char *nomfichier , char fn[] , bl_index *Idx)
{
    TOF *tof;

    tof = OpenFilef(nomfichier , 'A');
    char fname[50];
    blocfile bloc;
    int y;
    bool exist =false ;
    RechercherIndex(Idx ,fn,&y ,&exist);

    if (exist)
    {
        readbloc(nomfichier ,Idx->idx[y].ad->i ,&bloc);
        SortAllBlockfiche(nomfichier,&bloc);
        int debut = 0 ;
        int fin = bloc.nbfile - 1;

        while (debut <= fin)
        {
            int milieu = (debut+fin)/2;
            strcpy(fname,bloc.file[milieu].filename);

            if(strcmp(fn, fname) == 0)
            {
                return bloc.file[milieu];
            }else if(strcmp(fn,fname)<0)
                fin = milieu - 1;
            else
                debut = milieu + 1;

        }
    }
}



void WriteIndexToFile(bl_index *x,  char *filename) {
    FILE *file = fopen(filename, "wb");
printf("i m in write ") ;
    if (file == NULL) {
        perror("Error opening file for writing");
        return;
    }

    fwrite(&(x->nb_index), sizeof(int), 1, file);

    for (int k = 0; k < x->nb_index; k++) {
        int cleLength = strlen(x->idx[k].key) + 1; // Include null terminator
        fwrite(&cleLength, sizeof(int), 1, file);
        fwrite(x->idx[k].key, sizeof(char), cleLength, file);
        fwrite(&(x->idx[k].ad->i), sizeof(int), 1, file);
    }

    fclose(file);
}

void ReadIndexFromFile(bl_index *x,  char *filename) {
    FILE *file = fopen(filename, "rb");
    printf("i m in read ") ;

    if (file == NULL) {
        perror("Error opening file for reading");
        return;
    }

    fread(&(x->nb_index), sizeof(int), 1, file);

    for (int k = 0; k < x->nb_index; k++) {
        int cleLength;
        fread(&cleLength, sizeof(int), 1, file);

        x->idx[k].key = (char *)malloc(cleLength * sizeof(char));
        fread(x->idx[k].key, sizeof(char), cleLength, file);

        x->idx[k].ad = (adress *)malloc(sizeof(adress));
        fread(&(x->idx[k].ad->i), sizeof(int), 1, file);
    }
}
#endif // INDEX_C_INCLUDED
