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

typedef struct Wizyty {
    int id;
    int pacjent_id;
    int lekarz_id;
    char date[11];
    char time[6];
    int duration;
    int status;
    struct Wizyty *next;
} Wizyty;

void print_lekarze(Lekarz *head) {
    Lekarz *current = head;
    if (current == NULL) {
        printf("Baza pusta\n");
        return;
    }
    while (current != NULL) {
        printf("ID: %d | %s %s %s | %s\n", current->id, current->title, current->name, current->surname, current->typ);
        current = current->next;
    }
}

void print_pacjenci(Pacjent *head) {
    Pacjent *current = head;
    if (current == NULL) {
        printf("Baza pusta\n");
        return;
    }
    while (current != NULL) {
        printf("ID: %d | %s %s | PESEL: %s | Oddzial NFZ: %s\n",
               current->id, current->name, current->surname, current->pesel, current->nfz);
        current = current->next;
    }
}

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

void add_lekarz(Lekarz **head) {
    int choice = 1;
    printf("\n--- Tryb dodawania lekarzy ---\n");

    while (choice != 0) {
        Lekarz *nowy = (Lekarz*)malloc(sizeof(Lekarz));
        if (nowy == NULL) {
            printf("Blad: Brak pamieci!\n");
            return;
        }
        nowy->next = NULL;

        if (*head == NULL) {
            nowy->id = 1;
        } else {
            Lekarz *temp = *head;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            nowy->id = temp->id + 1;
        }

        printf("\nLekarz #%d\n", nowy->id);
        printf("Tytul zawodowy: ");
        scanf("%s", nowy->title);
        printf("Imie: ");
        scanf("%s", nowy->name);
        printf("Nazwisko: ");
        scanf("%s", nowy->surname);
        printf("PESEL: ");
        scanf("%s", nowy->pesel);
        printf("Numer PWZ: ");
        scanf("%s", nowy->pwz);
        printf("Specjalizacja: ");
        scanf("%s", nowy->typ);
        printf("E-mail: ");
        scanf("%s", nowy->email);
        printf("Telefon: ");
        scanf("%s", nowy->phone);
        printf("Godziny pracy (np. Pn-Pt_8-16): ");
        scanf("%s", nowy->hours);

        if (*head == NULL) {
            *head = nowy;
        } else {
            Lekarz *temp = *head;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = nowy;
        }
        printf("Dodano pomyslnie!\n");
        printf("\nDodac kolejnego? (1 - Tak, 0 - Zakoncz): ");
        scanf("%d", &choice);
    }
}

void add_pacjent(Pacjent **head) {
    int choice = 1;
    printf("\n--- Tryb dodawania pacjentow ---\n");

    while (choice != 0) {
        Pacjent *nowy = (Pacjent*)malloc(sizeof(Pacjent));
        if (nowy == NULL) {
            printf("Blad: Brak pamieci!\n");
            return;
        }
        nowy->next = NULL;

        if (*head == NULL) {
            nowy->id = 1;
        } else {
            Pacjent *temp = *head;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            nowy->id = temp->id + 1;
        }

        printf("\nPacjent #%d\n", nowy->id);
        printf("Imie: ");
        scanf("%s", nowy->name);
        printf("Nazwisko: ");
        scanf("%s", nowy->surname);
        printf("PESEL: ");
        scanf("%s", nowy->pesel);
        printf("Data urodzenia (DD.MM.RRRR): ");
        scanf("%s", nowy->birth_date);
        printf("Adres (bez_spacji): ");
        scanf("%s", nowy->address);
        printf("E-mail: ");
        scanf("%s", nowy->email);
        printf("Telefon: ");
        scanf("%s", nowy->phone);
        printf("Waga (kg): ");
        scanf("%f", &nowy->weight);
        printf("Wzrost (cm): ");
        scanf("%f", &nowy->height);
        printf("Oddzial NFZ: ");
        scanf("%s", nowy->nfz);

        if (*head == NULL) {
            *head = nowy;
        } else {
            Pacjent *temp = *head;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = nowy;
        }

        printf("Dodano pomyslnie!\n");
        printf("\nDodac kolejnego? (1 - Tak, 0 - Zakoncz): ");
        scanf("%d", &choice);
    }
}

