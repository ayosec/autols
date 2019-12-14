#include "autols.h"

void usage(const char* progname) {
  printf(
    "Usage: %s [-l file_limit] [-m name_limit] [-c ls_command] [dirname]\n"
    "\t-l file_limit\tMax number of files to run the ls. (Defaults to %d)\n"
    "\t-m name_limit\tMax length of the directory name in the header. (Defaults to %d, min 10)\n"
    "\t-c ls_command\tCommand to list the directory contents. (Defaults to '" DEFAULT_LS_COMMAND "')\n"
    "\ndirname will be the current directory when omited.\n",
    progname, DEFAULT_LIMIT_TO_EXEC_LS, DEFAULT_MAX_NAME_SHOWN
  );
}

void get_options(int argc, char** argv, struct options* options) {

  int option;

  memset(options, 0, sizeof(*options));
  options->max_name_shown = DEFAULT_MAX_NAME_SHOWN;
  options->limit_to_exec_ls = DEFAULT_LIMIT_TO_EXEC_LS;
  options->ls_command = NULL;

  while ((option = getopt (argc, argv, "hl:m:c:")) != -1) {
    switch(option) {
      case 'l':
        options->limit_to_exec_ls = atoi(optarg);
        break;

      case 'm':
        options->max_name_shown = atoi(optarg);
        if(options->max_name_shown < 10)
          options->max_name_shown = 10;
        break;

      case 'c':
        options->ls_command = strdup(optarg);
        break;

      default:
        usage(argv[0]);
        exit(1);
    }
  }

  /* Check if there is any extra argument. It should be only one */
  switch(argc - optind) {
    case 0:
      /* There is no extra argument, so the target directory will be the current */
      getcwd(options->path_name, sizeof(options->path_name));
      break;

    case 1:
      /* One extra argument, use it as the target directory */
      strncpy(options->path_name, argv[optind], sizeof(options->path_name));
      break;

    default:
      fprintf(stderr, "Too many arguments\n");
      usage(argv[0]);
      exit(2);
  }

  /* If there is no ls command, copy the default */
  if(options->ls_command == NULL)
    options->ls_command = DEFAULT_LS_COMMAND;

}
