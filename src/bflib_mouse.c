/******************************************************************************/
// Bullfrog Engine Emulation Library - for use to remake classic games like
// Syndicate Wars, Magic Carpet or Dungeon Keeper.
/******************************************************************************/
/** @file bflib_mouse.cpp
 *     Mouse related routines.
 * @par Purpose:
 *     Pointer position, movement and cursor support.
 * @par Comment:
 *     None.
 * @author   Tomasz Lis
 * @date     12 Feb 2008 - 26 Oct 2010
 * @par  Copying and copyrights:
 *     This program is free software; you can redistribute it and/or modify
 *     it under the terms of the GNU General Public License as published by
 *     the Free Software Foundation; either version 2 of the License, or
 *     (at your option) any later version.
 */
/******************************************************************************/
#include "bflib_mouse.h"

#include <string.h>
#include <stdarg.h>
#include <stdlib.h>

#include "bflib_basics.h"
#include "bfsprite.h"

#ifdef __cplusplus
extern "C" {
#endif
/******************************************************************************/
/*
TbResult LbMouseChangeSpriteAndHotspot(struct TbSprite *pointer_spr, long hot_x, long hot_y)
{
    if (pointerSprite == NULL)
        BFLIB_DEBUGLOG(0,"Setting to %s","NONE");
    else
        BFLIB_DEBUGLOG(0,"Setting to %dx%d, data at %p",(int)pointer_spr->SWidth,(int)pointer_spr->SHeight,pointer_spr->Data);
  if (!lbMouseInstalled)
    return Lb_FAIL;
  if (!pointerHandler.SetMousePointerAndOffset(pointerSprite, hot_x, hot_y))
    return Lb_FAIL;
  return Lb_SUCCESS;
}*/

TbResult LbMouseSetup(struct TbSprite *pointer_spr, int ratio_x, int ratio_y)
{
  TbResult ret;
  asm volatile ("call ASM_LbMouseSetup\n"
      : "=r" (ret) : "a" (pointer_spr), "d" (ratio_x), "b" (ratio_y));
/*  long x,y;
  if (lbMouseInstalled)
    LbMouseSuspend();
  y = (lbDisplay.MouseWindowHeight + lbDisplay.MouseWindowY) / 2;
  x = (lbDisplay.MouseWindowWidth + lbDisplay.MouseWindowX) / 2;
  pointerHandler.Install();
  lbMouseOffline = true;
  lbMouseInstalled = true;
  LbMouseSetWindow(0,0,LbGraphicsScreenWidth(),LbGraphicsScreenHeight());
  ret = Lb_SUCCESS;
  if (LbMouseSetPosition(x,y) != Lb_SUCCESS)
    ret = Lb_FAIL;
  if (LbMouseChangeSprite(pointerSprite) != Lb_SUCCESS)
    ret = Lb_FAIL;
  lbMouseInstalled = (ret == Lb_SUCCESS);
  lbMouseOffline = false;*/
  return ret;
}

/*TbResult LbMouseSetPointerHotspot(long hot_x, long hot_y)
{
  if (!lbMouseInstalled)
    return Lb_FAIL;
  if (!pointerHandler.SetPointerOffset(hot_x, hot_y))
    return Lb_FAIL;
  return Lb_SUCCESS;
}

TbResult LbMouseSetPosition(long x, long y)
{
  if (!lbMouseInstalled)
    return Lb_FAIL;
  if (!pointerHandler.SetMousePosition(x, y))
    return Lb_FAIL;
  return Lb_SUCCESS;
}*/

TbResult LbMouseChangeSprite(struct TbSprite *pointer_spr)
{
    if (pointer_spr == NULL)
        BFLIB_DEBUGLOG(0,"Setting to %s","NONE");
    else
        BFLIB_DEBUGLOG(0,"Setting to %dx%d, data at %p",(int)pointer_spr->SWidth,(int)pointer_spr->SHeight,pointer_spr->Data);
    TbResult ret;
    asm volatile ("call ASM_LbMouseChangeSprite\n"
        : "=r" (ret) : "a" (pointer_spr));
    return ret;
    /*
  if (!lbMouseInstalled)
    return Lb_FAIL;
  if (!pointerHandler.SetMousePointer(pointerSprite))
    return Lb_FAIL;
  return Lb_SUCCESS;*/
}

/*void GetPointerHotspot(long *hot_x, long *hot_y)
{
  struct TbPoint *hotspot;
  hotspot = pointerHandler.GetPointerOffset();
  if (hotspot == NULL)
    return;
  *hot_x = hotspot->x;
  *hot_y = hotspot->y;
}

TbResult LbMouseIsInstalled(void)
{
  if (!lbMouseInstalled)
    return Lb_FAIL;
  if (!pointerHandler.IsInstalled())
    return Lb_FAIL;
  return Lb_SUCCESS;
}

TbResult LbMouseSetWindow(long x, long y, long width, long height)
{
  if (!lbMouseInstalled)
    return Lb_FAIL;
  if (!pointerHandler.SetMouseWindow(x, y, width, height))
    return Lb_FAIL;
  return Lb_SUCCESS;
}

TbResult LbMouseOnMove(struct TbPoint shift)
{
  if ((!lbMouseInstalled) || (lbMouseOffline))
    return Lb_FAIL;
  if (!pointerHandler.SetMousePosition(lbDisplay.MMouseX+shift.x, lbDisplay.MMouseY+shift.y))
    return Lb_FAIL;
  return Lb_SUCCESS;
}*/

/** Converts mouse coordinates into relative shift coordinates.
 *
 * @param pos Pointer to the structure with source point, and where result is placed.
 */
/*void MouseToScreen(struct TbPoint *pos)
{
  // Static variables for storing last mouse coordinated; needed
  // because lbDisplay.MMouse? coords are scaled
  static long mx = 0;
  static long my = 0;
  struct TbRect clip;
  struct TbPoint orig;
  if ( lbMouseAutoReset )
  {
      if (!pointerHandler.GetMouseWindow(&clip))
          return;
      orig.x = pos->x;
      orig.y = pos->y;
      pos->x = ((pos->x - mx) * (long)lbDisplay.MouseMoveRatio)/256;
      pos->y = ((pos->y - my) * (long)lbDisplay.MouseMoveRatio)/256;
      mx = orig.x;
      my = orig.y;
      if ((mx < clip.left + 50) || (mx > clip.right - 50)
       || (my < clip.top + 50) || (my > clip.bottom - 50))
      {
          mx = (clip.right-clip.left)/2 + clip.left;
          my = (clip.bottom-clip.top)/2 + clip.top;
          SDL_WarpMouse(mx, my);
      }
  } else
  {
      orig.x = pos->x;
      orig.y = pos->y;
      pos->x = ((pos->x - mx) * (long)lbDisplay.MouseMoveRatio)/256;
      pos->y = ((pos->y - my) * (long)lbDisplay.MouseMoveRatio)/256;
      mx = orig.x;
      my = orig.y;
  }
}

TbResult LbMouseSuspend(void)
{
  if (!lbMouseInstalled)
    return Lb_FAIL;
  if (!pointerHandler.Release())
    return Lb_FAIL;
  return Lb_SUCCESS;
}

TbResult LbMouseOnBeginSwap(void)
{
    if (!pointerHandler.PointerBeginSwap())
        return Lb_FAIL;
    return Lb_SUCCESS;
}

TbResult LbMouseOnEndSwap(void)
{
    if (!pointerHandler.PointerEndSwap())
        return Lb_FAIL;
    return Lb_SUCCESS;
}

void mouseControl(unsigned int action, struct TbPoint *pos)
{
    struct TbPoint dstPos;
    dstPos.x = pos->x;
    dstPos.y = pos->y;
    switch ( action )
    {
    case MActn_MOUSEMOVE:
        MouseToScreen(&dstPos);
        LbMouseOnMove(dstPos);
        break;
    case MActn_LBUTTONDOWN:
        lbDisplay.MLeftButton = 1;
        if ( !lbDisplay.LeftButton )
        {
            MouseToScreen(&dstPos);
            LbMouseOnMove(dstPos);
            lbDisplay.MouseX = lbDisplay.MMouseX;
            lbDisplay.MouseY = lbDisplay.MMouseY;
            lbDisplay.RLeftButton = 0;
            lbDisplay.LeftButton = 1;
        }
        break;
    case MActn_LBUTTONUP:
        lbDisplay.MLeftButton = 0;
        if ( !lbDisplay.RLeftButton )
        {
            MouseToScreen(&dstPos);
            LbMouseOnMove(dstPos);
            lbDisplay.RMouseX = lbDisplay.MMouseX;
            lbDisplay.RMouseY = lbDisplay.MMouseY;
            lbDisplay.RLeftButton = 1;
        }
        break;
    case MActn_RBUTTONDOWN:
        lbDisplay.MRightButton = 1;
        if ( !lbDisplay.RightButton )
        {
            MouseToScreen(&dstPos);
            LbMouseOnMove(dstPos);
            lbDisplay.MouseX = lbDisplay.MMouseX;
            lbDisplay.MouseY = lbDisplay.MMouseY;
            lbDisplay.RRightButton = 0;
            lbDisplay.RightButton = 1;
        }
        break;
    case MActn_RBUTTONUP:
        lbDisplay.MRightButton = 0;
        if ( !lbDisplay.RRightButton )
        {
            MouseToScreen(&dstPos);
            LbMouseOnMove(dstPos);
            lbDisplay.RMouseX = lbDisplay.MMouseX;
            lbDisplay.RMouseY = lbDisplay.MMouseY;
            lbDisplay.RRightButton = 1;
        }
        break;
    case MActn_MBUTTONDOWN:
        lbDisplay.MMiddleButton = 1;
        if ( !lbDisplay.MiddleButton )
        {
            MouseToScreen(&dstPos);
            LbMouseOnMove(dstPos);
            lbDisplay.MouseX = lbDisplay.MMouseX;
            lbDisplay.MouseY = lbDisplay.MMouseY;
            lbDisplay.MiddleButton = 1;
            lbDisplay.RMiddleButton = 0;
        }
        break;
    case MActn_MBUTTONUP:
        lbDisplay.MMiddleButton = 0;
        if ( !lbDisplay.RMiddleButton )
        {
            MouseToScreen(&dstPos);
            LbMouseOnMove(dstPos);
            lbDisplay.RMouseX = lbDisplay.MMouseX;
            lbDisplay.RMouseY = lbDisplay.MMouseY;
            lbDisplay.RMiddleButton = 1;
        }
        break;
    case MActn_WHEELMOVEUP:
        lbDisplayEx.WhellPosition--;
        lbDisplayEx.WhellMoveUp++;
        lbDisplayEx.WhellMoveDown = 0;
        break;
    case MActn_WHEELMOVEDOWN:
        lbDisplayEx.WhellPosition++;
        lbDisplayEx.WhellMoveUp = 0;
        lbDisplayEx.WhellMoveDown++;
        break;
    default:
        break;
    }
}*/

/**
 * Changes mouse movement ratio.
 * Note that this function can be run even before mouse setup. Still, the factor
 *  will be reset during the installation - so use it after LbMouseSetup().
 *
 * @param ratio_x Movement ratio in X direction; 256 means unchanged ratio from OS.
 * @param ratio_y Movement ratio in Y direction; 256 means unchanged ratio from OS.
 * @return Lb_SUCCESS if the ratio values were of correct range and have been set.
 */
/*TbResult LbMouseChangeMoveRatio(long ratio_x, long ratio_y)
{
    if ((ratio_x < -8192) || (ratio_x > 8192) || (ratio_x == 0))
        return Lb_FAIL;
    if ((ratio_y < -8192) || (ratio_y > 8192) || (ratio_y == 0))
        return Lb_FAIL;
    SYNCLOG("New ratio %ldx%ld",ratio_x, ratio_y);
    // Currently we don't have two ratio factors, so let's store an average
    lbDisplay.MouseMoveRatio = (ratio_x + ratio_y)/2;
    //TODO INPUT Separate mouse ratios in X and Y direction when lbDisplay from DLL will no longer be used.
    //minfo.XMoveRatio = ratio_x;
    //minfo.YMoveRatio = ratio_y;
    return Lb_SUCCESS;
}*/

/******************************************************************************/
#ifdef __cplusplus
}
#endif