void add_wizyta(Wizyty **head, Lekarz *head_l, Pacjent *head_p) {
    int target_l, target_p;
    bool p_found = false, l_found = false;

    printf("\n--- Nowa wizyta ---\n");
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
    printf("Wpisz ID wybranego lekarza: ");
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
    printf("Data (DD.MM.RRRR): ");
    scanf("%10s", nowy->date);
    printf("Czas (HH:MM): ");
    scanf("%6s", nowy->time);
    printf("Czas trwania (w minutach): ");
    scanf("%d", &nowy->duration);
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

void save_lekarze(Lekarz *head) {
    FILE *file = fopen("lekarze.txt", "w");
    if (file != NULL) {
        Lekarz *current = head;
        while (current != NULL) {
            fprintf(file, "%d %s %s %s %s %s %s %s %s %s\n",
                    current->id, current->name, current->surname, current->pesel,
                    current->pwz, current->title, current->typ, current->email,
                    current->phone, current->hours);
            current = current->next;
        }
        fclose(file);
    }
}

void load_lekarze(Lekarz **head) {
    FILE *file = fopen("lekarze.txt", "r");
    if (file == NULL) return;

    Lekarz temp;
    while (fscanf(file, "%d %s %s %s %s %s %s %s %s %s",
                  &temp.id, temp.name, temp.surname, temp.pesel,
                  temp.pwz, temp.title, temp.typ, temp.email,
                  temp.phone, temp.hours) == 10) {
        Lekarz *nowy = (Lekarz*)malloc(sizeof(Lekarz));
        if (nowy == NULL) break;
        *nowy = temp;
        nowy->next = NULL;

        if (*head == NULL) {
            *head = nowy;
        } else {
            Lekarz *curr = *head;
            while (curr->next != NULL) {
                curr = curr->next;
            }
            curr->next = nowy;
        }
    }
    fclose(file);
}

void save_pacjenci(Pacjent *head) {
    FILE *file = fopen("pacjenci.txt", "w");
    if (file != NULL) {
        Pacjent *current = head;
        while (current != NULL) {
            fprintf(file, "%d %s %s %s %s %s %s %s %f %f %s\n",
                    current->id, current->name, current->surname, current->pesel,
                    current->birth_date, current->address, current->email,
                    current->phone, current->weight, current->height, current->nfz);
            current = current->next;
        }
        fclose(file);
    }
}

void load_pacjenci(Pacjent **head) {
    FILE *file = fopen("pacjenci.txt", "r");
    if (file == NULL) return;

    Pacjent temp;
    while (fscanf(file, "%d %s %s %s %s %s %s %s %f %f %s",
                  &temp.id, temp.name, temp.surname, temp.pesel,
                  temp.birth_date, temp.address, temp.email,
                  temp.phone, &temp.weight, &temp.height, temp.nfz) == 11) {
        Pacjent *nowy = (Pacjent*)malloc(sizeof(Pacjent));
        if (nowy == NULL) break;
        *nowy = temp;
        nowy->next = NULL;

        if (*head == NULL) {
            *head = nowy;
        } else {
            Pacjent *curr = *head;
            while (curr->next != NULL) {
                curr = curr->next;
            }
            curr->next = nowy;
        }
    }
    fclose(file);
}

void save_wizyty(Wizyty *head) {
    FILE *file = fopen("wizyty.txt", "w");
    if (file != NULL) {
        Wizyty *current = head;
        while (current != NULL) {
            fprintf(file, "%d %d %d %s %s %d %d\n",
                    current->id, current->pacjent_id, current->lekarz_id,
                    current->date, current->time, current->duration, current->status);
            current = current->next;
        }
        fclose(file);
    }
}

void load_wizyty(Wizyty **head) {
    FILE *file = fopen("wizyty.txt", "r");
    if (file == NULL) return;

    Wizyty temp;
    while (fscanf(file, "%d %d %d %s %s %d %d",
                  &temp.id, &temp.pacjent_id, &temp.lekarz_id,
                  temp.date, temp.time, &temp.duration, &temp.status) == 7) {
        Wizyty *nowy = (Wizyty*)malloc(sizeof(Wizyty));
        if (nowy == NULL) break;
        *nowy = temp;
        nowy->next = NULL;

        if (*head == NULL) {
            *head = nowy;
        } else {
            Wizyty *curr = *head;
            while (curr->next != NULL) {
                curr = curr->next;
            }
            curr->next = nowy;
        }
    }
    fclose(file);
}

void load_all(Wizyty **head_w, Lekarz **head_l, Pacjent **head_p) {
    load_lekarze(head_l);
    load_pacjenci(head_p);
    load_wizyty(head_w);
    printf("[System] Baza danych zaladowana pomyslnie.\n");
}

void save_all(Wizyty *head_w, Lekarz *head_l, Pacjent *head_p) {
    save_lekarze(head_l);
    save_pacjenci(head_p);
    save_wizyty(head_w);
    printf("[System] Wszystkie dane zostaly zapisane.\n");
}

int main(void) {
    Lekarz *head_lekarz = NULL;
    Pacjent *head_pacjent = NULL;
    Wizyty *head_wizyt = NULL;
    int main_choice = -1;

    load_all(&head_wizyt, &head_lekarz, &head_pacjent);

    while (main_choice != 0) {
        printf("\n=== MENU GLOWNE ===\n");
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
                    printf("\n--- ZARZADZANIE LEKARZAMI ---\n");
                    printf("1. Dodaj lekarzy\n");
                    printf("2. Pokaz lekarzy\n");
                    printf("3. Usuwanie lekarzy\n");
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
                            printf("Funkcja usuwania wkrotce...\n");
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
                    printf("\n--- ZARZADZANIE PACJENTAMI ---\n");
                    printf("1. Dodaj pacjenta\n");
                    printf("2. Pokaz pacjentow\n");
                    printf("3. Usuwanie pacjenta\n");
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
                            printf("Funkcja usuwania wkrotce...\n");
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
                    printf("\n--- ZARZADZANIE WIZYTAMI ---\n");
                    printf("1. Dodaj wizyte\n");
                    printf("2. Pokaz wizyty\n");
                    printf("3. Usuwanie wizyty\n");
                    printf("0. Powrot\n");
                    printf("Wybierz opcje: ");
                    scanf("%d", &sub_choice);

                    switch (sub_choice) {
                        case 1:
                            add_wizyta(&head_wizyt, head_lekarz, head_pacjent);
                            break;
                        case 2:
                            print_wizyty(head_wizyt);
                            break;
                        case 3:
                            printf("Funkcja usuwania wkrotce...\n");
                            break;
                        case 0:
                            break;
                        default:
                            printf("Nieznana opcja.\n");
                    }
                }
                break;
            }
            case 0:
                printf("Zamykanie systemu...\n");
                save_all(head_wizyt, head_lekarz, head_pacjent);
                break;
            default:
                printf("Nieznana opcja, sprobuj ponownie.\n");
        }
    }
    return 0;
}