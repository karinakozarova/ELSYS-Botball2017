#include <kipr/botball.h>

#define MOTOR_PORT_1 2
#define MOTOR_PORT_2 3
#define MOTOR_MOVE_SPEED 750
#define SERVO_MOVE_DISTANCE 1000
#define SERVO_MOVE_DELAY 500
#define SERVO_WAVE_COUNT 10
#define SERVO_PORT 0
#define REFLECTION_SENSOR_PORT 0

#define BLACK_LINE_VALUE 900

void move(int speed_left, int speed_right, int duration){
    mav(MOTOR_PORT_1, speed_right);
    mav(MOTOR_PORT_2, speed_left);
  	msleep(duration);
  	ao();
}
/*
//Not used function
void move_servo(int position, int delay){
  	enable_servos();
  	set_servo_position(SERVO_PORT, position);
  	msleep(delay);
  	disable_servos();
} 
*/

int main()
{
  	int rotate_time = 50;
  
  	while(1){
        while(analog(REFLECTION_SENSOR_PORT) > BLACK_LINE_VALUE){
             move(700, 700, rotate_time);
        }
      
      	int total_rotation_time = 0;
      
      	while(analog(REFLECTION_SENSOR_PORT) < BLACK_LINE_VALUE && total_rotation_time < 4000){
      		move(700, 0, rotate_time);
          	total_rotation_time += rotate_time;
        }
      
      	while(analog(REFLECTION_SENSOR_PORT) < BLACK_LINE_VALUE){
      		move(0, 700, rotate_time);
        }
    }
  
  	ao();
    return 0;
}
