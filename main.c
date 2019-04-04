 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <sys/stat.h>
 #include <sys/types.h>
 #include <unistd.h>
 FILE * fr;
 struct stat st = {0};

 void encRotate(void) {
   char filePath[255] = "process/", proceed = 0, fileName[255];
   int rotAmnt;
   system("clear");
   printf("\n   Enter the name of the file to encrypt.\n   Note the file should be in process/\n\n   ");
   do {
     scanf(" %255[^\n]", fileName);
     strcat(filePath, fileName);
     fr = fopen(fileName, "r");
     if (stat(filePath, &st) == -1) {
       system("clear");
       printf("\n   That file doesn't exist.\n   Please enter the correct file name.\n\n   ");
       strcpy(filePath, "process/");
     } else {proceed = 1;}
   } while (proceed == 0); proceed = 0;
   fr = fopen(filePath, "r");
   char fileText[255];
   fgets(fileText, 255, fr);
   fclose(fr);
   system("clear");
   printf("\n   How many rotations? (1 - 254)\n\n\n   ");
   do {
     scanf(" %d", &rotAmnt);
     if (rotAmnt > 0 && rotAmnt < 255) {proceed = 1;}
     else {
       system("clear");
       printf("\n   Please enter a valid value.\n\n\n   ");
     }
   } while (proceed == 0); proceed = 0;
   for (int n = 0; fileText[n] != '\0'; n++) {
     for (int r = 0; r <= rotAmnt; r++) {
       if (fileText[n] <= 244) {fileText[n]++;}
       else {fileText[n] = fileText[n] - 223;}
     }
   }
   fr = fopen("result/encrypted.txt", "w");
   fprintf(fr, "%s", fileText);
   fclose(fr);
   system("clear");
   printf("\n   Encryption Complete\n   Result printed to file: encrypted.txt\n   Result: %s\n\n", fileText);
 }

 void decRotate(void) {
   char filePath[255] = "process/", proceed = 0, fileName[255];
   int rotAmnt;
   system("clear");
   printf("\n   Enter the name of the file to decrypt.\n   Note the file should be in process/\n\n   ");
   do {
     scanf(" %255[^\n]", fileName);
     strcat(filePath, fileName);
     fr = fopen(fileName, "r");
     if (stat(filePath, &st) == -1) {
       system("clear");
       printf("\n   That file doesn't exist.\n   Please enter the correct file name.\n\n   ");
       strcpy(filePath, "process/");
     } else {proceed = 1;}
   } while (proceed == 0); proceed = 0;
   fr = fopen(filePath, "r");
   char fileText[255];
   fgets(fileText, 255, fr);
   fclose(fr);
   system("clear");
   printf("\n   How many rotations? (1 - 254)\n\n\n   ");
   do {
     scanf(" %d", &rotAmnt);
     if (rotAmnt > 0 && rotAmnt < 255) {proceed = 1;}
     else {
       system("clear");
       printf("\n   Please enter a valid value.\n\n\n   ");
     }
   } while (proceed == 0); proceed = 0;
   for (int n = 0; fileText[n] != '\0'; n++) {
     for (int r = 0; r <= rotAmnt; r++) {
       if (fileText[n] >= 32) {fileText[n]--;}
       else {fileText[n] = fileText[n] + 223;}
     }
   }
   fr = fopen("result/decrypted.txt", "w");
   fprintf(fr, "%s", fileText);
   fclose(fr);
   system("clear");
   printf("\n   Decryption Complete\n   Result printed to file: decrypted.txt\n   Result: %s\n\n", fileText);
 }


 void main() {
   // Main covers the initial menu, transfer to program and program end.
   char answer[255], type = 0, mode = 0;
   if (stat("result", &st) == -1)  {mkdir("result", 0700);}
   if (stat("process", &st) == -1) {mkdir("process", 0700);}
   do {
     system("clear");
     printf("\n   Welcome, would you like to \x1B[31mencrypt\x1B[37m\n   or \x1B[31mdecrypt\x1B[37m your file?\n   Note, type words that are in \x1B[31mred\x1B[37m to select them.\n\n   ");
     scanf("%s", answer);
     if      (strcmp(answer, "encrypt") == 0) {type = 1;}
     else if (strcmp(answer, "decrypt") == 0) {type = 3;}
     else                                     {type = 0;}
   } while(type == 0);
   do {
     system("clear");
     if (type == 1) {
       printf("\n   Choose encryption mode:\n   Rotation (\x1B[31mrotate\x1B[37m)\n   Substitution (\x1B[31msub\x1B[37m)\n\n   ");
     } else {
       printf("\n   Choose decryption mode:\n   Rotation (\x1B[31mrotate\x1B[37m)\n   Substitution (\x1B[31msub\x1B[37m)\n\n   ");
     }
     scanf("%s", answer);
     if      (strcmp(answer, "rotate") == 0) {mode = 1;}
     else if (strcmp(answer, "sub") == 0)    {mode = 2;}
     else                                    {mode = 0;}
   } while(mode == 0);

   mode = type + mode;
   switch (mode) {
     case 2: encRotate(); break;
     case 3:  break;
     case 4: decRotate(); break;
     case 5:  break;
   }
 }
