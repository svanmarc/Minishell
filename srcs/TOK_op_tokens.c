/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TOK_op_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svanmarc <@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 16:12:19 by svanmarc          #+#    #+#             */
/*   Updated: 2024/01/07 17:21:14 by svanmarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_op_id(char *line, int op_id)
{
	if (line[op_id + 1] == line[op_id])
		op_id += 2;
	else
		op_id += 1;
	return (op_id);
}

char	*get_val_of_op_token(char *line, int op_id)
{
	char	*val;

	if (line[op_id + 1] == line[op_id])
		val = ft_substr(line, op_id, 2);
	else
		val = ft_substr(line, op_id, 1);
	return (val);
}

int	make_op_token_and_return_id(char *line, int *i, t_token **tokens)
{
	int		type;
	char	*val;
	int		op_id;
	int		space_before;

	if (!line || !tokens || !i)
		return (-1);
	op_id = *i;
	space_before = get_val_of_space_before(line, i);
	type = get_token_type(line, op_id);
	val = get_val_of_op_token(line, op_id);
	if (!val || !make_list_tokens(tokens, val, type, space_before))
	{
		free(val);
		free_tokens(tokens);
		return (-1);
	}
	free(val);
	op_id = get_op_id(line, op_id);
	*i = op_id;
	return (op_id);
}
