#include <stdio.h>
#include <webots/motor.h>
#include <webots/robot.h>
#include <webots/touch_sensor.h>

#define SPEED 4
#define TIME_STEP 64

int main() {
  WbDeviceTag bumper;
  WbDeviceTag left_motor, right_motor;
  int movement_counter = 0;
  int left_speed, right_speed;
  int bump=0; /* 0 for right, 1 for left*/
  
  wb_robot_init();
  bumper = wb_robot_get_device("bumper");
  wb_touch_sensor_enable(bumper, TIME_STEP);

  left_motor = wb_robot_get_device("left wheel motor");
  right_motor = wb_robot_get_device("right wheel motor");
  wb_motor_set_position(left_motor, INFINITY);
  wb_motor_set_position(right_motor, INFINITY);
  wb_motor_set_velocity(left_motor, 0.0);
  wb_motor_set_velocity(right_motor, 0.0);

  /* control loop */
  while (wb_robot_step(TIME_STEP) != -1) {
    
    if (bump % 2 ==0)
    {
    if (wb_touch_sensor_get_value(bumper) > 0)
    {
      bump = bump + 1;
      movement_counter = 30;
    }
    if (movement_counter == 0) {
      left_speed = SPEED;
      right_speed = SPEED;
    } else if (movement_counter >= 17) {
      left_speed = -SPEED;
      right_speed = -SPEED;
      movement_counter--;
    } else {
      left_speed = -SPEED / 2;
      right_speed = SPEED;
      movement_counter--;
    }
    }
    else
    {
    if (wb_touch_sensor_get_value(bumper) > 0)
    {
      bump = bump + 1;
      movement_counter = 30;
    }
    if (movement_counter == 0) {
      left_speed = SPEED;
      right_speed = SPEED;

    } else if (movement_counter >= 17) {
      left_speed = -SPEED;
      right_speed = -SPEED;
      movement_counter--;
    } else {
      left_speed = SPEED ;
      right_speed = -SPEED/2;
      movement_counter--;
    }
    }
    printf("\n bumper value %d: \n", bump);
    wb_motor_set_velocity(left_motor, left_speed);
    wb_motor_set_velocity(right_motor, right_speed);
  }
  
  wb_robot_cleanup();

  return 0;
}