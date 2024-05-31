/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 08:19:32 by rvandepu          #+#    #+#             */
/*   Updated: 2024/05/31 19:03:48 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdbool.h>
# include <stdlib.h>
# include <limits.h>

# include "libft.h"

/*
 * Stacks & oplist
 */

// remember to change push_swap.c:parse_val if changing this type
typedef int		t_val;

// Order important for oplist.c:apply_ops, squash.c:squash_oplist
typedef enum e_op
{
	NOP = 0,
	SA,
	SB,
	SS,
	PA,
	PB,
	RA,
	RB,
	RR,
	RRA,
	RRB,
	RRR,
	MAXOP,
}	t_op;

typedef struct s_lst
{
	union
	{
		t_val	value;
		t_op	op;
	};
	struct s_lst	*next;
}	t_lst;

typedef t_lst	t_stack;
typedef t_lst	t_oplist;

enum e_type
{
	STACK,
	OPLIST,
};

typedef struct s_ctx
{
	t_oplist	**l;
	t_stack		**a;
	t_stack		**b;
	int			a_len;
	int			b_len;
	bool		turk_rev;
}	t_ctx;

// init.c
bool	parse_val(const char *val, t_val *ret);
bool	init_stacks(t_ctx *c, int argc, char **argv);
bool	normalize(t_ctx *c);

// lst_utils.c
t_lst	*lst_create(enum e_type type, ...);
bool	lst_add(t_lst **start, t_lst *new, int *len, bool check_dupes);
int		lst_size(t_lst *l);
int		lst_indexof(t_lst *l, t_lst *q);
void	free_lst(t_lst **s);

/*
 * Operations
 */

typedef bool	(*t_op_f)(t_ctx *c);

// oplist.c
bool	apply_ops(t_ctx *c, t_oplist **l, int ops[MAXOP]);
void	print_oplist(t_oplist *l);

// swap.c
bool	sa(t_ctx *c);
bool	sb(t_ctx *c);
bool	ss(t_ctx *c);

// push.c
bool	pa(t_ctx *c);
bool	pb(t_ctx *c);

// rot.c
bool	ra(t_ctx *c);
bool	rb(t_ctx *c);
bool	rr(t_ctx *c);

// rrot.c
bool	rra(t_ctx *c);
bool	rrb(t_ctx *c);
bool	rrr(t_ctx *c);

/*
 * Algorithm
 */

// algo.c
bool	is_sorted(t_ctx *c);
bool	fixup(t_ctx *c);
bool	sort(t_ctx *c);

// turk.c
bool	move_min_cost(t_ctx *c);

// squash.c
bool	squash_oplist(t_oplist **start);

#endif
