 ///////////////////////////////////////////////////////////////////// TITLE //
 // Ondrei Hornat - c3328588 - University of Newcastle

 ////////////////////////////////////////////////////////////////// CONTENTS //
 // TITLE                       LINE 001
 // CONTENTS                    LINE 004
 // SETUP                       LINE 017
 // MAIN MENU                   LINE 032
 // TYPE MENU                   LINE 057
 // ROTATIONS MENU              LINE 084
 // PASSKEY MENU                LINE 103
 // SUBSTITUTION KEY MENU       LINE 118
 // FILE NAME AND/OR LOCATION   LINE 136
 // RUN WITH CONFIG             LINE 156
 // END OF HEADER               LINE 166

 ///////////////////////////////////////////////////////////////////// SETUP //
 // Inclusion of headers and Definitions.

 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <sys/stat.h>
 #include <sys/types.h>
 #include <unistd.h>
 #define CY "\033[0;36m"
 #define CB "\033[1;36m"
 #define RE "\033[0;31m"
 #define WH "\033[0m"
 FILE * fr;

 ///////////////////////////////////////////////////////////////// MAIN MENU //
 void menu(void) {
   // Init variables and arrays
   char answer[255], type[4], mode[3], proceed = 0;
   char arg[255], fileName[255];
   type[0] = '-';
   MODE: do {
     // First menu:
     system("clear");
     printf("\n   ==================================================");
     printf("\n   | Welcome, would you like to %sencrypt%s or %sdecrypt%s  |",
     CY,WH,CY,WH);
     printf("\n   | your file? Note, type words that are in %scyan%s   |",
     CY,WH);
     printf("\n   | to select them. Note -b or -back will go back. |");
     printf("\n   ==================================================\n\n   ");

     // Check first responce:
     scanf("%s", answer);
     if (strcmp(answer, "-back") == 0 || strcmp(answer, "-b") == 0 ) exit(1);
     if (strcmp(answer, "encrypt") == 0) type[1] = 'e';
     if (strcmp(answer, "decrypt") == 0) type[1] = 'd';
   } while(type[1] == '\0');
   TYPE: do {

 ///////////////////////////////////////////////////////////////// TYPE MENU //
     // Second menu:
     system("clear");
     printf("\n   =================================================");
     printf("\n   | Choose mode:                                  |");
     printf("\n   | Rotation (%srotate%s)                             |",CY,WH);
     printf("\n   | Substitution (%ssub%s)                            |",CY,WH);
     if (type[1] == 'd') {
     printf("\n   | Rotation Bruteforce (%sbrute%s)                   |",CY,WH);
     printf("\n   | Substitution Guessing (%ssubguess%s)              |",CY,WH);
     }
     printf("\n   | Passkey (%spasskey%s)                             |",CY,WH);
     printf("\n   =================================================\n\n   ");
     scanf("%s", answer);
     if (strcmp(answer, "-back") == 0 || strcmp(answer, "-b") == 0 ) goto MODE;

     // Check second response:
     if (strcmp(answer, "rotate") == 0)  type[2] = 'r';
     if (strcmp(answer, "sub") == 0)     type[2] = 's';
     if (strcmp(answer, "passkey") == 0) type[2] = 'p';
     if (type[1] == 'd') {
       if (strcmp(answer, "brute") == 0)    strcpy(type, "-gr");
       if (strcmp(answer, "subguess") == 0) strcpy(type, "-gs");
     }
   } while(type[2] == '\0');
   ARG: system("clear");

 //////////////////////////////////////////////////////////// ROTATIONS MENU //
   // Rotations for Rotational Encryption:
   if (strcmp(type, "-er") == 0 || strcmp(type, "-dr") == 0) {
     printf("\n   How many rotations? (0+)");
     if (strcmp(type, "-dr") == 0) {
       printf("\n   Use \"auto\" if the file was made");
       printf("\n   using this program.\n\n   ");
     } else printf("\n\n   ");
     do {
       scanf("%s", arg);
       if (strcmp(arg, "-back") == 0 || strcmp(arg, "-b") == 0 ) {goto TYPE;}
       if (atoi(arg) >= 0) {proceed = 1;}
       else {
         system("clear");
         printf("\n   Please enter a valid value.\n\n   ");
       }
     } while (proceed == 0); proceed = 0;
   }

 ////////////////////////////////////////////////////////////// PASSKEY MENU //
   // Passkey for Passkey Encryption:                 Even if it's not canon :)
   if (strcmp(type, "-ep") == 0 || strcmp(type, "-dp") == 0) {
     printf("\n   Enter a passkey. (1 - 999999)\n\n   ");
     do {
       scanf("%s", arg);
       if (strcmp(arg, "-back") == 0 || strcmp(arg, "-b") == 0 ) goto TYPE;
       if (atoi(arg) > 0 && atoi(arg) < 1000000) proceed = 1;
       else {
         system("clear");
         printf("\n   Please enter a valid passkey.\n\n   ");
       }
     } while (proceed == 0); proceed = 0;
   } system("clear");

 ///////////////////////////////////////////////////// SUBSTITUTION KEY MENU //
   // Get subKey name or Path:
   if (type[2] == 's' || type[2] == 'g') {
     printf("\n   Enter the name of the subKey file to use.\n");
     printf("   The file should be next to a.out and should\n");
     printf("   contain ONE of each letter.\n\n   ");
     do {
       scanf(" %255[^\n]", arg);
       if (strcmp(arg, "-back") == 0 || strcmp(arg, "-b") == 0 ) {goto TYPE;}
       if (stat(arg, &st) == -1) {
         system("clear");
         printf("\n   That file doesn't exist.\n   Please enter the correct");
         printf("file name.\n\n   ");
       } else proceed = 1;
     } while (proceed == 0); proceed = 0;
   }
   LOCATION: system("clear");

 ///////////////////////////////////////////////// FILE NAME AND/OR LOCATION //
   // Get File name or Path:
   if (type[1] == 'e') printf("\n   Enter the name of the file to encrypt.\n");
   else                printf("\n   Enter the name of the file to decrypt.\n");
   printf("   The file should be next to a.out\n");
   printf("   otherwise provide the whole path.\n");
   printf("   Entering '-t' here will allow text\n");
   printf("   input later.\n\n   ");
   do {
     scanf(" %255[^\n]", fileName);
     if (strcmp(fileName, "-back") == 0 || \
     strcmp(fileName, "-b") == 0 ) goto ARG;
     if (stat(fileName, &st) == -1 && strcmp(fileName, "-t") != 0) {
       system("clear");
       printf("\n   That file doesn't exist.\n   Please enter the correct");
       printf(" file name.\n\n   ");
     } else {proceed = 1;}
   } while (proceed == 0); proceed = 0;
   system("clear");

 /////////////////////////////////////////////////////////// RUN WITH CONFIG //
   // Relaunch with configured arguments:
   if (type[1] == 'g') {
     char *argv[] = {"./a.out", type, fileName};
     execv("./a.out", argv);
   } else {
     char *argv[] = {"./a.out", type, arg, fileName};
     execv("./a.out", argv);
   }
 } // That was alot of printfing crap, wow.
 ///////////////////////////////////////////////////////////// END OF HEADER //
