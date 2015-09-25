// SVN: $Revision: 56 $
#include <errno.h>
#include <stdarg.h>
#include <string.h>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

void error_exit(const char *format, ...)
{
	va_list ap;

	va_start(ap, format);
	vfprintf(stderr, format, ap);
	va_end(ap);

	fprintf(stderr, "\nerrno at that time: %s (%d)\n", strerror(errno), errno);

	exit(EXIT_FAILURE);
}
