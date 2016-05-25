/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getbin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/23 11:11:06 by gmorer            #+#    #+#             */
/*   Updated: 2016/05/24 17:24:06 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**getline(char **env, char *argv)
{
	int	i;

	i = 0;
	while(ft_strstr(env[i], argv) == NULL)
		i++;
	return(ft_strsplit(strstr(env[i], argv), ':'));
}

char	*getexec(char *path, char *file)
{
	DIR				*dir;
	struct dirent	*ofile;

	(void)file;
	dir = opendir(path);
	if(dir == NULL)
		return (NULL);
	while ((ofile = readdir(dir)) && ft_strcmp(ofile->d_name, file))
		;
	closedir(dir);
	if (ofile && ofile->d_name[0] != '.')
	{
		//ft_putstr(path);
		//ft_putendl(ofile->d_name);
		return(path);
	}
	return (NULL);
}

char	*toexec(char **env, char *argv)
{
	char	**path;
	size_t	i;
	size_t	len;
	char	*temp;

	path = ft_strsplit(getenvline(env, "PATH="), ':');
	len = ft_strlen(path[0]);
//	ft_putendl("pathenv = ");
//	ft_putmap(path);
	len = ft_strstrlen(path);
	i = 0;
	//ft_putendl(path[i]);
	while(i < len && getexec(path[i], argv) == NULL)
		i++;
	if (i == len)
		return (NULL);
	temp = ft_strjoin(path[i], "/");
	ft_strstrfree(path);
	return (ft_strjoin(temp, argv));
}

int		ft_exec(char *bin, char **temp, char **env)
{
	int		exit;
	pid_t	pid;

	pid = fork();
	if (pid > 0)
	{
		waitpid(pid, &exit, 0);
	}	
	if (pid == 0)
		execve(bin, temp, env);
	return (1);
}