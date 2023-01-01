#include <iostream>
#include <vector>

#include "obsluga_danych.h"
#include "szukanie_trasy.h"

int main(int argc, char *args[]){
    
    //Dla programu uruchomionego bez argumentow
    if(argc==1){
        wypiszInstrukcje();
    }else{ //Dla przynajmniej jednego argumentu
        
        std::pair<int,double**> macierzOdleglosci = wczytajPlik(args[1]);

        wypiszOdleglosci(macierzOdleglosci);

        std::vector< std::vector<int> >znalezioneTrasy = znajdzDostepneTrasy(macierzOdleglosci);

        wypiszZnalezioneTrasy(znalezioneTrasy);
    }

    return 0;
}