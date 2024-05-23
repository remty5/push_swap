/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 08:18:11 by rvandepu          #+#    #+#             */
/*   Updated: 2024/05/23 03:52:57 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	print_stacks(t_ctx *c, t_stack *a, t_stack *b)
{
	int		a_len;
	int		b_len;

	a_len = lst_size(a);
	b_len = lst_size(b);
	while (a || b)
	{
		if (a_len > b_len)
		{
			ft_printf("%11d |\n", a->value);
			a_len--;
			a = a->next;
		}
		else if (a_len < b_len)
		{
			ft_printf("%11s | %d\n", "", b->value);
			b_len--;
			b = b->next;
		}
		else
		{
			ft_printf("%11d | %d\n", a->value, b->value);
			a = a->next;
			b = b->next;
		}
	}
	ft_printf("%11c | %c\n", '-', '-');
	ft_printf("%11c | %c\n", 'a', 'b');
	ft_printf("%11d | %d\n", c->a_len, c->b_len);
}

int	count_asc(t_stack *s);

// TODO display "Error\n" on error and check that values are integers
bool	move_min_cost(t_ctx *c, int *ret, int depth);

int	main(int argc, char *argv[])
{
	t_stack (*a) = NULL, *b = NULL;
	t_oplist (*l) = NULL;
	int (i) = 0;
	t_ctx (c) = {.l = &l, .a = &a, .b = &b};
	while (++i < argc)
		if (!lst_add(&a, lst_create(STACK, ft_atoi(argv[i])), &c.a_len, true))
			return (free_lst(&a), EXIT_FAILURE);
	print_stacks(&c, a, b);
	pb(&c);
	pb(&c);
	print_stacks(&c, a, b);
	ft_printf("sizes:\n\ta: %d,\n\tb: %d\n", c.a_len, c.b_len);
	ft_printf("number of sorted elements: %d\n", count_asc(a));
	ft_printf("number of operations: %d\n", lst_size(l));
	while (c.a_len)
		move_min_cost(&c, NULL, 0);
	print_stacks(&c, a, b);
	ft_printf("sizes:\n\ta: %d,\n\tb: %d\n", c.a_len, c.b_len);
	ft_printf("number of sorted elements: %d\n", count_asc(a));
	ft_printf("number of operations: %d\n", lst_size(l));
	free_lst(c.a);
	free_lst(c.b);
	free_lst(c.l);
	return (EXIT_SUCCESS);
}
