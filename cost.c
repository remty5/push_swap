/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cost.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:10:14 by rvandepu          #+#    #+#             */
/*   Updated: 2024/05/21 03:26:22 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// Longest Increasing Subsequence problem
int	count_asc(t_stack *s)
{
	t_val	last;
	int		n;

	if (!s)
		return (0);
	n = 1;
	last = s->s.value;
	while (s)
	{
		if (last < s->s.value)
		{
			last = s->s.value;
			n++;
		}
		s = s->next;
	}
	return (n);
}

/*void	calc_costs(t_turk *ctx)
{
	t_stack	*s;

	s = *a;
	while (s)
	{
		s->cost = 0;
		s = s->next;
	}
}*/
