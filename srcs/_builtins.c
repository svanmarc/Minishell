/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _builtins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svanmarc <@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 20:03:00 by svanmarc          #+#    #+#             */
/*   Updated: 2024/01/02 12:33:05 by svanmarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_echo(int argc, char **argv, char **env)
{
	int	i;

	i = 1;
	(void)env;
	if (argc > 1 && (ft_strncmp(argv[i], "-n", ft_strlen(argv[i])) == 0))
		i++;
	while (i < argc)
	{
		if (argv[i] != NULL)
		{
			printf("%s", argv[i]);
			if (i + 1 < argc)
				printf(" ");
		}
		i++;
	}
	if ((argc > 1 && ft_strncmp(argv[1], "-n", ft_strlen(argv[1])) != 0)
		|| (argc == 1))
		printf("\n");
	return (0);
}

int	builtin_pwd(int argc, char **argv, char **env)
{
	char	chemin[PATH_MAX];

	(void)argc;
	(void)argv;
	(void)env;
	getcwd(chemin, PATH_MAX);
	printf("%s\n", chemin);
	return (0);
}


