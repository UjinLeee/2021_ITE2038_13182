#include "file.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "stddef.h"


//fd_node *head = new fd_node(); // 일단 이렇게,,,근데 여기서 동적할당을 해도 되는것인지,,,ㅋㅋㅋㅋ
fd_node *head; //일단 선언만 해놓자.

//Open existing database file or create one if not existed.
/*int file_open_database_file(const char *pathname)
{
    int fd = open(pathname, O_RDWR | O_SYNC); // 왜이러지,,,?
    if (fd == -1)
    { //If there is no file, create a file.
        fd = open(pathname, O_CREAT, S_IRWXU);
        

       fd_node *new_fd;
       new_fd->fd = fd;
       new_fd->n_fd = head;
       head->n_fd = new_fd;

        //Create Header Page
        in_page o_header;
        o_header.page.HeaderPage.num_pages = 2560;
        o_header.page.HeaderPage.freepage_num = 1;
        *o_header.page.HeaderPage.reserved = '\0';
      
        //write 해주기
        
            pwrite(fd, &o_header.page.HeaderPage.num_pages, 8,0);
            sync();
            pwrite(fd, &o_header.page.HeaderPage.num_pages, 8,8);
            sync();
            pwrite(fd, &o_header.page.HeaderPage.reserved, 4080,16);
            sync();
            

        //Create free page
        int i = 1;

        for (i = 1; i < 2559; i++)
        {
            in_page o_free;
            o_free.page.FreePage.next_free = i + 1;
            *o_free.page.FreePage.reserved = '\0';
            //write 해주기
            pwrite(fd, &o_free.page.FreePage.next_free, 8, SIZE*i);
            sync();
            pwrite(fd, &o_free.page.FreePage.reserved, 4088, SIZE*i + 8);
            sync();
        }

        //2559번째 free page 만들기
        in_page last_free;
        last_free.page.FreePage.next_free = 0;
        *last_free.page.FreePage.reserved = '\0';
        //write 해주기
        pwrite(fd, &last_free.page.FreePage.next_free, 8, SIZE*i);
        sync();
        pwrite(fd, &last_free.page.FreePage.reserved, 4088, SIZE*i + 8);
        sync();

        
       
        return fd;

    }
    else
    {
        
       fd_node *new_fd;
       new_fd->fd = fd;
       new_fd->n_fd = head;
       head->n_fd = new_fd;
       
        return fd;
    }
}*/


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


//Allocate an on-disk page from the free page list
pagenum_t file_alloc_page(int fd)
{
    //read header

    char free_pgn[8];
    pread(fd, free_pgn, 8, 0);

    pagenum_t n = atoi(free_pgn);//헤더가 가리키는 free page

    char num_pg[8];
    pread(fd, num_pg, 8, 8);

     pagenum_t num = atoi(num_pg);//페이지수

    if (n == 0)
    {
        //There is no free page.

      //페이지수

        for (int i = num; i < 2 * num - 1; i++)
        {
            in_page temp_free;
            temp_free.page.FreePage.next_free = i + 1;
            *temp_free.page.FreePage.reserved = '\0';
            pwrite(fd, &temp_free.page.FreePage.next_free, 8, SIZE*i);
            sync();
            pwrite(fd, &temp_free.page.FreePage.reserved, 4088, SIZE*i + 8);
            sync();
        } //free page list 만들어주기

        //마지막 free page는 0 가리켜야 한다.
        in_page temp_free;
        temp_free.page.FreePage.next_free = 0;
        *temp_free.page.FreePage.reserved = '\0';
      
        pwrite(fd, &temp_free.page.FreePage.next_free, 8, SIZE*(2*num-1));
        sync();
        pwrite(fd, &temp_free.page.FreePage.reserved, 4088, SIZE*(2*num-1) + 8);
        sync();

        n = num+1;
        num = 2 * num;
        char arr[8];
        memcpy(arr, &n, sizeof(pagenum_t));
        //char arr[8] = n;
        pwrite(fd, arr, 8,0);
        sync();
        //char num_arr[8] = num;
        char num_arr[8];
        memcpy(num_arr, &num, sizeof(pagenum_t));
        pwrite(fd, num_arr, 8,8);
        sync();

        return (n-1);
    }
    else
    {
        //There is free page.
        in_page temp_free; // pagenum이 n인 free page
        char tmp_z[8];
        pread(fd, tmp_z, 8, n*SIZE); //pagenum이 n인 free page의 next free page

        pagenum_t new_free = atoi(tmp_z); 
        //header가 가리키는 free page 바꿔주기.
        //char arr_n[8] = n;
        char arr_n[8];
        memcpy(arr_n,&new_free,sizeof(pagenum_t));
        pwrite(fd, arr_n, 8, 0);
        sync();
        return n;
    }
}

//Free an on-disk page to the free page list
void file_free_page(int fd, pagenum_t pagenum)
{
    char free_arr[8]; 
    pread(fd, free_arr, 8,0); 
    pagenum_t free_pgn = atoi(free_arr); //헤더가 가리키는 free page number

    //1. pagenum의 next free를 free_pgn으로 바꾸고 write해주기
    in_page temp_pagenum;
    temp_pagenum.page.FreePage.next_free = free_pgn;
    *temp_pagenum.page.FreePage.reserved = '\0';
    pwrite(fd, &temp_pagenum.page.FreePage.next_free, 8, SIZE*pagenum);
    sync();
    pwrite(fd, &temp_pagenum.page.FreePage.reserved, 4088, SIZE*pagenum + 8);
    sync();

    //2. header의 next free를 pagenum으로 바꾸고 write해주기
    in_page tmp_header;
    tmp_header.page.HeaderPage.freepage_num = pagenum;
    pwrite(fd, &tmp_header.page.HeaderPage.freepage_num, 8, 0);
    sync();
    return;
}

//Read an on-disk page into the in-memory page structure(dest)
void file_read_page(int fd, pagenum_t pagenum, page_t *dest)
{
    int x;

    if((x=pread(fd, dest, SIZE, SIZE*pagenum))==-1){
        printf("File_read_page Error\n");
        return;
    }
    printf("File_read_page success\n");
    return;
}

//Write an in-memory page(src) to the on-disk page
void file_write_page(int fd, pagenum_t pagenum, const page_t *src)
{

    /*
        src에 있는 정보를 pagenum에 있는 파일에 적기. 
    */
    int y;

    if((y=pwrite(fd, src,SIZE,SIZE*pagenum))==-1){
        printf("file_write_page error\n");
        return;
    }else{
        printf("file_write_page success\n");
    return;
    }
}

//Close the database file -> fd가 여러개이기 때문에.
void file_close_database_file()
{ //node 닫아주고 free까지 해주어야 한다.

    fd_node * temp;
    while(head->n_fd != NULL){
        close(head->fd);
        temp = head->n_fd;
        free(head);
        head=temp;
    }
    close(head->fd);
    free(head);
    return;
}
