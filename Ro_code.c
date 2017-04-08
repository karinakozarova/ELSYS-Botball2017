#include <kipr/botball.h>
//SENSOR PORTS:
#define LIGHT_SENSOR 1	          //light sensor
#define LINE_SENSOR_PORT 5	 //line sensor (tophat)
#define ANALOG_ET_SENSOR_PORT 0	//distance sensor
#define Button_Port 4
//MOTOR PORTS:
#define LEFT_WHEEL_PORT 3	      //motor 1 
#define RIGHT_WHEEL_PORT 0	     //motor 2

//SERVO PORTS:
#define CLIPPER_UP_DOWN_PORT 0	    //servo 1
#define CLIPPER_OPEN_CLOSE_PORT 1  //servo 2

//CONSTS
#define BLACKLINE_MAX 2400	//blackline velocity
#define BLACKLINE_MIN 400	//blackline velocity
#define CLIPPERS_MAX 2000
#define CLIPPERS_NULL 0

//function declaration
void light_sensor(int LIGHT_SENSOR_PORT );       
void follow_black_line();
void follow_black_line_backwards();
void initial_positions();
void clippers_up();
void clippers_down();
void clippers_open();
void clippers_close();
void clippers_starting_position();



/* -------------------------------------------------------------------------------
			Used ports:
				Sensors:
				et_sensor = 0 port
				light sensor = 1 port
				line_sensor = 5 port
				Motors(wheels):
				left_wheel = 3 port (gore red, dolu black)
				right_wheel = 0 port (gore black, dolu red)
				Servos(on clippers) :
				up-down = 0 port
				open-close = 1 port
-------------------------------------------------------------------------------*/

int main()
{
    //light_sensor(LIGHT_SENSOR_PORT ); //add this when not testing
   
    //clippers_close();
    initial_positions();
	clippers_starting_position();

    while(1) //infinite loop
	{
		follow_black_line();
    }
    return 0;
}

void light_sensor(int LIGHT_SENSOR_PORT ){
	//Waits for light to be callibrated, starts the robot and shuts down in 119
	wait_for_light(LIGHT_SENSOR_PORT );
	printf("Start!");
	shut_down_in(119);
}

void follow_black_line(){

	  if(analog(LINE_SENSOR_PORT) < 3000) { 
	    mav(RIGHT_WHEEL_PORT,BLACKLINE_MAX);
	    mav(LEFT_WHEEL_PORT,BLACKLINE_MIN);
   	    printf("Detected white line...\n");
	  }
	  else
	  {
	    mav(RIGHT_WHEEL_PORT,BLACKLINE_MIN);
	    mav(LEFT_WHEEL_PORT, BLACKLINE_MAX);
	    printf("Black line...\n");
	  }
}

void initial_positions()
{
	set_servo_position(0, 0);
	set_servo_position(1, 200);
 	enable_servos();
}

void clippers_up()
{
	set_servo_position( CLIPPER_UP_DOWN_PORT, CLIPPERS_MAX);
 	enable_servos();
}

void clippers_down()
{
	set_servo_position( CLIPPER_UP_DOWN_PORT, CLIPPERS_NULL);
 	enable_servos();
}

void clippers_open(){
	set_servo_position(CLIPPER_OPEN_CLOSE_PORT, CLIPPERS_MAX);
 	enable_servos();
}

void clippers_close(){
	set_servo_position(CLIPPER_OPEN_CLOSE_PORT, CLIPPERS_NULL);
 	enable_servos();
}

void clippers_starting_position(){
	set_servo_position(CLIPPER_UP_DOWN_PORT, CLIPPERS_NULL);
	set_servo_position(CLIPPER_OPEN_CLOSE_PORT, 300);	
	set_servo_position(CLIPPER_UP_DOWN_PORT, 800);
 	enable_servos();
}

void follow_black_line_backwards(){
//TO BE TESTED!
	  if(analog(LINE_SENSOR_PORT) < 3000) { 
	    mav(RIGHT_WHEEL_PORT,-BLACKLINE_MAX);
	    mav(LEFT_WHEEL_PORT,-BLACKLINE_MIN);
   	    printf("Detected white line...\n");
	  }
	  else
	  {
	    mav(RIGHT_WHEEL_PORT,-BLACKLINE_MIN);
	    mav(LEFT_WHEEL_PORT, -BLACKLINE_MAX);
	    printf("Black line...\n");
	  }
}

void button_reading(){
  //TO BE TESTED!!!!
  if(digital(Button_Port)){
  //button is triggered
    int i;
 	for(i=0;i<10000;i++) follow_black_line_backwards();
    clippers_up();
    for(i=0;i<10000;i++) follow_black_line();
    clippers_open();
  }
  else{
    //button untouched
  }
}
