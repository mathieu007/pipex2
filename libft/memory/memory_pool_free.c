/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_params_init.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 12:32:38 by mroy              #+#    #+#             */
/*   Updated: 2022/11/29 14:50:37 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_all(void)
{
	int32_t		i;
	t_pool_info	**pools;

	pools = get_pools();
	i = 0;
	while (i < MAX_POOLS)
	{
		free(pools[i]->slots);
		free(pools[i]);
		i++;
	}
}

void	free_pool(void *data)
{
	t_pool_info	*pool;
	int32_t		*to_free;
	int32_t		chunk_size;

	to_free = &((int32_t *)data)[-2];
	chunk_size = to_free[0];
	pool = get_pools()[chunk_size];
	pool->count--;
	pool->slots[to_free[1]] = pool->slots[pool->count];
	pool->slots[pool->count] = (uint8_t *)to_free;
	to_free[1] = pool->count;
	((int32_t *)(pool->slots[pool->count]))[1] = to_free[1];
}
