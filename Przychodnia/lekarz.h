#ifndef LEKARZ_H
#define LEKARZ_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


typedef struct Lekarz {
    int id;
    char name[30];
    char surname[30];
    char pesel[12];
    char pwz[10];
    char title[30];
    char typ[40];
    char email[50];
    char phone[15];
    char hours[100];
    struct Lekarz *next;
} Lekarz;

void print_lekarze(Lekarz *head);
void add_lekarz(Lekarz **head);
void search_lekarz(Lekarz **head);
void delete_lekarz(Lekarz **head);
void sort_lekarz(Lekarz **head);
#endif