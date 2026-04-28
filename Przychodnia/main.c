/**
 * @file main.c
 * @brief Punkt wejścia aplikacji systemu zarządzania przychodnią.
 * * Plik zawiera funkcję główną (main), która inicjalizuje struktury danych,
 * ładuje zapisany stan systemu z plików oraz uruchamia interaktywne menu
 * konsolowe oparte na zagnieżdżonych pętlach i instrukcjach switch.
 * Menu pozwala na nawigację między modułami lekarzy, pacjentów i wizyt.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "lekarz.h"
#include "pacjent.h"
#include "wizyta.h"
#include "file_man.h"

/**
 * @brief Główna funkcja programu, sterująca pętlą zdarzeń i interfejsem użytkownika.
 * * @details Funkcja zarządza całym cyklem życia aplikacji:
 * 1. Inicjalizuje wskaźniki początkowe (głowy) list jednokierunkowych na NULL.
 * 2. Wywołuje funkcję load_all() w celu wczytania persystentnych danych z dysku.
 * 3. Uruchamia zagnieżdżone menu konsolowe (Główne -> Podmenu modułów).
 * 4. Gwarantuje bezpieczeństwo danych wywołując save_all() przy prawidłowym wyjściu z programu.
 * * @return int Zwraca 0 po pomyślnym i bezpiecznym zamknięciu systemu.
 */
int main(void) {
    Lekarz *head_lekarz = NULL;
    Pacjent *head_pacjent = NULL;
    Wizyty *head_wizyt = NULL;
    int main_choice = -1;

    load_all(&head_wizyt, &head_lekarz, &head_pacjent);

    while (main_choice != 0) {
        printf("\n MENU GLOWNE \n");
        printf("1. Lekarze\n");
        printf("2. Pacjenci\n");
        printf("3. Wizyty\n");
        printf("0. Wyjdz z programu\n");
        printf("Wybierz opcje: ");
        scanf("%d", &main_choice);

        switch (main_choice) {
            case 1: {
                int sub_choice = -1;
                while (sub_choice != 0) {
                    printf("\n ZARZADZANIE LEKARZAMI \n");
                    printf("1. Dodaj lekarzy\n");
                    printf("2. Pokaz lekarzy\n");
                    printf("3. Usuwanie lekarzy\n");
                    printf("4. Wyszukiwanie lekarzy\n");
                    printf("0. Powrot\n");
                    printf("Wybierz opcje: ");
                    scanf("%d", &sub_choice);

                    switch (sub_choice) {
                        case 1:
                            add_lekarz(&head_lekarz);
                            break;
                        case 2: {
                            int choice = 0;
                            print_lekarze(head_lekarz);
                            printf("Czy chcesz odsortowac dane? (1-Tak, Inne-Nie)");
                            scanf("%d", &choice);
                            if (choice == 1) {
                                sort_lekarz(&head_lekarz);
                            }
                            break;
                        }
                        case 3:
                            delete_lekarz(&head_lekarz);
                            break;
                        case 4:
                            search_lekarz(&head_lekarz);
                            break;
                        case 0:
                            break;
                        default:
                            printf("Nieznana opcja.\n");
                    }
                }
                break;
            }
            case 2: {
                int sub_choice = -1;
                while (sub_choice != 0) {
                    printf("\n ZARZADZANIE PACJENTAMI \n");
                    printf("1. Dodaj pacjenta\n");
                    printf("2. Pokaz pacjentow\n");
                    printf("3. Usuwanie pacjenta\n");
                    printf("4. Wyszukiwanie pacjenta\n");
                    printf("0. Powrot\n");
                    printf("Wybierz opcje: ");
                    scanf("%d", &sub_choice);

                    switch (sub_choice) {
                        case 1:
                            add_pacjent(&head_pacjent);
                            break;
                        case 2: {
                            int choice = 0;
                            print_pacjenci(head_pacjent);
                            printf("Czy chcesz odsortowac dane? (1-Tak, Inne-Nie)");
                            scanf("%d", &choice);
                            if (choice == 1) {
                                sort_pacjent(&head_pacjent);
                            }
                            break;
                        }
                        case 3:
                            delete_pacjent(&head_pacjent);
                            break;
                        case 4:
                            search_pacjent(&head_pacjent);
                            break;
                        case 0:
                            break;
                        default:
                            printf("Nieznana opcja.\n");
                    }
                }
                break;
            }
            case 3: {
                int sub_choice = -1;
                while (sub_choice != 0) {
                    printf("\n ZARZADZANIE WIZYTAMI \n");
                    printf("1. Dodaj wizyte\n");
                    printf("2. Pokaz wizyty\n");
                    printf("3. Usuwanie wizyty\n");
                    printf("4. Wyszukiwanie wizyty\n");

                    printf("0. Powrot\n");
                    printf("Wybierz opcje: ");
                    scanf("%d", &sub_choice);

                    switch (sub_choice) {
                        case 1:
                            add_wizyta(&head_wizyt, head_lekarz, head_pacjent);
                            break;
                        case 2: {
                            int opt;
                            print_wizyty(head_wizyt);
                            printf("Czy potrzebujesz filtrowania wizyt?(1-Tak, jakakolwiek inna liczba-Nie)\n");
                            scanf("%d", &opt);
                            if (opt == 1) {
                                filtry_wizyt(&head_wizyt);
                                break;
                            }
                            break;
                        }
                        case 3:
                            delete_wizyta(&head_wizyt);
                            break;
                        case 4:
                            search_wizyt(&head_wizyt);
                            break;
                        case 0:
                            break;
                        default:
                            printf("Nieznana opcja\n");
                    }
                }
                break;
            }
            case 0:
                printf("Zamykanie systemu\n");
                save_all(head_wizyt, head_lekarz, head_pacjent);
                break;
            default:
                printf("Nieznana opcja, sprobuj ponownie\n");
        }
    }
    return 0;
}