#include <sys/time.h>
#include "alarma.h"
#include "light.h"

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
	ALARMA_ACTIVA = 0;
	int frame = 0;
	while (1)
	{
		fsm_fire(interp_fsm);
		switch (frame){
			case 0 :
				fsm_fire(alarma_fsm);
				fsm_fire(light_fsm);
				break;
			case 1:
				fsm_fire(alarma_fsm);
				break;
			case 2:
				fsm_fire(alarma_fsm);
				break;
			case 3:
				fsm_fire(alarma_fsm);
				break;
			case 4:
				fsm_fire(alarma_fsm);
				break;
		}
		timeval_add(&next_activation, &next_activation, &T);
		delay_until(&next_activation);
		frame = (frame + 1) % 5;
	}
}
