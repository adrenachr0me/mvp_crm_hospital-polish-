/**
* @file file_man.h
 * @brief Moduł zarządzania plikami i trwałością danych.
 * * Ten nagłówek zawiera deklaracje funkcji odpowiedzialnych za serializację
 * i deserializację list lekarzy, pacjentów oraz wizyt do plików binarnych lub tekstowych.
 */

#ifndef FILE_MAN_H
#define FILE_MAN_H

#include "wizyta.h"
#include "pacjent.h"
#include "lekarz.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/** @name Obsługa Lekarzy */
///@{
/** @brief Zapisuje aktualną listę lekarzy do pliku. */
void save_lekarze();
/** @brief Wczytuje listę lekarzy z pliku do pamięci. */
void load_lekarze();
///@}

/** @name Obsługa Pacjentów */
///@{
/** @brief Zapisuje aktualną listę pacjentów do pliku. */
void save_pacjenci();
/** @brief Wczytuje listę pacjentów z pliku do pamięci. */
void load_pacjenci();
///@}

/** @name Obsługa Wizyt */
///@{
/** @brief Zapisuje listę wszystkich wizyt do pliku. */
void save_wizyty();
/** @brief Wczytuje listę wizyt z pliku do pamięci. */
void load_wizyty();
///@}

/** @name Operacje Zbiorcze */
///@{
/** @brief Zapisuje całą bazę danych (lekarzy, pacjentów i wizyty) jednym wywołaniem. */
void save_all();
/** @brief Wczytuje wszystkie dane z plików podczas startu systemu. */
void load_all();
///@}

#endif