/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzaz <hzaz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 00:47:00 by hedi              #+#    #+#             */
/*   Updated: 2024/06/04 00:01:47 by hzaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_plus(char *s)
{
	int	i;

	i = 0;
	while (s && s[i] && s[i] != '=' && s[i] != '+')
		i++;
	if (s[i] == '+')
		return (1);
	else
		return (0);
	return (-1);
}

void	ft_update_env_inc(t_env **tmp, char **s, int pos)
{
	while (*tmp && (*tmp)->index < pos)
		*tmp = (*tmp)->next;
	(*tmp)->val = join_free1((*tmp)->val, s[0]);
	if (!(*tmp)->val)
		perror("malloc");
	free((*tmp)->var);
	(*tmp)->var = join_free1(ft_strjoin((*tmp)->var_name, "="), (*tmp)->val);
	if (!(*tmp)->var)
		perror("malloc");
}

void	ft_update_env_inc2(t_env **tmp, char **s, int pos)
{
	while (*tmp && (*tmp)->index < pos)
		*tmp = (*tmp)->next;

	if (s[1] || have_equal((*tmp)->var))
	{
		if ((*tmp)->val)
			free((*tmp)->val);
		(*tmp)->val = s[1] ? ft_strdup(s[1]) : NULL;
		if (s[1] && !(*tmp)->val)
			perror("malloc");
	}

	if ((*tmp)->var)
		free((*tmp)->var);
	if ((*tmp)->val != NULL)
	{
		(*tmp)->var = join_free1(ft_strjoin((*tmp)->var_name, "="), (*tmp)->val);
	}
	else
	{
		(*tmp)->var = ft_strdup((*tmp)->var_name);
	}
	if (!(*tmp)->var)
		perror("malloc");
}


void	ft_update_env(char *str, t_data *shell, int pos)
{
	char	**s;
	t_env	*tmp;

	s = split_var(str);
	tmp = shell->env;
	if (!s)
		return ;

	if (check_plus(str))
		ft_update_env_inc(&tmp, s, pos);
	else
		ft_update_env_inc2(&tmp, s, pos);

	if (s[1])
		free(s[1]);
	free(s[0]);
	free(s);
}