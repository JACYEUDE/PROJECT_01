

import processing.serial.*;
String val;
PrintWriter output;
void setup() {
  String portName = Serial.list()[0]; //change the 0 to a 1 or 2 etc. to match your port
  myPort = new Serial(this, portName, 9600);
      output = createWriter( "data.txt" );
}
void draw() {
  
  
    if ( myPort.available() > 0) 
  {  // If data is available,
  val = myPort.readStringUntil('\n');         // read it and store it in val
  } 
println(val); //print it out in the console
}
