#define DDFIX
#ifndef BOTBALL_H
#define BOTBALL_H
#include <kipr/botball.h>
#include "create_functions.h"
#endif

void first_bale()
{
	//set_servo_position(LIFT_SERVO, CLAW_MIDDLE);
	create_turn_left();
	create_forward(PUSH_FIRST_BALE);
	create_backward(PUSH_FIRST_BALE-300);
	set_servo_position(CLAW_SERVO, CLAW_OPEN);
	msleep(200);
	create_turn_angle(72);	//LOL 420
	//create_turn_left(); // moje da e malko pod 90'
	//inache left leko prezaviva
	//create_turn_angle(45);
	//msleep(500);
	/*while(analog(BALE_SENSOR) < (BALE_DETECTED-200))
	{
		//create_forward(200, -200);
		create_turn_angle(3); //decrease
		msleep(10);
	}
	msleep(50);
	create_turn_angle(-2); //back off - compensation
	msleep(50);*/
	//create_drive_direct(100, 100);
	//msleep(100);
	create_stop();
	grab_bale();
	set_servo_position(LIFT_SERVO, CLAW_MIDDLE);
	create_turn_right();
	create_forward(500);
	create_turn_left();
	msleep(500);
}
