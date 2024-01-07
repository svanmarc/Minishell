/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TOK_tokenize_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svanmarc <@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 16:43:47 by svanmarc          #+#    #+#             */
/*   Updated: 2024/01/07 17:30:34 by svanmarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	make_str_token_and_return_id(char *line, int *i, t_token **tokens)
{
	int		end_str_id;
	char	*val;
	int		type;
	int		space_before;

	if (!line || !tokens || !i)
		return (-1);
	space_before = get_val_of_space_before(line, i);
	end_str_id = get_end_str_id(line, *i);
	type = TK_TYPE_STR;
	val = ft_substr(line, *i, end_str_id - *i);
	if (!val || !make_list_tokens(tokens, val, type, space_before))
	{
		free(val);
		free_tokens(tokens);
		return (-1);
	}
	free(val);
	return (end_str_id);
}

t_token	*make_tokens(t_data *data)
{
	t_token	*current;
	int		i;

	current = NULL;
	i = 0;
	while (data->line[i])
	{
		if (ft_is_white_space(data->line[i]))
			i++;
		else if (strchr("><|&", data->line[i]))
			i = make_op_token_and_return_id(data->line, &i, &current);
		else if (strchr("'\"", data->line[i]))
			i = make_quote_token_and_return_id(data->line, &i, &current);
		else
			i = make_str_token_and_return_id(data->line, &i, &current);
		if (i == -1)
		{
			free_tokens(&current);
			return (NULL);
		}
		if (data->tokens == NULL)
			data->tokens = current;
	}
	return (data->tokens);
}

t_token	*tokenize_line(t_data *data)
{
	if (!data->line || !data)
		return (NULL);
	data->tokens = make_tokens(data);
	return (data->tokens);
}
