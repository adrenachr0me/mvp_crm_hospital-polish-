#ifndef FILE_MAN_H
#define FILE_MAN_H
#include "wizyta.h"
#include "pacjent.h"
#include "lekarz.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
void save_lekarze();
void load_lekarze();
void save_pacjenci();
void load_pacjenci();
void save_wizyty();
void load_wizyty();
void save_all();
void load_all();
#endif