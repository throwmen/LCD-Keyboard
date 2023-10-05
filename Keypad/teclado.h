#ifndef TECLADO_H
#define TECLADO_H
#include "mbed.h"
#include <string>

class Teclado
{   
    private:
        DigitalIn rows[4];
        DigitalOut cols[3];
    public:
        explicit Teclado(DigitalIn in1, DigitalIn in2, DigitalIn in3, DigitalIn in4, DigitalOut out1, DigitalOut out2, DigitalOut out3); 
        std::string leerPalabra();
        std::string borrar(std::string retorno);
        char leerKey();
};

#endif