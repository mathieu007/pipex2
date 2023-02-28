/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroy <mroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 08:03:11 by math              #+#    #+#             */
/*   Updated: 2023/02/28 15:35:59 by mroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	int32_t	i;
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

void	unlink_fifo(char *f_name)
{
	if (unlink((const char *)f_name) != 0)
		perror("unlink() error");
}

t_cmd	**parse_cmds(t_proc *proc, char **argv, int32_t count)
{
	t_cmd	**cmds;
	char	**s_cmds;
	int32_t	i;

	i = 0;
	cmds = malloc(sizeof(t_cmd *) * count);
	if (cmds == NULL)
		return (free_all(), NULL);
	proc->cmds = cmds;
	while (i < count)
	{
		cmds[i] = malloc(sizeof(t_cmd));
		if (cmds[i] == NULL)
			return (free_all(), NULL);
		s_cmds = ft_split(argv[i], ' ');
		if (s_cmds == NULL)
			return (free_all(), NULL);
		cmds[i]->args = s_cmds;
		cmds[i]->cmd = s_cmds[0];
		i++;
	}
	return (cmds);
}

char	**parse_paths(char **envp)
{
	char	**paths;
	int32_t	i;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(envp[i], ':');
	return (paths);
}

char	*get_full_path_cmd(t_proc *proc, char *cmd)
{
	int32_t	i;
	char	*path;

	i = 0;
	while (proc->paths[i])
	{
		path = ft_strjoin_temp(proc->paths[i], "/");
		path = ft_strjoin_temp(path, cmd);
		if (access(path, F_OK) == 0)
			return (path);
		i++;
	}
	return (NULL);
}

void	execute(t_proc *proc, int32_t i)
{
	char	*fp_cmd;

	fp_cmd = get_full_path_cmd(proc, proc->cmds[i]->cmd);
	if (!fp_cmd)
		error_exit();
	if (execve(fp_cmd, proc->cmds[i]->args, proc->envp) == -1)
		error_exit();
}
