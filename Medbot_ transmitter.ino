#include<SPI.h>
#include<nRF24L01.h>
#include<RF24.h>

const int x_out = A0;
const int y_out = A1;
RF24 radio(8,10);// for establishing a SPI serial communication interface (short distance Communication).
const byte address[6] = "00001"; //for creating communication between two nrf modules we need to create a pipe with an address. 
struct data
{
  int xAxis;
  int yAxis;
};

data send_data;

void setup()//setup code which will run once 
{ 
radio.begin();
radio.openWritingPipe(address);// for opening the pipe. 
radio.setPALevel(RF24_PA_MIN);// defining minimum amount of transmitting power which will help in draining minimum power consumption we can also set it to maximum as to achieve maximum range.    
radio.setDataRate(RF24_250KBPS);// defining the data rate of transmission 250 KB
radio.stopListening();
}

void loop() // used to make code repeat 
{ 
send_data.xAxis = analogRead(x_out);
send_data.yAxis = analogRead(y_out);
radio.write(&send_data, sizeof(data));
}
