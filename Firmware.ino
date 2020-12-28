
// Include Libraries
#include "Arduino.h"
#include "SoftwareSerial.h"
#include "Adafruit_GPS.h"
#include "gfxfont.h"
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"
#include "Servo.h"
#include "TMP102.h"


// Pin Definitions
#define CAPACITIVETOUCHMOMENT_3V3_PIN_OUT	2
#define GPSADAFUIT_PIN_RX	11
#define GPSADAFUIT_PIN_TX	10
#define IRPROXIMITY_PIN_VOUT	A3
#define SERVO360_PIN_SIG	3



// Global variables and defines
#define GPSECHO  true
uint32_t timer = millis(); //timer to read & print out the current stats
boolean usingInterrupt = false; // off by default! this keeps track of whether we're using the interrupt
// object initialization
SoftwareSerial gpsSerial(GPSADAFUIT_PIN_TX,GPSADAFUIT_PIN_RX);
Adafruit_GPS gpsAdafuit(&gpsSerial);
Adafruit_8x8matrix LedMatrixMini = Adafruit_8x8matrix();
Servo servo360;
TMP102 tmp102;


// define vars for testing menu
const int timeout = 10000;       //define timeout of 10 sec
char menuOption = 0;
long time0;

// Setup the essentials for your circuit to work. It runs first every time your circuit is powered with electricity.
void setup() 
{
    // Setup Serial which is useful for debugging
    // Use the Serial Monitor to view printed messages
    Serial.begin(9600);
    while (!Serial) ; // wait for serial port to connect. Needed for native USB
    Serial.println("start");
    
    gpsAdafuit.init();
    LedMatrixMini.begin(0x70); // pass in the address
    menuOption = menu();
    
}

