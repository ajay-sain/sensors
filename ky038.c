/**
 * @file lm393_sound.c
 * @author ajay sain (ajaysain00786@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-11-20
 * 
 * @copyright Copyright (c) 2021
 * 
 * Following is for KY-038 sound sensor based on LM393
 * DIGITAL signal only
 * 
 */

#include<stdio.h>
#include<wiringPi.h>

#define DIGITAL_READ_PIN 0                            // GPIO PIN 17
#define ANALOG_READ_PIN 2                             // GPIO PIN 27

int main(int argc, char const *argv[]){
    int last_state = 0, delay_count = 0 ;
    
    if (wiringPiSetup () == -1)
        return 1 ;

    pinMode(DIGITAL_READ_PIN,INPUT);                  // setting pin mode to read state
    pinModeAlt(ANALOG_READ_PIN,INPUT);                
    // setting pin mode to read state

    while(TRUE){
        if(HIGH == digitalRead(DIGITAL_READ_PIN)){
            delay_count = analogRead(ANALOG_READ_PIN);
            if(last_state == 0){
                printf("off\n");
                last_state = 1;
            }else{
                printf("on\n");
                last_state = 0;
            }
            printf("%d\n", delay_count);
            delay(500);
        }
    }
    return 0;
}
