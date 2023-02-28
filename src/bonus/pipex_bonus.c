
// #include "pipex_bonus.h"

// void	child_process(char *argv, char **envp)
// {
// 	pid_t	pid;
// 	int32_t	fd[2];

// 	if (pipe(fd) == -1)
// 		error_exit();
// 	pid = fork();
// 	if (pid == -1)
// 		error_exit();
// 	if (pid == 0)
// 	{
// 		close(fd[0]);
// 		dup2(fd[1], STDOUT_FILENO);
// 		execute(argv, envp);
// 	}
// 	else
// 	{
// 		close(fd[1]);
// 		dup2(fd[0], STDIN_FILENO);
// 		waitpid(pid, NULL, 0);
// 	}
// }

// void	here_doc(char *sep, int argc)
// {
// 	pid_t	pid;
// 	int32_t	fd[2];
// 	char	*line;
// 	int32_t	sep_len;

// 	if (argc < 6)
// 		usage();
// 	if (pipe(fd) == -1)
// 		error_exit();
// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		close(fd[0]);
// 		sep_len = ft_strlen(sep);
// 		line = get_next_line_temp(0);
// 		while (line)
// 		{
// 			if (ft_strncmp(line, sep, sep_len) == 0)
// 				exit(EXIT_SUCCESS);
// 			write(fd[1], line, ft_strlen(line));
// 			line = get_next_line_temp(0);
// 		}
// 	}
// 	else
// 	{
// 		close(fd[1]);
// 		dup2(fd[0], STDIN_FILENO);
// 		wait(NULL);
// 	}
// }

// int32_t	main(int argc, char **argv, char **envp)
// {
// 	int32_t	i;
// 	int32_t	filein;
// 	int32_t	fileout;

// 	if (argc >= 5)
// 	{
// 		if (ft_strncmp(argv[1], "here_doc", 8) == 0)
// 		{
// 			i = 3;
// 			fileout = open_file(argv[argc - 1], 0);
// 			here_doc(argv[2], argc);
// 		}
// 		else
// 		{
// 			i = 2;
// 			fileout = open_file(argv[argc - 1], 1);
// 			filein = open_file(argv[1], 2);
// 			dup2(filein, STDIN_FILENO);
// 		}
// 		while (i < argc - 2)
// 			child_process(argv[i++], envp);
// 		dup2(fileout, STDOUT_FILENO);
// 		execute(argv[argc - 2], envp);
// 	}
// 	usage_bonus();
// }
