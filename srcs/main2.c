/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabertau <vabertau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 16:20:59 by vabertau          #+#    #+#             */
/*   Updated: 2024/06/15 16:21:10 by vabertau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	check_pwd(t_data *shell)
{
	char	*val;
	char	*val2;

	if (var_in_env("PWD", shell) < 0)
	{
		val2 = getcwd(NULL, 0);
		if (val2)
			val = join_free2("PWD=", val2);
		else
			val = ft_strdup("PWD");
		ft_add_env(val, shell);
		free(val);
	}
	if (var_in_env("OLDPWD", shell) < 0)
	{
		val = ft_strdup("OLDPWD");
		ft_add_env(val, shell);
		free(val);
	}
}

void	trim_env(t_data *shell)
{
	t_env	*tmp;
	int		i;

	tmp = shell->env;
	while (shell->env != NULL && shell->envp[0])
	{
		i = 0;
		while (shell->env->var[i] && shell->env->var[i] != '=')
			i++;
		shell->env->var_name = ft_strndup(shell->env->var, i);
		if (!shell->env->var_name)
			perror("malloc");
		if (!shell->env->var[i++])
			return ;
		shell->env->val = ft_strdup(shell->env->var + i);
		if (!shell->env->val)
			perror("malloc");
		shell->env = shell->env->next;
	}
	shell->env = tmp;
	check_pwd(shell);
}
