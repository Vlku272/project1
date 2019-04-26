///////////////////////////////////////////////////////////////////// TITLE //
// Ondrei Hornat - c3328588 - University of Newcastle

////////////////////////////////////////////////////////////////// CONTENTS //
// TITLE                       LINE 001
// CONTENTS                    LINE 004
// SETUP                       LINE 016
// DELAY                       LINE 033
// HELP                        LINE 039
// PARAMETER CHECKING          LINE 067
// READ FILES                  LINE 117
// NAME FILES                  LINE 134
// WRITE FILES                 LINE 160
// END HEADER                  LINE 179

///////////////////////////////////////////////////////////////////// SETUP //
// Inclusion of headers and Definitions.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#define RE "\033[0;31m"
#define GR "\033[0;32m"
#define WH "\033[0m"
struct stat st = {0};
FILE * fr;
clock_t clock();

 ///////////////////////////////////////////////////////////////////// DELAY //
 void delay(clock_t msec) {                                   // Put on a show!
   msec = clock() + msec*CLOCKS_PER_SEC/1000; while (clock() < msec);
   // Wait while time is less than start time plus delay.
 }

/////////////////////////////////////////////////////////////////////// HELP //
void helpF(void) {
  printf("\n  =============== %sHelp%s ===============\n",GR,WH);
  printf("  ./a.out <type> <arg> <path to file>\n");
  printf("  Current limits with processing files:\n");
  printf("  1k char per line, 10k total char.\n");
  printf("  %sType:%s <type>\n",GR,WH);
  printf("  \"-er\" - Rotation Encryption.\n");
  printf("  \"-es\" - Substitution Encryption.\n");
  printf("  \"-ep\" - Passkey Encryption.\n");
  printf("  \"-dr\" - Rotation Decryption.\n");
  printf("  \"-ds\" - Substitution Decryption.\n");
  printf("  \"-dp\" - Passkey Decryption.\n");
  printf("  %sArguments:%s <arg>\n",GR,WH);
  printf("  For er - Rotation Amount.\n");
  printf("  For es - Substitution Key file.\n");
  printf("  For ep - Passkey (1-999999).\n");
  printf("  For dr - none, aquired from .crypt file.\n");
  printf("  For ds - Substitution Key file.\n");
  printf("  For dp - Passkey (1-999999).\n\n");
  printf("  '-t' instead of ptf enables typing text.\n");
  printf("  Appending -v at the end of the command\n");
  printf("  will enable verbose.\n\n");
  printf("  Run \"./a.out gui\" for GUI mode,\n");
  printf("  Run in GUI mode if this help page wasn't\n");
  printf("  as helpful as it needed to be.\n\n");
}

///////////////////////////////////////////////////////// PARAMETER CHECKING //
// *Not guaranteed to stop spontaneos combustion of computer,
// and comes with absolutely NO warrenty, even if you ask nicely.
void parameterCheck(char type, int argc, char *argv[]) {
  if (type == 0) { // Strait up stop if not even an operation could be chosen.
    printf("  %sError:%s Invalid type. Append -h for help\n\n",RE,WH);
    exit(1);
  } // Checking of both existence of the reference file and cmd length.
  if (stat(argv[3], &st) == -1 && type != 5 && type != 9 && strcmp(argv[3], "-t") != 0) {
    printf("  %sError:%s Specified file doesn't exist.\n\n",RE,WH); exit(1);
  } else if (argc < 4  && type != 5 && type != 9) {
    printf("  %sError:%s Too few arguments.\n\n",RE,WH); exit(1);
  } else if (argc > 4 && type != 3 && type != 5 && type != 9) {
    printf("  %sError:%s Too many arguments.\n\n",RE,WH); exit(1);
  } // Same, needed to be different for different operations.
  if (stat(argv[2], &st) == -1 && (type == 5 || type == 9) && strcmp(argv[2], "-t") != 0) {
    printf("  %sError:%s Specified file doesn't exist.\n\n",RE,WH); exit(1);
  } else if (argc < 3 && (type == 5 || type == 9)) {
    printf("  %sError:%s Too few arguments.\n\n",RE,WH); exit(1);
  } else if (argc > 3 && (type == 5 || type == 9)) {
    printf("  %sError:%s Too many arguments.\n\n",RE,WH); exit(1);
  } // Prevent negative rotations because negative attitudes are not permitted :)
  if (type == 1 || type == 3) {
    if (atoi(argv[2]) < 1 && strcmp(argv[2], "auto") != 0) {
      printf("  %sError:%s Rotation amount too small or use \"auto\"\n\n",RE,WH);
      exit(1);

    }
  } // Keep passKey safely inside an int.
  if (type == 6 || type == 7) {
    int passKey = atoi(argv[2]);
    if (passKey < 1) {
      printf("  %sError:%s Passkey too small\n\n",RE,WH);
      exit(1);
    } else if (passKey > 999999) {
      printf("  %sError:%s Passkey too large\n\n",RE,WH);
      exit(1);
    }
    srand(passKey); // Seed rand for the actual cypher.
  }

  // Make sure a subKey is actually provided for substitution.
  if (stat(argv[2], &st) == -1 && (type == 2 || type == 4 || type == 9)) {
    printf("  %sError:%s Specified Key doesn't exist.\n\n",RE,WH);
    exit(1);
  }
  delay(100);
  printf("  %sParameters OK.%s\n",GR,WH);
}

