/**
 * @file jhd162a.c
 * @author Ajay Sain (ajaysain00786@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-11-22
 * 
 * @copyright Copyright (c) 2021
 * 
 * here the read write pin is default ground;
 * 
 */

#include<stdio.h>
#include<wiringPi.h>

#define REGISTER_SELECT_PIN 0                                   
#define ENABLE_SIGNAL_PIN 2       

unsigned int data_bus[8] = {25, 24, 23, 22, 29, 28, 27, 26};   // data pins from DB0 - DB7

void _init_screan();
void _clear_screen();
void _instruction(unsigned char data, int mode);
void _print(char *str, ...);
void _go_to(int x, int y);
void _read_from_screen();

int main(int argc, char const *argv[])
{
    /* code */
    if (wiringPiSetup () == -1)
        return 1 ;
    _init_screan();
    _clear_screen();
    _print("Kpuri devi");
    _instruction(0xc0, 0);
    _print("JINDABAD.");
    return 0;
}

void _init_screan(){
    pinMode(ENABLE_SIGNAL_PIN, OUTPUT);
    pinMode(REGISTER_SELECT_PIN, OUTPUT);
    for(int i = 0 ; i < 8 ; i++){
        pinMode(data_bus[i], OUTPUT);
    }
    _instruction(0x38, 0);
    _instruction(0xe, 0);
    _instruction(0x6, 0);

}

void _clear_screen(){
    _instruction(0x1, 0);
}

void _instruction(unsigned char data, int rs_mode){
    rs_mode == 1 ? digitalWrite(REGISTER_SELECT_PIN, HIGH) : digitalWrite(REGISTER_SELECT_PIN, LOW);
    digitalWrite(ENABLE_SIGNAL_PIN, LOW);
    for( int i = 7; i >= 0; i-- ) {
        ( data >> i ) & 1 ? digitalWrite(data_bus[i], HIGH) : digitalWrite(data_bus[i], LOW) ;
    }
    digitalWrite(ENABLE_SIGNAL_PIN, HIGH);
    delayMicroseconds(40);
    digitalWrite(ENABLE_SIGNAL_PIN, LOW);
}

void _print(char *str, ...){
    while(*str != '\0'){
        _instruction(*str, 1);
        *str++;
    }
}