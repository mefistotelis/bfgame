/******************************************************************************/
// Bullfrog Engine Emulation Library - for use to remake classic games like
// Syndicate Wars, Magic Carpet or Dungeon Keeper.
/******************************************************************************/
/** @file bflib_memory.h
 *     Header file for bflib_memory.c.
 * @par Purpose:
 *     Memory managing routines.
 * @par Comment:
 *     Just a header file - #defines, typedefs, function prototypes etc.
 * @author   Tomasz Lis
 * @date     10 Feb 2008 - 30 Dec 2008
 * @par  Copying and copyrights:
 *     This program is free software; you can redistribute it and/or modify
 *     it under the terms of the GNU General Public License as published by
 *     the Free Software Foundation; either version 2 of the License, or
 *     (at your option) any later version.
 */
/******************************************************************************/
#ifndef BFLIB_MEMORY_H
#define BFLIB_MEMORY_H

#include "bflib_basics.h"

#ifdef __cplusplus
extern "C" {
#endif
/******************************************************************************/
typedef unsigned char * MemAllocFunc(ulong);
/******************************************************************************/
extern char lbEmptyString[];
/******************************************************************************/
short update_memory_constraits(void);
void * LbMemorySet(void *dst, uchar c, ulong length);
void * LbMemoryCopy(void *in_dst, const void *in_src, ulong len);
TbResult LbMemorySetup();
TbResult LbMemoryReset(void);
TbResult  LbMemoryCheck(void);
unsigned char * LbMemoryAllocLow(ulong size);
unsigned char * LbMemoryAlloc(ulong size);
TbResult LbMemoryFree(void *mem_ptr);
TbResult LbMemoryGrow(void **ptr, unsigned long size);
TbResult LbMemoryShrink(void **ptr, unsigned long size);
int LbMemoryCompare(void *ptr1, void *ptr2, unsigned long size);
void * LbStringCopy(char *dst, const char *src, const ulong dst_buflen);
void * LbStringConcat(char *dst, const char *src, const ulong dst_buflen);
ulong LbStringLength(const char *str);
void * LbStringToLowerCopy(char *dst, const char *src, const ulong dst_buflen);
/******************************************************************************/
#ifdef __cplusplus
}
#endif
#endif
