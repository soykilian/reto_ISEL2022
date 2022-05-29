/**
ltl p1 {[](<>(semaforo_p==0)) &&
[](<>(semaforo_p==1)) &&
[](<>(semaforo_p==2)) &&
[](<>(semaforo_s==0)) &&
[](<>(semaforo_s==1)) &&
[](<>(semaforo_s==2))}
**/
ltl p2 {([]((semaforo_p==1)&&(semaforo_s==1))) &&
([]((semaforo_p==2)&&(semaforo_s==2))) &&
([]((semaforo_p==1)&&(semaforo_s==2))) &&
([]((semaforo_p==2)&&(semaforo_s==1))) &&
([]((semaforo_p==0)&&(semaforo_s==0)))}
/**
ltl p3 {[]((s_s==1) -> <>(semaforo_s==1)) &&
[]((b_s==1) -> <>(semaforo_s==1)) &&
[]((b_p==1) -> <>(semaforo_p==1)) }

ltl p4 {[]((semaforo_p==2) -> <>(semaforo_p==0)) &&
[]((semaforo_s==2) -> <>(semaforo_s==0))}
**/
/*Modelo promela*/
mtype = {VERDE1, GUARDA1, ESPERA1, ROJO1, ESPERA2}

/*INPUTS*/
int s_s, b_s, b_p;

/*OUTPUTS*/
int semaforo_p = 1;
int semaforo_s = 0; // = 2 AMARILLO, =1 VERDE, =0 ROJO
int state;
int time1, time2;
int now;
active proctype semaforo(){
	state = GUARDA1;
	do
	::if
	:: (state == GUARDA1) -> atomic{
		if
		:: (s_s == 1 || b_p == 1) -> state = ESPERA1; semaforo_p = 2; time1 = now + 5;
		fi;
	}
	:: (state == ESPERA1) -> atomic {
		if
		:: (now >= time1) -> semaforo_p =0; semaforo_s=1; time2= now + 30; state = ROJO1;
		//:: (now < time1) -> state = ESPERA1;
		fi;
	}
	:: (state == ROJO1) -> atomic {
		if
		:: (b_s == 1 || now >= time2) -> semaforo_s = 2; time1 = now + 5; state = ESPERA2;
		//:: (b_s == 0 && now < time2) -> state= ROJO1;
		fi;
	}
	:: (state == ESPERA2) -> atomic {
		if
		:: (now >= time1) -> semaforo_p = 1; semaforo_s = 0; time2 = now +90; state = VERDE1;
		fi;
	}
	:: (state == VERDE1) -> atomic {
		if
		:: (now >= time2) -> state = GUARDA1;
		fi;
	}
	fi;
	printf("STATE %e\n, SEMAFORO_PPAL %d\n, SEMAFORO_SEC %d\n NOW %d\n", state, semaforo_p, semaforo_s, now);
	printf("Pulsador ppal %d\n Pulsador secundario:%d\n Sensor secundariop :%d\n", b_p, b_s, s_s);
	printf("------------------------------------------\n");
	od;
}

active proctype entorno(){
	now = 0;
	do
	:: if
	:: b_s = 1;
	:: s_s = 1;
	:: b_p = 1;
	:: b_s = 0;
	:: s_s = 0;
	:: b_p = 0;
	:: skip
	fi;
	now = now + 1;
	od;
}
