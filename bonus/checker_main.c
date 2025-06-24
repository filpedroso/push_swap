/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filpedroso <filpedroso@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:54:01 by filpedroso        #+#    #+#             */
/*   Updated: 2025/06/24 15:54:01 by filpedroso       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

int	main(int argc, char **argv)
{
	t_stack	stack_a;
	t_stack	stack_b;
	char	*args;

	if (argc == 1)
		return (1);
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
	checker(&stack_a, &stack_b);
	free_stack(&stack_a);
	free_stack(&stack_b);
	return (0);
}
