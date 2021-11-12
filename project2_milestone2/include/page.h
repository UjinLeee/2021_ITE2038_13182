//page.h
#include <stdint.h>
#define SIZE 4096
typedef uint64_t pagenum_t

#pragma pack(push, 1)

typedef struct page_t{

	//0-7
	union{
		pagenum_t free_pgn; //header page
		pagenum_t next_free_pgn; //free page
		pagenum_t parent_pgn; //page header(internal or leaf)
	}
	//8-4096
	union{

		char not_used[4088];//free page

		typedef struct header_pg{
			pagenum_t num_pg; //8-15
			pagenum_t root_pgn; //16-23
			char h_reserved[4072];//24-4096
		}header_pg;

		typedef struct pg_header{ //leaf & internal
			uint32_t is_leaf; // 8-11 & 4 byte
			uint32_t num_keys; //12-15

			union{
			 	typedef struct leaf{

					char l_reserved[96];
					pagenum_t amount_free;//112-120
					pagenum_t r_pgn; //120-128
					//remain,,, how??
					union{

						slot s_arr[64];
						char value[3968];
					}
				}leaf;

				typedef struct internal{
					
					char in_reserved[104];
					pagenum_t one_pgn; //120-128
					pair entry[248];
				}internal;
			}//leaf & internal 16-4096
		}pg_header;
	}
}page_t;

typedef struct pair{
	pagenum_t key;
	pagenum_t pgnum;
}pair;

typedef struct slot{
	pagenum_t key;
	uint16_t size; //2byte
	uint16_t offset;
}slot;
#pragma pack(pop)
