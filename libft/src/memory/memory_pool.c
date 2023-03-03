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

/// @brief pools can be of variable size index: 1 = 2, 2 = 4, 3 = 8, 4 = 16 ...
/// @param
/// @return
t_pool_info	**get_pools(void)
{
	static t_pool_info	*pools[64];

	return (&pools[0]);
}

void	init_pools(void)
{
	int32_t		i;
	t_pool_info	**pools;

	pools = get_pools();
	i = 0;
	while (i < MAX_POOLS)
	{
		pools[i] = malloc(sizeof(t_pool_info));
		pools[i]->capacity = 0;
		pools[i]->count = 0;
		pools[i]->chunk_size = ft_exponent(2, i);
		pools[i]->slots = NULL;
		i++;
	}
}

void	*alloc(size_t size_in_bytes)
{
	t_pool_info	*pool;
	int32_t		cur_index;
	uint64_t	chunk_id;

	chunk_id = ft_log2_64((uint64_t)size_in_bytes - 1) + 1;
	pool = get_pools()[chunk_id];
	cur_index = pool->count;
	if (pool->count == pool->capacity && resize_pool(pool) == NULL)
		return (free_p_all(), NULL);
	pool->count++;
	*(int32_t *)(pool->slots[cur_index]) = chunk_id;
	return ((void *)&(pool->slots[cur_index])[8]);
}
