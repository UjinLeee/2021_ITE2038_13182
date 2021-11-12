#ifndef DB_FILE_H_
#define DB_FILE_H_

#include <stdint.h>
#include <stdio.h>
#define SIZE 4096

typedef uint64_t pagenum_t;

typedef struct page_t
{
    char data[4096];
} page_t;

typedef struct fd_node
{
    int fd ;
    fd_node *n_fd = NULL;
} fd_node;

typedef struct in_memory_page
{
    // in memory page structure
    union
    {

        struct
        {
            //Header Page
            pagenum_t freepage_num;
            pagenum_t num_pages;
            char reserved[4080];

        } HeaderPage;

        struct
        {
            //Free Page
            pagenum_t next_free;
            char reserved[4088];
        } FreePage;

    } page;

} in_page;

// Open existing database file or create one if not existed.
int file_open_database_file(const char *pathname);

// Allocate an on disk page from the free page list
pagenum_t file_alloc_page(int fd);
// Free an on disk page to the free page list
void file_free_page(int fd, pagenum_t pagenum);

//Read an on-disk page into the in-memory page structure(dest)
void file_read_page(int fd, pagenum_t pagenum, page_t *dest);

//Write an in-memory page(src) to the on-disk page
void file_write_page(int fd, pagenum_t pagenum, const page_t *src);

//Close the database file
void file_close_database_file();


#endif  // DB_FILE_H_
