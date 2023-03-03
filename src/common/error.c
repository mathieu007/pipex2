/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroy <mroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 08:03:11 by math              #+#    #+#             */
/*   Updated: 2023/03/03 14:56:14 by mroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errno.h"
#include "pipex.h"

void	error_exit(const char *msg)
{
	t_proc	*proc;
	char	*join_str;

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
	join_str = "Error";
	if (msg != NULL)
		join_str = ft_strjoin("Error: ", msg);
	perror(join_str);
	exit(EXIT_FAILURE);
}
