#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
char date[50];
double open;
double high;
double low;
double close;
long volume;
double adjclose;
} STOCK;
int main(int argc, char *argv[]) {
FILE *input = fopen(argv[1], "r");
int counter = 0;
char str[1000];
fgets(str, sizeof(str), input);
while(fgets(str, sizeof(str), input) != NULL) {
counter++;
}
fclose(input);
STOCK *ptr = (STOCK *) malloc(counter * sizeof(STOCK));
FILE *input_2 = fopen(argv[1], "r");

fgets(str, sizeof(str), input_2);
for(int x = 0; x < counter; x++) {
fgets(str, sizeof(str), input_2);
char *s = strtok(str, ",");
strcpy(ptr[x].date, s);
s = strtok(NULL, ",");
ptr[x].open = atof(s);
s = strtok(NULL, ",");
ptr[x].high = atof(s);
s = strtok(NULL, ",");
ptr[x].low = atof(s);
s = strtok(NULL, ",");
ptr[x].close = atof(s);
s = strtok(NULL, ",");
ptr[x].volume = atof(s);
s = strtok(NULL, ",");
ptr[x].adjclose = atof(s);
s = strtok(NULL, ",");

}
int big = ptr[0].high;
int count = 0;
for(int i = 0; i < counter; i++) {
if (ptr[i].high > big){
big = ptr[i].high;
count = i;
}
}
printf("Date: %s\n",ptr[count].date);
printf("Open: %lf\n",ptr[count].open);
printf("High: %lf\n",ptr[count].high);
printf("Low: %lf\n",ptr[count].low);
printf("Close: %lf\n",ptr[count].close);
printf("Volume: %ld\n",ptr[count].volume);
printf("Adj. close: %lf\n",ptr[count].adjclose);

fclose(input_2);
}