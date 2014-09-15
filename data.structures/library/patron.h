
#ifndef __patron_h__
#define __patron_h__

#include "config.h"
#include "book.h"
#include "list.h"

struct patron_ops_t;

struct loan_book_t {
	struct book *book;
	struct list_head list;
};

struct patron {
	char name[MAX_NAME_LEN];
	struct list_head loan_book_list;

	struct patron_ops_t *ops;

	/* link to the next/prev patron */
	struct list_head list;
};

struct patron_ops_t {
	int (*checkout)(struct book *b);
	int (*checkin)(struct book *b);
};

struct patron *patron_alloc(const char *name);
void patron_free(struct patron *p);
void patron_add(struct list_head *head, struct patron *new);
void patron_del(struct patron *del);

#endif
