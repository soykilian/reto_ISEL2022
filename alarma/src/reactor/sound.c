#include "sound.h"


static int check_alarma(fsm_t *this)
{
	return (ALARMA_ACTIVA == 1);
}
static int check_notalarma(fsm_t *this)
{
	return (ALARMA_ACTIVA == 0);
}
static int check_presencia(fsm_t *this)
{
	return (presencia==1);
}
/*---------------------------------ACTIONS-------------------------------*/
void activate_sound(fsm_t *this){
	light_2 = 1;
	sound = 1;
}
void deactivate_sound(fsm_t *this){
	light_2 = 0;
	sound = 0;
	printf("SE APAGA SONIDO\n");
}
fsm_t* fsm_new_sound(void)
{
	static fsm_trans_t tt[] = {
		{0, check_alarma, 1, NULL},
		{1, check_notalarma, 0, NULL},
		{1, check_presencia, 2, activate_sound},
		{2, check_notalarma, 0, deactivate_sound},
		{-1, NULL, -1, NULL}
	};
	return (fsm_new(tt));
}
