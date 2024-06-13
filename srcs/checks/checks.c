/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabertau <vabertau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 13:33:51 by vabertau          #+#    #+#             */
/*   Updated: 2024/06/13 14:11:34 by vabertau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*returns 1 if cmdline is emtpy*/

void	check_empty(t_data *data)
{
	int		i;
	char	*cmdline;

	i = 0;
	cmdline = data->cmdline;
	while (cmdline[i])
	{
		if (cmdline[i] == ' ' || cmdline[i] == '\t')
			i++;
		else
			return ;
	}
	set_exitloop_free(data);
}

void	checks(t_data *data)
{
	check_unclosedq(data);
	if (data->sh_exit_loop)
		return ;
	check_schar_error(data);
	if (data->sh_exit_loop)
		return ;
	check_pipe_ext(data);
	if (data->sh_exit_loop)
		return ;
}
