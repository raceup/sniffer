#ifndef CAN_H
#define CAN_H

#include "data.h"

void printFrame(CAN_FRAME &frame) {
    uint32_t canID = frame.id;

    Serial.print("New CAN frame. ID = ");
    Serial.print(canID);
    Serial.print("DATA = ");
    for (int i = 0; i < CAN_MSG_SIZE; i++) {
      Serial.print(frame.data.bytes[i]);
      Serial.print(" ");
    }
    Serial.println("\r\n");
}

void saveFrame(CAN_FRAME &frame) {
    uint32_t canID = frame.id;

    for (int i = 0; i < CAN_MSG_SIZE; i++) {
      if (canID < MAX_CAN_ID) {
        CAN_DATA[canID][i] = frame.data.bytes[i];  // todo use memcpy(newArray, myArray2, sizeof(myArray2));
      } else {
        Serial.print("ERROR! CANNOT LOG FRAME WITH ID = ");
        Serial.print(canID);
        Serial.print("! MAX ID IS ");
        Serial.println(MAX_CAN_ID);
      }
    }
}

#endif // CAN_H
