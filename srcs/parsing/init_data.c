/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabertau <vabertau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 14:48:50 by vabertau          #+#    #+#             */
/*   Updated: 2024/06/12 18:02:07 by vabertau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_data(t_data *data)
{
	data->cmdline = NULL;
	data->token = NULL;
	data->token = NULL;
	data->exec = NULL;
	data->is_bq = NULL;
	data->fullpath_tf = NULL;
	data->heredoc_index = 0;
}
