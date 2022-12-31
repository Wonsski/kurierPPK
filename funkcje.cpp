#include <iostream>
#include <fstream>
#include <sstream>

#include "funkcje.h"

void wypiszInstrukcje(){
    std::cout << "Uzycie programu:" << std::endl << "./a.out nazwa_pliku" << std::endl;
}

void wczytajPlik(std::string nazwa_pliku){
    
    std::ifstream plik(nazwa_pliku);

    if(plik){
        std::stringstream ss;
        std::string tekst;

        while(std::getline(plik, tekst,',')){

            bool jednokierunkowa = false;

            //Usuwanie zbednych znakow ze stringa, sprawdzenie czy dana trasa jest jednokierunkowa
            for(char &x : tekst){
                if(x=='>'){
                    jednokierunkowa=true;
                }
                if(!isdigit(x) && x!='.'){ //Wyrzucenie wszystkich znakow innych od cyfr, kropka zostaje dla zmiennoprzecinkowych
                    x=' ';
                }
            }


            //Wyłuskiwanie potrzebnych nam elementów
            ss << tekst;

            int klientA;
            int klientB;
            double odleglosc;

            ss >> klientA;
            ss >> klientB;
            ss >> odleglosc;

            std::cout << jednokierunkowa << ' ' << klientA << " " << klientB << " " << odleglosc << std::endl;

        }
    }

}

void wypiszOdleglosci(std::vector< std::vector<double> > macierz){

    for(int i=0; i<macierz.size(); i++){
        for(int j=0; j<macierz[i].size(); j++){
            std::cout << macierz[i][j] << " ";
        }
        std::cout<<std::endl;
    }

}