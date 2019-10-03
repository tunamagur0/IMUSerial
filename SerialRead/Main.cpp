#include <iostream>
#include "Serial.h"

struct vec3 {
  float x;
  float y;
  float z;
} acc, gyro;

int main(void) {
  const int serial_port = 3;
  const int baud_rate = 115200;
  Serial serial = Serial(serial_port);

  serial.Start(baud_rate);
  char buffer[1024];
  float pitch, roll, yaw, temp;
  while (true) {
    serial.Read(buffer);
    std::cout << sscanf(buffer, "g:%f,%f,%f a:%f,%f,%f p:%f r:%f y:%f t:%f",
                        &gyro.x, &gyro.y, &gyro.z, &acc.x, &acc.y, &acc.z,
                        &pitch, &roll, &yaw, &temp)
              << std::endl;
    std::cout << gyro.x << " " << gyro.y << " " << gyro.z << " " << acc.x << " "
              << acc.y << " " << acc.z << " " << pitch << " " << roll << " "
              << yaw << " " << temp << " " << std::endl;
  }
  serial.End();
  return 0;
}