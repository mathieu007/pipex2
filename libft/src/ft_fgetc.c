
#include "libft.h"

int	ft_fgetc(t_file *stream)
{
	int rval;

	if (!stream)
		return (-1);
	if (!stream->buf[stream->i])
	{
		stream->i = 0;
		rval = read(stream->fd, stream->buf, BUFF_SIZE);
		if (rval <= 0)
		{
			stream->buf[0] = 0;
			return (-1);
		}
		stream->buf[rval] = 0;
	}
	return ((int)stream->buf[stream->i++]);
}