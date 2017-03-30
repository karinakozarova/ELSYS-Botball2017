#include <kipr/botball.h>

#define LIGHT_SENSOR 1	//light sensor
#define LINE_SENSOR_PORT 5	//line sensor (tophat)
#define ANALOG_ET_SENSOR_PORT 0	//distance sensor

#define LEFT_WHEEL_PORT 3	//motor 1 
#define RIGHT_WHEEL_PORT 0	//motor 2
#define CLIPPER_UP_DOWN_PORT 0	//servo 1
#define CLIPPER_OPEN_CLOSE_PORT 1 //servo 2

#define BLACKLINE_MAX 3000	//blackline velocity
#define BLACKLINE_MIN 500	//blackline velocity

void light_sensor(int LIGHT_SENSOR_PORT );       
void follow_black_line();
void near_cup();
void bring_servo_up();
void bring_servo_down();
void open_clippers();
void close_clippers();

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
–-------------------------------------------------------------------------------*/

int main()
{
    //light_sensor(LIGHT_SENSOR_PORT ); //add this when not testing
    while(1) //infinite loop
	{
	   near_cup();
       wait_for_milliseconds(20);  //adds 20ms delay
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

	  if(analog(LINE_SENSOR_PORT) < 2000) { 
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

void near_cup(){
	analog_et(ANALOG_ET_SENSOR_PORT); //get a reading
	while(1)	//infinite loop
	{
		if(analog10(ANALOG_ET_SENSOR_PORT) > 512) //is close
		{
			ao();	//stops motors
			close_clippers();
			bring_servo_up();
		}
		else follow_black_line();	
	}
}

void bring_servo_up(){
	enable_servos();
	//TO DO: write the real code,this probably won't work
	//WARNING! where it's 2013 maybe it should be 0
	set_servo_position(CLIPPER_UP_DOWN_PORT,2013);   //(port,angle)
	disable_servos();

}
void bring_servo_down(){
	enable_servos();
	//TO DO: write the real code
	set_servo_position(CLIPPER_UP_DOWN_PORT,0);
	disable_servos();
}

void close_clippers(){
	enable_servos();
	//TO DO: write the real code
	set_servo_position(CLIPPER_OPEN_CLOSE_PORT,0);
	disable_servos();
}

void open_clippers(){
	enable_servos();
	//TO DO: write the real code
	set_servo_position(CLIPPER_OPEN_CLOSE_PORT,1000);
	disable_servos();
}
