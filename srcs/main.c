/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabat <mrabat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:15:21 by svanmarc          #+#    #+#             */
/*   Updated: 2024/01/08 17:49:14 by mrabat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_minishell(t_data *data)
{
	if (!data->line)
	{
		data->exit = 1;
		data->line = ft_strdup("");
	}
	else
	{
		add_history(data->line);
		data->tokens = tokenize_line(data);
		if (!data->tokens)
			return (handle_error_tokenizing(data));
		else
		{
			if (free_and_exit_if_forbidden_token(data) == 1)
				return (1);
			replace_env_var(data);
			merge_tokens_if_no_space_before(&data->tokens);
			ft_exec_pipe(data);
			ft_ftok(data);
		}
	}
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_data	*data;
	int		ret;

	(void)argc;
	(void)argv;
	data = init_data(env);
	handle_signal();
	while (1)
	{
		data->line = readline("Myshell $>");
		if (ft_minishell(data))
			continue ;
		ft_ftok(data);
		if (data->exit == 1)
			break ;
	}
	ret = data->last_exit_status;
	free_data(data);
	return (ret);
}
