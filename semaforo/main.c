#include "semaforo.h"
#include <stdio.h>
#define MAGENTA "\x1b[35m"
#define RESET   "\x1b[0m"
#define BLUE   "\x1b[36m" 
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
void delay_until (struct timeval* next_activation)
{
  struct timeval now, timeout;
  gettimeofday (&now, NULL);
  timeval_sub (&timeout, next_activation, &now);
  select (0, NULL, NULL, NULL, &timeout);
}

int main()
{
	printf("----------------------------" BLUE "MANUAL" RESET "----------------------------\n");
	printf("Comandos de uso\n");
	printf("El pulsador de peatones principal  se simula con : " MAGENTA "bp"RESET"\n");
	printf("El pulsador de peatones secundario  se simula con : " MAGENTA "bs"RESET"\n");
	printf("La espira de la secundaria se simula con : " MAGENTA "ss" RESET"\n");
	printf("--------------------------------------------------------------\n");
	printf("El semáforo tiene tres estados\n");
	printf(GREEN "Semáforo en verde: 1\n"RESET);
	printf(YELLOW "Semáforo en amarillo: 2\n"RESET);
	printf(RED "Semáforo en rojo : 0\n"RESET);
	printf("--------------------------------------------------------------\n");

	struct timeval clk_period = {0, 100*1000};
	struct timeval next_activation;
	
	fsm_t* semaforo_fsm = fsm_new_semaforo();
	fsm_t* interp_fsm = fsm_new_interp();
	gettimeofday(&next_activation, NULL);
	while (1)
	{
		fsm_fire(semaforo_fsm);
		fsm_fire(interp_fsm);
		timeval_add(&next_activation, &next_activation, &clk_period);
		delay_until(&next_activation);
	}
}
