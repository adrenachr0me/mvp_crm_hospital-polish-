#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
typedef struct{
    int id;
    char name[30];
    char surname[30];
    char typ[40];
}  Lekarz;
typedef struct{
    int id;
    char name[30];
    char surname[30];
    char diagnosis[100];
} Pacjent;
typedef struct{
    int id;
    char date[11];
    int lekarz_id;
    int pacjent_id;
    int room;
    char time[6];
} Wizyty;
typedef struct{
    int id;
    char name[40];
    double price;
    int lekarz_id;
} Uslugi;
int main(void) {
    Lekarz lekarzy[50];
    int lekarzy_count = 0;
    Pacjent pacjent[100];
    int pacjent_count = 0;
    lekarzy[0].id = 1;
    strcpy(lekarzy[0].name, "Jan");
    strcpy(lekarzy[0].surname, "Kowalski");
    strcpy(lekarzy[0].typ, "Kardiolog");
    lekarzy_count++;
    pacjent[0].id = 1;
    strcpy(pacjent[0].name, "Tomasz");
    strcpy(pacjent[0].surname, "Wojcik");
    strcpy(pacjent[0].diagnosis, "Grypa");
    pacjent_count++;

}