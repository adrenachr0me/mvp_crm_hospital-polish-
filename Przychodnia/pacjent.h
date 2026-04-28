/**
 * @file pacjent.h
 * @brief Definicja struktury Pacjent oraz funkcji do obsługi kartoteki pacjentów.
 */

#ifndef PACJENT_H
#define PACJENT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/**
 * @struct Pacjent
 * @brief Struktura reprezentująca dane pacjenta w formie węzła listy jednokierunkowej.
 */
typedef struct Pacjent {
    int id;                 ///< Unikalny numer identyfikacyjny pacjenta
    char name[30];          ///< Imię pacjenta
    char surname[30];       ///< Nazwisko pacjenta
    char pesel[12];         ///< Numer PESEL (11 znaków + znak końca napisu)
    char birth_date[11];    ///< Data urodzenia w formacie RRRR-MM-DD
    char address[100];      ///< Adres zamieszkania pacjenta
    char email[50];         ///< Adres e-mail pacjenta
    char phone[15];         ///< Numer telefonu kontaktowego
    float weight;           ///< Masa ciała pacjenta (w kg)
    float height;           ///< Wzrost pacjenta (w cm)
    char nfz[50];           ///< Informacja o oddziale NFZ pacjenta
    struct Pacjent *next;   ///< Wskaźnik na kolejnego pacjenta w liście (NULL na końcu)
} Pacjent;

/** @name Funkcje operacyjne na liście pacjentów */
///@{

/** @brief Dodaje nowego pacjenta do bazy danych (interaktywne pobieranie danych).
    @param head Podwójny wskaźnik na początek listy pacjentów. */
void add_pacjent(Pacjent **head);

/** @brief Wyświetla wszystkich pacjentów zarejestrowanych w systemie.
    @param head Wskaźnik na początek listy. */
void print_pacjenci(Pacjent *head);

/** @brief Wyszukuje pacjenta na podstawie podanych kryteriów (np. nazwisko lub PESEL).
    @param head Wskaźnik na początek listy. */
void search_pacjent(Pacjent **head);

/** @brief Usuwa pacjenta z listy na podstawie ID, zwalniając zajmowaną pamięć.
    @param head Podwójny wskaźnik na początek listy. */
void delete_pacjent(Pacjent **head);

/** @brief Sortuje listę pacjentów według wybranego klucza (np. alfabetycznie).
    @param head Podwójny wskaźnik na początek listy. */
void sort_pacjent(Pacjent **head);

///@}

#endif