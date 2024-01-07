/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   REDIR_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svanmarc <@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 11:57:28 by svanmarc          #+#    #+#             */
/*   Updated: 2024/01/07 21:54:40 by svanmarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	redirection_delim(char *delim, int pipe_fd[2])
{
	char	*line;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			printf("Warning: received EOF instead of '%s'\n", delim);
			break ;
		}
		if (ft_strcmp(line, delim) == 0)
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, pipe_fd[1]);
		ft_putstr_fd("\n", pipe_fd[1]);
		free(line);
	}
	exit(0);
}

int	apply_redirection_in_delim(t_data *data, t_token *token)
{
	int		status;
	int		pid;
	int		pipe_fd[2];
	char	*delim;

	delim = token->next->val;
	signal(SIGINT, &parent_sig_handler);
	signal(SIGQUIT, &parent_sig_handler);
	pipe(pipe_fd);
	pid = fork();
	if (pid < 0)
		return (data->last_exit_status = 1, 1);
	if (pid == 0)
		redirection_delim(delim, pipe_fd);
	waitpid(pid, &status, 0);
	dup_close_pipe(pipe_fd, STDIN_FILENO);
	handle_signal();
	if (status && WIFSIGNALED(status))
	{
		data->last_exit_status = 128 + WTERMSIG(status);
		return (1);
	}
	return (0);
}
