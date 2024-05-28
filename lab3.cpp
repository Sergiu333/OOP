#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

// Definirea tipului pentru DataCalendaristica
using DataCalendaristica = struct tm;

// Clasa Tranzactie
class Tranzactie {
private:
    string tipTranzactie;
    double suma;
    DataCalendaristica data;

public:
    Tranzactie(const string& tip, double suma, const DataCalendaristica& data)
        : tipTranzactie(tip), suma(suma), data(data) {}

    string getTipTranzactie() const { return tipTranzactie; }
    double getSuma() const { return suma; }
    DataCalendaristica getData() const { return data; }
};

// Clasa de baza CardBancar
class CardBancar {
protected:
    string numarCard;
    string numeProprietar;
    DataCalendaristica dataExpirare;
    double soldCont;

public:
    CardBancar(const string& numar, const string& nume, const DataCalendaristica& data, double sold)
        : numarCard(numar), numeProprietar(nume), dataExpirare(data), soldCont(sold) {}

    // Gettere si settere
    string getNumarCard() const { return numarCard; }
    string getNumeProprietar() const { return numeProprietar; }
    DataCalendaristica getDataExpirare() const { return dataExpirare; }
    double getSoldCont() const { return soldCont; }

    void setSoldCont(double sold) { soldCont = sold; }

    // Metode comune
    virtual void afiseazaMiniExtras() const {
        cout << "Numar card: " << numarCard << endl;
        cout << "Nume proprietar: " << numeProprietar << endl;
        cout << "Sold curent: " << soldCont << endl;
    }

    virtual void istoricTranzactii() const = 0;

    // Metode virtuale pentru extrageri si supliniri
    virtual void extrageBani(double suma) = 0;
    virtual void suplimenteazaCont(double suma) = 0;
};

// Clasa derivată CardDebit
class CardDebit : public CardBancar {
private:
    vector<Tranzactie> istoricTranzactiiDebit;

public:
    CardDebit(const string& numar, const string& nume, const DataCalendaristica& data, double sold)
        : CardBancar(numar, nume, data, sold) {}

    void extrageBani(double suma) override {
        // Implementarea extragerii de bani pentru CardDebit
    }

    void suplimenteazaCont(double suma) override {
        // Implementarea suplimentarii contului pentru CardDebit
    }

    void istoricTranzactii() const override {
        for (const auto& tranzactie : istoricTranzactiiDebit) {
            cout << "Tip tranzactie: " << tranzactie.getTipTranzactie() << endl;
            cout << "Suma: " << tranzactie.getSuma() << endl;
            DataCalendaristica data = tranzactie.getData();
            cout << "Data: " << asctime(&data) << endl;
        }
    }
};

// Clasa derivata CardCredit
class CardCredit : public CardBancar {
private:
    vector<Tranzactie> istoricTranzactiiCredit;

public:
    CardCredit(const string& numar, const string& nume, const DataCalendaristica& data, double sold)
        : CardBancar(numar, nume, data, sold) {}

    void extrageBani(double suma) override {
        // Implementarea extragerii de bani pentru CardCredit
    }

    void suplimenteazaCont(double suma) override {
        // Implementarea suplimentării contului pentru CardCredit
    }

    void istoricTranzactii() const override {
        for (const auto& tranzactie : istoricTranzactiiCredit) {
            cout << "Tip tranzactie: " << tranzactie.getTipTranzactie() << endl;
            cout << "Suma: " << tranzactie.getSuma() << endl;
            DataCalendaristica data = tranzactie.getData();
            cout << "Data: " << asctime(&data) << endl;
        }
    }
};

// Clasa Proprietar
class Proprietar {
private:
    vector<CardBancar*> listaCarduri;

public:
    // Adaugă un card la lista proprietarului
    void adaugaCard(CardBancar* card) {
        listaCarduri.push_back(card);
    }

    // Efectueaza o tranzactie pentru un anumit card
    void efectueazaTranzactie(int indexCard, const string& tipTranzactie, double suma) {
        if (indexCard >= 0 && indexCard < listaCarduri.size()) {
            if (tipTranzactie == "Extragere") {
                listaCarduri[indexCard]->extrageBani(suma);
            } else if (tipTranzactie == "Suplimentare") {
                listaCarduri[indexCard]->suplimenteazaCont(suma);
            }
        } else {
            cout << "Indice de card invalid." << endl;
        }
    }

    // afiseaza miniextras pentru un anumit card
    void afiseazaMiniExtras(int indexCard) const {
        if (indexCard >= 0 && indexCard < listaCarduri.size()) {
            listaCarduri[indexCard]->afiseazaMiniExtras();
        } else {
            cout << "Indice de card invalid." << endl;
        }
    }

    // afiseaza istoricul tranzactiilor pentru un anumit card
    void afiseazaIstoricTranzactii(int indexCard) const {
        if (indexCard >= 0 && indexCard < listaCarduri.size()) {
            listaCarduri[indexCard]->istoricTranzactii();
        } else {
            cout << "Indice de card invalid." << endl;
        }
    }

    // afiseaza miniextras și istoricul tranzactiilor pentru toate cardurile
    void afiseazaDetaliiToateCardurile() const {
        for (size_t i = 0; i < listaCarduri.size(); ++i) {
            cout << "Detalii card " << i + 1 << ":" << endl;
            afiseazaMiniExtras(i);
            afiseazaIstoricTranzactii(i);
            cout << endl;
        }
    }
};

int main() {
    // Data de expirare pentru carduri
    DataCalendaristica dataExp = {};
    dataExp.tm_mday = 31; // Z
    dataExp.tm_mon = 11; // luna (0-11, deci 11 = Decembrie)
    dataExp.tm_year = 124; // anul de la 1900 (124 + 1900 = 2024)

    // Crearea unui card debit
    CardDebit cardDebit("1234", "Anghelenici Sergiu", dataExp, 5000);
    // Crearea unui card credit
    CardCredit cardCredit("5678", "Anghelenici Sergiu", dataExp, 2000);

    // Crearea unui proprietar și adaugarea cardurilor
    Proprietar johnDoe;
    johnDoe.adaugaCard(&cardDebit);
    johnDoe.adaugaCard(&cardCredit);

    // Efectuarea unor tranzactii
    johnDoe.efectueazaTranzactie(0, "Extragere", 300);
    johnDoe.efectueazaTranzactie(0, "Suplimentare", 150);
    johnDoe.efectueazaTranzactie(1, "Extragere", 2500);
    johnDoe.efectueazaTranzactie(1, "Extragere", 3000);

    // Afisarea detaliilor pentru toate cardurile
    johnDoe.afiseazaDetaliiToateCardurile();

    return 0;
}

