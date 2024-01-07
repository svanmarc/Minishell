/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svanmarc <@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 20:43:08 by svanmarc          #+#    #+#             */
/*   Updated: 2024/01/07 11:15:23 by svanmarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*sup_current_token(t_token *current)
{
	t_token	*tmp;

	tmp = current->next;
	current->next->previous = NULL;
	current->previous->next = NULL;
	free(current->val);
	free(current);
	current = tmp;
	return (current);
}

t_token	**create_token_arrays(t_token **tokens, int nbpipes)
{
	t_token	*current;
	t_token	**token_arrays;
	int		i;

	current = *tokens;
	i = 0;
	token_arrays = malloc(sizeof(t_token *) * (nbpipes + 1));
	while (current)
	{
		token_arrays[i] = current;
		while (current && current->type != TK_TYPE_PIPE)
			current = current->next;
		i++;
		if (current && current->type == 44 && current->next)
			current = sup_current_token(current);
	}
	token_arrays[i] = NULL;
	return (token_arrays);
}

void	dup_close_pipe(int *pipefd, int fd)
{
	dup2(pipefd[fd], fd);
	close(pipefd[0]);
	close(pipefd[1]);
}

void	ft_fork_and_exec(t_data *data, int *pipefd)
{
	pid_t	pid;
	int		status;

	status = 0;
	pipe(pipefd);
	pid = fork();
	if (pid == 0)
	{
		dup_close_pipe(pipefd, 1);
		ft_exec(data);
		exit(data->last_exit_status);
	}
	else if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	waitpid(pid, &status, 0);
	dup_close_pipe(pipefd, 0);
	if (WIFEXITED(status))
		data->last_exit_status = WEXITSTATUS(status);
	else
		data->last_exit_status = 128 + WTERMSIG(status);
}

void	ft_wait_end(int nbcmd, int i, t_data *data)
{
	int	status;

	status = 0;
	while (i < nbcmd)
	{
		wait(&status);
		i++;
	}
	if (WIFEXITED(status))
		data->last_exit_status = WEXITSTATUS(status);
	else
		data->last_exit_status = 128 + WTERMSIG(status);
}
