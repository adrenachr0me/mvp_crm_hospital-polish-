/**
 * @file wizyta.c
 * @brief Implementacja systemu rezerwacji i zarządzania wizytami.
 * * Plik zawiera pełną logikę biznesową przychodni: sprawdzanie dostępności lekarzy,
 * walidację istnienia pacjentów, wykrywanie konfliktów czasowych w grafiku
 * oraz zaawansowane filtrowanie i wyszukiwanie wizyt.
 */

#include "wizyta.h"

/**
 * @brief Wyświetla listę wszystkich zarejestrowanych wizyt.
 * * Przechodzi przez listę jednokierunkową od podanej głowy i wypisuje
 * podstawowe informacje o każdej wizycie (ID, powiązania z pacjentem i lekarzem, data, czas, status).
 * * @param head Wskaźnik na początek listy wizyt.
 */
void print_wizyty(Wizyty *head) {
    Wizyty *current = head;
    if (current == NULL) {
        printf("Baza pusta\n");
        return;
    }
    while (current != NULL) {
        printf("Wizyta ID: %d | Lekarz ID: %d | Pacjent ID: %d | Data: %s %s | Status: %d\n",
               current->id, current->lekarz_id, current->pacjent_id, current->date, current->time, current->status);
        current = current->next;
    }
}

/**
 * @brief Dodaje nową wizytę z automatycznym sprawdzaniem kolizji czasowych.
 * * @details Funkcja wykonuje proces rezerwacji w kilku krokach:
 * 1. Pobiera ID pacjenta i weryfikuje jego istnienie w bazie.
 * 2. Pobiera ID lekarza i weryfikuje jego istnienie w bazie.
 * 3. Pobiera dane o dacie, czasie rozpoczęcia i przewidywanym czasie trwania wizyty.
 * 4. Uruchamia algorytm wykrywania konfliktów: przelicza godziny na minuty i sprawdza
 * nakładanie się przedziałów czasowych z już istniejącymi wizytami u danego lekarza w tym dniu.
 * 5. Jeśli brakuje konfliktów, alokuje pamięć, nadaje nowe ID i dodaje wizytę na koniec listy.
 * * @param head Podwójny wskaźnik na początek listy wizyt.
 * @param head_l Wskaźnik na początek listy lekarzy (do walidacji).
 * @param head_p Wskaźnik na początek listy pacjentów (do walidacji).
 */
void add_wizyta(Wizyty **head, Lekarz *head_l, Pacjent *head_p) {
    int target_l, target_p;
    bool p_found = false, l_found = false;

    printf("\nNowa wizyta\n");
    print_pacjenci(head_p);
    printf("Jaki ID pacjenta? ");
    scanf("%d", &target_p);

    Pacjent *curr_p = head_p;
    while (curr_p != NULL) {
        if (curr_p->id == target_p) {
            p_found = true;
            break;
        }
        curr_p = curr_p->next;
    }

    if (!p_found) {
        printf("Blad, nie ma pacjenta z takim id\n");
        return;
    }

    print_lekarze(head_l);
    printf("Wpisz ID wybranego lekarza: \n");
    scanf("%d", &target_l);

    Lekarz *curr_l = head_l;
    while (curr_l != NULL) {
        if (curr_l->id == target_l) {
            l_found = true;
            break;
        }
        curr_l = curr_l->next;
    }

    if (!l_found) {
        printf("Blad, nie ma lekarza z takim id\n");
        return;
    }
    char temp_date[11];
    char temp_time[6];
    int temp_duration;
    printf("Data (DD.MM.RRRR): \n");
    scanf("%10s", temp_date);
    printf("Czas (HH:MM): \n");
    scanf("%6s", temp_time);
    printf("Czas trwania (w minutach): \n");
    scanf("%d", &temp_duration);
    Wizyty *check = *head;
    bool conflict = false;
    while (check != NULL) {
        if (check->lekarz_id == target_l && strcmp(check->date, temp_date) == 0) {
            int ha,hb,ma,mb;
            sscanf(check->time, "%d:%d", &hb, &mb);
            sscanf(temp_time, "%d:%d", &ha, &ma);
            int time_b = hb * 60 + mb;
            int end_old = time_b + check->duration;
            int time_a = ha * 60 + ma;
            int end_new  = time_a + temp_duration;
            if (time_a < end_old && time_b < end_new) {
                conflict = true;
            }

        }
        check = check->next;
    }
    if (conflict) {
        printf("Blad: Lekarz ma juz wizyte w tym czasie!\n");
        return;
    }
    Wizyty *nowy = (Wizyty*)malloc(sizeof(Wizyty));
    if (nowy == NULL) {
        printf("Blad: Brak pamieci!\n");
        return;
    }
    nowy->next = NULL;

    if (*head == NULL) {
        nowy->id = 1;
    } else {
        Wizyty *temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        nowy->id = temp->id + 1;
    }

    nowy->pacjent_id = target_p;
    nowy->lekarz_id = target_l;
    strcpy(nowy->date,temp_date);
    strcpy(nowy->time,temp_time);
    nowy->duration = temp_duration;
    nowy->status = 0;

    if (*head == NULL) {
        *head = nowy;
    } else {
        Wizyty *temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = nowy;
    }

    printf("Wizyta o id %d dodana (Status: Zaplanowana)\n", nowy->id);
}

