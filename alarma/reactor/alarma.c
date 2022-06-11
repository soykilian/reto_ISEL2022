#include "alarma.h"
static struct timeval timer1;
static struct timeval timer10;
int i = 0;
char	codigo_introd[4] = "---\0";
char	correct_code[4] = "332\0";
char	values[10]= "1234567890";
int codigo_correcto(void)
{
	printf("codigo %s\n", codigo_introd);
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
	return (timeval_less(&now, &timer10) && i == 2 && codigo_correcto());
}
int check_falsecode(fsm_t *this)
{
	struct timeval now;

	gettimeofday(&now, NULL);
	return (timeval_less(&now, &timer10) && i == 2 && !codigo_correcto());
}
/******************************************************************************/
/*********************************FUNCIONES DE SALIDA**************************/ 
void act_cont(fsm_t *this)
{
	struct timeval now;
	struct timeval step = {3, 0};

	gettimeofday(&now, NULL);
	timeval_add(&timer1, &now, &step);
	cont++;
	printf("CONT%d\n", cont);
	pulsador=0;
}
void increase_i(fsm_t *this)
{
	struct timeval now;
	struct timeval step = {3, 0};

	gettimeofday(&now, NULL);
	timeval_add(&timer1, &now, &step);
	pulsador=0;
	printf("SIGUIENTE DIGITO\n");
	i++;
	cont++;
}
void save_code(fsm_t *this)
{
	codigo_introd[i] = values[cont - 1];
	printf("digito = %d\n", cont);
	cont = 0;
	struct timeval now;
	struct timeval step = {10, 0};
	gettimeofday(&now, NULL);
	timeval_add(&timer10, &now, &step);
}
void aprove_code(fsm_t *this)
{
	codigo_ok = 1;
	ALARMA_ACTIVA = !ALARMA_ACTIVA;
	printf("ALARMA = %d\n", ALARMA_ACTIVA);
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
		{2, check_timer10, 2, NULL},
		{2, check_pulsador_i, 1, increase_i},
		{2, check_code, 0, aprove_code},
		{2, check_falsecode, 0, disaprove_code},
	};
	return (fsm_new(tt));
}
