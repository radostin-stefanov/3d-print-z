//simple A4988 connection
//jumper reset and sleep together
//connect  VDD to Arduino 3.3v or 5v
//connect  GND to Arduino GND (GND near VDD)
//connect  1A and 1B to stepper coil 1
//connect 2A and 2B to stepper coil 2
//connect VMOT to power source (9v battery + term)
//connect GRD to power source (9v battery - term)


int stp = 3;  //connect pin 3 to step
int dir = 4;  // connect pin 4 to dir
int enable = 2;     //  gen counter

void setup() 
{                
  pinMode(stp, OUTPUT);
  pinMode(dir, OUTPUT); 
  pinMode(enable, OUTPUT);
   
  digitalWrite(2, LOW);   
  digitalWrite(dir, HIGH);   

  Serial.begin(9600);
  Serial.println("Ready. Input number of steps.");
}


void loop() 
{
  String s = Serial.readString();
  if (s.length() == 0)
    return;
  int sign = 1;
  int idx = 0;
  if (s.charAt(0) == '-') {
    sign = -1;
    idx++;  
  }
  if (s.charAt(0) == '+') {
    idx++;
  }
  int num = 0;
  while (idx < s.length()) {
    char ch = s.charAt(idx++);
    if (ch < '0' || ch > '9') {
      Serial.println("Invalid number");
      return;
    }
    num *= 10;
    num += ch - '0';
  }
  
  Serial.print("Moving ");
  Serial.print(num);
  Serial.print(" step(s) ");
  if (sign == 1) {
    Serial.println("upwards.");
    digitalWrite(dir, HIGH);
  }
  else {
    Serial.println("downwards.");
    digitalWrite(dir, LOW);
  }

  digitalWrite(enable, LOW); // enable
  for (int i = 0; i < num; i++)
  {
    digitalWrite(stp, HIGH);   
    delay(1);               
    digitalWrite(stp, LOW);  
    delay(1);              
  }
  digitalWrite(enable, HIGH); // disable

}
