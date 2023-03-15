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
    char buffer[200];
    size_t size = 199, read_bytes;
    int letters = 0, numbers = 0;
    int input, output, read_pipe, write_pipe;
    char write_name[] = "write.fifo";
    char read_name[] = "read.fifo";
    message_t buffer_struct;
    result_t result_struct;

    if (argc != 3)
    {
        printf("Неправильное количество аргументов командной строки\n");
        exit(-1);
    }

    (void)umask(0);
    mknod(write_name, S_IFIFO | 0666, 0);
    mknod(read_name, S_IFIFO | 0666, 0);

    printf("Работает в процессе для чтения текста\n");

    // открываю входной файл для чтения
    if ((input = open(argv[1], O_RDONLY, 0666)) < 0)
    {
        printf("Can\'t open input file\n");
        exit(-1);
    }
    // считываю текст в цикле и передаю в процесс для анализа, далее получаю от анализа результат по переданному тексту
    do
    {
        read_bytes = read(input, buffer, size);

        if (read_bytes == -1)
        {
            printf("Can\'t write this file\n");
            exit(-1);
        }

        buffer[read_bytes] = '\0';
        if ((write_pipe = open(write_name, O_WRONLY)) < 0)
        {
            printf("Can\'t open FIFO for writting\n");
            exit(-1);
        }

        // копирую сообщение из входного файла в буфер для передачи
        strcpy(buffer_struct.buffer, buffer);
        buffer_struct.flag = 0;
        size = write(write_pipe, &buffer_struct, sizeof(message_t));

        if (size < 0)
        {
            printf("Can\'t write all string to pipe\n");
            exit(-1);
        }

        if (close(write_pipe) < 0)
        {
            printf("parent: Can\'t close writing side of pipe\n");
            exit(-1);
        }

        if ((read_pipe = open(read_name, O_RDONLY)) < 0)
        {
            printf("Can\'t open FIFO for reading\n");
            exit(-1);
        }

        // считываю результат работы процесса для анализа
        size = read(read_pipe, &result_struct, sizeof(result_struct));

        if (size < 0)
        {
            printf("Can\'t read string from pipe\n");
            exit(-1);
        }

        if (close(read_pipe) < 0)
        {
            printf("child: Can\'t close pipe\n");
            exit(-1);
        }

        numbers += result_struct.number;
        letters += result_struct.letter;

    } while (read_bytes > 0);

    if ((write_pipe = open(write_name, O_WRONLY)) < 0)
    {
        printf("Can\'t open FIFO for writting\n");
        exit(-1);
    }
    // передаю сообщение процессу анализа, что нужно прекратить работу
    buffer_struct.flag = STOP_ANALYSE;
    size = write(write_pipe, &buffer_struct, sizeof(message_t));

    if (size < 0)
    {
        printf("Can\'t write all string to pipe\n");
        exit(-1);
    }

    if (close(write_pipe) < 0)
    {
        printf("parent: Can\'t close writing side of pipe\n");
        exit(-1);
    }

    if (close(input) < 0)
    {
        printf("Can\'t close input file\n");
    }

    // открываю файл для записи
    if ((output = open(argv[2], O_WRONLY, 0666)) < 0)
    {
        printf("Can\'t open output file\n");
        exit(-1);
    }

    //  сначала подготоавливаю строку с результатом, затем пишут его в выходной файл
    char buffer_for_output[200];
    sprintf(buffer_for_output, "Результат работы программы: \n кол-во цифр:%d \n кол-во букв:%d\n", numbers, letters);

    size = write(output, buffer_for_output, strlen(buffer_for_output));

    if (size < 0)
    {
        printf("Can\'t write all string\n");
        exit(-1);
    }

    if (close(output) < 0)
    {
        printf("Can\'t close output file\n");
    }

    printf("Конец работы в читателе и писателе\n");
    return 0;
}