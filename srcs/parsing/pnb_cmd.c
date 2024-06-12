/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pnb_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabertau <vabertau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 13:40:54 by vabertau          #+#    #+#             */
/*   Updated: 2024/05/28 20:53:23 by vabertau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
Sets the number of commands by counting pipes
*/
void	nb_cmd(t_data *data)
{
	int		i;
	int		ret;
	char	*cmdline;

	i = 0;
	ret = 1;
	cmdline = data->cmdline;
	while ((i < data->cmdline_len) && cmdline[i])
	{
		if (cmdline[i] == '\'')
			i += skip_sq(&(cmdline[i]));
		if (!cmdline[i])
			break ;
		if (cmdline[i] == '\"')
			i += skip_dq(&(cmdline[i]));
		if (!cmdline[i])
			break ;
		if (cmdline[i] == '|')
			ret++;
		i++;
	}
	data->nb_cmd = ret;
}
