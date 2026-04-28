/**
* @file lekarz.h
 * @brief Definicja struktury Lekarz oraz funkcji zarządzających listą lekarzy.
 */

#ifndef LEKARZ_H
#define LEKARZ_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/**
 * @struct Lekarz
 * @brief Struktura reprezentująca węzeł listy jednokierunkowej lekarzy.
 */
typedef struct Lekarz {
    int id;               ///< Unikalny identyfikator lekarza [cite: 6]
    char name[30];        ///< Imię lekarza [cite: 7]
    char surname[30];     ///< Nazwisko lekarza [cite: 8]
    char pesel[12];       ///< Numer PESEL [cite: 9]
    char pwz[10];         ///< Numer Prawa Wykonywania Zawodu [cite: 10]
    char title[30];       ///< Tytuł naukowy lub zawodowy [cite: 11]
    char typ[40];         ///< Specjalizacja lekarza [cite: 12]
    char email[50];       ///< Adres e-mail kontaktowy [cite: 13]
    char phone[15];       ///< Numer telefonu kontaktowego [cite: 14]
    char hours[100];      ///< Godziny przyjęć lekarza [cite: 15]
    struct Lekarz *next;  ///< Wskaźnik na następny element listy (NULL jeśli koniec) [cite: 16]
} Lekarz;

/** @name Funkcje zarządzające bazą lekarzy */
///@{

/** @brief Wyświetla listę wszystkich lekarzy w formacie tabelarycznym.
    @param head Wskaźnik na początek listy. */
void print_lekarze(Lekarz *head);

/** @brief Interaktywne dodawanie nowego lekarza do bazy.
    @param head Podwójny wskaźnik na głowę listy (pozwala na dodanie na początku). */
void add_lekarz(Lekarz **head);

/** @brief Wyszukuje lekarza na podstawie zadanych kryteriów.
    @param head Podwójny wskaźnik na głowę listy. */
void search_lekarz(Lekarz **head);

/** @brief Usuwa lekarza z listy na podstawie ID.
    @param head Podwójny wskaźnik na głowę listy (obsługuje usunięcie pierwszego elementu). */
void delete_lekarz(Lekarz **head);

/** @brief Sortuje listę lekarzy (np. alfabetycznie po nazwisku).
    @param head Podwójny wskaźnik na głowę listy. */
void sort_lekarz(Lekarz **head);

///@}

#endif