/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TOK_quote_tokens.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svanmarc <@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 16:11:43 by svanmarc          #+#    #+#             */
/*   Updated: 2024/01/07 16:17:50 by svanmarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_id_of_closing_quote(char *line, int opening_quote_id)
{
	char	quote_type;

	quote_type = line[opening_quote_id];
	opening_quote_id ++;
	while (line[opening_quote_id])
	{
		if (line[opening_quote_id] == quote_type)
			return (opening_quote_id);
		opening_quote_id++;
	}
	return (-1);
}

void	change_env_var_in_token(t_token *token, char quote_type)
{
	if (!token)
		return ;
	if (quote_type == '\'')
		token->change_env_var = 1;
	else if (quote_type == '\"')
		token->change_env_var = 0;
}

int	handle_missing_quote_error(char quote_type, t_token **tokens)
{
	printf(RED"Dont forget to close your quotes [%c]!\n"RST, quote_type);
	free_tokens(tokens);
	return (-1);
}

int	make_quote_token_and_return_id(char *line, int *i, t_token **tokens)
{
	char	quote_type;
	int		space_before;
	char	*val;
	t_token	*tmp;
	int		closing_quote_id;

	if (!line || !tokens || !i)
		return (-1);
	quote_type = line[*i];
	space_before = get_val_of_space_before(line, i);
	closing_quote_id = get_id_of_closing_quote(line, *i);
	if (closing_quote_id == -1)
		return (handle_missing_quote_error(quote_type, tokens));
	val = ft_substr(line, *i + 1, closing_quote_id - *i - 1);
	if (!val || !make_list_tokens(tokens, val, TK_TYPE_STR, space_before))
	{
		free(val);
		free_tokens(tokens);
		return (-1);
	}
	tmp = its_last_token(tokens);
	change_env_var_in_token(tmp, quote_type);
	free(val);
	return (closing_quote_id + 1);
}
