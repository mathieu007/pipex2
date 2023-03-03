/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroy <mroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 08:03:11 by math              #+#    #+#             */
/*   Updated: 2023/03/03 10:58:17 by mroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errno.h"
#include "pipex.h"

void	error_exit(const char *msg)
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
	perror("Error: ");
	if (msg != NULL)
		printf(": %s\n", msg);
	exit(EXIT_FAILURE);
}
