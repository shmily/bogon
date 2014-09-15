
#ifndef __utils_h__
#define __utils_h__

int file_read_value(const char *path, const char *name,
		const char *format, void *value);

int file_write_value(const char *path, const char *name,
		const char *format, void *value);

#endif
