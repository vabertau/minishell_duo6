/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env6.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzaz <hzaz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 13:19:14 by hzaz              #+#    #+#             */
/*   Updated: 2024/05/14 13:21:20 by hzaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	process_export_commands(char **split_cmd, t_data *shell)
{
	int	i;
	int	ret;

	ret = 0;
	i = 0;
	while (split_cmd[++i] != NULL)
	{
		ret |= validate_and_add_var(split_cmd[i], shell);
	}
	return (ret);
}

int	ft_export(char **split_cmd, t_data *shell)
{
	int	ret;

	ret = 0;
	if (split_cmd[1] == NULL)
	{
		display_exported_vars(shell->env);
	}
	else
	{
		ret = process_export_commands(split_cmd, shell);
	}
	return (ret);
}

int	check_s(char *s)
{
	int	i;

	i = -1;
	while (++i && s && s[i])
		if (s[i] != '_' && !ft_isalpha(s[i]))
			return (0);
	return (1);
}

void	free_single_env(t_env *e)
{
	if (!e)
		return ;
	if (e->val)
		free(e->val);
	if (e->var)
		free(e->var);
	if (e->var_name)
		free(e->var_name);
	free(e);
	e = NULL;
}
