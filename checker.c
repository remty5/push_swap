/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 08:18:11 by rvandepu          #+#    #+#             */
/*   Updated: 2024/05/31 19:34:14 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static const char *const	g_ops_str[MAXOP] = {\
	[SA] = "sa\n", \
	[SB] = "sb\n", \
	[SS] = "ss\n", \
	[PA] = "pa\n", \
	[PB] = "pb\n", \
	[RA] = "ra\n", \
	[RB] = "rb\n", \
	[RR] = "rr\n", \
	[RRA] = "rra\n", \
	[RRB] = "rrb\n", \
	[RRR] = "rrr\n", \
};

static bool	init_oplist(t_ctx *c)
{
	char	*input;
	t_op	op;

	input = get_next_line(0);
	while (input)
	{
		op = SA;
		while (op < MAXOP)
		{
			if (ft_strcmp(input, g_ops_str[op]) == 0)
			{
				if (!lst_add(c->l, lst_create(OPLIST, op), NULL, false))
					return (free(input), false);
				else
					break ;
			}
			op++;
		}
		if (op == MAXOP)
			return (free(input), false);
		input = (free(input), get_next_line(0));
	}
	return (true);
}

static bool	exec_oplist(t_ctx *c)
{
	static int	ops[MAXOP];
	t_oplist	*tmp;
	t_oplist	*l;

	tmp = NULL;
	l = *c->l;
	while (l)
	{
		ops[l->op]++;
		if (!apply_ops(c, &tmp, ops))
			return (free_lst(&tmp), false);
		l = l->next;
	}
	free_lst(&tmp);
	return (true);
}

static bool	is_ok(t_ctx *c)
{
	t_stack	*s;

	if (c->b_len)
		return (false);
	s = *c->a;
	while (s)
	{
		if (s->next && s->value > s->next->value)
			return (false);
		s = s->next;
	}
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
		|| !init_oplist(&c)
		|| !exec_oplist(&c))
		err = true;
	else if (is_ok(&c))
		ft_printf("OK\n");
	else
		ft_printf("KO\n");
	free_lst(c.a);
	free_lst(c.b);
	free_lst(c.l);
	if (err)
		return (ft_fprintf(stderr, "Error\n"), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
