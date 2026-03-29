#include "pacjent.h"


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
    int sort_col_pac = 1;
    int sort_dir_pac = 1;
    int compare_pac(const void *a, const void *b) {
        Pacjent *l1 = *(Pacjent **)a;
        Pacjent *l2 = *(Pacjent **)b;
        int result = 0;
        if (sort_col_pac == 1) {
            result = l1->id - l2->id;
        }
        else if (sort_col_pac == 2) {
            result = stricmp(l1->name, l2->name);
        }
        else if (sort_col_pac == 3) {
            result = stricmp(l1->surname, l2->surname);
        }
        else if (sort_col_pac == 4) {
            result = stricmp(l1->pesel, l2->pesel);
        }
        else if (sort_col_pac == 5) {
            result = stricmp(l1->nfz, l2->nfz);
        }
        if (sort_dir_pac == 2) {
            result = -result;
        }
        return result;
    }
    void sort_pacjent(Pacjent **head) {
        if (*head == NULL || (*head)->next == NULL) {
            printf("Baza jest pusta lub ma tylko jednego lekarza. Nie ma co sortowac!\n");
            return;
        }
        int count = 0;
        Pacjent *current = *head;
        while (current != NULL) {
            count++;
            current = current->next;
        }
        Pacjent **tab = malloc(count * sizeof(Pacjent *));
        if (tab == NULL) {
            printf("Blad pamieci!\n");
            return;
        }

        current = *head;
        for (int i = 0; i < count; i++) {
            tab[i] = current;
            current = current->next;
        }
        printf("Po jakim polu chcesz sortowac? (1-Id, 2-Imie, 3-Nazwisko, 4-Pesel, 5-Oddzial NFZ)\n");
        scanf("%d", &sort_col_pac);
        printf("W jakim kierunku chcesz sortowac? (1-Rosnaco, 2-Malejaco)\n");
        scanf("%d", &sort_dir_pac);
        qsort(tab, count, sizeof(Pacjent *), compare_pac);
        for (int i = 0; i < count - 1; i++) {
            tab[i]->next = tab[i + 1];
        }
        tab[count - 1]->next = NULL;
        *head = tab[0];
        for (int i = 0; i < count; i++) {
            printf("ID: %d | %s %s %s | %s\n", tab[i]->id, tab[i]->name, tab[i]->surname, tab[i]->pesel, tab[i]->nfz);
        }
        free(tab);
    }
