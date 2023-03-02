/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroy <mroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 15:21:35 by mroy              #+#    #+#             */
/*   Updated: 2023/03/02 16:41:14 by mroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_cmd
{
	char	**args;
	char	*cmd;
	int32_t	file_in;
	int32_t	file_out;
	pid_t	pid;
}			t_cmd;

typedef struct s_proc
{
	bool	here_doc;
	char	**paths;
	t_cmd	**cmds;
	char	*f_in;
	char	*f_out;
	int32_t	cmds_count;
	char	**envp;
}			t_proc;

int32_t		open_files(t_proc *proc, int32_t argc, char **argv);
void		unlink_fifo(char *f_name);
void		usage(void);
void		error_exit(void);
void		execute(t_proc *proc, int32_t i);
void		child_process(t_proc *proc, int32_t cmd_i);
char		**parse_paths(char **envp);
t_cmd		**parse_cmds(t_proc *proc, char **argv, int32_t count);
void		pipe_childs(t_proc *proc);
char		*get_full_path_cmd(t_proc *proc, char *cmd);
void		free_all(void);
t_proc		*get_proc(void);
t_proc		*init_data(int32_t argc, char **argv, char **envp);
t_proc		*init_fds(int32_t *fds, int32_t i);
void		exec_childs(t_proc *proc);

#endif
