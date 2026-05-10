#include <Wire.h> 


// 0011110b, I2C 7bit addressHMC5883 of HMC5883

#define addressHMC5883 0x0D
// Magnetometer variables
int xRaw, yRaw, zRaw;

// Calculated maximum value for each variable
// for callibration
// int xMax = -32765; 
// int xMin = 32765;
// int yMax = -32765;
// int yMin = 32765;

int xMax = 0; 
int xMin = 0;
int yMax = 0;
int yMin = 0;

// Printing variables
bool printStartingInstructions = true;
unsigned long lastTimeUpdatePrint = 0;
unsigned long timeUpdateInterval = 5000; // interval to print time update

// Calibration time in milliseconds
unsigned long calibrationTime = 30000;

unsigned long timeNow;

void scani2c() {
	byte error, address;
	int deviceCount = 0;
	
	Serial.println("Scan start I2C devices");
	
	for (address = 1; address < 127; address++) {
		Wire.beginTransmission(address);
		error = Wire.endTransmission();
		
		if (error == 0) {
			Serial.print("Found: 0x");
			if (address < 16) Serial.print("0");
			Serial.println(address, HEX);
			deviceCount++;
		}
	}
	
	if (deviceCount == 0) {
		Serial.println("No I2C device!");
	} else {
		Serial.print("All: ");
		Serial.println(deviceCount);
	}
	
	Serial.println("-------------------");
	
}

void setup(){
//Initialize Serial and I2C communications
	Serial.begin(115200);
	delay(2000);

	Wire.setSDA(20);
	Wire.setSCL(21);

	Wire.begin();

	scani2c();
	delay (5000);

	//Put the HMC5883 IC into the correct operating mode
	Wire.write(0x09); //select mode register
	Wire.write(0x0D); //continuous measurement mode
	Wire.endTransmission();
	
	Wire.beginTransmission(addressHMC5883); //open communication with HMC5883
	Wire.write(0x0B); //select Set/Reset period register
	Wire.write(0x01); //Define Set/Reset period
	Wire.endTransmission();
}

void loop(){
	timeNow = millis();
	// If it is the first iteration, print the intructions to use this calibration program
	if(printStartingInstructions)
	{
		printInstructions();
		printStartingInstructions = false;
	}
	
	// If time is not up, update magnetometer and get values
	if (timeNow < calibrationTime)
	{
		updateMagnetometerData();
		xMax = max(xRaw, xMax);
		xMin = min(xRaw, xMin);
		yMax = max(yRaw, yMax);
		yMin = min(yRaw, yMin);

		printMagnetometerData();
		
		// Check if it is time to print the elapsed time
		if ((timeNow - lastTimeUpdatePrint) > timeUpdateInterval)
		{
			
			printTimeUpdate();
			lastTimeUpdatePrint = timeNow;
		}
	}
	
	// If time is up, print the results and stop the program
	else
	{
		updateMagnetometerData();
		printMagnetometerData();
		//printResults();
		//while(1);
	}
	delay(10);
}

void printMagnetometerData()
{
	Serial.print("Magneto: ");
	Serial.print(xRaw);
	Serial.print(", ");
	Serial.print(yRaw);
	Serial.print(", ");
	Serial.print(zRaw);
	Serial.println("");
}

void updateMagnetometerData()
{
	//Tell the magnetometer where to begin reading data
	Wire.beginTransmission(addressHMC5883);
	Wire.write(0x00); //select register 0, X MSB register
	Wire.endTransmission();
	
	//Read data from each axis, 2 registers per axis
	Wire.requestFrom(addressHMC5883, 6);
	if(Wire.available()>=6) {
		xRaw = Wire.read(); //x lsb
		xRaw |= Wire.read()<<8; //x msb
		yRaw = Wire.read(); //y lsb
		yRaw |= Wire.read()<<8;; //y msb
		zRaw = Wire.read(); //z lsb
		zRaw |= Wire.read()<<8; //z msb
	}
}

void printInstructions()
{
	// Print the instructions to use the calibration
	Serial.println("Rotate your robot in a slow rate to one direction until it has been rotate 360 degrees.");
	Serial.println("Rotate it to the other direction for another 360 degrees.");
	Serial.println("Keep rotating it until calibration time is up.");
	Serial.println("Make sure you keep the robot leveled during the calibration!");
}

void printTimeUpdate()
{
	// Print elapsed time in the claibration process
	Serial.println();
	Serial.print("Elapsed time: ");
	Serial.print(timeNow/1000);
	Serial.print("s of ");
	Serial.print(calibrationTime/1000);
	Serial.println("s");
}

void printResults()
{
	// Print the results of the calibration
	Serial.println();
	Serial.println();
	Serial.println("Finished calibration!");
	Serial.println("Copy the following numbers to your main magnetometer code:");
	Serial.print("xMin: ");
	Serial.print(xMin);
	Serial.print("\txMax: ");
	Serial.print(xMax);
	Serial.print("\tyMin: ");
	Serial.print(yMin);
	Serial.print("\tyMax: ");
	Serial.println(yMax);
}

