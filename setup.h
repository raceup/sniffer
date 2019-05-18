#ifndef SETUP_H
#define SETUP_H

#include "data.h"
#include "interrupts.h"


void setupSerial() {
    while (!Serial) {
        delay(100);
    }

    Serial.begin(SERIAL_COMMUNICATION_FREQUENCY);
}


void createLogHeader() {
    header = "time,";
    for (int i = 0; i < MAX_CAN_ID - 1; i++) {
      header += "0x";
      header += String(i, 15);
      header += ",";  // .csv format
    }
    header += String(MAX_CAN_ID - 1);
}


bool setupSD() {
    createLogHeader();

    // see if the card is present and can be initialized
    if (!SD.begin(chipSelect)) {
        return false;
    }

    while (nr != 0) {
        sprintf(fileName, "log_%03d.csv", nr);
        if (SD.exists(fileName) == false) break;
        Serial.print(fileName);
        Serial.println(" exists!");
        nr++;
    }

    Serial.print(fileName);
    Serial.println( " created.");

    dataFile = SD.open(fileName, FILE_WRITE);
    dataFile.print("v CAN LOGGER@1.3\n");
    dataFile.print(header);
    dataFile.print("\r\n");
    return true;
}

bool setupTasks() {
    runner.init();

    runner.addTask(tWrite2SD);
    runner.addTask(tSave2SD);

    tSave2SD.enable();
    tWrite2SD.enable();
    return true;
}


bool setupCAN() {
    Can0.begin(CAN_COMMUNICATION_FREQUENCY);
    // Can0.setBigEndian(true);   // operate in big endian

    Can0.setNumTXBoxes(1);   // use 1 mailbox (out of 8 on the Arduino Due) for transmission

    // set up the remaining 7 CAN mailboxes to receive messages from the slaves
    int MB_0 = Can0.setRXFilter(0x0, 0x0, false);  // fault messages (ID 0x00)
    Can0.setCallback(MB_0, callbackFrame);

    return true;
}

bool setupMatrix()
    {
        typedef struct
        {
            uint8_t data[8]; // 8 bytes
        } SNIFFED_FRAME;

        const uint8_t idsSize = 40; // # of CAN IDs to save
        typedef struct
        {
            int timeMs;
            SNIFFED_FRAME frames[idsSize]; // frames at given time
        } TIMED_TELEMETRY;

        const uint8_t bufferSize = 100; // 1 each 50 ms -> to save 500 ms (½ second) we need 100 rows
        int currentRow = 0;
        TIMED_TELEMETRY telemetryBuffer[bufferSize];

        for (int i = 0; i < bufferSize; i++)
        {
            telemetryBuffer[i].timeMs = 0;
            memset(telemetryBuffer[i].frames, 0, 320); //320 = 8*40
        }
        return true;
    }

#endif // SETUP_H