// Main logic of your circuit. It defines the interaction between the components you selected. After setup, it runs over and over again, in an eternal loop.
void loop() 
{
    
    
    if(menuOption == '1')
    {
    // Disclaimer: The AT42QT1010 - Momentary Capacitive Touch Sensor Breakout is in testing and/or doesn't have code, therefore it may be buggy. Please be kind and report any bugs you may find.
    }
    else if(menuOption == '2') {
    // Adafruit Ultimate GPS Breakout - 66 channel w/10 Hz updates - Version 3 - Test Code
    if (! usingInterrupt) {
    // read data from the GPS in the 'main loop'
    char c = gpsAdafuit.read();
    // if you want to debug, this is a good time to do it!
    if (GPSECHO)
    if (c) Serial.print(c);
    }
    // if a sentence is received, we can check the checksum, parse it...
    if (gpsAdafuit.newNMEAreceived()) {
    // a tricky thing here is if we print the NMEA sentence, or data
    // we end up not listening and catching other sentences!
    // so be very wary if using OUTPUT_ALLDATA and trytng to print out data
    //Serial.println(gpsAdafuit.lastNMEA());   // this also sets the newNMEAreceived() flag to false
    if (!gpsAdafuit.parse(gpsAdafuit.lastNMEA()))   // this also sets the newNMEAreceived() flag to false
    return;  // we can fail to parse a sentence in which case we should just wait for another
    }
    // if millis() or timer wraps around, we'll just reset it
    if (timer > millis())  timer = millis();
    // approximately every 2 seconds or so, print out the current stats
    if (millis() - timer > 2000) {
    timer = millis(); // reset the timer
    Serial.print("\nTime: ");
    Serial.print(gpsAdafuit.hour, DEC); Serial.print(':');
    Serial.print(gpsAdafuit.minute, DEC); Serial.print(':');
    Serial.print(gpsAdafuit.seconds, DEC); Serial.print('.');
    Serial.println(gpsAdafuit.milliseconds);
    Serial.print("Date: ");
    Serial.print(gpsAdafuit.day, DEC); Serial.print('/');
    Serial.print(gpsAdafuit.month, DEC); Serial.print("/20");
    Serial.println(gpsAdafuit.year, DEC);
    Serial.print("Fix: "); Serial.print((int)gpsAdafuit.fix);
    Serial.print(" quality: "); Serial.println((int)gpsAdafuit.fixquality);
    if (gpsAdafuit.fix) {
    Serial.print("Location: ");
    Serial.print(gpsAdafuit.latitude, 4); Serial.print(gpsAdafuit.lat);
    Serial.print(", ");
    Serial.print(gpsAdafuit.longitude, 4); Serial.println(gpsAdafuit.lon);
    Serial.print("Location (in degrees, works with Google Maps): ");
    Serial.print(gpsAdafuit.latitudeDegrees, 4);
    Serial.print(", ");
    Serial.println(gpsAdafuit.longitudeDegrees, 4);
    Serial.print("Speed (knots): "); Serial.println(gpsAdafuit.speed);
    Serial.print("Angle: "); Serial.println(gpsAdafuit.angle);
    Serial.print("Altitude: "); Serial.println(gpsAdafuit.altitude);
    Serial.print("Satellites: "); Serial.println((int)gpsAdafuit.satellites);
    }
    }
    }
    else if(menuOption == '3')
    {
    // Disclaimer: The Adafruit HTU21D-F Temperature & Humidity Sensor Breakout Board is in testing and/or doesn't have code, therefore it may be buggy. Please be kind and report any bugs you may find.
    }
    else if(menuOption == '4')
    {
    // Disclaimer: The Infrared Proximity Sensor Long Range - Sharp GP2Y0A02YK0F is in testing and/or doesn't have code, therefore it may be buggy. Please be kind and report any bugs you may find.
    }
    else if(menuOption == '5')
    {
    // Disclaimer: The Triple-axis Accelerometer+Magnetometer (Compass) Board - LSM303 is in testing and/or doesn't have code, therefore it may be buggy. Please be kind and report any bugs you may find.
    }
    else if(menuOption == '6') {
    // Adafruit Mini 8x8 LED Matrix with I2C Backpack - Ultra Bright White - Test Code
    LedMatrixMini.setTextSize(1);
    LedMatrixMini.setTextWrap(false);  // we dont want text to wrap so it scrolls nicely
    LedMatrixMini.setTextColor(LED_ON);
    for (int i=0; i<4; i++) {
    LedMatrixMini.setRotation(i);
    for (int8_t x=0; x>=-36; x--) {
    LedMatrixMini.clear();
    LedMatrixMini.setCursor(x,0);
    LedMatrixMini.print("Circuito");
    LedMatrixMini.writeDisplay();
    delay(120);
    }
    }
    }
    else if(menuOption == '7') {
    // Servo - Generic Continuous Rotation (Micro Size) - Test Code
    // The servo will rotate CW in full speed, CCW in full speed, and will stop  with an interval of 2000 milliseconds (2 seconds) 
    servo360.attach(SERVO360_PIN_SIG);         // 1. attach the servo to correct pin to control it.
    servo360.write(180);  // 2. turns servo CW in full speed. change the value in the brackets (180) to change the speed. As these numbers move closer to 90, the servo will move slower in that direction.
    delay(2000);                              // 3. waits 2000 milliseconds (2 sec). change the value in the brackets (2000) for a longer or shorter delay in milliseconds.
    servo360.write(0);    // 4. turns servo CCW in full speed. change the value in the brackets (0) to change the speed. As these numbers move closer to 90, the servo will move slower in that direction.
    delay(2000);                              // 5. waits 2000 milliseconds (2 sec). change the value in the brackets (2000) for a longer or shorter delay in milliseconds.
    servo360.write(90);    // 6. sending 90 stops the servo 
    delay(2000);                              // 7. waits 2000 milliseconds (2 sec). change the value in the brackets (2000) for a longer or shorter delay in milliseconds.
    servo360.detach();                    // 8. release the servo to conserve power. When detached the servo will NOT hold it's position under stress.
    }
    else if(menuOption == '8') {
    // SparkFun TMP102 - Digital Temperature Sensor Breakout - Test Code
    float tmp102TempC = tmp102.readCelsius();
    Serial.print(F("Temp: ")); Serial.print(tmp102TempC); Serial.println(F("[°C]"));

    }
    
    if (millis() - time0 > timeout)
    {
        menuOption = menu();
    }
    
}



