#include "teclado.h"
#include <iostream>

char matriz [4][3] = {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'},
    {'*', '0', '#'},
    };

Teclado::Teclado(DigitalIn i1, DigitalIn i2, DigitalIn i3, DigitalIn i4, DigitalOut o1, DigitalOut o2, DigitalOut o3)
    : cols{o1, o2, o3}, rows{i1, i2, i3, i4}
{     

}

std::string Teclado::leerPalabra()
{
    string retorno ="";
    bool isEnter = false;
    while (!isEnter) {
        for (int i = 0; i < 3; i++){
            cols[i] = 0;
            for (int j  = 0; j < 4; j++){
                if(rows[j] == 0){
                    if (matriz[j][i] == '#')
                        isEnter = true;
                    else if (matriz[j][i] == '*')
                        retorno = borrar(retorno);
                    else
                        retorno += matriz[j][i];
                }    
            }
            cols[i] = 1;
        }
    }
    return retorno;
}

std::string Teclado::borrar(std::string retorno)
{
    if (!retorno.empty()) {
        retorno.erase(retorno.size() - 1); // Borra el último carácter
    }
    return retorno;
}


char Teclado::leerKey()
{
    char retorno;
    bool salir = false;
    while (!salir) {
        for (int i = 0; i < 3; i++){
            cols[i] = 0;
            for (int j  = 0; j < 4; j++){
                if(rows[j] == 0){
                    retorno = matriz[j][i];
                    salir = true;
                }    
            }
            cols[i] = 1;
        }
    }
    return retorno;
}