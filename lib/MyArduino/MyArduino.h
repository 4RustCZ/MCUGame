#ifndef MYARDUINO_H
#define MYARDUINO_H

typedef enum {
    INPUT = 0,
    OUTPUT = 1
} PinType;

typedef enum {
    A = 0,
    B = 1,
    C = 2,
    D = 3,
    E = 4
}Ports;

typedef enum {
    OFF = 0,
    ON = 1
} PinState;

void pinMode(int pin, Ports port, PinType mode);
void digitalWrite(int pin, Ports port, PinState state);
int digitalRead(int pin, Ports port);
unsigned long millis(void);

#endif