/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filpedroso <filpedroso@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 00:34:52 by filpedroso        #+#    #+#             */
/*   Updated: 2025/06/02 00:34:52 by filpedroso       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	main(int argc, char **argv)
{
	t_stack	stack_a;
	t_stack	stack_b;

	// check argc simply

	init_stacks(&stack_a, &stack_b);
	load_stack(&stack_a, argv);
	if (stack_a->size < 2)
	{
		error();
		exit(1);
	}
	push_swap(&stack_a, &stack_b);
	free_stack(&stack_a);
	free_stack(&stack_b);
	return (1);
}

void	push_swap(t_stack *stack_a, t_stack *stack_b)
{
	int		i;
	t_plan	plan;

	if (stack_a->size <= 3)
		return (two_or_three(stack_a));
	push(stack_a, stack_b);
	push(stack_a, stack_b);
	i = 0;
	while (stack_a->size > 3)
	{
		plan = get_cheapest_plan(stack_a, stack_b);
		execute_plan(plan, stack_a, stack_b);
	}
	return (two_or_three(stack_a));
}