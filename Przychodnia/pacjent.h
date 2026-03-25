#ifndef PACJENT_H
#define PACJENT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>




typedef struct Pacjent {
    int id;
    char name[30];
    char surname[30];
    char pesel[12];
    char birth_date[11];
    char address[100];
    char email[50];
    char phone[15];
    float weight;
    float height;
    char nfz[50];
    struct Pacjent *next;
} Pacjent;
void add_pacjent();
void print_pacjenci();
void search_pacjent();
void delete_pacjent();
void sort_pacjent();
#endif