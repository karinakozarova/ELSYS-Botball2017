#include <kipr/botball.h>
//SENSOR PORTS:
#define LIGHT_SENSOR 0	          //light sensor
#define LINE_SENSOR_PORT 5        //line sensor (tophat)
#define Button_Port 1				//button on clipper

//MOTOR PORTS:
#define LEFT_WHEEL_PORT 3	      //motor 1 
#define RIGHT_WHEEL_PORT 0	     //motor 2

//SERVO PORTS:
#define CLIPPER_UP_DOWN_PORT 1	    //servo 1
#define CLIPPER_OPEN_CLOSE_PORT 0  //servo 2

//CONSTS
#define BLACKLINE_MAX 1500	//blackline velocity
#define BLACKLINE_MIN 500	//blackline velocity
#define CLIPPERS_MAX 1800
#define CLIPPERS_MIN 240

//function declaration
void light_sensor(int LIGHT_SENSOR_PORT );       
void follow_black_line();
void initial_positions();
void clippers_up();
void clippers_down();
void clippers_open();
void clippers_close();
void clippers_starting_position();
void button_reading();
void backward_movement_3s();
void forward_movement_3s();


/* -------------------------------------------------------------------------------
		Used ports:
			Sensors:
				button = 1 port
				light sensor = 0 port
				line_sensor = 5 port
				
			Motors(wheels):
				left_wheel = 3 port (gore red, dolu black)
				right_wheel = 0 port (gore black, dolu red)
				
			Servos(on clippers) :
				up-down = 1 port
				open-close = 0 port
-------------------------------------------------------------------------------*/

int main()
{
    	
	  light_sensor(LIGHT_SENSOR_PORT ); //add this when not testing   
	  initial_positions();
	  clippers_starting_position();
	  wait_for_milliseconds(3000);
	  clippers_open();	
	  wait_for_milliseconds(2000);
	  clippers_close();
	  wait_for_milliseconds(2000);
	  clippers_down();
  
		/*	
					 wait_for_milliseconds(1000);
						clippers_close();
						 clippers_open();	

					 // clippers_up();
						while(1) //infinite loop
						{
							//follow_black_line();
						//  button_reading();
						}
		*/ 
   
   return 0;
}

void light_sensor(int LIGHT_SENSOR_PORT ){
	//Waits for light to be callibrated, starts the robot and shuts down in 119
	wait_for_light(LIGHT_SENSOR_PORT );
	printf("Start!");
	shut_down_in(119);
}

void follow_black_line(){
	//follows black line using the top hat sensor
	  if(analog(LINE_SENSOR_PORT) < 3000) { 
	    mav(RIGHT_WHEEL_PORT,BLACKLINE_MIN);
	    mav(LEFT_WHEEL_PORT,BLACKLINE_MAX);
   	    printf("Detected white line...\n");
	  }
	  else
	  {
	    mav(RIGHT_WHEEL_PORT,BLACKLINE_MAX);
	    mav(LEFT_WHEEL_PORT, BLACKLINE_MIN);
	    printf("Black line...\n");
	  }
}

void initial_positions()
{ 
   // null position;
	set_servo_position(0, 268);
	set_servo_position(1, 400);
 	enable_servos();
}

void clippers_up()
{
    //moves clippers up
	printf("Up\n");
	set_servo_position( CLIPPER_UP_DOWN_PORT, CLIPPERS_MAX);
 	enable_servos();
}

void clippers_down()
{
    //moves clippers down
	printf("Down\n");
	set_servo_position( CLIPPER_UP_DOWN_PORT, CLIPPERS_MIN);
 	enable_servos();
}

void clippers_open(){
     //opens clippers
        printf("Open\n");
	set_servo_position(CLIPPER_OPEN_CLOSE_PORT, 500);
 	enable_servos();
}

void clippers_close(){
	//closes clippers
  	printf("Close\n");
	set_servo_position(CLIPPER_OPEN_CLOSE_PORT, 0);
 	enable_servos();
}

void clippers_starting_position(){
	//how the clipper should be while going up the ramp
	set_servo_position(CLIPPER_UP_DOWN_PORT, CLIPPERS_MIN);
	set_servo_position(CLIPPER_OPEN_CLOSE_PORT, 268);	
	set_servo_position(CLIPPER_UP_DOWN_PORT, 700);
 	enable_servos();
}

void button_reading(){
  //TO BE TESTED!!!!
  if(!digital(Button_Port))  //button is triggered
  {
      	printf("In");
        backward_movement_3s();
        clippers_up();
        follow_black_line();
        clippers_open();
  }
  else follow_black_line();
  
}
  
void backward_movement_3s(){
  	//moves backward for 3 seconds
	int i;	
  	for(i=0;i<800;i++) 
   	 {
    	        mav(3,-2500);
  	 	mav(0,-2500);
  	  }
    	ao();
  }

  void forward_movement_3s(){
  	//moves forward for 3 seconds
	int i;	
  	for(i=0;i<800;i++) 
   	 {
    		mav(3,2500);
  	 	mav(0,2500);
  	  }
    	ao();
  }
