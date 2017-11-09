

int pin1 = 8;
int pin2 = 9;
int pin3 = 10;
int pin4 = 11;

int leftSwitch = 3;
int rightSwitch = 4;

void setup() {
  pinMode(pin1,OUTPUT);
  pinMode(pin2,OUTPUT);
  pinMode(pin3,OUTPUT);
  pinMode(pin4,OUTPUT);
  
  pinMode(leftSwitch,INPUT);
  pinMode(rightSwitch,INPUT);

}

void loop() {
  int ls = digitalRead(leftSwitch); //left switch
  int rs = digitalRead(rightSwitch); //right switch

  if(ls == HIGH && rs == LOW){ //right
    digitalWrite(8, HIGH);
    digitalWrite(9, HIGH);
    digitalWrite(10, HIGH);
    digitalWrite(11, LOW);
    
  }
  else if(ls == LOW && rs == HIGH){ //left
    digitalWrite(8, LOW);
    digitalWrite(9, HIGH);
    digitalWrite(10, HIGH);
    digitalWrite(11, HIGH);
  }
  else if(ls == HIGH && rs == HIGH){ //Reverse
    digitalWrite(8, HIGH);
    digitalWrite(9, HIGH);
    digitalWrite(10, HIGH);
    digitalWrite(11, HIGH);
  }
  else{ // Foward
    digitalWrite(8, LOW);
    digitalWrite(9, HIGH);
    digitalWrite(10, HIGH);
    digitalWrite(11, LOW);

  }
}
