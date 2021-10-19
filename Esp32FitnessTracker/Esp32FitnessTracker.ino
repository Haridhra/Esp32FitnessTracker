// Limit to single core for examples
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include "MAX30100_PulseOximeter.h"
 
#define REPORTING_PERIOD_MS 1000
PulseOximeter pox; 
uint32_t tsLastReport = 0;
void onBeatDetected(){
  Serial.println("Beat!");
}
float vector, vectorprevious, totalvector = 0; int Steps = 0;

Adafruit_MPU6050 mpu;

#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
#else
static const BaseType_t app_cpu = 1;
#endif

//Pin definitions
static const unsigned int led_pin = 2;  //BUILTIN_LED = pin 2

//Task : Get pulse oximeter data every 300ms
void task_getPulseOximeter(void *parameter) {
  while(1) {
  if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
  Serial.print("Heart rate:");
  Serial.print(pox.getHeartRate());
  Serial.print("bpm / SpO2:");
  Serial.print(pox.getSpO2());
  Serial.println("%");
  
  tsLastReport = millis();
  }
    vTaskDelay(300 / portTICK_PERIOD_MS);
  }
}


//Task : Get step count data every 500ms
void task_getStepCount(void *parameter) {
    while(1) {
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);
    
    vector = sqrt( (a.acceleration.x * a.acceleration.x) + (a.acceleration.y * a.acceleration.y) + (a.acceleration.z * a.acceleration.z) );
    totalvector = vector - vectorprevious;
      if (totalvector*10 > 6) {
      Steps++;
    }
    Serial.println(Steps);
    vectorprevious = vector;
    //Serial.println("Analyse Pulse Oximeter Data");
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(led_pin, OUTPUT);
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  Serial.print("Initializing pulse oximeter..");
  if (!pox.begin()) {
  Serial.println("FAILED");
  for(;;);
  } else {
  Serial.println("SUCCESS");
  }

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  
  xTaskCreatePinnedToCore(
              task_getPulseOximeter, //function to be called
              "Read Pulse Oximeter", //name
              1024, //stack size
              NULL, //parameters
              1, //priority
              NULL, //task handle
              app_cpu); //Run on one core
            
  xTaskCreatePinnedToCore(
            task_getStepCount, //function to be called
            "Get step count", //name
            2048, //stack size
            NULL, //parameters
            1, //priority
            NULL, //task handle
            app_cpu); //Run on one core
}

void loop() {
  
  pox.update();

}
