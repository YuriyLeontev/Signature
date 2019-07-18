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
    std::cout << "invalid parameters\nparam1 = path to src file\nparam2 = path to dst file\nparam3 = size block (Mb) default = 1 Mb" << std::endl;
return 0;
}
