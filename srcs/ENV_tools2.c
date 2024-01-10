/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ENV_tools2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svanmarc <@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 10:03:41 by svanmarc          #+#    #+#             */
/*   Updated: 2024/01/10 10:05:17 by svanmarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_setenv(char *name, char *value, t_data *data)
{
	int		i;
	char	*tmp;

	i = 0;
	while (data->env[i] != NULL)
	{
		if (ft_strncmp(data->env[i], name, ft_strlen(name)) == 0
			&& data->env[i][ft_strlen(name)] == '=')
		{
			tmp = data->env[i];
			free(tmp);
			tmp = NULL;
			tmp = ft_strjoin(name, "=");
			data->env[i] = ft_strjoin(tmp, value);
			free(tmp);
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
