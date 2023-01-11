#ifndef SZUKANIE_TRASY_H
#define SZUKANIE_TRASY_H


/**
 * Funkcja wyszukujaca wszystkie mozliwe trasy przejazdu
 * @return Zwraca wektor wektorow zawierajacych wszystkie mozliwe trasy
 * @param macierzOdleglosci Struktura zawierajaca wielkosc macierzy oraz macierz z danymi wejsciowymi
*/
std::vector< std::vector<int> > znajdzDostepneTrasy(std::pair<int,double**> macierzOdleglosci);

/**
 * Funkcja rekurencyjna dobierajaca odpowiednie kombinacje 
 * @return Wyniki rekurencji zapisywane sa w parametrsze wejsciowym znalezioneTrasy
 * @param pozycja Aktualna pozycja kuriera, punkt odniesienia do nastpnego punktu docelowego
 * @param macierzOdleglosci Struktura zawierajaca wielkosc macierzy oraz macierz z danymi wejsciowymi
 * @param znalezioneTrasy Wektor przetrzymujacy wyniki rekurencji
 * @param trasa Wektor zawierajacy aktualna trase przejazdu
*/
void szukajTrasy(int pozycja, std::pair<int,double**> macierzOdleglosci, std::vector< std::vector<int> > &znalezioneTrasy, std::vector<int> trasa);

/**
 * Funkcja sprawdza czy istnieje mozliwosc przejazdu z aktualnej pozycji do nastepnego docelowego klienta
 * @return Zwraca prawde jezeli istnieje mozliwosc przejazdu, zwraca falsz jezeli tej mozliwosci nie ma lub docelowy klient juz zostal odwiedziony
 * @param klient Docelowy punkt przejazdu
 * @param pozycja Aktualna pozycja kuriera
 * @param macierzOdleglosci Struktura zawierajaca wielkosc macierzy oraz macierz z danymi wejsciowymi
 * @param trasa Wektor zawierajacy aktualna trase przejazdu 
*/
bool czyMozeJechac(int klient, int pozycja, std::pair<int,double**> macierzOdleglosci, std::vector<int> trasa);

/**
 * Funkcja wypisujaca wszystkie mozliwe trasy przejazdu
 * @param znalezioneTrasy Wektor wektorow zawierajacych wszystkie mozliwe trasy
 * @param macierzOdleglosci Struktura zawierajaca wielkosc macierzy oraz macierz z danymi wejsciowymi
*/
void wypiszZnalezioneTrasy(std::vector< std::vector<int> > znalezioneTrasy, std::pair<int,double**> macierzOdleglosci);

/**
 * Funkcja wypisujaca pojedyncza trase w graficzny sposob typu (1) -> (2) -> (3)
 * @param trasa Wektor trasy do wypisania
*/
void rysujTrase(std::vector<int> trasa);

/**
 * Funkcja zwracajaca najkrotsza trase ze wszystkich podanych
 * @return Zwraca strukture zawierajaca dlugosc najkrotszej trasy oraz wektor zawierajacy przebieg tej trasy
 * @param znalezioneTrasy Wektor wektorow zawierajacych wszystkie mozliwe trasy z posrod ktorych ma zostac znaleziona najkrotsza trasa
 * @param macierzOdleglosci Struktura zawierajaca wielkosc macierzy oraz macierz z danymi wejsciowymi
*/
std::pair<double, std::vector<int> > wybierzNajkrotszaTrase(std::vector< std::vector<int> > znalezioneTrasy, std::pair<int,double**> macierzOdleglosci);

/**
 * Funkcja zwracajaca dlugosc trasy
 * @return Zwraca dlugosc trasy wejsciowej
 * @param trasa Wektor zawierajacy przebieg pojedynczej trasy
 * @param macierzOdleglosci Struktura zawierajaca wielkosc macierzy oraz macierz z danymi wejsciowymi
*/
double obliczDlugoscTrasy(std::vector<int> trasa, std::pair<int,double**> macierzOdleglosci);


#endif