/**
 * @brief Zaawansowane filtrowanie wizyt według wielu kryteriów.
 * * @details Pozwala na przeglądanie wizyt przypisanych do konkretnego lekarza lub pacjenta.
 * Oferuje dodatkową możliwość zawężenia wyników do określonej daty lub statusu wizyty.
 * Zastosowano logikę dopasowania (`match`), która ułatwia rozbudowę o kolejne filtry.
 * * @param head Podwójny wskaźnik na początek listy wizyt.
 */
void filtry_wizyt(Wizyty **head) {
    if (*head == NULL) {
        printf("Baza pusta\n");
        return;
    }

    int for_who, target_id, type_of_fil;
    char fil_data[11];
    int fil_status;

    printf("\nFiltrowanie wizyt\n");
    printf("Czyje wizyty chcesz zobaczyc? (1-Lekarz,2-Pacjent): ");
    scanf("%d", &for_who);

    if (for_who != 1 && for_who != 2) {
        printf("Bledna opcja!\n");
        return;
    }

    printf("Podaj ID: ");
    scanf("%d", &target_id);

    printf("Jaka filtracje potrzebujesz?\n");
    printf("1 - Brak filtrowania (pokaz wszystkie wizyty tej osoby)\n");
    printf("2 - Filtruj po dacie\n");
    printf("3 - Filtruj po statusie\n");
    printf("Wybierz opcje: ");
    scanf("%d", &type_of_fil);

    if (type_of_fil == 2) {
        printf("Podaj date (DD.MM.RRRR): ");
        scanf("%10s", fil_data);
    } else if (type_of_fil == 3) {
        printf("Podaj status (np. 0-zaplanowana): ");
        scanf("%d", &fil_status);
    }


    Wizyty *current = *head;
    bool found_any = false;

    printf("\nWyniki wyszukiwania:\n");

    while (current != NULL) {
        bool match = false;

        if (for_who == 1 && current->lekarz_id == target_id) match = true;
        if (for_who == 2 && current->pacjent_id == target_id) match = true;

        if (match == true) {
            if (type_of_fil == 2 && strcmp(current->date, fil_data) != 0) {
                match = false;
            }
            if (type_of_fil == 3 && current->status != fil_status) {
                match = false;
            }
        }

        if (match == true) {
            printf("ID: %d | Pacjent: %d | Lekarz: %d | Data: %s %s | Czas trwania: %d | Status: %d\n",
                   current->id, current->pacjent_id, current->lekarz_id,
                   current->date, current->time, current->duration, current->status);
            found_any = true;
        }

        current = current->next;
    }

    if (!found_any) {
        printf("Nie odnaleziono wizyt spelniajacych podane kryteria.\n");
    }
}

/**
 * @brief Wyszukuje konkretną wizytę i umożliwia pełną edycję jej danych.
 * * @details Wyszukuje po kombinacji daty oraz czasu wizyty. Po znalezieniu rekordu
 * użytkownik może wywołać interaktywne menu umożliwiające edycję powiązań (ID pacjenta/lekarza),
 * daty, czasu, czasu trwania oraz statusu rezerwacji.
 * * @param head Podwójny wskaźnik na początek listy wizyt.
 */
