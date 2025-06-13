#ifndef block_id_h__
#define block_id_h__

typedef struct {
  char *filename;
  int blknum;
} BlockID;

int block_id_equals(BlockID *x, BlockID *y);

#endif
