/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzaz <hzaz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 11:32:12 by vabertau          #+#    #+#             */
/*   Updated: 2024/06/04 00:08:37 by hzaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	decrem_env(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		tmp->index--;
		tmp = tmp->next;
	}
}

int	validate_identifier(char *var)
{
	if (!check_s(var))
	{
		ft_putstr_fd("bash: unset: `", 2);
		ft_putstr_fd(var, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (0);
	}
	return (1);
}

void	remove_env_var(t_data *shell, char *var_name)
{
	t_env	*current;
	t_env	*prev;
	t_env	*next_node;

	current = shell->env;
	while (current && ft_strcmp(current->var_name, var_name) != 0)
	{
		prev = current;
		current = current->next;
	}
	if (current != NULL)
	{
		if (prev == NULL)
		{
			shell->env = current->next;
			next_node = shell->env;
		}
		else
		{
			prev->next = current->next;
			next_node = prev->next;
		}
		free_single_env(current);
		decrem_env(next_node);
	}
}

int	ft_unset(t_data *shell, char **split_cmd)
{
	int	i;
	int	ret;

	i = 1;
	ret = 0;
	while (split_cmd[i])
	{
		if (validate_identifier(split_cmd[i]) && ft_strcmp(split_cmd[i], "_"))
		{
			remove_env_var(shell, split_cmd[i]);
		}
		else
		{
			ret = 1;
		}
		i++;
	}
	return (ret);
}

int	ft_env(t_data *shell, char **f)
{
	t_env	*tmp;

	tmp = shell->env;
	if (f[1])
		return ((void)ft_putstr_fd("No such file or directory\n", 2), 127);
	while (tmp)
	{
		ft_putstr_fd(tmp->var, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		tmp = tmp->next;
	}
	return (0);
}
