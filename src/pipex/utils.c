/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 08:03:11 by math              #+#    #+#             */
/*   Updated: 2023/02/27 22:28:36 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	int		i;
	char	*first;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	paths = ft_split_temp(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		first = ft_strjoin_temp(paths[i], "/");
		path = ft_strjoin_temp(first, cmd);
		if (access(path, F_OK) == 0)
			return (path);
		i++;
	}
	return (0);
}

void	error_exit(void)
{
	perror("Error");
	exit(EXIT_FAILURE);
}

void	execute(char *argv, char **envp)
{
	char	**cmd;
	int		i;
	char	*path;

	i = 0;
	cmd = ft_split_temp(argv, ' ');
	path = find_path(cmd[0], envp);
	if (!path)
		error_exit();
	if (execve(path, cmd, envp) == -1)
		error_exit();
}
