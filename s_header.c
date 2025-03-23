#include "s_header.h"

coord *move(coord *ip_coord, char input_dir, int len_tail, int interval_cnt){
	coord *data = ip_coord;
	int i;
	
	char horizontal_bound[]="----------------------------------------------------------------------------------";

	// tail configurations
	char t_down[] = "o\033[A\033[D";
	char t_right[] = "o\033[2D"; 
	char t_up[] = "o\033[B\033[D";
	char t_left[] = "o"; 

	// head configurations
	char h_down[] = "v\033[A\033[D"; 
	char h_right[] = ">\033[2D"; 
	char h_up[] = "^\033[B\033[D"; 
	char h_left[] = "<";

	char t_dir[9], h_dir[9];
	/* int upper_bound = (interval_cnt==0)? len_tail : interval_cnt; */
	int upper_bound = interval_cnt;
	int x= data -> x;
	int y= data -> y;

	// condition for boundary dimension
	if(x<=10){x=89;}
	else if(x>=90){x=11;}
	else {x=x;}

	if(y<=4) {y=29;}
	else if(y>=30) {y=5;}
	else {y=y;}
    //////////////////////////////////
	
	switch(input_dir){
		case 'w': y--; break;
		case 's': y++; break;
		case 'a': x--; break;
		case 'd': x++; break;
		default : break;
	}

	printf("\033[%d;%dH",y,x);

	if(len_tail != 0){
		switch(input_dir){
			case 's': strcpy(t_dir,t_down); 
				  strcpy(h_dir,h_down);
				  break;
			case 'w': strcpy(t_dir,t_up); 
				  strcpy(h_dir,h_up);
				  break;
			case 'd': strcpy(t_dir,t_right); 
				  strcpy(h_dir,h_right);
				  break;
			case 'a': strcpy(t_dir,t_left); 
				  strcpy(h_dir,h_left);
				  break;
			default: break;
		}

		for(i=0; i<upper_bound+1; i++){
			if(i==0){
				strcpy(data[i].bone, h_dir);
			}
			else{
				strcpy(data[i].bone, t_dir);
			}
		}

		for (i = 0; i < len_tail+1; i++) {
		    printf("%s", data[i].bone);
		}
		fflush(stdout);
	}

	else{
		switch(input_dir){
			case 'w': printf("^"); break;
			case 's': printf("v"); break;
			case 'a': printf("<"); break;
			case 'd': printf(">"); break;
			default : break;
		}
	}

	printf("\033[4;10H%s",horizontal_bound);
	printf("\033[30;10H%s",horizontal_bound);

	printf("\033[2;1Hx=%d,y=%d",x,y);

	printf("\033[3:1Hposx=%d,posy=%d", data -> rand_x, data -> rand_y);
	fflush(stdout);
	
	data -> x = x;
	data -> y = y;

	return data;
}

coord *pos(coord *input_coord){
	// initailise a new struct and give it the value of the struct sent in as argument
	coord *data = input_coord;

	// update the value of the rand coordinates in the new struct
	data -> rand_y= rand() % (25-1 +1) + 4;
	data -> rand_x= rand() % (69-1 +1) + 10;

	// clear the screen
	printf("\033[2J");
	
	// print [] at the rand coordinates
	printf("\033[%d;%dH", data->rand_y, data->rand_x);
	printf("[ ]");
	fflush(stdout);

	// return the data struct, which contains the new rand coordinates, to the main function	
	return data;
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
