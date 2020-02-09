
// to the pins used:
byte InPot1;  // Analog input pin that the potentiometer is attached to
byte InPot2; // Analog output pin that the LED is attached to

int sensorValue1 = 0;        // value read from the pot
int sensorValue2 = 0;        // value output to the PWM (analog out)


int OutputValue1 = 0;        // value read from the pot
int OutputValue2 = 0;        // value output to the PWM (analog out)
int OutputValue3 = 0;        // value read from the pot
int OutputValue4 = 0;


void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
}

void loop() {

  if (Serial.available()==2){
    InPot1 = Serial.read();
    InPot2 = Serial.read();
  }
  // read the analog in value:

  // map it to the range of the analog out:
  OutputValue1 = map(InPot1, 128, 255, 0, 255);
  OutputValue2 = map(InPot2, 128, 255, 0, 255);

  // change the analog out value:
 // analogWrite(analogOutPin, outputValue);

  // print the results to the serial monitor:
  //Serial.print("sensor = ");
 // Serial.print(sensorValue);
 // Serial.print("\t output = ");
  Serial.print("#");
  Serial.print(",");
  Serial.print(OutputValue1);
  Serial.print(",");
  Serial.print(OutputValue2);
  Serial.print(",");
  Serial.print(OutputValue3);
  Serial.print(",");
  Serial.println(OutputValue4);
  

  // wait 2 milliseconds before the next loop
  // for the analog-to-digital converter to settle
  // after the last reading:
  delay(500);
}
