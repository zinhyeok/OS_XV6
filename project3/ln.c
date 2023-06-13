#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{
  if(argc != 4){
    printf(2, "Usage: ln -option old new\n");
    exit();
  }
  //hardllink
  if(strcmp(argv[1], "-h")){
    if(link(argv[2], argv[3]) < 0){
      printf(2, "hard link %s %s: failed\n", argv[2], argv[3]);
    exit();
    }
  }
  //softlink
  if(strcmp(argv[1], "-s")){
    if(symlink(argv[2], argv[3]) < 0){
      printf(2, "soft link %s %s: failed\n", argv[2], argv[3]);
    exit();
    }
  }
  else{
    printf(2, "Usage: option should be -h or -s \n");
    exit();
  }
}
