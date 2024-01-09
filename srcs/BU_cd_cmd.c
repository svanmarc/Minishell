/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BU_cd_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svanmarc <@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 12:32:30 by svanmarc          #+#    #+#             */
/*   Updated: 2024/01/09 20:44:16 by svanmarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

int	ft_chdir(char *path, t_data *data)
{
	char	*old_path;
	char	*new_path;

	old_path = getcwd(NULL, 0);
	if (chdir(path) != 0)
	{
		handle_error_cd(path);
		return (free(old_path), 1);
	}
	new_path = getcwd(NULL, 0);
	ft_setenv("OLDPWD", old_path, data);
	ft_setenv("PWD", new_path, data);
	free(new_path);
	return (free(old_path), 0);
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
			return (ft_chdir(ft_getenvoldpwd(data->env), data));
		if (strcmp(argv[1], "~") == 0)
			return (ft_chdir(ft_getenvhome(data->env), data));
		return (ft_chdir(argv[1], data));
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
