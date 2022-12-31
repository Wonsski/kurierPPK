#ifndef STRUKTURY_H
#define STRUKTURY_H

/**
 * Struktura Trasa zawiera wszystkie informacje na temat odcinka pomiedzy dwoma klientami
*/
struct Trasa{
    bool jednokierunkowa = false;
    int klientA;
    int klientB;
    double odleglosc;
};

#endif