#include <iostream>
#include <vector>
#include <iomanip>

#include "obsluga_danych.h"
#include "szukanie_trasy.h"

int main(int argc, char *args[]){
    
    //Dla programu uruchomionego bez argumentow
    if(argc==1){
        wypiszInstrukcje(args[0]);
    }else{ //Dla przynajmniej jednego argumentu
        
        std::string nazwa_pliku;
        std::string plik_zapis = "wyjscie.txt"; //Domyslna nazwa pliku wyjsciowego
        bool wypisuj = false;
        std::pair<int,double**> macierzOdleglosci;

        if(strcmp( args[1], "-v") == 0){

            wypisuj=true;

            if(!args[2]){
                std::cout << "Dodaj argument z nazwą pliku!" << std::endl;
                return 0;
            }
            nazwa_pliku = args[2];

            if(args[3]){
                plik_zapis = args[3];
            }
        }else{
            if(!args[1]){
                std::cout << "Dodaj argument z nazwą pliku!" << std::endl;
                return 0;
            }
            nazwa_pliku = args[1];
            if(args[2]){
                plik_zapis = args[2];
            }
        }

        //Wczytywanie danych
        macierzOdleglosci = wczytajPlik(nazwa_pliku);
        

        if(wypisuj){
            //Wypisanie wczytanych danych
            wypiszOdleglosci(macierzOdleglosci);
        }

        //Generowanie dostepnych tras
        std::vector< std::vector<int> >znalezioneTrasy = znajdzDostepneTrasy(macierzOdleglosci);
        
        if(znalezioneTrasy.size()>0){
            
            if(wypisuj){
                //Wypisanie znalezionych tras
                wypiszZnalezioneTrasy(znalezioneTrasy,macierzOdleglosci);
            }

            //Znalezienie najkrotszej trasy
            std::pair<double, std::vector<int> > najkrotszaTrasa = wybierzNajkrotszaTrase(znalezioneTrasy,macierzOdleglosci);

            //Wypisz najkrotsza trase
            std::cout << std::endl;
            std::cout << std::setfill('-') << std::setw(30) << '-' << std::setfill(' ') << std::endl;
            std::cout << std::setw(7) << ' ' << "WYNIKI PROGRAMU" << std::endl;
            std::cout << std::setfill('-') << std::setw(30) << '-' << std::setfill(' ') << std::endl;

            std::cout << "Znaleziona trasa:" << std::endl;
            rysujTrase(najkrotszaTrasa.second);
            std::cout << std::endl << std::endl << "Łączna długość trasy: " << najkrotszaTrasa.first << std::endl << std::endl;

            //Zapisz wynik
            zapiszDoPliku(plik_zapis,najkrotszaTrasa);

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