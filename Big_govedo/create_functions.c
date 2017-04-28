#ifndef BOTBALL_H
#define BOTBALL_H
#include <kipr/botball.h>
#include "create_functions.h"
#endif

char bales_placed=0;

int create_init()
{
	if(create_connect() == 0)
	{
		enable_servos();
		set_servo_position(LIFT_SERVO, CLAW_HIGH);
		set_servo_position(CLAW_SERVO, CLAW_CLOSED);
		msleep(WAIT_FOR_SERVO);
		wait_for_light(STARTER);
		shut_down_in(119);
		return 0;
	}
	else
	{
		return -1;
	}
}

void create_forward( int time)
{
	create_drive_direct( -300, -300);
	msleep(time);
	create_stop();
}

void create_backward( int time)
{
	create_drive_direct( 300, 300);
	msleep(time);
	create_stop();
}

void create_turn_right()
{
	set_create_total_angle(0);
	while(get_create_total_angle() > -_90_DEGREES)
	{
		create_drive_direct(TURN_SPEED, -TURN_SPEED);
		msleep(5);
	}
	msleep(12);
	create_stop();
}

void create_turn_left()
{
	set_create_total_angle(0);
	while(get_create_total_angle() < _90_DEGREES)
	{
		create_drive_direct(-TURN_SPEED, TURN_SPEED);
		msleep(5);
	}
	msleep(12);
	create_stop();
}

void create_turn_angle(int angle)
{
	set_create_total_angle(0);
	if(angle > 0)
	{
		while(get_create_total_angle() < ((angle/3)*TURN_CORRECTION))
		{
			create_drive_direct(-300, 300);
			msleep(5);
		}
	}
	else
	{
		while(get_create_total_angle() > ((angle/3)*TURN_CORRECTION))
		{
			create_drive_direct(300, -300);
			msleep(5);
		}
	}
	create_stop();
}

void grab_bale()
{
	set_servo_position(LIFT_SERVO, CLAW_MIDDLE);
	msleep(WAIT_FOR_SERVO);
	set_servo_position(LIFT_SERVO, CLAW_LOW);
	msleep(WAIT_FOR_SERVO);
	set_servo_position(CLAW_SERVO, CLAW_CLOSED);
	msleep(WAIT_FOR_SERVO);
	set_servo_position(LIFT_SERVO, CLAW_HIGH);
	msleep(WAIT_FOR_SERVO);
}

void place_bale()
{
	int x=0;
	create_forward(BACK_OFF);
	create_turn_angle(180);
	create_forward((int)(1.8*PIPE_BUMP));		//(int)
	create_backward(BACK_OFF + bales_placed*CLAW_DISPLACEMENT);
	create_turn_right();
	while(analog(LINE_SENSOR) < BLACK)
	{
		create_forward(10);
	}
	create_forward(GET_IN_BARN);
	do
	{
		x=get_servo_position(LIFT_SERVO);
		x+=5;
		set_servo_position(LIFT_SERVO, x);
		msleep(10);
	}
	while(x<release[(int)bales_placed]);
	do
	{
		x=get_servo_position(CLAW_SERVO);
		x+=5;
		set_servo_position(CLAW_SERVO, x);
		msleep(10);
	}
	while(x<CLAW_OPEN);
	create_forward(50);
	set_servo_position(LIFT_SERVO, CLAW_HIGH);
	msleep(WAIT_FOR_SERVO);
	create_backward(GET_IN_BARN);
	bales_placed+=2;
}

void get_last_bale()
{
	create_drive_direct(200, 200);
	move_to_nth_bale(2);	//3?
	//create_backward(EARLY_BALE_CORRECTION);
	//create_backward(LAST_BALE);
    create_turn_right();
    set_servo_position(CLAW_SERVO, CLAW_MIDDLE);
    msleep(WAIT_FOR_SERVO);
    set_servo_position(CLAW_SERVO, CLAW_LOW);
    msleep(WAIT_FOR_SERVO);
    create_turn_right();
    set_servo_position(CLAW_SERVO, CLAW_HIGH);
    msleep(WAIT_FOR_SERVO);
    create_turn_left();
    create_turn_left();
    move_to_nth_bale(1);
	grab_second_bale();
}

