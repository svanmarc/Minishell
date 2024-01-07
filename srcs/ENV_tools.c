/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ENV_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svanmarc <@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 11:21:18 by svanmarc          #+#    #+#             */
/*   Updated: 2024/01/07 13:46:09 by svanmarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_setenv(char *name, char *value, char **env)
{
	int		i;
	char	*new_env;
	char	*tmp;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], name, ft_strlen(name)) == 0
			&& env[i][ft_strlen(name)] == '=')
		{
			tmp = ft_strjoin(name, "=");
			new_env = ft_strjoin(tmp, value);
			free(tmp);
			free(env[i]);
			env[i] = new_env;
			return (0);
		}
		i++;
	}
	return (1);
}

char	*ft_getenv(char *name, char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], name, ft_strlen(name)) == 0
			&& env[i][ft_strlen(name)] == '=')
			return (env[i] + ft_strlen(name) + 1);
		i++;
	}
	return (NULL);
}

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
