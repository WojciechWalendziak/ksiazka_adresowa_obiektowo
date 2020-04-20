#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <conio.h>
#include "Osoba.h"
#include "Adresat.h"
#include "Uzytkownik.h"

using namespace std;

void start()
{
    char znak = 'x';
    int id_do_edycji = 0, wybrany_numer = 0, i = 0, koniec = 0;
    string imie = "", nazwisko = "", telefon = "", email = "", adres = "";

             Osoba osoba;
             cout << "wybierz akcje" << endl;
             cout << "1. Logowanie" << endl;
             cout << "2. Rejestracja" << endl;
             cout << "3. Zamknij program" << endl;
             cin >> wybrany_numer;
              switch(wybrany_numer)
                    {
                        case 1:
                            {
                                osoba.logowanie();
                                break;
                            }
                        case 2:
                            {
                                Uzytkownik uzytkownik;
                                uzytkownik.rejestracja();
                                break;
                            }
                        case 3:
                            {
                                    osoba.zakoncz_program();
                                    break;
                            }
                    }
     while(znak != 13)
     {
         cout << "Wcisnij ENTER zeby kontynuowac" << endl;
         znak = getch();
     }
}
int main()
{
    start();
	return 0;
}
