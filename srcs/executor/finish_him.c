/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish_him.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabertau <vabertau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 21:08:17 by hedi              #+#    #+#             */
/*   Updated: 2024/06/14 19:11:29 by vabertau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_build(t_data *shell, char **f)
{
	if (ft_same_str(f[0], "echo", 4))
		shell->last_return_code = ft_echo(f);
	else if (ft_same_str(f[0], "cd", 2))
		shell->last_return_code = ft_cd(f, shell);
	else if (ft_same_str(f[0], "pwd", 3))
		shell->last_return_code = ft_pwd(shell);
	else if (ft_same_str(f[0], "export", 6))
		shell->last_return_code = ft_export(f, shell);
	else if (ft_same_str(f[0], "unset", 5))
		shell->last_return_code = ft_unset(shell, f);
	else if (ft_same_str(f[0], "env", 3))
		shell->last_return_code = ft_env(shell, f);
	else if (ft_same_str(f[0], "exit", 4))
		ft_exit(f, shell);
	else
		return ;
	exit_free(shell, 0);
}
// Aucun built-in correspondant trouvé
// if (ft_same_str(f[0], "echo", 4))
// 	ft_echo(f);
// else if (ft_same_str(f[0], "cd", 2))
// 	ft_cd();
// printf("test");

static void	init_exec_path(int *i, t_env **e, t_data *sh)
{
	*i = -1;
	*e = sh->env;
}

static void	incr_j(t_env *e, int *j)
{
	while (e->val[*j] != ':' && e->val[*j] && e->val)
		(*j)++;
}

void	exec_path(t_data *sh, char **f, char *tmp)
{
	int		i;
	int		j;
	int		k;
	char	*ret;
	t_env	*e;

	init_exec_path(&i, &e, sh);
	while (e)
	{
		if (ft_same_str(e->var_name, "PATH", 4))
		{
			j = -1;
			while (e->val && e->val[++j])
			{
				k = j;
				incr_j(e, &j);
				ret = join_free1(ft_substr(e->val, k, ((j) - k)), tmp);
				if (e->val[j] == ':')
					if (access(ret, F_OK) == 0)
					{
						execve(ret, f, sh->char_env);
						perror("minishell :");
					}
				free(ret);
				if (!e->val[j])
					break ;
			}
		}
		e = e->next;
	}
}

int	check_shell_cmd(char *str)
{
	int		len;
	int 	len2;
	char	*tmp;

	tmp = "/minishell";
	len2 = ft_strlen(tmp);
	len = ft_strlen(str);
	while(str[--len] && tmp[--len2])
	{
		if(str[len] != tmp[len2])
			return (0);
	}
	if (tmp[len2])
		return (0);
	return(1);
}

// void	exec_minishell(char **f, t_data *shell)
// {

// 	int tmp;

// 	tmp = 0;
// 	if (var_in_env(tmp,shell) > -1)
// 		ft_update_env(tmp, shell, var_in_env(tmp,shell));
// 	else
// 		ft_add_env(tmp, shell);
// 	if (var_in_env(tmp2,shell) > -1)
// 		ft_update_env(tmp2, shell, var_in_env(tmp2,shell));
// 	else
// 		ft_add_env(tmp2, shell);
// 	if (check_shell_cmd(f[0]))
// 	{

// 	}
// }

int is_directory(const char *path)
{
    struct stat fileStat;
	if (path && path[0] == ':' && !path[1])
		return (-1);
    if(stat(path, &fileStat) < 0) {
        perror("stat");
        return 0;
    }

    return S_ISDIR(fileStat.st_mode);
}

void	exec_cmd(t_data *shell, t_exec *cmd)
{
	char	*ret;
	char	*tmp;
	char	**f;
	int		code;

	code = 0;
	f = cmd->split_cmd;
	if (!f[0])
		return ; // added to fix leaks on echo lol | > lol because
	// there is no split_cmd in second command
	// it should not enter f
	if (f[0] && f[0][0] == ':' && !f[0][1])
		exit_free(shell, 0);
	handle_redirections(cmd, shell);
	if (!f[0])
		return ;
	if (f[0] && f[0][0] == '.' && f[0][1]=='/')
	{
        if (access(f[0], F_OK) != 0)
        {
            perror("minishell :");
            code = 127;
        }
        else if (is_directory(f[0]))
        {
            ft_putstr_fd("minishell: is a directory.\n", 2);
            code = 126;
        }
        else if (access(f[0], X_OK) != 0)
        {
            perror("minishell :");
            code = 126;
        }
        else
        {
            execve(f[0], f, shell->char_env);
            perror("minishell :");
            code = 126;
        }
        exit_free(shell, code);
	}
	exec_build(shell, f);
	tmp = ft_strjoin("/", f[0]);
	if (access(tmp, F_OK) == 0)
	{
		execve(tmp, f, shell->envp);
		perror("minishell :");
	}
	else
		exec_path(shell, f, tmp);
	code = 127;
	if (f[0][0] == '/' && is_directory(f[0]))
	{
		ret = ft_strdup("is a directory.\n");
		code = 126;
	}
	else
		ret = join_free1(ft_strjoin("command not found: ", f[0]), "\n");
	ft_putstr_fd_free(ret, 2);
	free(tmp);
	exit_free(shell, code);
}
