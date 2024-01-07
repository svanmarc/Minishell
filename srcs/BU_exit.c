/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svanmarc <@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 20:08:52 by svanmarc          #+#    #+#             */
/*   Updated: 2024/01/07 11:48:11 by svanmarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

long	ft_atoi_exit(unsigned char *nptr)
{
	long	res;
	int		sign;
	int		i;

	res = 0;
	sign = 1;
	i = 0;
	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
		if (nptr[i++] == '-')
			sign *= -1;
	while (ft_isdigit(nptr[i]))
		res = (res * 10) + (nptr[i++] - '0');
	return (res * sign);
}

int	ft_is_digit_world(unsigned char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(int argc, char **argv, t_data *data)
{
	data->exit = 1;
	if (argc == 2)
	{
		if (ft_is_digit_world((unsigned char *)argv[1]))
		{
			data->last_exit_status = ft_atoi_exit((unsigned char *)argv[1]);
			printf("exit");
			return (data->last_exit_status);
		}
		else
		{
			printf("exit: %s: numeric argument required\n", argv[0]);
			data->last_exit_status = 2;
			return (data->last_exit_status);
		}
	}
	if (argc > 1)
	{
		printf("exit: too many arguments\n");
		data->last_exit_status = 2;
		data->exit = 0;
	}
	return (data->last_exit_status);
}
