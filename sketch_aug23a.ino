#include "HX711.h"

HX711 scale(5, 6);
int buzzer = 10;
float calibration_factor = -7050; // use either -2200, 2200, 41800
float units;
float ounces;

void setup() {
  Serial.begin(9600);
  Serial.println("HX711 calibration sketch");
  Serial.println("Remove all weight from scale");
  Serial.println("After readings begin, place known weight on scale");

  scale.set_scale();
  scale.tare();  //Reset the scale to 0
  
  long zero_factor = scale.read_average(); //Get a baseline reading
  Serial.print("Zero factor: "); //This can be used to remove the need to tare the scale. Useful in permanent scale projects.
  Serial.println(zero_factor);
}

void loop() {

  scale.set_scale(calibration_factor); //Adjust to this calibration factor

  Serial.print("Reading: ");
  units = scale.get_units(), 10;
  if (units < 0)
  {
    units = 0.00;
  }
  ounces = units * 0.035274;
  Serial.print(units);
  Serial.print(" kg"); 
  Serial.print(" calibration_factor: ");
  Serial.print(calibration_factor);
  Serial.println();
  delay(500);
  setCal();
}
void setCal(){ // For manually Calibrating
  
  if(Serial.available())
  {
    char temp = Serial.read();
   if(temp == '+' || temp == 'a')
      calibration_factor += 10;
    else if(temp == '-' || temp == 'z')
      calibration_factor -= 10;
    else if(temp == 's')
      calibration_factor += 100;  
    else if(temp == 'x')
      calibration_factor -= 100;  
    else if(temp == 'd')
      calibration_factor += 1000;  
    else if(temp == 'c')
      calibration_factor -= 1000;
    else if(temp == 'f')
      calibration_factor += 10000;  
    else if(temp == 'v')
      calibration_factor -= 10000;  
    else if(temp == 't')
      scale.tare();  //Reset the scale to zero
  }
}
void buzz(){
  
  unsigned char i, j ;
  while (1)
  {
    for (i = 0; i <80; i++) 
    {
      digitalWrite (buzzer, HIGH) ;
      delay (100);
      digitalWrite (buzzer, LOW);
      delay (100);
    }
    for (i = 0; i <100; i++) 
    {
      digitalWrite (buzzer, HIGH);
      delay (100);
      digitalWrite (buzzer, LOW);
      delay (100);
    }
  }

}

