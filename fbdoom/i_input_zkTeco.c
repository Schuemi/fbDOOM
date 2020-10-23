//
// Copyright(C) 1993-1996 Id Software, Inc.
// Copyright(C) 2005-2014 Simon Howard
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// DESCRIPTION:
//	DOOM keyboard input via linux tty
//


#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <linux/keyboard.h>
#include <linux/kd.h>

#include "config.h"
#include "deh_str.h"
#include "doomtype.h"
#include "doomkeys.h"
#include "i_joystick.h"
#include "i_system.h"
#include "i_swap.h"
#include "i_timer.h"
#include "i_video.h"
#include "i_scale.h"
#include "m_argv.h"
#include "m_config.h"
#include "m_misc.h"
#include "tables.h"
#include "v_video.h"
#include "w_wad.h"
#include "z_zone.h"

int vanilla_keyboard_mapping = 1;

// Is the shift key currently down?

static int shiftdown = 0;

// Lookup table for mapping AT keycodes to their doom keycode

 /*
  *
0  *1: 400
1   2: 800
2   3: 1000
3   4: 100
4   5: 200
5   6: 2000
6   7: 80000000
7   8: 20000000
8   9: 1000000
9   0: 10000000
10  <- 40000000
11  -> 8000000
12  ok 4000000
13  open: 8000
14  unten: 2000000
15  esc 4000


*/
 
static const unsigned char zk_to_doom[] =
{
    /* 0x00 */ 0x00,
    /* 0x01 */ 0x00,
    /* 0x02 */ 0x00,
    /* 0x03 */ 0x00,
    /* 0x04 */ 0x00,
    /* 0x05 */ 0x00,
    /* 0x06 */ 0x00,
    /* 0x07 */ 0x00,
    /* 0x08 */ 0x00,
    /* 0x09 */ KEY_FIRE,
    /* 0x0a */ KEY_LEFTARROW,
    /* 0x0b */ KEY_RIGHTARROW,
    /* 0x0c */ KEY_ENTER,
    /* 0x0d */ KEY_UPARROW,
    /* 0x0e */ KEY_DOWNARROW,
    /* 0x0f */ KEY_ESCAPE
    
    
    
    
    
};

// Lookup table for mapping ASCII characters to their equivalent when
// shift is pressed on an American layout keyboard:
static const char shiftxform[] =
{
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
    11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
    21, 22, 23, 24, 25, 26, 27, 28, 29, 30,
    31, ' ', '!', '"', '#', '$', '%', '&',
    '"', // shift-'
    '(', ')', '*', '+',
    '<', // shift-,
    '_', // shift--
    '>', // shift-.
    '?', // shift-/
    ')', // shift-0
    '!', // shift-1
    '@', // shift-2
    '#', // shift-3
    '$', // shift-4
    '%', // shift-5
    '^', // shift-6
    '&', // shift-7
    '*', // shift-8
    '(', // shift-9
    ':',
    ':', // shift-;
    '<',
    '+', // shift-=
    '>', '?', '@',
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N',
    'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
    '[', // shift-[
    '!', // shift-backslash - OH MY GOD DOES WATCOM SUCK
    ']', // shift-]
    '"', '_',
    '\'', // shift-`
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N',
    'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
    '{', '|', '}', '~', 127
};

/* Checks whether or not the given file descriptor is associated
   with a local keyboard.
   Returns 1 if it is, 0 if not (or if something prevented us from
   checking). */

int tty_is_kbd(int fd)
{
 

}

static int old_mode = -1;
static struct termios old_term;
static int kb = -1; /* keyboard file descriptor */

char keyPressed[16];
const unsigned int zkKeys[16] = {
0x400,0x800,0x1000,0x100,0x200,0x2000,0x80000000,0x20000000,0x1000000,0x10000000,0x40000000,0x8000000,0x4000000,0x8000,0x2000000,0x4000
};
void kbd_shutdown(void)
{
    
    close(kb);
    exit(0);
}

static int kbd_init(void)
{
   
    memset(keyPressed, 0, 16);
    kb = open("/dev/i2c-1", O_RDWR);
    DEH_printf("kb: %d\n", kb);
    return 0;
}

int kbd_read(int *pressed, unsigned char *key)
{
    DEH_printf("readKb\n");
    return 0;
}

static unsigned char TranslateKey(unsigned char key)
{
     
}

// Get the equivalent ASCII (Unicode?) character for a keypress.

static unsigned char GetTypedChar(unsigned char key)
{
   return 0;
}

static void UpdateShiftStatus(int pressed, unsigned char key)
{
    
}



void I_GetEvent(void)
{
   if (kb == -1) return;
    unsigned char buf[2];
   event_t event;
    int l;
    int i;
    unsigned int key = 0;
    ioctl(kb, 0x706, 0x68);
    write(kb, "\10", 1);
    l = read(kb, buf, 1);
    key += buf[0];

    key = key << 8;
    ioctl(kb, 0x706, 0x68);
    write(kb, "\f", 1);
    l = read(kb, buf, 1);
    key += buf[0];
    key = key << 8;

    ioctl(kb, 0x706, 0x68);
    write(kb, "\t", 1);
    l = read(kb, buf, 1);
    key += buf[0];
    key = key << 8;

    ioctl(kb, 0x706, 0x68);
    write(kb, "\f", 1);
    l = read(kb, buf, 1);
    key += buf[0];

     for (i = 0; i < 16; i++) {
            if ((key & zkKeys[i]) && ! keyPressed[i]) {
                keyPressed[i] = 1;
                
                event.type = ev_keydown;
                event.data1 = zk_to_doom[i];
                event.data2 = 0x00;
                if (event.data1 != 0)
                {
                    D_PostEvent(&event);
                } 
                
            } else if (! (key & zkKeys[i]) && keyPressed[i]){
                keyPressed[i] = 0;
                
                event.type = ev_keyup;
                event.data1 = zk_to_doom[i];
                event.data2 = 0x00;
                if (event.data1 != 0)
                {  
                    D_PostEvent(&event);
                }
            }
     }
 
}

void I_InitInput(void)
{
   kbd_init();
}

