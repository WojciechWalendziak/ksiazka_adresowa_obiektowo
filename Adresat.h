#include <iostream>
#include <vector>

using namespace std;
using std::vector;

class Adresat: public Osoba
{
    int id, id_uzytkownika;
    string imie, nazwisko, numerTelefonu, email, adres;

public:
    Adresat(int id = 0, int id_uzytkownika = 0, string imie = "", string nazwisko = "", string numerTelefonu = "", string email = "", string adres = "");
    vector<Adresat> wczytaj_adresatow(int id_uzytkownika);
    void dodaj_adresata(int id_uzytkownika);
    void znajdz_imiona_nazwiska(int numer, int id_uzytkownika);
    void pokaz_wszystkich(int id_uzytkownika);
    void usun_adresata(int id_uzytkownika);
    void edytuj_adresata(int id_uzytkownika);
    void wyloguj();
};
