//This code is written by @tylerdurdenxd
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#define DHT11_PIN 2    
#define DHT22_PIN 3    
#define DHT11_TYPE DHT11
#define DHT22_TYPE DHT22

DHT_Unified dht11(DHT11_PIN, DHT11_TYPE);
DHT_Unified dht22(DHT22_PIN, DHT22_TYPE);

uint32_t delayMS;

void setup() {
  Serial.begin(9600);
  dht11.begin();
  dht22.begin();
  Serial.println(F("DHTxx Unified Sensor Example"));

  printSensorDetails(dht11, "DHT11");
  printSensorDetails(dht22, "DHT22");
}

void loop() {
  readAndPrintSensorData(dht11, "DHT11");
  readAndPrintSensorData(dht22, "DHT22");
  delay(5000);
}

void printSensorDetails(DHT_Unified &dht, const char* sensorName) {
  sensor_t sensor;
  Serial.print(F("------------------------------------\n"));
  Serial.print(F("Sensor: ")); Serial.println(sensorName);

  dht.temperature().getSensor(&sensor);
  Serial.println(F("Temperature Sensor"));
  Serial.print(F("Sensor Type: ")); Serial.println(sensor.name);
  Serial.print(F("Driver Ver: ")); Serial.println(sensor.version);
  Serial.print(F("Unique ID: ")); Serial.println(sensor.sensor_id);
  Serial.print(F("Max Value: ")); Serial.print(sensor.max_value); Serial.println(F("°C"));
  Serial.print(F("Min Value: ")); Serial.print(sensor.min_value); Serial.println(F("°C"));
  Serial.print(F("Resolution: ")); Serial.print(sensor.resolution); Serial.println(F("°C"));

  dht.humidity().getSensor(&sensor);
  Serial.println(F("Humidity Sensor"));
  Serial.print(F("Sensor Type: ")); Serial.println(sensor.name);
  Serial.print(F("Driver Ver: ")); Serial.println(sensor.version);
  Serial.print(F("Unique ID: ")); Serial.println(sensor.sensor_id);
  Serial.print(F("Max Value: ")); Serial.print(sensor.max_value); Serial.println(F("%"));
  Serial.print(F("Min Value: ")); Serial.print(sensor.min_value); Serial.println(F("%"));
  Serial.print(F("Resolution: ")); Serial.print(sensor.resolution); Serial.println(F("%"));
  
  delayMS = sensor.min_delay / 1000;
  Serial.print(F("------------------------------------\n"));
}

void readAndPrintSensorData(DHT_Unified &dht, const char* sensorName) {
  sensors_event_t event;

  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    Serial.print(sensorName);
    Serial.println(F(": Error reading temperature!"));
  } else {
    Serial.print(sensorName);
    Serial.print(F(" Temperature: "));
    Serial.print(event.temperature);
    Serial.println(F("°C"));
  }

  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    Serial.print(sensorName);
    Serial.println(F(": Error reading humidity!"));
  } else {
    Serial.print(sensorName);
    Serial.print(F(" Humidity: "));
    Serial.print(event.relative_humidity);
    Serial.println(F("%"));
  }
}
