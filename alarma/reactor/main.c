static fsm_t* alarma_fsm;
static fsm_t* light_fsm;


//REACTOR EVENTS
//Process key task and update timers state

//Alarm fsm task
static void alarm_task (struct event_handler_t* this) {
    static const struct timeval period = {0, 0.25*1000000};
    fsm_fire(alarm_fsm);
    timeval_add (&this->next_activation, &this->next_activation, &period);
}

//light fsm task
static void light_task (struct event_handler_t* this) {
    static const struct timeval period = {0, 0.5*1000000};
    fsm_fire(light_fsm);
    timeval_add (&this->next_activation, &this->next_activation, &period);
}

int main () {

    //Initialze input and output pins
    //initializePins()

    //Initialize events
    EventHandler task_kbd, task_alarm, task_code, task_light;
    reactor_init();

    /*
    * Finite States Machine
    * { OriginState, Trigger, DestinationState, Actions }
    */
    light_fsm = fsm_new_light();
    alarm_fsm = fsm_new_alarm();

    //WELCOME MESSAGE
    printf("\r\n-----------------------------------------------------------------------------------\n");
    printf("\rWELCOME!!! \n\n");
    printf("\rControls: \n");
    printf("\r    'k'    -> Enter digit of alarm code (wait 1sec to enter next digit). \n");
    printf("\r    'p'    -> Trigger presence sensor (PIR). \n");
    printf("\r    'q'    -> Exit program. \n");
    printf("\r-----------------------------------------------------------------------------------\n\n");

    //Initialize and add tasks
    event_handler_init (&task_alarm, 2, alarm_task);
    reactor_add_handler (&task_alarm);

    event_handler_init (&task_light, 1, light_task);
    reactor_add_handler (&task_light);
    //Start handling them
    while (1) {
        reactor_handle_events ();
    }

}
