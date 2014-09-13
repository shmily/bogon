
#include "tree.h"
#include "logger.h"
#include <stdlib.h>
#include <memory.h>

/*
 * Allocate a new tree structure and initialize.
 */
struct tree *tree_alloc(void *data, int depth)
{
	struct tree *t;

	t = malloc(sizeof(*t));
	if (!t) {
		log_err("fail to alloc memory.");
		return NULL;
	}

	/* store the user data */
	t->data = data;

	t->depth = depth;
	t->tail = t;
	t->next = NULL;
	t->prev = NULL;
	t->child = NULL;
	t->parent = NULL;
	t->nrchild = 0;

	return t;
}

/*
 * Free a tree structure.
 */
void tree_free(struct tree *t)
{
	free(t);
}

/*
 * Add at the end of the list.
 */
void tree_add_tail(struct tree *head, struct tree *new)
{
	new->prev = head->tail;
	head->tail->next = new;
	head->tail = new;
}

/*
 * Add a child in to a parent list.
 */
void tree_add_child(struct tree *parent, struct tree *child)
{
	child->parent = parent;

	if (parent->child)
		return tree_add_tail(parent->child, child);

	parent->child = child;
}

/*
 * Go over the tree, callback at each node.
 */
int tree_for_each(struct tree *tree, tree_cb_t cb, void *data)
{
	if (!tree)
		return 0;

	if (cb(tree, data))
		return -1;

	if (tree_for_each(tree->child, cb, data))
		return -1;

	return tree_for_each(tree->next, cb, data);
}

/*
 * Go over the tree at the reverse order, callback at each node.
 */

int tree_for_each_reverse(struct tree *tree, tree_cb_t cb, void *data)
{
	if (!tree)
		return 0;

	if (cb(tree, data))
		return -1;

	if (tree_for_each_reverse(tree->prev, cb, data))
		return -1;

	return tree_for_each_reverse(tree->parent, cb, data);
}

/*
 * Go over all the parent of the specified node.
 */
int tree_for_each_parent(struct tree *tree, tree_cb_t cb, void *data)
{
	if (!tree)
		return 0;

	if (tree_for_each_parent(tree->parent, cb, data))
		return -1;

	return cb(tree, data);
}

/*
 * find the node match with the input param.
 * @ cmp : the user define match founction
 * @ data : the input param
 */
struct tree *tree_find(struct tree *tree, tree_cmp_t cmp, void *data)
{
	struct tree *t;

	if (!tree)
		return NULL;

	if (!cmp(tree, data))
		return tree;

	t = tree_find(tree->child, cmp, data);
	if (t)
		return t;

	return tree_find(tree->next, cmp, data);
}


