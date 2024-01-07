/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CMD_array_checkexe.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svanmarc <@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 13:04:09 by svanmarc          #+#    #+#             */
/*   Updated: 2024/01/07 13:42:21 by svanmarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_getcmd(char *arg)
{
	return (ft_strjoin("/usr/bin/", arg));
}

char	*ft_checkexe(char *cmd, char **path)
{
	int		i;
	char	*tmp;
	char	*for_exe;

	i = 0;
	while (path[i])
	{
		for_exe = ft_strjoin(path[i], "/");
		tmp = ft_strjoin(for_exe, cmd);
		if (access(tmp, F_OK) == 0)
		{
			free(for_exe);
			return (tmp);
		}
		free(for_exe);
		free(tmp);
		i++;
	}
	return (NULL);
}

void	fill_argv(t_token **tokens, char **argv)
{
	t_token	*tmp;
	int		i;

	i = 0;
	tmp = *tokens;
	while (tmp)
	{
		if (tmp->type == TK_TYPE_RED_IN || tmp->type == TK_TYPE_RED_OUT
			|| tmp->type == TK_TYPE_RED_OUT_APPEND
			|| tmp->type == TK_TYPE_RED_IN_DELIM)
		{
			if (tmp->next && tmp->next->next)
				tmp = tmp->next->next;
			else
				break ;
		}
		else if (tmp->type == TK_TYPE_STR)
		{
			argv[i] = tmp->val;
			i ++;
			tmp = tmp->next;
		}
	}
	argv[i] = NULL;
}

char	**get_cmd_array(t_token **tokens)
{
	int		tk_size;
	char	**argv;

	tk_size = ft_tokensize(tokens);
	argv = (char **)ft_calloc(tk_size + 2, sizeof(char *));
	if (!argv)
		return (NULL);
	fill_argv(tokens, argv);
	return (argv);
}
