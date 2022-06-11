#include "alarma.h"
#include "light.h"

static char cmd[40];

static int input_ready (fsm_t* fsm)
{
        int ret;
        fd_set rds;
        struct timeval timeout = { 0, 0 };
        FD_ZERO(&rds);
        FD_SET(0, &rds);
        ret = select(1, &rds, NULL, NULL, &timeout); 
        return ret;
}

static void do_read (fsm_t* fsm)
{ 
        int cnt = read(0, cmd, 40);
        cmd[cnt-1] = '\0';
}


static int cmd_cod(fsm_t* fsm)
{
	return (strcmp(cmd, "a") == 0);
}

static int cmd_presencia(fsm_t* fsm)
{
	return (strcmp(cmd, "presencia") == 0);
}
static int cmd_notpresencia(fsm_t* fsm)
{
	return (strcmp(cmd, "no presencia") == 0);
}
static void do_cod(fsm_t* this)
{
	pulsador = 1;
    cmd[0] = '\0';
}

static void do_presencia(fsm_t* this)
{
	presencia = 1;
}
static void do_notpresencia(fsm_t* this)
{
	presencia = 0;
}
fsm_t*	fsm_new_interp(void)
{
	static fsm_trans_t tt[] = {
		{ 0, input_ready, 0, do_read },
		{ 0, cmd_cod, 0, do_cod },
		{ 0, cmd_presencia, 0, do_presencia},
		{ 0, cmd_notpresencia, 0, do_notpresencia},
		{ -1, NULL, -1, NULL },
	};
	return fsm_new(tt);
}
