#include "autols.h"

void analyze_dir(const struct options* options, struct dirdata* dd) {

  int path_name_length;
  char file_path[PATH_MAX];

  DIR* directory;
  struct stat st;
  struct dirent* dir_entry;

  /* Erase everything, just for paranoid */
  memset(dd, 0, sizeof(*dd));

  /* dd->short_name will be a copy of the directory name, but if the name is
     bigger than DEFAULT_MAX_NAME_SHOWN we will remove the middle part to adjust it */
  strncpy(dd->short_name, options->path_name, sizeof(dd->short_name));

  path_name_length = strlen(dd->short_name);
  if(path_name_length > options->max_name_shown) {
    char* buf = dd->short_name;
    int middle = options->max_name_shown / 3;
    int final = options->max_name_shown - middle - 3;

    buf[middle] = buf[middle+1] = buf[middle+2] = '.';
    memmove(buf + middle + 3, buf + path_name_length - final, final + 1);
  }

  /* Initialize the counters before traverse the directory */
  dd->dirs_count = -2; /* Skip . & .. */
  dd->files_count = 0;
  dd->visible_count = 0;
  dd->hidden_count = 0;
  dd->size = 0;
  directory = opendir(options->path_name);

  while ((dir_entry = readdir(directory))) {

    /* hidden files are not counted in visible_count */
    if (dir_entry->d_name[0] != '.')
      dd->visible_count++;
    else
      dd->hidden_count++;

    /* Build a full path to stat it */
    if(snprintf(file_path, sizeof(file_path), "%s/%s", options->path_name, dir_entry->d_name) < 0)
      continue;

    if (!stat(file_path, &st)) {
      if (S_ISDIR(st.st_mode))
        dd->dirs_count++;
      else {
        dd->size += st.st_size;
        dd->files_count++;
      }
    }
  }
  closedir(directory);

}
