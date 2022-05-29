ltl spec{

	/*Funcionamiento básico semáforo principal*/
	[] ((semaforoP==G) -> ((semaforoP==G) U (semaforoP==Y))) &&
	[] ((semaforoP==Y) -> ((semaforoP==Y) U (semaforoP==R))) &&
	[] ((semaforoP==R) -> ((semaforoP==R) U (semaforoP==G))) &&
	[] (((semaforoP==R) && !(semaforoP==Y) && !(semaforoP==G)) || (!(semaforoP==R) && (semaforoP==Y) && !(semaforoP==G)) || (!(semaforoP==R) && !(semaforoP==Y) && (semaforoP==G))) &&
	[] ((semaforoP==G) -> !X(semaforoP==R)) &&
	[]<>(semaforoP==G) && 

	/*Funcionamiento básico semáforo secundario*/
	[] ((semaforoS==G) -> ((semaforoS==G) U (semaforoS==Y))) &&
	[] ((semaforoS==Y) -> ((semaforoS==Y) U (semaforoS==R))) &&
	[] ((semaforoS==R) -> ((semaforoS==R) U (semaforoS==G))) &&
        [] (((semaforoS==R) && !(semaforoS==Y) && !(semaforoS==G)) || (!(semaforoS==R) && (semaforoS==Y) && !(semaforoS==G)) || (!(semaforoS==R) && !(semaforoS==Y) && (semaforoS==G))) &&
	[] ((semaforoS==G) -> !X(semaforoS==R)) && 

	/*Funcionamiento básico semáforo peatones principal*/
	[] ((peatonesP==G) -> ((peatonesP==G) U (peatonesP==R))) &&
	[] ((peatonesP==R) -> ((peatonesP==R) U (peatonesP==G))) &&
	[] (((peatonesP==R) && !(peatonesP==G)) || (!(peatonesP==R) && (peatonesP==G))) &&

	/*Funcionamiento básico semáforo peatones secundario*/
	[] ((peatonesS==G) -> ((peatonesS==G) U (peatonesS==R))) &&
	[] ((peatonesS==R) -> ((peatonesS==R) U (peatonesS==G))) &&
	[] (((peatonesS==R) && !(peatonesS==G)) || (!(peatonesS==R) && (peatonesS==G))) &&

	/*Comportamiento ante estímulos*/
	[](BotonP -> <>((semaforoP==R) && (semaforoS==G) && (peatonesP==G) && (peatonesS==R))) &&
	[](Sensor -> <>((semaforoP==R) && (semaforoS==G) && (peatonesP==G) && (peatonesS==R))) &&
	[](((time >= next) && !BotonP) -> <>((semaforoP==G) && (semaforoS==R) && (peatonesP==R) && (peatonesS==G))) &&
	[](!Sensor -> <>((semaforoP==G) && (semaforoS==R) && (peatonesP==R) && (peatonesS==G)))
}

/* FSM imputs */
int BotonP;
int Sensor;
int time;
int next;

/* FSM outputs */
mtype {G, Y, R};
mtype semaforoP;
mtype semaforoS;
mtype peatonesP;
mtype peatonesS;

/* Process that indicates FSM behaviour */
active proctype fsm(){
	int state = 0;
	next = time;
	semaforoP=G;
	semaforoS=R;
	peatonesP=R;
	peatonesS=G;	

	printf("Estado inicial: 0\n");
	printf ("estado = %d, BotonP = %d, Sensor = %d, time =%d, next = %d,semaforoP =%d, semaforoS =%d, peatonesP =%d, peatonesS =%d\n",
	    	state, BotonP, Sensor, time, next, semaforoP, semaforoS, peatonesP, peatonesS)
	do
	::if
		::(state == 0) -> atomic {
			if
			::((BotonP) || (Sensor))-> state=1; semaforoP=Y; BotonP=0; Sensor=0;
                       			 printf("(Transition from state 0 to state 1\n");
                        ::((!BotonP) && (!Sensor)) -> state=0; semaforoP=G; peatonesP=R; semaforoS=R; peatonesS=G;
                                         printf("Transition from state 0 to state 0\n");		
			fi
		}
                ::(state == 1) -> atomic {
                         state=2; semaforoP=R; peatonesP=G; semaforoS=G; peatonesS=R; next = time + 10;
                                         printf("Transition from state 1 to state 2\n");
                }
                ::(state == 2) -> atomic {
                        if
			::((time >= next)) -> state=3; semaforoS=Y;
                                    printf("Transition from state 2 to state 3\n");
                        ::((time < next)) -> state=2; semaforoP=R; peatonesP=G; semaforoS=G; peatonesS=R; BotonP=0; Sensor=0;
                                    printf("Transition from state 2 to state 2\n");
			fi
                }
                ::(state == 3) -> atomic {
                        state=0; semaforoP=G; peatonesP=R; semaforoS=R; peatonesS=G; time=0;
                                    printf("Transition from state 3 to state 0\n");
                }
	fi;
        printf ("estado = %d, BotonP = %d, Sensor = %d, time =%d, next =%d, semaforoP =%d, semaforoS =%d, peatonesP =%d, peatonesS =%d\n",
                state, BotonP, Sensor, time, next, semaforoP, semaforoS, peatonesP, peatonesS)
	od
}

active proctype entorno(){
	do
	::if
	::BotonP=1;
	::Sensor=1;
	::skip
	fi;
	time=time+1;
	od
	}



