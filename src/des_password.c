#include "des.h"
#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

static void	error(char *error_msg)
{
	ft_dprintf(2, "%s\n", error_msg);
	exit(-1);
}

void		des_get_password_from_stdin(t_des_options *options)
{
	char	*password;

	password = getpass("Enter encryption password: ");
	if (password == NULL)
		error("Something went wrong!");
	if (ft_strlen(password) > 1023)
		error("Password is too long");
	ft_strcpy(options->password, password);
	password = getpass("Repeat encryption password: ");
	if (password == NULL)
		error("Something went wrong!");
	if (ft_strcmp(options->password, password) != 0)
		error("Password verifing failed");
	options->password_present = TRUE;
}
