/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroy <mroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 08:03:11 by math              #+#    #+#             */
/*   Updated: 2023/02/28 15:24:11 by mroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_exit(void)
{
	perror("Error");
	exit(EXIT_FAILURE);
}

void	usage(void)
{
	printf("Error: Invalid argument count.\n");
	printf("Ex: ./pipex <file1> <cmd1> <cmd2> <file2>\n");
}