#include "../../includes/shell.h"

void	print_error(char *cmd, int err, int iscmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	if (err == 2 && iscmd)
		ft_putstr_fd(": command not found", 2);
	else 
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(err), 2);
	}
	ft_putchar_fd('\n', 2);
}