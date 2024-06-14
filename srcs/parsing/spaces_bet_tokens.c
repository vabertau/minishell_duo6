/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spaces_bet_tokens.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabertau <vabertau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 09:48:08 by vabertau          #+#    #+#             */
/*   Updated: 2024/06/14 17:47:26 by vabertau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* Calls functions to add space before and after special
characters if a space is missing.
stores a boolean sp_bf for index matters in add_space_af */
static void	add_space_bf_af(int i, char *ret, char *tmp)
{
	bool	sp_bf;

	sp_bf = add_space_bf(i, ret, tmp);
	add_space_af(i, sp_bf, ret, tmp);
}

/*
added = to fix segfault on export=\"hey y\" counting token after hey
 when founding space
*/
int	add_space_inc(t_data *data, char **ret, char **tmp, int i)
{
	if ((*ret)[i] == '<' || (*ret)[i] == '>' || (*ret)[i] == '|')
	{
		*tmp = ft_strdup(*ret);
		if (!(*tmp))
			return (free(*ret), exit_free(data, -1), -1);
		add_space_bf_af(i, *ret, *tmp);
		free(*tmp);
	}
	return (0);
}

/*skips characters between quotes,
	and calls function to add missing spaces between and
after separators
*/
char	*add_space(char *cmdline, t_data *data)
{
	int		i;
	char	*tmp;
	char	*ret;

	i = -1;
	ret = malloc(sizeof(char) * (fixed_cmdline_len(cmdline) + 1));
	if (ret == NULL)
		exit_free(data, -1);
	ft_strlcpy(ret, cmdline, ft_strlen(cmdline) + 1);
	while (ret[++i])
	{
		i += skip_sq(&(ret[i]));
		if (!ret[i])
			break ;
		i += skip_dq(&(ret[i]));
		if (!ret[i])
			break ;
		if (ret[i] == '\t')
			ret[i] = ' ';
		if (add_space_inc(data, &ret, &tmp, i) == -1)
			return (NULL);
	}
	ret[fixed_cmdline_len(cmdline)] = '\0';
	data->cmdline_len = ft_strlen(ret);
	return (free(cmdline), ret);
}

/*add_spaces function launcher*/
int	spaces_bet_tokens(t_data *data)
{
	data->cmdline = add_space(data->cmdline, data);
	return (0);
}
