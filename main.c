 ///////////////////////////////////////////////////////////////////// TITLE //
 // Ondrei Hornat - c3328588 - University of Newcastle

 ////////////////////////////////////////////////////////////////// CONTENTS //
 // TITLE                       LINE 001
 // CONTENTS                    LINE 004
 // SETUP                       LINE 020
 // VARIABLES                   LINE 041
 // PROCESS ROUTING             LINE 060
 // DEFAULT DISPLAY             LINE 078
 // VERBOSE HANDLING            LINE 088
 // STAGE ONE REDIRECTS         LINE 100
 // PARAMETER CHECKING          LINE 111
 // BASIC INPUT                 LINE 127
 // FILE IMPORT                 LINE 141
 // STAGE TWO REDIRECTS (MAIN)  LINE 148
 // FILE EXPORT                 LINE 193
 // END OF SCRIPT               LINE 201

 ///////////////////////////////////////////////////////////////////// SETUP //
 // Inclusion of headers, Definitions and beginning of main().

 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <sys/stat.h>
 #include <sys/types.h>
 #include <unistd.h>
 #include "headers/cyphgen.h"
 #include "headers/psky.h"
 #include "headers/rotate.h"
 #include "headers/sub.h"
 #include "headers/gui.h"
 #define RE "\033[0;31m"
 #define GR "\033[0;32m"
 #define WH "\033[0m"
 FILE * fr;
 void main(int argc, char *argv[]) {


 ///////////////////////////////////////////////////////////////// VARIABLES //
 // Variable declarations. These are mostly used for
 // transferring values between functions.

   // Type: char
   char type = 0;        // Used for redirects.
   char fileName[255];   // Stores either file name or ptf.
   char subKey[27];      // Stores key for use in substitution.
   char fileID[2] = "K"; // Used as a reference for rotation decryption.

   // Type: unsigned char
   unsigned char fileText[10000]; // Stores file contents for processing.
   unsigned char fileTextN[1000]; // Used as a buffer for files with
                                  // more than one line.

   // Type: int
   int vBose = 0; // Allows visulistation of processes as they happen.


 /////////////////////////////////////////////////////////// PROCESS ROUTING //
 // Converts argv[1] to a simpler process ID.

   // Reads from the command line arguments what operation to perform.
   if (argc > 1) {
     if (strcmp(argv[1], "-er") == 0) type = 1;  // Rotation Encryption
     if (strcmp(argv[1], "-es") == 0) type = 2;  // Substitution Encryption
     if (strcmp(argv[1], "-dr") == 0) type = 3;  // Rotation Decryption
     if (strcmp(argv[1], "-ds") == 0) type = 4;  // Substitution Decryption
     if (strcmp(argv[1], "-gr") == 0) type = 5;  // Rotation Bruteforce
     if (strcmp(argv[1], "-ep") == 0) type = 6;  // PassKey Encryption
     if (strcmp(argv[1], "-dp") == 0) type = 7;  // PassKey Decryption
     if (strcmp(argv[1], "gui") == 0) type = 8;  // GUI Mode
     if (strcmp(argv[1], "-gs") == 0) type = 9;  // Substitution Guessing
     if (strcmp(argv[1], "-h") == 0)  type = 10; // Show help
   } else {


 /////////////////////////////////////////////////////////// DEFAULT DISPLAY //
 // Basic display to explain operation.

     // Default message (no args given.):
     printf("\n  %sThe Cryptomator 9000%s\n",GR,WH);
     printf("  Append -h for help, or \"gui\" to run in GUI mode.\n\n");
     exit(1);
   }


 ////////////////////////////////////////////////////////// VERBOSE HANDLING //
 // Toggles verbose mode when command is appened
 // by "-v".

   // Toggles the vBose variable to 1 and adjusts "argc"
   // length to prevent breakage in functions.
   if (strcmp(argv[argc-1], "-v") == 0)
   {vBose = 1; argc--; printf("  Verbose On.");}
   if (strcmp(argv[argc-1], "-v") == 0)
   {vBose = 1; argc--; printf("  Verbose On.");}


 /////////////////////////////////////////////////////// STAGE ONE REDIRECTS //
 // Send the program flow to the
 // non-process options.

   // Sends the program flow to menu() if "gui" is given. (gui.h)
   if (type == 8) {menu(); exit(1);}

   // Sends the program flow to the help menu if "-h" is given. (cyphgen.h)
   if (type == 10) {helpF(); exit(1);}


 //////////////////////////////////////////////////////// PARAMETER CHECKING //
 // Stops idiotic behaviour breaking the
 // cypher functions.

   // Takes in ALL arguments and compares them to ensure they
   // are all valid and wont break the following functions. (cyphgen.h)
   printf("\n  Checking Parameters...\n");
   parameterCheck(type, argc, argv);

   // Remove CLOCKS_PER_SEC for this function in "cyphgen.h"
   // to basically disable delays if you really hate them...
   // Program is too efficient for my liking, has no dramatic
   // effect without these :)
   delay(100);


 /////////////////////////////////////////////////////////////// BASIC INPUT //
 // Manual text entry option if the user is too
 // lazy to use files for input.

   // If "-t" is given instead of a file name, ask for text instead.
   if (strcmp(argv[2], "-t") == 0 && (type == 9 || type == 5)) {
     printf("\n  Enter text to process:\n  ");
     scanf("%1000[^\n]", fileText);
   } else if (argc > 3) {
     if (strcmp(argv[3], "-t") == 0 && type != 9 && type != 5) {
       printf("\n  Enter text to process:\n  ");
       scanf("%1000[^\n]", fileText);
     } else goto CONTINUE;
   } // SUPER bandaid solution using goto here, but it was that or
     // have segmentation faults with an argc < 4 at the time of
     // writing.


 /////////////////////////////////////////////////////////////// FILE IMPORT //
 // Reads in the specified file if -t isn't used.

   // Imports the given file to the array "fileText". (cyphgen.h)
   else CONTINUE:readFile(type, fileText, fileTextN, argv);


 //////////////////////////////////////////////// STAGE TWO REDIRECTS (MAIN) //
 // Main flow control to cypher functions.

   // Sends program flow to the right function(s) for the job.
   switch (type) {

     // Rotation encryption. (rotate.h)
     case 1: rotEncr(fileText, atoi(argv[2]), fileID, vBose);
             break;

     // Substitution encryption (sub.h)
     case 2: subKeyImport(subKey, argv); // Imports subKey
             subEncr(fileText, subKey, vBose);
             break;

     // Rotation decryption. (rotate.h)
     case 3: rotDecr(fileText, argv, fileID, vBose);
             break;

     // Substitution decryption (sub.h)
     case 4: subKeyImport(subKey, argv); // Imports subKey
             subDecr(fileText, subKey, vBose);
             break;

     // PassKey (en/de)cription, not part of this assessment. (psky.h)
     // Significantly more secure than rotation and immune to the
     // bruteforce included in this script. Even attempting to
     // bruteforce this with a custom script would take at a minimun
     // 1 mil attempts to try ALL values.
     case 6: pskEncr(fileText, vBose);
             break;
     case 7: pskDecr(fileText, vBose);
             break;

     // Substitution estimation (sub.h)
     case 9: subGuess(fileText, vBose);
             break;

     // Rotation bruteforce. (rotate.h)
     case 5: rotGuess(fileText, vBose);
             break;
     default: exit(1);
    }


 /////////////////////////////////////////////////////////////// FILE EXPORT //
 // writes the result to a file.

    file2Write(type, fileName, argv);
    fileExport(fileName, fileText, vBose);
  }


 ///////////////////////////////////////////////////////////// END OF SCRIPT //
