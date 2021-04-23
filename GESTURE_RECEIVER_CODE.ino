#include<SPI.h>
#include<nRF24L01.h>
#include<RF24.h>

const byte address[6] = "00001"; //for creating communication between two nrf modules we need to create a pipe with an address. 

int ENA = 3;//for turning the motors ON, OFF and control its speed
int ENB = 9;//for turning the motors ON, OFF and control its speed
int MotorA1 = 4;//for controlling motor A1
int MotorA2 = 5;//for controlling motor A2
int MotorB1 = 6;//for controlling motor B1
int MotorB2 = 7;//for controlling motor B2

RF24 radio(8, 10);

struct data 
{
  int xAxis;
  int yAxis;
};

data receive_data;


void setup()//setup code which will run once
{
Serial.begin(9600);// intiate serial communication 9600 = baud rate 
radio.begin();
radio.openReadingPipe(0,address);// for opening the pipe. 
radio.setPALevel(RF24_PA_MIN);// defining minimum amount of transmitting power which will help in draining minimum power consumption we can also set it to maximum as to achieve maximum range.
radio.setDataRate(RF24_250KBPS);// defining the data rate of transmission 250 KB
radio.startListening();
pinMode(ENA, OUTPUT);//for turning the motors ON, OFF and control its speed
pinMode(ENB, OUTPUT);//for turning the motors ON, OFF and control its speed
pinMode(MotorA1, OUTPUT);//for controlling motor A1
pinMode(MotorA2, OUTPUT);//for controlling motor A2
pinMode(MotorB1, OUTPUT);//for controlling motor B1
pinMode(MotorB2, OUTPUT);//for controlling motor B2
}

void loop()// used to make code repeat  
{
 while(radio.available())//turning motors HIGH and LOW for the motion of robot
 {
  radio.read(&receive_data, sizeof(data));
   if(receive_data.yAxis > 400)
    {
      digitalWrite(MotorA1, LOW);
      digitalWrite(MotorA2, HIGH);
      digitalWrite(MotorB1, HIGH);
      digitalWrite(MotorB2, LOW);
      analogWrite(ENA, 150);
      analogWrite(ENB, 150);  
    }
   else if(receive_data.yAxis < 320) 
    {
      digitalWrite(MotorA1, HIGH);
      digitalWrite(MotorA2, LOW);
      digitalWrite(MotorB1, LOW);
      digitalWrite(MotorB2, HIGH);
      analogWrite(ENA, 150);
      analogWrite(ENB, 150);
    } 
   else if(receive_data.xAxis < 320) 
    {
      digitalWrite(MotorA1, HIGH);
      digitalWrite(MotorA2, LOW);
      digitalWrite(MotorB1, HIGH);
      digitalWrite(MotorB2, LOW);
      analogWrite(ENA, 150);
      analogWrite(ENB, 150);
    }
   else if(receive_data.xAxis > 400) 
    {
      digitalWrite(MotorA1, LOW);
      digitalWrite(MotorA2, HIGH);
      digitalWrite(MotorB1, LOW);
      digitalWrite(MotorB2, HIGH);
      analogWrite(ENA, 150);
      analogWrite(ENB, 150);
    }
   else // for neutral position
    {
      digitalWrite(MotorA1, LOW);
      digitalWrite(MotorA2, LOW);
      digitalWrite(MotorB1, LOW);
      digitalWrite(MotorB2, LOW);
      analogWrite(ENA, 0);
      analogWrite(ENB, 0);
    }
 }
}
