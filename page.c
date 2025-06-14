#include "page.h"
#include <stdlib.h>
#include <string.h>

static int page_ensure_capacity(Page *page, size_t min_capacity)
{
    if (min_capacity > page->capacity)
    {
        size_t new_capacity = page->capacity * 2;
        while (new_capacity < min_capacity)
            new_capacity *= 2;
        char *new_data = (char *)realloc(page->data, new_capacity);
        if (!new_data)
            return 0;
        page->data = new_data;
        page->capacity = new_capacity;
    }
    return 1;
}

void page_init(Page *page)
{
    page->capacity = PAGE_INIT_CAPACITY;
    page->size = 0;
    page->data = (char *)malloc(page->capacity);
}

void page_free(Page *page)
{
    free(page->data);
    page->data = NULL;
    page->size = 0;
    page->capacity = 0;
}

void page_set_int(Page *page, size_t offset, int value)
{
    page_set_bytes(page, offset, &value, sizeof(int));
}

int page_get_int(Page *page, size_t offset, int *out_value)
{
    if (offset + sizeof(int) > page->size)
        return PAGE_ERROR_GET_INT;
    memcpy(out_value, page->data + offset, sizeof(int));
    return PAGE_ERROR_NONE;
}

void page_set_bytes(Page *page, size_t offset, const void *src, size_t len)
{
    if (!page_ensure_capacity(page, offset + len))
        return;
    memcpy(page->data + offset, src, len);
    if (offset + len > page->size)
        page->size = offset + len;
}

int page_get_bytes(Page *page, size_t offset, void *dest, size_t len)
{
    if (offset + len > page->size)
        return PAGE_ERROR_GET_BYTES;
    memcpy(dest, page->data + offset, len);
    return PAGE_ERROR_NONE;
}

void page_set_string(Page *page, size_t offset, const char *str)
{
    size_t len = strlen(str) + 1;
    page_set_bytes(page, offset, str, len);
}

int page_get_string(Page *page, size_t offset, char *buf, size_t buflen)
{
    if (offset >= page->size)
        return PAGE_ERROR_GET_STRING;
    strncpy(buf, page->data + offset, buflen - 1);
    buf[buflen - 1] = '\0';
    return PAGE_ERROR_NONE;
}
