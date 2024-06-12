/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_free2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzaz <hzaz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 12:44:07 by vabertau          #+#    #+#             */
/*   Updated: 2024/05/14 12:38:02 by hzaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_token(t_token *token)
{
	t_token	*tmp;

	while (token != NULL)
	{
		tmp = token;
		token = token->next;
		if (tmp->word != NULL)
			free(tmp->word);
		free(tmp);
	}
}

void	free_bf_newprompt(t_data *data)
{
	if (data->cmdline != NULL)
		free(data->cmdline);
	free_token(data->token);
}

void	free_env(t_data *shell)
{
	t_env	*tmp;

	while (shell->env)
	{
		tmp = shell->env->next;
		if (shell->env->val)
			free(shell->env->val);
		if (shell->env->var)
			free(shell->env->var);
		if (shell->env->var_name)
			free(shell->env->var_name);
		free(shell->env);
		shell->env = tmp;
	}
}
