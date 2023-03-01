/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroy <mroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 14:47:58 by mroy              #+#    #+#             */
/*   Updated: 2023/03/01 16:12:51 by mroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	child_process(char *argv, char **envp)
{
	pid_t	pid;
	int32_t	fds[2];
	t_proc	*proc;

	if (pipe(fds) == -1)
		error_exit();
	pid = fork();
	proc = init_fds(fds);
	if (pid == -1)
		error_exit();
	if (pid == 0)
	{
		close(proc->file_in);
		dup2(proc->file_out, STDOUT_FILENO);
		execute(argv, envp);
	}
	else
	{
		close(proc->file_out);
		dup2(proc->file_in, STDIN_FILENO);
		waitpid(pid, NULL, 0);
	}
}

void	here_doc(char *sep, int argc)
{
	pid_t	pid;
	int32_t	fds[2];
	char	*line;
	int32_t	sep_len;

	if (argc < 6)
		usage();
	if (pipe(fds) == -1)
		error_exit();
	pid = fork();
	if (pid == 0)
	{
		close(fds[0]);
		sep_len = ft_strlen(sep);
		line = get_next_line_temp(0);
		while (line)
		{
			if (ft_strncmp(line, sep, sep_len) == 0)
				exit(EXIT_SUCCESS);
			write(fds[1], line, ft_strlen(line));
			line = get_next_line_temp(0);
		}
	}
	else
	{
		close(fds[1]);
		dup2(fds[0], STDIN_FILENO);
		wait(NULL);
	}
}

int32_t	open_files(t_proc *proc, int32_t argc, char **argv)
{
	int32_t	f_in;
	int32_t	f_out;

	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		proc->here_doc = true;
		f_out = open(argv, O_WRONLY | O_CREAT | O_APPEND, 0777);
		here_doc(argv[2], argc);
	}
	else
	{
		proc->here_doc = false;
		f_out = open(argv, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		f_in = open(argv, O_RDONLY, 0777);
		dup2(f_in, STDIN_FILENO);
	}
	return (f_out);
}

int32_t	main(int32_t argc, char **argv, char **envp)
{
	t_proc	*proc;
	int32_t	f_out;

	if (argc < 5)
		usage_bonus();
	proc = init_data(argc, argv, envp);
    f_out = open_files(proc, argc, argv);
	while (i < argc - 2)
		child_process(argv[i++], envp);
	dup2(f_out, STDOUT_FILENO);
	execute(argv[argc - 2], envp);
}
