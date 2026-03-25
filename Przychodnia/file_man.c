#include "file_man.h"

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
    printf("Baza danych zaladowana pomyslnie.\n");
}

void save_all(Wizyty *head_w, Lekarz *head_l, Pacjent *head_p) {
    save_lekarze(head_l);
    save_pacjenci(head_p);
    save_wizyty(head_w);
    printf("Wszystkie dane zostaly zapisane.\n");
}