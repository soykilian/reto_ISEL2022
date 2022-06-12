ltl p1 {([](presencia -> (<>luz))) && 
([] (((T) && ((!presencia)W(!luz))) -> (<> (!luz))))}

/*INPUTS*/
int presencia = 0;
int T = 0;

/*OUTPUTS*/ 
int luz = 0;

/*STATES*/ 
mtype = {OFF,ON}
byte estado;

active proctype luz_fsm () {
	
	T = 0;
	luz = 0;
	estado = OFF;
	do
	:: if
	::	(estado == OFF) -> atomic {
		if 
		:: (presencia==1) -> estado = ON; T=0; presencia=0; luz=1; printf("Se ha detectado presencia, pasamos a ON\n");
		fi;
	}
		::	(estado == ON) -> atomic {
		if 
		:: (presencia==1) ->	estado=ON; presencia = 0; T = 0; luz=1; 
		:: ((presencia==0) && (T==1)) -> estado=OFF; luz=0;printf("No presencia y tiempo, pasamos a OFF \n");
		fi;
	}
	fi;

    printf("STATE %e\n", estado);
    // printf("T %d, luz %d, presencia: %d \n", T, luz, presencia);
    printf("\n----------------------------\n");

	od
}

active proctype entorno () {

	do
    :: presencia = 1;
    :: T = 1;
	:: skip -> skip
	od

}
