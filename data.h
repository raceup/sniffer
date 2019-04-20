#ifndef DATA_H
#define DATA_H

#include <due_can.h>

#define SERIAL_COMMUNICATION_FREQUENCY 115200
#define CAN_COMMUNICATION_FREQUENCY CAN_BPS_1000K
#define MAX_CAN_ID 800
#define CAN_MSG_SIZE 8

// callbacks
Scheduler runner;

void write2SDCallback();
void save2SDCallback();

Task tWrite2SD(20, TASK_FOREVER, &write2SDCallback);  // write to SD file each 20 ms
Task tSave2SD(5 * TASK_SECOND, TASK_FOREVER, &save2SDCallback);  // save to SD each 5 s

// CAN data logging
uint8_t CAN_DATA[MAX_CAN_ID][8];
CAN_FRAME incoming;  // read CAN data into this

// SD
const int chipSelect = 87; // SD pin
String header;  // header of log file
char fileName[16];  // SDcard uses 8.3 names so 16 bytes is enough NOte room for the '\0' char is needed!
unsigned int nr = 1;  // # of log file
File dataFile; // to save in SD

#endif // DATA_H
