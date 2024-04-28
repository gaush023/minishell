# include "../includes/minishell.h"

int	__get_tokens(char *line);

int	main(int ac, char **av, char **ev)
{
	t_data	data;

	init_data(&data);
	init_env(ev, &data.env);
	get_shlvl_plus(data.env);
	// __get_tokens(" abc defg\'hijklmn\'\'opqrstu\' hoge");
	__get_tokens(" abc    defg   \'hoge hoge\'   hijk ");
	/*
	while (data.continue_flag)
	{
		init_sig();
		parse(&data);
		if (data.continue_flag == false)
			exit(0);
	}
	*/
	return (0);
	(void)ac;
	(void)av;
}