void search_wizyt(Wizyty **head) {
    if (*head == NULL) {
        printf("Baza pusta;\n");
        return;
    }
    printf("Wyszukiwanie wizyty\n");
    char search_date[20];
    char search_time[20];
    printf("Wprowadz date wizyty: \n");
    scanf("%19s", search_date);
    printf("Wprowadz czas wizyty: \n");
    scanf("%19s", search_time);
    Wizyty *current = *head;
    bool found = false;
    while (current != NULL) {
        if (strcmp(current->date, search_date) == 0 && strcmp(current->time, search_time) == 0) {
            found = true;
            printf("ID: %d\n", current->id);
            printf("Pacjent: %d\n", current->pacjent_id);
            printf("Lekarz: %d\n", current->lekarz_id);
            printf("Data: %s\n", current->date);
            printf("Czas: %s\n", current->time);
            printf("Trwalosc: %d\n", current->duration);
            printf("Status: %d\n", current->status);
            int edit;
            printf("Czy chcesz edytowac dane wizyty? (1-Tak, 0-Nie)");
            scanf("%d", &edit);
            if (edit == 1) {
                int field = -1;
                while (field != 0) {
                    printf("1.ID: %d\n", current->id);
                    printf("2.Pacjent: %d\n", current->pacjent_id);
                    printf("3.Lekarz: %d\n", current->lekarz_id);
                    printf("4.Data: %s\n", current->date);
                    printf("5.Czas: %s\n", current->time);
                    printf("6.Trwalosc: %d\n", current->duration);
                    printf("7.Status: %d\n", current->status);
                    printf("0.Wyjscie\n");
                    scanf("%d", &field);
                    switch (field) {
                        case 1: {
                            int assured;
                            printf("Zmiena id nie jest polecana, czy na pewno chcesz kontynuowac?(Wprowadz 1 dla podtwierdzenia)\n");
                            scanf("%d", &assured);
                            if (assured == 1) {
                                printf("Wprowadz nowe id:\n");
                                scanf("%d", &current->id);
                                break;
                            }
                            else {
                                printf("Madry wybor\n");
                                break;
                            }
                        }
                        case 2:
                            printf("Wprowadz nowego pacjenta:\n");
                            scanf("%d", &current->pacjent_id);
                            break;
                        case 3:
                            printf("Wprowadz nowego lekarza:\n");
                            scanf("%d", &current->lekarz_id);
                            break;
                        case 4:
                            printf("Wprowadz nowa date:\n");
                            scanf("%10s", current->date);
                            break;
                        case 5:
                            printf("Wprowadz nowy czas:\n");
                            scanf("%5s", current->time);
                            break;
                        case 6: {
                            int temp_duration;
                            printf("Wprowadz nowa trwalosc (wiecej niz 0 minut):\n");
                            while (1) {
                                if (scanf("%d", &temp_duration) == 1 && temp_duration > 0) {
                                    current->duration = temp_duration;
                                    break;
                                }
                                else
                                    {
                                    printf("Bledna wartosc! Czas trwania musi byc liczba dodatnia. Sprobuj ponownie:\n");
                                    while (getchar() != '\n');
                                }
                            }
                            break;
                        }
                        case 7: {
                            int temp_status;
                            printf("Wprowadz nowy status (0 - zaplanowana, 1 - odbyta, 2 - odwolana):\n");
                            while (1) {
                                if (scanf("%d", &temp_status) == 1 && temp_status >= 0 && temp_status <= 2) {
                                    current->status = temp_status;
                                    break;
                                    break;
                                } else {
                                    printf("Bledna wartosc! Status musi byc od 0 do 2. Sprobuj ponownie:\n");
                                    while (getchar() != '\n');
                                }
                            }
                            break;
                        }
                        case 0:
                            printf("Zakonczono edycje.\n");
                            break;
                        default:
                            printf("Nieznana opcja!\n");
                    }
                }
            }
        }
        current = current->next;
    }
    if (!found) {
        printf("Nie odnaleziono wizyty");
    }
}

/**
 * @brief Usuwa zaplanowaną wizytę z systemu na podstawie jej identyfikatora.
 * * Implementacja bezpiecznie odpina węzeł wizyty z listy jednokierunkowej,
 * zwalniając odpowiednio przypisaną do niej pamięć dynamiczną.
 * * @param head Podwójny wskaźnik na początek listy wizyt.
 */
void delete_wizyta(Wizyty **head) {
    if (*head == NULL) {
        printf("Baza pusta;\n");
        return;
    }
    int target_id;
    printf("Usuwanie wizyty\n");
    printf("Podaj id wizyty do usuniecia:\n");
    scanf("%d", &target_id);
    Wizyty *current = *head;
    Wizyty *prev = NULL;
    if (current != NULL && current->id == target_id) {
        *head = current->next;
        free(current);
        return;
    }
    while (current != NULL && current->id != target_id) {
        prev = current;
        current = current->next;
    }
    if (current == NULL) {
        printf("Nie odnaleziono wizyty o takim  id\n");
        return;
    }
    if (current != NULL && current->id == target_id) {
        prev->next = current->next;
        free(current);
    }
    printf("Wizyta o id %d zostala usunieta\n", target_id);
}