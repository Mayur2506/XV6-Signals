#define MAXSIGNALS  32

#define SIG_IGN     0
#define SIG_DFL     1
#define SIGINT      2
#define SIGKILL     9
#define SIGSTOP     19


struct sigaction{
	void (*sa_handler)(int);
	int sigmask; 
};


