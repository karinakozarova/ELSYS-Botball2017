#include <kipr/botball.h>
//SENSOR PORTS:
#define LIGHT_SENSOR 0 // light sensor
#define LINE_SENSOR_PORT 5 // line sensor (tophat)
#define BUTTON_PORT 1 //clickable button
#define INFRARED_PORT 4 // infrared sensor

//MOTOR PORTS:
#define LEFT_WHEEL_PORT 3 //motor 1 
#define RIGHT_WHEEL_PORT 0 //motor 2

//SERVO PORTS:
#define CLIPPER_UP_DOWN_PORT 1 //servo 1
#define CLIPPERS_OPEN_CLOSE_PORT 2 //servo 2

//CONSTS
#define BLACKLINE_MAX 1500 //blackline velocity
#define BLACKLINE_MIN 500 //blackline velocity
#define CLIPPERS_MAX 1550
#define CLIPPERS_NULL 50

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
void clippers_open(int servo_value);
void clippers_close(int servo_value);
void grab_water_container();
void blue_ball_leave();
void pick_up_pink_poms();


/*
	CLIPPERS_OPEN_CLOSE_SERVO:
   	port 2;
    values:
    	min: 0; - closed;
       	max: 1000; - opened;
*/

int main()
{  
    //light_sensor(LIGHT_SENSOR_PORT ); //add this when not testing
	/*
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
  	*/
  	initial_positions();
  	//grab_water_container();
	blue_ball_leave();
	pick_up_pink_poms();

  
  	/*
  	while(!digital(1)) {
      	printf("%d\n", analog(4));
      	msleep(500);
    }*/
    ao();
  	clippers_down(100);
  	
    return 0;
}

void initial_positions()
{ 
  	// null positions for servos
  	clippers_close(0);
  	clippers_up(150);
  	enable_servos();
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


void clippers_open(int servo_value)
{
  	int x=get_servo_position(CLIPPERS_OPEN_CLOSE_PORT);
  	//set_servo_position(CLIPPER_UP_DOWN_PORT, CLIPPERS_MAX);
    msleep(200);
  	while(get_servo_position(CLIPPERS_OPEN_CLOSE_PORT) < servo_value) {
		set_servo_position(CLIPPERS_OPEN_CLOSE_PORT, x);
  		msleep(5);
      	x+=5;
    }
  	msleep(100);
  
  	//set_servo_position(CLIPPERS_OPEN_CLOSE_PORT, servo_value);
}

void clippers_close(int servo_value)
{  
 	set_servo_position(CLIPPERS_OPEN_CLOSE_PORT, servo_value); 
}

void grab_water_container()
{
 	while(analog(LINE_SENSOR_PORT) < 3000)
	{
		drive_revolutions_forward(1000, 0.1);
    }
  	while(analog(INFRARED_PORT) < 500)
    	turn_right(1000, 5);
	drive_distance_backward(1500, 400);  // bump into the tube
    
  	clippers_up(300);
  	msleep(2500);
  	
  	// drive to the water container
	drive_distance_forward(1500, 400);  // drive past the fertilizer hopper
  	while(analog(INFRARED_PORT) < 300) // drive until water container tube is detected
	{
     	drive_revolutions_forward(1500, 0.1);
    }
  	while(analog(INFRARED_PORT) > 300) // drive past the water container tube
	{
     	drive_revolutions_forward(1500, 0.1);
    }
  	drive_distance_forward(1000, 50);
  	ao();
  	msleep(500);
  	clippers_up(CLIPPERS_MAX);
  	msleep(2000);
	turn_left(1000, 93);
  	
  	// grab water container
  
	clippers_open(1000);
  	drive_distance_forward(1000, 280); // ~ 27 - 28 cm
  	msleep(1500);
  	clippers_close(100);
  	msleep(1500);
  	drive_distance_backward(740, 270); // ~ 27 - 28 cm
  	ao();
  	msleep(250);
  	// return to the base
  	drive_distance_forward(1000, 28);
    ao();
    msleep(500);
    while(analog(INFRARED_PORT) < 300)
  		turn_right(1000, 5);
   while(analog(INFRARED_PORT) > 300)
  		turn_right(1000, 5);
    turn_left(500, 5);
    msleep(1000);
	/*
  	// adjust the water container
  	clippers_down(CLIPPERS_NULL);
  	msleep(1500);
  	clippers_open(300);
  	msleep(500);
  	clippers_close(150);
  	msleep(500);
  	clippers_up(CLIPPERS_MAX);
  	msleep(2500);
  	*/
 
  	while(analog(LINE_SENSOR_PORT) < 3000)
	{
		drive_revolutions_backward(1500, 0.1);
    }
	drive_distance_backward(1000, 20);
  
    msleep(500);
  	drive_distance_forward(1000,30);
  	// get in position to go up the ramp
  	turn_left(1000, 105);
  	drive_distance_backward(1500, 560); // bump into the tube
  	drive_distance_forward(500, 140);
  	msleep(500);
    turn_right(500, 86);
  	drive_distance_backward(1000,400);
  	drive_distance_forward(1000,420);
  	
    
}
void blue_ball_leave(){
		clippers_down(560);
  		msleep(1500);
  		drive_distance_forward(1000,150);
		while(!digital(1)) //infinite loop
		{
            follow_black_line();
			if(gyro_y() < -250)
            {  //when on ramp
                  drive_distance_forward(1000,50);
                  clippers_up(950);
            }
        }
        drive_distance_backward(1000,30);
        clippers_up(1400);
  		msleep(2500);
        drive_distance_forward(1000,210);
        turn_left(1000,10);
        while(analog(LINE_SENSOR_PORT) < 3000)
        {
            turn_right(500, 5);
        }
  		turn_right(500,15);
  		msleep(1500);
   		clippers_open(500);
}


void pick_up_pink_poms()
{
  		//move back
  		drive_distance_backward(1000,10);
  		turn_left(1000, 5);
  		while(analog(LINE_SENSOR_PORT) > 3000)
            turn_left(1000, 5);
  		//turn_left(1000, 5);
  			
 		clippers_open(1000);
  		drive_distance_backward(1500, 200);
  		clippers_down(100);
 		msleep(1500);
  		drive_distance_forward(1500, 20);
  			
  		clippers_close(100);
  		msleep(500);
  		drive_distance_backward(1000, 70);
 		clippers_up(950);
  		msleep(2000);
  		
  		while(analog(LINE_SENSOR_PORT) < 3000)
          	turn_left(500, 5);
  		drive_distance_backward(1000, 100);
  
  		// code from above function
  		while(!digital(1)) //infinite loop
		{
           	follow_black_line();
		}
        drive_distance_backward(1000,30);
        clippers_up(1400);
  		msleep(2500);
        drive_distance_forward(1000,210);
        turn_left(1000,10);
        while(analog(LINE_SENSOR_PORT) < 3000)
        {
            turn_right(500, 5);
        }
  		turn_right(500,15);
  		msleep(1500);
   		clippers_open(500);
}
