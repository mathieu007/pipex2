
// #include "pipex_bonus.h"

// void	usage_bonus(void)
// {
// 	printf("Error: Invalid arguments count.");
// 	printf("Example: ./pipex <file1> <cmd1> <cmd2> <...> <file2>\n");
// 	printf("Example: ./pipex \"here_doc\" <LIMITER> <cmd>"
// 		"<cmd1> <...> <file>\n");
// 	exit(EXIT_FAILURE);
// }

// int32_t	open_file(char *argv, int i)
// {
// 	int32_t	file;

// 	file = 0;
// 	if (i == 0)
// 		file = open(argv, O_WRONLY | O_CREAT | O_APPEND, 0777);
// 	else if (i == 1)
// 		file = open(argv, O_WRONLY | O_CREAT | O_TRUNC, 0777);
// 	else if (i == 2)
// 		file = open(argv, O_RDONLY, 0777);
// 	if (file == -1)
// 		error_exit();
// 	return (file);
// }
