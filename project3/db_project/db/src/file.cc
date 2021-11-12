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
		fd = open(pathname, O_CREAT, S_IRWXU); //create
		table_arr[size_table_arr].table_name = pathname;
		table_arr[size_table_arr].table_id = fd;
		size_table_arr++; 

		//create header page
		
		page_t o_header;
		o_header.free_pgn = 1;//not sure,,,
		o_header.header_pg.num_pg = 2560;
		o_header.header_pg.root_pgn = 0;
		o_header.header_pg.h_reserved = NULL;

		pwrite(fd, &o_header.free_pgn, 8, 0);
		sync();
		pwrite(fd, &o_header.header_pg.num_pg,8,8);
		sync();
		pwrite(fd, &o_header.header_pg.root_pgn,8,16);
		sync();
//		pwrite(fd, &o_header.header_pg.h_reserved,4072, 24);
//		sync();

		for(int i = 1; i < 2559; i++){

			page_t free_page;
			free_page.next_free_pgn = i+1;
			pwrite(fd, &free_page.next_free_pgn, 8, SIZE*i);
			sync();

		}

		return table_arr[size_table_arr].table_id;
	
	}else{ //When the file exist, open and update the file table
		if(size_table_arr == 20){
			printf("Error,,,The size of tables is more than 20\n");
			return -1;
		}else{
			table_arr[size_table_arr].table_name = pathname;
			table_arr[size_table_arr].table_id = fd;
			size_table_arr++;
			return table_arr[size_table_arr].table_id;
		} 
	}
 }

// Allocate an on-disk page from the free page list
pagenum_t file_alloc_page(int64_t table_id) { 

	char pgn_buf[8];
	pagenum_t free_pgn;
	pread(fd, pgn_buf, 8, 0);

	free_pgn = atio(pgn_buf);

	char num_pg_buf[8];
	pagenum_t num;
	pread(fd, num_pg_buf, 8, 8);
	num_pg = atoi(num_pg_buf);

	if(free_pgn == 0){ //no free page
		
		for(int i = num; i < 2*num-1; i++){
			page_t temp_free;
			temp_free.next_free_pgn = i+1;
			pwrite(fd, &temp_free.next_free_pgn, 8, SIZE*i);
			sync();
		}
		page_t last_free;
		last_free.next_free_pgn = 0;
		pwrite(fd, &last_free.next_free_pgn, 8, SIZE*(2*num-1));
		sync();

		free_pgn = num+1;
		num = 2*num;
		char arr[8];
		memcpy(arr, &free_pgn, sizeof(pagenum_t));
		pwrite(fd, arr, 8, 0);
		sync();

		char num_arr[8];
		memcpy(num_arr, &num, sizeof(pagenum_t));
		pwrite(fd, num_arr, 8, 8);
		sync();

		return (free_pgn - 1);

	}else{ //There is free page
		
		page_t tmp_free;
		char n_freepg_buffer[8];
		pread(fd, n_freepg_buffer, 8, free_pgn*SIZE);

		pagenum_t new_free = atoi(n_freepg_buffer);

		char arr_n[8];
		memcpy(arr_n, &new_free, sizeof(pagenum_t));
		pwrite(fd, arr_n, 8, 0);
		sync();
		return free_pgn;


	}
}

// Free an on-disk page to the free page list
void file_free_page(int64_t table_id, pagenum_t pagenum) {
	
	int fd = table_id;

	char free_arr[8];
	pread(fd, free_arr, 8, 0);
	pagenum_t free_pgn = atoi(free_arr);

	page_t pagenum_page;
	pagenum_page.next_free_pgn = free_pgn;
	pwrite(fd, pagenum_page.next_free_pgn, 8, SIZE*pagenum);
	sync();

	page_t tmp_header;
	tmp_header.free_pgn = pagenum;
	pwrite(fd, tmp_header.free_pgn, 8, 0);
	sync();

	return;
}

// Read an on-disk page into the in-memory page structure(dest)
void file_read_page(int64_t table_id, pagenum_t pagenum, page_t* dest) {

	int fd = table_id;

	int x;
	
	if((x = pread(fd, dest, SIZE, SIZE*pagenum)==-1){

		printf("Error: File_read_page error\n");
		return;
	}
	printf("file_read_page success,,,\n");
	return;
}

// Write an in-memory page(src) to the on-disk page
void file_write_page(int64_t table_id, pagenum_t pagenum, const page_t* src) {

	int64_t fd = table_id;

	int y = pwrite(fd, src, SIZE, SIZE*pagenum);
	if(y == -1){
		printf("Error: file_write_page error\n");
		return;
	}else{
		printf("Success: file_write_page success\n");
		return;
	}
}

// Close the database file
void file_close_database_file() {
	int64_t  fd;
	for(int i = 0; i < size_table_arr; i++){
		fd = table_arr[i].table_id;
		close(fd);
	}
	return;
}

typedef struct table{
	int64_t table_id; //this is,,, unique table id,,,
	char* table_name;
}Table;
int size_table_arr=0; // table_arr size...

Table table_arr[20];
