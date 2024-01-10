/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ENV_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svanmarc <@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 11:21:18 by svanmarc          #+#    #+#             */
/*   Updated: 2024/01/10 10:04:31 by svanmarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**ft_getenvpath(char **envp)
{
	int		b_find;
	int		i;
	char	**t_path;
	char	*tmp_slip;

	b_find = 0;
	i = 0;
	while (envp[i] && b_find == 0)
	{
		if (ft_strncmp(envp[i], "PATH", 4) == 0)
			b_find = 1;
		i++;
	}
	if (b_find == 0)
		return (NULL);
	tmp_slip = envp[i - 1] + 5;
	t_path = ft_split(tmp_slip, ':');
	return (t_path);
}

char	*ft_getenvoldpwd(char **envp)
{
	int		b_find;
	int		i;
	char	*tmp_slip;

	b_find = 0;
	i = 0;
	while (envp[i] && b_find == 0)
	{
		if (ft_strncmp(envp[i], "OLDPWD", 6) == 0)
			b_find = 1;
		i++;
	}
	if (b_find == 0)
	{
		printf("cd: OLDPWD not set\n");
		return (NULL);
	}
	tmp_slip = envp[i - 1] + 7;
	if (access(tmp_slip, F_OK) == 0)
		printf("%s\n", tmp_slip);
	return (tmp_slip);
}

char	*ft_getenvhome(char **envp)
{
	int		b_find;
	int		i;
	char	*tmp_slip;

	b_find = 0;
	i = 0;
	while (envp[i] && b_find == 0)
	{
		if (ft_strncmp(envp[i], "HOME", 4) == 0)
			b_find = 1;
		i++;
	}
	if (b_find == 0)
	{
		printf("cd: HOME not set\n");
		return (NULL);
	}
	tmp_slip = envp[i - 1] + 5;
	return (tmp_slip);
}

void	sort_env(t_data *data)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (data->env[i])
	{
		j = i + 1;
		while (data->env[j])
		{
			if (ft_strcmp(data->env[i], data->env[j]) > 0)
			{
				tmp = data->env[i];
				data->env[i] = data->env[j];
				data->env[j] = tmp;
			}
			j++;
		}
		i++;
	}
}
