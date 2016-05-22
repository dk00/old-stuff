#include "printinfo.h"

void printinfo(int cmd){
    switch(cmd){
			  case 1:
				    write(2, "Client closed the dedicated FIFO\n", 33);
				    break;
				case 2:
				    write(2, "No client\n", 10);
				    break;
				case 3:
				    write(2, "Server closed the well-known FIFO\n", 34);
				    break;
				case 4:
				    write(2, "Server closed the dedicated FIFO\n", 33);
				    break;
				default:
				    write(2, "I am a default action\n", 22);
    }
}
