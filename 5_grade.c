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
    uid_t pid, ppid, chpid = -1;
    char buffer[5001];
    size_t size;
    int input, output, read_pipe, write_pipe;
    char write_name[] = "write.fifo";
    char read_name[] = "read.fifo";
    message_t result_struct;

    if (argc != 3)
    {
        printf("Неправильное количество аргументов командной строки\n");
        exit(-1);
    }
    (void)umask(0);
    mknod(write_name, S_IFIFO | 0666, 0);

    //  создаю процесс для анализа текста
    chpid = fork();
    if (chpid)
    {
        printf("Работает в процессе для чтения текста\n");

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
            printf("Can\'t read all string\n");
            exit(-1);
        }

        if (close(input) < 0)
        {
            printf("Can\'t close input file\n");
        }

        // записываю текст в канал
        if ((write_pipe = open(write_name, O_WRONLY)) < 0)
        {
            printf("Can\'t open FIFO for writting\n");
            exit(-1);
        }

        size = write(write_pipe, buffer, strlen(buffer));

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
        mknod(read_name, S_IFIFO | 0666, 0);
        chpid = fork();

        if (chpid)
        {
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
        }
        else
        {
            if (chpid == -1)
            {
                printf("Не удалось запустить новый прпоцесс\n");
                exit(-1);
            }

            printf("Работает в процессе для вывода текста\n");

            if ((read_pipe = open(read_name, O_RDONLY)) < 0)
            {
                printf("Can\'t open FIFO for reading\n");
                exit(-1);
            } 

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

            // открываю файл для записи
            if ((output = open(argv[2], O_WRONLY, 0666)) < 0)
            {
                printf("Can\'t open output file\n");
                exit(-1);
            }

            //  сначала подготоавливаю строку с результатом, затем пишут его в выходной файл
            char buffer_for_output[50001];
            sprintf(buffer_for_output, "Результат работы программы: \n кол-во цифр:%d \n кол-во букв:%d\n", result_struct.number, result_struct.letter);
            buffer_for_output[5000] = '\0';
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
