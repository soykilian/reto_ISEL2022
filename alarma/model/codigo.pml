ltl p1{([]((comprueba_codigo) && (!pulsador W T10) -> <>(codigo_ok))) &&
([]((!comprueba_codigo) && (!pulsador W T10) -> <>(!codigo_ok)))}

/*INPUTS*/
int pulsador = 0;
int T1 = 0; 
int T10 = 0; 

/*OUTPUTS*/ 
int codigo_ok = 0;

/*STATES*/ 
mtype = {IDLE,COUNT,WAIT}
byte estado;

byte codigo_correcto[3] = {3, 2, 0};
byte codigo[3] = {0,0,0};
int i;
int comprueba_codigo = 0;
int count = 0;
int j = 0;

active proctype codigo_fsm () {

	estado = IDLE;
	codigo_ok = 0;
	count = 0;
	j = 0;

	do
    ::if
	::	(estado == IDLE) -> atomic {
		if 
		:: (pulsador==1) -> estado = COUNT; pulsador = 0; count++; T1 = 0; T10 = 0; j = 0; codigo_ok=0; printf("Pulsador pulsado, pasamos a COUNT\n"); printf("COUNT: %d\n", count);
		fi;
	}
	::	(estado == COUNT) -> atomic {
		if 
		:: (pulsador==1) -> pulsador = 0; estado = COUNT; count++; T1 = 0; T10 = 0; printf("COUNT: %d\n", count);
		:: ((T1==1) && (count<=10)) -> estado = WAIT; pulsador = 0; T1 = 0;	T10 = 0; codigo[j]=count; count=0; printf("Tiempo ha pasado, pasamos a WAIT\n"); printf("Codigo introducido: [%d,%d,%d] \n", codigo[0],codigo[1],codigo[2]);
        :: (count>10) -> estado=IDLE; count=0; T1=0; T10=0; pulsador=0;
        fi;
	}
	::	(estado == WAIT) -> atomic {
		if 
		:: ((pulsador==1) && (j < 2)) -> estado = COUNT; pulsador = 0; count++; T1 = 0; T10 = 0; j++; printf("Pulsador y digitos disponibles, pasamos a COUNT\n"); printf("COUNT: %d\n", count);
		:: ((j == 2) && T10)-> estado = IDLE; printf("Pasamos a IDLE\n"); pulsador = 0; i = 0; comprueba_codigo = 1; T1 = 0; T10 = 0; j = 0; count = 0;			
				do 
				:: (i < 3) -> 
					comprueba_codigo = (comprueba_codigo && (codigo[i] == codigo_correcto[i]));
					codigo[i] = 0;
					i++;
				:: else -> break
				od;
				if
				:: comprueba_codigo -> codigo_ok = 1; printf("ACERTASTE\n");
				:: !comprueba_codigo -> codigo_ok = 0; printf("FALLASTE\n");
				fi;
		fi;
	}
    fi;
    printf("STATE: %e, COUNT: %d, codigo_ok: %d, digito=%d, pulsador: %d\n", estado, count, codigo_ok, j, pulsador);
    printf("\n----------------------------------\n");

	od;

}


active proctype entorno () {
	
	do
    :: pulsador = 1
    :: T1 = 1
    :: T10 = 1
    :: skip -> skip
	od

}
