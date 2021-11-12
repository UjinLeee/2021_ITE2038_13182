//buffer.h
#include <page.h>

/*
Physical frame
table_id (unique id of a table)
page number page_num
is_dirty
is_pinned
next of LRU
prev of LRU
*/

typedef struct buffer{

	page_t frame;
	int64_t table_id;
	pagenum_t page_num;
	int is_dirty;
	int is_pinned;
	buffer* n_LRU;
	buffer* p_LRU;
}buffer;
