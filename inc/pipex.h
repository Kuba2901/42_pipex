/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:05:34 by jnenczak          #+#    #+#             */
/*   Updated: 2024/04/19 14:07:31 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <libft.h>
# include <sys/wait.h>

# define INPUT_INVALID -1

typedef enum s_bool
{
	FALSE,
	TRUE
}	t_bool;

typedef struct s_cmd_args
{
	char	*cmd;
	char	**args;
}	t_cmd_args;

typedef struct s_pipex
{
	int			in_fd;
	int			out_fd;
	t_bool		here_doc;
	t_bool		input_invalid;
	t_cmd_args	**cmd_args;
	char		**cmd_paths;
	int			cmd_count;
	char		**envp;
}	t_pipex;

t_cmd_args	**parse_cmd_with_args(int ac, char **av);
void		free_cmd_with_args(t_cmd_args **cmds);
void		print_cmd_with_args(t_cmd_args **cmds);
void		free_resources(t_pipex pipex);
t_pipex		parse_input(int ac, char **av, char **envp);
t_cmd_args	*create_cmd_args(char *cmd);
char		**retrieve_cmd_paths(char **envp);
void		free_split(char **split);
void		print_split(char **split);
void		assign_fds(t_pipex *pipex, char **av);
#endif
