/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpedroso <fpedroso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 16:04:34 by filpedroso        #+#    #+#             */
/*   Updated: 2025/06/26 12:22:57 by fpedroso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int argc, char **argv)
{
	t_stack	stack_a;
	t_stack	stack_b;
	char	*args;

	if (argc == 1)
		return (0);
	args = args_to_str(argc, argv);
	if (!args)
		return (1);
	if (!check_args(args))
	{
		free(args);
		ft_putstr_fd("Error\n", 2);
		return (1);
	}
	init_stacks(&stack_a, &stack_b);
	load_stack(&stack_a, args);
	free(args);
	push_swap(&stack_a, &stack_b);
	free_stack(&stack_a);
	free_stack(&stack_b);
	return (0);
}
