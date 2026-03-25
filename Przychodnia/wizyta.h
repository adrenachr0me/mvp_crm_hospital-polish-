#ifndef WIZYTA_H
#define WIZYTA_H

#include "wizyta.h"
#include "pacjent.h"
#include "lekarz.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Wizyty {
    int id;
    int pacjent_id;
    int lekarz_id;
    char date[11];
    char time[6];
    int duration;
    int status;
    struct Wizyty *next;
} Wizyty;
void print_wizyty();
void add_wizyta();
void search_wizyt();
void filtry_wizyt();
void delete_wizyta();
#endif