
#include <stdlib.h>
#include <stdio.h>

struct list {
	struct list *next;
	int data;
};

struct list *list_alloc(void)
{
	struct list *l;

	l = malloc(sizeof(*l));
	if (!l) {
		printf("list_alloc failed\n");
		return NULL;
	}

	l->next = NULL;
	return l;
}

void list_dump(struct list *list)
{
	while(list) {
		printf("%d -> ", list->data);
		list = list->next;
	}

	printf("\n");
}

int main(void)
{
	int len;	/* the length of the list */
	int k;		/* the point to reverse */

	struct list head;
	struct list *tail, *new;
	struct list *p1, *p2;
	struct list *rever, *next, *tmp;

	scanf("%d %d", &len, &k);

	tail = &head;
	for (int i=0; i<len; i++) {
		new = list_alloc();
		new->data = i;
		tail->next = new;
		tail = new;
	}
	list_dump(head.next);

	/* reverse the first part */
	rever = NULL;
	next = head.next;
	tmp = head.next; 	/* incase for k = 0 */
	for (int i=0; i<k; i++) {
		tmp = next->next;
		next->next = rever;
		rever = next;
		next = tmp;
	}

	p1 = rever;
	list_dump(p1);

	/* reverse the second part */
	rever = NULL;
	next = tmp;
	while (next) {
		tmp = next->next;
		next->next = rever;
		rever = next;
		next = tmp;
	}

	p2 = rever;
	list_dump(p2);

	/* together */
	head.next->next = p2;
	head.next = p1;

	list_dump(head.next);
	return 0;
}
