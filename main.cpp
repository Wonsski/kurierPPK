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
        
        //Argumenty programu
        std::string nazwa_pliku;
        std::string plik_zapis = "wyjscie.txt"; //Domyslna nazwa pliku wyjsciowego
        bool wypisuj = false;
        int klient_start = 1;

        if(!zaladujArgumenty(argc, args, nazwa_pliku, plik_zapis, wypisuj, klient_start)){return 0;}

        

        //Wczytywanie danych
        std::pair<int,double**> macierzOdleglosci;
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

        delete[] macierzOdleglosci.second; //Czyszczenie pamieci
    }

    return 0;
}