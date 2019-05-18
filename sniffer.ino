#include <SPI.h>
#include <SD.h>
#include <TaskScheduler.h>

#include "setup.h"
#include "callbacks.h"
#include "data.h"
#include "utils.h"

bool goodSerial = false;
bool goodSetup = false;

void setup() {
  setupSerial();

  bool ok = setupCAN();
  if (!ok) {
    logToSerial("ERROR! CANNOT SETUP CAN!");
  }

  ok &= setupTasks();
  if (!ok) {
    logToSerial("ERROR! CANNOT SETUP TASKS!");
  }

  ok &= setupSD();
  if (!ok) {
    logToSerial("ERROR! CANNOT SETUP SD!");
  }
  
  //setup matrix 
  ok &= setupMatrix();
  if (!ok) {
    logToSerial("ERROR! CANNOT SETUP MATRIX!");
  }

  goodSetup = ok;


}

void loop() {
  if (goodSetup) {
    runner.execute();  // start SD writer and saver

    if (Can0.available() > 0) {
      Can0.read(incoming);  // read CAN to &incoming
      saveFrame(incoming);
    }
  }
}
