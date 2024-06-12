/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabertau <vabertau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 12:01:21 by vabertau          #+#    #+#             */
/*   Updated: 2024/05/14 12:02:49 by vabertau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	init_pipes(t_data *shell)
{
	int	i;

	i = 0;
	while (i < (shell->nb_cmd - 1))
	{
		if (pipe(shell->pipe_fds + i * 2) < 0)
		{
			perror("pipe");
			return (0);
		}
		i++;
	}
	return (1);
}
