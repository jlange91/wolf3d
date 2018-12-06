#include "wolf3d.h"

void ft_error(int error)
{
  char *str[15];

  str[0] = "";
  str[1] = "";
  /*
  ** 1 = probleme d'open
  */
  str[2] = "Error: Malloc error\n";
  str[3] = "Error: Parse error\n";
  str[4] = "Error: Only rectangular map\n";
  str[5] = "Error: No space for player in map\n";
  if (error > 1 && error < 15)
    ft_putstr_fd(str[error], 2);
}
