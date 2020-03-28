#include<stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <strings.h>
#include <assert.h>
#include <unistd.h>

typedef struct user_s {
  uint32_t id;
  char* name;
  char* email;
} User;

int main() {
  User antonio = {
    .id = 1,
    .name = "Antonio Viggiano",
    .email = "antonio@real2u.com.br"
  };
  User caio = {
    .id = 2,
    .name = "Caio Jahara",
    .email = "caio@real2u.com.br"
  };

  size_t antonio_name_length = strlen(antonio.name);
  size_t antonio_email_length = strlen(antonio.email);
  size_t caio_name_length = strlen(caio.name);
  size_t caio_email_length = strlen(caio.email);

  size_t size = 
    sizeof(antonio.id) + 
    + sizeof(uint32_t) + antonio_name_length + 
    + sizeof(uint32_t) + antonio_email_length +

    sizeof(antonio.id) + 
    + sizeof(uint32_t) + caio_name_length + 
    + sizeof(uint32_t) + caio_email_length
  ;
  void* data = malloc(size);
  size_t end = 0;
  memcpy(data + end, &antonio.id, sizeof(antonio.id));
  end += sizeof(antonio.id);
  memcpy(data + end, &antonio_name_length, sizeof(uint32_t));
  end += sizeof(uint32_t);
  memcpy(data + end, antonio.name, antonio_name_length);
  end += antonio_name_length;
  memcpy(data + end, &antonio_email_length, sizeof(uint32_t));
  end += sizeof(uint32_t);
  memcpy(data + end, antonio.email, antonio_email_length);
  end += antonio_email_length;


  memcpy(data + end, &caio.id, sizeof(caio.id));
  end += sizeof(caio.id);
  memcpy(data + end, &caio_name_length, sizeof(uint32_t));
  end += sizeof(uint32_t);
  memcpy(data + end, caio.name, caio_name_length);
  end += caio_name_length;
  memcpy(data + end, &caio_email_length, sizeof(uint32_t));
  end += sizeof(uint32_t);
  memcpy(data + end, caio.email, caio_email_length);
  end += caio_email_length;

  assert(end == size);

 
  
  int fd = open("database.bin", O_WRONLY | O_CREAT);
  write(fd, data, size);
  close(fd);
  return 0;  
}    
