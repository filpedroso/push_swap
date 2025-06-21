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

# include <stdio.h>
# include <limits.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>

/* ************************************************************************** */
/*                                 ERRORS                                     */
/* ************************************************************************** */

# define OUTSIDE_INT -1
# define INVALID_ELEMENT -2

/* ************************************************************************** */
/*                              INSTRUCTIONS                                  */
/* ************************************************************************** */

# define SA 1
# define SB 2
# define SS 3
# define PA 4
# define PB 5
# define RA 6
# define RB 7
# define RR 8
# define RRA 9
# define RRB 10
# define RRR 11

/* ************************************************************************** */
/*                                 ENUMS                                      */
/* ************************************************************************** */

typedef enum e_dir
{
	ROTATE,
	REVERSE
}					t_dir;

typedef enum	e_flow
{
	A_B,
	B_A
}				t_flow;

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

typedef struct 		s_plan
{
	int				a_index;
	int				b_index;
	int				a_moves;
	int				b_moves;
	t_dir			a_direction;
	t_dir			b_direction;
	int				total_cost;
	t_flow			push_flow;
}					t_plan;

/* ************************************************************************** */
/*                                FUNCTIONS                                   */
/* ************************************************************************** */

void				load_stack(t_stack *stack_a, char *list);
void				free_stack(t_stack *stack);
void				put_sorted_indexes(t_stack *stack);
t_node				*new_node(int element);
void				stack_add_bottom(t_stack *stack, t_node *node);
long				get_next_element(char **list);
int					in_bounds(long number);
void				init_stacks(t_stack *stack_a, t_stack *stack_b);
void				push_swap(t_stack *stack_a, t_stack *stack_b);
void				execute_plan(t_plan plan, t_stack *stack_a,
						t_stack *stack_b);
void				rr(t_stack *stack_a, t_stack *stack_b);
void				rrr(t_stack *stack_a, t_stack *stack_b);
int					rotate(t_stack *stack, int times, char *move);
int					reverse(t_stack *stack, int times, char *move);
void				rotate_to_min(t_stack *stack);
t_plan				best_plan_ab(t_stack *stack_a, t_stack *stack_b);
t_plan				best_plan_ba(t_stack *stack_b, t_stack *stack_a);
int					ft_max(int a, int b);
int					find_b_insert_pos(t_stack *stack_b, int sorted_idx);
int					find_a_insert_pos(t_stack *stack_a, int sorted_idx);
void				calc_moves(t_plan *plan, t_stack *stack_1,
						t_stack *stack_2);
int					is_sorted(t_stack *stack);
void				sort_three(t_stack *stack);
void				push(t_stack *stack_1, t_stack *stack_2, char *move);
void				calc_single_move(int position, int size, int *moves,
						t_dir *dir);
t_node				*pop(t_stack *stack);
int					ft_numlen(int num);
long				ft_atoi(const char *str);
void				reinsert_after(t_node *position, t_node *node);
void				swap(t_stack *stack, char *move);
int					has_duplicate(t_stack *stack);
int					check_args(char *input);
void				rotate_same_dir(t_plan *plan, t_stack *stack_a, t_stack *stack_b);
void				ft_putstr_fd(const char *str, int fd);
void				print_stack_dbg(t_stack *stack_a);
void				dbg_print_indexes(t_stack *stack);

#endif