// message.h
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdio.h>
#include <time.h>

// коды сообщений
#define CAN_ANALYSE  0     // сообщение о том, что процесс анализа может начать работу
#define STOP_ANALYSE 1     // сообщение о том, что процесс анализа должен закончить работу


// структура сообщения, помещаемого в канал
typedef struct {
    char buffer[200];
    int flag;
} message_t;

typedef struct {
    int letter;
    int number;
} result_t;

