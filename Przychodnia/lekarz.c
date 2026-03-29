#include "lekarz.h"
    int sort_col = 1;
    int sort_dir = 1;
    int compare(const void *a, const void *b) {
        Lekarz *l1 = *(Lekarz **)a;
        Lekarz *l2 = *(Lekarz **)b;
        int result = 0;
        if (sort_col == 1) {
            result = l1->id - l2->id;
        }
        else if (sort_col == 2) {
            result = stricmp(l1->name, l2->name);
        }
        else if (sort_col == 3) {
            result = stricmp(l1->surname, l2->surname);
        }
        else if (sort_col == 4) {
            result = stricmp(l1->title, l2->title);
        }
        else if (sort_col == 5) {
            result = stricmp(l1->typ, l2->typ);
        }
        if (sort_dir == 2) {
            result = -result;
        }
        return result;
    }
    void sort_lekarz(Lekarz **head) {
        if (*head == NULL || (*head)->next == NULL) {
            printf("Baza jest pusta lub ma tylko jednego lekarza. Nie ma co sortowac!\n");
            return;
        }
        int count = 0;
        Lekarz *current = *head;
        while (current != NULL) {
            count++;
            current = current->next;
        }
        Lekarz **tab = malloc(count * sizeof(Lekarz *));
        if (tab == NULL) {
            printf("Blad pamieci!\n");
            return;
        }

        current = *head;
        for (int i = 0; i < count; i++) {
            tab[i] = current;
            current = current->next;
        }
        printf("Po jakim polu chcesz sortowac? (1-Id, 2-Imie, 3-Nazwisko, 4-Tytul, 5-Specjalizacja)\n");
        scanf("%d", &sort_col);
        printf("W jakim kierunku chcesz sortowac? (1-Rosnaco, 2-Malejaco)\n");
        scanf("%d", &sort_dir);
        qsort(tab, count, sizeof(Lekarz *), compare);
        for (int i = 0; i < count - 1; i++) {
            tab[i]->next = tab[i + 1];
        }
        tab[count - 1]->next = NULL;
        *head = tab[0];
        for (int i = 0; i < count; i++) {
            printf("ID: %d | %s %s %s | %s\n", tab[i]->id, tab[i]->title, tab[i]->name, tab[i]->surname, tab[i]->typ);
        }
        free(tab);
    }
void print_lekarze(Lekarz *head) {
    Lekarz *current = head;
    int choice = 1;
    if (current == NULL) {
        printf("Baza pusta\n");
        return;
    }
    while (current != NULL) {
        printf("ID: %d | %s %s %s | %s\n", current->id, current->title, current->name, current->surname, current->typ);
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


void search_lekarz(Lekarz **head) {
    if (*head == NULL) {
        printf("Baza pusta;\n");
        return;
    }
    printf("Wyszukiwanie lekarza\n");
    char search[20];
    printf("Wprowadz numer PESEL lekarza: \n");
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


