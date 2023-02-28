/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroy <mroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 07:57:14 by mroy              #+#    #+#             */
/*   Updated: 2023/02/28 16:40:31 by mroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/// @brief The child process shall have its own copy of the parent's file
/// descriptors. Each of the child's file descriptors shall refer to the same
/// open file description with the corresponding file descriptor of the parent.
/// @param argv
/// @param envp
/// @param fd
// void	child_process(char **argv, char **envp, int32_t *fd)
// {
// 	int32_t	f_in;

// 	f_in = open(argv[1], O_RDONLY, 0777);
// 	if (f_in == -1)
// 	{
// 		unlink_fifo(argv[1]);
// 		error_exit();
// 	}
// 	dup2(fd[1], STDOUT_FILENO);
// 	dup2(f_in, STDIN_FILENO);
// 	close(fd[0]);
// 	unlink_fifo(argv[1]);
// 	execute(argv[2], envp);
// }

// void	parent_process(char **argv, char **envp, int32_t *fd)
// {
// 	int32_t	f_out;

// 	f_out = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
// 	if (f_out == -1)
// 	{
// 		unlink_fifo(argv[4]);
// 		error_exit();
// 	}
// 	dup2(fd[0], STDIN_FILENO);
// 	dup2(f_out, STDOUT_FILENO);
// 	close(fd[1]);
// 	unlink_fifo(argv[4]);
// 	execute(argv[3], envp);
// }

void	child_process(t_proc *proc, int32_t i)
{
	proc->file_in->fd = open(proc->file_in->f_name, O_RDONLY, 0777);
	if (proc->file_in->fd == -1)
	{
		unlink_fifo(proc->file_in->f_name);
		error_exit();
	}
	dup2(proc->file_in->fd, STDIN_FILENO);
	close(proc->file_out->fd);
	close(proc->file_in->fd);
	unlink_fifo(proc->file_in->f_name);
	execute(proc, i);
}

void	parent_process(t_proc *proc, int32_t i)
{
	proc->file_out->fd = open(proc->file_out->f_name,
								O_WRONLY | O_CREAT | O_TRUNC,
								0777);
	if (proc->file_out->fd == -1)
	{
		unlink_fifo(proc->file_out->f_name);
		error_exit();
	}
	dup2(proc->file_out->fd, STDOUT_FILENO);
	close(proc->file_in->fd);
	close(proc->file_out->fd);
	unlink_fifo(proc->file_out->f_name);
	execute(proc, i);
}
