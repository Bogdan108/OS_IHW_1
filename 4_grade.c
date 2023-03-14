#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include "message.h"

int main(int argc, char *argv[])
{
    uid_t pid, ppid, chpid = -1;
    int write_pipe[2], read_pipe[2];
    char buffer[5001];
    size_t size;
    int input, output;
    message_t result_struct;

    if (argc != 3)
    {
        printf("Неправильное количество аргументов командной строки\n");
        exit(-1);
    }

    pipe(write_pipe);

    //  создаю процесс для анализа текста
    chpid = fork();
    if (chpid)
    {
        printf("Работает в процессе для чтения текста\n");
        if (close(write_pipe[0]) < 0)
        {
            printf("parent: Can\'t close reading side of pipe\n");
            exit(-1);
        }
        // открываю входной файл для чтения
        if ((input = open(argv[1], O_RDONLY, 0666)) < 0)
        {
            printf("Can\'t open input file\n");
            exit(-1);
        }
        // считываю текст
        size = read(input, buffer, sizeof(buffer));
        buffer[size] = '\0';

        if (size < 0)
        {
            printf("Can\'t write all string\n");
            exit(-1);
        }

        if (close(input) < 0)
        {
            printf("Can\'t close input file\n");
        }

        // записываю текст в канал
        size = write(write_pipe[1], buffer, strlen(buffer));

        if (size != strlen(buffer))
        {
            printf("Can\'t write all string to pipe\n");
            exit(-1);
        }

        if (close(write_pipe[1]) < 0)
        {
            printf("parent: Can\'t close writing side of pipe\n");
            exit(-1);
        }
        printf("Конец работы в читателе\n");
    }
    else
    {
        if (chpid == -1)
        {
            printf("Не удалось запустить новый прпоцесс\n");
            exit(-1);
        }

        // создаю процесс для вывода текста в файл
        pipe(read_pipe);
        chpid = fork();

        if (chpid)
        {
            printf("Работает в процессе для анализа текста\n");
            if (close(write_pipe[1]) < 0)
            {
                printf("child: Can\'t close writing side of pipe\n");
                exit(-1);
            }

            // считываю данные, переданные для анализа
            size = read(write_pipe[0], buffer, sizeof(buffer));

            if (size < 0)
            {
                printf("Can\'t read string from pipe\n");
                exit(-1);
            }

            if (close(write_pipe[0]) < 0)
            {
                printf("child: Can\'t close reading side of pipe\n");
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

            if (close(read_pipe[0]) < 0)
            {
                printf("child: Can\'t close reading side of pipe\n");
                exit(-1);
            }
            // передаю записанные данные в канал
            size = write(read_pipe[1], &result_struct, sizeof(result_struct));

            if (size != sizeof(result_struct))
            {
                printf("Can\'t write all string to pipe\n");
                exit(-1);
            }

            if (close(read_pipe[1]) < 0)
            {
                printf("child: Can\'t close writing side of pipe\n");
                exit(-1);
            }
            printf("Конец работы в анализе\n");
        }
        else
        {
            if (chpid == -1)
            {
                printf("Не удалось запустить новый прпоцесс\n");
                exit(-1);
            }

            printf("Работает в процессе для вывода текста\n");

            if (close(read_pipe[1]) < 0)
            {
                printf("child: Can\'t close writing side of pipe\n");
                exit(-1);
            }

            size = read(read_pipe[0], &result_struct, sizeof(result_struct));
            if (size < 0)
            {
                printf("Can\'t read string from pipe\n");
                exit(-1);
            }

            if (close(read_pipe[0]) < 0)
            {
                printf("child: Can\'t close reading side of pipe\n");
                exit(-1);
            }

            // открываю файл для записи
            if ((output = open(argv[2], O_WRONLY, 0666)) < 0)
            {
                printf("Can\'t open output file\n");
                exit(-1);
            }

            //  сначала подготоавливаю строку с результатом, затем пишут его в выходной файл
            char buffer_for_output[50001];
            sprintf(buffer_for_output, "Результат работы программы: \n кол-во цифр:%d \n кол-во букв:%d\n", result_struct.number, result_struct.letter);
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
            printf("Конец работы в писателе\n");
        }
    }
    return 0;
}
