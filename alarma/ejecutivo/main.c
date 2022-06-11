#include <sys/time.h>
#define MAGENTA "\x1b[35m"
#define RESET   "\x1b[0m"
#define BLUE    "\x1b[32m"
#include "alarma.h"
#include "light.h"
#include "sound.h"
void delay_until (struct timeval* next_activation)
{
  struct timeval now, timeout;

  gettimeofday (&now, NULL);
  timeval_sub (&timeout, next_activation, &now);
  select (0, NULL, NULL, NULL, &timeout);
}

int main()
{
	struct timeval next_activation;
	struct timeval T = {0, 50*1000};
	gettimeofday(&next_activation, NULL);

	fsm_t* alarma_fsm = fsm_new_alarma();
	fsm_t* interp_fsm = fsm_new_interp();
	fsm_t* light_fsm = fsm_new_light();
	fsm_t* sound_fsm = fsm_new_sound();
	ALARMA_ACTIVA = 0;
	int frame = 0;
	printf("----------------------------" BLUE "MANUAL" RESET "----------------------------\n");
	printf("Comandos de uso\n");
	printf("El pulsador se simula con : " MAGENTA "a"RESET"\n");
	printf("El sensor de movimiento se activa con : " MAGENTA "presencia"RESET"\n");
	printf("El sensor de movimiento se desactiva con : " MAGENTA "no presencia"RESET"\n");
	printf("--------------------------------------------------------------\n");
	while (1)
	{
		fsm_fire(interp_fsm);
		switch (frame){
			case 0 :
				fsm_fire(alarma_fsm);
				fsm_fire(sound_fsm);
				fsm_fire(light_fsm);
				break;
			case 1:
				fsm_fire(alarma_fsm);
				fsm_fire(sound_fsm);
				break;
			case 2:
				fsm_fire(alarma_fsm);
				fsm_fire(sound_fsm);
				break;
			case 3:
				fsm_fire(alarma_fsm);
				fsm_fire(sound_fsm);
				break;
			case 4:
				fsm_fire(alarma_fsm);
				fsm_fire(sound_fsm);
				break;
		}
		timeval_add(&next_activation, &next_activation, &T);
		delay_until(&next_activation);
		frame = (frame + 1) % 5;
	}
}
