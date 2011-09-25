#include "autols.h"

int main(int argc, char** argv)
{
  struct options options;
  struct dirdata dirdata;

  char human_size_buf[128];
  char header[256];
  char *ignore;
  int string_width;

  /* Parse options and analyze the directory */
  get_options(argc, argv, &options);
  analyze_dir(&options, &dirdata);

  human_size(dirdata.size, human_size_buf, sizeof(human_size_buf));
  string_width = snprintf(header, sizeof(header),
      "[\033[4;33m%s\033[m: %d dirs, %s in %d files (%d hidden)]",
        dirdata.short_name,
        dirdata.dirs_count,
        human_size_buf,
        dirdata.files_count,
        dirdata.hidden_count);

  if (string_width < 0)
    exit(1);

  /* Align the header to the right, with 5 chars for padding */
  string_width = window_columns() - string_width;
  while (string_width-- > -5)
    putc(' ', stdout);
  puts(header);

  if (dirdata.visible_count < options.limit_to_exec_ls) {
    chdir(options.path_name);
    execl("/bin/sh", "sh", "-c", options.ls_command, NULL);
  }

  return 0;
}
