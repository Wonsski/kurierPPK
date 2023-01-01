#include <iostream>
#include <vector>

bool czyMozeJechac(int klient, int pozycja, std::pair<int,double**> macierzOdleglosci, std::vector<int> trasa){

    int wielkoscMacierzy = macierzOdleglosci.first;
    double** odleglosci = macierzOdleglosci.second;

    //Sprawdzenie czy mozna sie poruszyc z konkretnej pozycji do celu
    //       Aktualne polozenie      Cel
    if(odleglosci[trasa[pozycja-1]][klient] == 0){
        return false;
    }

    //Sprawdzenie czy klient nie jest juz odwiedzony
    for(int i=0; i<wielkoscMacierzy; i++){
        if(trasa[i]==klient){
            return false;
        }
    }
    return true;
}


void szukajTrasy(int pozycja, std::pair<int,double**> macierzOdleglosci, std::vector< std::vector<int> > &znalezioneTrasy, std::vector<int> trasa, bool odwiedzeni[]){

    int wielkoscMacierzy = macierzOdleglosci.first;
    double** odleglosci = macierzOdleglosci.second;

    //Czy wszyscy odwiedzeni liczba odwiedzonych == liczba klientow
    if(pozycja == wielkoscMacierzy){


        //Czy ostatni klient ma polaczenie z pierwszym klientem (domkniecie trasy)
        if(odleglosci[trasa[trasa.size()-1]][trasa[0]] != 0){

            trasa.push_back(trasa[0]); //Dopisanie pierwszego klienta na koniec trasy
            
            znalezioneTrasy.push_back(trasa); //Dodanie trasy do listy

            return;
        }
    }


    for(int i=0; i<wielkoscMacierzy; i++){

        if(czyMozeJechac(i,pozycja,macierzOdleglosci,trasa)){

            //Dopisanie klienta do trasy
            trasa.push_back(i);

            //Szukanie dalszej trasy
            szukajTrasy(pozycja+1, macierzOdleglosci, znalezioneTrasy, trasa, odwiedzeni);
            
            //Usuniecie klienta z trasy i szukanie innych opcji
            trasa.pop_back();

        }

    }

}

std::vector< std::vector<int> > znajdzDostepneTrasy(std::pair<int,double**> macierzOdleglosci){
    
    std::vector< std::vector<int> > znalezioneTrasy;

    std::vector<int> trasa;
    trasa.push_back(0); //Dodajemy 0 (Klient nr 1) jako rozpoczynajacego trase

    bool odwiedzeni[macierzOdleglosci.first];
    for(int i=0; i<macierzOdleglosci.first; i++){
        odwiedzeni[i] = false;
    }
    odwiedzeni[0] = true; //Ustawiamy pierwszego klienta jako odwiedzonego

    //Szukanie trasy

    szukajTrasy(1, macierzOdleglosci, znalezioneTrasy, trasa, odwiedzeni);

    return znalezioneTrasy;
}

void rysujTrase(std::vector<int> trasa){
    for(int i=0; i<trasa.size(); i++){
        std::cout << '(' << trasa[i];

        if(i==trasa.size()-1){
            std::cout<< ')';
        }else{
            std::cout<< ") -> ";
        }
    }
    std::cout << std::endl;
}

void wypiszZnalezioneTrasy(std::vector< std::vector<int> > znalezioneTrasy){
    for(int i=0; i<znalezioneTrasy.size(); i++){    
        rysujTrase(znalezioneTrasy[i]);
    }
}
