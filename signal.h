#define MAXSIGNALS  32

//#define SIG_IGN     0
#define SIG_DFL     0
#define SIGINT      2
#define SIGKILL     9
#define SIGSTOP     19
#define SIGTERM	    15

struct sigaction{
	void (*sa_handler)(int);
	int sigmask; 
};


