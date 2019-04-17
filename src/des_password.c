#include "des.h"
#include "libft.h"
#include "ssl_error.h"
#include <stdlib.h>
#include <unistd.h>

void		des_get_password_from_stdin(t_des_options *options)
{
	char	*password;

	password = getpass("Enter encryption password: ");
	if (password == NULL)
		ssl_error("Something went wrong!");
	if (ft_strlen(password) > 1023)
		ssl_error("Password is too long");
	ft_strcpy(options->password, password);
	if (options->encode == TRUE)
	{
		password = getpass("Repeat encryption password: ");
		if (password == NULL)
			ssl_error("Something went wrong!");
		if (ft_strcmp(options->password, password) != 0)
			ssl_error("Password verifing failed");
	}
	options->password_present = TRUE;
}
