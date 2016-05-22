#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Log messages with fixed sizes are maintained in global memory.
// You can either maintain your log messages with your own data structures
// in AtomicLog_Functions.c or use Log[8192] in AtomicLog_Main.c
// It depends on your choice. Don't confuse.
char Log[8192];

// 
// FUNCTION: 
//     atomic_log_open: open a file for appending log
//                      message.
// ARGUMENTS: 
//     pathname: pathname for the log file
// RETURN: 
//     -1: fail to open the file
//     0 or positive integer: file descriptor for the log file
// 
int atomic_log_open(char *pathname);

// 
// FUNCTION: 
//     log_string: 
// ARGUMENTS: 
//     source_log: the message we want to store
// RETURN: 
//     -1: fail to maintain the log messages in the memory of each process
//     >=0: number of bytes stored in memory
// 
ssize_t log_string(char *source_log);

// 
// FUNCTION: 
//     atomic_log_send: 
// ARGUMENTS: 
//     fd: file descriptor for the log file
// RETURN: 
//     -1: fail to write the log messages to file
//     >=0: number of bytes written to log file.
// 
ssize_t atomic_log_send(int fd);

void err_quit(const char* msg){
	fprintf(stderr, msg);
	exit(1); /*failure*/
}

main(int argc, char* argv[]){

	char *LogFileName; // pathname
	int RandSeed = 1; // rand seed
	int ChildProcessIndex = 0;
	int NumberofChildProcess = 0; // number of process
	int NumberofMessage = 1;
	double SleepForAWhile = 0;
	int fd;
	
	if(argc != 4)
		err_quit("usage: hw1 filename seed numberofprocess\n");
	
	pid_t pid;
	LogFileName = argv[1];
	RandSeed = atoi(argv[2]);
	NumberofChildProcess = atoi(argv[3]);
		
	//Set the seed for random number generator
	srand(RandSeed);


	//At most fork NumberofPorcess childs, and only parent can fork.
	while(ChildProcessIndex < NumberofChildProcess){
		// At most 200 messages
		NumberofMessage = (int)100 * (1.0 + (double)rand()/(RAND_MAX));
		
		// At most sleep for 1 seconds
		SleepForAWhile = (double)rand()/(RAND_MAX);
		
		printf("Number of messages for Child Process %c = %d\n", 
					 ChildProcessIndex + 65, NumberofMessage); 
		printf("sleep_time for Child Process %c = %f\n", 
					 ChildProcessIndex + 65, SleepForAWhile); 
		fflush(stdout);

		// Fork a child process
		if ((pid=fork()) < 0)
			/*Fork error*/
			err_quit("fork error\n");	
		else if ( pid == 0){
			// Child process
			//
			// We will ask the child process to sleep 
			// for a while first. Then, it will generate
			// a number of log messages, store the messages
			// in memory, and send the messages to the log
			// file at the end. 
			int index = 0;
			
			usleep(SleepForAWhile * 1000000);

			if((fd = atomic_log_open( LogFileName )) == -1)
				err_quit("open/create file error\n");

			for (index = 0; index < NumberofMessage; index++){
				char LogMessage[40];
				
				sprintf(LogMessage, "Child Process %c: Message-ID: %d \n", 
					ChildProcessIndex + 65, index);
				
				#ifdef DEBUG
				fprintf(stderr, LogMessage);
				#endif
				if(log_string(LogMessage) < strlen(LogMessage)) {
					break;
				}
			}
			atomic_log_send(fd);
			_exit(0);
		}else
			/*Parent Process*/
			ChildProcessIndex++;

	}
  
	/*Fork successfully*/
	exit(0);
	
}
