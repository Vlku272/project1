 ///////////////////////////////////////////////////////////////////// TITLE //
 // Ondrei Hornat - c3328588 - University of Newcastle

 ////////////////////////////////////////////////////////////////// CONTENTS //
 // TITLE                       LINE 001
 // CONTENTS                    LINE 004
 // SETUP                       LINE 014
 // ENCRYPTION                  LINE 029
 // DECRYPTION                  LINE 058
 // IMPORT KEY                  LINE 083
 // BEST GUESS SUBSTITUTION     LINE 100
 // END OF HEADER               LINE 233

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

 // All Substitution specific functions are here.

 //////////////////////////////////////////////////////////////// ENCRYPTION //
 // Substitution Encryption.
 void subEncr(char fileText[], char subKey[], int vBose) {
  printf("  Encrypting text...\n");

  // Define upper/lowercase alphabets
  char upperCase[26] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"; // Define ULetters
  char lowerCase[26] = "abcdefghijklmnopqrstuvwxyz"; // Define LLetters

  // Replaces letters with their counterparts
  // designated in the subKey txt file.
  for (int n = 0; fileText[n] != '\0'; n++) { // Loops until EOF is reached.
    for (int r = 0; r < 26; r++) { // Loops through each letter value 1 - 26.
      if (fileText[n] == upperCase[r] || fileText[n] == lowerCase[r]) {
        fileText[n] = subKey[r]; // Replace if a match is found.
        r = 26; // Stop "r" loop to stop repeat replacements.
      }
    } // Live printout while vBose = 1.
    if (vBose == 1) {
      delay(100);
      system("clear");
      printf("%s\n", fileText);
      fflush(stdout);
    }
  }
  delay(100);
  printf("  %sEncryption done.%s\n",GR,WH);
 }

 //////////////////////////////////////////////////////////////// DECRYPTION //
 // Substitution Decryption.
 void subDecr(char fileText[], char subKey[], int vBose) {
   printf("  Decrypting text...\n");

   // Define default alphabet order.
   char upperCase[26] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
   for (int n = 0; fileText[n] != '\0'; n++) { // Loops until EOF is reached.
    for (int r = 0; r < 26; r++) { // Loops through each letter value 1 - 26.
      if (fileText[n] == subKey[r]) {
        fileText[n] = upperCase[r]; // Replace if match is found.
        r = 26; // Stop "r" loop to stop repeat replacements.
      }
    } // Live printout while vBose = 1.
    if (vBose == 1) {
      delay(100);
      system("clear");
      printf("%s\n", fileText);
      fflush(stdout);
    }
  }
  delay(100);
  printf("  %sDecryption done.%s\n",GR,WH);
 }

 //////////////////////////////////////////////////////////////// IMPORT KEY //
 // subKey Importing
 void subKeyImport(char subKey[], char *argv[]) {
   printf("  Importing subKey...\n");

   // Open designated key file.
   fr = fopen(argv[2], "r");

   // Read in key to array.
   fgets(subKey, 27, fr);

   // Close file.
   fclose(fr);
   printf("  %ssubKey:%s %s\n",GR,WH,subKey);
   delay(100);
 }

 /////////////////////////////////////////////////// BEST GUESS SUBSTITUTION //
 // Attempt to decypher unknown substitution.
 void subGuess(char fileText[], int vBose) {
   printf("  Attempting decryption...\n");
   delay(100);
   int letFreq[26], a, editpos;

   // Define default letter order.
   char letPos[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ", b;

   // Ensure all sections of the counting array start at 0.
   for (int n = 0; n < 26; n++) {letFreq[n] = 0;}

   // Counting how many of each letter are in the text.
   for (int n = 0; fileText[n] != '\0'; n++) { // Loop untill EOF.
     for (int r = 0; r < 26; r++) { // Cycle through letter values 1 - 26.
       if (fileText[n] == letPos[r]) {
         letFreq[r]++; // Add 1 to count if match is found.
         r = 26; // Not neccesary since no changes are made but here anyway.
       }
     }
   }
   do { // Sorting Algorithm. !!! Should probably be a function itself !!!
     editpos = 0;

     // Display live sorting if vBose = 1.
     if (vBose == 1) {
       delay(100); system("clear");
       printf("\n  %sCounting characters, found:%s\n",GR,WH);
       fflush(stdout);
     }

     for (int n = 1; n < 26; n++) { // Loops through letter positions.
       if (letFreq[n] > letFreq[n-1]) { // Compare counts.

         // Sorting process, swaps positions of BOTH count number AND
         // the position of the letter in their arrays, this produces
         // basically a ranked list of letter counts.
         a = letFreq[n-1];           b = letPos[n-1];
         letFreq[n-1] = letFreq[n];  letPos[n-1] = letPos[n];
         letFreq[n] = a;             letPos[n] = b;

         editpos++; // If a change is made its tracked for looping purposes.

       } // Further vBose display.
       if (vBose == 1) {
         printf("  %c: %d\n", letPos[n], letFreq[n]);
         fflush(stdout);
       }

     } // Loops until a pass is completed where no changes to order were made.
   } while (editpos != 0); if (vBose == 1) {
     printf("\n");
     fflush(stdout);
   }

   printf("  Comparing and replacing common characters...\n");

   // Most common letters in the english language:
   char comLet[26] = "ETAOINSRHLDCUMFPGWYBVKJXQZ";
   delay(200);

   // Replaces the letters with "Most frequently used"
   // letters in english according to their new ranks.
   for (int n = 0; fileText[n] != '\0'; n++) { // Loop until EOF.
     for (int r = 0; r < 26; r++) { // Loop through letter values 1 - 26.
       if (fileText[n] == letPos[r]) {
         fileText[n] = comLet[r]; // Replace if match is found.
         r = 26; // Stop "r" loop to stop repeat replacements.
       }
     }
   } delay(200);

   // Reset alphabet order and counts.
   strcpy(letPos, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
   for (int n = 0; n < 26; n++) {letFreq[n] = 0;}

   // Double letter checking. Acts as a second pass which replaces
   // common double letters in the order of how common they are in
   // english.
   for (int n = 1; fileText[n] != '\0'; n++) { // Loop until EOF.
     for (int r = 0; r < 26; r++) { // Loop through letter values 1 - 26.
       if (fileText[n] == letPos[r] && fileText[n] == fileText[n-1]) {
         letFreq[r]++; // Add 1 to count if match is found.
         r = 26; // Not neccesary since no changes are made but here anyway.
       }
     }
   }

   do { // Sorting Algorithm again, see previos one for details.
     editpos = 0;
     if (vBose == 1) {
       delay(100);
       system("clear");
       printf("\n  %sCounting double characters, found:%s\n",GR,WH);
       fflush(stdout);
     }
     for (int n = 1; n < 26; n++) {
       if (letFreq[n] > letFreq[n-1]) {
         a = letFreq[n-1];           b = letPos[n-1];
         letFreq[n-1] = letFreq[n];  letPos[n-1] = letPos[n];
         letFreq[n] = a;             letPos[n] = b;
         editpos++;
       }
       if (vBose == 1) {
         printf("  %c: %d\n", letPos[n], letFreq[n]);
         fflush(stdout);
       }
     }
   } while (editpos != 0); if (vBose == 1) {
     printf("\n");
     fflush(stdout);
   }
   // End Sorting Algorithm.

   printf("  Comparing and replacing common double characters...\n");
   delay(200);

   // Replacing loop described multiple times here already.
   char DcomLet[8] = "SETFLMOP";
   for (int n = 0; fileText[n] != '\0'; n++) {
     for (int r = 0; r < 8; r++) {
       if (fileText[n] == letPos[r] && letFreq[r] != 0) {
         fileText[n] = DcomLet[r]; r = 26;
       }
     }
   } delay(200);

   printf("  %sAttempt Complete.%s\n",GR,WH);
   printf("  Result: \n\n%s\n\n", fileText);
   exit(1); // Guess loop has its own end so it terminates
            // the program to prevent the default end.
 }
 ///////////////////////////////////////////////////////////// END OF HEADER //
