/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroy <mroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 08:03:11 by math              #+#    #+#             */
/*   Updated: 2023/03/07 14:08:30 by mroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
	cmds = malloc(sizeof(t_cmd *) * (count + 1));
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
	cmds[i] = NULL;
	return (cmds);
}

/// @brief
/// @param envp
/// @return
char	**parse_paths(char **envp)
{
	char	**paths;
	int32_t	i;
	char	*seps;

	if (!envp)
		return (NULL);
	seps = ":";
	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	paths = ft_split_many(envp[i] + 5, seps);
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
		path = ft_strjoin(path, cmd);
		if (access(path, F_OK) == 0)
			return (path);
		i++;
	}
	return (NULL);
}

int32_t	open_files(t_proc *proc)
{
	int32_t	f_in;
	int32_t	f_out;

	proc->here_doc = false;
	f_out = open(proc->fds->f_out_name, O_WRONLY | O_CREAT | O_TRUNC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
	f_in = open(proc->fds->f_in_name, O_WRONLY | O_CREAT | O_TRUNC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
	if (access(proc->fds->f_in_name, F_OK))
		error_exit("infile not accessible.", 2);
	dup2(f_in, STDIN_FILENO);
	return (f_out);
}
