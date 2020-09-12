/* Socket tutorial

url: http://www.linuxhowtos.org/C_C++/socket.htm

*/
/* A simple server in the internet domain using TCP
   The port number is passed as an argument
   This version runs forever, forking off a separate
   process for each connection
*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <math.h>
#include <pthread.h>


typedef struct Temperature_Data {
     int socket_id;
     double temperature;
     int conn_num;
     double central_temp;
}Temperature_Data;

void dostuff(int); /* function prototype */

void error(const char* msg)
{
     perror(msg);
     exit(1);
}
void generate_central_temp();
void* request_new_temps(void* threadarg);
void* send_exit(void* threadarg);
int is_stable();
void print_temperature_status();

double central_temperature;
Temperature_Data temp_array[4];
double temp_data[4];

int main(int argc, char* argv[])
{
     int sockfd, newsockfd, portno, pid, num_connections;
     socklen_t clilen;
     struct sockaddr_in serv_addr, cli_addr;
     char* eptr;

     if (argc < 2)
     {
          fprintf(stderr, "ERROR, no port provided\n");
          exit(1);
     }
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0)
          error("ERROR opening socket");
     bzero((char*)&serv_addr, sizeof(serv_addr));
     portno = atoi(argv[1]);
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
     if (bind(sockfd, (struct sockaddr*) & serv_addr,
          sizeof(serv_addr)) < 0)
          error("ERROR on binding");
     listen(sockfd, 4); //only want 4 connections total
     clilen = sizeof(cli_addr);

     central_temperature = strtod(argv[2], &eptr);
     num_connections = 0;

     while (num_connections < 4) //keep accepting until you all 4 have been accepted and stored in the struct array
     {

          double conn_temp;
          int  connection_number, n;
          char buffer[256];

          newsockfd = accept(sockfd,
               (struct sockaddr*) & cli_addr, &clilen);
          if (newsockfd < 0)
               error("ERROR on accept");


          bzero(buffer, 256);
          n = read(newsockfd, buffer, 255);


          char* token = strtok(buffer, " "); //parsing the input using strtok
          conn_temp = strtod(token, &eptr);
          token = strtok(NULL, " ");
          connection_number = atoi(token);
          printf("Client %d Connected. Temperature: %lf\n", connection_number, conn_temp);

          if (n < 0)
               error("ERROR on reading");

          temp_array[num_connections].socket_id = newsockfd;
          temp_array[num_connections].temperature = conn_temp;
          temp_array[num_connections].conn_num = connection_number;
          temp_array[num_connections].central_temp = central_temperature;
          temp_data[num_connections] = conn_temp + 1;

          //if we got a reply from a client, increase the counter.
          if (newsockfd > 0)
               num_connections++;
     } /* end of while */

     printf("\n");

     //now to create threads and get new temperature values.
     pthread_t threads[4];
     int rc;
     int first_pass = 1;


     printf("\nInitial Temperatures based on first central temp!\nNew Temperatures:\n");
     printf("Central Temperature: %lf\n", central_temperature);
     for (int i = 0; i < 4; i++) {
          temp_data[i] = temp_array[i].temperature;
          rc = pthread_create(&threads[i], NULL, request_new_temps, (void*)
               &temp_array[i]);

          if (rc) {
               printf("ERROR; return code from pthread_create() is %d\n", rc);
               exit(-1);
          }
     }
     //joining threads together
     for (int i = 0; i < 4; i++) {
          (void)pthread_join(threads[i], NULL);

     }
     print_temperature_status();


     while (1) {
          if (is_stable() == 1) {
               printf("Central Temperature: %lf\n", central_temperature);
               printf("Temperature is stable!\n");
               print_temperature_status();
               for (int i = 0; i < 4; i++) {
                    rc = pthread_create(&threads[i], NULL, send_exit, (void*)
                         &temp_array[i]);

                    if (rc) {
                         printf("ERROR; return code from pthread_create() is %d\n", rc);
                         exit(-1);
                    }
               }
               //joining threads together
               for (int i = 0; i < 4; i++) {
                    (void)pthread_join(threads[i], NULL);

               }
               break; //break out of while loop.
          }
          else {
               if(first_pass == 1)
                    generate_central_temp();
               printf("\nTemperature is not stable!\nNew Temperatures:\n");
               printf("New Central Temperature: %lf\n", central_temperature);

               for (int i = 0; i < 4; i++) {
                    temp_data[i] = temp_array[i].temperature;
                    rc = pthread_create(&threads[i], NULL, request_new_temps, (void*)
                         &temp_array[i]);

                    if (rc) {
                         printf("ERROR; return code from pthread_create() is %d\n", rc);
                         exit(-1);
                    }
               }
               //joining threads together
               for (int i = 0; i < 4; i++) {
                    (void)pthread_join(threads[i], NULL);

               }
               print_temperature_status();
          }
          first_pass = 1;
     }


     close(sockfd); //close socket.


     return 0;
}

void* request_new_temps(void* threadarg)
{
     char* eptr;
     int socket_id, index, n;
     double temp, central_temp1;
     char buffer[256];

     Temperature_Data* my_data;
     my_data = (Temperature_Data*)threadarg;
     socket_id = my_data->socket_id;
     index = my_data->conn_num;
     temp = my_data->temperature;
     central_temp1 = my_data->central_temp;

     //zero out buffer, write the new central temperature to the buffer, and send the buffer.
     bzero(buffer, 256);
     snprintf(buffer, 256, "%lf", central_temp1);
     n = write(socket_id, buffer, strlen(buffer));
     if (n < 0)
          error("ERROR writing to socket");
     sleep(1);

     //zero the buffer again, read the resulting new temperature from client, store that into the global struct.
     bzero(buffer, 256);
     n = read(socket_id, buffer, 255);
     if (n < 0)
          error("ERROR reading socket");
     temp = strtod(buffer, &eptr);
     my_data->temperature = temp;
     pthread_exit(NULL); //kill the thread
}
void* send_exit(void* threadarg)
{
     int socket_id, n;
     char buffer[256];
     Temperature_Data* my_data;
     my_data = (Temperature_Data*)threadarg;
     socket_id = my_data->socket_id;


     bzero(buffer, 256);
     strcpy(buffer, "quit");
     n = write(socket_id, buffer, strlen(buffer));
     if (n < 0)
          error("ERROR writing to socket");
     pthread_exit(NULL);
}

int is_stable() {
     int result = 1;

     for (int i = 0; i < 4; i++) {
          //printf("Tempbefore #%d %lf Temp after %lf\n", i, temp_data[i], temp_array[i].temperature);
          if (temp_array[i].temperature != temp_data[i]) {
               result = 0;
          }

     }
     return result;
}

void generate_central_temp() {
     double result = (central_temperature * 2);

     for (int i = 0; i < 4; i++) {
          result += temp_array[i].temperature;
     }
     result = result / 6;
     central_temperature = result;
     for (int i = 0; i < 4; i++)
          temp_array[i].central_temp = central_temperature;
}

void print_temperature_status() {
     for (int i = 0; i < 4; i++) {
          printf("Connection #: %d Temperature: %lf Socket id: %d\n", temp_array[i].conn_num, temp_array[i].temperature, temp_array[i].socket_id);
     }
     printf("\n");
}