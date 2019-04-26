 ///////////////////////////////////////////////////////////////////// TITLE //
 // Ondrei Hornat - c3328588 - University of Newcastle

 // NOTE: THIS HEADER IS NOT CANON :)
 // I'll try and make the comments here a bit entertaining, maybe?

 ////////////////////////////////////////////////////////////////// CONTENTS //
 // TITLE                       LINE 001
 // CONTENTS                    LINE 006
 // SETUP                       LINE 015
 // VARIABLES                   LINE 028
 // PROCESS ROUTING             LINE 059   // Best one, but
 // DEFAULT DISPLAY             LINE 089   // it didn't even make 100 lines?

 ///////////////////////////////////////////////////////////////////// SETUP //
 // Instructions for the whingy compiler.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#define RE "\033[0;31m" // Errors spill blood
#define GR "\033[0;32m" // Slimey
#define WH "\033[0m"    // Bleach the terminal

///////////////////////////////////////////////////////////////// ENCRYPTION //
// Spagettification.
 void pskEncr(char fileText[], int vBose) {
   printf("  Encrypting text...\n");
   for (int n = 0; fileText[n] != '\0'; n++) { // NULL: YOU SHALL NOT PASS!
     int rotAmnt = rand() % 52; // Randomness intensifies.
     for (int r = 0; r <= rotAmnt; r++) { // Applied science of random.
       if (fileText[n] >= 'A' && fileText[n] < 'Z') {
         fileText[n]++; // Forwards...
       } else if (fileText[n] >= 'a' && fileText[n] < 'z') {
         fileText[n]++; // Forwards
       } else if (fileText[n] == 'Z') {
         fileText[n] = 'a'; // More Forwards...
       } else if(fileText[n] == 'z') {
         fileText[n] = 'A'; // All the way back to the start!
       } else if (fileText[n] >= '0' && fileText[n] < '9') {
         fileText[n]++; // The numbers have come to play.
       } else if (fileText[n] == '9') {
         fileText[n] = '0'; // Back to the start for them too!
       } else {r = rotAmnt;} // Leave those pesky symbols out of this.
       if (vBose == 1) { // Someone taught this program how to speak...
         system("clear");
         printf("Rotating by: %d\n%s\n",rotAmnt,fileText);
         fflush(stdout); // Make printf behave while going warp speed.
         delay(10);
       }
   }}
   delay(100);
   printf("  %sEncryption done.%s\n",GR,WH);
 } // I wonder if this spagetti could be used for something...

 //////////////////////////////////////////////////////////////// DECRYPTION //
 // Making pasta out of the spagetti.
 void pskDecr(char fileText[], int vBose) {
   printf("  Decrypting text...\n");
   for (int n = 0; fileText[n] != '\0'; n++) { // NULL still holding the fort.
     int rotAmnt = (rand() % 52); // Defeat randomness with more randomness.
     for (int r = 0; r <= rotAmnt; r++) { // Has random gone too far?
       if (fileText[n] > 'A' && fileText[n] <= 'Z') {
         fileText[n]--; // Backwards...
       } else if (fileText[n] > 'a' && fileText[n] <= 'z') {
         fileText[n]--; // Backwards...
       } else if (fileText[n] == 'a') {
         fileText[n] = 'Z'; // No this is getting old.
       } else if (fileText[n] == 'A') {
         fileText[n] = 'z'; // Hop scotch but for ASCII values.
       } else if (fileText[n] > '0' && fileText[n] <= '9') {
         fileText[n]--; // It's the final countdown, do, do, doooo, do...
       } else if (fileText[n] == '0') {
         fileText[n] = '9'; // But it's broken and looping.
       } else {r = rotAmnt;} // Might be bullying the symbols here...
       if (vBose == 1) { // Probably shouldn't have taught this how to talk.
         system("clear");
         printf("Rotating by: %d\n%s\n",rotAmnt,fileText);
         fflush(stdout); // Won't shutup now, oh wait, -v is optional.
         delay(10);
       }
   }}
   delay(100);
   printf("  %sDecryption done.%s\n",GR,WH);
 } // Damn it's over already?
///////////////////////////////////////////////////////////////// END OF FUN //
