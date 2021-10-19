#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_TFTLCD.h> // Hardware-specific library

// The control pins for the LCD can be assigned to any digital or
// analog pins...but we'll use the analog pins as this allows us to
// double up the pins with the touch screen (see the TFT paint example).
#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0

#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin

// Assign human-readable names to some common 16-bit color values:
#define	BLACK   0x0000
#define	BLUE    0x001F
#define	RED     0xF800
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);


void setup(void) {
  Serial.begin(9600);
  Serial.println(F("Fitness Tracker TFT LCD Demo"));

  tft.reset();

  uint16_t identifier = tft.readID();

  tft.begin(identifier);
}

void loop(void) {
  heartRateDisplay(72);
  delay(2000);
  oxygenDisplay(95);
  delay(2000);
  stepCountDisplay(700);
  delay(2000);
  distanceDisplay(0.93, 0.46);
  delay(2000);
  bodyTempDisplay(97.8);
  delay(2000);
}

void heartRateDisplay(int heartrate) {
  tft.fillScreen(BLACK);
  tft.setCursor(40, 20);
  tft.setTextColor(RED);
  tft.setTextSize(3);
  tft.println("Heartrate");

  tft.setCursor(90, 70);
  tft.setTextSize(6);
  tft.println(heartrate, DEC);
}

void oxygenDisplay(int oxy) {
  tft.fillScreen(BLACK);
  tft.setCursor(0, 20);
  tft.setTextColor(YELLOW);
  tft.setTextSize(3);
  tft.println("O2 Saturation");

  tft.setCursor(80, 70);
  tft.setTextSize(6);
  tft.print(oxy, DEC);
  tft.println("%");
}

void stepCountDisplay(int steps) {
  tft.fillScreen(BLACK);
  tft.setCursor(40, 20);
  tft.setTextColor(CYAN);
  tft.setTextSize(3);
  tft.println("Step Count");

  tft.setCursor(80, 70);
  tft.setTextSize(6);
  tft.println(steps, DEC);
}

void distanceDisplay(float wDist, float rDist) {
  tft.fillScreen(BLACK);
  tft.setCursor(5, 20);
  tft.setTextColor(GREEN);
  tft.setTextSize(3);
  tft.println("Walk Distance");

  tft.setCursor(40, 70);
  tft.setTextSize(5);
  tft.print(wDist);
  tft.println("km");

  tft.setCursor(15, 130);
  tft.setTextSize(3);
  tft.println("Run Distance");

  tft.setCursor(40, 190);
  tft.setTextSize(5);
  tft.print(rDist);
  tft.println("km");
}

void bodyTempDisplay(float temp) {
  tft.fillScreen(BLACK);
  tft.setCursor(25, 20);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.println("Temperature");

  tft.setCursor(35, 70);
  tft.setTextSize(5);
  tft.print(temp);
  tft.println("F");
}
