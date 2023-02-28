/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroy <mroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 08:02:59 by math              #+#    #+#             */
/*   Updated: 2023/02/28 14:52:38 by mroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_cmds(t_proc *proc)
{
	int32_t	i;
	int32_t	i2;

	i = 0;
	while (i < proc->cmds_count)
	{
		i2 = 0;
		while (proc->cmds[i]->args)
		{
			free(proc->cmds[i]->args[i2]);
			i2++;
		}
		if (proc->cmds[i]->args)
			free(proc->cmds[i]->args);
		free(proc->cmds[i]);
		i++;
	}
	free(proc->cmds);
}

void	free_all(void)
{
	t_proc	*proc;
	int32_t	i;

	i = 0;
	proc = get_proc();
	if (proc == NULL)
		return ;
	if (proc->paths != NULL)
	{
		while (proc->paths[i])
		{
			free(proc->paths);
			i++;
		}
		free(proc->paths);
	}
	if (proc->cmds != NULL)
		free_cmds(proc);
}
