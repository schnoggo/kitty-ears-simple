// Circuit Playground Kitty Ears
// Author: Lon Koenig
// License: MIT License (https://opensource.org/licenses/MIT)
#include <Adafruit_CircuitPlayground.h>
#include <Wire.h>
#include <SPI.h>
#include <Servo.h>


#define G_BOUNCE_THRESHOLD 1
#define SERVO_MIN 60
#define SERVO_MAX 90+65

// servo stuff
#define left_servo_pin 10
#define right_servo_pin  6
Servo servoLeft;              // Define left servo
Servo servoRight;             // Define right servo

float last_accel_reading_x = 0;
float last_accel_reading_y = 0;
int current_rotation_left_ear  = 90; // start at 90 degrees
int current_rotation_right_ear =  90;
unsigned long stable_start_time = millis(); // now
int rand_degree = 0;

#define stable_threshold 2000



void setup() {
  randomSeed(analogRead(12)); // Pin 12 should be floating
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

   CircuitPlayground.clearPixels();

}

void loop() {


  // Grab x, y acceleration values (in m/s^2).
  float x_vector = CircuitPlayground.motionX();
  float y_vector = CircuitPlayground.motionY();

  if ( abs(last_accel_reading_x - x_vector) > G_BOUNCE_THRESHOLD ){
    CircuitPlayground.setPixelColor(2, 0, 254, 0);
    stable_start_time = millis();
    last_accel_reading_x = x_vector;
    current_rotation_left_ear = floor(90+( -4* x_vector));
    rotate_left_ear_degrees(current_rotation_left_ear);
    current_rotation_right_ear = floor(90+(  4 * x_vector));
    rotate_right_ear_degrees(current_rotation_right_ear);
  } else {
    CircuitPlayground.setPixelColor(2, 0, 0, 0);
    if ((millis() - stable_start_time) > stable_threshold){
      CircuitPlayground.setPixelColor(1, 254, 0, 0);
    //  stable_start_time = millis();
      rand_degree =  (2 - random(5)) * 3;
      current_rotation_left_ear = clamp_servo_range(current_rotation_left_ear+rand_degree);
      rotate_left_ear_degrees(current_rotation_left_ear);

      rand_degree =  (2 - random(5)) * 3;
      current_rotation_right_ear = clamp_servo_range(current_rotation_right_ear+rand_degree);
      rotate_right_ear_degrees(current_rotation_right_ear);

    } else {
        CircuitPlayground.setPixelColor(1, 0, 0, 0);
    }


  }




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

int clamp_servo_range(int rot){
  int clamped_rot = max( SERVO_MIN, min( SERVO_MAX, rot));
  Serial.println(clamped_rot);

  return clamped_rot;
}
