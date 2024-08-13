/*
  SD card write example

  This example shows how to read and write data to and from an SD card file
  The circuit:
   SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4 (for MKRZero SD: SDCARD_SS_PIN)

*/

#include <SPI.h>
#include <SD.h>

File myFile;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ;  // wait for serial port to connect. Needed for native USB port only
  }

  // Init of SD card - If init fails, halt program
  Serial.print("Initializing SD card...");
  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    while (1)
      ;
  }
  Serial.println("initialization done.");
}

void loop() {

  int variable = 99;  // Luftballons
  
  // Open the file, create handle. Only one file can be open at a time.
  myFile = SD.open("test.txt", FILE_WRITE);

  // If the file opened, write to it:
  if (myFile) {
    myFile.println("testing 1, 2, 3.");  // Example for writing text to a file
    myFile.println(variable);            // Example for writing the contents of a variable to a file

    // Below shows an example that combines text and variables in one line of the SD card
    variable = 1;
    myFile.print("testing ");     
    myFile.print(variable);
    myFile.print(", ");
    myFile.print(variable + 1);
    myFile.print(", ");
    myFile.println(variable + 2);
    
    // You MUST close the file before pulling the SD card to read in a computer
    myFile.close();
    Serial.println("File opened, written, and closed succesfully!");    // Indicate success of open, write, and close 
  } else {
    Serial.println("Error opening test.txt");                           // If the file didn't open, print an error
  }
  delay(10000); // run every 10 seconds
}
