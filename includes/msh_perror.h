#ifndef MSH_PERROR_H
# define MSH_PERROR_H

# include <errno.h>

# define ERROR -1

int	msh_perror(char *s1, char *s2, char *msg);
int	msh_perror_exit(char *s1, char *s2, char *msg, int status);

#endif