/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_back.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filpedroso <filpedroso@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 11:47:28 by filpedroso        #+#    #+#             */
/*   Updated: 2025/06/24 11:47:28 by filpedroso       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	push_back(t_stack *stack_a, t_stack *stack_b)
{
	int	idx_in_a;

	while (stack_b->size)
	{
		idx_in_a = find_idx_in_a(stack_a, stack_b->top->index);
		rotate_a_to_position(stack_a, idx_in_a);
		push(stack_b, stack_a, "pa\n");
	}
}

int	find_idx_in_a(t_stack *stack_a, int idx_from_b)
{
	int	big;
	int	small;

	big = biggest_idx(stack_a);
	small = smallest_idx(stack_a);
	if (idx_from_b > big || idx_from_b < small)
		return (small);
	return (find_mid_idx_a(stack_a, idx_from_b));
}

int	find_mid_idx_a(t_stack *stack_a, int idx_from_b)
{
	t_node	*current;
	int		i;
	int		mid_idx;

	current = stack_a->top;
	i = 0;
	while (i < stack_a->size)
	{
		mid_idx = current->next->index;
		if (current->index < current->next->index)
		{
			if (current->index < idx_from_b
				&& idx_from_b < current->next->index)
				break ;
		}
		current = current->next;
		i++;
	}
	return (mid_idx);
}

void	rotate_a_to_position(t_stack *stack_a, int idx)
{
	t_dir	dir;
	int		n_rot;

	n_rot = min_rotations_to(stack_a, idx, &dir);
	if (dir == DIRECT)
		rotate(stack_a, n_rot, "ra\n");
	else
		reverse(stack_a, n_rot, "rra\n");
}
