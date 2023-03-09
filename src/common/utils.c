/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 19:40:18 by math              #+#    #+#             */
/*   Updated: 2023/03/08 21:39:06 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	unlink_fifo(char *f_name)
{
	if (unlink((const char *)f_name) != 0)
	{
		free_all();
		perror("unlink() error");
	}
}

int32_t	count_arg_char(char *cmd)
{
	int32_t	i;

	i = 0;
	i++;
	if (*cmd == '"')
	{
		while (cmd[i])
			if (cmd[i] == '"' && cmd[i - 2] != '\\')
				return (i + 1);
		i++;
	}
	else if (*cmd == '\'')
	{
		while (cmd[i])
		{
			if (cmd[i] == '\'' && cmd[i - 2] != '\\')
				return (i + 1);
			i++;
		}
	}
	else
		while (cmd[i] && cmd[i] != ' ')
			i++;
	return (i);
}

char	*get_arg_start(char *cmd)
{
	int32_t	i;

	i = 0;
	while (cmd[i] && (cmd[i] == ' ' || cmd[i] == '\t'))
		i++;
	return (&cmd[i]);
}

char	*get_cmd_start(char *cmd)
{
	int32_t	i;

	i = 0;
	while (cmd[i] && (cmd[i] == ' ' || cmd[i] == '\t'))
		i++;
	return (&cmd[i]);
}

char	*get_cmd_end(char *cmd)
{
	int32_t	i;

	i = 0;
	while (cmd[i] && cmd[i] != ' ' && cmd[i] != '\t')
		i++;
	return (&cmd[i]);
}

char	**get_args(char *str, char *cmd)
{
	int32_t	count;
	t_lst	*lst;
	char	*dest;

	str = get_cmd_end(str);
	lst = lst_new(10, sizeof(char *));
	count = 0;
	lst_add(lst, cmd);
	while (str[count])
	{
		str = get_arg_start(str);
		count = count_arg_char(str);
		dest = malloc(count + 1);
		if (dest == NULL)
			return (lst_free(lst), free_all(), NULL);
		dest[count] = '\0';
		lst_add(lst, ft_strncpy(dest, str, count));
	}
	lst_add(lst, NULL);
	return (lst_free_to_array(lst));
}

char	*get_cmd(char *str)
{
	char	*cmd;
	int32_t	len;

	len = get_cmd_end(str) - str;
	cmd = malloc(len + 1);
	cmd[len] = '\0';
	ft_strncpy(cmd, str, len);
	return (cmd);
}

t_cmd	**parse_cmds(t_proc *proc, char **argv, int32_t count)
{
	t_cmd	**cmds;
	int32_t	i;
	char	*cmd;

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
		// s_cmds = ft_split(ft_replace_char_temp(argv[i], '\'', "\\'"), ' ');
		// if (s_cmds == NULL)
		// 	return (free_all(), NULL);
		cmd = get_cmd_start(argv[i]);
		cmds[i]->cmd = get_cmd(cmd);
		cmds[i]->args = get_args(cmd, cmds[i]->cmd);
		i++;
	}
	cmds[i] = NULL;
	return (cmds);
}

char	**parse_paths(char **envp)
{
	char	**paths;
	int32_t	i;

	if (!envp)
		return (NULL);
	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	return (paths);
}

char	*get_full_path_cmd(t_proc *proc, char *cmd)
{
	int32_t	i;
	char	*path;

	i = 0;
	if (cmd[0] == '/' && access(cmd, F_OK) == 0)
		return (ft_strdup(cmd));
	while (proc->paths[i])
	{
		path = ft_strjoin_temp(proc->paths[i], "/");
		path = ft_strjoin(path, cmd);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
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
		printf("%s: %s\n", strerror(errno), proc->fds->f_out_name);
	}
	f_in = open(proc->fds->f_in_name, O_RDONLY, 0777);
	if (f_in == -1)
		write_error(2);
	dup2(f_in, STDIN_FILENO);
	return (f_out);
}
