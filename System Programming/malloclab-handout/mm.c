/*
 * mm-naive.c - The fastest, least memory-efficient malloc package.
 *
 * In this naive approach, a block is allocated by simply incrementing
 * the brk pointer.  A block is pure payload. There are no headers or
 * footers.  Blocks are never coalesced or reused. Realloc is
 * implemented directly using mm_malloc and mm_free.
 *
 * NOTE TO STUDENTS: Replace this header comment with your own header
 * comment that gives a high level description of your solution.
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>

#include "mm.h"
#include "memlib.h"

/*********************************************************
 * NOTE TO STUDENTS: Before you do anything else, please
 * provide your team information in the following struct.
 ********************************************************/

/*

JEONWOONGBAE 20161248
wbjeon2k@gmail.com

*/



/* text book basic macros*/
#define ALIGNMENT 8
#define WSIZE 4
#define DSIZE 8
#define CHUNKSIZE (1<<10)
#define LISTSIZE 20

#define MAX(x,y) ( (x) > (y) ? (x) : (y) )
#define MIN(x,y) ( (x) > (y) ? (y) : (x))

#define PACK(size, alloc) ((size) | (alloc))

#define GET(p) (*(unsigned int*)(p))
#define PUT(p,val) (*(unsigned int*)(p)=val)

#define GET_SIZE(p) (GET(p) & ~0x7)
#define GET_ALLOC(p) (GET(p) & 0x1)

#define HDRP(bp) ((char*)(bp) - (WSIZE))
#define FTRP(bp) ((char*)(bp) + GET_SIZE(HDRP(bp)) - (DSIZE))

#define NEXT_BLKP(bp) ((char*)(bp) + GET_SIZE((char*)(bp) -WSIZE))
#define PREV_BLKP(bp) ((char*)(bp) - GET_SIZE((char*)(bp) -DSIZE))

#define ALIGN(size) (((size) + (ALIGNMENT-1)) & ~0x7)
#define SIZE_T_SIZE (ALIGN(sizeof(size_t)))

/* macros for segregated list*/

/*
seglist node structure:
    HEADER
    PREV_PTR
    SUCC_PTR

    MEMORY CONTENTS
    FOOTER
*/

#define SEG_PREV_PTR(ptr) ((char*)(ptr) + WSIZE)
#define SEG_SUCC_PTR(ptr) ((char*)(ptr) + DSIZE)

#define SEG_PREV(ptr) (*(char**)(ptr))
#define SEG_SUCC(ptr) (*(char**)(SEG_SUCC_PTR(ptr)))

#define SET_PTR(p,ptr) (*(unsigned int*)(p) = (unsigned int)(ptr))


team_t team = {
    /* Team name */
    "ateam",
    /* First member's full name */
    "Harry Bovik",
    /* First member's email address */
    "bovik@cs.cmu.edu",
};


static void *extend_heap(size_t words);
static void *place(void *bp, size_t asize);
//static void *find_fit(size_t asize);
static void *coalesce(void *bp);
static size_t seg_index(size_t bsize);
static void deleteNode(void* bp);
static void insertNode(void* bp, size_t asize);


static void* seglist[LISTSIZE];

/*
 * mm_init - initialize the malloc package.
 */

static size_t seg_index(size_t bsize){
    size_t idx = 0;

    while(bsize > 1){
        ++idx;
        bsize = bsize/2 ;
    }

    if(idx < LISTSIZE){ return idx; }
    else{ return LISTSIZE-1; }
}


/*
Insert node with the ascending order of block size.
If the order is not ascending, it is vulnerable to external fragmentation,
because the largest block in the seglist will almost always allocated first,
and rest of the unused free memory is pushed into different sector of seglist
*/
static void insertNode(void* bp, size_t asize){

    //printf("start insertNode\n");

    size_t idx = 0;
    idx = seg_index( asize );

    void* searchPoint;
    searchPoint = seglist[idx];

    if(searchPoint == NULL)/*if head node*/{
        SET_PTR(SEG_PREV_PTR(bp), NULL);
        SET_PTR(SEG_SUCC_PTR(bp), NULL);
        seglist[idx] = bp;
    }
    else{
        //if searchpoint is at the end of seglist
        SET_PTR(SEG_PREV_PTR(bp), NULL);
        SET_PTR(SEG_SUCC_PTR(bp), searchPoint);
        SET_PTR(SEG_PREV_PTR(searchPoint), bp);
        seglist[idx] = bp;
    }

    //printf("end insertNode\n");
}

