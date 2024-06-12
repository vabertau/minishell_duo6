/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzaz <hzaz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 12:40:32 by vabertau          #+#    #+#             */
/*   Updated: 2024/05/27 09:13:07 by hzaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	aff_val(t_data *data)
{
	t_exec	*cur_cmd;
	t_token	*cur_redir;
	int		j;
	int		i;

	cur_cmd = data->exec;
	j = 1;
	while (cur_cmd && j++)
	{
		i = -1;
		cur_redir = cur_cmd->redir;
		printf("full[%d] = %s\n\n\n", j, cur_cmd->full_cmd);
		while (cur_cmd->split_cmd[++i])
			printf("split[%d][%d] = %s\n\n\n", j, i, cur_cmd->split_cmd[i]);
		while (cur_redir)
		{
			printf("%s\n%u\n", cur_redir->word, cur_redir->type);
			cur_redir = cur_redir->next;
		}
		cur_cmd = cur_cmd->next;
	}
}

int	len_env(t_env *env)
{
	t_env	*tmp;
	int		i;

	tmp = env;
	i = 0;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

void	set_char_env(t_data *shell)
{
	t_env	*tmp;
	int		len;
	int		i;

	i = -1;
	tmp = shell->env;
	len = len_env(tmp);
	shell->char_env = malloc(sizeof(char *) * (len + 1));
	if (!shell->char_env)
		perror("malloc");
	while (++i < len && tmp)
	{
		shell->char_env[i] = ft_strdup(tmp->var);
		if (!shell->char_env[i])
			perror("malloc");
		tmp = tmp->next;
	}
	shell->char_env[i] = NULL;
}
