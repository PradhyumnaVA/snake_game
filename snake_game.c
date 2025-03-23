#include "s_header.h"

int main(){
	// pipefd holds the read and write fd(file descriptor)
	int pipefd[2]; 
	char buffer[1];
	pid_t pid;
	int buf_status;

	// creating pipe
	if(pipe(pipefd) == -1){
		perror("pipe not created");
		exit(EXIT_FAILURE);
	}

	if(fcntl(pipefd[0], F_SETFL, O_NONBLOCK) < 0){
		exit(EXIT_FAILURE);
	}

	// creating child 
	pid = fork();
	
	// process not created
	if (pid == -1) {
        	perror("fork"); // Handle fork error
		exit(EXIT_FAILURE);
	}

	//child process
	if(pid == 0){
		// variable to hold input direction
		char dir; 

		char *write_byte; 

		// closing read end of pipe
		close(pipefd[0]); 

		printf("\033[2J");

		// change the terminal to raw mode, input directly taken, no need to press ENTER
		system("stty raw -echo");

		while(1){
			// get input from user for direction
			dir= getchar();
			
			// the input to write needs to be pointer, so user input is turned into pointer
			write_byte = &dir;

		        // write 1 byte of data that is entered 	
			write(pipefd[1], write_byte, 1); 
			
			if(dir == 'q'){
				break; // ends the infinite loop
			}
		}
		
		// change terminal back to normal mode
		system("stty cooked echo");

		// ends the child process, so that it doesnt become zombie
		exit(EXIT_SUCCESS); 
	}

	//parent process
	else {
		// change the terminal to raw mode, input directly taken, no need to press ENTER
		system("stty raw -echo");
		
		// allocate memory on the heap for the present coordinate struct
		coord *present_c = (coord*)malloc(100*sizeof(coord));

		char *score = (char*)malloc(20*sizeof(char)); 
		int count=0;

		// initial position of head 
		present_c -> x=20;
		present_c -> y=5;

		// variable to hold intermediate direction
		char input_dir='d';

		// variable to count the instances between key press
		int interval_cnt=0;

		// closing write end of pipe
		close(pipefd[1]); 
		
		// initial position of []
		present_c=pos(present_c);

		// time increment variable
		int time_incr=130000;

		while(1){
			// reading from the buffer, read internally clears the buffer
			buf_status = read(pipefd[0], buffer, sizeof(buffer)); 

			if(buf_status == -1) {
				// if buffer is empty then movement of head occurs
				if(errno == EAGAIN) {

					printf("\033[%d;%dH", present_c->rand_y, present_c->rand_x);
					printf("[ ]");

					if((present_c->x == present_c->rand_x+1) && (present_c->y == present_c->rand_y)){
						printf("\033[2J");
						printf("\033[1;1Hsuccess\n");
						(present_c->x)++;
						(present_c->y)++;
						count++;
						time_incr=time_incr-6000;
						score = keep_score(score,count);			
						present_c = pos(present_c);
						continue;
					}		

					printf("\033[1;1H");
					printf("%s%d", score, count*10);
					fflush(stdout);

					present_c = move(present_c, input_dir, count, interval_cnt);

					interval_cnt++;

					usleep(time_incr);
					printf("\033[2J");
				}
				else {
					perror("read");
					exit(EXIT_FAILURE);
				}
			}
			
			// when key is pressed 
			else {
				input_dir = buffer[0];
				interval_cnt = 0;
				if(input_dir == 'q'){
					break; // ends the infinite loop
				}
			}
		}
		system("stty cooked echo");
		free(present_c);	
		free(score);
		printf("incr=%d",time_incr);
		exit(EXIT_SUCCESS);
	}
	return EXIT_SUCCESS;
}
