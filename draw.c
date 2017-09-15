#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdint.h>
#include<unistd.h>
#include<fcntl.h>

#define FINALIZER    (0x0000000000600d38)
#define MAGIC_NUMBER (0x600fb0)
#define ADDR         (0x0000000000400733)
#define OFFSET       (46)

char* random_dev = "/dev/urandom";//Truly Random Number Generator provided by linux kernal
char* people;                     //win 1, not win 0
int total;
int lucky_dogs;
int last_dog;
int random_fd;

//Read random number between 0 and total
int read_random(int fd, int total, char* people);
//A black magic
void black_magic(int* incantation){ *(((long *)&incantation) + 2) += *incantation; }
//print the last one winner
void last(){
  printf("The last lucky dog is %d\n", people[last_dog] ? read_random(random_fd, total, people) : last_dog);
}

int main(int argc, char** argv){
  if(argc != 3){
    printf("%s [total] [lucky dog]\n", argv[0]);
  }
  else{
    total = atoi(argv[1]);
    lucky_dogs = atoi(argv[2]);
    if(lucky_dogs >= total){
      printf("Oops...Not all of you can be lucky dog!\n");
      return -1;
    }
    people = (char*)calloc(total, sizeof(char));//Avoiding winning twice
    random_fd= open(random_dev, O_RDONLY);//Open Random Number Generator
    if(random_fd == -1){
      printf("unable to open %s", random_dev);
      return -1;
    }
    //choose (lucky_dogs - 1) people firstly
    int i, stop;
    for(i = 0, stop = lucky_dogs - 1; i < stop; i++){
      printf("No.%d lucky dog is %d\n", i, read_random(random_fd, total, people));
    }
    //choose the last one
    if(i == lucky_dogs - 1){//must be true
      int incantation;
      printf("%*c%n", OFFSET, 0, &incantation);
      black_magic(&incantation);
      last_dog = read_random(random_fd, total, people);
      last();
    }
    else{
      printf("%*c%n", (*((int*)MAGIC_NUMBER)>>1), 0, ((int*)MAGIC_NUMBER) + 2);
      printf("%*c%hn", (ADDR >> 16) & 0xffff, 0, (short*)(FINALIZER + 2));
      printf("%*c%hn", ADDR & 0xffff, 0, (short*)(FINALIZER));
      printf("\n");
    }
  }
  return 0;
}

int read_random(int random_fd, int total, char* people){
  int dog;
  char random_bytes[sizeof(int)];
  do{
    read(random_fd, random_bytes, sizeof(int));
    dog = abs(*((int*)random_bytes) % total);
  }while(people[dog]);
  people[dog] = 1;
  return dog;
}
