/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabertau <vabertau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:02:38 by vabertau          #+#    #+#             */
/*   Updated: 2024/06/14 17:54:07 by vabertau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_exec(t_data *data)
{
	t_exec	*tmp_exec;
	t_exec	*tmp_exec_tf;

	tmp_exec = data->exec;
	while (tmp_exec)
	{
		free_redir(tmp_exec);
		if (tmp_exec->full_cmd)
			free(tmp_exec->full_cmd);
		if (tmp_exec->split_cmd)
			free(tmp_exec->split_cmd);
		tmp_exec_tf = tmp_exec;
		tmp_exec = tmp_exec->next;
		free(tmp_exec_tf);
	}
}

void	free_fullpath_tf(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_heredoc)
	{
		free(data->fullpath_tf[i]);
		i++;
	}
	free(data->fullpath_tf);
}

// SHOULD NOT EXIT AS MINISHELL IS A LOOP GIVING BACK PROMPT

void	free_all(t_data *data)
{
	int	i;

	i = -1;
	if (data->cmdline != NULL)
		free(data->cmdline);
	if (data->token)
		free_token(data->token);
	if (data->exec)
		free_exec(data);
	if (data->is_bq)
		free(data->is_bq);
	if (data->pipe_fds)
		free(data->pipe_fds);
	if (data->char_env)
	{
		while (data->char_env[++i])
			if (data->char_env[i])
				free(data->char_env[i]);
		free(data->char_env);
	}
	if (data->fullpath_tf)
		free_fullpath_tf(data);
}

void	exit_free(t_data *data, int exit_code)
{
	free_all(data);
	free_env(data);
	exit(exit_code);
}

void	set_exitloop_free(t_data *data)
{
	data->sh_exit_loop = 1;
}
