#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

// file_manager programının başlangıçta bir thread ve dosya listesi dizisi oluşturması gerekiyor. Bu dizi, file_manager programı tarafından işletilen dosyaların isimlerini saklayacak.
// file_manager programı, file_client ile iletişim kurmak için "file_manager_named_pipe" isimli named pipe'ı kullanacak.
// file_manager programı, file_client tarafından gelen komutları dinleyecek ve ilgili işlemleri gerçekleştirecek. Örneğin, "create" komutu geldiğinde, file_manager programı bir dosya oluşturacak ve dosya listesi dizisine dosya ismini ekleyecek.
// file_manager programı, file_client tarafından gelen "exit" komutunu alınca, file_client ile olan iletişimini keserek thread'i sonlandıracak.
// file_manager programı, her bir işlemden sonra file_client'a işlem durumu hakkında bir response döndürecek.

//GLOBAL VARIABLES
const int thread_count = 5;
const int file_count = 10;

pthread_t tids[thread_count];
char file_list[file_count];

void *status;

int main(int argc, char *argv[])
{
    
    return 0;
}


void createFile()
{
    // File_List’te dosya ismi yoksa boş olan sıraya dosya ismini ekler ve sistemde dosyayı oluşturur.
    FILE *f;

    // Dosya oluştur
    if ((f = fopen("file.txt", "w")) == NULL)
    {
        perror("fopen");
        return 1;
    }
}

void deleteFile()
{
    // File_List’te dosya ismi varsa sistemden ve File_List’ten(indexten) dosyayı siler.
}

void readFile()
{
    //     File_List’te dosya ismi varsa sistemden ilgili indexteki lineni dosyadan okuyarak ilgili
    // File_Client’a gönderir
}

void writeFile()
{
}

void exit()
{
    //     Ilgili file_client threadini bitirir, iletişim kopar.
    // o Exit komutu gelene kadar thred dinleme işlemi devam etmektedir.
}
