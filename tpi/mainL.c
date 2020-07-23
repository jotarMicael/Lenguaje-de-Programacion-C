

#include <stdio.h>
#include <stdlib.h>
#include "list_t.h"


int main(int argc, char const *argv[])
{
	tpuntero l;
	list_new(&l);
	insert_InList(&l,3.3);
	insert_InList(&l,4.3);
	insert_InList(&l,5.3);
	insert_InList(&l,6.3);
	print_List(l);
	delete_List(&l);

}