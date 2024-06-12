/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzaz <hzaz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 11:07:32 by vabertau          #+#    #+#             */
/*   Updated: 2024/05/14 13:14:57 by hzaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strndup_var(const char *s, int n)
{
	int		i;
	int		j;
	char	*ret;

	i = 0;
	j = 0;
	while (s[i])
		i++;
	if (i <= n)
		ret = malloc(sizeof(char) * (i + 1));
	else
		ret = malloc(sizeof(char) * (n + 1));
	if (!ret)
		return (0);
	while (j < i && j < n)
	{
		ret[j] = s[j];
		j++;
	}
	if (ret[j - 1] == '=')
		--j;
	ret[j] = '\0';
	return (ret);
}

char	**malloc_var(int i, char *s, int j, int n)
{
	char	**ret;

	ret = malloc(sizeof(char *) * (n + 1));
	if (!ret)
		return (NULL);
	ret[0] = ft_strndup_var(s, (j));
	if (!ret[0])
	{
		free(ret);
		return (NULL);
	}
	if (n == 2)
	{
		ret[1] = ft_strdup(s + i);
		if (!ret[1])
		{
			free(ret[0]);
			free(ret);
			return (NULL);
		}
		ret[2] = NULL;
	}
	else
		ret[1] = NULL;
	return (ret);
}

char	**split_var(char *s)
{
	int		i;
	int		n;
	int		j;
	char	**ret;

	i = 0;
	while (s && s[i] && s[i] != '=' && s[i] != '+')
		i++;
	n = 1;
	j = i;
	if (s[i])
		n = 2;
	if (s[i] == '+' && s[i + 1] == '=')
		i += 2;
	else if (s[i] == '=')
		i++;
	ret = malloc_var(i, s, j, n);
	return (ret);
}

int	find_index_env(char *env)
{
	int	i;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	return (i);
}

int	have_equal(char *env)
{
	int	i;

	i = -1;
	while (env[++i])
		if (env[i] == '=')
			return (i);
	return (0);
}
