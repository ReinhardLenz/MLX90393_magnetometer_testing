
#include "Adafruit_MLX90393.h"
Adafruit_MLX90393 sensor = Adafruit_MLX90393();
#define MLX90393_CS 10
#define SAMPLERATE_DELAY_MS (100)
void setup(void)
{
  Serial.begin(9600);

  /* Wait for serial on USB platforms. */
  while (!Serial) {
      delay(10);
  }

//  Serial.println("Starting Adafruit MLX90393 Demo");

  if (! sensor.begin_I2C()) {          // hardware I2C mode, can pass in address & alt Wire
  //if (! sensor.begin_SPI(MLX90393_CS)) {  // hardware SPI mode
  Serial.println("No sensor found ... check your wiring?");
    while (1) { delay(10); }
  }

//  Serial.println("Found a MLX90393 sensor");

  sensor.setGain(MLX90393_GAIN_1X);
/*
  // You can check the gain too
  Serial.print("Gain set to: ");
  switch (sensor.getGain()) {
    case MLX90393_GAIN_1X: Serial.println("1 x"); break;
    case MLX90393_GAIN_1_33X: Serial.println("1.33 x"); break;
    case MLX90393_GAIN_1_67X: Serial.println("1.67 x"); break;
    case MLX90393_GAIN_2X: Serial.println("2 x"); break;
    case MLX90393_GAIN_2_5X: Serial.println("2.5 x"); break;
    case MLX90393_GAIN_3X: Serial.println("3 x"); break;
    case MLX90393_GAIN_4X: Serial.println("4 x"); break;
    case MLX90393_GAIN_5X: Serial.println("5 x"); break;
  }
*/
  // Set resolution, per axis. Aim for sensitivity of ~0.3 for all axes.
  sensor.setResolution(MLX90393_X, MLX90393_RES_16);
  sensor.setResolution(MLX90393_Y, MLX90393_RES_16);
  sensor.setResolution(MLX90393_Z, MLX90393_RES_16);



  // Set oversampling
  sensor.setOversampling(MLX90393_OSR_3);

  // Set digital filtering
  sensor.setFilter(MLX90393_FILTER_5);
}

void loop() {
    float x, y, z;
    // get X Y and Z data at once
if (sensor.readData(&x, &y, &z)) {
    // Check if any of the x, y, or z values are zero
    if (x == 0.0 || y == 0.0 || z ==0.0) {
    } else {
        // If none are zero, then print the values
        Serial.print(x, 6); Serial.print(",");
        Serial.print(y, 6); Serial.print(",");
        Serial.println(z, 6);
    }
} else {
    delay(SAMPLERATE_DELAY_MS);
}
    delay(SAMPLERATE_DELAY_MS);
}
