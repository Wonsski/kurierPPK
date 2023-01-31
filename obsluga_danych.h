#ifndef OBSLUGA_DANYCH_H
#define OBSLUGA_DANYCH_H

#include <vector>

/**
 * Funkcja wypisuje instrukcje korzystania z programu
 * @param nazwa_programu Nazwa pliku programu
*/
void wypiszInstrukcje(std::string nazwa_programu);

/**
 * Funkcja ładuje parametry do odpowiednich zmiennych
 * @param argc Liczba argumentow
 * @param args Tablica argumentow
 * @param nazwa_pliku Nazwa otwieranego pliku
 * @param plik_zapis Nazwa pliku zapisu
 * @param wypisuj Zmienna przechowujaca informacje czy maja byc wypisywane dodatkowe informacje
 * @param klient_start Zmienna przechowujaca parametr klienta startowego 
 * @return Zwraca true, jezeli wprowadzone argumenty są prawidłowe
*/
bool zaladujArgumenty(int argc, char *args[], std::string &nazwa_pliku, std::string &plik_zapis, bool &wypisuj, int &klient_start);

/**
 * Funkcja wczytujace dane z pliku wejsciowego i normalizujaca dane wejsciowe do odpowiedniego formatu
 * @return Zwraca macierz zawierającą odleglosci pomiedzy wszystkimi punktami
 * @param nazwa_pliku Nazwa pliku tekstowego z którego wczytujemy dane wejściowe
*/
std::pair<int,double**> wczytajPlik(const std::string &nazwa_pliku);

/**
 * Funkcja wypisuje zawartosc macierzy zawierajacej odleglosci
 * @param macierzOdleglosci Struktura zawierajaca wielkosc macierzy oraz macierz z danymi wejsciowymi
*/
void wypiszOdleglosci(std::pair<int,double**> &macierzOdleglosci);

/**
 * Funkcja zwraca liczbe klientow (gdyby numery klientow byly nie po kolei)
 * @return Zwraca liczbe klientow
 * @param macierzOdleglosci Struktura zawierajaca wielkosc macierzy oraz macierz z danymi wejsciowymi
*/
int ileKlientow(std::pair<int,double**> &macierzOdleglosci);

/**
 * Funkcja zapisujaca wyniki programu do pliku
 * @param nazwa_pliku Nazwa pliku wyjściowego
 * @param trasa Wektor zawierajacy najkrotsza trase
 * @param dlugosc Dlugosc najkrotszej trasy
*/
void zapiszDoPliku(const std::string &nazwa_pliku, std::vector<int> &trasa, double &dlugosc);
#endif