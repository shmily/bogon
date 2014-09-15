
#ifndef __author_h__
#define __author_h__

#include "config.h"

struct author_ops_t;

struct author {
	char name[MAX_NAME_LEN];
	struct book *book;
	struct author_ops_t *ops;

	struct author *prev;
	struct author *next;
};

struct author_ops_t {
	int (*is_me)(const char *author_name);
	int (*book_add)(struct book *new);
	int (*book_del)(struct book *del);
};

#endif

