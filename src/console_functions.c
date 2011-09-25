
#include "autols.h"

int window_columns() {
  struct winsize win;
  ioctl(1, TIOCGWINSZ, &win);
  return win.ws_col;
}

int human_size(long int bytes, char* buffer, int buffer_size)
{
#define H(s,c) if (bytes > c) return snprintf(buffer, buffer_size, "%.1f"s, bytes / (double)c)

  H("G", 1073741824);
  H("M", 1048576);
  H("k", 1024);

  return snprintf(buffer, buffer_size, "%lub", bytes);

#undef H

}
