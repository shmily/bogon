
#ifndef __tree_h__
#define __tree_h__

#include <stdio.h>

struct tree {
	struct tree *tail;		/* points to the last element in the list */
	struct tree *next;		/* points to the next element in the list */
	struct tree *prev;		/* points to the prev element in the list */
	struct tree *child;		/* points to the child node */
	struct tree *parent;	/* points to the parent node */

	int nrchild;			/* count of the child */
	int depth;				/* depth */

	void *data;				/* every thing what you want */
};

typedef int (*tree_cb_t)(struct tree *t, void *data);
typedef int (*tree_filter_t)(const char *name);
typedef int (*tree_cmp_t)(struct tree *t, void *data);

struct tree *tree_alloc(void *data, int depth);
void tree_add_child(struct tree *parent, struct tree *child);

#endif
