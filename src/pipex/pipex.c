/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 08:02:59 by math              #+#    #+#             */
/*   Updated: 2023/02/27 22:13:09 by math             ###   ########.fr       */
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

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid1;

	init_pools();
	if (argc == 5)
	{
		if (pipe(fd) == -1)
			error_exit();
		pid1 = fork();
		if (pid1 == -1)
			error_exit();
		if (pid1 == 0)
			child_process(argv, envp, fd);
		waitpid(pid1, NULL, 0);
		parent_process(argv, envp, fd);
	}
	else
	{
		ft_putstr_fd("Error: Invalid argument count.\n", 2);
		ft_putstr_fd("Ex: ./pipex <file1> <cmd1> <cmd2> <file2>\n", 1);
	}
	return (0);
}
