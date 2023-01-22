#include <iostream>
#include <vector>
#include <iomanip>
#include <cstring>

#include "obsluga_danych.h"
#include "szukanie_trasy.h"

int main(int argc, char *args[]){
    
    //Dla programu uruchomionego bez argumentow
    if(argc==1){
        wypiszInstrukcje(args[0]);
    }else{ //Dla przynajmniej jednego argumentu
        
        std::string nazwa_pliku;
        std::string plik_zapis = "wyjscie.txt"; //Domyslna nazwa pliku wyjsciowego
        std::pair<int,double**> macierzOdleglosci;


        //Sprawdzanie wybranych opcji
        int licznikWlaczonychOpcji = 0;
        bool wypisuj = false;
        bool ustawStart = false;
        int klient_start = 1;

        for(int i=1; i<argc; i++){
            if(strcmp( args[i], "-v") == 0){
                wypisuj=true;
                licznikWlaczonychOpcji++;
            }
            if(strcmp( args[i], "-s") == 0){
                ustawStart=true;
                licznikWlaczonychOpcji+=2;    //Plus parametr s  

                if(args[i+1]){
                    klient_start = atoi(args[i+1]); 
                }else{
                    std::cout << "Opcja -s potrzebuje parametru. Instrukcja jak to zrobić jest dostępna po uruchomieniu programu bez parametrów" << std::endl;
                    return 0;
                }    
            }
        }

        int indeksParamNazwaPliku = 1+licznikWlaczonychOpcji;
        int indeksParamNazwaZapisPliku = 2+licznikWlaczonychOpcji;

        if(args[indeksParamNazwaPliku] && licznikWlaczonychOpcji+1<argc){
            nazwa_pliku = args[indeksParamNazwaPliku];

            if(args[indeksParamNazwaZapisPliku]){
                plik_zapis = args[indeksParamNazwaZapisPliku];
            }
        }else{
            std::cout << "Podaj poprawnie parametry. Instrukcja jak to zrobić jest dostępna po uruchomieniu programu bez parametrów" << std::endl;
            return 0;
        }

        //Wczytywanie danych
        macierzOdleglosci = wczytajPlik(nazwa_pliku);
        

        if(wypisuj){
            //Wypisanie wczytanych danych
            wypiszOdleglosci(macierzOdleglosci);
        }

        //Generowanie dostepnych tras
        std::cout << std::endl << "Start od klienta nr: " << klient_start << std::endl;

        std::vector< std::vector<int> >znalezioneTrasy = znajdzDostepneTrasy(klient_start,macierzOdleglosci);
        
        if(znalezioneTrasy.size()>0){
            
            if(wypisuj){
                //Wypisanie znalezionych tras
                wypiszZnalezioneTrasy(znalezioneTrasy,macierzOdleglosci);
            }

            //Znalezienie najkrotszej trasy
            std::vector<int> najkrotszaTrasa;
            double dlugoscNajkrotszejTrasy;
            wybierzNajkrotszaTrase(0, znalezioneTrasy.size()-1, dlugoscNajkrotszejTrasy, najkrotszaTrasa, znalezioneTrasy,macierzOdleglosci);

            //Wypisz najkrotsza trase
            std::cout << std::endl;
            std::cout << std::setfill('-') << std::setw(30) << '-' << std::setfill(' ') << std::endl;
            std::cout << std::setw(7) << ' ' << "WYNIKI PROGRAMU" << std::endl;
            std::cout << std::setfill('-') << std::setw(30) << '-' << std::setfill(' ') << std::endl;

            std::cout << "Znaleziona trasa:" << std::endl;
            rysujTrase(najkrotszaTrasa);
            std::cout << std::endl << std::endl << "Łączna długość trasy: " << dlugoscNajkrotszejTrasy << std::endl << std::endl;

            //Zapisz wynik
            zapiszDoPliku(plik_zapis,najkrotszaTrasa,dlugoscNajkrotszejTrasy);

        }else{
            //Brak tras
            std::cout << std::endl;
            std::cout << std::setfill('-') << std::setw(63) << '-' << std::setfill(' ') << std::endl;
            std::cout << std::setw(20) << ' ' << "NIE MOŻNA UTWORZYĆ TRASY" << std::endl;
            std::cout << std::setfill('-') << std::setw(63) << '-' << std::setfill(' ') << std::endl;
            std::cout << "Nie udało się utworzyć trasy korzystając z wprowadzonych danych" <<std::endl;
            std::cout << "Wprowadzony plik wejściowy: " << nazwa_pliku << std::endl << std::endl;
        }
    }

    return 0;
}