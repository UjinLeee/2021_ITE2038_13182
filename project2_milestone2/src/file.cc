//file.cc
#include "file.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "stddef.h"

// Open existing database file or create one if it doesn't exist
int64_t file_open_database_file(const char* pathname) { 
	//IF open already opened file,,, error handling
	for (int i = 0; i < size_table_arr; i++){
		if(pathname == table_arr[i].table_name){
			return -1;
		}
	}

	int fd = open(pathname, O_RDWR | O_SYNC);
	if(fd==-1){ //doesn't exist, then create

//update file table
		fd = open(pathname, O_CREAT, S_IRWXU);
		table_arr[size_table_arr].table_name = pathname;
		table_arr[size_table_arr].fd = fd;
		size_table_arr++; 

		//create header page
		
		page_t o_header;
		o_header.free_pgn = 1;//not sure,,,
		o_header.header_pg.num_pg = 2560;
		o_header.header_pg.root_pgn = 0;
		o_header.header_pg.h_reserved = NULL;


	
	}

//open!! 

//return the unique table id 
return 0; }

// Allocate an on-disk page from the free page list
pagenum_t file_alloc_page(int64_t table_id) { return 0; }

// Free an on-disk page to the free page list
void file_free_page(int64_t table_id, pagenum_t pagenum) {}

// Read an on-disk page into the in-memory page structure(dest)
void file_read_page(int64_t table_id, pagenum_t pagenum, page_t* dest) {}

// Write an in-memory page(src) to the on-disk page
void file_write_page(int64_t table_id, pagenum_t pagenum, const page_t* src) {}

// Close the database file
void file_close_database_file() {}

typedef struct table{
	int64_t fd; //this is,,, unique table id,,,
	char* table_name;
}Table;
int size_table_arr=0; // table_arr size...

Table table_arr[20];
