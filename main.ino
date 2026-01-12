#include "movement.h"

void setup() {
  inisialisasi_motor();
  ps3_init();
}

void loop() {
  motormov();
  delay(50);
}
