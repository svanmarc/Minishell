/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svanmarc <@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 11:53:08 by svanmarc          #+#    #+#             */
/*   Updated: 2024/01/07 12:59:30 by svanmarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	free_tokens_and_ret_neg(t_token **tokens)
{
	free_tokens(tokens);
	return (-1);
}

int	free_tokens_and_val_and_ret_neg(t_token **tokens, char *val)
{
	free(val);
	free_tokens(tokens);
	return (-1);
}

void	free_token(t_token *token)
{
	if (!token)
		return ;
	if (token->val)
	{
		free(token->val);
		token->val = NULL;
	}
	if (token)
		free(token);
}

void	free_tokens(t_token **tokens)
{
	t_token	*current;
	t_token	*next;

	if (!tokens || !*tokens)
		return ;
	current = *tokens;
	while (current)
	{
		next = current->next;
		if (current->val)
		{
			free(current->val);
			current->val = NULL;
		}
		free(current);
		current = next;
	}
	*tokens = NULL;
}