/*ordinary double-linked linked list (Same as in Data structure course)*/
static void deleteNode(void* bp){

    //printf("start delete node\n");

    int iter, idx;
    size_t bsize = GET_SIZE(bp);
    idx = seg_index(bsize);

    if(SEG_PREV(bp) == NULL){
        if(SEG_SUCC(bp) == NULL){
            //remove the only node and empty the seglist
            //printf("P1\n");
            seglist[idx] = NULL;
        }
        else{
            //printf("P2\n");
            SET_PTR(SEG_PREV_PTR(SEG_SUCC(bp)) , NULL);
            seglist[idx] = SEG_SUCC_PTR(bp);
            //seglist[idx] = SEG_SUCC(bp);
        }
    }
    else{
        if(SEG_SUCC(bp) == NULL){
            //printf("P3\n");
            //end of the seglist
            SET_PTR(SEG_SUCC_PTR(SEG_PREV(bp)), NULL);
        }
        else{
            //printf("P4\n");
            //link out current node by
            //linking the  previous node and the succeeding node
            SET_PTR(SEG_SUCC_PTR(SEG_PREV(bp)), SEG_SUCC(bp));
            SET_PTR(SEG_PREV_PTR(SEG_SUCC(bp)), SEG_PREV(bp));
        }
    }

    SET_PTR(SEG_PREV_PTR(bp) , NULL);
    SET_PTR(SEG_SUCC_PTR(bp) , NULL);

    //printf("end delete node\n");
}

/*4 cases of coalesce situations are described in textbook*/
static void* coalesce(void* bp){

    //printf("start coalesce\n");
    size_t prev_alloc = GET_ALLOC(HDRP(PREV_BLKP(bp)));
    size_t next_alloc = GET_ALLOC(HDRP(NEXT_BLKP(bp)));
    size_t size = GET_SIZE(HDRP(bp));

    //if both blocks are allocated
    if(prev_alloc && next_alloc) {
        //insertNode(bp, size);
        return bp;
    }

    else if (prev_alloc && !next_alloc){
        deleteNode(bp);
        deleteNode(NEXT_BLKP(bp));
        size += GET_SIZE(HDRP(NEXT_BLKP(bp)));

        PUT(HDRP(bp) , PACK(size,0));
        PUT(FTRP(bp) , PACK(size,0));
    }

    else if(!prev_alloc && next_alloc){
        deleteNode(bp);
        deleteNode(PREV_BLKP(bp));
        size += GET_SIZE(HDRP(PREV_BLKP(bp)));

        PUT(FTRP(bp), PACK(size,0));
        PUT(HDRP(PREV_BLKP(bp)), PACK(size,0));
        bp = PREV_BLKP(bp);
    }

    else{
        deleteNode(bp);
        deleteNode(PREV_BLKP(bp));
        deleteNode(NEXT_BLKP(bp));

        size += GET_SIZE(HDRP(PREV_BLKP(bp))) + GET_SIZE(HDRP(NEXT_BLKP(bp)));

        PUT(HDRP(PREV_BLKP(bp)), PACK(size,0));
        PUT(FTRP(NEXT_BLKP(bp)) , PACK(size,0));
        bp = PREV_BLKP(bp);
    }
    insertNode(bp, size);

    //printf("end coalesce\n");
    return bp;

}

//initialize memory
int mm_init(void)
{
    //printf("start mm_init\n");
    size_t i=0;
    char* heap_startp;

    //printf("start seglist init\n");

    for (i = 0; i < LISTSIZE; ++i) {
        seglist[i] = NULL;
    }

    //printf("end seglist init\n");

    if((long)(heap_startp = mem_sbrk(4*WSIZE)) == -1) return -1;

    PUT(heap_startp , 0);
    PUT(heap_startp + (WSIZE), PACK(DSIZE,1));
    PUT(heap_startp + (2*WSIZE) , PACK(DSIZE,1));
    PUT(heap_startp + (3*WSIZE) , PACK(0,1));

    //initialize seglist
    //printf("end heap memory init\n");

    if(extend_heap(CHUNKSIZE) == NULL){
        //printf("not enough memory in heap\n");
        return -1;
    }

    //printf("end mm_init\n");
    //printf("enough memory in heap\n");

    return 0;
}

