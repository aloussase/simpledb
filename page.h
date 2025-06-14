#ifndef page_h__
#define page_h__

#include <stddef.h>

#define PAGE_INIT_CAPACITY 4096

typedef struct
{
    char *data;
    size_t size;
    size_t capacity;
} Page;

void page_init(Page *page);
void page_free(Page *page);

void page_set_int(Page *page, size_t offset, int value);
int page_get_int(Page *page, size_t offset);

void page_set_bytes(Page *page, size_t offset, const void *src, size_t len);
void page_get_bytes(Page *page, size_t offset, void *dest, size_t len);

void page_set_string(Page *page, size_t offset, const char *str);
void page_get_string(Page *page, size_t offset, char *buf, size_t buflen);

#endif
