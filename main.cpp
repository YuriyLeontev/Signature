#include <cstdlib>
#include "director.h"

#define MB 1048576 

int main (int argc, char *argv[]){
  Director director;

  if (argc == 4){
    int size = atoi(argv[3]);
    if (size && size != __INT_MAX__)
      director.start(argv[1], argv[2],size * MB);
    else
      director.start(argv[1], argv[2]);
  }
  else if (argc == 3)
    director.start(argv[1], argv[2]);
  else
    return -1;

return 0;
}
