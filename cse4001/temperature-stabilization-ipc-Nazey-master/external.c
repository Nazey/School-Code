/* Socket tutorial

url: http://www.linuxhowtos.org/C_C++/socket.htm

*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <math.h>


void error(const char* msg)
{
     perror(msg);
     exit(1);
}

double central_temperature; 

double generate_new_ex_temp(double temperature); //generates new external temperature based on given temperature. Based on formula from canvas.

int main(int argc, char* argv[])
{

     // similar to server's 
     int sockfd, portno, n, temp;
     struct sockaddr_in serv_addr;
     struct hostent* server;
     double temperature;
     char buffer[256];

     if (argc < 3) {
          fprintf(stderr, "usage %s hostname port temperature connection number\n", argv[0]);
          exit(0);
     }
     portno = atoi(argv[2]);
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0)
          error("ERROR opening socket");

     temperature = atof(argv[3]); //initial temperature from command line.

     // The variable argv[1] contains the name of a host on the Internet	
     server = gethostbyname(argv[1]);
     if (server == NULL) {
          fprintf(stderr, "ERROR, no such host\n");
          exit(0);
     }

     // similar to server's 
     bzero((char*)&serv_addr, sizeof(serv_addr));
     serv_addr.sin_family = AF_INET;
     bcopy((char*)server->h_addr,
          (char*)&serv_addr.sin_addr.s_addr,
          server->h_length);
     serv_addr.sin_port = htons(portno);

     // Establish a connection to the server. It takes three arguments, 
     // the socket file descriptor, the address of the host to which it wants 
     // to connect (including the port number), and the size of this address. 
     // The client needs to know the port number of the server, but it does not 
     // need to know its own port number. This is typically assigned by the 
     // system when connect is called.
     if (connect(sockfd, (struct sockaddr*) & serv_addr, sizeof(serv_addr)) < 0)
          error("ERROR connecting");


     bzero(buffer, 256);                          //here we use snprintf to store the double into the buffer. Then we concatenate it with a space and 
     snprintf(buffer, 256, "%lf", temperature);   //the Id/connection number we specififed in command line arguments.
     strcat(buffer, " ");
     strcat(buffer, argv[4]); 
     n = write(sockfd, buffer, strlen(buffer));
     if (n < 0)
          error("ERROR writing to socket");

     printf("Sucessfully Connected\n");
     while (1) {    //wait for a response from the server to continue.
          char *eptr;    //need this in order to convert a string to a double with strtod
          bzero(buffer, 256);
          n = read(sockfd, buffer, 256);
          if (n < 0)
               error("ERROR reading from socket");
          if (strcmp(buffer, "quit") == 0) { //see if it server is telling you to quit, if so, close socket and break out of the program.
               printf("System stabilized. Quitting...\n");
               close(sockfd);
               exit(0);
          }
          else if(buffer[0] != '\0') { //else the server must be sending you a number to request that a new temperature from client be sent.
               
               printf("System not stablized.\nNew central temperature is: %s\n", buffer);
              
               central_temperature = strtod(buffer, &eptr);
               temperature = generate_new_ex_temp(temperature); //temperature is the new temperature to send to the server.
               
               bzero(buffer, 256);                 
               snprintf(buffer, 256, "%lf", temperature); 
               printf("New external temperature is: %s\n", buffer);

               n = write(sockfd, buffer, strlen(buffer));
               if (n < 0)
                    error("ERROR writing to socket");

          }

     }

     return 0;
}

double generate_new_ex_temp(double temperature) {
     double result = ((temperature * 3) + (2 * central_temperature)) / 5;
     return result;
}