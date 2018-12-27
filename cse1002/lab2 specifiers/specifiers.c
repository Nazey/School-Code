/* 
 * Author: Brian Massino, bmassino2017@my.fit.edu 
 * Course: CSE 1002, Section 01, Spring 2018 
 * Project: specifiers 
 */
 #include <stdio.h>
 #include <string.h>
 #include <stdlib.h>

void read_file(char file_name[50], char inputs[20][100], int* length); 
// read the file in a variable

void reformat_and_save_file(char file_name[50], char inputs[20][100], int length); 
// reformat the variables as each line ask how and save in a new file adding a new column 

int main(void){
	char file_name[50];
	char inputs[20][100];
	int length=0;
	
	printf("Enter in the name of your file: ");
	gets(file_name);
	read_file(file_name, inputs, &length);
    reformat_and_save_file("database_output.csv", inputs, length);
    printf("File has been formatted.");
	return 0;
}

//reading in the csv file as an array of strings
void read_file(char file_name[50], char inputs[20][100], int* length){
	FILE *fin = fopen(file_name, "r");
    int i =0;
	while(!feof(fin)){
		fgets(inputs[i], 100, fin);
		i++;
	}
	*length=i;
	fclose(fin);
    
}


//in each block, I format the strings and convert into decimals/doubles/ints and use the proper format specifiers with them
void reformat_and_save_file(char file_name[50], char inputs[20][100], int length){
    FILE *fout = fopen(file_name, "w");
    
    char temp_str[100];
    double numerator, denominator,whole_num;
    char dummy_variable;
    
    strncpy(temp_str, inputs[0], strlen(inputs[0])-1);
    fprintf(fout, "%s %s\n", temp_str, "output");  
    
    memset(temp_str,0,strlen(temp_str));
    strncpy(temp_str, inputs[1], strlen(inputs[1])-1);
    fprintf(fout, "%s%d\n", temp_str, atoi(inputs[1]));
    
    memset(temp_str,0,strlen(temp_str));
    strncpy(temp_str, inputs[2], strlen(inputs[2])-1);
    fprintf(fout, "%s%o\n", temp_str, atoi(inputs[2]));
    
    memset(temp_str,0,strlen(temp_str));
    strncpy(temp_str, inputs[3], strlen(inputs[3])-1);
    fprintf(fout, "%s%.10d\n", temp_str, atoi(inputs[3]));
    
    memset(temp_str,0,strlen(temp_str));
    strncpy(temp_str, inputs[4], strlen(inputs[4])-1);
    fprintf(fout, "%s%X\n", temp_str, atoi(inputs[4]));
     
    memset(temp_str,0,strlen(temp_str));
    strncpy(temp_str, inputs[5], strlen(inputs[5])-1);
    fprintf(fout, "%s%#0x\n", temp_str, atoi(inputs[5]));
    
    //only reason I use the dummy_variable is to get past the '/' without any issues. Never actually used.
    sscanf(inputs[6], "%lf%c%lf", &numerator, &dummy_variable, &denominator);
    whole_num=numerator/denominator;
    memset(temp_str,0,strlen(temp_str));
    strncpy(temp_str, inputs[6], strlen(inputs[6])-1);
    fprintf(fout, "%s%.18lf\n", temp_str, whole_num); 
    
    memset(temp_str,0,strlen(temp_str));
    strncpy(temp_str, inputs[7], strlen(inputs[7])-1);
    fprintf(fout, "%s%.2lf\n", temp_str, whole_num); 
    
    memset(temp_str,0,strlen(temp_str));
    strncpy(temp_str, inputs[8], strlen(inputs[8])-1);
    fprintf(fout, "%s%.4lf\n", temp_str, whole_num); 
    
    memset(temp_str,0,strlen(temp_str));
    strncpy(temp_str, inputs[9], strlen(inputs[9])-1);
    fprintf(fout, "%s%.6lf\n", temp_str, whole_num); 
    
    memset(temp_str,0,strlen(temp_str));
    strncpy(temp_str, inputs[10], strlen(inputs[10])-1);
    fprintf(fout, "%s%.0e\n", temp_str, atof(inputs[10])); 
    
    memset(temp_str,0,strlen(temp_str));
    strncpy(temp_str, inputs[11], strlen(inputs[11])-1);
    fprintf(fout, "%.42s\"%.41s\"\n", temp_str, temp_str);
    
    //created a for loop to transform the '/' into '%'
    memset(temp_str,0,strlen(temp_str));
    strncpy(temp_str, inputs[12], strlen(inputs[12])-1);
   
    for(int i=0; i<strlen(inputs[12]); i++){
        if(inputs[12][i]=='/'){
           inputs[12][i]='%';
        }
    }
    
    fprintf(fout, "%s%.10s\n", temp_str, inputs[12]); 
    
    memset(temp_str,0,strlen(temp_str));
    strncpy(temp_str, inputs[13], strlen(inputs[13])-1);
    fprintf(fout, "%s\n", temp_str);
    
    //again, another for loop to replace the '/' with a format specifier '/t' or tab
    memset(temp_str,0,strlen(temp_str));
    strncpy(temp_str, inputs[14], strlen(inputs[14])-1);
    for(int i=0; i<strlen(inputs[14]); i++){
        if(inputs[14][i]=='/'){
           inputs[14][i]='\t';
        }
    }
    fprintf(fout, "%s%.10s\n", temp_str, inputs[14]);
    
    memset(temp_str,0,strlen(temp_str));
    strncpy(temp_str, inputs[15], strlen(inputs[15])-1);
    fprintf(fout, "%s%.1s\n", temp_str, temp_str);
    
    fprintf(fout, "%s%.6s", inputs[16], inputs[16]);
    
    fclose(fout);
}	
