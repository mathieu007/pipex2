/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 08:03:11 by math              #+#    #+#             */
/*   Updated: 2023/03/07 19:56:24 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errno.h"
#include "pipex.h"

void	write_msg(const char *msg, int32_t stderror)
{
	if (msg != NULL)
	{
		write(stderror, msg, ft_strlen(msg));
		write(stderror, "\n", 1);
	}
}

void	write_error(int32_t stderror)
{
	if (errno)
	{
		write(stderror, strerror(errno), ft_strlen(strerror(errno)));
		write(stderror, strerror(errno), ft_strlen(strerror(errno)));
	}
}

void	error_exit(const char *msg, int32_t stderror)
{
	t_proc	*proc;
	proc = get_proc();
	free_all();
	if (proc->fds->f_in)
	{
		close(proc->fds->f_in);
		unlink_fifo(get_proc()->fds->f_in_name);
	}
	if (proc->fds->f_out)
	{
		close(proc->fds->f_out);
		unlink_fifo(get_proc()->fds->f_out_name);
	}
	write_msg(msg, stderror);
	write_error(stderror);
	exit(EXIT_FAILURE);
}
