#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#define BUFFER_SIZE 8

struct Items {
  int buffer[BUFFER_SIZE];
  int in;
  int out;
};

void producer(struct Items *cbuf) {
  int next_produced;

  srand(time(NULL));
  next_produced = rand() % 100;

  cbuf->buffer[cbuf->in] = next_produced;
  printf("'%d' was produced ", cbuf->buffer[cbuf->in]);
  cbuf->in = (cbuf->in + 1) % BUFFER_SIZE;
}

void consume(struct Items *cbuf) {
  int next_consumed;

  next_consumed = cbuf->buffer[cbuf->out];
  printf("'%d' was consumed ", cbuf->buffer[cbuf->out]);
  cbuf->buffer[cbuf->out] =
      NULL; // this is to make the print function not print the consumed items
  cbuf->out = (cbuf->out + 1) % BUFFER_SIZE;
}

void bufPrinter(struct Items *cbuf) {
  printf("\nBuffer Contents: ");
  for (int i = 0; i < BUFFER_SIZE; i++) {
    if (cbuf->buffer[i] !=
        NULL) { // assures program wont print '0' for empty cells of buffer
      printf("%d ", cbuf->buffer[i]);
    }
  }
  printf("\n");
}

int main(int argc, char *argv[]) {
  struct Items cbuf;

  char usrInput;
  for (int i = 0; i < BUFFER_SIZE; i++) {
    cbuf.buffer[i] = NULL; // initialize buffer with space characters
  }

  cbuf.in = 0;
  cbuf.out = 0;

  while (1) {
    // get inputs for from user
    scanf(" %c", &usrInput);

    // producer
    //  check to see if input is "p", then check again if there is room in the
    //  buffer and produce an item
    if (usrInput == 112 || usrInput == 80) {
      if (((cbuf.in + 1) % BUFFER_SIZE) == cbuf.out) {
        printf("\t\t\t<Buffer full>\n");
      } else {
        producer(&cbuf);
        bufPrinter(&cbuf);
      }
    }
    // consumer
    else if (usrInput == 99 || usrInput == 67) {
      // check to see if buffer is empty
      if (cbuf.in == cbuf.out) {
        printf("\t\t\t<Buffer is empty>\n");
      } else {
        consume(&cbuf);
        bufPrinter(&cbuf);
      }
    } else {
      printf("\nExiting program...\n");
      exit(0);
    }
  }
  // Producer
  // item next_produced;
  // while (1) {
  //   // produce an item in next_produced
  //   while (((in + 1) % BUFFER_SIZE) == out)
  //     ;
  //   // buffer full: do nothing
  //   buffer[in] = next_produced;
  //   in = (in + 1) % BUFFER_SIZE;
  // }

  // // Consumer
  // item next_consumed;
  // while (1) {
  //   while (in == out)
  //     ;
  //   // buffer empty: do nothing

  //   next_consumed = buffer[out];
  //   out = (out + 1) % BUFFER_SIZE;
  // consume the item in next consumed

  return 0;
}
