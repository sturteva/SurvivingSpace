#include <fcntl.h>
#include <signal.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/errno.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>
#include <stdexcept>
#include <iostream>
#include <algorithm>

void PeriodicUpdates();

//Descriptors
static fd_set in_set;
static fd_set out_set;
static fd_set exc_set;

/*When a player sends an interruption signal*/
void leave(int signal){
	cout << "Terminated by player with signal " << signal << endl;
}
