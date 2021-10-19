#include <Wire.h>

int accelX, accelY, accelZ;
char mpu = 0x68;
float vectorprevious;
float vector;
float totalvector;
int Steps = 0;

void setup() {
  Serial.begin(115200);
  Wire.begin(21,22);
  Wire.beginTransmission(mpu);
  Wire.write(0x6B); //  Power setting address
  Wire.write(0b00000000); // Disable sleep mode (just in case)
  Wire.endTransmission();
  Wire.beginTransmission(mpu);
  Wire.write(0x1B); // Config register for Gyro
  Wire.write(0x00000000); // 250° per second range (default)
  Wire.endTransmission();
  Wire.beginTransmission(mpu); //I2C address of the MPU
  Wire.write(0x1C); // Accelerometer config register
  Wire.write(0b00000000); // 2g range +/- (default)
  Wire.endTransmission();
}
void loop() {
  getAccel();
  vector = sqrt( (accelX * accelX) + (accelY * accelY) + (accelZ * accelZ) );
  totalvector = vector - vectorprevious;
  if (totalvector > 6) {
    Steps++;
  }
  Serial.println(Steps);
  vectorprevious = vector;
  delay(600);
}
void getAccel() {
  Wire.beginTransmission(mpu); //I2C address of the MPU
  Wire.write(0x3B); //  Acceleration data register
  Wire.endTransmission();
  Wire.requestFrom(mpu, 6); // Get 6 bytes, 2 for each DoF
  accelX = Wire.read() << 8 | Wire.read();
  accelY = Wire.read() << 8 | Wire.read();
  accelZ = Wire.read() << 8 | Wire.read();
}
