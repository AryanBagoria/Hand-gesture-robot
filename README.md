# NRF24L01 Wireless Robot Control (Receiver)

This Arduino sketch serves as the **receiver code** for a wirelessly controlled robot using an **NRF24L01 radio module**. It reads joystick data (X and Y axis values) transmitted from a corresponding sender unit and translates these values into motor commands to control a robotic platform.

## Features

* **Wireless Communication:** Utilizes the NRF24L01 module for robust 2.4 GHz wireless data transmission.
* **Joystick Control:** Interprets X and Y axis data from a remote joystick to dictate robot movement.
* **Differential Drive Control:** Controls two DC motors (likely via an H-bridge motor driver) to achieve forward, backward, left, right, and stop movements.
* **Adjustable Speed:** Motor speed is set to a constant value (150 PWM) but can be easily modified.
* **Low Power Transmission:** Configured for minimum power amplification (`RF24_PA_MIN`) for basic range and power efficiency.

---

## Hardware Requirements

* **Arduino Board:** (e.g., Arduino Uno, Nano, Mega)
* **NRF24L01 Wireless Transceiver Module:** (with breakout board if necessary)
* **L298N Motor Driver Module:** Or any equivalent H-bridge motor driver
* **DC Motors:** 2 motors for differential drive robot
* **Power Supply:** Suitable for your motors and Arduino

---

## Wiring Diagram

Connect the components as follows. Please verify the pin numbers on your specific Arduino board and motor driver, as they might vary.

### NRF24L01 Module Connections:

| NRF24L01 Pin | Arduino Pin |
| :----------- | :---------- |
| VCC          | 3.3V        |
| GND          | GND         |
| CE           | 8           |
| CSN          | 10          |
| SCK          | 13          |
| MOSI         | 11          |
| MISO         | 12          |

**Note:** The SCK, MOSI, and MISO pins are the SPI pins, which are fixed on most Arduino boards (e.g., Uno: 13, 11, 12 respectively). CE and CSN pins are user-definable; in this code, they are 8 and 10.

### Motor Driver (L298N) and Motor Connections:

| L298N Pin | Arduino Pin | Description              |
| :-------- | :---------- | :----------------------- |
| ENA       | 3 (PWM)     | Motor A Enable/Speed     |
| IN1       | 4           | Motor A Direction Control|
| IN2       | 5           | Motor A Direction Control|
| IN3       | 6           | Motor B Direction Control|
| IN4       | 7           | Motor B Direction Control|
| ENB       | 9 (PWM)     | Motor B Enable/Speed     |

Connect your two DC motors to the Motor A and Motor B output terminals on the L298N. Ensure the L298N's power input (12V or 5V depending on your motors) and ground are connected to a suitable power source.

---

## Software Requirements

* **Arduino IDE:** [Download from Arduino.cc](https://www.arduino.cc/en/software)
* **RF24 Library:** Install via Arduino IDE's Library Manager (Sketch > Include Library > Manage Libraries...). Search for "RF24" by TMRh20.

---

## Installation and Usage

1.  **Install Arduino IDE:** If you haven't already, download and install the Arduino IDE.
2.  **Install Libraries:** Open the Arduino IDE. Go to `Sketch > Include Library > Manage Libraries...`. Search for `RF24` and install the library by `TMRh20`.
3.  **Upload the Code:**
    * Open the provided `.ino` file in the Arduino IDE.
    * Select your Arduino board from `Tools > Board`.
    * Select the correct COM Port for your Arduino from `Tools > Port`.
    * Click the "Upload" button to compile and upload the code to your Arduino board.
4.  **Power Up:** Once uploaded, ensure your robot is powered correctly.

---

## How it Works

The code continuously listens for incoming data from the NRF24L01 module. The `data` struct expects `xAxis` and `yAxis` integers, typically ranging from 0-1023 (for a 10-bit ADC).

* **Forward:** `yAxis > 400`
* **Backward:** `yAxis < 320`
* **Right Turn:** `xAxis > 400`
* **Left Turn:** `xAxis < 320`
* **Stop:** If no directional input is received within the specified thresholds (i.e., `xAxis` and `yAxis` are within the dead zone, typically around 320-400), the motors are stopped.

The `analogWrite()` function is used to set the motor speed (PWM value). The current speed is set to `150` for both motors, which can be adjusted from 0 (off) to 255 (full speed).

---

## Customization

* **NRF24L01 Address:** The `address` byte array (`"00001"`) must match the address used by your sender NRF24L01 module for communication.
* **Motor Control Pins:** Adjust `ENA`, `ENB`, `MotorA1`, `MotorA2`, `MotorB1`, `MotorB2` to match your motor driver's connections.
* **Joystick Thresholds:** The values `400` and `320` for `xAxis` and `yAxis` define the "dead zone" of your joystick. You might need to adjust these based on your joystick's output range and desired sensitivity.
* **Motor Speed:** Change the `150` value in `analogWrite(ENA, 150)` and `analogWrite(ENB, 150)` to increase or decrease the robot's speed.
* **NRF24L01 Power Level:** `radio.setPALevel(RF24_PA_MIN)` sets the minimum transmitting power. You can change this to `RF24_PA_LOW`, `RF24_PA_HIGH`, or `RF24_PA_MAX` to adjust the range, keeping in mind higher power consumes more energy.
* **Data Rate:** `radio.setDataRate(RF24_250KBPS)` sets the data transfer rate. Other options include `RF24_1MBPS` and `RF24_2MBPS`. A lower data rate generally provides better range and reliability.

---

## Troubleshooting

* **"RF24 library not found":** Ensure you've installed the RF24 library correctly through the Arduino IDE's Library Manager.
* **No communication:**
    * Double-check all wiring, especially the NRF24L01 module's VCC (3.3V) and GND.
    * Ensure the `address` byte array is identical on both the sender and receiver NRF24L01 modules.
    * Verify both modules are powered on.
    * Check the baud rate in `Serial.begin()` matches any serial monitor you are using for debugging.
* **Motors not moving/moving incorrectly:**
    * Ensure your motor driver is correctly wired and receiving sufficient power.
    * Verify the `MotorA` and `MotorB` pins are connected to the correct `IN` pins on your motor driver.
    * Check if `ENA` and `ENB` are connected to PWM-capable pins on your Arduino (pins 3 and 9 are PWM on Uno).
    * Adjust `receive_data.yAxis` and `receive_data.xAxis` thresholds if your joystick's neutral position or range is different.
