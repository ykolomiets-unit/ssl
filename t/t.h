#ifndef T_H
# define T_H

# include "libft.h"

# define RUN_GROUP(group) do {ft_printf("\n"#group":\n"); group();} while(0)
# define RUN_TEST(test) do {			\
		ft_printf("\t"#test":");	\
		if (!test())				\
			ft_printf("OK\n");		\
		else						\
			ft_printf("FAILED\n");	\
		} while(0)					\

#endif
