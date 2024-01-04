/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabat <mrabat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 09:38:25 by svanmarc          #+#    #+#             */
/*   Updated: 2023/12/30 20:21:32 by svanmarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_rediretion_error(t_data *data, t_token *token)
{
	if (!token->next)
	{
		printf("Myshell: syntax error near unexpected");
		printf(" token `newline'\n");
		data->last_exit_status = 2;
		return (1);
	}
	else if (token->next->type != TK_TYPE_STR)
	{
		printf("Myshell: syntax error near unexpected");
		printf(" token `%s'\n", token->next->val);
		data->last_exit_status = 2;
		return (1);
	}
	return (0);
}

int	handle_error_fd(t_data *data, t_token *token, int fd)
{
	printf("Myshell: %s: %s\n", token->next->val, strerror(errno));
	data->last_exit_status = 1;
	if (fd)
		close(fd);
	return (1);
}

void	reset_redirections(t_data *data)
{
	if (data->original_stdout != -1)
	{
		dup2(data->original_stdout, STDOUT_FILENO);
		close(data->original_stdout);
		data->original_stdout = -1;
	}
	if (data->original_stdin != -1)
	{
		dup2(data->original_stdin, STDIN_FILENO);
		close(data->original_stdin);
		data->original_stdin = -1;
	}
	if (data->heredoc_handled == 1)
		unlink (".heredoc");
	data->heredoc_handled = 0;
}
