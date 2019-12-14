#include <dirent.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/wait.h>

#define DEFAULT_MAX_NAME_SHOWN 60
#define DEFAULT_LIMIT_TO_EXEC_LS 40
#define DEFAULT_LS_COMMAND "ls --color=auto --group-directories-first -F"

struct dirdata {
  int dirs_count;
  int files_count;
  int visible_count;
  int hidden_count;
  unsigned long int size;
  char short_name[PATH_MAX];
};

struct options {
  int max_name_shown;
  int limit_to_exec_ls;
  char *ls_command;
  char path_name[PATH_MAX];
};

int window_columns();
int human_size(long int bytes, char* buffer, int buffer_size);
void analyze_dir(const struct options* options, struct dirdata* dd);
void get_options(int argc, char** argv, struct options* options);
