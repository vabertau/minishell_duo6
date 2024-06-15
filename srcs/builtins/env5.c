/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env5.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabertau <vabertau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 13:18:55 by hzaz              #+#    #+#             */
/*   Updated: 2024/06/15 17:24:59 by vabertau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_printf_var_env(char *var)
{
	write(STDOUT_FILENO, "declare -x ", 11);
	write(STDOUT_FILENO, var, ft_strlen(var));
	write(STDOUT_FILENO, "\n", 1);
}

int	check_cmd(char *s)
{
	int	i;

	i = 0;
	if (!s[0] || (s[0] != '_' && !ft_isalpha(s[0])))
		return (0);
	while (++i && s && s[i] && s[i] != '=' && s[i] != '+')
		if ((s[i] != '_' && !ft_isalnum(s[i])))
			return (0);
	if (s[i] == '+' && s[i + 1] != '=')
		return (0);
	return (1);
}

void	display_exported_vars(t_env *env)
{
	while (env)
	{
		ft_printf_var_env(env->var);
		env = env->next;
	}
}

int	validate_and_add_var(char *var, t_data *shell)
{
	char	*tmp;
	int		result;

	result = 0;
	if (!check_cmd(var))
	{
		tmp = ft_strjoin("bash: export: `", var);
		ft_putstr_fd_free(join_free1(tmp, "': not a valid identifier\n"), 2);
		result = 1;
	}
	else
	{
		if (ft_putenv(var, shell) != 1)
		{
			perror("export");
			exit_free(shell, EXIT_FAILURE);
		}
	}
	return (result);
}
