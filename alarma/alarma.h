#include <stdio.h>
#include "fsm.h"
#include <unistd.h>
#include <sys/select.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <sys/time.h>

int cont;
int pulsador;
int codigo_ok;

void timeval_sub (struct timeval *res, struct timeval *a, struct timeval *b);
void timeval_add (struct timeval *res, struct timeval *a, struct timeval *b);
int timeval_less (struct timeval *a, struct timeval *b);


fsm_t* fsm_new_alarma(void);
fsm_t*  fsm_new_interp(void);
fsm_t*	fsm_new (fsm_trans_t* tt);
void fsm_init (fsm_t* this, fsm_trans_t* tt);
void	fsm_fire(fsm_t* this);
//fsm_t*	fsm_new_interp(void);
void delay_until (struct timeval* next_activation);
