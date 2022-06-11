#include "alarma.h"
#include "light.h"
#include "reactor.h"
#define MAGENTA "\x1b[35m"
#define RESET   "\x1b[0m"
#define BLUE    "\x1b[32m"

static fsm_t *alarma_fsm;
static fsm_t *light_fsm;
static fsm_t *interp_fsm;
static fsm_t *sound_fsm;

static void interp_task (struct event_handler_t* this) {
    static struct timeval period = {0, 50*1000};
    fsm_fire(interp_fsm);
    timeval_add (&this->next_activation, &this->next_activation, &period);
}
static void alarm_task (struct event_handler_t* this) {
    static struct timeval period = {0, 50*1000};
    fsm_fire(alarma_fsm);
    timeval_add (&this->next_activation, &this->next_activation, &period);
}

static void light_task (struct event_handler_t* this) {
    static struct timeval period = {0, 250*1000};
    fsm_fire(light_fsm);
    timeval_add (&this->next_activation, &this->next_activation, &period);
}

static void sound_task (struct event_handler_t* this) {
    static struct timeval period = {0, 100*1000};
    fsm_fire(sound_fsm);
    timeval_add (&this->next_activation, &this->next_activation, &period);
}
int main () {

    EventHandler task_alarm, task_light, task_interp, task_sound;
    reactor_init();

    light_fsm = fsm_new_light();
    alarma_fsm = fsm_new_alarma();
	interp_fsm = fsm_new_interp();
	sound_fsm = fsm_new_sound();

    event_handler_init (&task_interp, 4, interp_task);
    reactor_add_handler (&task_interp);

    event_handler_init (&task_sound, 2, sound_task);
    reactor_add_handler (&task_sound);

    event_handler_init (&task_alarm, 3, alarm_task);
    reactor_add_handler (&task_alarm);

    event_handler_init (&task_light, 1, light_task);
    reactor_add_handler (&task_light);

    //Start handling them
	printf("----------------------------" BLUE "MANUAL" RESET "----------------------------\n");
	printf("Comandos de uso\n");
	printf("El pulsador se simula con : " MAGENTA "a"RESET"\n");
	printf("El sensor de movimiento se activa con : " MAGENTA "presencia"RESET"\n");
	printf("El sensor de movimiento se desactiva con : " MAGENTA "no presencia"RESET"\n");
	printf("--------------------------------------------------------------\n");
    while (1) {
        reactor_handle_events ();
    }
}
