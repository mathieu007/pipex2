/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroy <mroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 08:02:59 by math              #+#    #+#             */
/*   Updated: 2023/03/01 15:49:54 by mroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_proc	*get_proc(void)
{
	static t_proc	proc[1];

	return (&proc[0]);
}

t_proc	*init_fds(int *fds)
{
	t_proc	*proc;

	proc = get_proc();
	proc->file_in->fd = fds[0];
	proc->file_out->fd = fds[1];
	return (&proc[0]);
}

t_proc	*init_data(int32_t argc, char **argv, char **envp)
{
	t_proc	*proc;

	proc = get_proc();
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		proc->here_doc = true;
	else
		proc->here_doc = false;
	proc->file_in->f_name = ft_strjoin("./", argv[1]);
	proc->file_out->f_name = ft_strjoin("./", argv[argc - 1]);
	proc->paths = parse_paths(envp);
	proc->cmds = parse_cmds(proc, &argv[2], 2);
	proc->cmds_count = 2;
	if (proc->cmds == NULL)
		return (free_all(), NULL);
	proc->envp = envp;
	return (&proc[0]);
}

int32_t	main(int32_t argc, char **argv, char **envp)
{
	int32_t	status;
	pid_t	pid1;
	t_proc	*proc;
	int32_t	fds[2];

	if (argc != 5)
		usage();
	if (pipe(fds) == -1)
		error_exit();
	proc = init_data(argc, argv, envp);
	proc = init_fds(fds);
	pid1 = fork();
	if (pid1 == -1)
		error_exit();
	if (pid1 == 0)
		child_process(proc, 0);
	waitpid(pid1, &status, 0);
	parent_process(proc, 1);
	return (0);
}
