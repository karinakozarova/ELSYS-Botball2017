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
	create_backward(170);
	msleep(200);
	create_turn_angle(72);	//къф е тоз див ъгъл?!? LOL 420
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
	//create_drive_direct(-100, 100);
	//msleep(FIRST_BALE_CORRECTION);
	create_stop();
	grab_bale();
	create_turn_right();
	create_forward(170+700);
	create_turn_left();
}
