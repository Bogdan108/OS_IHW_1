// message.h
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdio.h>
#include <time.h>


// структура сообщения, помещаемого в разделяемую память
typedef struct {
    int letter;
    int number;
} message_t;

