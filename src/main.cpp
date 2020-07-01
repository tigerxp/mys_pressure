/*
 *  Pressure MySensors-2.x sensor
 */
#include <Arduino.h>

#define MY_DEBUG
#define MY_RADIO_RF24
#define MY_BAUD_RATE 9600

// Settings
#define BARO_CHILD_ID 0
#define BARO_SENSOR_PIN A1
#define SLEEP_TIME 20000 // 20s

#define SKETCH_NAME "Water Pressure Sensor"
#define SKETCH_MAJOR_VER "0"
#define SKETCH_MINOR_VER "5"

#include <MySensors.h>

MyMessage pressureMsg(BARO_CHILD_ID, V_PRESSURE);

void presentation() {
	sendSketchInfo(SKETCH_NAME, SKETCH_MAJOR_VER "." SKETCH_MINOR_VER);
	present(BARO_CHILD_ID, S_BARO, "Water Pressure");
}

void setup() {
#ifdef MY_DEBUG
	Serial.begin(MY_BAUD_RATE);
#endif
}

void loop(){
	int sensorVal = analogRead(A1);
#ifdef MY_DEBUG
	Serial.print("Sensor Value: ");
	Serial.print(sensorVal);
#endif

	float voltage = (sensorVal * 5.0) / 1024.0;
#ifdef MY_DEBUG
	Serial.print(" Voltage: ");
	Serial.print(voltage);
#endif

	float pressure = (voltage - 0.48) * 4.1; // bars
#ifdef MY_DEBUG
	Serial.print(" Pressure = ");
	Serial.print(pressure);
	Serial.println(" bars");
#endif

	send(pressureMsg.set(pressure, 2));
	sleep(SLEEP_TIME);
}
