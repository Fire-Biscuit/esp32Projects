CC = gcc
CROSS_COMPILE =

DEFINES = #-DTARGET_${BLUEBOT_TARGET} -DBOARD_${BLUEBOT_BOARD} ${DDEBUG}
OPTIMIZATION = -O3

CFLAGS = -Wall -Werror ${DEFINES} -g ${OPTIMIZATION} #-pthread
LDLIBS = #-pthread -lrt
LDFLAGS =

APP = main
OBJS = main.o utilities.o periodic_tasks.o

all: $(APP)

$(APP): $(OBJS)
	${CROSS_COMPILE}${CC} ${CFLAGS} ${OBJS} ${LDFLAGS} ${LDLIBS} -o ${APP}

main.o: main.c
	${CROSS_COMPILE}${CC} ${CFLAGS} -c main.c

utilities.o: utilities.c
	${CROSS_COMPILE}${CC} ${CFLAGS} -c utilities.c

periodic_tasks.o: periodic_tasks.c
	${CROSS_COMPILE}${CC} ${CFLAGS} -c periodic_tasks.c

clean:
	rm -f *.d *.o $(APP) *~
