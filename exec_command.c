/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 21:12:19 by caqueiro          #+#    #+#             */
/*   Updated: 2024/10/10 02:05:33 by cassius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void exec_command(t_token_lst *l, t_hashmap *envs);
static void handle_main_process(t_token **t, t_token_lst *lst);
static void	update_last_status(t_hashmap *envs, int status);

void exec_all_commands(t_token_lst *lst, t_hashmap *envs)
{
  t_token *t;
  t_token *tmp;
  pid_t 	pid;
	int 		status;

  t = lst->head;
	unquotes_all_words(lst);
	pipe_all_cmds(lst);
  while (t)
  {
    redir_next_cmd(lst);
    if (t->type == COMMAND)
    {
      pid = fork();
      if (pid == 0)
      {
        exec_command(lst, envs);
        exit(0);
      }
      else
        handle_main_process(&t, lst);
    }
    else
      t = t->next;
  }
  while (wait(&status) > 0)
  {
    if (WIFEXITED(status))
			update_last_status(envs, WEXITSTATUS(status));
  }
}

static void exec_command(t_token_lst *l, t_hashmap *envs)
{
  char **args;
  char *path;
	t_token *t;

  if (l->head->type != COMMAND)
    return ;
  args = build_args(*l);
  path = absolute_path(l->head, envs);
  if (!path)
	{
		ft_printf("%s: command not found\n", l->head->word);
		exit(127);
	}
  if (l->head->fd[0] != STDIN_FILENO)
  {
    dup2(l->head->fd[0], STDIN_FILENO);
    close(l->head->fd[0]);
  }
  if (l->head->fd[1] != STDOUT_FILENO)
  {
    dup2(l->head->fd[1], STDOUT_FILENO);
    close(l->head->fd[1]);   
  }
	t = l->head;
	while (t)
	{
		close_not_used_fd(t);
		t = t->next;
	}
  execve(path, args, to_envp(*envs));
}

static void handle_main_process(t_token **t, t_token_lst *lst)
{
  t_token *tmp;

  close_not_used_fd(*t);
  tmp = (*t)->next;
  consume_token(lst, *t);
  *t = tmp;
  while (*t && (*t)->type != COMMAND)
  {
    tmp = (*t)->next;
    consume_token(lst, *t);
    *t = tmp;
  }
}

void close_not_used_fd(t_token *t)
{
	if (t->fd[0] != STDIN_FILENO)
		close(t->fd[0]);
	if (t->fd[1] != STDOUT_FILENO)
		close(t->fd[1]);
}

static void	update_last_status(t_hashmap *envs, int status)
{
	char	*str;

	str = ft_itoa(status);
	insert_pair(&envs, create_pair("?", str));
	free(str);
}