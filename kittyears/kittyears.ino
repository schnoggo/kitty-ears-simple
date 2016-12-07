// Circuit Playground Kitty Ears
// Author: Lon Koenig
// License: MIT License (https://opensource.org/licenses/MIT)
#include <Adafruit_CircuitPlayground.h>
#include <Wire.h>
#include <SPI.h>
#include <Servo.h>


#define G_BOUNCE_THRESHOLD .2

// servo stuff
#define left_servo_pin 10
#define right_servo_pin  6
Servo servoLeft;              // Define left servo
Servo servoRight;             // Define right servo
int angle = 0;

float last_accel_reading_x = 0;
float last_accel_reading_y = 0;
int current_rotation_left_ear  = -99;
int current_rotation_right_ear = -99;




void setup() {

    Serial.begin(9600);
  // Initialize Circuit Playground library.
  CircuitPlayground.begin();

  CircuitPlayground.setAccelRange(LIS3DH_RANGE_2_G);
  // LIS3DH_RANGE_2_G
  // LIS3DH_RANGE_4_G
  // LIS3DH_RANGE_8_G
  // LIS3DH_RANGE_16_G

   servoLeft.attach(left_servo_pin);
   servoRight.attach(right_servo_pin);
}

void loop() {


  // Grab x, y acceleration values (in m/s^2).
  float x_vector = CircuitPlayground.motionX();
  float y_vector = CircuitPlayground.motionY();

  if ( abs(last_accel_reading_x - x_vector) > G_BOUNCE_THRESHOLD ){
    last_accel_reading_x = x_vector;
    angle = floor(90+( 4* x_vector));
    rotate_left_ear_degrees(angle);
    angle = floor(90+(-4 * x_vector));
    rotate_right_ear_degrees(angle);
  }


  float last_accel_reading_x = 0;
  float last_accel_reading_y = 0;
  int current_rotation_left_ear  = -99;
  int current_rotation_right_ear = -99;


  /*
  // Use the magnitude of acceleration to interpolate the mouse velocity.
  float x_mag = abs(x);
  float x_mouse = lerp(x_mag, XACCEL_MIN, XACCEL_MAX, 0.0, XMOUSE_RANGE);
  float y_mag = abs(y);
  float y_mouse = lerp(y_mag, YACCEL_MIN, YACCEL_MAX, 0.0, YMOUSE_RANGE);
  // Change the mouse direction based on the direction of the acceleration.
  if (x < 0) {
    x_mouse *= -1.0;
  }
  if (y < 0) {
    y_mouse *= -1.0;
  }
  // Apply any global scaling to the axis (to flip it for example) and truncate
  // to an integer value.
  x_mouse = floor(x_mouse*XMOUSE_SCALE);
  y_mouse = floor(y_mouse*YMOUSE_SCALE);
angle=90+x_mouse*2;
*/
// Serial.println(x);



  // Small delay
  delay(20);


}

void rotate_left_ear_degrees(int dest_rotation){
  // servoLeft is a global
  dest_rotation = min(dest_rotation, 180);
  dest_rotation = max(0, dest_rotation);
  servoLeft.write(dest_rotation);
}

void rotate_right_ear_degrees(int dest_rotation){
  // servoRight is a global
  dest_rotation = min(dest_rotation, 180);
  dest_rotation = max(0, dest_rotation);
  servoRight.write(dest_rotation);
}
