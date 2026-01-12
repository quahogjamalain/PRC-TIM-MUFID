#include "movement.h"

void setup() {
  Serial.begin(115200);
  inisialisasi_motor();
  ps3_init();
}

void loop() {
  motormov();
  delay(50);
}
