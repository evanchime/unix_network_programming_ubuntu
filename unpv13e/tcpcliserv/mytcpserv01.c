#include	"unp.h"
//#include	"mysigchldwait.h"
//#include	"mystr_echo.h"
#include	"mystr_echo.h"

int
main(int argc, char **argv)
{
	int	listenfd, connfd;
	pid_t	childpid;
	socklen_t	clilen;
	struct sockaddr_in	cliaddr, servaddr;

	listenfd = Socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family      = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port        = htons(/*SERV_PORT*//*13*/19);

	Bind(listenfd, (SA *) &servaddr, sizeof(servaddr));

	Listen(listenfd, LISTENQ);

//	Signal (SIGCHLD, sig_chld); /* must call waitpid() */ 


	for ( ; ; ) {
		clilen = sizeof(cliaddr);
		connfd = Accept(listenfd, (SA *) &cliaddr, &clilen);
		/*if ( (connfd = accept (listenfd, (SA *) &cliaddr, &clilen)) < 0)//correctly handles a return of EINTR from accept 
		{              
			if (errno == EINTR)                  
				continue;         //  back to for() 
			else                  
				err_sys("accept error"); 
		}*/ 
 

		if ( (childpid = Fork()) == 0) {	/* child process */
			Close(listenfd);	/* close listening socket */
			str_echo(connfd);	/* process the request */
			exit(0);
		}
		Close(connfd);			/* parent closes connected socket */
	}
}
