/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabertau <vabertau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 13:59:10 by vabertau          #+#    #+#             */
/*   Updated: 2024/06/14 17:26:38 by vabertau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* Added for $unexisting expands : it creates a \0 chain in
split_cmd that need to
be removed. If not $unexisting tries to execute \0 chain and prints command
not found */
void	rm_nullcmd(t_data *data)
{
	t_exec	*cur_cmd;
	int		j;
	int		i;

	cur_cmd = data->exec;
	j = 0;
	while (cur_cmd)
	{
		i = 0;
		while (cur_cmd->split_cmd && cur_cmd->split_cmd[i])
		{
			if (cur_cmd->split_cmd[i][0] == '\0')
			{
				j = i;
				while (cur_cmd->split_cmd[j])
				{
					cur_cmd->split_cmd[j] = cur_cmd->split_cmd[j + 1];
					j++;
				}
			}
			i++;
		}
		cur_cmd = cur_cmd->next;
	}
}

/*
Take the tokens and organize them in a structure containing
all the elements necessary to execve
*/
void	parser(t_data *data)
{
	nb_cmd(data);
	malloc_exec(data);
	init_exec(data);
	fill_full_cmd(data);
	fill_split_cmd(data);
	check_redirfile(data);
	if (data->sh_exit_loop)
		return ;
	fill_redir(data);
	data->pipe_fds = malloc(sizeof(int) * (2 * (data->nb_cmd - 1)));
	if (!data->pipe_fds)
		return ;
	rm_nullcmd(data);
}
