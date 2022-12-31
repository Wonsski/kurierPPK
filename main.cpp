#include <iostream>
#include <vector>

#include "funkcje.h"

int main(int argc, char *args[]){
    
    //Dla programu uruchomionego bez argumentow
    if(argc==1){
        wypiszInstrukcje();
    }else{ //Dla przynajmniej jednego arguementu
        //std::vector< std::vector<double> > odleglosci;
        
        wczytajPlik(args[1]);

        //wypiszOdleglosci(odleglosci);
    }

    return 0;
}