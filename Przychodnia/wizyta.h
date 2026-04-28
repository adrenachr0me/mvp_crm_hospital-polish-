/**
* @file wizyta.h
 * @brief Zarządzanie terminarzem wizyt lekarskich.
 */

#ifndef WIZYTA_H
#define WIZYTA_H

// UWAGA: Usunięto #include "wizyta.h" - plik nie powinien dołączać samego siebie
#include "pacjent.h"
#include "lekarz.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/**
 * @struct Wizyty
 * @brief Struktura reprezentująca pojedynczą wizytę w systemie (węzeł listy).
 */
typedef struct Wizyty {
    int id;                 ///< Unikalny numer identyfikacyjny wizyty
    int pacjent_id;         ///< ID pacjenta przypisanego do wizyty
    int lekarz_id;          ///< ID lekarza prowadzącego wizytę
    char date[11];          ///< Data wizyty (RRRR-MM-DD)
    char time[6];           ///< Godzina wizyty (GG:MM)
    int duration;           ///< Czas trwania wizyty w minutach
    int status;             ///< Status wizyty (np. 0-planowana, 1-odbyta, 2-odwołana)
    struct Wizyty *next;    ///< Wskaźnik na następną wizytę w liście
} Wizyty;

/** @name Funkcje obsługi terminarza */
///@{

/** @brief Wyświetla listę wszystkich zarejestrowanych wizyt.
    @param head Wskaźnik na początek listy wizyt. */
void print_wizyty(Wizyty *head);

/** @brief Dodaje nową wizytę, weryfikując dostępność lekarza i pacjenta.
    @param head Podwójny wskaźnik na początek listy wizyt. */
void add_wizyta(Wizyty **head, Lekarz *head_l, Pacjent *head_p);

/** @brief Wyszukuje konkretną wizytę na podstawie ID lub daty.
    @param head Wskaźnik na początek listy. */
void search_wizyt(Wizyty **head);

/** @brief Pozwala na filtrowanie wizyt według zadanych kryteriów (np. tylko danego lekarza).
    @param head Wskaźnik na początek listy. */
void filtry_wizyt(Wizyty **head);

/** @brief Usuwa wizytę z systemu i zwalnia pamięć.
    @param head Podwójny wskaźnik na początek listy. */
void delete_wizyta(Wizyty **head);

///@}

#endif