#include "s_header.h"

coord *move(coord *ip_coord, char input_dir, int len_tail, int interval_cnt){
	/* coord *data = ip_coord; */
  coord *spine = ip_coord;
	int i;
	 
  // variable for head character type
  char head;
  // total number of spines 
  int num_spines = len_tail;
  // this is required for pushing the dir value to the next spine in the tail at each movement
  /* int turn_cnt = num_spines -1; */
  int turn_cnt = num_spines;

  switch(input_dir){
    case 'w': 
      if(spine[0].dir != 's'){
        spine[0].dir=input_dir;
      } 
      /* else { */
      /*   spine[0].dir=spine[0].dir; */
      /* } */
      break;
    case 'a':
      if(spine[0].dir != 'd'){
        spine[0].dir=input_dir;
      } 
      break;
    case 's':
      if(spine[0].dir != 'w'){
        spine[0].dir=input_dir;
      } 
      break;
    case 'd':
      if(spine[0].dir != 'a'){
        spine[0].dir=input_dir;
      } 
      break;
    default: break;
  }
  /* spine[0].dir=input_dir; */
  
	char horizontal_bound[]="---------------------------------------------------------------------------------";

  // after each movement, each spine-dir is given the dir of its previous spine, this is so that each spine is aware of the direction in which its moving
  while(turn_cnt>0){
    spine[turn_cnt].dir = spine[turn_cnt-1].dir;
    spine[turn_cnt].p_x = spine[turn_cnt-1].p_x;
    spine[turn_cnt].p_y = spine[turn_cnt-1].p_y;
    turn_cnt--;
  }

    for(i=0; i<=num_spines; i++){
      // dont worry about the head being assigned value in each iteration, cause at i=0 the head value will be printed into spine[0] so subsequent assignments of head wont affect the first spine

      // this is where spines are made - coordinate based
      if(i!=0){
      /* switch(spine[i].dir){ */
      /*   case 'w': spine[i].p_y--; */
      /*             break; */
      /*   case 's': spine[i].p_y++; */
      /*             break; */
      /*   case 'a': spine[i].p_x--; */
      /*             break; */
      /*   case 'd': spine[i].p_x++; */
      /*             break; */
      /*   default : break; */
      /* } */
        sprintf(spine[i].bone, "\033[%d;%dHo", spine[i].p_y, spine[i].p_x);
      } else{
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
        sprintf(spine[i].bone, "\033[%d;%dH%c", spine[i].p_y, spine[i].p_x, head);
      }
      // condition for boundary dimension
      if(spine[i].p_x<=10) {
        spine[i].p_x=89;
      } else if(spine[i].p_x>=90) {
        spine[i].p_x=11;
      } else {
        spine[i].p_x=spine[i].p_x;
      }

      if(spine[i].p_y<=4) {
        spine[i].p_y=29;
      } else if(spine[i].p_y>=30) {
        spine[i].p_y=5;
      } else {
        spine[i].p_y=spine[i].p_y;
      }
      //////////////////////////////////
        
    }

    // printing the whole tail
    for(int cnt=0; cnt<=num_spines; cnt++){
      printf("%s",spine[cnt].bone);
      fflush(stdout);
    }

  /* // after each movement, each spine-dir is given the dir of its previous spine, this is so that each spine is aware of the direction in which its moving */
  /* while(turn_cnt>0){ */
  /*   spine[turn_cnt].dir = spine[turn_cnt-1].dir; */
  /*   turn_cnt--; */
  /* } */

	printf("\033[4;10H%s",horizontal_bound);
	printf("\033[30;10H%s",horizontal_bound);

	for(int v_cnt=5;v_cnt<30;v_cnt++){
		printf("\033[%d;10H|",v_cnt);
		printf("\033[%d;90H|",v_cnt);
	}

	/* printf("\033[2;1Hx=%d,y=%d",x,y); */

	/* printf("\033[3:1Hposx=%d,posy=%d", data -> rand_x, data -> rand_y); */

	printf("\033[3;1Hinterval_cnt=%d",interval_cnt);
	fflush(stdout);
	
	/* data -> x = x; */
	/* data -> y = y; */

	return spine;
}

coord *pos(coord *input_coord, int num_spines){
	// initailise a new struct and give it the value of the struct sent in as argument
	coord *spine = input_coord;
  if(num_spines!=0){
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
  }

	// update the value of the rand coordinates in the new struct
	spine -> rand_y= rand() % (25-1 +1) + 4;
	spine -> rand_x= rand() % (69-1 +1) + 10;

	// clear the screen
	printf("\033[2J");
	
	// print [] at the rand coordinates
	printf("\033[%d;%dH", spine->rand_y, spine->rand_x);
	printf("[ ]");
	fflush(stdout);

	// return the spine struct, which contains the new rand coordinates, to the main function	
	return spine;
}

char* keep_score(char *input, int i){
	char *foo = (char*)malloc(20*sizeof(char)); 
	foo = input;

	strcat(foo, "#");
	printf("\033[1;1H");
	printf("%s%d", foo, i*10);
	fflush(stdout);

	return foo;
}

/* struct node *turn_point(coord *ip_coord, char input_dir, struct node *head){ */
/*   int pos_x= ip_coord -> x; */
/*   int pos_y= ip_coord -> y; */
/*   head = head_insert(head, pos_x, pos_y, input_dir); */
/* 	/1* printf("\033[1;20H"); *1/ */
/*   /1* printtab(head); *1/ */
/*   return head; */
/* } */
