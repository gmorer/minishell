/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/23 13:33:16 by gmorer            #+#    #+#             */
/*   Updated: 2016/12/08 11:58:36 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		**ft_strstrdelone(int i, char **str)
{
	char	**rslt;
	int		y;

	y = 0;
	if(!(rslt = malloc(sizeof(char*) * ft_strstrlen(str))))
		return (NULL);
	i++;
	while (y < i)
	{
		rslt[y] = str[y];
		y++;
	}
	free(str[i - 1]);
	while (str[i])
	{
		rslt[i - 1] = str[i];
		i++;
	}
	rslt[i - 1] = NULL;
	free(str);
	return (rslt);
}

static int	ft_unsetenv(char **argv, char ***env, t_binary ***table)
{
	int		i;
	size_t	len;

	len = ft_strstrlen(*env);
	if (ft_strstrlen(argv) != 2)
	{
		ft_putstr("unsetenv: bad usage\nusage: ");
		ft_putendl("unsetenv [environement varibale]");
		return (1);
	}
	if ((i = casenofor(*env, argv[1])) == -1)
	{
		ft_putstr("unsetenv: no variable ");
		ft_putstr(argv[1]);
		ft_putendl(" in the environement");
		return (1);
	}
	if (ft_strcmp(argv[1], "BINARY_LEN") == 0)
		return (0);
	if (ft_strcmp(argv[1], "PATH") == 0)
		ft_free_hash_tab(*env, table);
	*env = ft_strstrdelone(i, *env);
	return (0);
}

static int	ft_exit(char **argv, t_binary ***table, char **env)
{
	int i;

	if (ft_strstrlen(argv) > 2)
	{
		ft_putendl("exit: too many arguments");
		return (1);
	}
	if (ft_strstrlen(argv) == 1)
	{
		ft_free_hash_tab(env, table);
		exit(0);
	}
	i = ft_atoi(argv[1]);
	if (!i)
	{
		ft_putendl("exit: Expression Syntax.");
		return (1);
	}
	ft_free_hash_tab(env, table);
	exit(i);
}

int			redirectfunction_builtin(char **argv, char ***env, t_binary ***table)
{
	int result;

	result = -1;
	if (ft_strcmp("cd", argv[0]) == 0)
		result = ft_cd(argv, env);
	if (ft_strcmp("setenv", argv[0]) == 0)
		result = ft_setenv(argv, env, table);
	if (ft_strcmp("unsetenv", argv[0]) == 0)
		result = ft_unsetenv(argv, env, table);
	if (ft_strcmp("echo", argv[0]) == 0)
		result = ft_echo(argv);
	if (ft_strcmp("hashtab", argv[0]) == 0)
		result = ft_show_hash_tab(*env, *table);
	if (ft_strcmp("upper", argv[0]) == 0 && argv[1] && argv[2] && argv[3])
		result = uppercase(argv[1], argv[2], argv[3]);
	if (ft_strcmp("job", argv[0]) == 0)
		result = ft_jobs(argv);
	if (ft_strcmp("fg", argv[0]) == 0)
		result = ft_fg(argv);
	if (ft_strcmp("match", argv[0]) == 0)
		result = ft_match(argv);
	if (ft_strcmp("env", argv[0]) == 0)
	{
		result = 0;
		ft_putmap(*env);
	}
	if (ft_strcmp("exit", argv[0]) == 0)
		result = ft_exit(argv, table, *env);
	return (result);
}
