#include <stdio.h>
#include "fsm.h"
#include <unistd.h>
#include <sys/select.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <sys/time.h>

int boton_s, boton_p, sensor_s;
void timeval_sub (struct timeval *res, struct timeval *a, struct timeval *b);
void timeval_add (struct timeval *res, struct timeval *a, struct timeval *b);
int timeval_less (struct timeval *a, struct timeval *b);

fsm_t*	fsm_new_interp(void);
void	fsm_fire (fsm_t* this);
void fsm_init (fsm_t* this, fsm_trans_t* tt);
fsm_t*	fsm_new (fsm_trans_t* tt);
fsm_t* fsm_new_semaforo(void);
void delay_until (struct timeval* next_activation);
