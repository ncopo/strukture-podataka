#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Student {
    string ime;
    string prezime;
    int bodovi;
};

int brojRedakaDatoteke(const string& imeDatoteke) {
    ifstream file(imeDatoteke);
    int brojRedaka = 0;
    string linija;

    while (getline(file, linija)) {
        brojRedaka++;
    }

    file.close();
    return brojRedaka;
}

void ucitajStudente(const string& imeDatoteke, Student* studenti, int brojStudenata, int& maxBodovi) {
    ifstream file(imeDatoteke);
    maxBodovi = 0;

    for (int i = 0; i < brojStudenata; i++) {
        file >> studenti[i].ime >> studenti[i].prezime >> studenti[i].bodovi;

        if (studenti[i].bodovi > maxBodovi) {
            maxBodovi = studenti[i].bodovi;
        }
    }

    file.close();
}

void ispisiStudente(Student* studenti, int brojStudenata, int maxBodovi) {
    for (int i = 0; i < brojStudenata; i++) {
        double relativniBodovi = (double)studenti[i].bodovi / maxBodovi * 100;
        cout << "Ime: " << studenti[i].ime << ", Prezime: " << studenti[i].prezime
             << ", Bodovi: " << studenti[i].bodovi << ", Relativni broj bodova: " 
             << relativniBodovi << "%" << endl;
    }
}

int main() {
    string imeDatoteke = "studenti.txt";

    // Prvo čitanje broja redaka
    int brojStudenata = brojRedakaDatoteke(imeDatoteke);
    if (brojStudenata == 0) {
        cout << "Datoteka je prazna ili nije pronadena!" << endl;
        return 1;
    }

    // Dinamička alokacija memorije za studente
    Student* studenti = new Student[brojStudenata];

    // Učitavanje studenata i traženje maksimalnog broja bodova
    int maxBodovi = 0;
    ucitajStudente(imeDatoteke, studenti, brojStudenata, maxBodovi);

    // Ispis studenata s apsolutnim i relativnim brojem bodova
    ispisiStudente(studenti, brojStudenata, maxBodovi);

    // Oslobađanje memorije
    delete[] studenti;

    return 0;
}
