#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
struct stat st = {0};

#define CL "\033[1;35m"
#define RS "\033[0m"

void main() {
  char cwd[1024], cmd[1024];
  getcwd(cwd, sizeof(cwd));
  if (geteuid() != 0) {
    char cmd[128] = "sudo '";
    strcat(cmd, cwd);
    strcat(cmd, "/install'");
    system(cmd);
    exit(1);
  }
  printf("Preparing to install Cryptr...\n");
  strcat(cwd, "/cryptr");
  strcpy(cmd, "cp '");
  strcat(cmd, cwd);
  strcat(cmd, "' /bin/cryptr > /tmp/dump");
  printf("Running command: %s%s%s\n", CL, cmd, RS);
  system(cmd);
  if (stat("/bin/cryptr", &st) == -1) {
    printf("Installation failed.\n");
  } else {
    printf("Installation successful.\n");
  }
}
