ltl p1 {([](((estado==DESARMADA)) -> (!LED && !buzzer))) &&
([](((estado==DESARMADA) && codigo_ok) -> <>(estado==ARMADA))) &&
([](( (estado==ALERTA) && (codigo_ok)) -> <>(estado==DESARMADA)))}

/*INPUTS*/
int presencia = 0;
int codigo_ok = 0;

/*OUTPUTS*/ 
int LED = 0;
int buzzer = 0;

/*STATES*/
mtype = {DESARMADA,ARMADA,ALERTA}
byte estado;

active proctype alarma_fsm () {

	estado = DESARMADA;
	LED = 0;
	buzzer = 0;
	do
    ::if
	::	(estado == DESARMADA) -> atomic {
		if 
		:: (codigo_ok==1) -> estado = ARMADA; codigo_ok = 0; LED = 0; buzzer = 0; printf("CODIGO_OK pasamos a ARMADA\n");
		fi;
	}
	::	(estado == ARMADA) -> atomic {
		if 
		:: (codigo_ok==1) -> estado = DESARMADA; codigo_ok = 0;  LED = 0; buzzer = 0; printf("CODIGO_OK pasamos a DESARMADA\n");
		:: (presencia==1) -> estado = ALERTA; presencia = 0; LED = 1; buzzer = 1; printf("PRESENCIA detectada, pasamos a ALERTA\n");
        :: (presencia==0) -> estado =ARMADA; printf("Se mantiene ARMADA\n")
		fi;
	}
	::	(estado == ALERTA) -> atomic {
		if 
		:: (codigo_ok==1) -> estado = DESARMADA; codigo_ok = 0;  LED = 0; buzzer = 0; printf("CODIGO_OK pasamos a DESARMADA\n");
		fi;
	}
    fi;
    printf("STATE: %e,LED: %d, buzzer: %d, codigo_OK: %d\n", estado,LED, buzzer, codigo_ok);
    printf("\n----------------------------\n");
	od
}

active proctype entorno () {
	
	do
    :: presencia = 1;
    :: codigo_ok = 1;
    :: skip -> skip

	od
    
}
