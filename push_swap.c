/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 08:18:11 by rvandepu          #+#    #+#             */
/*   Updated: 2024/05/31 18:54:39 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static bool	exec_algo(t_ctx *c)
{
	if (c->a_len < 2)
		return (true);
	if (c->a_len == 2 || c->a_len == 3)
	{
		if (!fixup(c))
			return (false);
		if ((*c->a)->value > (*c->a)->next->value)
			return (sa(c));
		return (true);
	}
	if (is_sorted(c))
		return (fixup(c));
	if (!sort(c))
		return (false);
	return (true);
}

int	main(int argc, char *argv[])
{
	t_stack		*a;
	t_stack		*b;
	t_oplist	*l;
	t_ctx		c;
	bool		err;

	err = false;
	c = (t_ctx){.l = &l, .a = &a, .b = &b};
	if (!init_stacks(&c, argc, argv)
		|| !exec_algo(&c)
		|| !squash_oplist(c.l)
		|| (print_oplist(*c.l), false))
		err = true;
	free_lst(c.a);
	free_lst(c.b);
	free_lst(c.l);
	if (err)
		return (ft_fprintf(stderr, "Error\n"), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
