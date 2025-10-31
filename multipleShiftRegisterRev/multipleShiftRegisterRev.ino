//define arduino pin
int latchPin = 8;
int dataPin = 9;
int clockPin = 7;

//define variables to hold shift registers data
//values are nonzero to help debug
byte switchVar1 = 72;  //01001000
byte switchVar2 = 159; //10011111


void setup() {
  //start serial
  Serial.begin(9600);
  //define pin modes
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, INPUT);
}

void loop() {
  //Pulse the latch pin:
  //set it to 1 to collect parallel data, wait, set to 0 to transmit data serially
  digitalWrite(latchPin,1);
  delayMicroseconds(20);
  digitalWrite(latchPin,0);

  //while the shift register is in serial mode
  //collect each shift register into a byte
  //the register attached to the chip comes in first
  switchVar1 = shiftIn(dataPin, clockPin);
  switchVar2 = shiftIn(dataPin, clockPin);

  //print
  printBin(switchVar1);
  Serial.println("");
}

////// ----------------------------------------shiftIn function
///// just needs the location of the data pin and the clock pin
///// it returns a byte with each bit in the byte corresponding
///// to a pin on the shift register. leftBit 7 = Pin 7 / Bit 0= Pin 0

byte shiftIn(int myDataPin, int myClockPin){
  int i;
  int temp = 0;
  int pinState;
  byte myDataIn = 0;
  
  pinMode(myClockPin, OUTPUT);
  pinMode(myDataPin, INPUT);

  //we will be holding the clock pin high 8 times (0,..,7) at the
  //end of each time through the for loop
  
  //at the beginning of each loop when we set the clock low, it will
  //be doing the necessary low to high drop to cause the shift
  //register's DataPin to change state based on the value
  //of the next bit in its serial information flow.
  //The register transmits the information about the pins from pin 7 to pin 0
  //so that is why our function counts down
  for (i=7; i>=0; i--){
    
    digitalWrite(myClockPin, 0);
    delayMicroseconds(2);
    temp = digitalRead(myDataPin);
    
    if (temp){
      
      pinState = 1;
      //set the bit to 0 no matter what
      myDataIn = myDataIn | (1 << i);
    }
    else{
      
      //turn it off -- only necessary for debugging
     //print statement since myDataIn starts as 0
      pinState = 0;
    }
    
    //Debugging print statements
    //Serial.print(pinState);
    //Serial.print("     ");
    //Serial.println (dataIn, BIN);

    digitalWrite(myClockPin, 1);
  }

  //debugging print statements whitespace
  //Serial.println();
  //Serial.println(myDataIn, BIN);

  return myDataIn;
}

//prints bin values with leading 0
void printBin(byte aByte) {
  for (int8_t aBit = 7; aBit >= 0; aBit--)
    Serial.write(bitRead(aByte, aBit) ? '1' : '0');
}
