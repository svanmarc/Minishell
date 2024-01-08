/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BU_environement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabat <mrabat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 20:04:59 by svanmarc          #+#    #+#             */
/*   Updated: 2024/01/08 18:28:29 by mrabat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exec_env(t_data *data)
{
	int	i;

	i = 0;
	while (data->env[i])
	{
		if (ft_strchr(data->env[i], '='))
			printf("%s \n", data->env[i]);
		i++;
	}
	return (0);
}
