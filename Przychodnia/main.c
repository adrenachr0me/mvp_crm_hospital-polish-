#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "lekarz.h"
#include "pacjent.h"
#include "wizyta.h"
#include "file_man.h"

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
                        case 2:
                            print_lekarze(head_lekarz);
                            break;
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
                        case 2:
                            print_pacjenci(head_pacjent);
                            break;
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