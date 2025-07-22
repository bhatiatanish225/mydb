// src/pager.c

#include "pager.h"
#include <stdlib.h>
#include <string.h>

Pager* pager_open(const char* filename) {
    FILE* file = fopen(filename, "r+b");
    if (!file) {
        file = fopen(filename, "w+b");
    }

    fseek(file, 0, SEEK_END);
    uint32_t file_length = ftell(file);

    Pager* pager = (Pager*) malloc(sizeof(Pager));
    pager->file = file;
    pager->file_length = file_length;
    pager->num_pages = file_length / PAGE_SIZE;

    if (file_length % PAGE_SIZE != 0) {
        printf("DB file corrupt. Partial page.\n");
        exit(EXIT_FAILURE);
    }

    for (uint32_t i = 0; i < MAX_PAGES; i++) {
        pager->pages[i] = NULL;
    }

    return pager;
}

void* get_page(Pager* pager, uint32_t page_num) {
    if (page_num > MAX_PAGES) {
        printf("Page number out of bounds.\n");
        exit(EXIT_FAILURE);
    }

    if (pager->pages[page_num] == NULL) {
        void* page = malloc(PAGE_SIZE);

        uint32_t num_pages = pager->file_length / PAGE_SIZE;

        if (page_num < num_pages) {
            fseek(pager->file, page_num * PAGE_SIZE, SEEK_SET);
            fread(page, PAGE_SIZE, 1, pager->file);
        }

        pager->pages[page_num] = page;

        if (page_num >= pager->num_pages) {
            pager->num_pages = page_num + 1;
        }
    }

    return pager->pages[page_num];
}

void pager_flush(Pager* pager, uint32_t page_num) {
    if (pager->pages[page_num] == NULL) {
        printf("No page to flush.\n");
        return;
    }

    fseek(pager->file, page_num * PAGE_SIZE, SEEK_SET);
    fwrite(pager->pages[page_num], PAGE_SIZE, 1, pager->file);
}

void pager_close(Pager* pager) {
    for (uint32_t i = 0; i < pager->num_pages; i++) {
        if (pager->pages[i] != NULL) {
            pager_flush(pager, i);
            free(pager->pages[i]);
        }
    }

    fclose(pager->file);
    free(pager);
}
