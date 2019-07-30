#include "asm.h"

int		is_asm_file(char *name)
{
	char	*ext;

	ext = ft_strrchr(name, '.');
	if (!ft_strequ(ext, ".s"))
		return (0);
	return (1);
}
