#include <kipr/botball.h>
//SENSOR PORTS:
#define LIGHT_SENSOR 0	             //light sensor
#define LINE_SENSOR_PORT 5          //line sensor (tophat)
#define Button_Port 1			   //clickable button
#define INFRARED_PORT 4			  // infrared sensor


//MOTOR PORTS:
#define LEFT_WHEEL_PORT 3	      //motor 1 
#define RIGHT_WHEEL_PORT 0	     //motor 2

//SERVO PORTS:
#define CLIPPER_UP_DOWN_PORT 1	    //servo 1
#define CLIPPER_OPEN_CLOSE_PORT 0  //servo 2

//CONSTS
#define BLACKLINE_MAX 1500	 //blackline velocity
#define BLACKLINE_MIN 500	//blackline velocity
#define CLIPPERS_MAX 2000
#define CLIPPERS_NULL 400

#define WHEEL_CIRCUMFERANCE 175.8 // in mm

//function declaration
void drive(int velocity, int time);
void drive_distance_forward(int velocity, int distance);
void drive_distance_backward(int velocity, int distance);
void turn_90_degrees(int velocity, int time);
void light_sensor(int LIGHT_SENSOR_PORT);       
void follow_black_line();
void follow_black_line_backwards();
void initial_positions();
void clippers_up(int servo_value);
void clippers_down(int servo_value);
void clippers_open(int servo_value);
void clippers_close(int servo_value);
void backward_movement_3s();

/*
	CLIPPER_OPEN_CLOSE_SERVO value:
	min: 0;
    max: 800;
*/

int main()
{  
    //light_sensor(LIGHT_SENSOR_PORT ); //add this when not testing
	
  /*
	clippers_up(1200);
  	mav(RIGHT_WHEEL_PORT,700);
	mav(LEFT_WHEEL_PORT,700);
  	msleep(5000);
    clippers_down(700);
  	msleep(1000);
  	while(1) //infinite loop
	{
		follow_black_line();
    //  button_reading();
    }/*/
  	//clippers_up(750);
  	//enable_servos();
  	/*
  	initial_positions(); // setup servos
 
  	while(analog(LINE_SENSOR_PORT) < 3000)
	{
		drive(1000, 50);
    }
	turn_90_degrees(-1000, 950);
	drive(-1500, 2000);  // bump into the tube
  	clippers_up(750);
  
  	// drive to the water container
	drive(1500, 2500);  // drive past the fertilizer hopper
  	while(analog(INFRARED_PORT) < 400)
	{
		drive(1500, 50);
    }
	turn_90_degrees(1000, 900);
  	
  	// prepare to grab the water container
	ao();
  	clippers_up(CLIPPERS_MAX);
  	msleep(1500);	
  	clippers_open(800);
  	
  	// grab water container
	drive(500, 3500);
  	ao();
  	msleep(1500);
  	clippers_close(200);
 	msleep(3000);
  	
  	// return to base
	drive(-500, 1000);
  	drive(-1000, 1500);
	
  	// put the clippers down
  	ao();
  	clippers_down(CLIPPERS_NULL);
  	msleep(2000);
  	
  	// grab the water container
  	clippers_open(350);
  	msleep(500);
  	clippers_close(200);
  	msleep(500);
  
  	clippers_up(900);
  	msleep(1500);
  	
  	turn_90_degrees(-1000, 950);
  	drive(-1000, 1500);
  	while(analog(LINE_SENSOR_PORT) < 3000)
	{
		drive(-1500, 50);
    }
	drive(-1000, 500);
  
  	turn_90_degrees(-1000, 1050);
  	clippers_up(1400);
  	drive(1500, 3000); // bump into the tube with the front
  	drive(-500, 2500);
  	while(analog(INFRARED_PORT) < 100) // detect fertilizer hopper
	{
		turn_90_degrees(500, 5);
    }
  	
  
  	//turn_90_degrees(1000, 1800);
  	//turn_90_degrees(1000, 900);
  
  	// follow the black line
  	while(analog(LINE_SENSOR_PORT) > 3000)
    {
      drive(500, 20);
    }
  	clippers_down(900); */

  	initial_positions();
  	clippers_open(300);
 	clippers_up(950); 
    msleep(1500);
  	
  	while(analog(LINE_SENSOR_PORT) < 3000)
    {
      drive(500, 20);
    }
  	
    while(!digital(1)) //infinite loop
	{
		follow_black_line();
      	if(gyro_y() < -250) {  //when on ramp
          clippers_up(1500);
        }
      	
    }
  	printf("Button clicked");	//is near the cup
  	drive(-500,250);  //goes backward
  	// put the water container
  	clippers_down(1200);
  	msleep(1000);	
  	drive(500, 2000);
  	ao();
  	msleep(2000);
  	clippers_open(700);
	
  	drive_distance_backward(-1000, 300);
  	msleep(1000);
  	ao();
  	clippers_open(800);
  	// pick up the pink poms
  	clippers_down(400);
  	msleep(1000);
  	drive_distance_forward(1000, 300);
  	clippers_close(100);
  	drive(-500, 2000);
  	clippers_up(2000);
  	ao();
  	msleep(300000);
  //drive(500,2000);
 
 /* //moves in circle
  	while(analog(LINE_SENSOR_PORT) < 3000) {
  		turn_90_degrees(-500, 20);  
    }
  	while(analog(LINE_SENSOR_PORT) > 3000) {
  		turn_90_degrees(-500, 20);  
    }*/
  
     //drive(-500, 4000);
     //clippers_open(700);
  	

      /*
  	drive(-500, 2000);
	turn_90_degrees(1000, 950);
	
	while(analog(LINE_SENSOR_PORT) < 3000)
	{
		drive(1000, 50);
    }
	turn_90_degrees(1000, 1800); // 180 degrees turn
  	
  	// put clippers down
  	ao();
  	clippers_down(1000);
  	msleep(3000);
  	
  	drive(-1500, 3500); // bump into the tube
	
  	// get in position to climb up the ramp
  	turn_90_degrees(1000, 950);
  	drive(-1500, 2500); // bump into the tube
	turn_90_degrees(-1000, 950);
  	drive(-1500, 2000); // bump into the tube
	*/
  	// always include this at the end... ALWAYS...
  	ao();
  	clippers_down(80); 
  	msleep(3000);
  	return 0;
}
/*
	//gyro sensor test
    
  	initial_positions();
  	clippers_up(900);
  	msleep(2000);
  	while(gyro_y() > -200) {
    	follow_black_line();
    }
  	drive(1000, 1000);
*/
void initial_positions()
{ 
  	// null positions for servos
  	clippers_close(250); // change this in the future to 100/50
	clippers_up(600);
  	enable_servos();
}

