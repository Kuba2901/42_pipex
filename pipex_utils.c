/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:04:14 by jnenczak          #+#    #+#             */
/*   Updated: 2024/04/19 14:04:30 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void	assign_fds(t_pipex *pipex, char **av)
{
	pipex->input_invalid = TRUE;
	pipex->in_fd = -1;
	pipex->out_fd = -1;
	pipex->in_fd = open(av[1], O_RDONLY);
	if (pipex->in_fd < 0)
		return ;
	pipex->out_fd = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (pipex->out_fd < 0)
	{
		close(pipex->in_fd);
		return ;
	}
	pipex->input_invalid = FALSE;
}

void	print_split(char **split)
{
	while (*split)
		ft_printf("%s\n", *split++);
}

void	free_split(char **split)
{
	int	i;

	i = -1;
	while (split[++i])
		free(split[i]);
	free(split);
}

char	**retrieve_cmd_paths(char **envp)
{
	char	*temp;
	char	**paths;
	int		i;

	i = -1;
	while (envp[++i])
	{
		if (!ft_strncmp(envp[i], "PATH", 4))
			break ;
	}
	temp = ft_substr(envp[i], 5, ft_strlen(envp[i]) - 5);
	paths = ft_split(temp, ':');
	free(temp);
	i = -1;
	while (paths[++i])
	{
		temp = ft_strdup("/");
		paths[i] = ft_join_reassign(paths[i], temp);
	}
	return (paths);
}

t_cmd_args	*create_cmd_args(char *cmd)
{
	t_cmd_args	*ret;
	char		**temp;

	temp = ft_split(cmd, ' ');
	ret = malloc(sizeof(t_cmd_args));
	ret->cmd = temp[0];
	ret->args = temp + 1;
	return (ret);
}
