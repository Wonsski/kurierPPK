#include <iostream>
#include <fstream>
#include <sstream>

#include "obsluga_danych.h"
#include "struktury.h"

void wypiszInstrukcje(){
    std::cout << "Uzycie programu:" << std::endl << "./a.out nazwa_pliku" << std::endl << "./a.out -v nazwa_pliku" << std::endl;
}

std::pair<int,double**> wczytajPlik(const std::string nazwa_pliku){
    
    std::ifstream plik(nazwa_pliku);

    if(plik){
        std::stringstream ss;
        std::string tekst;

        std::vector<Trasa> wszystkieOdcinki; //Zbior wszystkich tras

        int iloscKlientow = 0;

        while(std::getline(plik, tekst, ',')){ //Pobieranie kawalkow tekstu oddzielonych przecinkiem

            Trasa trasa; //Struktura dla pojedynczego odcinka

            //Usuwanie zbednych znakow ze stringa, sprawdzenie czy dana trasa jest jednokierunkowa
            for(char &x : tekst){
                if(x=='>'){
                    trasa.jednokierunkowa=true;
                }
                if(!isdigit(x) && x!='.'){ //Wyrzucenie wszystkich znakow innych od cyfr, kropka zostaje dla zmiennoprzecinkowych
                    x=' ';
                }
            }


            //Wyłuskiwanie potrzebnych nam elementów
            ss << tekst;

            ss >> trasa.klientA;
            ss >> trasa.klientB;
            ss >> trasa.odleglosc;

            if(trasa.klientA>iloscKlientow){
                iloscKlientow = trasa.klientA;
            }                                       //Szukanie klienta o najwiekszym numerze - potrzebne do okreslenia wielkosci macierzy
            if(trasa.klientB>iloscKlientow){
                iloscKlientow = trasa.klientB;
            }


            wszystkieOdcinki.push_back(trasa); //Dodanie do zbioru
        }

        const int wielkoscMacierzy = iloscKlientow;
        double **macierzOdleglosci = new double*[wielkoscMacierzy];

        for(int i=0; i<wielkoscMacierzy; i++){ //Wyzerowanie macierzy (zapelnienie nieistniejacych polaczen zerami)
            macierzOdleglosci[i] = new double[wielkoscMacierzy];
            for(int j=0; j<wielkoscMacierzy; j++){
                macierzOdleglosci[i][j] = 0;
            }
        }

        for(int i=0; i<wszystkieOdcinki.size();i++){

            int klientA = wszystkieOdcinki[i].klientA-1;
            int klientB = wszystkieOdcinki[i].klientB-1;

            if(wszystkieOdcinki[i].jednokierunkowa){
                macierzOdleglosci[klientA][klientB] = wszystkieOdcinki[i].odleglosc; //Jednokierunkowa zapisujemy tylko jeden raz
            }else{
                macierzOdleglosci[klientA][klientB] = wszystkieOdcinki[i].odleglosc; //Dwukierunkowa zapisujemy "w obie strony"
                macierzOdleglosci[klientB][klientA] = wszystkieOdcinki[i].odleglosc;
            }

        }
        
        std::pair <int, double**> wynik;

        wynik.first = wielkoscMacierzy;
        wynik.second = macierzOdleglosci;

        return wynik; //Zwrocenie wyniku
    }

    std::pair <int, double**> wynik;

    wynik.first = 0;
    wynik.second = 0;

    return wynik; //W przypadku gdyby nie udalo sie otworzyc pliku zwraca zero

}

void wypiszOdleglosci(std::pair<int,double**> macierzOdleglosci){

    for(int i=0; i<macierzOdleglosci.first; i++){
        for(int j=0; j<macierzOdleglosci.first; j++){
            std::cout << macierzOdleglosci.second[i][j] << " ";
        }
        std::cout << std::endl;
    }

}

int ileKlientow(std::pair<int,double**> macierzOdleglosci){
    int wielkoscMacierzy = macierzOdleglosci.first;
    double** odleglosci = macierzOdleglosci.second;

    int pustyKlient = 0;

    for(int i=0; i<wielkoscMacierzy; i++){
        double suma = 0;
        for(int j=0; j<wielkoscMacierzy; j++){
            suma += odleglosci[i][j];
        }
        if(suma==0){
            pustyKlient++;
        }
    }

    return wielkoscMacierzy-pustyKlient;
}