/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_plan.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filpedroso <filpedroso@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 11:35:18 by filpedroso        #+#    #+#             */
/*   Updated: 2025/06/24 11:35:18 by filpedroso       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	rotate_same_dir(t_plan *plan, t_stack *stack_a, t_stack *stack_b);

void	execute_plan(t_plan plan, t_stack *stack_a, t_stack *stack_b)
{
	if (plan.dir_origin == plan.dir_dest)
		rotate_same_dir(&plan, stack_a, stack_b);
	if (plan.moves_origin)
	{
		if (plan.dir_origin == DIRECT)
			rotate(stack_a, plan.moves_origin, "ra\n");
		else
			reverse(stack_a, plan.moves_origin, "rra\n");
	}
	plan.moves_origin = 0;
	if (plan.moves_dest)
	{
		if (plan.dir_dest == DIRECT)
			rotate(stack_b, plan.moves_dest, "rb\n");
		else
			reverse(stack_b, plan.moves_dest, "rrb\n");
	}
	plan.moves_dest = 0;
	push(stack_a, stack_b, "pb\n");
}

static void	rotate_same_dir(t_plan *plan, t_stack *stack_a, t_stack *stack_b)
{
	while (plan->moves_origin && plan->moves_dest)
	{
		if (plan->dir_origin == DIRECT)
			rr(stack_a, stack_b, PRINT);
		else
			rrr(stack_a, stack_b, PRINT);
		plan->moves_origin--;
		plan->moves_dest--;
	}
}
