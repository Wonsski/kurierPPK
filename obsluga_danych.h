#ifndef OBSLUGA_DANYCH_H
#define OBSLUGA_DANYCH_H

#include <vector>

/**
 * Funkcja wypisuje instrukcje korzystania z programu
*/
void wypiszInstrukcje();

/**
 * Funkcja wczytujace dane z pliku wejsciowego i normalizujaca dane wejsciowe do odpowiedniego formatu
 * @return Zwraca macierz zawierającą odleglosci pomiedzy wszystkimi punktami
 * @param nazwa_pliku Nazwa pliku tekstowego z którego wczytujemy dane wejściowe
*/
std::pair<int,double**> wczytajPlik(const std::string nazwa_pliku);

/**
 * Funkcja wypisuje zawartosc macierzy zawierajacej odleglosci
 * @param macierzOdleglosci Struktura zawierajaca wielkosc macierzy oraz macierz z danymi wejsciowymi
*/
void wypiszOdleglosci(std::pair<int,double**> macierzOdleglosci);

/**
 * Funkcja zwraca liczbe klientow (gdyby numery klientow byly nie po kolei)
 * @return Zwraca liczbe klientow
 * @param macierzOdleglosci Struktura zawierajaca wielkosc macierzy oraz macierz z danymi wejsciowymi
*/
int ileKlientow(std::pair<int,double**> macierzOdleglosci);
#endif