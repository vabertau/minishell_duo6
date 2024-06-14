/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_free2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabertau <vabertau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 12:44:07 by vabertau          #+#    #+#             */
/*   Updated: 2024/06/14 17:54:15 by vabertau         ###   ########.fr       */
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

void	free_redir(t_exec *tmp_exec)
{
	t_token	*tmp_redir;
	t_token	*to_free;

	tmp_redir = tmp_exec->redir;
	to_free = tmp_exec->redir;
	while (tmp_redir)
	{
		tmp_redir = tmp_redir->next;
		free(to_free);
		to_free = tmp_redir;
	}
}
