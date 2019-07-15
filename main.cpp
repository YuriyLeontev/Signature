#include <cstdlib>
#include "director.h"


int main (int argc, char *argv[]){
  Director director;

  if (argc == 4){
    uint size = atoi(argv[3]);
    if (size && size != __UINT16_MAX__)
      director.start(argv[1], argv[2],size);
    else
      director.start(argv[1], argv[2]);
  }
  else if (argc == 3)
    director.start(argv[1], argv[2]);
  else
    return -1;

return 0;
}
