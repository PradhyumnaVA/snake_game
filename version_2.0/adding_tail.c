#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>


int main(){
  typedef struct {
    char bone[10];
    int p_x;
    int p_y;
    char dir;
  }data;
  int x=10;
  int y=3;
  data *spine = malloc(10*sizeof(data)); 

  // this is the tail initialisation part - ignore it for now
  for(int i=0; i<5; i++){
    spine[i].p_y = y;
    spine[i].dir = 'd';
    if(i!=0){
      sprintf(spine[i].bone, "\033[%d;%dHo", y, x-i);
      spine[i].p_x = x-i;
    } else{
      sprintf(spine[i].bone, "\033[%d;%dH>", y, x);
      spine[i].p_x = x;
    }
  }
  //////////////////////////////////////////
  
  // important variables //
  char head = '>';

  // this is required for pushing the dir value to the next spine in the tail at each movement
  int turn_cnt = 0;

  // total number of spines 
  int num_spines = 5;

for(int j=0; j<10; j++){
  // clear screen
  printf("\033[2J");

  turn_cnt = num_spines -1;

  // testing the turns
  if(j==2){spine[0].dir = 's';}
  else if(j==4){spine[0].dir = 'd';}
  else if(j==6){spine[0].dir = 'w';}
  //////////////////////////////////////////
  
  for(int i=0; i<num_spines; i++){
    // dont worry about the head being assigned value in each iteration, cause at i=0 the head value will be printed into spine[0] so subsequent assignments of head wont affect the first spine
    switch(spine[i].dir){
      case 'w': spine[i].p_y--;
                head = '^';
                break;
      case 's': spine[i].p_y++;
                head = 'v';
                break;
      case 'a': spine[i].p_x--;
                head = '<';
                break;
      case 'd': spine[i].p_x++;
                head = '>';
                break;
      default : break;
    }

    // this is where spines are made - coordinate based
    if(i!=0){
      sprintf(spine[i].bone, "\033[%d;%dHo", spine[i].p_y, spine[i].p_x);
    } else{
      sprintf(spine[i].bone, "\033[%d;%dH%c", spine[i].p_y, spine[i].p_x, head);
    }

  }
    // printing the whole tail
    for(int cnt=0; cnt<num_spines; cnt++){
      printf("%s",spine[cnt].bone);

      /* printf("\033[1;1H%d",j); */
      /* printf("\033[1;5H%c",spine[0].dir); */
      /* printf("\033[1;19Hspine1=%c",spine[1].dir); */
      /* printf("\033[1;30H%c",spine[4].dir); */
      fflush(stdout);
    }

  // after each movement, each spine-dir is given the dir of its previous spine, this is so that each spine is aware of the direction in which its moving
  while(turn_cnt>0){
    spine[turn_cnt].dir = spine[turn_cnt-1].dir;
    turn_cnt--;
  }

  if(j==5){
    // this needs to go in the position change function in snake game - this is for adding next spine to the tail
    switch(spine[num_spines-1].dir){
      case 'w': spine[num_spines].p_y=spine[num_spines-1].p_y+1;
                spine[num_spines].p_x=spine[num_spines-1].p_x;
                break;
      case 's': spine[num_spines].p_y=spine[num_spines-1].p_y-1;
                spine[num_spines].p_x=spine[num_spines-1].p_x;
                break;
      case 'a': spine[num_spines].p_y=spine[num_spines-1].p_y;
                spine[num_spines].p_x=spine[num_spines-1].p_x+1;
                break;
      case 'd': spine[num_spines].p_y=spine[num_spines-1].p_y;
                spine[num_spines].p_x=spine[num_spines-1].p_x-1;
                break;
      default : break;
    }
    spine[num_spines].dir=spine[num_spines-1].dir;
    num_spines++;
  }
    usleep(500000);
}
  printf("\n \n");
  return 0;
}
