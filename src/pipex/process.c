/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 07:57:14 by mroy              #+#    #+#             */
/*   Updated: 2023/02/28 22:23:33 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process(t_proc *proc, int32_t i)
{
	int32_t	f_in;

	f_in = open(proc->file_in->f_name, O_RDONLY);
	if (f_in == -1)
		error_exit();
	dup2(f_in, STDIN_FILENO);
	dup2(proc->file_out->fd, STDOUT_FILENO);
	close(proc->file_in->fd);
	execute(proc, i);
	unlink_fifo(proc->file_in->f_name);
}

void	parent_process(t_proc *proc, int32_t i)
{
	int32_t	f_out;

	f_out = open(proc->file_out->f_name,
					O_WRONLY | O_CREAT | O_TRUNC,
					0777);
	if (f_out == -1)
		error_exit();
	dup2(f_out, STDOUT_FILENO);
	dup2(proc->file_in->fd, STDIN_FILENO);
	close(proc->file_out->fd);
	execute(proc, i);
	unlink_fifo(proc->file_out->f_name);
}
