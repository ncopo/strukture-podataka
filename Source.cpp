#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 50

typedef struct _osoba* Pozicija;

typedef struct _osoba {
    char ime[MAX_SIZE];
    char prezime[MAX_SIZE];
    int god;

    Pozicija Next;
} osoba;

int UnosNaPocetak(Pozicija P);
int UnosNaKraj(Pozicija P);
int IspisListe(Pozicija P);
int PronadiPoPrezimenu(Pozicija P);
int ObrisiOsobu(Pozicija P);

int main() {
    osoba Head;
    Head.Next = NULL;
    int Choice;

    while (1) {
        printf("\nUnesi:\n1 - Unos na pocetak\n2 - Unos na kraj\n3 - Ispis liste\n4 - Trazi po prezimenu\n5 - Obrisi po prezimenu\n6 - Izlaz\n");
        printf("Izbor: ");
        if (scanf("%d", &Choice) != 1) {
            printf("Greska u unosu.\n");
            break;
        }

        switch (Choice) {
            case 1:
                UnosNaPocetak(&Head);
                break;
            case 2:
                UnosNaKraj(&Head);
                break;
            case 3:
                IspisListe(Head.Next);
                break;
            case 4:
                PronadiPoPrezimenu(Head.Next);
                break;
            case 5:
                ObrisiOsobu(&Head);
                break;
            case 6:
                printf("Izlaz iz programa.\n");
                return 0;
            default:
                printf("Nisi unio ispravan broj, pokusaj ponovno!\n");
                break;
        }
    }

    return EXIT_SUCCESS;
}

int UnosNaPocetak(Pozicija P) {
    Pozicija Q = (Pozicija)malloc(sizeof(osoba));

    if (!Q) {
        printf("Neuspjesna alokacija memorije.\n");
        return 1;
    }

    printf("Unesi ime osobe: ");
    scanf("%s", Q->ime);
    printf("Unesi prezime osobe: ");
    scanf("%s", Q->prezime);
    printf("Unesi godinu rodenja osobe: ");
    scanf("%d", &Q->god);

    Q->Next = P->Next;
    P->Next = Q;

    return 0;
}


int UnosNaKraj(Pozicija P) {
    Pozicija Q = (Pozicija)malloc(sizeof(osoba));

    if (!Q) {
        printf("Neuspjesna alokacija memorije.\n");
        return 1;
    }

    while (P->Next != NULL) {
        P = P->Next;
    }

    printf("Unesi ime osobe: ");
    scanf("%s", Q->ime);
    printf("Unesi prezime osobe: ");
    scanf("%s", Q->prezime);
    printf("Unesi godinu rodenja osobe: ");
    scanf("%d", &Q->god);

    Q->Next = NULL;
    P->Next = Q;

    return 0;
}


int IspisListe(Pozicija P) {
    if (!P) {
        printf("Lista je prazna.\n");
        return 0;
    }

    printf("\nLista osoba:\n");
    while (P != NULL) {
        printf("%s %s %d\n", P->ime, P->prezime, P->god);
        P = P->Next;
    }

    return 0;
}


int PronadiPoPrezimenu(Pozicija P) {
    char prezime[MAX_SIZE];
    printf("Unesi prezime osobe koju zelis pronaci: ");
    scanf("%s", prezime);

    while (P != NULL && strcmp(prezime, P->prezime) != 0) {
        P = P->Next;
    }

    if (P == NULL) {
        printf("Osoba s prezimenom %s nije pronadjena.\n", prezime);
    } else {
        printf("Pronadjena osoba: %s %s %d\n", P->ime, P->prezime, P->god);
    }

    return 0;
}


int ObrisiOsobu(Pozicija P) {
    char prezime[MAX_SIZE];
    Pozicija temp = NULL;

    printf("Unesi prezime osobe koju zelis obrisati: ");
    scanf("%s", prezime);

    while (P->Next != NULL && strcmp(prezime, P->Next->prezime) != 0) {
        P = P->Next;
    }

    if (P->Next == NULL) {
        printf("Osoba s prezimenom %s ne postoji.\n", prezime);
        return 1;
    }

    temp = P->Next;
    P->Next = temp->Next;
    free(temp);

    printf("Osoba s prezimenom %s je uspjesno obrisana.\n", prezime);

    return 0;
}
