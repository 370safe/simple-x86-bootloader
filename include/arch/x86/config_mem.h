#ifndef _CONFIG_MEM_H
#define _CONFIG_MEM_H

#define DEF_1KB                 1024
#define DEF_1MB                 (1024 * DEF_1KB)
#define SEGMENT_SIZE_16bit_MODE (64 * DEF_1KB)

/**********
 * Boot 0 *
 **********/

/* Code segment (BOOT0_CODE_SEGMENT:BOOT0_CODE_OFFSET) = (0000:7c00) */
/* The code offset is provided by the absolute long jump */
#define BOOT0_CODE_SEGMENT        0x0000

/* Stack segment (BOOT0_STACK_SEGMENT:BOOT0_STACK_BASE_OFFSET) = (0000:8000) --> (0000:7e00) // 512 bytes */
#define BOOT0_STACK_SEGMENT       0x0000
#define BOOT0_STACK_BASE_OFFSET   0x8000

/* Stage 1's location in RAM */
#define BOOT1_CODE_SEGMENT_RM  0x1000
#define BOOT1_START_ADDR_RM    0x0000

#ifdef BOOTLOADER_PROTECTED_MODE_ENABLED
#define BOOT1_START_ADDR_PM    ((BOOT1_CODE_SEGMENT_RM << 4) | BOOT1_START_ADDR_RM)
#endif

/* Stage 1's location on disk */
#define BOOT1_HEAD          0
#define BOOT1_NB_SECTORS    40     // 20kB

/* Data segments */
#define BOOT0_DATA_SEGMENT        0x0000
#define BOOT0_EXTRA_DATA_SEGMENT  BOOT1_CODE_SEGMENT_RM



/**************
 * Bootloader *
 **************/

#ifdef BOOTLOADER_PROTECTED_MODE_ENABLED

#define CODE_BASE_OFFSET     BOOT1_START_ADDR_PM
#define SEGMENT_CODE_LENGTH  SEGMENT_SIZE_16bit_MODE

#define DATA_BASE_OFFSET     (CODE_BASE_OFFSET + SEGMENT_SIZE_16bit_MODE)
#define SEGMENT_DATA_LENGTH  SEGMENT_SIZE_16bit_MODE

#define STACK_BASE_OFFSET    0x9F000

#else // REAL MODE

#define SEGMENT_CODE         BOOT1_CODE_SEGMENT_RM
#define CODE_BASE_OFFSET     BOOT1_START_ADDR_RM
#define SEGMENT_CODE_LENGTH  (SEGMENT_SIZE_16bit_MODE - CODE_BASE_OFFSET)

#define SEGMENT_DATA         0x2000
#define DATA_BASE_OFFSET     0x0000
#define SEGMENT_DATA_LENGTH  (SEGMENT_SIZE_16bit_MODE - DATA_BASE_OFFSET)

#define SEGMENT_EXTRA_DATA     0x3000
#define EXTRA_DATA_BASE_OFFSET 0x0000

/* Stack segment (SEGMENT_STACK:STACK_BASE_OFFSET) = (1000:FFFF) --> (1000:EFFF) */
#define SEGMENT_STACK        SEGMENT_DATA
#define STACK_BASE_OFFSET    0xffff

#endif // REAL MODE

#endif
