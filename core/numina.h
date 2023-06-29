#pragma once

#include <stdint.h>

#define NMN_HEADER_VERSION_1_0_0    1

#define NMN_HEADER_BLOCK_SIZE_512   1
#define NMN_HEADER_BLOCK_SIZE_1024  2
#define NMN_HEADER_BLOCK_SIZE_2048  4
#define NMN_HEADER_BLOCK_SIZE_4096  8
#define NMN_HEADER_BLOCK_SIZE_8192  16

typedef struct nmn_lba_s {
    uint32_t lba_lsb;       // Least significant bytes of LBA48
    uint16_t lba_msb;       // Most significant bytes of LBA48
    uint16_t lba_idx;       // Index for internal use
} __attribute__((packed)) NmnLBA;

typedef struct nmn_header_s {
    uint8_t     version;                // Version of Numina being used
    uint8_t     block_size;             // Size of the block
    uint16_t    reserved_blocks;        // Amount of reserved blocks
    NmnLBA      lba_start;              // LBA of the start of this partition
    NmnLBA      lba_end;                // LBA of the end of this partition
    uint64_t    block_bitmap_count;     // Amount of blocks that contains data block bitmaps
    NmnLBA      root_directory_lba;     // LBA of the Root Directory
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
