/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroy <mroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 15:21:35 by mroy              #+#    #+#             */
/*   Updated: 2023/03/01 15:48:34 by mroy             ###   ########.fr       */
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
	char		**args;
	char		*cmd;
}				t_cmd;

typedef struct s_file_d
{
	int32_t		fd;
	char		*f_name;
}				t_file_d;

typedef struct s_proc
{
	t_file_d	file_in[1];
	t_file_d	file_out[1];
	pid_t		pid;
	bool		here_doc;
	char		**paths;
	t_cmd		**cmds;
	int32_t		cmds_count;
	char		**envp;
}				t_proc;

int32_t			open_file(char *argv, int i);
void			unlink_fifo(char *f_name);
void			usage(void);
void			error_exit(void);
char			*find_path(char *cmd, char **envp);
void			execute(t_proc *proc, int32_t i);
void			child_process(t_proc *proc, int32_t cmd_i);
void			parent_process(t_proc *proc, int32_t cmd_i);
char			**parse_paths(char **envp);
t_cmd			**parse_cmds(t_proc *proc, char **argv, int32_t count);
char			*get_full_path_cmd(t_proc *proc, char *cmd);
void			free_all(void);
t_proc			*get_proc(void);
t_proc			*init_data(int32_t argc, char **argv, char **envp);
t_proc			*init_fds(int *fds);

#endif
