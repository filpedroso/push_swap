/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filpedroso <filpedroso@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 14:35:11 by filpedroso        #+#    #+#             */
/*   Updated: 2025/06/24 14:35:11 by filpedroso       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

static int	exec_instruct(t_stack *stack_a, t_stack *stack_b, char *instr);
static int	ft_strncmp(const char *s1, const char *s2, size_t n);

void	checker(t_stack *stack_a, t_stack *stack_b)
{
	char	*instruction;

	instruction = get_next_line(0);
	while (instruction)
	{
		if (exec_instruct(stack_a, stack_b, instruction) == -1)
			return (free(instruction));
		free(instruction);
		instruction = get_next_line(0);
	}
	rotate_a_to_top(stack_a);
	if (is_sorted(stack_a))
		ft_putstr_fd("OK\n", 1);
	else
		ft_putstr_fd("KO\n", 1);
}

static int	exec_instruct(t_stack *stack_a, t_stack *stack_b, char *instr)
{
	if (!ft_strncmp(instr, "sa", 2))
		swap(stack_a, "");
	else if (!ft_strncmp(instr, "pa", 2))
		push(stack_b, stack_a, "");
	else if (!ft_strncmp(instr, "pb", 2))
		push(stack_a, stack_b, "");
	else if (!ft_strncmp(instr, "ra", 2))
		rotate(stack_a, 1, "");
	else if (!ft_strncmp(instr, "rb", 2))
		rotate(stack_b, 1, "");
	else if (!ft_strncmp(instr, "rra", 3))
		reverse(stack_a, 1, "");
	else if (!ft_strncmp(instr, "rrb", 3))
		reverse(stack_b, 1, "");
	else if (!ft_strncmp(instr, "rrr", 3))
		rrr(stack_a, stack_b, NO_PRINT);
	else if (!ft_strncmp(instr, "rr", 2))
		rr(stack_a, stack_b, NO_PRINT);
	else
	{
		ft_putstr_fd("Error\n", 2);
		return (-1);
	}
	return (1);
}

static int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (n && *s1 && *s2 && (*s1 == *s2))
	{
		s1++;
		s2++;
		n--;
	}
	if (n == 0)
	{
		return (0);
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}
