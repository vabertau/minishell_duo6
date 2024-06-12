/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pfill_redir2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabertau <vabertau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 14:02:12 by vabertau          #+#    #+#             */
/*   Updated: 2024/06/12 18:08:39 by vabertau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*added to count nb of heredoc to malloc a double chain containing all
the full_pathes
of heredoc to free them after*/
int		nb_heredoc(t_data *data)
{
	t_token	*tmp_token;
	int		i;
	int		nb_heredoc;

	i = 0;
	nb_heredoc = 0;
	tmp_token = data->token;
	while (i < data->nb_tokens)
	{
		if (tmp_token->type == LEFT2)
			nb_heredoc++;
		i++;
		tmp_token = tmp_token->next;
	}
	return (nb_heredoc);
}

/*
Calculates the nb of redirections with the nb of > < >> <<
and fills data->exec->nb_redir
*/

void	nb_redir(t_data *data)
{
	t_exec	*tmp_exec;
	t_token	*tmp_token;
	int		i;
	int		nb_redir;

	i = 0;
	nb_redir = 0;
	tmp_exec = data->exec;
	tmp_token = data->token;
	while (i < data->nb_tokens)
	{
		if (tmp_token->type != WORD && tmp_token->type != PIPE)
			nb_redir++;
		if (tmp_token->type == PIPE || (i + 1) == data->nb_tokens)
		{
			tmp_exec->nb_redir = nb_redir;
			nb_redir = 0;
			tmp_exec = tmp_exec->next;
		}
		i++;
		tmp_token = tmp_token->next;
	}
}