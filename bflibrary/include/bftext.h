/******************************************************************************/
// Bullfrog Engine Emulation Library - for use to remake classic games like
// Syndicate Wars, Magic Carpet, Genewars or Dungeon Keeper.
/******************************************************************************/
/** @file bftext.h
 *     Header file for gtext.cpp.
 * @par Purpose:
 *     Unknown.
 * @par Comment:
 *     None.
 * @author   Tomasz Lis
 * @date     12 Nov 2008 - 05 Nov 2021
 * @par  Copying and copyrights:
 *     This program is free software; you can redistribute it and/or modify
 *     it under the terms of the GNU General Public License as published by
 *     the Free Software Foundation; either version 2 of the License, or
 *     (at your option) any later version.
 */
/******************************************************************************/
#ifndef BFLIBRARY_GTEXT_H_
#define BFLIBRARY_GTEXT_H_

#include "bftypes.h"

#ifdef __cplusplus
extern "C" {
#endif

#pragma pack(1)

struct TbAnyWindow { // sizeof=20
    long x; // offset=0
    long y; // offset=4
    ulong width; // offset=8
    ulong height; // offset=12
    ubyte *ptr; // offset=16
};

typedef struct TbAnyWindow TbAnyWindow;

#pragma pack()

int LbTextSetWindow();
int LbTextSetJustifyWindow();
int LbTextSetClipWindow();
int LbTextStringWidth();
int LbTextWordWidth();
int LbTextStringHeight();
int LbTextDraw();
extern int lbSpacesPerTab;
extern int lbTextJustifyWindow;
extern int lbTextClipWindow;
extern int lbFontPtr;

#ifdef __cplusplus
};
#endif

#endif // BFLIBRARY_GTEXT_H_
/******************************************************************************/
