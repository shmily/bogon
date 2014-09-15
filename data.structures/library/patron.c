
#include <stdlib.h>
#include <string.h>
#include <memory.h>

#include "patron.h"


static int _checkout(struct book *b);
static int _checkin(struct book *b);

static struct patron_ops_t patron_ops = {
	.checkout = _checkout,
	.checkin  = _checkin
};

/*
 * create a new patron
 */
struct patron *patron_alloc(const char *name)
{
	struct patron *new;

	new = malloc(sizeof(*new));
	if (!new)
		return NULL;

	strcpy(new->name, name);

	INIT_LIST_HEAD(&new->loan_book_list);

	new->ops = &patron_ops;

	return new;
}

/*
 * free a patron
 */
void patron_free(struct patron *p)
{
	free(p);
}

/*
 * add a patron to the list
 */
void patron_add(struct list_head *head, struct patron *new)
{
	list_add(&new->list, head);
}

/*
 * del a patron from list
 */
void patron_del(struct patron *del);
{
	list_del(&del->list);
}

