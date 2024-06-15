/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env4.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabertau <vabertau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 11:34:46 by vabertau          #+#    #+#             */
/*   Updated: 2024/06/15 17:24:40 by vabertau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	var_in_env(char *s, t_data *shell)
{
	int		ret;
	t_env	*tmp;
	char	**var;

	var = split_var(s);
	if (!var)
	{
		perror("malloc");
		exit_free(shell, EXIT_FAILURE);
	}
	ret = -1;
	tmp = shell->env;
	while (tmp)
	{
		if (tmp->var_name && !ft_strcmp(tmp->var_name, var[0]))
		{
			ret = tmp->index;
			break ;
		}
		tmp = tmp->next;
	}
	free(var[0]);
	if (var[1])
		free(var[1]);
	return (free(var), ret);
}

t_env	*initialize_new_node(char **str)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
	{
		perror("malloc");
		return (NULL);
	}
	if (!str[1])
	{
		new_node->var = ft_strdup(str[0]);
		new_node->var_name = ft_strdup(str[0]);
		new_node->val = NULL;
	}
	else
	{
		new_node->var = join_free1(ft_strjoin(str[0], "="), str[1]);
		new_node->var_name = ft_strdup(str[0]);
		new_node->val = ft_strdup(str[1]);
	}
	new_node->next = NULL;
	return (new_node);
}

void	add_to_env(t_env *new_node, t_data *shell)
{
	t_env	*e;

	if (shell->env == NULL)
	{
		shell->env = new_node;
		new_node->index = 0;
	}
	else
	{
		e = shell->env;
		while (e->next != NULL)
			e = e->next;
		e->next = new_node;
		new_node->index = e->index + 1;
	}
}

void	ft_add_env(char *s, t_data *shell)
{
	char	**str;
	t_env	*new_node;

	str = split_var(s);
	if (!str)
		return ;
	new_node = initialize_new_node(str);
	if (!new_node)
		return ;
	add_to_env(new_node, shell);
	if (str[1])
		free(str[1]);
	free(str[0]);
	free(str);
}

int	ft_putenv(char *s, t_data *shell)
{
	int	pos;

	pos = var_in_env(s, shell);
	if (pos > -1)
	{
		ft_update_env(s, shell, pos);
	}
	else
	{
		ft_add_env(s, shell);
	}
	return (1);
}
