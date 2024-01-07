/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabat <mrabat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 12:32:30 by svanmarc          #+#    #+#             */
/*   Updated: 2024/01/07 01:29:08 by mrabat           ###   ########.fr       */
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

void	handle_error_cd(char *path)
{
    if (errno == ENOENT)
        printf(RED"cd: no such file or directory: %s\n"RST, path);
    else if (errno == EACCES)
        printf(RED"cd: permission denied: %s\n"RST, path);
    else if (errno == ENOTDIR)
        printf(RED"cd: not a directory: %s\n"RST, path);
    else
        printf(RED"cd: %s: %s\n"RST, path, strerror(errno));
}
int ft_chdir(char *path, t_data *data)
{
	char	*old_path;

	old_path = getcwd(NULL, 0);
	if (chdir(path) != 0)
	{
        handle_error_cd(path);
		return (1);
	}
	ft_setenv("OLDPWD", old_path, data->env);
	ft_setenv("PWD", path, data->env);
	return (0);

}

int	handle_cd_dash(t_data *data)
{
	char	*old_path;
	char	*new_path;

	old_path = getcwd(NULL, 0);
	new_path = ft_getenv("OLDPWD", data->env);
	if (new_path == NULL)
	{
		printf(RED"cd: OLDPWD not set\n"RST);
		return (1);
	}
	if (chdir(new_path) != 0)
	{
		printf(RED"cd: %s: %s\n"RST, new_path, strerror(errno));
		return (1);
	}
	printf("%s\n", new_path);
	ft_setenv("OLDPWD", old_path, data->env);
	ft_setenv("PWD", new_path, data->env);
	return (0);
}


int	builtin_cd(int argc, char **argv, t_data *data)
{
	int		ret;

	ret = 0;
	if (argc == 1)
		ret = ft_chdir(ft_getenvhome(data->env), data);
	if (argc == 2)
	{
		errno = 0;
		if (strcmp(argv[1], "-") == 0)
			return (handle_cd_dash(data));
		if (strcmp(argv[1], "~") == 0)
			ret = ft_chdir(ft_getenvhome(data->env), data);
		else ft_chdir(argv[1], data);
	}
	if (argc > 2)
	{
		ret = 1;
		if (opendir(argv[1]))
			ret = ft_chdir(argv[1], data);
		else
			printf(RED"cd: too many arguments\n"RST);
	}
	return (ret);
}
