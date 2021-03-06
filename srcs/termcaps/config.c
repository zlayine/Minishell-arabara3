/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlayine <zlayine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 09:42:22 by zlayine           #+#    #+#             */
/*   Updated: 2020/11/17 16:54:49 by zlayine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

void	display_tmp_data(t_config *config)
{
	int		i;
	char	*tmp;

	i = -1;
	while (config->tmp && config->tmp[++i])
	{
		config->buff = config->tmp[i];
		if (ft_isprint(config->buff))
			print_char(config);
		else if (config->buff == ENTER_BTN || config->buff == 4)
			break ;
	}
	if (config->buff != ENTER_BTN && config->buff != 4)
	{
		ft_del(config->tmp);
		config->tmp = NULL;
		config->buff = 0;
	}
	else
	{
		tmp = ft_strdup(config->tmp + i + 1);
		ft_del(config->tmp);
		config->tmp = tmp;
	}
}

void	init_prompt(t_config *config, int err)
{
	if (config && config->history)
		config = add_history(config);
	else
		init_config_data(config);
	ft_bzero(config->str, 1048576 * sizeof(char));
	config->c = 0;
	config->len = 0;
	config->buff = 0;
	config->control.str = NULL;
	config->control.len = 0;
	config->control.start = 0;
	config->control.cut = 0;
	config->term.c_lflag &= ~(ICANON | ECHO);
	config->cursor = tgetstr("cm", NULL);
	if (tcsetattr(0, 0, &config->term) == -1)
		print_error("Terminal error", 0, 0);
	if (err != 130 && err == 0)
		ft_putstr_fd("\033[1;34mminishell\033[0m\033[1;32m~>\033[0m", 1);
	else if (err != 130)
		ft_putstr_fd("\033[1;34mminishell\033[0m\033[1;31m~>\033[0m", 1);
	get_cursor_pos(config);
	config->x = config->o_x - 1;
	config->y = config->o_y;
	display_cursor(config);
	display_tmp_data(config);
}

void	init_config_data(t_config *config)
{
	char	*term;
	int		ret;

	term = getenv("TERM");
	ret = tgetent(NULL, term);
	if (ret < 1)
		print_error("Terminal error", 0, 0);
	if (tcgetattr(0, &config->term) == -1)
		print_error("Terminal error", 0, 0);
	config->str = malloc(sizeof(char) * 1048576);
	config->history = malloc(sizeof(t_history));
	config->history->data = NULL;
	config->history->prev = NULL;
	config->history->next = NULL;
	config->width = tgetnum("co");
	config->height = tgetnum("li");
	config->tmp = NULL;
	config->o_x = 0;
	config->o_y = 0;
	init_control(&config->control, 0);
}

void	end_terminal(t_config *config)
{
	config->term.c_lflag |= (ICANON | ECHO);
	tcsetattr(0, 0, &config->term);
	if (tcsetattr(0, 0, &config->term) == -1)
		print_error("Terminal error", 0, 0);
}
