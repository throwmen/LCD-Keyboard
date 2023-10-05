/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */
#include "TextLCD.h"
#include "mbed.h"
#include <iostream>
#include "Keypad/teclado.h"

UnbufferedSerial serial(USBTX, USBRX, 9600);

TextLCD lcd(D2,D3,D4,D5,D6,D7,TextLCD::LCD16x2);
Teclado teclado(D8,D9,D10,D11,D12,D13,D14);

#define BLINKING_RATE     200ms

int aux(){
    lcd.cls();
    string retorno = "";
    bool salir = false;
    char key;
    while(!salir){
        key = teclado.leerKey();
        if (key == '#')
            salir = true;
        else if (key == '*')
            retorno = teclado.borrar(retorno);
        else if (retorno.length() < 32){
            retorno += key;
            lcd.printf("%c",key);
        }
    }
    lcd.cls();
    return stoi(retorno);
}

int main()
{   
    lcd.printf("Ingrese el caso:");
    char caso = teclado.leerKey();
    lcd.cls();
    lcd.putc(caso);
    ThisThread::sleep_for(BLINKING_RATE);
    switch(caso)
    {
        case '1':{
            int x1,y1,x2,y2;
            while(true){
                lcd.cls();
                lcd.printf("Ingrese x1:");   
                x1 = aux();
                lcd.printf("Ingrese y1:");
                y1 = aux();
                lcd.printf("Ingrese x2:");
                x2 = aux();
                lcd.printf("Ingrese y2:");
                y2 = aux();
                if (x1 != x2){
                    float pendiente = (y2-y1)/(x2-x1);
                    lcd.printf("%f", pendiente);
                    float intercepto = -y1/pendiente + x1;
                    lcd.printf("%f", intercepto);
                }else {
                    lcd.printf("Error");
                }
            } 
        }
        break;
        case '2':{
            int N = 0;
            int temperaturas[N];
            float suma = 0;
            float desviacion = 0;
            while (true){
                lcd.cls();
                lcd.printf("Numero temp:");
                N = aux();
                for (int k = 0; k < N; k++){
                    lcd.printf("Ingrese temp:");
                    temperaturas[k] = aux();
                }
                for (int i = 0; i < N; i++){
                    suma = suma + temperaturas[i];
                }
                suma = suma/N;
                lcd.printf("%f", suma);
                for (int i = 0; i < N; i++){
                    desviacion = desviacion + pow(temperaturas[i]-suma, 2);
                }
                desviacion = sqrt(desviacion/N);
                lcd.printf("%f", desviacion);
            }
        }
        break;
        case '3':{
            int r, g ,b;
            PwmOut ledR(LED1);
            PwmOut ledG(LED2);
            PwmOut ledB(LED3);

            ledR.period(0.01);
            ledG.period(0.01);
            ledB.period(0.01);

            while(true){
                lcd.printf("Led rojo:");
                r = aux();
                lcd.printf("Led verde:");
                g = aux();
                lcd.printf("Led azul:");
                b = aux();

                ledR.write(1.0f - (float)r / 255.0f);
                ledG.write(1.0f - (float)g / 255.0f);
                ledB.write(1.0f - (float)b / 255.0f);
                }
        }
        break;
    }
}
