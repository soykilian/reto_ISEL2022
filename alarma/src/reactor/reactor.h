#ifndef _REACTOR_H
#define _REACTOR_H

#include "sys/time.h"
#include "alarma.h"
#include "light.h"
#include "sound.h"

void timeval_sub (struct timeval *res, struct timeval *a, struct timeval *b);
void timeval_add (struct timeval *res, struct timeval *a, struct timeval *b);
int timeval_less (struct timeval *a, struct timeval *b);

struct event_handler_t;
typedef void (*eh_func_t) (struct event_handler_t*);

struct event_handler_t {
  int prio;
  struct timeval next_activation;
  eh_func_t run;
};
typedef struct event_handler_t EventHandler;

void event_handler_init (EventHandler* eh, int prio, eh_func_t run);
void event_handler_run (EventHandler* eh);

void reactor_init (void);
void reactor_add_handler (EventHandler* eh);
void reactor_handle_events (void);

#endif
