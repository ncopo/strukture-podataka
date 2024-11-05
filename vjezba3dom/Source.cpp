#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 50

struct _osoba;
typedef struct _osoba* Pozicija;

typedef struct _osoba {
    char ime[MAX_SIZE];
    char prezime[MAX_SIZE];
    int god;
    Pozicija Next;
} osoba;

int UnosP(Pozicija P);
int UnosK(Pozicija P);
int Ispis(Pozicija P);
Pozicija TraziPrezime(Pozicija P);
int Brisi(Pozicija P);
int UnosIza(Pozicija P);
int UnosIspred(Pozicija P);
int SortUnos(Pozicija P);
int WriteData(Pozicija P);
int ReadData(Pozicija P);
int OslobodiMemoriju(Pozicija P);

int main() {
    osoba Head = { .ime = {0}, .prezime = {0}, .god = 0 };
    Head.Next = NULL;
    char Choice;

    while (1) {
        printf("\nUnesi znak:\n"
               "A (unos na pocetak)\n"
               "B (unos na kraj)\n"
               "C (ispis)\n"
               "D (trazi po prezimenu)\n"
               "E (brisi)\n"
               "F (dodaj iza)\n"
               "G (dodaj ispred)\n"
               "H (sortirani unos)\n"
               "I (upisi u datoteku)\n"
               "J (citaj iz datoteke)\n"
               "X (izlaz)\n\n");

        (void)scanf(" %c", &Choice);

        switch (Choice) {
            case 'A': UnosP(&Head); break;
            case 'B': UnosK(&Head); break;
            case 'C': Ispis(Head.Next); break;
            case 'D': TraziPrezime(Head.Next); break;
            case 'E': Brisi(&Head); break;
            case 'F': UnosIza(&Head); break;
            case 'G': UnosIspred(&Head); break;
            case 'H': SortUnos(&Head); break;
            case 'I': WriteData(Head.Next); break;
            case 'J': ReadData(&Head); break;
            case 'X': OslobodiMemoriju(Head.Next); return EXIT_SUCCESS;
            default: printf("Nisi unio ispravan znak, pokusaj ponovno!\n"); break;
        }
    }
}

int UnosP(Pozicija P) {
    Pozicija Q = (Pozicija)malloc(sizeof(osoba));
    if (!Q) {
        printf("Neuspjesna alokacija memorije.\n");
        return 1;
    }

    printf("Unesi ime osobe: ");
    (void)scanf("%s", Q->ime);
    printf("Unesi prezime osobe: ");
    (void)scanf("%s", Q->prezime);
    printf("Unesi godinu rodenja osobe: ");
    (void)scanf("%d", &Q->god);

    Q->Next = P->Next;
    P->Next = Q;

    return 0;
}

int UnosK(Pozicija P) {
    while (P->Next) P = P->Next;

    Pozicija Q = (Pozicija)malloc(sizeof(osoba));
    if (!Q) {
        printf("Neuspjesna alokacija memorije.\n");
        return 1;
    }

    printf("Unesi ime osobe: ");
    (void)scanf("%s", Q->ime);
    printf("Unesi prezime osobe: ");
    (void)scanf("%s", Q->prezime);
    printf("Unesi godinu rodenja osobe: ");
    (void)scanf("%d", &Q->god);

    Q->Next = P->Next;
    P->Next = Q;

    return 0;
}

int Ispis(Pozicija P) {
    if (!P) {
        printf("Lista je prazna.\n");
        return 0;
    }

    while (P) {
        printf("%s %s %d\n", P->ime, P->prezime, P->god);
        P = P->Next;
    }

    return 0;
}

Pozicija TraziPrezime(Pozicija P) {
    char prez[MAX_SIZE];
    printf("Unesi prezime osobe koju zelis pronaci:\n");
    (void)scanf("%s", prez);

    while (P && strcmp(prez, P->prezime) != 0) P = P->Next;

    if (!P) printf("Ne postoji osoba pod tim prezimenom.\n");
    else printf("Pronadena osoba: %s %s %d\n", P->ime, P->prezime, P->god);

    return P;
}

