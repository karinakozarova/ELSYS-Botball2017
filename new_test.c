// tuka ima podobreni functions za dvijenie na robota, no vse oshte ne sa implementirani v test

#include <kipr/botball.h>
//SENSOR PORTS:
#define LIGHT_SENSOR 0 // light sensor
#define LINE_SENSOR_PORT 5 // line sensor (tophat)
#define Button_Port 1 //clickable button
#define INFRARED_PORT 4 // infrared sensor


//MOTOR PORTS:
#define LEFT_WHEEL_PORT 3 //motor 1 
#define RIGHT_WHEEL_PORT 0 //motor 2

//SERVO PORTS:
#define CLIPPER_UP_DOWN_PORT 1 //servo 1

//CONSTS
#define BLACKLINE_MAX 1500 //blackline velocity
#define BLACKLINE_MIN 500 //blackline velocity
#define CLIPPERS_MAX 2000
#define CLIPPERS_NULL 400

#define WHEEL_CIRCUMFERANCE 175.8 // in mm
#define DISTANCE_BETWEEN_WHEELS 120.0 // in mm

//function declaration
void drive_revolutions_forward(int velocity, float revolutions);
void drive_revolutions_backward(int velocity, float revolutions);
void drive_distance_forward(int velocity, int distance);
void drive_distance_backward(int velocity, int distance);
void turn_left(int velocity, int degrees);
void turn_right(int velocity, int degrees);
void light_sensor(int LIGHT_SENSOR_PORT);       
void follow_black_line();
void initial_positions();
void clippers_up(int servo_value);
void clippers_down(int servo_value);
void clippers_open(int speed, float revolutions);
void clippers_close(int speed, float revolutions);

void grab_water_container();
void drive(int velocity, int port, float revolutions);

/*
	CLIPPER_OPEN_CLOSE_SERVO value:
	min: 0;
    max: 800;
*/

int main()
{  
    //light_sensor(LIGHT_SENSOR_PORT ); //add this when not testing
	/*
  	drive_revolutions_forward(1000, 2.0);
  	msleep(3000);
  	drive_revolutions_backward(1000, 2.0);
 	*/
  	/*
 	drive_distance_forward(1000, 200);
    msleep(3000);
  	drive_distance_backward(1000, 200);
  	*/
  	/*
  	turn_left(1000, 90);
  	msleep(3000);
  	turn_right(1000, 180);
  	msleep(3000);
  	turn_left(1000, 270);
  	*/
  	initial_positions(); // setup servos
  	clippers_up(1000);
  	//clippers_close(500, 0.2);
  	msleep(2000);
  	while(!digital(1)) //infinite loop
	{
		follow_black_line();
      	if(gyro_y() < -250) {  //when on ramp
          clippers_up(1250);
        }
      	
    }
  
  	//drive(-500, 0, 0.2);
  	//grab_water_container();
  	ao();
  	clippers_down(500);
  	return 0;
}

void initial_positions()
{ 
  	// null positions for servos
  	//clippers_close(250); // change this in the future to 100/50
	clippers_up(600);
  	enable_servos();
}

void drive(int velocity, int port, float revolutions) {
 	cmpc(port);
  	if(velocity > 0) {
    	while(gmpc(port) < 1400 * revolutions) {
     		mav(port, velocity);
      		msleep(5);
    	}
    }
 	else {
    	while(gmpc(port) > -1400 * revolutions) {
     		mav(port, velocity);
      		msleep(5);
    	}
    }
  	ao();
}

