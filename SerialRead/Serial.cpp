#include "Serial.h"
#include <string>
Serial::Serial(int port_num) : port_num_(port_num) {
  TCHAR port_name[10];
  _stprintf(port_name, _T("COM%d"), port_num);

  com_port_ = CreateFile((LPCTSTR)port_name, GENERIC_READ, 0, NULL,
                         OPEN_EXISTING, 0, NULL);
};
Serial::~Serial() { End(); };

void Serial::Start(unsigned long baud_rate) {
  DCB port_config;
  GetCommState(com_port_, &port_config);

  port_config.BaudRate = baud_rate;
  port_config.ByteSize = 8;
  port_config.Parity = NOPARITY;
  port_config.StopBits = ONESTOPBIT;
  port_config.fOutxCtsFlow = FALSE;
  SetCommState(com_port_, &port_config);
};

void Serial::End() { CloseHandle(com_port_); };

DWORD Serial::Read(char* buffer) {
  DWORD number_of_read;

  int i = 0;
  char tmp;
  do {
    ReadFile(com_port_, &tmp, sizeof(tmp), &number_of_read, NULL);
    buffer[i] = tmp;
    i++;
  } while (number_of_read > 0 && tmp != '\n');

  return i;
};
