#include <iostream>
#include <vector>

#include "obsluga_danych.h"
#include "szukanie_trasy.h"

int main(int argc, char *args[]){
    
    //Dla programu uruchomionego bez argumentow
    if(argc==1){
        wypiszInstrukcje();
    }else{ //Dla przynajmniej jednego argumentu
        
        bool wypisuj = false;
        std::pair<int,double**> macierzOdleglosci;

        if(strcmp( args[1], "-v") == 0){

            wypisuj=true;

            //Wczytywanie danych
            macierzOdleglosci = wczytajPlik(args[2]);
        }else{

            //Wczytywanie danych
            macierzOdleglosci = wczytajPlik(args[1]);
        }

        

        if(wypisuj){
            //Wypisanie wczytanych danych
            wypiszOdleglosci(macierzOdleglosci);
        }

        //Generowanie dostepnych tras
        std::vector< std::vector<int> >znalezioneTrasy = znajdzDostepneTrasy(macierzOdleglosci);
        
        if(znalezioneTrasy.size()>0){
            
            if(wypisuj){
                //Wypisanie znalezionych tras
                wypiszZnalezioneTrasy(znalezioneTrasy);
            }

            //Znalezienie najkrotszej trasy
            std::pair<double, std::vector<int> > najkrotszaTrasa = wybierzNajkrotszaTrase(znalezioneTrasy,macierzOdleglosci);

            //Wypisz najkrotsza trase
            std::cout << najkrotszaTrasa.first << std::endl;
            rysujTrase(najkrotszaTrasa.second);

        }else{
            //Brak tras
            std::cout << "Brak tras" << std::endl;
        }
    }

    return 0;
}