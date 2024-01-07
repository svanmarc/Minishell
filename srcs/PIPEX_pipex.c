/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svanmarc <@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 20:00:19 by svanmarc          #+#    #+#             */
/*   Updated: 2024/01/07 10:36:19 by svanmarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_count_pipe(t_token **tokens, int *count)
{
	t_token	*tmp;

	*count = 1;
	tmp = *tokens;
	while (tmp)
	{
		if (tmp->type == TK_TYPE_PIPE && !tmp->next)
		{
			*count = 0;
			return ;
		}
		if (tmp->type == TK_TYPE_PIPE)
			*count = *count + 1;
		tmp = tmp->next;
	}
}

void	ft_launch_cmd(int nbcmd, t_data *data, int *pipefd)
{
	int		i;
	t_token	**token_arrays;

	i = 0;
	token_arrays = create_token_arrays(&data->tokens, nbcmd);
	data->default_stdin = dup(STDIN_FILENO);
	data->default_stdout = dup(STDOUT_FILENO);
	while (i + 1 < nbcmd)
	{
		data->tokens = token_arrays[i];
		ft_fork_and_exec(data, pipefd);
		i++;
		free_tokens(&data->tokens);
	}
	data->tokens = token_arrays[i];
	if (data->tokens->val)
		ft_exec(data);
	dup2(data->default_stdin, STDIN_FILENO);
	dup2(data->default_stdout, STDOUT_FILENO);
	close(data->default_stdout);
	close(data->default_stdin);
	free(token_arrays);
}

int	ft_exec_pipe(t_data *data)
{
	int	nbcmd;
	int	pipefd[2];

	nbcmd = 0;
	ft_count_pipe(&data->tokens, &nbcmd);
	if (nbcmd > 0)
		ft_launch_cmd(nbcmd, data, pipefd);
	else
	{
		printf("need command for pipe \n");
		return (1);
	}
	return (0);
}
