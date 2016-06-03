/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/23 13:33:16 by gmorer            #+#    #+#             */
/*   Updated: 2016/06/03 16:48:43 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			ft_setenv(char	**argv, char ***env)
{
	int		i;
	char	*temp;

	temp = ft_strjoin(argv[1], "=");
	if (ft_strstrlen(argv) != 3)
	{
		ft_putendl("setenv: bad usage");
		return (-1);
	}
	if((i = casenofor(*env, argv[1])) == -1)
		*env = ft_strstradd(ft_strjoin(temp, argv[2]), *env);
	else
	{
		free((*env)[i]);
		(*env)[i] = ft_strjoin(temp, argv[2]);
	}
	free(temp);
	return (0);
}

char		**ft_strstrdelone(int i, char **str)
{
	i++;
	free(str[i - 1]);
	while(str[i])
	{
		str[i - 1] = str[i];
		i++;
	}
	str[i - 1] = NULL;
	return (str);
}

static int		ft_unsetenv(char **argv, char ***env)
{
	int		i;
	size_t	len;

	len = ft_strstrlen(*env);
	if (ft_strstrlen(argv) != 2)
	{
		ft_putendl("unsetenv: bad usage\nusage: unsetenv [environement varibale]");
		return (1);
	}
	if ((i = casenofor(*env, argv[1])) == -1)
	{
		ft_putstr("unsetenv: no variable ");
		ft_putstr(argv[1]);
		ft_putendl(" in the environement");
		return (1);
	}
	*env = ft_strstrdelone(i, *env);
	return (0);
}

static int	ft_exit(char **argv)
{
	int i;

	if(ft_strstrlen(argv) > 2)
	{
		ft_putendl("exit: too many arguments");
		return (1);
	}
	if(ft_strstrlen(argv) == 1)
		exit(1);
	i = ft_atoi(argv[1]);
	if(!i)
	{
		ft_putendl("exit: Expression Syntax.");
		return (1);
	}
	exit(i);
}

int		redirectfunction(char **argv, char ***env)
{
	int result;

	result = -1;
	if(ft_strcmp("cd", argv[0]) == 0)
		result = ft_cd(argv, env);
	if(ft_strcmp("setenv", argv[0]) == 0)
		result = ft_setenv(argv, env);
	if(ft_strcmp("unsetenv", argv[0]) == 0)
		result = ft_unsetenv(argv, env);
	if(ft_strcmp("env", argv[0]) == 0)
	{
		result = 0;
		ft_putmap(*env);
	}
	if(ft_strcmp("exit", argv[0]) == 0)
		result = ft_exit(argv);
	return (result);
}
