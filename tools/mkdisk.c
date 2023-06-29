#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "../core/numina.h"

#define LBA_SIZE_BYTES 512
#define BLOCK_SIZE_LBA(BLOCK_SIZE)                      (BLOCK_SIZE / LBA_SIZE_BYTES)
#define TOTAL_SIZE_LBA(SIZE_BYTES)                      ((uint64_t) SIZE_BYTES / LBA_SIZE_BYTES)
#define TOTAL_SIZE_BLOCKS(SIZE_BYTES, BLOCK_SIZE)       ((SIZE_BYTES / LBA_SIZE_BYTES) / BLOCK_SIZE_LBA(BLOCK_SIZE))
#define DATA_BITMAP_BLOCK_COUNT(SIZE_BYTES, BLOCK_SIZE) ((SIZE_BYTES / BLOCK_SIZE_LBA(BLOCK_SIZE)) / (BLOCK_SIZE_LBA(BLOCK_SIZE) * LBA_SIZE_BYTES))

int main(int argc, char **argv)
{
    if (argc < 4)
    {
        printf("Usage: <filename> <size> <block_size>\n");
        printf("<size> is in bytes and must be a multiple of 512.\n");
        printf("<block_size> is an integer as described in 'numina.h'.");

        return 0;
    }

    char *filename = argv[1];
    char *size_str = argv[2];
    char *block_size_str = argv[3];

    int size = atoi(size_str);
    int block_size = atoi(block_size_str);
    int block_size_bytes = LBA_SIZE_BYTES * block_size;

    uint64_t root_dir_lba = ((DATA_BITMAP_BLOCK_COUNT(size, block_size_bytes) + 1) * block_size) / LBA_SIZE_BYTES;

    NmnHeader header = {
        .version = NMN_HEADER_VERSION_1_0_0,
        .block_size = NMN_HEADER_BLOCK_SIZE_4096,
        .reserved_blocks = 1,
        .lba_start = 0,
        .lba_end = {
            .lba_lsb = TOTAL_SIZE_LBA(size) & 0xFFFFFFFF,
            .lba_msb = (TOTAL_SIZE_LBA(size) >> 32) & 0xFFFF,
            .lba_idx = 0
        },
        .block_bitmap_count = DATA_BITMAP_BLOCK_COUNT(size, block_size_bytes),
        .root_directory_lba = {
            .lba_lsb = root_dir_lba & 0xFFFFFFFF,
            .lba_msb = (root_dir_lba >> 32) & 0xFFFF,
            .lba_idx = 0
        },
    };

    
}
