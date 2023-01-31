#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

#include "obsluga_danych.h"
#include "struktury.h"

void wypiszInstrukcje(std::string nazwa_programu){
    std::cout << std::endl;
    std::cout << std::setfill('-') << std::setw(50) << '-' << std::setfill(' ') << std::endl;
    std::cout << std::setw(10) << ' ' << "INSTRUKCJA PROGRAMU - KURIER" << std::endl;
    std::cout << std::setfill('-') << std::setw(50) << '-' << std::setfill(' ') << std::endl;

    std::cout << "Program pozwala na znalezienie najkrótszej zamkniętej trasy dla kuriera" << std::endl;
    std::cout << "odwiedzającego każdego klienta tylko jeden raz" << std::endl;

    std::cout << std::endl;
    std::cout << "Program toleruje drogi jednokierunkowe, odpowiednio zapisane w pliku wejściowym" << std::endl;

    std::cout << std::endl << "Dostępne opcje: " << std::endl;
    std::cout << "  -v    Tryb \"gadatliwy\" wypisujący etapy po kolei wykonywanych operacji" << std::endl;
    std::cout << "  -s <numer klienta>    Wybór klienta rozpoczynającego trasę" << std::endl;

    std::cout << std::endl << "Argumenty programu: " << std::endl;
    std::cout << "  nazwa_pliku       [WYMAGANE]   Nazwa pliku wejściowego w którym znajdują się dane dot. odległości od klientów" << std::endl;
    std::cout << "  plik_wyjsciowy    [OPCJONALNE] Nazwa pliku w którym ma zostać zapisany wynik programu. Domyślnie wyjscie.txt" << std::endl;

    std::cout << std::endl << "UŻYCIE: " << std::endl;
    std::cout << "  " << nazwa_programu << " [opcje] nazwa_pliku plik_wyjsciowy" << std::endl;

    std::cout << std::endl << "Przykłady: " << std::endl;
    std::cout << "  " << nazwa_programu << " plik.txt" << std::endl;
    std::cout << "  " << nazwa_programu << " -v plik.txt" << std::endl;
    std::cout << "  " << nazwa_programu << " -v plik.txt tuMiZapisz.txt" << std::endl << std::endl;

    std::cout << "Autor programu: Radosław Rajda" << std::endl << std::endl;

    
}

bool zaladujArgumenty(int argc, char *args[], std::string &nazwa_pliku, std::string &plik_zapis, bool &wypisuj, int &klient_start){
    int licznikWlaczonychOpcji = 0;

    for(int i=1; i<argc; i++){
        if(strcmp( args[i], "-v") == 0){
            wypisuj=true;
            licznikWlaczonychOpcji++;
        }
        if(strcmp( args[i], "-s") == 0){
            licznikWlaczonychOpcji+=2;    //Plus parametr s  

            if(args[i+1]){
                klient_start = atoi(args[i+1]); 
            }else{
                std::cout << "Opcja -s potrzebuje parametru. Instrukcja jak to zrobić jest dostępna po uruchomieniu programu bez parametrów" << std::endl;                    
                return false;
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
        return false;
    }

    return true;
}

std::pair<int,double**> wczytajPlik(const std::string &nazwa_pliku){
    
    std::ifstream plik(nazwa_pliku);

    if(plik){
        std::string tekst;

        std::vector<Trasa> wszystkieOdcinki; //Zbior wszystkich tras

        int iloscKlientow = 0;

        while(std::getline(plik, tekst, ',')){ //Pobieranie kawalkow tekstu oddzielonych przecinkiem

            std::stringstream ss;
            Trasa trasa; //Struktura dla pojedynczego odcinka
            
            int licznik=0;
            //Usuwanie zbednych znakow ze stringa, sprawdzenie czy dana trasa jest jednokierunkowa
            for(char &x : tekst){
                if(x=='>'){
                    trasa.jednokierunkowa=true;
                }
                if(!isdigit(x) && x!='.'){ //Wyrzucenie wszystkich znakow innych od cyfr, kropka zostaje dla zmiennoprzecinkowych
                    x=' ';
                }

                if(x==' '){ //Podliczanie ilosci spacji
                    licznik++;
                }
            }
            
            if(tekst.length()==licznik) continue; //Same biale znaki w linijce - pomin

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

            if(trasa.klientA!=0 && trasa.klientB!=0 && trasa.odleglosc!=0.0)
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

void wypiszOdleglosci(std::pair<int,double**> &macierzOdleglosci){

    int wielkoscMacierzy = macierzOdleglosci.first;
    double** odleglosci = macierzOdleglosci.second;

    int offset = (macierzOdleglosci.first*7)+4;
    std::cout << std::endl;
    std::cout << std::setfill('-') << std::setw(offset) << '-' << std::setfill(' ') << std::endl;
    std::cout << std::setw((offset*0.5)*0.5) << ' ' << "MACIERZ ODLEGŁOŚCI" << std::endl;
    std::cout << std::setfill('-') << std::setw(offset) << '-' << std::setfill(' ') << std::endl;



    for(int i=1; i<=wielkoscMacierzy; i++){
        if(i==1){
            std::cout << std::setw(9) << "KL" << std::left << std::setw(5) << i;
        }else{
            std::cout << "KL" << std::left << std::setw(5) << i;
        }
    }

    std::cout << std::endl;

    for(int i=0; i<wielkoscMacierzy; i++){
        std::cout << "KL" << std::left << std::setw(5) << i+1;

        for(int j=0; j<wielkoscMacierzy; j++){
            std::cout << std::setw(7) << std::left << std::fixed << std::setprecision(1) << odleglosci[i][j];
        }
        std::cout << std::endl;
    }

}

int ileKlientow(std::pair<int,double**> &macierzOdleglosci){
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

void zapiszDoPliku(const std::string &nazwa_pliku, std::vector<int> &trasa, double &dlugosc){
    std::ofstream plik(nazwa_pliku);

    if(plik){

        plik << "Znaleziona trasa:" << std::endl;

        for(int i=0; i<trasa.size(); i++){
            plik << '(' << trasa[i]+1;

            if(i==trasa.size()-1){
                plik << ')';
            }else{
                plik << ") -> ";
            }
        }
        plik << std::endl;

        plik << "Łączna długość trasy: " << dlugosc << std::endl;
        std::cout << "Wynik zapisano w pliku: " << nazwa_pliku << std::endl;
    }else{
        std::cout << "Nie udało się zapisać wyniku do pliku: " << nazwa_pliku << std::endl;
    }
}