/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroy <mroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 08:03:11 by math              #+#    #+#             */
/*   Updated: 2023/03/03 18:17:09 by mroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errno.h"
#include "pipex.h"

void	unlink_fifo(char *f_name)
{
	if (unlink((const char *)f_name) != 0)
	{
		free_all();
		perror("unlink() error");
	}
}

void	escape_single_quotes(char **cmds_split)
{
	int32_t	i;
	int32_t	c_i;
	char	**new_cmds;
	int32_t	count;
	int32_t	count_sep;

	i = 0;
	count = 0;
	while (cmds_split[i])
		count++;
	new_cmds = malloc(count + 1);
	new_cmds[count] = NULL;
	while (cmds_split[i])
	{
		c_i = 0;
		count = 0;
		count_sep = 0;
		while (cmds_split[i][c_i])
		{
			if (cmds_split[i][c_i] == '\'')
				count_sep++;
			c_i++;
			count++;
		}
		c_i = 0;
		new_cmds[i] = malloc(count + count_sep + 1);
		new_cmds[i][count + count_sep] = '\0';
		while (cmds_split[i][c_i])
		{
			if (cmds_split[i][c_i] == '\'')
			{
				new_cmds[i][c_i++] = '\'';
				new_cmds[i][c_i] = '\'';
			}
		}
		i++;
	}
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

/// @brief // linux path is ":", so handle PATH= and PATH:
/// gros criss de cave check your linux path AGAIN.
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
	i = 0;
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
	f_out = open(proc->fds->f_out_name, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (f_out == -1)
	{
		f_out = 0;
		printf("%s: %s\n", sys_errlist[errno], proc->fds->f_out_name);
	}
	f_in = open(proc->fds->f_in_name, O_RDONLY, 0777);
	if (f_in == -1)
	{
		f_in = 0;
		printf("%s: %s\n", sys_errlist[errno], proc->fds->f_in_name);
	}
	dup2(f_in, STDIN_FILENO);
	return (f_out);
}
