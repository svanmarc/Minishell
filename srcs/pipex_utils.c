/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabat <mrabat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 20:43:08 by svanmarc          #+#    #+#             */
/*   Updated: 2024/01/06 22:45:34 by mrabat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_print_token_array(t_token **token_array)
{
	t_token	*tmp;
	int		i;

	i = 0;
	while (token_array[i])
	{
		printf("Pointer _array[%d] = %p\n", i, token_array[i]);
		tmp = token_array[i];
		while (tmp)
		{
			printf("liste du p token_array %s \n", tmp->val);
			tmp = tmp->next;
		}
		i++;
	}
}

t_token	**create_token_arrays(t_token **tokens, int nbpipes)
{
	t_token	*current_token;
	t_token	**token_arrays;
	t_token	*tmp;
	int		i;
	current_token = *tokens;
	i = 0;
	token_arrays = malloc(sizeof(t_token *) * (nbpipes + 1));
	while (current_token)
	{
		token_arrays[i] = current_token;
		while (current_token && current_token->type != TK_TYPE_PIPE)
			current_token = current_token->next;
		i++;
		if (current_token && current_token->type == 44
			&& current_token->next)
		{
			tmp = current_token->next;
			current_token->next->previous = NULL;
			current_token->previous->next = NULL;
			free(current_token->val);
			free(current_token);
			current_token = tmp;
		}
	}
	token_arrays[i] = NULL;
	return (token_arrays);
}

void	ft_fork_and_exec(t_data *data, int *pipefd)
{
	pid_t	pid;
	int	status;

	status = 0;
	pipe(pipefd);
	pid = fork();
	if (pid == 0)
	{
		dup2(pipefd[1], 1);
		close(pipefd[0]);
		close(pipefd[1]);
		ft_exec(data);	
		exit(data->last_exit_status);
	}
	else if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	waitpid(pid, &status, 0);
	dup2(pipefd[0], 0);
	close(pipefd[0]);
	close(pipefd[1]);

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
