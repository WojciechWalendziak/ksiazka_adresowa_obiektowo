#include <iostream>
#include <vector>

using namespace std;
using std::vector;

class Uzytkownik: public Osoba
{
    int id = 0;
    string login = "", haslo = "";

public:
    Uzytkownik(int id = 0, string login = "", string haslo = "");
    vector<Uzytkownik> wczytaj_uzytkownikow();
    void rejestracja();
    int sprawdzenie_hasla(string haslo);
    void zmien_haslo(int id_uzytkownika);
    int sprawdzenie_uzytkownika(string login, string haslo);
};
