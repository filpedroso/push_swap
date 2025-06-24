/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_rotations.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filpedroso <filpedroso@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 11:51:03 by filpedroso        #+#    #+#             */
/*   Updated: 2025/06/24 11:51:03 by filpedroso       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	min_rotations_to(t_stack *stack, int idx, t_dir *dir)
{
	int	rot_direct;
	int	rot_reverse;

	rot_direct = min_rot_direct(stack, idx);
	rot_reverse = min_rot_reverse(stack, idx);
	if (rot_direct <= rot_reverse)
	{
		*dir = DIRECT;
		return (rot_direct);
	}
	*dir = REVERSE;
	return (rot_reverse);
}

int	min_rot_direct(t_stack *stack, int idx)
{
	int		rot_direct;
	t_node	*node;

	node = stack->top;
	rot_direct = 0;
	while (rot_direct < stack->size)
	{
		if (idx == node->index)
			break ;
		node = node->next;
		rot_direct++;
	}
	return (rot_direct);
}

int	min_rot_reverse(t_stack *stack, int idx)
{
	int		rot_reverse;
	t_node	*node;

	node = stack->top;
	rot_reverse = 0;
	while (rot_reverse < stack->size)
	{
		if (idx == node->index)
			break ;
		node = node->prev;
		rot_reverse++;
	}
	return (rot_reverse);
}

int	biggest_idx(t_stack *stack)
{
	t_node	*node;
	int		biggest;
	int		i;

	node = stack->top;
	i = 0;
	while (i < stack->size)
	{
		if (i == 0 || node->index > biggest)
			biggest = node->index;
		node = node->next;
		i++;
	}
	return (biggest);
}

int	smallest_idx(t_stack *stack)
{
	t_node	*node;
	int		smallest;
	int		i;

	node = stack->top;
	i = 0;
	while (i < stack->size)
	{
		if (i == 0 || node->index < smallest)
			smallest = node->index;
		node = node->next;
		i++;
	}
	return (smallest);
}
