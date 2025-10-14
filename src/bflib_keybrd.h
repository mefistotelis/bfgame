/******************************************************************************/
// Bullfrog Engine Emulation Library - for use to remake classic games like
// Syndicate Wars, Magic Carpet or Dungeon Keeper.
/******************************************************************************/
/** @file bflib_keybrd.h
 *     Header file for bflib_keybrd.c.
 * @par Purpose:
 *     Keyboard related routines - reading keyboard.
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
#ifndef BFLIB_KEYBRD_H
#define BFLIB_KEYBRD_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif
/******************************************************************************/
enum KeyAction {
        KActn_NONE = 0,
        KActn_KEYDOWN,
        KActn_KEYUP,
};

/******************************************************************************/
extern uint32_t lbInkey_prefixed;
extern uint16_t lbShift;


/******************************************************************************/
#ifdef __cplusplus
}
#endif
#endif
