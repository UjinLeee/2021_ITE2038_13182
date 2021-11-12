//bpt.cc
#include <stdlib.h>
#include <stdio.h>
#include "page.h"
#include "buffer.h"

buffer* buf_arr;
int num_buf;

int init_db(int n){

	num_buf = n;
	if((buf_arr = (buffer*)malloc(sizeof(buffer)*num_buf))==NULL){
	printf("Init_db error: Insufficient memory");
	return -1;
	};

	for(int i = 0; i < num_buf; i++){
		buf_arr[i].frame = null;
		buf_arr[i].table_id = 0;
		buf_arr[i].page_num = -1;
		buf_arr[i].is_dirty = 0;
		buf_arr[i].is_pinned = 0;
		if(i == num_buf-1){
			buf_arr[i].p_LRU = buf_arr[i-1];
			buf_arr[i].n_LRU = buf_arr[0];
		}else if(i == 0){
			buf_arr[i].p_LRU = buf_arr[num_buf-1];
			buf_arr[i].n_LRU = buf_arr[i+1];
		}else{
			buf_arr[i].p_LRU = buf_arr[i-1];
			buf_arr[i].n_LRU = buff_arr[i+1];
		}
	}
	
	return 0;//on success

}

int shutdown_db(){
	
	for(int i = 0; i < num_buf; i++){
	
		//check dirty
		if(buf_arr[i].is_dirty == 1){
			//change !!

		}
	}

	free(buf_arr);
}
