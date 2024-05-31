/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 08:18:11 by rvandepu          #+#    #+#             */
/*   Updated: 2024/05/31 17:51:50 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*void	print_stacks(t_ctx *c, t_stack *a, t_stack *b)
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
}*/

static inline bool	parse_val(const char *val, t_val *ret)
{
	int		i;
	char	sign;
	long	n;

	while (*val == ' ' || ('\t' <= *val && *val <= '\r'))
		val++;
	sign = 1;
	if (*val == '-' || *val == '+')
		if (*(val++) == '-')
			sign = -sign;
	i = 0;
	n = 0;
	while ('0' <= val[i] && val[i] <= '9' && i < 10)
	{
		n *= 10;
		n += val[i++] - '0';
	}
	n = n * sign;
	if (i == 0 || n < INT_MIN || INT_MAX < n)
		return (false);
	*ret = n;
	return (val[i] == '\0');
}

static bool	init_stacks(t_ctx *c, int argc, char **argv)
{
	t_val	val;
	int		i;

	*c->a = NULL;
	*c->b = NULL;
	*c->l = NULL;
	i = 0;
	while (++i < argc)
		if (!parse_val(argv[i], &val)
			|| !lst_add(c->a, lst_create(STACK, val), &c->a_len, true))
			return (false);
	if (!normalize(c))
		return (false);
	return (true);
}

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
		return (ft_printf("Error\n"), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
