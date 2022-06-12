ifneq ($(words $(MAKECMDGOALS)),1)
.DEFAULT_GOAL = all
%:
	@$(MAKE) $@ --no-print-directory -rRf $(firstword $(MAKEFILE_LIST))
else
ifndef ECHO
T := $(shell $(MAKE) $(MAKECMDGOALS) --no-print-directory \
      -nrRf $(firstword $(MAKEFILE_LIST)) \
      ECHO="COUNTTHIS" | grep -c "COUNTTHIS")

N := x
C = $(words $N)$(eval N := x $N)
ECHO = echo "`expr " [\`expr $C '*' 100 / $T\`" : '.*\(....\)$$'`%]"
endif

NAME	= semaforo

CC		= gcc

CFLAGS	= -Wall -g

SRCS_DIR = src

SRC	= fsm.c timeval_helper.c main.c semaforo.c interp.c

SRCS =  $(addprefix $(SRCS_DIR)/, $(SRC))

OBJS	= ${SRCS:.c=.o}

INCLUDES = -I ./inc
RM		= rm -f

all: ${NAME}

%o: %c
	@$(ECHO) Compiling $@
	@${CC} ${CFLAGS} -c $< -o ${<:.c=.o} ${INCLUDES}

$(NAME) : ${OBJS}
	@$(ECHO) Linking $@
	@${CC} ${CFLAGS} ${OBJS} -o ${NAME}

clean:
	@${RM} ${OBJS}

fclean:		clean
	@${RM} ${NAME}

re:		fclean all

.PHONY:		clean re fclean all

endif
