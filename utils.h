#ifndef UTILS_H
#define UTILS_H

void logToFile(double value) {
    dataFile.print(value);
    dataFile.print(",");  // csv syntax
}

void logToSerial(String message) {
  Serial.println(message);
}

#endif // UTILS_H