void drive_revolutions_forward(int velocity, float revolutions)
{
  	/*
  		velocity: ticks/sec; note: velocity > 0

  		1 revolution = 1400 ticks
  		1 revolution = 175.8 mm (WHEEL_CIRCUMFERANCE)
  	*/
  	cmpc(LEFT_WHEEL_PORT);
  	cmpc(RIGHT_WHEEL_PORT);
  
  	while(gmpc(LEFT_WHEEL_PORT) < 1400 * revolutions) {
    	mav(RIGHT_WHEEL_PORT, velocity); // power right motor at 100%
  		
     	if(gmpc(LEFT_WHEEL_PORT) < gmpc(RIGHT_WHEEL_PORT)) {
   		     // left motor is slower -> power left motor at 125%
    	     mav(LEFT_WHEEL_PORT, 125 * velocity / 100);
  	    }
      	else if(gmpc(LEFT_WHEEL_PORT) > gmpc(RIGHT_WHEEL_PORT)) {
        	// right motor is slower -> power left motor at 75%
         	mav(LEFT_WHEEL_PORT, 75 * velocity / 100);
      	}
      	else {
        	// power both motors at 100% velocity
       		mav(LEFT_WHEEL_PORT, velocity);
      	}
    }
  	ao();
}

void drive_revolutions_backward(int velocity, float revolutions)
{
  	/*
  		velocity: ticks/sec; note: velocity > 0

  		1 revolution = 1400 ticks
  		1 revolution = 175.8 mm (WHEEL_CIRCUMFERANCE)
  	*/
  	cmpc(LEFT_WHEEL_PORT);
  	cmpc(RIGHT_WHEEL_PORT);
  
  	while(gmpc(LEFT_WHEEL_PORT) > -1400 * revolutions) {
    	mav(RIGHT_WHEEL_PORT, -velocity); // power right motor at 100%
  		
     	if(gmpc(LEFT_WHEEL_PORT) > gmpc(RIGHT_WHEEL_PORT)) {
   		     // left motor is slower -> power left motor at 125%
    	     mav(LEFT_WHEEL_PORT, 125 * -velocity / 100);
  	    }
      	else if(gmpc(LEFT_WHEEL_PORT) < gmpc(RIGHT_WHEEL_PORT)) {
        	// right motor is slower -> power left motor at 75%
         	mav(LEFT_WHEEL_PORT, 75 * -velocity / 100);
      	}
      	else {
        	// power both motors at 100% velocity
       		mav(LEFT_WHEEL_PORT, -velocity);
      	}
    }
  	ao();
}


void drive_distance_forward(int velocity, int distance) {
	/*
  		velocity: ticks/sec; note: velocity > 0
  		distance: mm

  		1 revolution = 1400 ticks
  		1 revolution = 175.8 mm
  	*/
  	float revolutions = distance / WHEEL_CIRCUMFERANCE;
  	drive_revolutions_forward(velocity, revolutions);
}

void drive_distance_backward(int velocity, int distance) {
	/*
  		velocity: ticks/sec; note: velocity > 0
  		distance: mm

  		1 revolution = 1400 ticks
  		1 revolution = 175.8 mm
  	*/
  	float revolutions = distance / WHEEL_CIRCUMFERANCE;
  	drive_revolutions_backward(velocity, revolutions);
}


void turn_left(int velocity, int degrees) {
	float distance = (3.14 * DISTANCE_BETWEEN_WHEELS) / (360 / degrees);
  	float revolutions = distance / WHEEL_CIRCUMFERANCE;
  
  	cmpc(LEFT_WHEEL_PORT);
  	while(gmpc(LEFT_WHEEL_PORT) > -1400 * revolutions) {
    	mav(RIGHT_WHEEL_PORT, velocity);
		mav(LEFT_WHEEL_PORT, -velocity);
  		msleep(5);	
    }
  	ao();
}


void turn_right(int velocity, int degrees) {
	float distance = (3.14 * DISTANCE_BETWEEN_WHEELS) / (360 / degrees);
  	float revolutions = distance / WHEEL_CIRCUMFERANCE;
  
  	cmpc(RIGHT_WHEEL_PORT);
  	while(gmpc(RIGHT_WHEEL_PORT) > -1400 * revolutions) {
    	mav(RIGHT_WHEEL_PORT, -velocity);
		mav(LEFT_WHEEL_PORT, velocity);
  		msleep(5);	
    }
  	ao();
}

