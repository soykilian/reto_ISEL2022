#include "alarma.h"
#include "light.h"
struct timeval timer1;

int check_timer(fsm_t *this)
{
	struct timeval now;

	gettimeofday(&now, NULL);
	return (timeval_less(&now, &timer1) &&  presencia!=1);
}
int check_presencia(fsm_t *this)
{
	return (presencia==1);
}
int check_alarma(fsm_t *this)
{
	return (ALARMA_ACTIVA == 1);
}
int check_deactivate(fsm_t *this)
{
	return (ALARMA_ACTIVA != 1);
}
void turn_onlight(fsm_t *this)
{
	struct timeval now;
	struct timeval step = {5, 0};

	gettimeofday(&now, NULL);
	timeval_add(&timer1, &now, &step);
	light = 1;
	printf("LIGHT %d\n", light);
}
void turn_offlight(fsm_t *this)
{
	light=0;
	printf("LIGHT %d\n", light);
}

void set_timer(fsm_t *this)
{
	struct timeval now;
	struct timeval step = {5, 0};

	gettimeofday(&now, NULL);
	timeval_add(&timer1, &now, &step);
}
fsm_t* fsm_new_light(void)
{
	static fsm_trans_t tt[] = {
		{0, check_alarma, 1, NULL},
		{1, check_presencia, 2, turn_onlight},
		{1, check_deactivate, 0, NULL},
		{2, check_timer, 1, turn_offlight},
		{2, check_presencia, 2, set_timer},
		{-1, NULL, -1, NULL}
	};
	return (fsm_new(tt));
}
