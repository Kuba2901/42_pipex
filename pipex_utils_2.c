/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:05:08 by jnenczak          #+#    #+#             */
/*   Updated: 2024/04/19 14:05:13 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

t_cmd_args	**parse_cmd_with_args(int ac, char **av)
{
	t_cmd_args	**ret;
	char		*temp;
	int			i;

	ret = malloc(sizeof(t_cmd_args *) * ((ac - 3) + 1));
	i = 1;
	while (++i < ac - 1)
	{
		temp = ft_strdup(av[i]);
		ret[i - 2] = create_cmd_args(temp);
		free(temp);
	}
	ret[i - 2] = NULL;
	return (ret);
}

void	free_cmd_with_args(t_cmd_args **cmds)
{
	int	i;

	i = -1;
	while (cmds[++i])
	{
		free_split((cmds[i]->args - 1));
		free(cmds[i]);
	}
	free(cmds);
}

void	print_cmd_with_args(t_cmd_args **cmds)
{
	int	i;
	int	j;

	i = -1;
	while (cmds[++i])
	{
		j = -1;
		printf("Command: %s, args: ", cmds[i]->cmd);
		while (cmds[i]->args[++j])
			printf("%s ", cmds[i]->args[j]);
		printf("\n");
	}
}

void	free_resources(t_pipex pipex)
{
	if (pipex.in_fd != -1)
		close(pipex.in_fd);
	if (pipex.out_fd != -1)
		close(pipex.out_fd);
	free_cmd_with_args(pipex.cmd_args);
	free_split(pipex.cmd_paths);
}

t_pipex	parse_input(int ac, char **av, char **envp)
{
	t_pipex	ret;

	assign_fds(&ret, av);
	if (ret.input_invalid)
		return (ret);
	ret.cmd_args = parse_cmd_with_args(ac, av);
	ret.cmd_paths = retrieve_cmd_paths(envp);
	return (ret);
}
