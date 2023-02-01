/* A simple server in the internet domain using TCP
 * Answer the questions below in your writeup
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
    /* 1. What is argc and *argv[]?
     *  'argc' holds the number of arguments passed to the program
     * '*argv[]' is a pointer to an array of character strings that contain the arguments passed to the program
     */
    int sockfd, newsockfd, portno;
    /* 2. What is a UNIX file descriptor and file descriptor table?
     *  A UNIX file descriptor is an integer value that refers to an open file in the operating system.
     * The file descriptor table is a table of all open file descriptors with each entry ontains info about an open file.
     */
    socklen_t clilen;

    struct sockaddr_in serv_addr, cli_addr;
    /* 3. What is a struct? What's the structure of sockaddr_in?
     *  A struct is a  data type that groups  variables of different data types under a single name.
     *  The structure of sockaddr_in is a data structure that holds information about a socket address, including the IP address and port number.
     */
    
    int n;
    if (argc < 2) {
        fprintf(stderr,"ERROR, no port provided\n");
        exit(1);
    }
    
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    /* 4. What are the input parameters and return value of socket()
     *  domain(AF_INET for Internet domain), type(SOCK_STREAM for a stream socket), protocol (0 to use a default protocol)
     *  The return value is a file descriptor that refers to the newly created socket.
     */
    
    if (sockfd < 0) 
       error("ERROR opening socket");
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    
    if (bind(sockfd, (struct sockaddr *) &serv_addr,
             sizeof(serv_addr)) < 0) 
             error("ERROR on binding");
    /* 5. What are the input parameters of bind() and listen()?
     * for blind (), the input parameters are 
        the socket file descriptor, 
        a pointer to the socket address structure (e.g., serv_addr), 
        and the size of the socket address structure. 
     * for listen(), the input parameters are 
        the socket file descriptor and 
        the maximum number of connections to queue.
     */
    
    listen(sockfd,5);
    clilen = sizeof(cli_addr);
    
    while(1) {
        /* 6.  Why use while(1)? Based on the code below, what problems might occur if there are multiple simultaneous connections to handle?
        *    while(1) would continuously accept and handle incoming connection
        *    if there are multiple simultaneous connections to handle, only one connection can be handled at a time using this code, as the code will block until the previous connection has been closed.
        */
        
	char buffer[256];
        newsockfd = accept(sockfd, 
                    (struct sockaddr *) &cli_addr, 
                    &clilen);
	/* 7. Research how the command fork() works. How can it be applied here to better handle multiple connections?
         *  fork() is a system call that creates a child process. It can be used in this code to handle multiple connections by creating a new child process for each incoming connection. This would allow the parent process to continue accepting new connections while the child process handles the current connection.
         */
        
	if (newsockfd < 0) 
             error("ERROR on accept");
	bzero(buffer,256);
        
	n = read(newsockfd,buffer,255);
        if (n < 0) 
            error("ERROR reading from socket");
        //printf("Here is the message: %s\n",buffer);
        n = write(newsockfd,"I got your message",18);
        if (n < 0) 
            error("ERROR writing to socket");
        close(newsockfd);
    }
    close(sockfd);
    return 0; 
}
  
/* This program makes several system calls such as 'bind', and 'listen.' What exactly is a system call?
 *  A system call is a low-level programming interface that allows a program to request a service from the operating system.
 */