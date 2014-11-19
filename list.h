#ifndef LIST_H
#define LIST_H

typedef struct node {
	struct node *right;
	void *obj;
} node_t;

typedef struct {
	node_t *head;
} list_t;

typedef void(*ListIter)(void *, void *);
typedef char(*BoolIter)(void *, void *);
typedef void(*FailedNodeFunc)(void *);
typedef void *voidptr;

list_t list_list();
void list_add(list_t *list, void *obj);
void list_remove_obj(list_t *list, void *obj);
int list_index_of(list_t *list, void *obj);
void list_remove_idx(list_t *list, int idx);
void *list_obj_at(list_t *list, int idx);
void list_for_each(list_t *list, ListIter iter, void *data);
void list_for_each_bool(list_t *list, BoolIter iter, voidptr data, FailedNodeFunc failed);
int list_count(list_t *list);
void list_free(list_t *list);

#endif