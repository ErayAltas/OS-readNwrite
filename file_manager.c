#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>


// file_manager programının başlangıçta bir thread ve dosya listesi dizisi oluşturması gerekiyor. Bu dizi, file_manager programı tarafından işletilen dosyaların isimlerini saklayacak.
// file_manager programı, file_client ile iletişim kurmak için "file_manager_named_pipe" isimli named pipe'ı kullanacak.
// file_manager programı, file_client tarafından gelen komutları dinleyecek ve ilgili işlemleri gerçekleştirecek. Örneğin, "create" komutu geldiğinde, file_manager programı bir dosya oluşturacak ve dosya listesi dizisine dosya ismini ekleyecek.
// file_manager programı, file_client tarafından gelen "exit" komutunu alınca, file_client ile olan iletişimini keserek thread'i sonlandıracak.
// file_manager programı, her bir işlemden sonra file_client'a işlem durumu hakkında bir response döndürecek.

// GLOBAL VARIABLES
const int thread_count = 5;
const int file_count = 10;

pthread_t tids[thread_count];
char file_list[file_count];

void *status;

int main(int argc, char *argv[])
{

    return 0;
}

void createFile(char *filename) {
  // File_List dizisinde boş olan sıraya dosya ismini ekle
  int i;
  for (i = 0; i < 10; i++) {
    if (strlen(file_list[i]) == 0) {
      strcpy(file_list[i], filename);
      break;
    }
  }

  if (i == 10) {
    printf("File_List is full\n");
    return;
  }

  // Dosyayı sistemde oluştur
  FILE *file = fopen(filename, "w");
  if (file == NULL) {
    perror("fopen failed");
    return;
  }

  if (fclose(file) == EOF) {
    perror("fclose failed");
    return;
  }

  printf("Response: File created\n");
}

void deleteFile(char *filename) {
  // File_List dizisinden dosyayı sil
  int i;
  for (i = 0; i < 10; i++) {
    if (strcmp(file_list[i], filename) == 0) {
      strcpy(file_list[i], "");
      break;
    }
  }

  if (i == 10) {
    printf("File not found in File_List\n");
  }

  printf("Response: File deleted\n");
}




void readFile(char *filename, int rowNumber)
{
    // Dosyayı aç
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        perror("fopen failed");
        return;
    }

    // Dosyadaki ilgili satıra gidin
    if (fseek(file, rowNumber, SEEK_SET) != 0)
    {
        perror("fseek failed");
        fclose(file);
        return;
    }

    // Satırı oku
    char c;
    while ((c = fgetc(file)) != '\n' && c != EOF)
    {
        putchar(c);
    }

    // Dosyayı kapat
    if (fclose(file) == EOF)
    {
        perror("fclose failed");
        return;
    }

    printf("\n");
    printf("Response : File read");
}

void writeFile(char *filename, char *data)
{
    // Dosyayı aç
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        perror("fopen failed");
        return;
    }

    // Veriyi dosyaya yaz
    if (fwrite(data, strlen(data), 1, file) != 1)
    {
        perror("fwrite failed");
        fclose(file);
        return;
    }

    // Dosyayı kapat
    if (fclose(file) == EOF)
    {
        perror("fclose failed");
        return;
    }

    printf("Response: File wrote\n");
}

void exit(int thread_index) {
  // Thread'i sonlandır
  if (pthread_cancel(tids[thread_index]) != 0) {
    perror("pthread_cancel failed");
    return;
  }

  printf("Response: Exit called, Thread destroyed\n");
}
