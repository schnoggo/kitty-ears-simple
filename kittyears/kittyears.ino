// Circuit Playground Accelerometer Mouse Example
// Tilt Circuit Playground left/right and up/down to move your mouse, and
// press the left and right push buttons to click the mouse buttons!  Make sure
// the slide switch is in the on (+) position to enable the mouse, or slide into
// the off (-) position to disable it.  By default the sketch assumes you hold
// Circuit Playground with the USB cable coming out the top.
// Author: Tony DiCola
// License: MIT License (https://opensource.org/licenses/MIT)
#include <Adafruit_CircuitPlayground.h>
#include <Wire.h>
#include <SPI.h>
#include <Servo.h>



// Configuration values to adjust the sensitivity and speed of the mouse.
// X axis (left/right) configuration:
#define XACCEL_MIN 0.1      // Minimum range of X axis acceleration, values below
                            // this won't move the mouse at all.
#define XACCEL_MAX 8.0      // Maximum range of X axis acceleration, values above
                            // this will move the mouse as fast as possible.
#define XMOUSE_RANGE 25.0   // Range of velocity for mouse movements.  The higher
                            // this value the faster the mouse will move.
#define XMOUSE_SCALE 1      // Scaling value to apply to mouse movement, this is
                            // useful to set to -1 to flip the X axis movement.

// Y axis (up/down) configuration:
// Note that the meaning of these values is exactly the same as the X axis above,
// just applied to the Y axis and up/down mouse movement.  You probably want to
// keep these values the same as for the X axis (which is the default, they just
// read the X axis values but you can override with custom values).
#define YACCEL_MIN XACCEL_MIN
#define YACCEL_MAX XACCEL_MAX
#define YMOUSE_RANGE XMOUSE_RANGE
#define YMOUSE_SCALE 1

// Set this true to flip the mouse X/Y axis with the board X/Y axis (what you want
// if holding with USB cable facing up).
#define FLIP_AXES true


// servo stuff
#define left_servo_pin 10
#define right_servo_pin  6
Servo servoLeft;              // Define left servo
Servo servoRight;             // Define right servo
int angle = 0;






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
  // Check if the slide switch is enabled (on +) and if not then just exit out
  // and run the loop again.  This lets you turn on/off the mouse movement with
  // the slide switch.
  if (!CircuitPlayground.slideSwitch()) {
    return;
  }





  // Grab initial left & right button states to later check if they are pressed
  // or released.  Do this early in the loop so other processing can take some
  // time and the button state change can be detected.
//  boolean left_first = CircuitPlayground.leftButton();
//  boolean right_first = CircuitPlayground.rightButton();

  // Grab x, y acceleration values (in m/s^2).
  float x = CircuitPlayground.motionX();
  float y = CircuitPlayground.motionY();
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
angle = floor(90+(4*x));
  servoLeft.write(angle);
  angle = floor(90-(4*x));
    servoRight.write(angle);



  // Small delay to wait for button state changes and slow down processing a bit.
  delay(20);


}
