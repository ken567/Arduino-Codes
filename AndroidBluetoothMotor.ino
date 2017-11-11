//MotorDriver Pins
int pin1 = 8;
int pin2 = 9;
int pin3 = 10;
int pin4 = 11;
void setup() {
  Serial.begin(9600);

  pinMode(pin1,OUTPUT);
  pinMode(pin2,OUTPUT);
  pinMode(pin3,OUTPUT);
  pinMode(pin4,OUTPUT);
}

void loop() {
  char data;
  if(Serial.available()>0){
    data = Serial.read();
    
    Serial.println(data);
    if(data == 'w'){ 
      Serial.println(data);   
      digitalWrite(pin1, HIGH);
      digitalWrite(pin2, HIGH);
      digitalWrite(pin3, HIGH);
      digitalWrite(pin4, HIGH);
    }
    else if( data == 'q'){
      Serial.println(data);
     digitalWrite(pin1, HIGH);
      digitalWrite(pin2, HIGH);
      digitalWrite(pin3, HIGH);
      digitalWrite(pin4, LOW);
    }
    else if(data == 'e'){
      Serial.println(data);
      digitalWrite(pin1, LOW);
      digitalWrite(pin2, HIGH);
      digitalWrite(pin3, HIGH);
      digitalWrite(pin4, HIGH);  
    }
    else if(data == 's'){
      Serial.println(data);
      digitalWrite(pin1, LOW);
      digitalWrite(pin2, HIGH);
      digitalWrite(pin3, HIGH);
      digitalWrite(pin4, LOW);
    }
    else if (data == '0'){
      digitalWrite(9, LOW);
      digitalWrite(10, LOW);
    }
  }
}