void drive(int velocity, int time)
{
	mav(RIGHT_WHEEL_PORT, velocity);
	mav(LEFT_WHEEL_PORT, velocity);
  	msleep(time);
}

void drive_distance_forward(int velocity, int distance) {
	// velocity: ticks/sec
  	// distance: mm

  	// 1 revolution = 1400 ticks
  	// 1 revolution = 175.8 mm
  	cmpc(0);
  	float ticks = 1400 * (distance / WHEEL_CIRCUMFERANCE);
  	while(gmpc(0) < ticks) {
      	//printf("\n%d", gmpc(0)); // debugging
    	drive(velocity, 5);
	}
}

void drive_distance_backward(int velocity, int distance) {
	// velocity: ticks/sec
  	// distance: mm

  	// 1 revolution = 1400 ticks
  	// 1 revolution = 175.8 mm
  	cmpc(0);
  	float ticks = -(1400 * (distance / WHEEL_CIRCUMFERANCE));
  	while(gmpc(0) > ticks) {
      	//printf("\n%d", gmpc(0)); // debugging
    	drive(velocity, 5);
	}
}


void turn_90_degrees(int velocity, int time)
{
	// To turn left pass a positive value for velocity, to turn right - negative
	mav(RIGHT_WHEEL_PORT, velocity);
	mav(LEFT_WHEEL_PORT, -velocity);
  	msleep(time);
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

void clippers_open(int servo_value){
  	printf("Opening clippers...\n");
	set_servo_position(CLIPPER_OPEN_CLOSE_PORT, servo_value);
}

void clippers_close(int servo_value){
  	printf("Closing clippers...\n");
	set_servo_position(CLIPPER_OPEN_CLOSE_PORT, servo_value);
}

void backward_movement_3s(){
  	int i;	
  	for(i=0;i<800;i++) 
    {
    	mav(3,-2500);
  	 	mav(0,-2500);
    }
    ao();
}
