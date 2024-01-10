/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TOK_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svanmarc <@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 17:02:16 by svanmarc          #+#    #+#             */
/*   Updated: 2024/01/10 07:04:35 by svanmarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_merged_tokens(t_token *tmp, t_token *next, char *merged_val)
{
	free(tmp->val);
	tmp->val = merged_val;
	tmp->next = next->next;
	if (tmp->next)
		tmp->next->previous = tmp;
	free(next->val);
	free(next);
}

void	merge_tokens_if_no_space_before(t_token **tokens)
{
	t_token		*tmp;
	char		*merged_val;
	t_token		*next_token;

	tmp = *tokens;
	tmp = tmp->next;
	while (tmp && tmp->next)
	{
		next_token = tmp->next;
		if (tmp->next->space_before == 0
			&& tmp->next->type == TK_TYPE_STR && tmp->type == TK_TYPE_STR)
		{
			merged_val = ft_strjoin(tmp->val, next_token->val);
			if (!merged_val)
				return ;
			handle_merged_tokens(tmp, next_token, merged_val);
		}
		else
			tmp = tmp->next;
	}
}

void	ft_ftok(t_data *data)
{
	if (data->tokens)
	{
		free_tokens(&(data->tokens));
		data->tokens = NULL;
	}
	if (data->line)
	{
		free(data->line);
		data->line = NULL;
	}
}

int	free_and_exit_if_forbidden_token(t_data *data)
{
	t_token	*tmp;

	tmp = data->tokens;
	while (tmp)
	{
		if (is_redirection(tmp) && (!tmp->previous || !tmp->next))
		{
			printf("Myshell ♥‿♥ : syntax error near");
			printf(" unexpected token `newline'\n");
			ft_ftok(data);
			return (1);
		}
		if (tmp->type == TK_TYPE_AND || tmp->type == TK_TYPE_OR)
		{
			printf(RED "sorry, dont use [%s] ", tmp->val);
			printf(RED "we haven't done the bonus\n"RST);
			ft_ftok(data);
			return (1);
		}
		tmp = tmp->next;
	}
	if (tmp)
		ft_ftok(data);
	return (0);
}

int	handle_error_tokenizing(t_data *data)
{
	free(data->line);
	data->line = NULL;
	free_tokens(&data->tokens);
	return (1);
}
