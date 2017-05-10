#include <Wire.h>
#include <Arduino.h>
#include <MLX90393.h>

MLX90393 mlx;

const float pi = 3.1415926353;
float heading, headingDegrees, headingFiltered, declination;

void setup(){
  // DRDY line connected to A3 (omit third parameter to used timed reads)
  uint8_t status = mlx.begin(0, 0, 0);
  Serial.begin(9600);
}

void loop(){
  MLX90393::txyz data;
  mlx.readData(data);
  Serial.print(data.x);
  Serial.print(" ");
  Serial.print(data.y);
  Serial.print(" ");
  Serial.print(data.z);
  Serial.print(" ");
  Serial.println(data.t);
  delay(1);

  heading = atan2(data.y, data.x);
 
  // Correcting the heading with the declination angle depending on your location
  // You can find your declination angle at: http://www.ngdc.noaa.gov/geomag-web/
  // At my location it's 4.2 degrees => 0.073 rad
  declination = 0.073; 
  heading += declination;
  
  // Correcting when signs are reveresed
  if(heading <0) heading += 2*PI;
  // Correcting due to the addition of the declination angle
  if(heading > 2*PI)heading -= 2*PI;
  headingDegrees = heading * 180/PI;

  // Smoothing the output angle / Low pass filter 
  headingFiltered = headingFiltered*0.85 + headingDegrees*0.15;
  //Sending the heading value through the Serial Port to Processing IDE
  Serial.println(headingFiltered);

}
