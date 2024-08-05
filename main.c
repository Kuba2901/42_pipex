/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 13:54:30 by jnenczak          #+#    #+#             */
/*   Updated: 2024/08/05 16:20:59 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void	pipe_start_process(t_pipex pipex, int cmd_num, int pipe_end[2])
{
	int		i;
	char	*temp;

	dup2(pipex.in_fd, STDIN_FILENO);
	dup2(pipe_end[1], STDOUT_FILENO);
	close(pipe_end[0]);
	i = -1;
	while (pipex.cmd_paths[++i])
	{
		temp = ft_strjoin(pipex.cmd_paths[i], pipex.cmd_args[cmd_num]->cmd);
		execve(temp, pipex.cmd_args[cmd_num]->args - 1, pipex.envp);
		free(temp);
	}
	close(pipex.in_fd);
	if (access(pipex.cmd_args[cmd_num]->cmd, X_OK) < 0)
		perror(pipex.cmd_args[cmd_num]->cmd);
	exit(EXIT_FAILURE);
}

void	pipe_end_process(t_pipex pipex, int cmd_num, int pipe_end[2])
{
	int		i;
	char	*temp;

	dup2(pipex.out_fd, STDOUT_FILENO);
	dup2(pipe_end[0], STDIN_FILENO);
	close(pipe_end[1]);
	i = -1;
	while (pipex.cmd_paths[++i])
	{
		temp = ft_strjoin(pipex.cmd_paths[i], pipex.cmd_args[cmd_num]->cmd);
		execve(temp, pipex.cmd_args[cmd_num]->args - 1, pipex.envp);
		free(temp);
	}
	close(pipex.out_fd);
	if (access(pipex.cmd_args[cmd_num]->cmd, X_OK) < 0)
		perror(pipex.cmd_args[cmd_num]->cmd);
	exit(EXIT_FAILURE);
}

void	close_and_wait(int end[2], pid_t child1, pid_t child2, int *status)
{
	close(end[0]);
	close(end[1]);
	waitpid(child1, status, 0);
	waitpid(child2, status, 0);
}

void	do_pipe(t_pipex pipex)
{
	int		end[2];
	int		status;
	pid_t	child1;
	pid_t	child2;

	if (pipe(end))
		exit(1);
	child1 = fork();
	if (child1 < 0)
	{
		perror("");
		exit(EXIT_FAILURE);
	}
	if (child1 == 0)
		pipe_start_process(pipex, 0, end);
	child2 = fork();
	if (child2 < 0)
	{
		perror("");
		exit(EXIT_FAILURE);
	}
	if (child2 == 0)
		pipe_end_process(pipex, 1, end);
	close_and_wait(end, child1, child2, &status);
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	pipex;

	if (ac < 5)
		exit(EXIT_FAILURE);
	pipex = parse_input(ac, av, envp);
	if (pipex.input_invalid)
		return (0);
	pipex.cmd_count = ac - 3;
	pipex.envp = envp;
	do_pipe(pipex);
	free_resources(pipex);
	return (0);
}