void light_sensor(int LIGHT_SENSOR_PORT ){
	//Waits for light to be callibrated, starts the robot and shuts down in 119
	wait_for_light(LIGHT_SENSOR_PORT );
	printf("Start!");
	shut_down_in(119);
}

void follow_black_line(){
	  if(analog(LINE_SENSOR_PORT) < 3000) { 
	    mav(RIGHT_WHEEL_PORT, BLACKLINE_MIN);
	    mav(LEFT_WHEEL_PORT, BLACKLINE_MAX);
   	    //printf("Detected white line...\n");
	  }
	  else
	  {
	    mav(RIGHT_WHEEL_PORT, BLACKLINE_MAX);
	    mav(LEFT_WHEEL_PORT, BLACKLINE_MIN);
	    //printf("Black line...\n");
	  }
}


void clippers_up(int servo_value)
{
	set_servo_position(CLIPPER_UP_DOWN_PORT, servo_value);
}

void clippers_down(int servo_value)
{	
  	int x=get_servo_position(CLIPPER_UP_DOWN_PORT);
  	//set_servo_position(CLIPPER_UP_DOWN_PORT, CLIPPERS_MAX);
    msleep(200);
  	while(get_servo_position(CLIPPER_UP_DOWN_PORT) > servo_value) {
		set_servo_position( CLIPPER_UP_DOWN_PORT, x);
  		msleep(5);
      	x-=5;
    }
  	msleep(100);
}

void clippers_open(int speed, float revolutions){
  	printf("Opening clippers...\n");
 	drive(-speed, 1, revolutions);
}

void clippers_close(int speed, float revolutions){
  	printf("Closing clippers...\n");
 	drive(speed, 1, revolutions);
}
/*
void grab_water_container()
{
  
  	// NOTE: distances should be adjusted slghtly
  	while(analog(LINE_SENSOR_PORT) < 3000)
	{
		drive_revolutions_forward(1000, 0.1);
    }
	turn_right(1000, 90);
	drive_distance_backward(1500, 350);  // bump into the tube
  	clippers_up(750);
  	
  	// drive to the water container
	drive_distance_forward(1500, 400);  // drive past the fertilizer hopper
  	while(analog(INFRARED_PORT) < 400) // drive until water container tube is detected
	{
     	drive_revolutions_forward(1500, 0.1);
    }
  	turn_left(1000, 90);
  	
  	// prepare to grab the water container
	clippers_up(CLIPPERS_MAX);
  	msleep(1500);	
  	clippers_open(800);
  	
  	// grab water container
	drive_distance_forward(500, 210); // ~ 21 - 22 cm
  	msleep(1500);
  	clippers_close(200);
 	msleep(1500);
  	drive_distance_backward(1000, 210); // ~ 21 - 22 cm
  	clippers_down(CLIPPERS_NULL);
  	msleep(1500);
  	
  	// adjust the water container
  	clippers_open(350);
  	msleep(500);
  	clippers_close(200);
  	msleep(500);
  	clippers_up(900);
  	msleep(1000);
  	
  	// return to base
  	turn_right(1000, 90);
  	drive_distance_backward(1000, 200); // drive past the water container tube
  	while(analog(LINE_SENSOR_PORT) < 3000)
	{
		drive_revolutions_backward(1500, 0.1);
    }
	drive_distance_backward(1000, 150);
  	
  	// get in position to go up the ramp
  	turn_left(1000, 90);
  	clippers_up(1400);
  	drive_distance_backward(1500, 560); // bump into the tube
  	drive_distance_forward(500, 50);
  	while(analog(INFRARED_PORT) < 100) // detect fertilizer hopper
	{
		turn_right(500, 5);
    }
  	/*
  	// follow the black line
  	while(analog(LINE_SENSOR_PORT) > 3000)
    {
      drive(500, 20);
    }
  	clippers_down(900);
  
}
*/