static void* extend_heap(size_t words){

    //printf("start extend heap\n");

    void* bp;
    size_t size;

    size = ALIGN(words) ;
    if((bp = mem_sbrk(size)) == (void*)-1) return NULL;

    PUT(HDRP(bp), PACK(size,0));
    PUT(FTRP(bp), PACK(size,0));
    PUT(HDRP(NEXT_BLKP(bp)), PACK(0,1));

    insertNode(bp, size);

    //printf("call coalesce\n");
    return coalesce(bp);

}

/*
 * mm_malloc - Allocate a block by incrementing the brk pointer.
 *     Always allocate a block whose size is a multiple of the alignment.
 */
void *mm_malloc(size_t size)
{
    //printf("mm_malloc called\n");
    size_t asize ,extendsize , idx;
    void* bp = NULL;

    if(size==0) return NULL;

    if(size <= DSIZE) { asize = 2*DSIZE; }
    else { asize = ALIGN(size + DSIZE); }

    idx = seg_index(asize);

    bp = seglist[idx];
    //find free block which its size is equal or larger than target size
    while ((bp != NULL) && (asize > GET_SIZE(HDRP(bp))) ){
        bp = SEG_SUCC(bp);
    }

    //printf("out of while loop\n");

    //if there is no such free block
    if(bp == NULL){
        extendsize = MAX(asize, MIN(mem_heapsize(), CHUNKSIZE));
        //if there is no heap memory available
        if((bp = extend_heap(extendsize)) == NULL) { return NULL; }
    }

    bp = place(bp,asize);

    //printf("passed place\n");
    //printf("end mm_malloc\n");
    return bp;

}

//naive place as described in textbook
static void* place(void* bp, size_t asize){
    //asize = ALIGN(asize);
    size_t size = GET_SIZE(HDRP(bp));
    size_t fragment = size - asize;

    //printf("start place\n");

    deleteNode(bp);

    if (fragment < 2*DSIZE) {
        // Do not split block
        PUT(HDRP(bp), PACK(size, 1));
        PUT(FTRP(bp), PACK(size, 1));
    }
    else {
        // Split block
        //as described in textbook p.920
        PUT(HDRP(bp), PACK(asize, 1));
        PUT(FTRP(bp), PACK(asize, 1));

        PUT(HDRP(NEXT_BLKP(bp)), PACK(fragment, 0));
        PUT(FTRP(NEXT_BLKP(bp)), PACK(fragment, 0));
        insertNode(NEXT_BLKP(bp), fragment);
        //bp = NEXT_BLKP(bp);
    }

    //printf("end place\n");
    return bp;
}

/*
 * mm_free - Freeing a block
 */
void mm_free(void *bp){
    //printf("start free\n");

    if(bp == NULL) return;

    size_t size = GET_SIZE(HDRP(bp));

    PUT(HDRP(bp), PACK(size,0));
    PUT(FTRP(bp), PACK(size,0));

    insertNode(bp,size);
    coalesce(bp);
    //printf("end free\n");
}

/*
 * mm_realloc - Implemented simply in terms of mm_malloc and mm_free
 */
void *mm_realloc(void *oldptr, size_t size)
{
    void *newptr;
    size_t csize;
    //printf("start realloc\n");
    if(oldptr == NULL) { return mm_malloc(size); }

    if(size==0) {mm_free(oldptr) ; return NULL;}

    csize = GET_SIZE(HDRP(oldptr));
    if(csize <= DSIZE) { csize = 2*DSIZE; }
    else { csize = ALIGN(size + DSIZE); }



    newptr = mm_malloc(csize);

    if (newptr == NULL) { return NULL; }

    memcpy(newptr, oldptr, (csize > size ? size : csize));

    //printf("free old ptr\n");
    mm_free(oldptr);
    //printf("end realloc\n");
    return newptr;

}

