/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filpedroso <filpedroso@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 22:02:32 by filpedroso        #+#    #+#             */
/*   Updated: 2025/06/02 22:02:32 by filpedroso       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

/* ************************************************************************** */
/*                                 ENUMS                                      */
/* ************************************************************************** */

typedef enum e_dir
{
	DIRECT,
	REVERSE
}					t_dir;

typedef enum e_flow
{
	A_B,
	B_A
}					t_flow;

/* ************************************************************************** */
/*                                 STRUCTS                                    */
/* ************************************************************************** */

typedef struct s_node
{
	int				value;
	int				index;
	struct s_node	*next;
	struct s_node	*prev;
}					t_node;

typedef struct s_stack
{
	t_node			*top;
	int				size;
}					t_stack;

typedef struct s_plan
{
	t_flow			push_flow;
	int				moves_origin;
	t_dir			dir_origin;
	int				moves_dest;
	t_dir			dir_dest;
	int				total_cost;
}					t_plan;

/* ************************************************************************** */
/*                               PROTOTYPES                                   */
/* ************************************************************************** */

void				load_stack(t_stack *stack_a, char *list);
void				free_stack(t_stack *stack);
t_node				*new_node(int element);
void				stack_add_bottom(t_stack *stack, t_node *node);
int					in_bounds(long number);
void				init_stacks(t_stack *stack_a, t_stack *stack_b);
void				push_swap(t_stack *stack_a, t_stack *stack_b);
void				execute_plan(t_plan plan, t_stack *stack_a,
						t_stack *stack_b);
void				rr(t_stack *stack_a, t_stack *stack_b);
void				rrr(t_stack *stack_a, t_stack *stack_b);
int					rotate(t_stack *stack, int times, char *move);
int					reverse(t_stack *stack, int times, char *move);
void				rotate_a_to_top(t_stack *stack);
t_plan				best_plan_ab(t_stack *stack_a, t_stack *stack_b);
int					ft_max(int a, int b);
int					is_sorted(t_stack *stack);
void				sort_three(t_stack *stack);
void				push(t_stack *stack_1, t_stack *stack_2, char *move);
int					ft_numlen(int num);
long				ft_atoi(const char *str);
void				swap(t_stack *stack, char *move);
int					check_args(char *input);
void				ft_putstr_fd(const char *str, int fd);
void				print_stack_dbg(t_stack *stack_a, char *text);
void				dbg_print_indexes(t_stack *stack);
void				calc_mid_position(t_plan *plan, t_stack *stack_b, int idx);
int					smallest_idx(t_stack *stack);
int					biggest_idx(t_stack *stack);
void				push_back(t_stack *stack_a, t_stack *stack_b);
void				rotate_a_to_position(t_stack *stack_a, int idx);
int					min_rotations_to(t_stack *stack, int idx, t_dir *dir);
int					min_rot_direct(t_stack *stack, int idx);
int					min_rot_reverse(t_stack *stack, int idx);
int					find_mid_idx_a(t_stack *stack_a, int idx_from_b);
int					find_idx_in_a(t_stack *stack_a, int idx_from_b);

#endif