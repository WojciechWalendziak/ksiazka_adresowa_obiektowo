#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <conio.h>
#include "Osoba.h"
#include "Adresat.h"

using namespace std;

Adresat::Adresat(int x, int y, string name, string surname, string phone, string mail, string adress)
{
    id = x;
    id_uzytkownika = y;
    imie = name;
    nazwisko = surname;
    numerTelefonu = phone;
    email = mail;
    adres = adress;
}
vector<Adresat> Adresat::wczytaj_adresatow(int id_uzytkownika)
{
    char znak = 'x';
    int i = 0, x = 0, id_number = 0, licznik = 0, id_uzytkownika_w_linii = 0;
    string imie = "", nazwisko = "", telefon = "", email = "", adres = "", linia;
    Adresat adresat(0, 0, "null", "null", "null", "null", "null");
    vector <Adresat> adresaci;
    fstream ksiazka_adresowa;
    ksiazka_adresowa.open("ksiazka_adresowa.txt", ios::in);
    if(ksiazka_adresowa.good()==false)
    {
        return adresaci;
    }
    else
    {
        while(getline(ksiazka_adresowa, linia))
        {
            i = 0;
            x = 0;
            do
            {
                if(linia[i] == '|')
                {
                    licznik++;
                    if(licznik == 1)
                    {
                        for(x = 0; x < i; x++)
                        {
                            id_number = id_number + (linia[x]-48)*potega_dziesiec(i-x-1);
                        }
                        x++;
                    }
                    if(licznik == 2)
                    {
                        for(x; x < i; x++)
                        {
                            id_uzytkownika_w_linii = id_uzytkownika_w_linii + (linia[x]-48)*potega_dziesiec(i-x-1);
                        }
                        x++;
                    }
                }
                i++;
            }while(licznik != 2);
            licznik = 0;
            i = 0;
            if(id_uzytkownika_w_linii == id_uzytkownika)
            {
            do
            {
                if(linia[i] == '|')
                {
                    licznik++;
                    switch(licznik)
                    {
                        case 1:
                            adresat.id = id_number;
                            id_number = 0;
                            break;
                        case 2:
                            adresat.id_uzytkownika = id_uzytkownika_w_linii;
                            id_uzytkownika_w_linii = 0;
                            break;
                        case 3:
                            for(x; x < i; x++)
                            {
                                imie = imie + linia[x];
                            }
                            x = x + 1;
                            adresat.imie = imie;
                            imie = "";
                            break;
                        case 4:
                            for(x; x < i; x++)
                            {
                                nazwisko = nazwisko + linia[x];
                            }
                            x = x + 1;
                            adresat.nazwisko = nazwisko;
                            nazwisko = "";
                            break;
                        case 5:
                            for(x; x < i; x++)
                            {
                                telefon = telefon + linia[x];
                            }
                            x = x + 1;
                            adresat.numerTelefonu = telefon;
                            telefon = "";
                            break;
                        case 6:
                            for(x; x < i; x++)
                            {
                                email = email + linia[x];
                            }
                            x = x + 1;
                            adresat.email = email;
                            email = "";
                            break;
                        case 7:
                            for(x; x < i; x++)
                            {
                                adres = adres + linia[x];
                            }
                            adresat.adres = adres;
                            adres = "";
                            break;
                    }
                }
                i++;
            }while(licznik != 7);
             adresaci.push_back(adresat);
            }
            id_number = 0;
            id_uzytkownika_w_linii = 0;
            licznik = 0;
        };
        ksiazka_adresowa.close();
    }
    return adresaci;
}
void Adresat::dodaj_adresata(int id_uzytkownika){

    int i = 0, x = 0, id_number = 0, licznik = 0;
    string linia = "";
    Adresat adresat(0, 0, "null", "null", "null", "null", "null");
    fstream ksiazka_adresowa;
    ksiazka_adresowa.open("ksiazka_adresowa.txt", ios::in);
    if(ksiazka_adresowa.good()==false)
    {
        id_number = 0;
    }
    else
    {
        while(getline(ksiazka_adresowa, linia))
        {
             i = 0;
         x = 0;
         id_number = 0;
         licznik = 0;
         do
         {
             if(linia[i] == '|')
                {
                    licznik++;
                    if(licznik == 1)
                    {
                        for(x = 0; x < i; x++)
                        {
                            id_number = id_number + (linia[x]-48)*potega_dziesiec(i-x-1);
                        }
                        x++;
                    }
                }
         i++;
         }while(licznik != 1);
        }
        ksiazka_adresowa.close();
    }
    ksiazka_adresowa.open("ksiazka_adresowa.txt", ios::out | ios::app);
    if(ksiazka_adresowa.good()==false)
    {
        exit(0);
    }
    else
    {
        adresat.id = id_number + 1;
        adresat.id_uzytkownika = id_uzytkownika;
        cout << "Podaj imie: ";
        cin >> adresat.imie;
        cout << "Podaj nazwisko: ";
        cin >> adresat.nazwisko;
        cout << "Podaj numer Telefonu: ";
        cin.sync();
        getline(cin, adresat.numerTelefonu);
        cout << "Podaj email: ";
        cin >> adresat.email;
        cout << "Podaj adres: ";
        cin.sync();
        getline(cin, adresat.adres);
        cout << endl;
        ksiazka_adresowa<<adresat.id<<"|"<<id_uzytkownika<<"|"<<adresat.imie<<"|"<<adresat.nazwisko<<"|"<<adresat.numerTelefonu<<"|"<<adresat.email<<"|"<<adresat.adres<<"|"<<endl;
        ksiazka_adresowa.close();
    }
}
void Adresat::znajdz_imiona_nazwiska(int numer, int id_uzytkownika){

    int i;
    char znak = 'x';
    string dana_szukana;
    Adresat adresat(0, 0, "null", "null", "null", "null", "null");
    vector <Adresat> adresaci;
    adresaci = wczytaj_adresatow(id_uzytkownika);
    if(numer == 2)
    {
        cout << "Podaj szukane imie: ";
        cin >> dana_szukana;
        for(i = 0; i < adresaci.size(); i++)
        {
            if(adresaci[i].imie == dana_szukana)
            {
                cout << "ID: " << adresaci[i].id << endl;
                cout << "Imie: " << adresaci[i].imie << endl;
                cout << "Nazwisko: " << adresaci[i].nazwisko << endl;
                cout << "Telefon: " << adresaci[i].numerTelefonu << endl;
                cout << "Email: " << adresaci[i].email << endl;
                cout << "Adres: " << adresaci[i].adres << endl;
                cout << endl;
            }
        }
    }
    else
    {
        cout << "Podaj szukane nazwisko: ";
        cin >> dana_szukana;
        for(i = 0; i < adresaci.size(); i++)
        {
            if(adresaci[i].nazwisko == dana_szukana)
            {
                cout << "ID: " << adresaci[i].id << endl;
                cout << "Imie: " << adresaci[i].imie << endl;
                cout << "Nazwisko: " << adresaci[i].nazwisko << endl;
                cout << "Telefon: " << adresaci[i].numerTelefonu << endl;
                cout << "Email: " << adresaci[i].email << endl;
                cout << "Adres: " << adresaci[i].adres << endl;
                cout << endl;
            }
        }
    }
    while(znak != 13)
    {
        cout << "Wcisnij ENTER zeby kontynuowac" << endl;
        znak = getch();
    }
    adresaci.erase (adresaci.begin(),adresaci.begin()+adresaci.size());
}
void Adresat::pokaz_wszystkich(int id_uzytkownika){

    int i;
    char znak = 'x';
    Adresat adresat(0, 0, "null", "null", "null", "null", "null");
    vector <Adresat> adresaci;
    adresaci = wczytaj_adresatow(id_uzytkownika);
    for(i = 0; i < adresaci.size(); i++)
    {
        cout << "ID: " << adresaci[i].id << endl;
        cout << "Imie: " << adresaci[i].imie << endl;
        cout << "Nazwisko: " << adresaci[i].nazwisko << endl;
        cout << "Telefon: " << adresaci[i].numerTelefonu << endl;
        cout << "Email: " << adresaci[i].email << endl;
        cout << "Adres: " << adresaci[i].adres << endl;
        cout << endl;
    }
    while(znak != 13)
    {
        cout << "Wcisnij ENTER zeby kontynuowac" << endl;
        znak = getch();
    }
    adresaci.erase(adresaci.begin(),adresaci.begin()+adresaci.size());
}
void Adresat::usun_adresata(int id_uzytkownika)
{
    char znak = 'x';
    int id_do_usuniecia = 0, x = 0, i = 0, id = 0, id_number = 0, licznik = 0;
    string imie, nazwisko, telefon, email, adres, linia;
    fstream ksiazka_adresowa, adresaci_tymczasowy;
    Adresat adresat(0, 0, "null", "null", "null", "null", "null");
    vector <Adresat> adresaci;
    while(znak != 116)
    {
        cout << "Podaj numer id do usuniecia: ";
        cin >> id_do_usuniecia;
        cout << "Jezeli potwierdzasz usuniecie Adresata o numerze ID " << id_do_usuniecia << " wczytaj z klawiatury mala litere <t>" << endl;
        znak = getch();
    }
    adresaci = wczytaj_adresatow(id_uzytkownika);
     for(i = 0; i < adresaci.size(); i++)
     {
         if(adresaci[i].id == id_do_usuniecia)
         {
             adresaci.erase(adresaci.begin()+i);
             x = 1;
             i = adresaci.size();
         }
     }
     if(x == 1)
     {
         adresaci_tymczasowy.open("adresaci_tymczasowy.txt", ios::out);
         ksiazka_adresowa.open("ksiazka_adresowa.txt", ios::in);
     if(ksiazka_adresowa.good()==false)
     {
         exit(0);
     }
     else
     {
         while(getline(ksiazka_adresowa, linia))
     {
         i = 0;
         x = 0;
         id_number = 0;
         licznik = 0;
         do
         {
             if(linia[i] == '|')
                {
                    licznik++;
                    if(licznik == 1)
                    {
                        for(x = 0; x < i; x++)
                        {
                            id_number = id_number + (linia[x]-48)*potega_dziesiec(i-x-1);
                        }
                        x++;
                    }
                }
         i++;
         }while(licznik != 1);
         if(id_number != id_do_usuniecia)
         {
             adresaci_tymczasowy<<linia<<endl;
         }
     }
     }
     ksiazka_adresowa.close();
     adresaci_tymczasowy.close();
     adresaci_tymczasowy.open("adresaci_tymczasowy.txt", ios::in);
     ksiazka_adresowa.open("ksiazka_adresowa.txt", ios::out);
     if(ksiazka_adresowa.good()==false || adresaci_tymczasowy.good()==false)
     {
         exit(0);
     }
     else
     {
         while(getline(adresaci_tymczasowy, linia))
     {
         ksiazka_adresowa<<linia<<endl;
     }
     }
     while(znak != 13)
     {
         cout << "Wcisnij ENTER zeby kontynuowac" << endl;
         znak = getch();
     }
     }
     else
     {
         while(znak != 13)
         {
             cout << "Nie ma adresata z takim id. Wcisnij ENTER zeby kontynuowac" << endl;
             znak = getch();
         }
     }
     adresaci.erase(adresaci.begin(),adresaci.begin()+adresaci.size());
}
void Adresat::edytuj_adresata(int id_uzytkownika)
{
    char znak = 'x';
    int id_number = 0, id_uzytkownika_w_linii = 0, id_do_edycji = 0, wybrany_numer = 0, i = 0, x = 0, licznik = 0, numer_adresata;
    string linia = "", imie = "", nazwisko = "", telefon = "", email = "", adres = "";
    fstream ksiazka_adresowa, adresaci_tymczasowy;
    Adresat adresat(0, 0, "null", "null", "null", "null", "null");
    vector <Adresat> adresaci;
    cout << "Podaj numer id do edycji: ";
    cin >> id_do_edycji;
    adresaci = wczytaj_adresatow(id_uzytkownika);
     for(i = 0; i < adresaci.size(); i++)
     {
         if(adresaci[i].id == id_do_edycji)
         {
             cout << "wskaz element do edycji" << endl;
             cout << "1. imie" << endl;
             cout << "2. nazwisko" << endl;
             cout << "3. numer telefonu" << endl;
             cout << "4. email" << endl;
             cout << "5. adres" << endl;
             cout << "6. powrot do menu" << endl;
             cin >> wybrany_numer;
             numer_adresata = i;
             switch(wybrany_numer)
                    {
                        case 1:
                            cout << "Podaj nowe imie: ";
                            cin >> imie;
                            adresaci[i].imie = imie;
                            break;
                        case 2:
                            cout << "Podaj nowe nazwisko: ";
                            cin >> nazwisko;
                            adresaci[i].nazwisko = nazwisko;
                            break;
                        case 3:
                            cout << "Podaj nowy telefon: ";
                            cin >> telefon;
                            adresaci[i].numerTelefonu = telefon;
                            break;
                        case 4:
                            cout << "Podaj nowy email: ";
                            cin >> email;
                            adresaci[i].email = email;
                            break;
                        case 5:
                            cout << "Podaj nowy adres: ";
                            cin.sync();
                            getline(cin, adres);
                            adresaci[i].adres = adres;
                            break;
                        case 6:
                            znak = 13;
                            break;
                    }
         }
     }
     if(wybrany_numer == 0)
        {
             while(znak != 13)
             {
                 cout << "Adresat o podanym numerze nie istnieje. Wcisnij ENTER aby ponownie sie zalogowac" << endl;
                 znak = getch();
             }
             Adresat::logowanie();
         }
     adresaci_tymczasowy.open("adresaci_tymczasowy.txt", ios::out);
     ksiazka_adresowa.open("ksiazka_adresowa.txt", ios::in);
     if(ksiazka_adresowa.good()==false)
     {
         exit(0);
     }
     else
     {
      while(getline(ksiazka_adresowa, linia))
     {
         i = 0;
         x = 0;
         id_number = 0;
         id_uzytkownika_w_linii = 0;
         licznik = 0;
         do
         {
             if(linia[i] == '|')
                {
                    licznik++;
                    if(licznik == 1)
                    {
                        for(x = 0; x < i; x++)
                        {
                            id_number = id_number + (linia[x]-48)*potega_dziesiec(i-x-1);
                        }
                        x++;
                    }
                }
         i++;
         }while(licznik != 1);
         if(id_number == id_do_edycji)
         {
             adresaci_tymczasowy<<id_do_edycji<<"|"<<id_uzytkownika<<"|"<<adresaci[numer_adresata].imie<<"|"<<adresaci[numer_adresata].nazwisko<<"|"<<adresaci[numer_adresata].numerTelefonu<<"|"<<adresaci[numer_adresata].email<<"|"<<adresaci[numer_adresata].adres<<"|"<<endl;
         }
         else
         {
             adresaci_tymczasowy<<linia<<endl;
         }
     }
     }
     ksiazka_adresowa.close();
     adresaci_tymczasowy.close();
     adresaci_tymczasowy.open("adresaci_tymczasowy.txt", ios::in);
     ksiazka_adresowa.open("ksiazka_adresowa.txt", ios::out);
     if(ksiazka_adresowa.good()==false || adresaci_tymczasowy.good()==false)
     {
         exit(0);
     }
     else
     {
      while(getline(adresaci_tymczasowy, linia))
     {
         ksiazka_adresowa<<linia<<endl;
     }
     }
     while(znak != 13)
     {
         cout << "Wcisnij ENTER zeby kontynuowac" << endl;
         znak = getch();
     }
     adresaci.erase(adresaci.begin(),adresaci.begin()+adresaci.size());
}
void Adresat::wyloguj()
{
    char znak = 'x';
    int wybrany_numer = 0, i = 0;
    string imie = "", nazwisko = "", telefon = "", email = "", adres = "";

             cout << "wskaz kolejn¹ akcjê: " << endl;
             cout << "1. Logowanie" << endl;
             cout << "2. Zamknij program" << endl;
             cin >> wybrany_numer;
             switch(wybrany_numer)
                    {
                        case 1:
                            Adresat::logowanie();
                            break;
                        case 2:
                            Adresat::zakoncz_program();
                            break;
                    }
}
