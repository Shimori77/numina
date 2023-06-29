#pragma once

#include <stdint.h>

#define NMN_HEADER_VERSION_1_0_0    1

#define NMN_HEADER_BLOCK_SIZE_512   1
#define NMN_HEADER_BLOCK_SIZE_1024  2
#define NMN_HEADER_BLOCK_SIZE_2048  3
#define NMN_HEADER_BLOCK_SIZE_4096  4
#define NMN_HEADER_BLOCK_SIZE_8192  5

typedef struct nmn_lba_s {
    uint32_t lba_lsb;       // Least significant bytes of LBA48
    uint16_t lba_msb;       // Most significant bytes of LBA48
    uint16_t lba_idx;       // Index for internal use
} __attribute__((packed)) NmnLBA;

typedef struct nmn_header_s {
    uint8_t     version;
    uint8_t     block_size;
    uint16_t    reserved_blocks;
    NmnLBA      lba_start;
    NmnLBA      lba_end;
    uint64_t    block_bitmap_count;
    NmnLBA      root_directory_lba;
} __attribute__((packed)) NmnHeader;

typedef struct nmn_node_s {
    uint64_t    nid;                // Node ID.
    uint8_t     flags;              // Flags including node type.
    uint32_t    permissions;        // Node permissions.
    
    uint64_t    size;               // Total size in bytes.

    NmnLBA      direct[8];          // LBA for each direct block of storage.
    NmnLBA      indirect[8];        // LBA for each indirect block of storage.

    uint8_t     identifier[64];     // Human readable identifier. Zero terminated.

    uint8_t     reserved[43];       // Reserved for future usage.
} __attribute__((packed)) NmnNode;
