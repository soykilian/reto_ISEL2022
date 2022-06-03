#include "alarma.h"

struct timeval timer1;
struct timeval timer10;
int i = 0;
char	codigo_introd[3] = "---";
char	correct_code[3] = "332";
char	values[10]= "1234567890";
int codigo_correcto(void)
{
	return (strncmp(correct_code, codigo_introd, 3) == 0);
}
/*********************************CONDICIONES DE GUARDA************************/ 
int check_pulsador(fsm_t *this)
{
	return (pulsador == 1);
}
int check_notpuls(fsm_t *this)
{
	struct timeval now;

	gettimeofday(&now, NULL);
	return (!pulsador && timeval_less(&timer1,&now));
}
int check_timer10(fsm_t *this)
{
	struct timeval now;

	gettimeofday(&now, NULL);
	return (!pulsador && timeval_less(&timer10,&now));
}
int check_pulsador_i(fsm_t *this)
{
	return (pulsador && i < 3);
}
int check_code(fsm_t *this)
{
	struct timeval now;

	gettimeofday(&now, NULL);
	return (timeval_less(&timer10, &now) && i == 3 && codigo_correcto());
}
int check_falsecode(fsm_t *this)
{
	struct timeval now;

	gettimeofday(&now, NULL);
	return (timeval_less(&timer10, &now) && i == 3 && !codigo_correcto());
}
/******************************************************************************/
/*********************************FUNCIONES DE SALIDA**************************/ 
void act_cont(fsm_t *this)
{
	struct timeval now;
	struct timeval step = {1, 0};

	gettimeofday(&now, NULL);
	timeval_add(&timer1, &now, &step);
	cont++;
	printf("contador %d\n",cont);
	pulsador=0;
	printf("pulsador %d\n", pulsador);
}
void increase_i(fsm_t *this)
{
	pulsador=0;
	i++;
}
void save_code(fsm_t *this)
{
	codigo_introd[i] = values[cont - 1];
	cont = 0;
	struct timeval now;
	struct timeval step = {10, 0};
	gettimeofday(&now, NULL);
	timeval_add(&timer10, &now, &step);
}
void aprove_code(fsm_t *this)
{
	codigo_ok = 1;
	i = 0;
	cont = 0;
}
void disaprove_code(fsm_t *this)
{
	codigo_ok = 0;
	i = 0;
	cont = 0;
}
/******************************************************************************/
fsm_t* fsm_new_alarma(void)
{
	static fsm_trans_t tt[] = {
		{0, check_pulsador, 1, act_cont},
		{1, check_pulsador, 1, act_cont},
		{1, check_notpuls, 2, save_code},
		{2, check_timer10, 1, NULL},
		{2, check_pulsador_i, 1, increase_i},
		{2, check_code, 0, aprove_code},
		{2, check_falsecode, 0, disaprove_code},
	};
	return (fsm_new(tt));
}