///////////////////////////////////////////////////////////////// READ FILES //
// Read in files completely into an array so the files aren't laying around.
void readFile(char type, char fileText[], char fileTextN[], char *argv[]) {
  printf("  Opening file...\n");
  if (type != 5 && type != 9) fr = fopen(argv[3], "r");
  if (type == 5 || type == 9) fr = fopen(argv[2], "r");
  delay(100);
  printf("  Reading text...\n");
  while (fgets(fileTextN, 1000, fr)) { // Read in one line.
    strcat(fileText, fileTextN); // Add that line to the main text.
  }
  delay(200);
  printf("  Closing file...\n");
  fclose(fr); // Close the file for safety.
  delay(100);
}

///////////////////////////////////////////////////////////////// NAME FILES //
// Determine where the text will be dumped.
void file2Write(int type, char fileName[], char *argv[]) {
  printf("  Generating file...\n");

  // If file was used to input, use that name, text is given a default file name
  if (type != 5 && type != 9 && strcmp(argv[3], "-t") != 0) {
    strcpy(fileName, argv[3]);
  } else if ((type == 5 || type == 9) && strcmp(argv[3], "-t") != 0) {
    strcpy(fileName, argv[3]);
  } else strcpy(fileName, "output.txt"); // Default for manual input.

  // Change file extensions. Just overcomplicated things but sure here it is.
  // At least the old file wasn't overwritten while I was testing stuff.
  if ((type == 1 || type == 2 || type == 6) && strcmp(argv[3], "-t")) {
    int naLen = strlen(fileName) - 4;
    for (int n = naLen; n <= 5; n++) {fileName[n] = '\0';}
    strcat(fileName, ".crypt");
  } if ((type == 3 || type == 4 || type == 7) && strcmp(argv[3], "-t")) {
    int naLen = strlen(fileName) - 6;
    for (int n = naLen; n <= 7; n++) {fileName[n] = '\0';}
    strcat(fileName, ".txt");
  }
  delay(100);
}

//////////////////////////////////////////////////////////////// WRITE FILES //
// Dump the text array into the file.
void fileExport(char fileName[], char fileText[], int vBose) {
  fr = fopen(fileName, "w");
  printf("  Writing result to %s...\n", fileName);
  if (stat(fileName, &st) == -1) { // Check the file was actully made before
                                   // printing.
    printf("  %sError:%s File couldn't be saved.\n\n",RE,WH);
    exit(1);
  }
  fprintf(fr, "%s", fileText); // Dump here.
  delay(200);
  printf("  Closing file...\n");
  fclose(fr); // Seal up the file for viewing later.
  delay(100);
  printf("\n  %sComplete.%s\n",GR,WH);
  if (vBose == 0) {printf("  Result: \n\n%s\n\n", fileText);} else {printf("\n");}
  exit(1); // Print result if it wasn't already printed somewhere by verbose.
}
//////////////////////////////////////////////////////////// END ABOMANATION //
