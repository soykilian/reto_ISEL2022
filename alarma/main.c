#include "alarma.h"

void delay_until (struct timeval* next_activation)
{
  struct timeval now, timeout;

  gettimeofday (&now, NULL);
  timeval_sub (&timeout, next_activation, &now);
  select (0, NULL, NULL, NULL, &timeout);
}

int main()
{
	struct timeval clk_period = {0, 500*1000};
	struct timeval next_activation;
	
	fsm_t* alarma_fsm = fsm_new_alarma();
	fsm_t* interp_fsm = fsm_new_interp();
	fsm_t* light_fsm = fsm_new_light();
	gettimeofday(&next_activation, NULL);
	ALARMA_ACTIVA = 0;
	while (1)
	{
		fsm_fire(alarma_fsm);
		fsm_fire(light_fsm);
		fsm_fire(interp_fsm);
		timeval_add(&next_activation, &next_activation, &clk_period);
		delay_until(&next_activation);
	}
}
