// Limit to single core for examples
#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
#else
static const BaseType_t app_cpu = 1;
#endif

//Pin definitions
static const unsigned int led_pin = 2;  //BUILTIN_LED = pin 2

//constants
int rate1 = 500;
int rate2 = 333;

//Task : Toggle LED state every 500ms(Blink)
void toggleLED1(void *parameter) {
  while(1) {
    digitalWrite(led_pin, HIGH);
    vTaskDelay(rate1 / portTICK_PERIOD_MS);
    digitalWrite(led_pin, LOW);
    vTaskDelay(rate1 / portTICK_PERIOD_MS);
  }
}

//Task : Toggle LED state every 1000ms(Blink)
void toggleLED2(void *parameter) {
  while(1) {
    digitalWrite(led_pin, HIGH);
    vTaskDelay(rate2 / portTICK_PERIOD_MS);
    digitalWrite(led_pin, LOW);
    vTaskDelay(rate2 / portTICK_PERIOD_MS);
  }
}

void setup() {
  // put your setup code here, to run once:
  pinMode(led_pin, OUTPUT);

  xTaskCreatePinnedToCore(
              toggleLED1, //function to be called
              "Toggle LED 2Hz", //name
              1024, //stack size
              NULL, //parameters
              1, //priority
              NULL, //task handle
              app_cpu); //Run on one core

  xTaskCreatePinnedToCore(
            toggleLED2, //function to be called
            "Toggle LED 1HZ", //name
            1024, //stack size
            NULL, //parameters
            1, //priority
            NULL, //task handle
            app_cpu); //Run on one core
}

void loop() {
  // put your main code here, to run repeatedly:

}