void go_to_bales()
{
	create_forward(PIPE_BUMP);
	create_backward(BACK_OFF);
	/*create_turn_right();
	create_drive_direct(-TURN_SPEED, TURN_SPEED);
	msleep(150);
	create_stop();
	create_turn_right();*/
	create_backward(DO_BALITE);
	set_servo_position(LIFT_SERVO, CLAW_HIGH);
	create_turn_right();
	create_forward((int)(1.8*PIPE_BUMP));		//(int)
	create_backward((int)(1.1*BACK_OFF));		//(int)
	create_turn_left();
}

void get_more_bales()
{
	create_backward(RETURN_TO_BALES);
	create_turn_left();
	msleep(500);
    create_drive_direct(-200, -200);
    msleep(1500);
   
    create_drive_direct(200, 200);
    msleep(BACK_OFF);
    
    create_turn_right();
    create_turn_right();
    
	create_drive_direct(-200, -200);
    move_to_nth_bale(1);
	create_forward(EARLY_BALE_CORRECTION);
	grab_bale();
	create_drive_direct(-200, -200);
	move_to_nth_bale(1);
	create_forward(EARLY_BALE_CORRECTION);
	create_drive_direct(200, 200);
	msleep(BALE_CATCH_CORRECTION);
	create_stop();
	grab_second_bale();
	create_backward(AFTER_BALES);
}

void move_to_nth_bale(int n)
{
  	printf("Moving the the %d bale now", n);
	int bales_detected=0;
	int prev_value=0;
	int current_value=0;
	while(bales_detected < n)
	{	
		current_value=analog(BALE_SENSOR);
		printf("%d\n", current_value);
		if(current_value > BALE_DETECTED+200 && prev_value < BALE_DETECTED+200)
		{
            if(debounceSensor(BALE_SENSOR, 20) <= BALE_DETECTED+200)
                return;
            
			//printf("\n++++++++++++++++++");
			bales_detected++;
          	printf("Bale detected. Current bale : %d", bales_detected);
		}
        
		prev_value=current_value;      	
		msleep(10);
	}
	create_stop();
}

void grab_second_bale()
{
	set_servo_position(LIFT_SERVO, CLAW_MIDDLE);
	msleep(WAIT_FOR_SERVO);
	set_servo_position(LIFT_SERVO,release[1]);
	msleep(WAIT_FOR_SERVO);
	set_servo_position(CLAW_SERVO, CLAW_OPEN);
	msleep(WAIT_FOR_SERVO);
	if(bales_placed==0)
		create_forward(50);
	set_servo_position(LIFT_SERVO, CLAW_LOW);
	msleep(WAIT_FOR_SERVO);
	set_servo_position(CLAW_SERVO, CLAW_CLOSED);
	msleep(WAIT_FOR_SERVO);
	set_servo_position(LIFT_SERVO, CLAW_HIGH);
}

void get_the_bowl()
{
	create_turn_right();
	create_forward(2500);
	set_servo_position(LIFT_SERVO, CLAW_MIDDLE);
	msleep(WAIT_FOR_SERVO);
	create_turn_left();
	create_forward(200);
	create_turn_left();
	set_servo_position(LIFT_SERVO, CLAW_LOW);
	msleep(WAIT_FOR_SERVO);
	create_turn_right();
	create_backward(200);
	create_turn_right();
	create_backward(2500);
	create_turn_left();
}

void few_more_points()
{
  	create_forward(GET_IN_BARN);
  	create_turn_right();
}

int debounceSensor(int pin, int time){
	msleep(time);
    
    return analog(pin);
}
