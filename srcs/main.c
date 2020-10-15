#include "../includes/shell.h"

void	free_shell(t_shell *shell)
{
	int i;
	t_cmds *tmp;
	// free all the data and re-init
	free(shell->line);
	while(shell->cmds)
	{
		i = 0;
		while (shell->cmds->args[i])
		{
			ft_del(*(shell->cmds->args));
			i++;
		}
		ft_del(shell->cmds->args);
		ft_del(shell->cmds->cmd);
		tmp = shell->cmds->next;
		ft_del(shell->cmds);
		shell->cmds = tmp;
	}
	shell->cmds = NULL;
}
int		command_line(t_shell *shell)
{
	int		r;
	int		status;

	r = 1;
	status = 1;
	
	while (status)
	{
		ft_putstr_fd("minishell~>", 1);
		r = get_next_line(0, &shell->line);
		if (ft_strlen(shell->line))
			status = run_commands(shell);
		//free_shell(shell);
	}
	return (status);
}

void	sig_handle_ctrl_c(int signal)
{
	/* if (signal)
		exit(EXIT_FAILURE); */
		kill(0, SIGINT);
		//signal ( SIGINT , sig_handle_ctrl_c);
}

int     main(int argc, char **argv, char **envp)
{
	t_shell shell;

	if (argc && argv)
	{
		shell.env = ft_arrdup(envp);
		signal(SIGINT, sig_handle_ctrl_c);
		while (command_line(&shell))
			;
	}
    return (0);
}