#include "Adafruit_MLX90393.h"
 #define RAD_TO_DEG 57.295
Adafruit_MLX90393 sensor = Adafruit_MLX90393();
#define MLX90393_CS 10

// parametrit Missä käänsin kaikkia akseleita pitkin
    float defaultXb_ =3.345839;
    float defaultYb_ = -44.911106;
    float defaultZb_ = 43.41767;
    
    float default_s11 = 1.044880;
    float default_s12=  0.021320;
    float default_s13 = 0.029141;

    float default_s21 = 0.021320;
    float default_s22=  1.186608;
    float default_s23 = 0.013212;

    float default_s31 = 0.029141;
    float default_s32=  0.013212;
    float default_s33 = 1.041497;

//**************************************
/* Parametrit, mis käänsin vain X ja Y ympäri huom kuinka iso on diagonaalit!!

    float defaultXb_ =5.342067;
    float defaultYb_ = -46.328909;
    float defaultZb_ = -3.784576;
    
    float default_s11 = 3.958458;
    float default_s12=  -0.009681;
    float default_s13 = 0.227066;

    float default_s21 = -0.009681;
    float default_s22=  4.169884;
    float default_s23 = 0.026928;

    float default_s31 = 0.227066;
    float default_s32=  0.026928;
    float default_s33 = 5.524710;

*/
//**************************************



void setup(void)
{
  Serial.begin(9600);

  /* Wait for serial on USB platforms. */
  while (!Serial) {
      delay(10);



  }

 // Serial.println("Starting Adafruit MLX90393 Demo");

  if (! sensor.begin_I2C()) {          // hardware I2C mode, can pass in address & alt Wire
  //if (! sensor.begin_SPI(MLX90393_CS)) {  // hardware SPI mode
//    Serial.println("No sensor found ... check your wiring?");
    while (1) { delay(10); }
  }
//  Serial.println("Found a MLX90393 sensor");

  sensor.setGain(MLX90393_GAIN_1X);
  // You can check the gain too
 /*
  
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
  sensor.setResolution(MLX90393_X, MLX90393_RES_17);
  sensor.setResolution(MLX90393_Y, MLX90393_RES_17);
  sensor.setResolution(MLX90393_Z, MLX90393_RES_16);

  // Set oversampling
  sensor.setOversampling(MLX90393_OSR_3);

  // Set digital filtering
  sensor.setFilter(MLX90393_FILTER_5);
}

void loop(void) {

  /*
  float x, y, z;

  // get X Y and Z data at once
  if (sensor.readData(&x, &y, &z)) {
      Serial.print("X: "); Serial.print(x, 4); Serial.println(" uT");
      Serial.print("Y: "); Serial.print(y, 4); Serial.println(" uT");
      Serial.print("Z: "); Serial.print(z, 4); Serial.println(" uT");
  } else {
      Serial.println("Unable to read XYZ data from the sensor.");
  }

  delay(500);
*/
  /* Or....get a new sensor event, normalized to uTesla */
  sensors_event_t event;
  sensor.getEvent(&event);
  /* Display the results (magnetic field is measured in uTesla) */
  float x = event.magnetic.x-defaultXb_;
  float y = event.magnetic.y-defaultYb_;
  float z = event.magnetic.z-defaultZb_;
   
  float x1= default_s11*x +default_s12*y+default_s13*z;
  float y1= default_s21*x +default_s22*y+default_s23*z;
  float z1= default_s31*x +default_s32*y+default_s33*z;

  //Serial.print(" X: "); Serial.print(x1);
  //Serial.print(" Y: "); Serial.print(y1);
  //((Serial.print(" Z: "); Serial.println(z1);

  float nx=sqrt(x1 *x1 +y1 * y1 + z1 * z1);
  float yn=y1/nx;
  float xn=x1/nx;
  float yaw = atan2(yn, xn) * RAD_TO_DEG;

  
  // Output the Euler angles

  Serial.print(" Z: "); Serial.println(yaw);
  
  delay(500);
}
