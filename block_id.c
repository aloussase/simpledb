#include <string.h>

#include "block_id.h"

int block_id_equals(BlockID *x, BlockID *y)
{
  return strcmp(x->filename, y->filename) == 0 && x->blknum == y->blknum;
}
