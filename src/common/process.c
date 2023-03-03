/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroy <mroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 07:57:14 by mroy              #+#    #+#             */
/*   Updated: 2023/03/03 11:07:02 by mroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/// @brief Very important use WNOHANG: no hang in wait
/// @param proc
/// @param i
void	child_process(t_proc *proc, int32_t i)
{
	int32_t	status;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		error_exit(NULL);
	if (pid == 0)
	{
		close(proc->cmds[i]->file_in);
		dup2(proc->cmds[i]->file_out, STDOUT_FILENO);
		execute(proc, i);
	}
	else
	{
		close(proc->cmds[i]->file_out);
		dup2(proc->cmds[i]->file_in, STDIN_FILENO);
		waitpid(pid, &status, WNOHANG);
	}
}

void	pipe_childs(t_proc *proc)
{
	int32_t	i;
	int32_t	fds[2];

	i = 0;
	while (i < proc->cmds_count - 1)
	{
		if (pipe(fds) == -1)
			error_exit(NULL);
		proc = init_fds(fds, i);
		i++;
	}
}

void	exec_childs(t_proc *proc)
{
	int32_t	i;

	i = 0;
	while (i < proc->cmds_count - 1)
	{
		child_process(proc, i);
		i++;
	}
}

void	execute(t_proc *proc, int32_t i)
{
	char	*fp_cmd;

	fp_cmd = get_full_path_cmd(proc, proc->cmds[i]->cmd);
	if (!fp_cmd)
		error_exit("Command do not exit in environement path.");
	if (execve(fp_cmd, proc->cmds[i]->args, proc->envp) == -1)
		error_exit("Could not execve.");
}
