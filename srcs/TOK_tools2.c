/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TOK_tools2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svanmarc <@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 15:53:20 by svanmarc          #+#    #+#             */
/*   Updated: 2024/01/09 15:55:36 by svanmarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int is_redirection(t_token *token)
{
    if (token->type == TK_TYPE_RED_IN
        || token->type == TK_TYPE_RED_IN_DELIM
        || token->type == TK_TYPE_RED_OUT
        || token->type == TK_TYPE_RED_OUT_APPEND)
        return (1);
    return (0);
}