#include <iostream>
#include <vector>
#include <iomanip>

#include "obsluga_danych.h"

bool czyMozeJechac(const int &klient, const int &pozycja, const std::pair<int,double**> &macierzOdleglosci, const std::vector<int> &trasa){

    int wielkoscMacierzy = macierzOdleglosci.first;
    double** odleglosci = macierzOdleglosci.second;

    //Sprawdzenie czy mozna sie poruszyc z konkretnej pozycji do celu
    //       Aktualne polozenie      Cel     Brak połączenia
    if(odleglosci[trasa[pozycja-1]][klient] == 0){
        return false;
    }
    
    return true;
}


void szukajTrasy(int pozycja, std::pair<int,double**> &macierzOdleglosci, std::vector< std::vector<int> > &znalezioneTrasy, std::vector<int> trasa, const int &ileKlientow, bool odwiedzeni[]){

    int wielkoscMacierzy = macierzOdleglosci.first;
    double** odleglosci = macierzOdleglosci.second;

    //Czy wszystkich odwiedzilismy       liczba odwiedzonych == liczba klientow
    if(pozycja == ileKlientow){


        //Czy ostatni klient ma polaczenie z pierwszym klientem (domkniecie trasy)
        if(odleglosci[trasa[trasa.size()-1]][trasa[0]] != 0){

            trasa.push_back(trasa[0]); //Dopisanie pierwszego klienta na koniec trasy
            
            znalezioneTrasy.push_back(trasa); //Dodanie trasy do listy

            return;
        }
    }


    for(int i=0; i<wielkoscMacierzy; i++){

        if(czyMozeJechac(i,pozycja,macierzOdleglosci,trasa) && !odwiedzeni[i]){

            //Dopisanie klienta do trasy
            trasa.push_back(i);
            odwiedzeni[i] = true;

            //Szukanie dalszej trasy
            szukajTrasy(pozycja+1, macierzOdleglosci, znalezioneTrasy, trasa, ileKlientow, odwiedzeni);
            
            //Usuniecie klienta z trasy i szukanie innych opcji
            trasa.pop_back();
            odwiedzeni[i] = false;

        }

    }

}

std::vector< std::vector<int> > znajdzDostepneTrasy(std::pair<int,double**> macierzOdleglosci){
    
    std::vector< std::vector<int> > znalezioneTrasy;

    std::vector<int> trasa;
    trasa.push_back(0); //Dodajemy 0 (Klient nr 1) jako rozpoczynajacego trase

    int wielkoscMacierzy = macierzOdleglosci.first;
    bool odwiedzeni[wielkoscMacierzy];
    for(int i=0; i<wielkoscMacierzy; i++){
        odwiedzeni[i]=false;
    }
    odwiedzeni[0] = true;


    //Szukanie trasy
    szukajTrasy(1, macierzOdleglosci, znalezioneTrasy, trasa, ileKlientow(macierzOdleglosci), odwiedzeni);

    return znalezioneTrasy;
}

void rysujTrase(std::vector<int> trasa){
    for(int i=0; i<trasa.size(); i++){
        std::cout << '(' << trasa[i]+1;

        if(i==trasa.size()-1){
            std::cout<< ')';
        }else{
            std::cout<< ") -> ";
        }
    }
}

double obliczDlugoscTrasy(std::vector<int> trasa, std::pair<int,double**> macierzOdleglosci){
    
    int wielkoscMacierzy = macierzOdleglosci.first;
    double** odleglosci = macierzOdleglosci.second;

    double dlugoscTrasy = 0;

    for(int i=1; i<trasa.size(); i++){
        dlugoscTrasy += odleglosci[trasa[i-1]][trasa[i]];
    }

    return dlugoscTrasy;
}

void wypiszZnalezioneTrasy(std::vector< std::vector<int> > znalezioneTrasy, std::pair<int,double**> macierzOdleglosci){
    
    std::cout << std::endl;
    std::cout << std::setfill('-') << std::setw(30) << '-' << std::setfill(' ') << std::endl;
    std::cout << std::setw(7) << ' ' << "ZNALEZIONE TRASY" << std::endl;
    std::cout << std::setfill('-') << std::setw(30) << '-' << std::setfill(' ') << std::endl;

    for(int i=0; i<znalezioneTrasy.size(); i++){    
        std::cout << i+1 << '.' << ' ';
        rysujTrase(znalezioneTrasy[i]);
        std::cout << " | Długość trasy: " << obliczDlugoscTrasy(znalezioneTrasy[i],macierzOdleglosci) << std::endl;
    }
}


std::pair<double, std::vector<int> > wybierzNajkrotszaTrase(std::vector< std::vector<int> > znalezioneTrasy, std::pair<int,double**> macierzOdleglosci){

    int indeksNajkrotszejTrasy = 0; //Domyslne pierwsza trasa najkrotsza
    double dlugoscNajkrotszejTrasy = obliczDlugoscTrasy(znalezioneTrasy[0],macierzOdleglosci);

    //Dla pozostalych tras
    for(int i=0; i<znalezioneTrasy.size(); i++){
        double dlugoscTrasy = obliczDlugoscTrasy(znalezioneTrasy[i],macierzOdleglosci);

        if(dlugoscTrasy<dlugoscNajkrotszejTrasy){
            indeksNajkrotszejTrasy = i;
            dlugoscNajkrotszejTrasy = dlugoscTrasy;
        }
    }

    //Spakowanie wynikow
    std::pair<double, std::vector<int> > wynik;
    wynik.first = dlugoscNajkrotszejTrasy;
    wynik.second = znalezioneTrasy[indeksNajkrotszejTrasy];

    return wynik;

}
