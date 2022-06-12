#include "semaforo.h"

void timeval_sub (struct timeval *res, struct timeval *a, struct timeval *b);
void timeval_add (struct timeval *res, struct timeval *a, struct timeval *b);
int timeval_less (struct timeval *a, struct timeval *b);

int light_p, light_s;
struct timeval timer1;
struct timeval timer2;
/*********************************CONDICIONES DE GUARDA************************/ 
int check_second(fsm_t *this)
{
	return  (boton_p == 1 || sensor_s == 1);
}

int check_timer1(fsm_t *this)
{
	struct timeval now;
	gettimeofday(&now, NULL);
	return  (timeval_less(&timer1, &now));
}

int check_time_second(fsm_t *this)
{
	struct timeval now;
	gettimeofday(&now, NULL);
	return  (boton_s == 1 || timeval_less(&timer2, &now));
}

int check_timer2(fsm_t *this)
{
	struct timeval now;
	gettimeofday(&now, NULL);
	return  (timeval_less(&timer2, &now));
}
/******************************************************************************/
/*********************************FUNCIONES DE SALIDA**************************/ 
void set_yellow_first(fsm_t *this)
{
	struct timeval now;
	struct timeval step = {5, 0};
	gettimeofday(&now, NULL);
	timeval_add(&timer1, &step, &now);
	light_p = 2;
	printf("SEMAFORO PPAL : %i, SEMAFORO SECND %i\n", light_p, light_s);
	printf("------------------------------------------------\n");
}

void set_red_first(fsm_t *this)
{
	struct timeval now;
	struct timeval step = {20, 0};
	gettimeofday(&now, NULL);
	timeval_add(&timer2, &step, &now);
	light_p = 0;
	light_s = 1;
	printf("SEMAFORO PPAL : %i, SEMAFORO SECND %i\n", light_p, light_s);
	printf("------------------------------------------------\n");
}

void set_yellow_second(fsm_t *this)
{
	struct timeval now;
	struct timeval step = {5, 0};
	gettimeofday(&now, NULL);
	timeval_add(&timer1, &step, &now);
	light_s = 2;
	printf("SEMAFORO PPAL : %i, SEMAFORO SECND %i\n", light_p, light_s);
	printf("------------------------------------------------\n");
}

void set_green_first(fsm_t *this)
{
	struct timeval now;
	struct timeval step = {60, 0};
	gettimeofday(&now, NULL);
	timeval_add(&timer2, &step, &now);
	light_s = 0;
	light_p = 1;
	printf("SEMAFORO PPAL : %i, SEMAFORO SECND %i\n", light_p, light_s);
	printf("------------------------------------------------\n");
}
/******************************************************************************/
fsm_t* fsm_new_semaforo(void)
{
	static fsm_trans_t tt[] ={
		{0, check_second, 1, set_yellow_first},
		{1, check_timer1, 2, set_red_first},
		{2, check_time_second, 3, set_yellow_second},
		{3, check_timer1, 4, set_green_first},
		{4, check_timer2,0, NULL},
		{-1, NULL, -1, NULL}
	};
	return (fsm_new(tt));
}
