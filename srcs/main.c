# include "../includes/minishell.h"

int	__get_tokens(char *line);

int	main(int ac, char **av, char **ev)
{
	t_data	data;
	char	*str;
	
	/* str	= ft_strdup(" echo \'hoge hoge\'>>text.txt;echo \'Hello  World\'>>hoge.txt "); */
	str	= ft_strdup(" a b c d e f g ");
	str = transform_line(str);

	init_data(&data);
	init_env(ev, &data.env);
	get_shlvl_plus(data.env);
	// __get_tokens(" abc defg\'hijklmn\'\'opqrstu\' hoge");
	printf("test string :\n\t%s\n", str);
	__get_tokens(str);
	/* get_tokens(str, &data); */
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

/*
ab cdef 'gh  ij' klmn
[ab cdef] [gh  ij] [klmn]

*/
