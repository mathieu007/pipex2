/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroy <mroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 08:03:11 by math              #+#    #+#             */
/*   Updated: 2023/03/07 14:22:35 by mroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errno.h"
#include "pipex.h"

void	error_exit(const char *msg, int32_t std)
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
	if (errno)
		write(std, strerror(errno), ft_strlen(strerror(errno)));
	if (msg)
		write(std, msg, ft_strlen(msg));
	exit(EXIT_FAILURE);
}
