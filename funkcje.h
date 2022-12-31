#ifndef FUNKCJE_H
#define FUNKCJE_H

#include <vector>

/**
 * Funkcja wypisuje instrukcje korzystania z programu
*/
void wypiszInstrukcje();

/**
 * @return Zwraca macierz zawierającą odleglosci pomiedzy wszystkimi punktami
 * @param nazwa_pliku Nazwa pliku tekstowego z którego wczytujemy dane wejściowe
*/
std::pair<int,double**> wczytajPlik(const std::string nazwa_pliku);

/**
 * Funkcja wypisuje zawartosc macierzy zawierajacej odleglosci
 * @param macierz Wektor wektorów typu double zawierający odległości pomiędzy wszystkimi punktami
*/
void wypiszOdleglosci(std::pair<int,double**> macierzOdleglosci);
#endif