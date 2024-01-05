/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svanmarc <@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 06:12:02 by svanmarc          #+#    #+#             */
/*   Updated: 2024/01/04 18:47:57 by svanmarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	make_op_token_and_return_id(char *line, int *i, t_token **tokens)
{
	int		type;
	char	*val;
	int		op_id;

	if (!line || !tokens || !i)
		return (-1);
	op_id = *i;
	if (line[op_id + 1] == line[op_id])
	{
		type = get_token_type(line, op_id);
		val = ft_substr(line, op_id, 2);
		if (!val)
		{
			free_tokens(tokens);
			return (-1);
		}
		if (!make_list_tokens(tokens, val, type, 0))
		{
			free(val);
			free_tokens(tokens);
			return (-1);
		}
		free(val);
		op_id += 2;
	}
	else
	{
		type = get_token_type(line, op_id);
		val = ft_substr(line, op_id, 1);
		if (!val)
		{
			free_tokens(tokens);
			return (-1);
		}
		if (!make_list_tokens(tokens, val, type, 0))
		{
			free(val);
			free_tokens(tokens);
			return (-1);
		}
		free(val);
		op_id += 1;
	}
	*i = op_id;
	return (op_id);
}

int	make_quote_token_and_return_id(char *line, int *i, t_token **tokens)
{
	int		closing_quote_id;
	char	*val;
	int		type;
	t_token	*tmp;
	char	quote_type;

	if (!line || !tokens || !i)
		return (-1);
	quote_type = line[*i];
	tmp = NULL;
	closing_quote_id = get_id_of_closing_quote(line, *i);
	if (closing_quote_id == -1)
	{
		printf("don't forget to close the quote [%c]\n", quote_type);
		free_tokens(tokens);
		return (-1);
	}
	val = ft_substr(line, *i + 1, closing_quote_id - *i - 1);
	if (!val)
	{
		free_tokens(tokens);
		return (-1);
	}
	type = TK_TYPE_STR;
	if (!make_list_tokens(tokens, val, type, 0))
	{
		free(val);
		free_tokens(tokens);
		return (-1);
	}
	tmp = its_last_token(tokens);
	if (quote_type == '"')
		tmp->change_env_var = 0;
	else if (quote_type == '\'')
		tmp->change_env_var = 1;
	return (closing_quote_id + 1);
}

int	make_str_token_and_return_id(char *line, int *i, t_token **tokens)
{
	int		end_str_id;
	char	*val;
	int		type;
	int		space_before;

	if (!line || !tokens || !i)
		return (-1);
	if (*i > 0 && ft_is_white_space(line[*i - 1]))
		space_before = 1;
	else
		space_before = 0;
	end_str_id = get_end_str_id(line, *i);
	val = ft_substr(line, *i, end_str_id - *i);
	if (!val)
	{
		free_tokens(tokens);
		return (-1);
	}
	type = TK_TYPE_STR;
	if (!make_list_tokens(tokens, val, type, space_before))
	{
		free(val);
		free_tokens(tokens);
		return (-1);
	}
	free(val);
	return (end_str_id);
}

// t_token	**free_tokens_and_return_null(t_token **tokens)
// {
// 	free_tokens(tokens);
// 	return (NULL);
// }

t_token	*tokenize_line(t_data *data)
{
	t_token	*current;
	int		i;

	if (!data->line || !data)
		return (NULL);
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
