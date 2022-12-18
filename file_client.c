#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h> /* Semaphore */

// C program to implement one side of FIFO
// This side writes first, then reads
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

// file_client programı, "file_manager_named_pipe" isimli named pipe'ı kullanarak file_manager programı ile iletişim kuracak.

// file_client programı, kullanıcıdan bir komut alacak ve bu komutu file_manager programına gönderecek. Örneğin, "create file.txt" komutu geldiğinde, file_client programı file_manager programına "create" komutunu gönderecek ve dosya ismini de gönderecek.

// file_client programı, file_manager programından gelen response'ları ekrana yazdıracak.

// file_client programı, "exit" komutu geldiğinde iletişimi kesecek ve programı sonlandıracak.

void *listenPipe()
{
    int fd;
    char *myfifo = "/tmp/myfifo";
    mkfifo(myfifo, 0666);
    char cevap[80], komut[80];
    while (1)
    {

        fd = open(myfifo, O_WRONLY);
        fgets(komut, 80, stdin);
        write(fd, komut, strlen(komut) + 1);
        close(fd);

        fd = open(myfifo, O_RDONLY);
        read(fd, cevap, strlen(cevap) + 1);
        printf("cevap: %s\n", cevap);
        close(fd);
    }
}



int main(int argc, char *argv[])
{
    int threadCount = 5;
    int file_count = 10;
    pthread_t tids[threadCount];
    FILE *file_list[file_count];
    void *status;

    for (int var = 0; var < threadCount; ++var)
    {
        pthread_join(tids[var], &status);
    }

    return 0;
}