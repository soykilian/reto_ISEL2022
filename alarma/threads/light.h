#ifndef LIGHT_H
# define LIGHT_H
#include "alarma.h"
#include "fsm.h"
int light;
int presencia;
fsm_t* fsm_new_light(void);

void timeval_sub (struct timeval *res, struct timeval *a, struct timeval *b);
void timeval_add (struct timeval *res, struct timeval *a, struct timeval *b);
int timeval_less (struct timeval *a, struct timeval *b);
#endif
