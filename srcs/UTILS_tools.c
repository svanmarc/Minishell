/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UTILS_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svanmarc <@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 18:10:14 by svanmarc          #+#    #+#             */
/*   Updated: 2024/01/07 13:49:34 by svanmarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_is_white_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	return (0);
}

char	*ft_strtrim_whitespace(const char *str)
{
	int		start;
	int		end;
	char	*trimmed;

	if (!str)
		return (NULL);
	start = 0;
	while (str[start] && ft_is_white_space(str[start]))
		start++;
	end = ft_strlen(str) - 1;
	while (end > start && ft_is_white_space(str[end]))
		end--;
	trimmed = ft_substr(str, start, end - start + 1);
	return (trimmed);
}

void	ft_realloc(char **str, int size)
{
	char	*new_str;

	new_str = (char *)ft_calloc(size + 1, sizeof(char));
	if (!new_str)
		return ;
	ft_strlcpy(new_str, *str, size + 1);
	free(*str);
	*str = new_str;
}
