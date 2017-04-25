//Портове
#define CLAW_SERVO 2
#define LIFT_SERVO 1
#define STARTER 4
#define BALE_SENSOR 5
#define LINE_SENSOR 3

//Серво мотори
#define CLAW_OPEN 1605
#define CLAW_CLOSED 680
#define CLAW_LOW 1400
#define CLAW_MIDDLE 1000
#define CLAW_HIGH 640

#ifndef DDFIX
const int release[4]={1350, 1200, 1070, 900};
#endif

//Сензори
#define BALE_DETECTED 2600	//2600
#define BLACK 3500

//Разстояния
#define PIPE_BUMP 800
#define BACK_OFF 400
#define DO_BALITE 4450	//Зависи от батерията
#define RETURN_TO_BALES 950
#define AFTER_BALES 1100	//Зависи от батерията
#define GET_IN_BARN 850

//Корекции
#define TURN_CORRECTION 1.046	//0.075 Зависи от разположението на контролера върху робота
#define CLAW_DISPLACEMENT -20	//++
#define _90_DEGREES 29	//презавива
#define TURN_SPEED 200
#define WAIT_FOR_SERVO 700
#define BALE_CATCH_CORRECTION 50
#define EARLY_BALE_CORRECTION 50

int create_init();
void create_turn_left();
void create_turn_right();
void create_forward();
void create_backward();
void create_turn_angle(int angle);
void grab_bale();
void place_bale();
void get_last_bale();
void first_bale();
void go_to_bales();
void get_more_bales();
void move_to_nth_bale(int n);
void grab_second_bale();
void get_the_bowl();
