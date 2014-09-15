
#ifndef __book_h__
#define __book_h__

#include "config.h"

struct book_ops_t;

struct book {
	char name[MAX_BOOK_NAME_LEN];
	int state;
	struct author *author;
	struct patron *owner;
	struct book_ops_t *ops;

	struct book *prev;
	struct book *next;
};

struct book_ops_t {
	int (*book_checkout)(struct book *b);
	int (*book_checkin)(struct book *b);
};

#endif
