ltl p2 {([](!((semaforo_p==1)&&(semaforo_s==1)))) &&
([](!((semaforo_p==2)&&(semaforo_s==2)))) &&
([](!((semaforo_p==1)&&(semaforo_s==2)))) &&
([](!((semaforo_p==2)&&(semaforo_s==1)))) &&
([](!((semaforo_p==0)&&(semaforo_s==0)))) &&
([]((s_s==1) -> <>(semaforo_s==1))) &&
([]((b_s==1) -> <>(semaforo_s==0))) &&
([]((b_p==1) -> <>(semaforo_p==0))) &&
[]((semaforo_p==2) -> <>(semaforo_p==0)) && []((semaforo_s==2) -> <>(semaforo_s==0))}

/*Modelo promela*/
mtype = {VERDE1, GUARDA1, ESPERA1, ROJO1, ESPERA2}

/*INPUTS*/
int s_s, b_s, b_p;

/*OUTPUTS*/
int semaforo_p = 1;
int semaforo_s = 0; // = 2 AMARILLO, =1 VERDE, =0 ROJO
int state;
//int time1, time2;
//int now;
active proctype semaforo(){
	state = GUARDA1;
	do
	::if
	:: (state == GUARDA1) -> atomic{
		if
		:: (s_s == 1 || b_p == 1) -> state = ESPERA1; semaforo_p = 2; s_s=0;
b_p=0;
		fi;
	}
	:: (state == ESPERA1) -> atomic {
		if
		:: semaforo_p =0; semaforo_s=1;  state = ROJO1;
		//:: (now < time1) -> state = ESPERA1;
		fi;
	}
	:: (state == ROJO1) -> atomic {
		if
		:: (b_s == 1) -> semaforo_s = 2; state = ESPERA2; b_s = 1;
		//:: (b_s == 0 && now < time2) -> state= ROJO1;
		fi;
	}
	:: (state == ESPERA2) -> atomic {
		if
		:: semaforo_p = 1; semaforo_s = 0;  state = VERDE1;
		fi;
	}
	:: (state == VERDE1) -> atomic {
		if
		:: state = GUARDA1;
		fi;
	}
	fi;
	printf("STATE %e\n, SEMAFORO_PPAL %d\n, SEMAFORO_SEC %d\n", state, semaforo_p, semaforo_s);
	printf("Pulsador ppal %d\n Pulsador secundario:%d\n Sensor secundariop :%d\n", b_p, b_s, s_s);
	printf("------------------------------------------\n");
	od;
}

active proctype entorno(){
	do
	:: b_s = 1;
	:: s_s = 1;
	:: b_p = 1;
	:: skip -> skip
	od;
}
