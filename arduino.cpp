
const int dataPin = 3; // to 74HC595 pin 14
const int latchPin = 2; // to 74HC595 pin 12
const int clockPin = 4; // to 74HC595 pin 11
 #define trigPin 13
 #define echoPin 12
 #define trigPin2 8
 #define echoPin2 9

const char common = 'a'; // common anode

int button = 7;
int i = 0;
int currentState = 0;
int previousState = 0;
int currentState2 = 0;
int previousState2 = 0;
 
byte bits;
bool decPt = true; // decimal point display flag
byte myfnNumToBits(int someNumber) {
 switch (someNumber) {
 case 0:
 return B11111100;
 break;
 case 1:
 return B01100000;
 break;
 case 2:
 return B11011010;
 break;
 case 3:
 return B11110010;
 break;
 case 4:
 return B01100110;
 break;
 case 5:
 return B10110110;
 break;
 case 6:
 return B10111110;
 break;
 case 7:
 return B11100000;
 break;
 case 8:
 return B11111110;
 break;
 case 9:
 return B11110110;
 break; 
 default:
 return B10010010; // Error condition, displays three vertical bars
 break; 
 }
}
void myfnUpdateDisplay(byte eightBits) {
 if (common == 'a') { 
 eightBits = eightBits ^ B11111111; // then flip all bits using XOR 
 }
 digitalWrite(latchPin, LOW); // prepare shift register for data
 shiftOut(dataPin, clockPin, LSBFIRST, eightBits); // send data
 digitalWrite(latchPin, HIGH); // update display
}

void setup() {
 // initialize I/O pins
 pinMode(dataPin, OUTPUT);
 pinMode(latchPin, OUTPUT);
 pinMode(clockPin, OUTPUT);
 pinMode(button, INPUT);
 pinMode(trigPin, OUTPUT);
 pinMode(echoPin, INPUT);
 pinMode(trigPin2, OUTPUT);
 pinMode(echoPin2, INPUT);
}

void loop() {
 decPt = !decPt; 
 long duration, distance;
 digitalWrite(trigPin, LOW); 
 delayMicroseconds(2); 
 digitalWrite(trigPin, HIGH);
 delayMicroseconds(10); 
 digitalWrite(trigPin, LOW);
 duration = pulseIn(echoPin, HIGH);
 distance = (duration/2) / 29.1;
 long duration2, distance2;
 digitalWrite(trigPin2, LOW); 
 delayMicroseconds(2); 
 digitalWrite(trigPin2, HIGH);
 delayMicroseconds(10); 
 digitalWrite(trigPin2, LOW);
 duration2 = pulseIn(echoPin2, HIGH);
 distance2 = (duration2/2) / 29.1;
 // object entering in the system
 if (distance <= 10){
 currentState = 1;
 }
 else {
 currentState = 0;
 }
 //delay(100);
 if(currentState != previousState){
 while(currentState == 1) {
 long duration2, distance2;
 digitalWrite(trigPin2, LOW); 
 delayMicroseconds(2); 
 digitalWrite(trigPin2, HIGH);
 delayMicroseconds(10); 
 digitalWrite(trigPin2, LOW);
 duration2 = pulseIn(echoPin2, HIGH);
 distance2 = (duration2/2) / 29.1;
 if (distance2 <= 10){
 currentState2 = 1;
 }
 else {
 currentState2 = 0;
 }
 //delay(100);
 if(currentState2 != previousState2){
 if(currentState2 == 1) {
 i = i+1;
 byte bits = myfnNumToBits(i);
 myfnUpdateDisplay(bits); // display numeric digit
 delay(1000); // pause for 1/2 second
 }
 else {
 byte bits = myfnNumToBits(i);
 myfnUpdateDisplay(bits); // display numeric digit
 }
 return;
 
   }
  }
 }
 // object exit from the system 
if (distance2 <= 10){
 currentState2 = 1;
 }
 else {
 currentState2 = 0;
 }
 delay(100);
 if(currentState2 != previousState2){
 while (currentState2 == 1) {
 long duration, distance;
 digitalWrite(trigPin, LOW); 
 delayMicroseconds(2); 
 digitalWrite(trigPin, HIGH);
 delayMicroseconds(10); 
 digitalWrite(trigPin, LOW);
 duration = pulseIn(echoPin, HIGH);
 distance = (duration/2) / 29.1;
 if (distance <= 10){
 currentState = 1;
 }
 else {
 currentState = 0;
 }
 delay(100);
 if(currentState != previousState){
 if(currentState == 1) {
 i = i-1; 
 byte bits = myfnNumToBits(i);
 myfnUpdateDisplay(bits); // display alphanumeric digit
 delay(1000); 
 }
 else {
 byte bits = myfnNumToBits(i);
 myfnUpdateDisplay(bits); // display alphanumeric digit
 }
 return;
   }
  }
 }
}
