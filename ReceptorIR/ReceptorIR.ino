 /*

 * IRremote: IRrecvDump - dump details of IR codes with IRrecv

 * An IR detector/demodulator must be connected to the input RECV_PIN.

 * Version 0.1 July, 2009

 * Copyright 2009 Ken Shirriff

 * http://arcfn.com

 * http://as3breeze.com/arduino-sending-samsung-ir-codes/

 */
#define RAW_BUFFER_LENGTH  730
#define MARK_EXCESS_MICROS    20    // Adapt it to your IR receiver module. 20 is recommended for the cheap VS1838 modules.

#include <IRremote.h>



int RECV_PIN = 2;

 

IRrecv irrecv(RECV_PIN);

 

//decode_results results; // descontinuado

 

void setup()

{

  Serial.begin(9600);

  irrecv.enableIRIn(); // Start the receiver

}

 

// Dumps out the decode_results structure.

// Call this after IRrecv::decode()

// void * to work around compiler issue

//void dump(void *v) {

//  decode_results *results = (decode_results *)v

void dump() {
Serial.println();
  int count =  IrReceiver.decodedIRData.rawDataPtr->rawlen;//results->rawlen; descontinuado

  if (IrReceiver.decodedIRData.protocol == UNKNOWN){//(results->decode_type == UNKNOWN) {

    Serial.print("Unknown encoding: ");

  } 

  else if (IrReceiver.decodedIRData.protocol == NEC) {

    Serial.print("Decoded NEC: ");

  } 

  else if (IrReceiver.decodedIRData.protocol == SONY) {

    Serial.print("Decoded SONY: ");

  } 

  else if (IrReceiver.decodedIRData.protocol == RC5) {

    Serial.print("Decoded RC5: ");

  } 

  else if (IrReceiver.decodedIRData.protocol == RC6) {

    Serial.print("Decoded RC6: ");

  }

  else if (IrReceiver.decodedIRData.protocol == PANASONIC) {

    Serial.print("Decoded PANASONIC: ");

  }

  else if (IrReceiver.decodedIRData.protocol == JVC) {

    Serial.print("Decoded JVC: ");

  }

  else if (IrReceiver.decodedIRData.protocol == SAMSUNG) {

    Serial.print("Decoded SAMSUNG: ");

  }

  int val1 = IrReceiver.decodedIRData.rawDataPtr->rawlen;// results->value;

  Serial.print(val1, HEX);

  Serial.print(" (");

  int valbits = IrReceiver.decodedIRData.numberOfBits;

  Serial.print(valbits, DEC);

  Serial.println(" bits)");

  Serial.print("Raw (");

  Serial.print(count, DEC);

  Serial.println("): ");

 

  for (int i = 0; i < count; i++) {

    // if ((i % 2) == 1) {

      int valen = IrReceiver.decodedIRData.rawDataPtr->rawbuf[i]*USECPERTICK;

      Serial.print(valen, DEC);
    
 

    // } 

    // else {

    //   int negvalen =-(int)IrReceiver.decodedIRData.rawDataPtr->rawbuf[i]*USECPERTICK;

    //   Serial.print(negvalen, DEC);

    // }

    Serial.print(", ");

  }

  //Serial.println("");
   //Serial.println(F("Raw result in internal ticks (50 us) - with leading gap"));
            //IrReceiver.printIRResultRawFormatted(&Serial, false); // Output the results in RAW format
            //Serial.println(F("Raw result in microseconds - with leading gap"));
            //IrReceiver.printIRResultRawFormatted(&Serial, true);  // Output the results in RAW format
           // Serial.println();       
}

 

void loop() {

  if (IrReceiver.decode()){//if (irrecv.decode(&results)) {

    int hexen = IrReceiver.decodedIRData.decodedRawData;

    Serial.println(hexen, HEX);

    dump();

    irrecv.resume(); // Receive the next value

  }

}