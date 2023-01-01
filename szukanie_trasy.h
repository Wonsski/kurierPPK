#ifndef SZUKANIE_TRASY_H
#define SZUKANIE_TRASY_H



std::vector< std::vector<int> > znajdzDostepneTrasy(std::pair<int,double**> macierzOdleglosci);

void szukajTrasy(int pozycja, std::pair<int,double**> macierzOdleglosci, std::vector< std::vector<int> > &znalezioneTrasy, std::vector<int> trasa, bool odwiedzeni[]);

bool czyMozeJechac(int klient, int pozycja, std::pair<int,double**> macierzOdleglosci, std::vector<int> trasa);

void wypiszZnalezioneTrasy(std::vector< std::vector<int> > znalezioneTrasy);

void rysujTrase(std::vector<int> trasa);

#endif