#include <stdio.h>
#include <stdlib.h>

#include "list.h"

void printobj(void *obj, void *data)
{
	printf("%s\n", (char *)obj);
}

int main()
{
	list_t list = list_list();

	list_add(&list, (voidptr)"heyo");
	list_add(&list, (voidptr)"how's it going?");
	list_add(&list, (voidptr)"I'm fine, thanks.");

	list_for_each(&list, printobj, NULL);

	char *idx1 = (char *)list_obj_at(&list, 3);
	printf("\n%s\n", idx1);

	list_free(&list);

	return 0;
}
