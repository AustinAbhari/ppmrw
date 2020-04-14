/*
Project #1 PPM Converter
Austin Abhari
CS430
9/16/16
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Declaring fucntion names
void P3();
void P6();
int get_magic_number();


// Main
int main( int argc, char *argv[] )  {

   printf("\n----------------------------------------------------------\n");
   printf("             Welcome to the PPM Converter \n"); 
   printf("                  By: Austin Abhari \n"); 
   printf("                         CS430 \n"); 
   printf("                       Project #1 \n"); 
   printf("----------------------------------------------------------\n\n");  
	
   //Check for 4 inputs
	if(argc == 4) {
      //Name file format, second input
      int file_format = atoi(argv[1]);
      //Check if 2nd input is == 3
    	if(file_format == 3){
            //4th input is the name of the output file
            char *output_file = argv[3];
            //Checking the output file has .ppm at the end
            int len = strlen(output_file);
            const char *file_extention = &output_file[len-4];
         if(strcmp(".ppm", file_extention) != 0){
            fprintf(stderr, "The output file must be of file extention '.PPM'\n");
            return(1);
         } //Printing out some nice information about the inputs for fun
               char *input_file = argv[2];
               printf("Your Inputed File Format is:    %d \n", file_format);
               printf("This program was called with:   %s \n\n", argv[0]);
               int count;
               if (argc > 1){
                  for (count = 1; count < argc; count++){
                     printf("Input #%d : %s\n", count, argv[count]);
                  }
                  printf("\n");
               }
               //Open Input file
               FILE *fd_header = fopen(input_file, "rb");
               //Get Magic nuber
               int validated_magic_number = get_magic_number(fd_header, file_format);
               if(validated_magic_number == 3){
                  //Reoprn file and send to method
                  FILE *fd_full = fopen(input_file, "rb");
                  P3(fd_full, output_file);
               }
      }else if(file_format == 6){
         //Putting the output file in a variable
         char *output_file = argv[3];
         //checking if the file is .ppm
         int len = strlen(output_file);
         const char *file_extention = &output_file[len-4];
            if(strcmp(".ppm", file_extention) != 0){
            fprintf(stderr, "The out put file must be of file extention '.PPM' \n");
            return(1);
         } //Printing input information
               char *input_file = argv[2];
               printf("Your Inputed File Format is:    %d \n", file_format);
               printf("This program was called with:   %s \n\n", argv[0]);
               int count;
               if (argc > 1){
                  for (count = 1; count < argc; count++){
                     printf("Input #%d : %s\n", count, argv[count]);
                  }
                  printf("\n");
               }
               //Open up the file
               FILE *fd_header = fopen(input_file, "rb");
               //Get magic number
               int validated_magic_number = get_magic_number(fd_header, file_format);
               if(validated_magic_number == 6){
                  //Reopen file send out to method
                  FILE *fd_full = fopen(input_file, "rb");
                  P6(fd_full, output_file);
               }
      }else{
         //Making sure the correct file format was entered
         fprintf(stderr, "Error: The file format must be 3 or 6 \n\n");
         return(1);
   }
   }else if( argc > 4) {
      //Checking for correct amount of arguments
      fprintf(stderr, "Too many arguments supplied.\n");
      return(1);
   }else{
      //Checking for correct amount of arguments
      fprintf(stderr,"Too Little Arguments \n");
      return(1);
   } 
}



int get_magic_number(FILE *fd, int file_format){
   //Make sure there are contents
   if(fd != NULL){
      int c = fgetc(fd);
      //Check if P is at the beginning of the file
      if(c == 'P') {
          c = fgetc(fd);
          //Check if 3 comes after
         if (file_format == 3){
             if(c == '3'){
               return(3);
               //Close up the file
               fclose(fd);
             }else{
               //Error return
               fprintf(stderr, "Error: The Input of '3' does not match the magic number of '6' \n\n");
             }
             //Check if 6 comes after
          }else if(file_format == 6){
            if(c == '6'){
               return (6);
               //Close up the file
               fclose(fd);
            }else{
               //Making sure the formats match
               fprintf(stderr, "Error: The Input of '6' does not match the magic number of '3' \n\n");
            }
          }
      }else{
         fprintf(stderr, "Error: This is not a PPM file \n\n");
         exit(1);
      }

   }else{
      fprintf(stderr, "Error: the input file is null \n\n");
      exit(1);
   }
}

// I didn't write to a buffer here. Hope that was alright.
void P3(FILE *fp, char *output_file ){
   //Open up new file based on input
   FILE *fd_out = fopen(output_file, "wb");
   char ch;
   //Write all contents to the new file using fputc
   while (1) {
      ch = fgetc(fp);
      if (ch == EOF)
         break;
      else
         fputc(ch, fd_out);
   }
   //Close up both files
   fclose(fp);
   fclose(fd_out);
   exit(0);
}

void P6(FILE *fp, char *output_file){
   //Create a buffer for loading
   char buffer[64];
   //Create the new file based on input
   FILE *fd_out = fopen(output_file, "wb");
   int i = 0;
   int c = fgetc(fp);
   //Write file contents into the buffer
   while(c != ' '){
      buffer[i] = c;
      c = fgetc(fp);
      printf("%d", c);
      i += 1;
   }
   //Get the size of the buffer
   int size = atoi(buffer);
   //Write contents from buffer to output file
   fwrite(fp, 64, size, fd_out);
   //Close them up 
   fclose(fp);
   fclose(fd_out);
   exit(0);
}