#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <conio.h>
#include "Osoba.h"
#include "Uzytkownik.h"

using namespace std;

Uzytkownik::Uzytkownik(int i, string log, string pass)
{
    id = i;
    login = log;
    haslo = pass;
}
vector<Uzytkownik> Uzytkownik::wczytaj_uzytkownikow()
{
    int i, x, id_number = 0, licznik = 0;
    string linia = "", login = "", haslo = "";
    Uzytkownik uzytkownik(0, "null", "null");
    vector <Uzytkownik> lista_uzytkownikow;
    fstream uzytkownicy;
    uzytkownicy.open("uzytkownicy.txt", ios::in);
    if(uzytkownicy.good()==false)
    {
        return lista_uzytkownikow;
    }
    else
    {
        while(getline(uzytkownicy, linia))
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
                            id_number = id_number + (linia[x]-48)*uzytkownik.potega_dziesiec(i-x-1);
                        }
                        x++;
                    }
                }
                i++;
            }while(licznik != 1);
            licznik = 0;
            i = 0;
            do
            {
                if(linia[i] == '|')
                {
                    licznik++;
                    switch(licznik)
                    {
                        case 1:
                            uzytkownik.id = id_number;
                            id_number = 0;
                            break;
                        case 2:
                            for(x; x < i; x++)
                            {
                                login = login + linia[x];
                            }
                            x = x + 1;
                            uzytkownik.login = login;
                            login = "";
                            break;
                        case 3:
                            for(x; x < i; x++)
                            {
                                haslo = haslo + linia[x];
                            }
                            x = x + 1;
                            uzytkownik.haslo = haslo;
                            haslo = "";
                            break;
                    }
                }
                i++;
            }while(licznik != 3);
            licznik = 0;
            lista_uzytkownikow.push_back(uzytkownik);
        };
    }
    uzytkownicy.close();
    return lista_uzytkownikow;
}
void Uzytkownik::rejestracja()
{
    char znak = 'x';
    int i = 0, poprawnosc_danych = 1, koniec = 0, wybrany_numer = 0;
    string login, haslo;
    Uzytkownik uzytkownik(0, "null", "null");
    vector <Uzytkownik> lista_uzytkownikow;
    fstream uzytkownicy;
    uzytkownicy.open("uzytkownicy.txt", ios::out | ios::app);
    if(uzytkownicy.good()==false)
    {
        exit(0);
    }
    else
    {
        lista_uzytkownikow = wczytaj_uzytkownikow();
        if(lista_uzytkownikow.size() > 0)
        {
            uzytkownik.id = lista_uzytkownikow[lista_uzytkownikow.size()-1].id + 1;
        }
        else
        {
            uzytkownik.id = 1;
        }
        while(poprawnosc_danych == 1)
        {
            while(znak != 13)
            {
                cout << "Podaj nazwe: ";
                cin >> login;
                znak = 13;
                if(lista_uzytkownikow.size() > 0)
                {
                    for(i = 0; i < lista_uzytkownikow.size(); i++)
                    {
                        if(lista_uzytkownikow[i].login == login)
                        {
                            cout << "Podany login juz istnieje. Wybierz ENTER żeby zakończyć program lub wcisnij dowolny inny klawisz zeby wczytac nowy login" << endl;
                            znak = getch();
                            if(znak == 13)
                            {
                                uzytkownik.zakoncz_program();
                            }
                            i = lista_uzytkownikow.size();
                        }
                        else
                        {
                            znak = 13;
                        }
                    }
                }
            }
            znak = 'x';
            while(znak != 13)
            {
                cout << "Podaj haslo: ";
                cin >> haslo;
                znak = 13;
                if(lista_uzytkownikow.size() > 0)
                {
                    for(i = 0; i < lista_uzytkownikow.size(); i++)
                    {
                        if(lista_uzytkownikow[i].haslo == haslo)
                        {
                            cout << "Podany login juz istnieje. Wybierz ENTER żeby zakończyć program lub wcisnij dowolny inny klawisz zeby wczytac nowy login" << endl;
                            znak = getch();
                            if(znak == 13)
                            {
                                uzytkownik.zakoncz_program();
                            }
                            i = lista_uzytkownikow.size();
                        }
                        else
                        {
                            znak = 13;
                        }
                    }
                }
            }
            poprawnosc_danych = 0;
            uzytkownik.login = login;
            uzytkownik.haslo = haslo;
            uzytkownicy<<uzytkownik.id<<"|"<<uzytkownik.login<<"|"<<uzytkownik.haslo<<"|"<<endl;
        }
    }
    uzytkownicy.close();
    lista_uzytkownikow.erase(lista_uzytkownikow.begin(),lista_uzytkownikow.begin() + lista_uzytkownikow.size());

        system("cls");
        cout << "wybierz akcje" << endl;
             cout << "1. Logowanie" << endl;
             cout << "2. Rejestracja" << endl;
             cout << "3. Zamknij program" << endl;
             cin >> wybrany_numer;
             switch(wybrany_numer)
                    {
                        case 1:
                            uzytkownik.logowanie();
                            break;
                        case 2:
                            uzytkownik.rejestracja();
                            break;
                        case 3:
                            uzytkownik.zakoncz_program();
                            break;
                    }
}
int Uzytkownik::sprawdzenie_hasla(string haslo)
{
    string linia = "", nazwa_w_bazie_danych = "", haslo_w_bazie_danych = "";
    Uzytkownik uzytkownik(0, "null", "null");
    vector <Uzytkownik> lista_uzytkownikow;
    int i = 0, x = 0, licznik = 0, haslo_poprawne = 0, poprawnosc_danych = 0;
    fstream uzytkownicy, uzytkownicy_tymczasow;
     lista_uzytkownikow = wczytaj_uzytkownikow();
    if(lista_uzytkownikow.size() > 0)
    {
        for(i = 0; i < lista_uzytkownikow.size(); i++)
        {
            if(lista_uzytkownikow[i].haslo == haslo)
            {
                poprawnosc_danych = lista_uzytkownikow[i].id;
            }
        }
    }
    lista_uzytkownikow.erase(lista_uzytkownikow.begin(),lista_uzytkownikow.begin()+lista_uzytkownikow.size());
    return poprawnosc_danych;
}
void Uzytkownik::zmien_haslo(int id_uzytkownika)
{
    int i = 0, poprawnosc_danych = 1;
    char znak = 'x';
    fstream uzytkownicy;
    string nowe_haslo = "", nowe_haslo_bis = "";
    Uzytkownik uzytkownik(0, "null", "null");
    vector <Uzytkownik> lista_uzytkownikow;
    lista_uzytkownikow = wczytaj_uzytkownikow();
    for(i = 0; i < lista_uzytkownikow.size(); i++)
    {
        if(lista_uzytkownikow[i].id == id_uzytkownika)
        {
            cout << "Podaj nowe haslo: " << endl;
            cin >> nowe_haslo;
            cout << "Powtorz haslo: " << endl;
            cin >> nowe_haslo_bis;
            if(nowe_haslo == nowe_haslo_bis)
            {
                poprawnosc_danych = sprawdzenie_hasla(nowe_haslo);
                if(poprawnosc_danych == 0)
                {
                    lista_uzytkownikow[i].haslo = nowe_haslo;
                }
                else
                {
                    while(znak != 13)
                    {
                        cout << "Podane haslo jest juz zajete. Wcisnij ENTER zeby kontynuowac" << endl;
                        znak = getch();
                    }
                }
                i = lista_uzytkownikow.size();
            }
            else
            {
                while(znak != 13)
                {
                    cout << "Hasla sa niezgodne. Wcisnij ENTER zeby kontynuowac" << endl;
                    znak = getch();
                }
                i = lista_uzytkownikow.size();
            }
        }
    }
    uzytkownicy.open("uzytkownicy.txt", ios::out);
    for(i = 0; i < lista_uzytkownikow.size(); i++)
    {
         uzytkownicy<<lista_uzytkownikow[i].id<<"|"<<lista_uzytkownikow[i].login<<"|"<<lista_uzytkownikow[i].haslo<<"|"<<endl;
    }
    uzytkownicy.close();
    lista_uzytkownikow.erase(lista_uzytkownikow.begin(),lista_uzytkownikow.begin()+lista_uzytkownikow.size());
}
int Uzytkownik::sprawdzenie_uzytkownika(string login, string haslo)
{
    string linia = "", nazwa_w_bazie_danych = "", haslo_w_bazie_danych = "";
    Uzytkownik uzytkownik(0, "null", "null");
    vector <Uzytkownik> lista_uzytkownikow;
    int i = 0, x = 0, licznik = 0, login_poprawny = 0, haslo_poprawne = 0, poprawnosc_danych = 0;
    fstream uzytkownicy;
    uzytkownicy.open("uzytkownicy.txt", ios::out | ios::app);
    if(uzytkownicy.good()==false)
    {
        exit(0);
    }
    lista_uzytkownikow = wczytaj_uzytkownikow();
    if(lista_uzytkownikow.size() > 0)
    {
        for(i = 0; i < lista_uzytkownikow.size(); i++)
        {
            if(lista_uzytkownikow[i].login == login && lista_uzytkownikow[i].haslo == haslo)
            {
                poprawnosc_danych = lista_uzytkownikow[i].id;
            }
        }
    }
    lista_uzytkownikow.erase(lista_uzytkownikow.begin(),lista_uzytkownikow.begin()+lista_uzytkownikow.size());
    return poprawnosc_danych;
}
