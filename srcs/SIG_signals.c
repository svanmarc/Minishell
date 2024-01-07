/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SIG_signals.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svanmarc <@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 11:26:26 by glambrig          #+#    #+#             */
/*   Updated: 2024/01/07 21:54:59 by svanmarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sig_handler_sa(int signal)
{
	if (signal == SIGINT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		printf("\n");
		rl_redisplay();
	}
	else if (signal == SIGQUIT)
	{
		write(STDOUT_FILENO, "\33[2K\r", 5);
		rl_on_new_line();
		rl_redisplay();
		return ;
	}
}

void	parent_sig_handler(int signal)
{
	if (signal == SIGQUIT)
		ft_putstr_fd("Quit", STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
}

int	handle_signal(void)
{
	signal(SIGINT, &sig_handler_sa);
	signal(SIGQUIT, &sig_handler_sa);
	return (0);
}
