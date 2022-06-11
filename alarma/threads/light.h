#include <stdio.h>
#include "fsm.h"
#include "alarma.h"
#include <unistd.h>
#include <sys/select.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <sys/time.h>


int light;
int presencia;
fsm_t* fsm_new_light(void);
