#define DDFIX
#ifndef BOTBALL_H
#define BOTBALL_H
#include <kipr/botball.h>
#include "create_functions.h"
#endif

int main()
{
	if(create_init()==-1)
		return -1;
	first_bale();
	go_to_bales();
	get_last_bale();
	place_bale();
	get_more_bales();
	place_bale();
	/*get_the_bowl();*/
	create_disconnect();
	return 0;
}
