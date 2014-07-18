/*
  Parawing SD card datalogger
 	
 The circuit:
 * digital switches on D2, D5,D6, and D7
 * digital motor sensor on D8 and D9
 * SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** SLK/CLK - pin 13
 ** CS - pin 10	 
 */

#include <SD.h>
const int chipSelect = 10;

void setup()
{
  Serial.begin(9600);
  for(int i=2;i<=7;i++){
    pinMode(i,INPUT);
  }
  pinMode(8,INPUT_PULLUP);
  pinMode(9,INPUT_PULLUP);
  pinMode(10, OUTPUT);
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    return;
  }
}
int counter=0;
void loop()
{
//#################################################
//               Assemble dataString             //
//#################################################
  String dataString = "";
  dataString+=counter;
  dataString+="\t";
  dataString+=digitalRead(2);
  dataString+="\t";
  dataString+=digitalRead(5);
  dataString+="\t";\
  dataString+=digitalRead(6);
  dataString+="\t";
  dataString+=digitalRead(7);
  dataString+="\t\t";
  dataString+=!digitalRead(8);//connect to gnd to activate
  dataString+="\t";
  dataString+=!digitalRead(9);//connect to gnd to activate
  dataString+=";";

//#################################################
// WRITE dataString to SD card if it's available //
//#################################################
  File dataFile = SD.open("DATAFILE.TXT", FILE_WRITE);  
  if (dataFile) {
    if(counter==0){
        dataString="Count\tCutSig\tRturn\tNotTun\tLturn\t\tSigR\tSigL";

    }
    dataFile.println(dataString);
    dataFile.close();
    Serial.println(dataString);
  }  
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
  }
  counter++;
  delay(500);
}