// Menu function for selecting the components to be tested
// Follow serial monitor for instrcutions
char menu()
{

    Serial.println(F("\nWhich component would you like to test?"));
    Serial.println(F("(1) AT42QT1010 - Momentary Capacitive Touch Sensor Breakout"));
    Serial.println(F("(2) Adafruit Ultimate GPS Breakout - 66 channel w/10 Hz updates - Version 3"));
    Serial.println(F("(3) Adafruit HTU21D-F Temperature & Humidity Sensor Breakout Board"));
    Serial.println(F("(4) Infrared Proximity Sensor Long Range - Sharp GP2Y0A02YK0F"));
    Serial.println(F("(5) Triple-axis Accelerometer+Magnetometer (Compass) Board - LSM303"));
    Serial.println(F("(6) Adafruit Mini 8x8 LED Matrix with I2C Backpack - Ultra Bright White"));
    Serial.println(F("(7) Servo - Generic Continuous Rotation (Micro Size)"));
    Serial.println(F("(8) SparkFun TMP102 - Digital Temperature Sensor Breakout"));
    Serial.println(F("(menu) send anything else or press on board reset button\n"));
    while (!Serial.available());

    // Read data from serial monitor if received
    while (Serial.available()) 
    {
        char c = Serial.read();
        if (isAlphaNumeric(c)) 
        {   
            
            if(c == '1') 
    			Serial.println(F("Now Testing AT42QT1010 - Momentary Capacitive Touch Sensor Breakout - note that this component doesn't have a test code"));
    		else if(c == '2') 
    			Serial.println(F("Now Testing Adafruit Ultimate GPS Breakout - 66 channel w/10 Hz updates - Version 3"));
    		else if(c == '3') 
    			Serial.println(F("Now Testing Adafruit HTU21D-F Temperature & Humidity Sensor Breakout Board - note that this component doesn't have a test code"));
    		else if(c == '4') 
    			Serial.println(F("Now Testing Infrared Proximity Sensor Long Range - Sharp GP2Y0A02YK0F - note that this component doesn't have a test code"));
    		else if(c == '5') 
    			Serial.println(F("Now Testing Triple-axis Accelerometer+Magnetometer (Compass) Board - LSM303 - note that this component doesn't have a test code"));
    		else if(c == '6') 
    			Serial.println(F("Now Testing Adafruit Mini 8x8 LED Matrix with I2C Backpack - Ultra Bright White"));
    		else if(c == '7') 
    			Serial.println(F("Now Testing Servo - Generic Continuous Rotation (Micro Size)"));
    		else if(c == '8') 
    			Serial.println(F("Now Testing SparkFun TMP102 - Digital Temperature Sensor Breakout"));
            else
            {
                Serial.println(F("illegal input!"));
                return 0;
            }
            time0 = millis();
            return c;
        }
    }
}

/*******************************************************

*    Circuito.io is an automatic generator of schematics and code for off
*    the shelf hardware combinations.

*    Copyright (C) 2016 Roboplan Technologies Ltd.

*    This program is free software: you can redistribute it and/or modify
*    it under the terms of the GNU General Public License as published by
*    the Free Software Foundation, either version 3 of the License, or
*    (at your option) any later version.

*    This program is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*    GNU General Public License for more details.

*    You should have received a copy of the GNU General Public License
*    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*    In addition, and without limitation, to the disclaimers of warranties 
*    stated above and in the GNU General Public License version 3 (or any 
*    later version), Roboplan Technologies Ltd. ("Roboplan") offers this 
*    program subject to the following warranty disclaimers and by using 
*    this program you acknowledge and agree to the following:
*    THIS PROGRAM IS PROVIDED ON AN "AS IS" AND "AS AVAILABLE" BASIS, AND 
*    WITHOUT WARRANTIES OF ANY KIND EITHER EXPRESS OR IMPLIED.  ROBOPLAN 
*    HEREBY DISCLAIMS ALL WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT 
*    NOT LIMITED TO IMPLIED WARRANTIES OF MERCHANTABILITY, TITLE, FITNESS 
*    FOR A PARTICULAR PURPOSE, NON-INFRINGEMENT, AND THOSE ARISING BY 
*    STATUTE OR FROM A COURSE OF DEALING OR USAGE OF TRADE. 
*    YOUR RELIANCE ON, OR USE OF THIS PROGRAM IS AT YOUR SOLE RISK.
*    ROBOPLAN DOES NOT GUARANTEE THAT THE PROGRAM WILL BE FREE OF, OR NOT 
*    SUSCEPTIBLE TO, BUGS, SECURITY BREACHES, OR VIRUSES. ROBOPLAN DOES 
*    NOT WARRANT THAT YOUR USE OF THE PROGRAM, INCLUDING PURSUANT TO 
*    SCHEMATICS, INSTRUCTIONS OR RECOMMENDATIONS OF ROBOPLAN, WILL BE SAFE 
*    FOR PERSONAL USE OR FOR PRODUCTION OR COMMERCIAL USE, WILL NOT 
*    VIOLATE ANY THIRD PARTY RIGHTS, WILL PROVIDE THE INTENDED OR DESIRED
*    RESULTS, OR OPERATE AS YOU INTENDED OR AS MAY BE INDICATED BY ROBOPLAN. 
*    YOU HEREBY WAIVE, AGREE NOT TO ASSERT AGAINST, AND RELEASE ROBOPLAN, 
*    ITS LICENSORS AND AFFILIATES FROM, ANY CLAIMS IN CONNECTION WITH ANY OF 
*    THE ABOVE. 
********************************************************/