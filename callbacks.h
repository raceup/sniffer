#ifndef CALLBACKS_H
#define CALLBACKS_H

#include "utils.h"

void write2SDCanId(int id) {
    for (int i = 0; i < CAN_MSG_SIZE - 1; i++) {
      dataFile.print(CAN_DATA[id][i]);
      dataFile.print(" ");  // space in between
    }
    dataFile.print(CAN_DATA[id][CAN_MSG_SIZE - 1]);
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

//select right where put data


#endif // CALLBACKS_H























