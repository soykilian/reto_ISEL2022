#include "semaforo.h"

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

static int cmd_bs(fsm_t* fsm)
{
	return (strcmp(cmd, "bs") == 0);
}

static int cmd_bp(fsm_t* fsm)
{
	return (strcmp(cmd, "bp") == 0);
}

static int cmd_ss(fsm_t* fsm)
{
	return (strcmp(cmd, "ss") == 0);
}

static int cmd_quit(fsm_t* fsm)
{
	return (strcmp(cmd, "quit") == 0);
}

static void do_quit(fsm_t* this)
{
	exit(0);
}

static void do_bs(fsm_t* this)
{
	boton_s = 1;
}

static void do_bp(fsm_t* this)
{
	boton_p = 1;
}

static void do_ss(fsm_t* this)
{
	sensor_s = 1;
}

fsm_t*	fsm_new_interp(void)
{
	static fsm_trans_t tt[] = {
		{ 0, input_ready, 0, do_read },
		{ 0, cmd_bp, 0, do_bp },
		{ 0, cmd_bs, 0, do_bs },
		{ 0, cmd_ss, 0, do_ss },
		{ 0, cmd_quit, 0, do_quit },
		{ -1, NULL, -1, NULL },
	};
	return fsm_new(tt);
}
