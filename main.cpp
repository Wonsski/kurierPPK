#include <iostream>
#include <vector>

#include "funkcje.h"

int main(int argc, char *args[]){
    
    //Dla programu uruchomionego bez argumentow
    if(argc==1){
        wypiszInstrukcje();
    }else{ //Dla przynajmniej jednego arguementu
        
        std::pair<int,double**> macierzOdleglosci = wczytajPlik(args[1]);

        wypiszOdleglosci(macierzOdleglosci);
    }

    return 0;
}