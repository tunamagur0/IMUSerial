#include <iostream>
#include "Serial.h"

int main(void) {
  Serial serial = Serial(3);

  serial.Start(115200);
  char buffer[1024];
  while (true) {
    serial.Read(buffer);
    std::cout << buffer << std::endl;
  }
  serial.End();
  return 0;
}