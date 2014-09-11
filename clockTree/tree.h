
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
}

#endif
