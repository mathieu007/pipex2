/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroy <mroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 14:48:40 by mroy              #+#    #+#             */
/*   Updated: 2023/03/01 16:14:32 by mroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	usage_bonus(void)
{
	printf("Error: Invalid arguments count.");
	printf("Example: ./pipex <file1> <cmd1> <cmd2> <...> <file2>\n");
	printf("Example: ./pipex \"here_doc\" <LIMITER> <cmd>"
		"<cmd1> <...> <file>\n");
	exit(EXIT_FAILURE);
}