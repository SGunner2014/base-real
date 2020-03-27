typedef struct {
    uint32_t entries[1024];
} page_table_t;

typedef struct {
    page_table_t tables[1024];
} page_directory_t;

void setup_paging();