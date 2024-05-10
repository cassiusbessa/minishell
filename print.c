/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caqueiro <caqueiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 20:39:51 by caqueiro          #+#    #+#             */
/*   Updated: 2024/04/11 20:40:52 by caqueiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_double_pointer(char **arr)
{
	int	i;

	i = 0;
	if (arr == NULL)
		return ;
	ft_printf("args:\n");
	while (arr[i])
	{
		ft_printf("%s ", arr[i]);
		i++;
	}
	ft_printf("\n");
}

void  print_all_commands(t_cmd_lst *lst)
{
  t_command *current;
  t_command *next;

  current = lst->head;
  while (current)
  {
    next = current->next;
    ft_printf("instruction:%s\n", current->instruction);
    ft_printf("flags:\n");
    print_list(current->flags);
    ft_printf("args:\n");
    print_list(current->args);
    ft_printf("separator:%s\n", current->separator);
    ft_printf("path:%s\n", current->path);
    current = next;
  }
}

void	print_list(t_list *lst)
{
	t_node *current;

	if (!lst)
		return ;
	current = lst->head;
	while (current != NULL)
	{
		ft_printf("%s\n", current->value);
		current = current->next;
	}
}