// Limit to single core for examples
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
    // do task
    Serial.println("Get Pulse Oximeter Data");
    vTaskDelay(300 / portTICK_PERIOD_MS);
  }
}

//Task : Analyse pulse oximeter data every 300ms
void task_analysePulseOximeter(void *parameter) {
  while(1) {
    // do task
    Serial.println("Analyse Pulse Oximeter Data");
    vTaskDelay(300 / portTICK_PERIOD_MS);
  }
}

void setup() {
  // put your setup code here, to run once:
  pinMode(led_pin, OUTPUT);

  xTaskCreatePinnedToCore(
              task_getPulseOximeter, //function to be called
              "Read Pulse Oximeter", //name
              1024, //stack size
              NULL, //parameters
              1, //priority
              NULL, //task handle
              app_cpu); //Run on one core

  xTaskCreatePinnedToCore(
            task_analysePulseOximeter, //function to be called
            "Analyse Pulse Oximtery", //name
            1024, //stack size
            NULL, //parameters
            1, //priority
            NULL, //task handle
            app_cpu); //Run on one core
}

void loop() {
  // put your main code here, to run repeatedly:

}
