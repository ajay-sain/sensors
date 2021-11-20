#include <stdio.h>
#include <wiringPi.h>

#define DATA_PIN 0 // GPIO PIN 17

int temp, temp_decimal, checksum, humidity, humidity_decimal;

void request();
void response();
void defaultSetup();
int readByte();

int main(){
    printf("Raspberry Pi wiringPi DHT11 Temperature program\n");
    wiringPiSetup();
    if (wiringPiSetup() == -1)
        return 1;

    while (TRUE){
        request();
        response();
        temp = temp_decimal = checksum = humidity = humidity_decimal = 0;
        humidity = readByte();
        humidity_decimal = readByte();
        temp = readByte();
        temp_decimal = readByte();
        checksum = readByte();
        if (temp + temp_decimal + humidity + humidity_decimal == checksum)
            printf("working --> Humidity: %d.%d & Temperature: %d.%d\n", humidity, humidity_decimal, temp, temp_decimal);
        else
            printf("Not good\n");
        delay(2000);
    }
}

void request(){
    pinMode(DATA_PIN, OUTPUT);
    digitalWrite(DATA_PIN, HIGH);
    delay(18);
    digitalWrite(DATA_PIN, LOW);
    delay(18); //start signal active low
    digitalWrite(DATA_PIN, HIGH);
}

void response(){
    pinMode(DATA_PIN, INPUT);
    while (digitalRead(DATA_PIN) == 1);
    while (digitalRead(DATA_PIN) == 0);
    while (digitalRead(DATA_PIN) == 1);
}

void defaultSetup(){
    temp = temp_decimal = checksum = humidity = humidity_decimal = 0;
}

int readByte(){
    int data = 0, i, count = 0;
    for (i = 0; i < 8; i++){
        count = 0;
        while (digitalRead(DATA_PIN) == 0)
            delayMicroseconds(10);
        while (digitalRead(DATA_PIN) == 1){
            delayMicroseconds(1);
            count++;
        }
        data <<= 1;
        if (count > 50  )
            data |= 1;
    }
    return data;
}