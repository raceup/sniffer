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


int selectColumn(int ID)
{
    switch (ID)
    {
    case 0x13:
        return 1;
    case 0x14:
        return 2;
    case 0x15:
        return 3;
    case 0x16:
        return 4;
    case 0x17:
        return 5;
    case 0x21:
        return 6;
    case 0x22:
        return 7;
    case 0x23:
        return 8;
    case 0x184:
        return 9;
    case 0x185:
        return 10;
    case 0x188:
        return 11;
    case 0x189:
        return 12;
    case 0x283:
        return 13;
    case 0x284:
        return 14;
    case 0x287:
        return 15;
    case 0x288:
        return 16;
    case 0x285:
        return 17;
    case 0x286:
        return 18;
    case 0x289:
        return 19;
    case 0x28a:
        return 20;
    case 0x67:
        return 21;
    case 0x68:
        return 22;
    case 0x100:
        return 23;
    case 0x110:
        return 24;
    case 0x111:
        return 25;
    case 0x120:
        return 26;
    case 0x121:
        return 27;
    case 0x122:
        return 28;
    case 0x123:
        return 29;
    case 0x124:
        return 30;
    case 0x131:
        return 31;
    case 0x132:
        return 32;
    case 0x133:
        return 33;
    case 0x134:
        return 34;
    case 0x135:
        return 35;
    case 0x136:
        return 36;
    case 0x137:
        return 37;
    case 0x138:
        return 38;
    case 0x161:
        return 39;
    case 0x174:
        return 40;
    case 0x175:
        return 41;
    case 0x176:
        return 42;
    }
}
//write to the matrix
void writeToStruct(CAN_FRAME &frame)
{
  //check time
  if(telemetryBuffer.timeMs == 0)
  {
    telemetryBuffer.timeMs = millis();
  }
   //check overwrite
  //check overflow row
  if(telemetryBuffer[currentRow].frames[col] != 0)
    {
      if(currentRow <= idsSize){
        currentRow++;
      }
      else{
        currentRow = 0;
    }
  }

  int col = selectColumn(frame.id);
  memcpy(frame.data.bytes, &telemetryBuffer[currentRow].frames[col], 8);
}

#endif // CAN_H
