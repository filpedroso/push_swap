/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   best_plan_ab.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filpedroso <filpedroso@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 11:17:31 by filpedroso        #+#    #+#             */
/*   Updated: 2025/06/24 11:17:31 by filpedroso       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	calc_b_moves(t_plan *plan, t_stack *stack_b, int idx);
static int	find_mid_idx_b(t_stack *stack_b, int new_idx);
static void	wrap_plan(t_plan *plan);

t_plan	best_plan_ab(t_stack *stack_a, t_stack *stack_b)
{
	t_plan	best;
	t_plan	plan;
	t_node	*current;
	int		i;

	current = stack_a->top;
	i = -1;
	while (++i < stack_a->size)
	{
		plan.moves_origin = i;
		plan.dir_origin = DIRECT;
		if (i > stack_a->size / 2)
		{
			plan.moves_origin = stack_a->size - i;
			plan.dir_origin = REVERSE;
		}
		calc_b_moves(&plan, stack_b, current->index);
		wrap_plan(&plan);
		if (i == 0 || plan.total_cost < best.total_cost)
			best = plan;
		current = current->next;
	}
	return (best);
}

static void	calc_b_moves(t_plan *plan, t_stack *stack_b, int idx)
{
	int	big;
	int	small;
	int	mid;

	big = biggest_idx(stack_b);
	small = smallest_idx(stack_b);
	plan->dir_dest = DIRECT;
	if (idx > big || idx < small)
		plan->moves_dest = min_rotations_to(stack_b, big, &plan->dir_dest);
	else
	{
		mid = find_mid_idx_b(stack_b, idx);
		plan->moves_dest = min_rotations_to(stack_b, mid, &plan->dir_dest);
	}
}

static int	find_mid_idx_b(t_stack *stack_b, int new_idx)
{
	t_node	*current;
	int		i;
	int		mid_idx;

	current = stack_b->top;
	i = 0;
	while (i < stack_b->size)
	{
		mid_idx = current->next->index;
		if (current->index > current->next->index)
		{
			if (current->index > new_idx && new_idx > current->next->index)
				break ;
		}
		current = current->next;
		i++;
	}
	return (mid_idx);
}

static void	wrap_plan(t_plan *plan)
{
	if (plan->dir_dest == plan->dir_origin)
	{
		plan->total_cost = ft_max(plan->moves_dest, plan->moves_origin);
		return ;
	}
	plan->total_cost = plan->moves_dest + plan->moves_origin;
}
