#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define BUFFER_SIZE 8

typedef struct {

} item;

int main(int argc, char *argv[]) {
  item buffer[BUFFER_SIZE];
  int in = 0;
  int out = 0;

  // Producer
  item next_produced;
  while (1) {
    // produce an item in next_produced
    while (((in + 1) % BUFFER_SIZE) == out)
      ;
    // buffer full: do nothing
    buffer[in] = next_produced;
    in = (in + 1) % BUFFER_SIZE;
  }

  // Consumer
  item next_consumed;
  while (1) {
    while (in == out)
      ;
    // buffer empty: do nothing

    next_consumed = buffer[out];
    out = (out + 1) % BUFFER_SIZE;
    // consume the item in next consumed
  }

  return 0;
}
