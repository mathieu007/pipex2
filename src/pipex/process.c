/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroy <mroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 07:57:14 by mroy              #+#    #+#             */
/*   Updated: 2023/02/28 08:00:28 by mroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process(char **argv, char **envp, int32_t *fd)
{
	int32_t	f_in;

	f_in = open(argv[1], O_RDONLY, 0777);
	if (f_in == -1)
		error_exit();
	dup2(fd[1], STDOUT_FILENO);
	dup2(f_in, STDIN_FILENO);
	close(fd[0]);
	execute(argv[2], envp);
}

void	parent_process(char **argv, char **envp, int32_t *fd)
{
	int32_t	f_out;

	f_out = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (f_out == -1)
		error_exit();
	dup2(fd[0], STDIN_FILENO);
	dup2(f_out, STDOUT_FILENO);
	close(fd[1]);
	execute(argv[3], envp);
}
