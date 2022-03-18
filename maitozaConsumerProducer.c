#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#define BUFFER_SIZE 8

struct Items {
  char buffer[BUFFER_SIZE];
  int in;
  int out;
};

void producer(struct Items *cbuf) {
  int next_produced;

  srand(time(0));
  next_produced = rand();

  cbuf->buffer[cbuf->in] = next_produced;
  cbuf->in = (cbuf->in + 1) % BUFFER_SIZE;
  // produce an item in next_produced
  //  while (((circ_buffer->in + 1) % BUFFER_SIZE) == circ_buffer->out) {
  //    printf("<Buffer Full>");
}

void consume(struct Items *cbuf) {
  int next_consumed;

  next_consumed = cbuf->buffer[cbuf->out];
  cbuf->out = (cbuf->out + 1) % BUFFER_SIZE;
}

int main(int argc, char *argv[]) {
  struct Items cbuf;
  for (int i = 0; i < BUFFER_SIZE; i++) {
    cbuf.buffer[i] = NULL;
  }

  cbuf.in = 0;
  cbuf.out = 0;

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
