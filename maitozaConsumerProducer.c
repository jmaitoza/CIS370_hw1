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

  srand(time(0));
  next_produced = rand();

  cbuf->buffer[cbuf->in] = next_produced;
  cbuf->in = (cbuf->in + 1) % BUFFER_SIZE;

  printf("\n%d ", cbuf->buffer[cbuf->in]);
}

void consume(struct Items *cbuf) {
  int next_consumed;

  next_consumed = cbuf->buffer[cbuf->out];
  cbuf->out = (cbuf->out + 1) % BUFFER_SIZE;

  printf("\n%d ", cbuf->buffer[cbuf->out]);
}

int main(int argc, char *argv[]) {
  struct Items cbuf;
  char usrInput;
  for (int i = 0; i < BUFFER_SIZE; i++) {
    cbuf.buffer[i] = NULL;
  }

  cbuf.in = 0;
  cbuf.out = 0;

  while (1) {
    // get inputs for from user
    scanf(" %c", &usrInput);

    // producer
    //  check to see if input is "p", then check again if there is room in the
    //  buffer and produce an item
    if (strcmp(&usrInput, "p") == 0 || strcmp(&usrInput, "P") == 0) {
      if (((cbuf.in + 1) % BUFFER_SIZE) == cbuf.out) {
        printf("\t\t\t<Buffer full>\n");
      } else {
        producer(&cbuf);
      }
    }

    // consumer
    if (strcmp(&usrInput, "c") == 0 || strcmp(&usrInput, "C") == 0) {
      // check to see if buffer is empty
      if (cbuf.in == cbuf.out) {
        printf("\t\t\t<Buffer is empty>\n");
      } else {
        consume(&cbuf);
      }
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