int Brisi(Pozicija P) {
    char prez[MAX_SIZE];
    Pozicija temp;

    printf("Unesi prezime osobe koju zelis pronaci:\n");
    (void)scanf("%s", prez);

    while (P->Next && strcmp(prez, P->Next->prezime) != 0) P = P->Next;

    if (!P->Next) {
        printf("Osoba s prezimenom %s ne postoji.\n", prez);
        return 1;
    }

    temp = P->Next;
    P->Next = temp->Next;
    free(temp);

    printf("Osoba s prezimenom %s je uspjesno izbrisana.\n", prez);
    return 0;
}

int UnosIza(Pozicija P) {
    Pozicija newP = (Pozicija)malloc(sizeof(osoba));
    if (!newP) {
        printf("Neuspjesna alokacija memorije!\n");
        return 1;
    }

    printf("Unesi ime osobe: ");
    (void)scanf("%s", newP->ime);
    printf("Unesi prezime osobe: ");
    (void)scanf("%s", newP->prezime);
    printf("Unesi godinu rodenja osobe: ");
    (void)scanf("%d", &newP->god);

    char prez[MAX_SIZE];
    printf("Upisi prezime osobe iza koje zelis dodati novu osobu:\n");
    (void)scanf("%s", prez);

    while (P && strcmp(prez, P->prezime) != 0) P = P->Next;

    newP->Next = P->Next;
    P->Next = newP;

    return 0;
}

int UnosIspred(Pozicija P) {
    Pozicija newP = (Pozicija)malloc(sizeof(osoba));
    if (!newP) {
        printf("Neuspjesna alokacija memorije!\n");
        return 1;
    }

    printf("Unesi ime osobe: ");
    (void)scanf("%s", newP->ime);
    printf("Unesi prezime osobe: ");
    (void)scanf("%s", newP->prezime);
    printf("Unesi godinu rodenja osobe: ");
    (void)scanf("%d", &newP->god);

    char prez[MAX_SIZE];
    printf("Upisi prezime osobe ispred koje zelis dodati novu osobu:\n");
    (void)scanf("%s", prez);

    while (P->Next && strcmp(prez, P->Next->prezime) != 0) P = P->Next;

    if (!P->Next) {
        printf("Osoba s prezimenom %s ne postoji.\n", prez);
        free(newP);
        return 1;
    }

    newP->Next = P->Next;
    P->Next = newP;
    return 0;
}

int WriteData(Pozicija P) {
    FILE* fp = fopen("osobe.txt", "w");
    if (!fp) {
        printf("Greska, datoteka se ne moze otvoriti!\n");
        return 1;
    }

    while (P) {
        fprintf(fp, "%s %s %d\n", P->ime, P->prezime, P->god);
        P = P->Next;
    }

    fclose(fp);
    printf("Podaci su uspjesno zapisani u datoteku.\n");
    return 0;
}

int ReadData(Pozicija P) {
    FILE* fp = fopen("osobe.txt", "r");
    if (!fp) {
        printf("Greska u otvaranju datoteke!\n");
        return 1;
    }

    
    while (P->Next) {
        Pozicija temp = P->Next;
        P->Next = temp->Next;
        free(temp);
    }

    char name[MAX_SIZE], surname[MAX_SIZE];
    int birthYear;

    while (fscanf(fp, "%s %s %d", name, surname, &birthYear) == 3) {
        Pozicija q = (Pozicija)malloc(sizeof(osoba));
        if (!q) {
            printf("Neuspjesna alokacija memorije!\n");
            fclose(fp);
            return 1;
        }

        strcpy(q->ime, name);
        strcpy(q->prezime, surname);
        q->god = birthYear;

        q->Next = P->Next;
        P->Next = q;
    }

    fclose(fp);
    printf("Podaci su uspjesno ucitani iz datoteke.\n");
    return 0;
}

int SortUnos(Pozicija P) {
    Pozicija q = (Pozicija)malloc(sizeof(osoba));
    if (!q) {
        printf("Neuspjesna alokacija memorije.\n");
        return 1;
    }

    printf("Unesi ime osobe: ");
    (void)scanf("%s", q->ime);
    printf("Unesi prezime osobe: ");
    (void)scanf("%s", q->prezime);
    printf("Unesi godinu rodenja osobe: ");
    (void)scanf("%d", &q->god);

    while (P->Next && strcmp(q->prezime, P->Next->prezime) > 0) P = P->Next;

    q->Next = P->Next;
    P->Next = q;

    return 0;
}

int OslobodiMemoriju(Pozicija P) {
    while (P) {
        Pozicija temp = P;
        P = P->Next;
        free(temp);
    }

    return 0;
}
