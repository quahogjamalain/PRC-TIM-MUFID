#include <Ps3Controller.h>
#pragma once

// DEFINISI MAC Adreess Master, skalar kinematik, dan deadzone
// Lambda = skalar kecepatan (sensitivitas pwm) theta = skalar kecepatan putar (angular velocity)
#define MACADDR   "DD:AA:FF:FA:AA:AA"
#define lambda    1
#define theta     2
#define deadzone  15

void inisialisasi_motor(void);  // Init Motor
void motormov(void);            // Tulis PWM ke Motor
void kineval(void);             // Hitung kinematik buat M1 M2 M3 M4
void ps3_init(void);            // Init ps3
void ps3_fetch(void);           // Kalibrasi dead zone ps3

