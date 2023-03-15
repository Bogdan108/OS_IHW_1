#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include "message.h"

int main(int argc, char *argv[])
{
    char buffer[5001];
    size_t size;
    int input, output, read_pipe, write_pipe;
    char write_name[] = "write.fifo";
    char read_name[] = "read.fifo";
    message_t result_struct;

    printf("Работает в процессе для анализа текста\n");

    // считываю данные, переданные для анализа
    if ((write_pipe = open(write_name, O_RDONLY)) < 0)
    {
        printf("Can\'t open FIFO for reading\n");
        exit(-1);
    }
    size = read(write_pipe, buffer, sizeof(buffer));

    if (size < 0)
    {
        printf("Can\'t read string from pipe\n");
        exit(-1);
    }

    if (close(write_pipe) < 0)
    {
        printf("child: Can\'t close pipe\n");
        exit(-1);
    }
    // анализ текста
    int i = 0;
    result_struct.number = 0;
    result_struct.letter = 0;

    while (buffer[i] != '\0' && i < 5001)
    {
        if (buffer[i] >= '0' && buffer[i] <= '9')
        {
            result_struct.number++;
        }
        if (buffer[i] >= 'A' && buffer[i] <= 'z')
        {
            result_struct.letter++;
        }
        i++;
    }

    // передаю записанные данные в канал
    if ((read_pipe = open(read_name, O_WRONLY)) < 0)
    {
        printf("Can\'t open FIFO for reading\n");
        exit(-1);
    }

    size = write(read_pipe, &result_struct, sizeof(result_struct));

    if (size < 0)
    {
        printf("Can\'t write all string to pipe\n");
        exit(-1);
    }

    if (close(read_pipe) < 0)
    {
        printf("child: Can\'t close pipe\n");
        exit(-1);
    }
    printf("Конец работы в анализе\n");

    return 0;
}