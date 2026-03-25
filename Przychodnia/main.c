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
    printf("\nDodawanie lekarzy\n");

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
    printf("\nDodawanie pacjentow\n");

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
void search_pacjent(Pacjent **head) {
    if (*head == NULL) {
        printf("Baza pusta;\n");
        return;
    };
    printf("Wyszukiwanie pacjenta\n");
    char search[20];
    printf("Wprowadz numer telefona lub PESEL pacjenta: \n");
    scanf("%19s", search);

    Pacjent *current = *head;
    bool found = false;
    while (current != NULL) {
        if (strcmp(current->pesel, search) == 0 || strcmp(current->phone, search) == 0) {
            found = true;
            printf("ID: %d\n", current->id);
            printf("Name: %s\n", current->name);
            printf("Surname: %s\n", current->surname);
            printf("Pesel: %s\n", current->pesel);
            printf("Birth date: %s\n", current->birth_date);
            printf("Address: %s\n", current->address);
            printf("Email: %s\n", current->email);
            printf("Phone: %s\n", current->phone);
            printf("Weight: %f\n", current->weight);
            printf("Height: %f\n", current->height);
            int edit;
            printf("Czy chcesz edytowac dane pacjenta? (1-Tak, 0-Nie)");
            scanf("%d", &edit);
            if (edit == 1) {
                int field = -1;
                while (field != 0) {
                    printf("1.ID: %d\n", current->id);
                    printf("2.Name: %s\n", current->name);
                    printf("3.Surname: %s\n", current->surname);
                    printf("4.Address: %s\n", current->address);
                    printf("5.Email: %s\n", current->email);
                    printf("6.Phone: %s\n", current->phone);
                    printf("7.Weight: %f\n", current->weight);
                    printf("8.Height: %f\n", current->height);
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
                            printf("Wprowadz nowe imie:\n");
                            scanf("%s", current->name);
                            break;
                        case 3:
                            printf("Wprowadz nowe nazwisko:\n");
                            scanf("%s", current->surname);
                            break;
                        case 4:
                            printf("Wprowadz nowy adress:\n");
                            scanf("%s", current->address);
                            break;
                        case 5:
                            printf("Wprowadz nowy email:\n");
                            scanf("%s", current->email);
                            break;
                        case 6:
                            printf("Wprowadz nowy numer telefonu:\n");
                            scanf("%s", current->phone);
                            break;
                        case 7:
                            printf("Wprowadz nowa wage:\n");
                            scanf("%f", &current->weight);
                            break;
                        case 8:
                            printf("Wprowadz nowy wzrost:\n");
                            scanf("%f", &current->height);
                            break;
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
        printf("Nie odnaleziono pacjenta z podanymi dannymi\n");
    }
}

void search_lekarz(Lekarz **head) {
    if (*head == NULL) {
        printf("Baza pusta;\n");
        return;
    }
    printf("Wyszukiwanie lekarz\n");
    char search[20];
    printf("Wprowadz numer PESEL lekarz: \n");
    scanf("%19s", search);
    Lekarz *current = *head;
    bool found = false;
    while (current != NULL) {
        if (strcmp(current->pesel, search) == 0) {
            printf("ID: %d\n", current->id);
            printf("Name: %s\n", current->name);
            printf("Surname: %s\n", current->surname);
            printf("Pesel: %s\n", current->pesel);
            printf("PWZ: %s\n", current->pwz);
            printf("Tytul: %s\n", current->title);
            printf("Specjalizacja: %s\n", current->typ);
            printf("Email: %s\n", current->email);
            printf("Phone: %s\n", current->phone);
            printf("Godziny pracy: %s\n", current->hours);
            found = true;
            int edit;
            printf("Czy chcesz edytowac dane lekarza? (1-Tak, 0-Nie)");
            scanf("%d", &edit);
            if (edit == 1) {
                int field = -1;
                while (field != 0) {
                    printf("1.ID: %d\n", current->id);
                    printf("2.Name: %s\n", current->name);
                    printf("3.Surname: %s\n", current->surname);
                    printf("4.PWZ: %s\n", current->pwz);
                    printf("5.Email: %s\n", current->email);
                    printf("6.Phone: %s\n", current->phone);
                    printf("7.Tytul: %s\n", current->title);
                    printf("8.Specjalizacja: %s\n", current->typ);
                    printf("9.Godziny pracy: %s\n", current->hours);
                    printf("0. Wyjscie\n");
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
                            printf("Wprowadz nowe imie:\n");
                            scanf("%s", current->name);
                            break;
                        case 3:
                            printf("Wprowadz nowe nazwisko:\n");
                            scanf("%s", current->surname);
                            break;
                        case 4:
                            printf("Wprowadz nowe PWZ:\n");
                            scanf("%s", current->pwz);
                            break;
                        case 5:
                            printf("Wprowadz nowy email:\n");
                            scanf("%s", current->email);
                            break;
                        case 6:
                            printf("Wprowadz nowy numer telefonu:\n");
                            scanf("%s", current->phone);
                            break;
                        case 7:
                            printf("Wprowadz nowy tytul:\n");
                            scanf("%s", current->title);
                            break;
                        case 8:
                            printf("Wprowadz nowa specjalizacje:\n");
                            scanf("%s", current->typ);
                            break;
                        case 9:
                            printf("Wprowadz nowe godziny pracy:\n");
                            scanf("%s", current->hours);
                            break;
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
        printf("Nie odnaleziono lekarza");
    }

}
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
                            scanf("%s", current->date);
                            break;
                        case 5:
                            printf("Wprowadz nowy czas:\n");
                            scanf("%s", current->time);
                            break;
                        case 6:
                            printf("Wprowadz nowa trwalosc:\n");
                            scanf("%d", &current->duration);
                            break;
                        case 7:
                            printf("Wprowadz nowy status:\n");
                            scanf("%d", &current->status);
                            break;
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
void delete_pacjent(Pacjent **head) {
    if (*head == NULL) {
        printf("Baza pusta;\n");
        return;
    }
    int target_id;
    printf("Usuwanie pacjenta\n");
    printf("Podaj id pacjenta do usuniecia:\n");
    scanf("%d", &target_id);
    Pacjent *current = *head;
    Pacjent *prev = NULL;
    if (current != NULL && current->id == target_id) {
        *head = current->next;
        free(current);
        printf("Pacjent o id %d zostal usuniety\n", target_id);
        return;
    }
    while (current != NULL && current->id != target_id) {
        prev = current;
        current = current->next;
    }
    if (current == NULL) {
        printf("Pacjenta o takim id nie odnalieziono;\n");
        return;
    }

    if (current != NULL && current->id == target_id) {
        prev->next = current->next;
        free(current);
    }
    printf("Pacjent o id %d zostal usuniety\n", target_id);


}
void delete_lekarz(Lekarz **head) {
    if (*head == NULL) {
        printf("Baza pusta;\n");
        return;
    }
    int target_id;
    printf("Usuwanie lekarza\n");
    printf("Podaj id lekarza do usuniecia:\n");
    scanf("%d", &target_id);
    Lekarz *current = *head;
    Lekarz *prev = NULL;
    if (current != NULL && current->id == target_id) {
        *head = current->next;
        free(current);
        printf("Lekarz o id %d zostal usuniety\n", target_id);
        return;
    }
    while (current != NULL && current->id != target_id) {
        prev = current;
        current = current->next;
    }
    if (current == NULL) {
        printf("Lekarza o takim id nie odnaleziono\n");
        return;
    }
    if (current != NULL && current->id == target_id) {
        prev->next = current->next;
        free(current);
    }
    printf("Lekarz o id %d zostal usuniety\n", target_id);
}
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
void load_all(Wizyty **head_w, Lekarz **head_l, Pacjent **head_p) {
    load_lekarze(head_l);
    load_pacjenci(head_p);
    load_wizyty(head_w);
    printf("Baza danych zaladowana pomyslnie.\n");
}

void save_all(Wizyty *head_w, Lekarz *head_l, Pacjent *head_p) {
    save_lekarze(head_l);
    save_pacjenci(head_p);
    save_wizyty(head_w);
    printf("Wszystkie dane zostaly zapisane.\n");
}

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
                        case 2:
                            print_wizyty(head_wizyt);
                            break;
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