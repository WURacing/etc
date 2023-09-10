//Declare pin functions on Arduino
#define stp 2
#define dir 3
#define MS1 4
#define MS2 5
#define MS3 6
#define EN  7

//Declare variables for functions
char user_input;
int i;
int x;
int y;
int state;
int distance;
int pos = 0;


void setup() {
  pinMode(stp, OUTPUT);
  pinMode(dir, OUTPUT);
  pinMode(MS1, OUTPUT);
  pinMode(MS2, OUTPUT);
  pinMode(MS3, OUTPUT);
  pinMode(EN, OUTPUT);
  resetBEDPins(); //Set step, direction, microstep and enable pins to default states
  Serial.begin(9600); //Open Serial connection for debugging
  Serial.println("Begin motor control");
  Serial.println();
  //Print prompt instructions
  Serial.println("Enter target position:");
  Serial.print("Current position is:");
  Serial.println(pos);
  Serial.println();
}

//Main loop
void loop() {
  while(Serial.available()){
    user_input = Serial.parseInt();
    if (user_input != 0){
        int target = user_input; //Read user input and trigger appropriate function
          Serial.println(target);
        digitalWrite(EN, LOW); //Pull enable pin low to set FETs active and allow motor control
        if (target != pos){
        actuate(target);
      }
      //resetBEDPins();
    }
  }
}

//Reset Big Easy Driver pins to default states
void resetBEDPins()
{
  digitalWrite(stp, LOW);
  digitalWrite(dir, LOW);
  digitalWrite(MS1, LOW);
  digitalWrite(MS2, LOW);
  digitalWrite(MS3, LOW);
  digitalWrite(EN, HIGH);
}

//move the postion forward till position matches target
void actuate(int(target))
{
  if(pos < target){
    digitalWrite(dir, LOW); //pull direction pin low to move "forward"
    distance = abs(pos - target);
    for (x = 1; x <= distance; x++){
    digitalWrite(stp,HIGH); //Trigger one step forward
    delay(1);
    digitalWrite(stp,LOW); //Pull step pin low so it can be triggered again
    delay(1);
    pos++;
    }
  }
  else if(pos > target){
    digitalWrite(dir, HIGH); //pull direction pin high to move "backward"
    distance = abs(pos - target);
    for (x = 1; x <= distance; x++){
    digitalWrite(stp,HIGH); //Trigger one step forward
    delay(1);
    digitalWrite(stp,LOW); //Pull step pin low so it can be triggered again
    delay(1);
    pos = pos -1;
    }
  }
  Serial.println("Actuation Complete!");
  Serial.print("Positon is:");
  Serial.println(pos);
  Serial.print("Target is:");
  Serial.println(target);
  Serial.println();
}

//********************* Test code for running diffferent motions of stepper motor *******************************************************************

////Default microstep mode function
//void StepForwardDefault()
//{
//  Serial.println("Moving forward at default step mode.");
//  digitalWrite(dir, LOW); //Pull direction pin low to move "forward"
//  for(x= 1; x<1000; x++)  //Loop the forward stepping enough times for motion to be visible
//  {
//    digitalWrite(stp,HIGH); //Trigger one step forward
//    delay(100);
//    digitalWrite(stp,LOW); //Pull step pin low so it can be triggered again
//    delay(100);
//  }
//  Serial.println("Enter new option");
//  Serial.println();
//}
//
////Reverse default microstep mode function
//void ReverseStepDefault()
//{
//  Serial.println("Moving in reverse at default step mode.");
//  digitalWrite(dir, HIGH); //Pull direction pin high to move in "reverse"
//  for(x= 1; x<1000; x++)  //Loop the stepping enough times for motion to be visible
//  {
//    digitalWrite(stp,HIGH); //Trigger one step
//    delay(1);
//    digitalWrite(stp,LOW); //Pull step pin low so it can be triggered again
//    delay(1);
//  }
//  Serial.println("Enter new option");
//  Serial.println();
//}
//
//// 1/16th microstep foward mode function
//void SmallStepMode()
//{
//  Serial.println("Stepping at 1/16th microstep mode.");
//  digitalWrite(dir, LOW); //Pull direction pin low to move "forward"
//  digitalWrite(MS1, HIGH); //Pull MS1,MS2, and MS3 high to set logic to 1/16th microstep resolution
//  digitalWrite(MS2, HIGH);
//  digitalWrite(MS3, HIGH);
//  for(x= 1; x<1000; x++)  //Loop the forward stepping enough times for motion to be visible
//  {
//    digitalWrite(stp,HIGH); //Trigger one step forward
//    delay(1);
//    digitalWrite(stp,LOW); //Pull step pin low so it can be triggered again
//    delay(1);
//  }
//  Serial.println("Enter new option");
//  Serial.println();
//}
//
////Forward/reverse stepping function
//void ForwardBackwardStep()
//{
//  Serial.println("Alternate between stepping forward and reverse.");
//  for(x= 1; x<5; x++)  //Loop the forward stepping enough times for motion to be visible
//  {
//    //Read direction pin state and change it
//    state=digitalRead(dir);
//    if(state == HIGH)
//    {
//      digitalWrite(dir, LOW);
//    }
//    else if(state ==LOW)
//    {
//      digitalWrite(dir,HIGH);
//    }
//    
//    for(y=1; y<1000; y++)
//    {
//      digitalWrite(stp,HIGH); //Trigger one step
//      delay(1);
//      digitalWrite(stp,LOW); //Pull step pin low so it can be triggered again
//      delay(1);
//    }
//  }
//  Serial.println("Enter new option");
//  Serial.println();
//}
////fastest 90 degree turn
//void FastTurn()
//{
//  Serial.println("Closing");
//  //for(i = 1; i <101; i++)
//  {
//  digitalWrite(dir, LOW); //Pull direction pin low to move "forward"
//  for(x= 1; x<101; x++)  //Loop the forward stepping 90 degrees
//  {
//    digitalWrite(stp,HIGH); //Trigger one step forward
//    delayMicroseconds(2000);
//    digitalWrite(stp,LOW); //Pull step pin low so it can be triggered again
//    delayMicroseconds(2000);
//  }
////  digitalWrite(dir, HIGH); //Pull direction pin low to move "Backward"
////  for(x= 1; x<51; x++)  //Loop the forward stepping 90 degrees
////  {
////    digitalWrite(stp,HIGH); //Trigger one step forward
////    delayMicroseconds(2000);
////    digitalWrite(stp,LOW); //Pull step pin low so it can be triggered again
////    delayMicroseconds(2000);
////  }
//  }
//  Serial.println("Enter new option");
//  Serial.println();
//}
//
//void Open()
//{
//  Serial.println("Opening");
//  for(x= 1; x<101; x++)  //Loop the forward stepping 90 degrees
//  {
//    digitalWrite(stp,HIGH); //Trigger one step forward
//    delayMicroseconds(2000);
//    digitalWrite(stp,LOW); //Pull step pin low so it can be triggered again
//    delayMicroseconds(2000);
//  }
//  Serial.println("Enter new option");
//  Serial.println();
//}
