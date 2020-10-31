/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaqlzim <aaqlzim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 09:34:03 by aaqlzim           #+#    #+#             */
/*   Updated: 2020/10/31 14:27:10 by aaqlzim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

int		*pipe_fds(int num_pipe, int *fds)
{
	int		i;

	i = -1;
	if (!(fds = (int *)malloc(sizeof(int) * 2 * num_pipe)))
	{
		print_error("malloc", 12, 0);
		exit(1);
	}
	while (++i < num_pipe)
	{
		if (pipe(fds + i * 2) < 0)
		{
			print_error("pipe", 32, 0);
			exit(1);
		}
	}
	return (fds);
}

int		*create_fds(t_cmds *cmds, int j, int *fds)
{
	if (j != 0)
	{
		if (dup2(fds[j - 2], 0) < 0)
		{
			print_error("Dup2", 2, 0);
			exit(1);
		}
	}
	if (cmds->next)
	{
		if (dup2(fds[j + 1], 1) < 0)
		{
			print_error("Dup2", 2, 0);
			exit(1);
		}
	}
	return (fds);
}

void	read_from_stdin(int fd)
{
	char	buff[1024];
	int		r;

	while ((r = read(0, buff, 1024)))
	{
		if (write(fd, buff, r) < r)
			return ;
	}
}

int		open_input(char *args, int append, int ifd)
{
	int		fd;
	int		pipefd[2];

	if (append)
	{
		pipe(pipefd);
		read_from_stdin(pipefd[1]);
		close(pipefd[1]);
		ifd = pipefd[0];
	}
	else
	{
		if ((fd = open(args, O_RDONLY)) < 0)
		{
			print_error(args, errno, 0);
			exit(1);
		}
		ifd = fd;
	}
	return (ifd);
}

int		open_output(t_cmds *cmd, int append)
{
	int		fd;
	int		flag;
	int		flag_mode;

	flag = O_WRONLY | O_CREAT;
	flag_mode = S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH;
	if (append)
		flag = flag | O_APPEND;
	else
		flag = flag | O_TRUNC;
	if ((fd = open(cmd->next->args[0], flag, flag_mode)) < 0)
	{
		print_error(cmd->next->args[0], errno, 0);
		exit(1);
	}
	return (fd);
}
