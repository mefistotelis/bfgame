/******************************************************************************/
// Bullfrog Sound Library - for use to remake classic games like
// Syndicate Wars, Magic Carpet, Genewars or Dungeon Keeper.
/******************************************************************************/
/** @file ssamplst.c
 *     Sound Sample Fade support routines.
 * @par Purpose:
 *     Functions for handling sound samples fade.
 * @par Comment:
 *     None.
 * @author   Tomasz Lis
 * @date     12 Jun 2022 - 05 Sep 2022
 * @par  Copying and copyrights:
 *     This program is free software; you can redistribute it and/or modify
 *     it under the terms of the GNU General Public License as published by
 *     the Free Software Foundation; either version 2 of the License, or
 *     (at your option) any later version.
 */
/******************************************************************************/
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <assert.h>

#include "ssampfad.h"

#include "bfsound.h"
#include "aildebug.h"
/******************************************************************************/
long sample_fade_handle = 0;

TbBool volatile samples_currently_fading = false;
TbBool volatile switch_off_sample_fade_timer = false;
TbBool a_sample_is_fading = false;

extern TbBool SoundInstalled;
extern TbBool SoundAble;
extern TbBool SoundActive;

extern struct SampleInfo sample_id[32];
extern struct SampleInfo *end_sample_id;

/******************************************************************************/

void cbfadesample()
{
    struct SampleInfo *p_smpinf;
    int i;

    if (!SoundInstalled || !SoundAble || !SoundActive)
    {
        switch_off_sample_fade_timer = 1;
        samples_currently_fading = 0;
        for (p_smpinf = sample_id; p_smpinf <= end_sample_id; p_smpinf++)
        {
            p_smpinf->FadeState = 0;
            p_smpinf->FadeStopFlag = 0;
        }
        return;
    }

    if (switch_off_sample_fade_timer)
    {
        AIL_release_timer_handle(sample_fade_handle);
        return;
    }

    a_sample_is_fading = switch_off_sample_fade_timer;

    for (p_smpinf = sample_id; p_smpinf <= end_sample_id; p_smpinf++)
    {
        switch (p_smpinf->FadeState)
        {
        case 1:
            a_sample_is_fading = 1;
            if (AIL_sample_status(p_smpinf->SampleHandle) != SNDSMP_PLAYING)
            {
                p_smpinf->FadeState = 0;
                p_smpinf->FadeStopFlag = 0;
                break;
            }
            if (p_smpinf->FadeToVolume > 127)
                p_smpinf->FadeToVolume = 127;
            if (p_smpinf->FadeToVolume <= p_smpinf->SampleVolume)
            {
                p_smpinf->FadeState = 0;
                if (p_smpinf->FadeStopFlag) {
                    AIL_end_sample(p_smpinf->SampleHandle);
                    p_smpinf->FadeStopFlag = 0;
                }
            }
            if (p_smpinf->FadeState != 1)
                break;
            for (i = 1; i <= p_smpinf->FadeStep ; i++)
            {
                p_smpinf->SampleVolume++;
                if (p_smpinf->SampleVolume >= 127) {
                    p_smpinf->SampleVolume = 127;
                    break; // for() only
                }
                if (p_smpinf->FadeToVolume <= p_smpinf->SampleVolume) {
                    p_smpinf->SampleVolume = p_smpinf->FadeToVolume;
                    break; // for() only
                }
            }
            AIL_set_sample_volume(p_smpinf->SampleHandle, p_smpinf->SampleVolume);
            break;
        case 2:
            a_sample_is_fading = 1;
            if (AIL_sample_status(p_smpinf->SampleHandle) != SNDSMP_PLAYING)
            {
                p_smpinf->FadeState = 0;
                p_smpinf->FadeStopFlag = 0;
                break;
            }
            if (p_smpinf->FadeToVolume >= p_smpinf->SampleVolume)
            {
                p_smpinf->FadeState = 0;
                if (p_smpinf->FadeStopFlag) {
                    AIL_end_sample(p_smpinf->SampleHandle);
                    p_smpinf->FadeStopFlag = 0;
                }
            }
            if (p_smpinf->FadeState != 2)
                break;
            for (i = 1; i <= p_smpinf->FadeStep ; i++)
            {
                p_smpinf->SampleVolume--;
                if (p_smpinf->SampleVolume <= 0) {
                    p_smpinf->SampleVolume = 0;
                    break; // for() only
                }
                if (p_smpinf->FadeToVolume >= p_smpinf->SampleVolume) {
                    p_smpinf->SampleVolume = p_smpinf->FadeToVolume;
                    break; // for() only
                }
            }
            AIL_set_sample_volume(p_smpinf->SampleHandle, p_smpinf->SampleVolume);
            break;
        default:
            break;
        }
    }

    if (!a_sample_is_fading)
    {
        switch_off_sample_fade_timer = 1;
        samples_currently_fading = 0;
    }
}

void StopAllSampleFadeTimers(void)
{
    struct SampleInfo *smpinfo;

    if (samples_currently_fading == 0)
        return;
    switch_off_sample_fade_timer = 1;
    AIL_release_timer_handle(sample_fade_handle);
    samples_currently_fading = 0;
    for (smpinfo = sample_id; smpinfo <= end_sample_id; smpinfo++)
    {
        smpinfo->FadeState = 0;
        smpinfo->FadeStopFlag = 0;
    }
}

/******************************************************************************/
