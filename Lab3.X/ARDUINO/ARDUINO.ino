// to the pins used:
float InPot1;  // Analog input pin that the potentiometer is attached toucha
float InPot2; // Analog output pin that the LED is attached to

float Value1 = 0;        // value read from the pot
float Value2 = 0;        // value output to the PWM (analog out)

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

  Value1 = OutputValue1/51.0;
  Value2 = OutputValue2/51.0;

  Serial.println("Pot 1");
  Serial.println(Value1,2);
  //Serial.print("    ");
  Serial.println("Pot 2");
 // Serial.print("      ");
  Serial.println(Value2,2);
//  Serial.flush();
//  Serial.print("+");
  

  // wait 2 milliseconds before the next loop
  // for the analog-to-digital converter to settle
  // after the last reading:
  delay(500);
}
