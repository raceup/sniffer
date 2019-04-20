#ifndef CALLBACKS_H
#define CALLBACKS_H

#include "utils.h"

void write2SDCanId(int id) {
    for (int i = 0; i < CAN_MSG_SIZE; i++) {
      dataFile.print(CAN_DATA[id][i]);
      dataFile.print(" ");
    }
}

void write2SDCallback()
{
    int arduinoTime = micros() / 1000;  // time
    dataFile.print(arduinoTime);
    dataFile.print(",");

    for (int i = 0; i < MAX_CAN_ID - 1; i++) {
      write2SDCanId(i);
      dataFile.print(",");  // .csv log format
    }
    write2SDCanId(MAX_CAN_ID - 1);

    dataFile.print("\r\n");
}

void save2SDCallback()
{
    dataFile.close();
    dataFile = SD.open(fileName, FILE_WRITE);
}

#endif // CALLBACKS_H
