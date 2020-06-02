#include <OneWire.h>
#include <DallasTemperature.h>

// This is an updated version of the Tester program that comes with the DallasTemp library
// It will drive a DS18x20 tempurature sensor plugged directly to the Arduino header pins 8,9, and 10.
// The flat side of the sensor should face into the center of the board.
// More info and a video here...
// http://wp.josh.com/2014/06/23/no-external-pull-up-needed-for-ds18b20-temp-sensor/#more-1892


// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS 9
#define TEMPERATURE_PRECISION 9

// Uncomment this line if you are using the updated dallas_temp_library that 
// supports the busFail() method to diagnose bus problems
// #define BUSFAIL 

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

void setup(void)
{
  
  // This lines just make it so you can plug a DS18B20 directly into 
  // digitial pins 8-10. 

  // start serial port
  Serial.begin(9600);
  Serial.println("Dallas Temperature IC Control Library Demo");
    
}


void loop(void)
{ 
 

   int numberOfDevices; // Number of temperature devices found

  DeviceAddress tempDeviceAddress; // We'll use this variable to store a found device address    
  
  // For testing purposes, reset the bus every loop so we can see if any devices appear or fall off

 sensors.begin();

 
/*****************************************************************************_____-: Checks for power mode of sensor:-______*******************************************/
  Serial.print(" Parasite:"); 
  if (sensors.isParasitePowerMode()) Serial.print("ON ");
  else Serial.print("OFF ");
  
  /*****************************************************************************_____-:Grab a count of devices on the wire:-______*******************************************/
  numberOfDevices = sensors.getDeviceCount();  
  Serial.print("Count:");
  Serial.print(numberOfDevices, DEC);


  sensors.requestTemperatures(); // Send the command to get temperatures
  
 /*****************************************************************************_____-: Loop through each device, print out temperature data:-______*******************************************/
  
  for(int i=0;i<numberOfDevices; i++)
  {
    // Search the wire for address
    if(sensors.getAddress(tempDeviceAddress, i))
	{
		// Output the device ID
		Serial.print(" #");
		Serial.print(i,DEC);
		Serial.print("=");


                float tempC = sensors.getTempC(tempDeviceAddress);

                Serial.print(tempC); // Converts tempC to Fahrenheit

	} 
  /*****************************************************************************_____-: else ghost device! Check your power requirements and cabling:-______*******************************************/

  }
  
 Serial.println("");
  
 delay(1000); 
}




/*****************************************************************************_____-: Getting Device Id For Other Connected Devices In The  Bus:-______*******************************************/


// function to print a device address
void printAddress(DeviceAddress deviceAddress)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }

}
