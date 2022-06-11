#include <stdio.h>
#include "task.h"
#include "alarma.h"
#include "light.h"
#include "sound.h"
#define MAGENTA "\x1b[35m"
#define RESET   "\x1b[0m"
#define BLUE    "\x1b[32m"
static fsm_t *alarma_fsm;
static fsm_t *light_fsm;
static fsm_t *interp_fsm;
static fsm_t *sound_fsm;

/*CODIGO*/
static void * task1_func (void* arg)
{
  static int cnt = 0;

  struct timeval next_activation;
  struct timeval now, timeout;

  gettimeofday (&next_activation, NULL);
  while (1) {
    struct timeval *period = task_get_period (pthread_self());
    timeval_add (&next_activation, &next_activation, period);
    gettimeofday (&now, NULL);
    timeval_sub (&timeout, &next_activation, &now);
    select (0, NULL, NULL, NULL, &timeout) ;
	fsm_fire(alarma_fsm);
  }
}
/*ALARMA SONIDO*/
static void * task2_func (void* arg)
{
  static int cnt = 0;

  struct timeval next_activation;
  struct timeval now, timeout;

  gettimeofday (&next_activation, NULL);
  while (1) {
    struct timeval *period = task_get_period (pthread_self());
    timeval_add (&next_activation, &next_activation, period);
    gettimeofday (&now, NULL);
    timeval_sub (&timeout, &next_activation, &now);
    select (0, NULL, NULL, NULL, &timeout) ;
	fsm_fire(sound_fsm);
  }
}
/*LUZ DE PRESENCIA*/
static void * task3_func (void* arg)
{
  static int cnt = 0;

  struct timeval next_activation;
  struct timeval now, timeout;

  gettimeofday (&next_activation, NULL);
  while (1) {
    struct timeval *period = task_get_period (pthread_self());
    timeval_add (&next_activation, &next_activation, period);
    gettimeofday (&now, NULL);
    timeval_sub (&timeout, &next_activation, &now);
    select (0, NULL, NULL, NULL, &timeout) ;
	fsm_fire(light_fsm);
  }
}
static void * task4_func (void* arg)
{
  static int cnt = 0;

  struct timeval next_activation;
  struct timeval now, timeout;

  gettimeofday (&next_activation, NULL);
  while (1) {
    struct timeval *period = task_get_period (pthread_self());
    timeval_add (&next_activation, &next_activation, period);
    gettimeofday (&now, NULL);
    timeval_sub (&timeout, &next_activation, &now);
    select (0, NULL, NULL, NULL, &timeout) ;
	fsm_fire(interp_fsm);
  }
}

int main(void)
{
    light_fsm = fsm_new_light();
    alarma_fsm = fsm_new_alarma();
	sound_fsm = fsm_new_sound();
	interp_fsm = fsm_new_interp();
	ALARMA_ACTIVA = 0;
	printf("----------------------------" BLUE "MANUAL" RESET "----------------------------\n");
	printf("Comandos de uso\n");
	printf("El pulsador se simula con : " MAGENTA "a"RESET"\n");
	printf("El sensor de movimiento se activa con : " MAGENTA "presencia"RESET"\n");
	printf("El sensor de movimiento se desactiva con : " MAGENTA "no presencia"RESET"\n");
	printf("--------------------------------------------------------------\n");

	pthread_t alarma = task_new ("task1", task1_func, 50, 50, 4, 1024);
	pthread_t sound = task_new ("task2", task2_func, 100, 100, 2, 1024);
	pthread_t light = task_new ("task3", task3_func, 300, 300, 1, 1024);
	pthread_t interp= task_new ("task4", task4_func, 50, 50, 3, 1024);

  pthread_join (alarma, NULL);
  pthread_join (interp, NULL);
  pthread_join (sound, NULL);
  pthread_join (light, NULL);
}
