 ///////////////////////////////////////////////////////////////////// TITLE //
 // Ondrei Hornat - c3328588 - University of Newcastle

 ////////////////////////////////////////////////////////////////// CONTENTS //
 // TITLE                       LINE 001
 // CONTENTS                    LINE 004
 // SETUP                       LINE 014
 // ENCRYPTION                  LINE 026
 // DECRYPTION                  LINE 055
 // BRUTE FORCE                 LINE 105
 // END OF HEADER               LINE 133

 ///////////////////////////////////////////////////////////////////// SETUP //
 // Inclusion of headers and Definitions.

 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <sys/stat.h>
 #include <sys/types.h>
 #include <unistd.h>
 #define RE "\033[0;31m"
 #define GR "\033[0;32m"
 #define WH "\033[0m"

 //////////////////////////////////////////////////////////////// ENCRYPTION //
 // Rotation Encryption.
 void rotEncr(char fileText[], int rotAmnt, char fileID[], int vBose) {
   printf("  Adding token...\n");
   strcat(fileText, fileID); // Add token to EOF for auto decryption.
   delay(100);
   printf("  Encrypting text...\n");
   for (int n = 0; fileText[n] != '\0'; n++) { // Loops until EOF is reached.
     for (int r = 0; r <= rotAmnt; r++) { // Rotates by rotation amount.
       if (fileText[n] >= 'A' && fileText[n] < 'Z') {
         fileText[n]++; // If between A and Z, rotate by one.
       } else if (fileText[n] >= 'a' && fileText[n] < 'z') {
         fileText[n]++; // If between a and z, rotate by one.
       } else if (fileText[n] == 'Z') {
         fileText[n] = 'a'; // If at Z, skip to a.
       } else if(fileText[n] == 'z') {
         fileText[n] = 'A'; // If at z, skip to A.
       } else {r = rotAmnt;} // Terminate loop if not a letter.
       if (vBose == 1) { // Live printout while vBose = 1.
         delay(10);
         system("clear");
         printf("Rotating by: %d\n%s\n",rotAmnt,fileText);
         fflush(stdout); // Really only useful here in fast loops. Forces
       }                 // printf to print so theres minimal flickering.
   }}
   delay(100);
   printf("  %sEncryption done.%s\n",GR,WH);
 }

 //////////////////////////////////////////////////////////////// DECRYPTION //
 // Rotation Decryption.
 void rotDecr(char fileText[], char *argv[], char fileID[], int vBose) {
   printf("  Decrypting text...\n");
   int fileLen = strlen(fileText) - 1;
   int rotAmnt = 0;
   if (strcmp(argv[2], "auto") == 0) { // Auto decryption mode.
     do { // Search for amount of rotations to get token back to K.
       if (fileText[fileLen] > 'A' && fileText[fileLen] <= 'Z') {
         fileText[fileLen]--; // If between A and Z, rotate by one.
       } else if (fileText[fileLen] > 'a' && fileText[fileLen] <= 'z') {
         fileText[fileLen]--; // If between a and z, rotate by one.
       } else if (fileText[fileLen] == 'a') {
         fileText[fileLen] = 'Z'; // If at a, skip to Z.
       } else if (fileText[fileLen] == 'A') {
         fileText[fileLen] = 'z'; // If at A, skip to z.
       } rotAmnt++; // Count last rotation.
       if (vBose == 1) { // Live printout while vBose = 1.
         delay(10);
         system("clear");
         printf("Testing Key: %c\n", fileText[fileLen]);
         fflush(stdout); // Really only useful here in fast loops. Forces
       }                 // printf to print so theres minimal flickering.
     } while (fileText[fileLen] != fileID[0] + 1);
   } else {rotAmnt = atoi(argv[2]);} // Use set rotation amount if not auto.
   fileText[fileLen] = '\0'; // Removes the token from the file.
                             // MAY delete last letter of other files, but
   // Start main decryption. // usually just deletes the last '\n'.
   for (int n = 0; fileText[n] != '\0'; n++) { // Loops until EOF is reached.
     for (int r = 0; r <= rotAmnt; r++) { // Rotates by rotation amount.
       if (fileText[n] > 'A' && fileText[n] <= 'Z') {
         fileText[n]--; // If between A and Z, rotate by one.
       } else if (fileText[n] > 'a' && fileText[n] <= 'z') {
         fileText[n]--; // If between a and z, rotate by one.
       } else if (fileText[n] == 'a') {
         fileText[n] = 'Z'; // If at a, skip to Z.
       } else if (fileText[n] == 'A') {
         fileText[n] = 'z'; // If at A, skip to z.
       } else {r = rotAmnt;}
       if (vBose == 1) { // Live printout while vBose = 1.
         delay(10);
         system("clear");
         printf("Rotating by: %d\n%s\n",rotAmnt,fileText);
         fflush(stdout); // Really only useful here in fast loops. Forces
       }                 // printf to print so theres minimal flickering.
   }}
   delay(100);
   printf("  %sDecryption done.%s\n",GR,WH);
 }

//////////////////////////////////////////////////////////////// BRUTE FORCE //
// Basically a can of screen spam.
 void rotGuess(char fileText[], int vBose) {
   printf("  Guessing 52 rotations...\n\n");
   int fileLen = strlen(fileText) - 1, rotAmnt = 0;
   fileText[fileLen] = '\0'; // Hopefully remove only a token or '\n'.
   do { // Loop 52 times to test ALL rotations
     for (int n = 0; fileText[n] != '\0'; n++) { // Loops until EOF is reached.
       if (fileText[n] > 'A' && fileText[n] <= 'Z') {
         fileText[n]--; // If between A and Z, rotate by one.
       } else if (fileText[n] > 'a' && fileText[n] <= 'z') {
         fileText[n]--; // If between a and z, rotate by one.
       } else if (fileText[n] == 'a') {
         fileText[n] = 'Z'; // If at a, skip to Z.
       } else if (fileText[n] == 'A') {
         fileText[n] = 'z'; // If at A, skip to z.
       } // Only one rotation pass needed per iteration.
     }
     delay(20);
     printf("RB-%d: %s\n\n",rotAmnt,fileText); // Print result each loop
     rotAmnt++;            // Make sure it stops at 52 rotations, however
   } while (rotAmnt < 52); // turns out it encounters the same string twice
   delay(300);             // but in opposite caps so could be halved probably.
   printf("\n  %sDecryption done.%s\n",GR,WH);
   printf("  Decrypt RB-(rotations) of the legible text to save as a file.\n\n");
   exit(1);
 }

 ///////////////////////////////////////////////////////////// END OF HEADER //
