/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spaces_bet_tokens2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabertau <vabertau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 12:51:15 by vabertau          #+#    #+#             */
/*   Updated: 2024/06/14 18:36:18 by vabertau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	fixed_cmdline_len(char *cmdline)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (cmdline[i])
	{
		i += skip_sq(&(cmdline[i]));
		if (!cmdline[i])
			break ;
		if (cmdline[i] == '<' || cmdline[i] == '>' || cmdline[i] == '|')
		{
			if (i > 0 && cmdline[i - 1] != '<' && cmdline[i - 1] != '>'
				/*&& cmdline[i - 1] != '|'*/ && cmdline[i - 1] != ' ')
				ret++;
			if (cmdline[i + 1] != '<' && cmdline[i + 1] != '>' /*&& cmdline[i
					+ 1] != '|'*/ && cmdline[i + 1] != ' ')
				ret++;
		}
		i++;
	}
	return (ret + ft_strlen(cmdline));
}

/* Searches for a missing space before a special character,
	and adds it if it is missing
 */
int	add_space_bf(int i, char *ret, char *tmp)
{
	if (i > 0 && ret[i - 1] != '<' && ret[i - 1] != '>' /*&& ret[i - 1] != '|'*/
		&& ret[i - 1] != ' ')
	{
		ft_strlcpy(&(ret[i + 1]), &(tmp[i]), ft_strlen(&(ret[i])) + 1);
		ret[i] = ' ';
		return (1);
	}
	return (0);
}

/* Searches for a missing space after a special character,
	and adds it if it is missing
 */
void	add_space_af(int i, int sp_bf, char *ret, char *tmp)
{
	if (tmp[i + 1] != '<' && tmp[i + 1] != '>' /*&& tmp[i + 1] != '|'*/
		&& tmp[i + 1] != ' ') /*|| ((tmp[i + 1] == '<' || tmp[i + 1] == '>') && tmp[i] == '|'))*/
	{
		if (sp_bf == 1)
		{
			ft_strlcpy(&(ret[i + 3]), &(tmp[i + 1]), ft_strlen(&tmp[i + 1])
				+ 1);
			ret[i + 2] = ' ';
		}
		else
		{
			ft_strlcpy(&(ret[i + 2]), &(tmp[i + 1]), ft_strlen(&(tmp[i + 1]))
				+ 1);
			ret[i + 1] = ' ';
		}
	}
}
