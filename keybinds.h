/*
 * Skip to 'HERE' if you dont know what your doing 
 */




#ifndef KEYBINDS_DEF_H_
#define KEYBINDS_DEF_H_

#include <X11/XF86keysym.h> 
#include <X11/keysym.h>
#include "toggle.h"
#include "config.h"

/* key definitions */
#define ALT     Mod1Mask
#define NUMLOCK Mod2Mask
#define SUPER   Mod4Mask /* windows key */
#define CTRL    ControlMask
#define SHIFT   ShiftMask
#define TAB     XK_Tab
#define CAPSLOCK LockMask
/* Mouse definitions */
#define LMB  Button1    /* left  mouse button */
#define MMB  Button2    /* midde mouse button */
#define RMB  Button3    /* Right mouse button */
/*
#define Button4 Button4
#define Button5 Button5
#define Button6 Button6
*/
/* #define ISO_LEVEL5_SHIFT Mod3Mask
 * #define ISO_LEVEL3_SHIFT Mod5Mask */

#define TAGKEYS(KEY,TAG) \
{ KeyPress,                     SUPER,                       KEY,      View,            {.ui = 1 << TAG} }, \
{ KeyPress,                     SUPER|CTRL,                  KEY,      ToggleView,      {.ui = 1 << TAG} }, \
{ KeyPress,                     SUPER|SHIFT,                 KEY,      TagWindow,       {.ui = 1 << TAG} }, \


/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* Multimedia Keys (laptops and function keyboards) */
static const char *up_vol[]   = { "pactl", "set-sink-volume", "@DEFAULT_SINK@", "+1%",   NULL };
static const char *down_vol[] = { "pactl", "set-sink-volume", "@DEFAULT_SINK@", "-1%",   NULL };
static const char *mute_vol[] = { "pactl", "set-sink-mute",   "@DEFAULT_SINK@", "toggle", NULL };
static const char *pause_vol[]= { "playerctl", "play-pause"};
static const char *next_vol[] = { "playerctl", "next"};
static const char *prev_vol[] = { "playerctl", "previous"};
static const char *brighter[] = { "brightnessctl", "set", "1%+", NULL };
static const char *dimmer[]   = { "brightnessctl", "set", "1%-", NULL };
/* commands */
static char dmenumon[2] = "0"; 
static const char *dmenucmd[] = 
{ 
    "dmenu_run", "-m", dmenumon, "-fn", dmenufont, 
    "-nb", CFG_DMENU_COL_NORM_BACKGROUND, "-nf", CFG_DMENU_COL_NORM_FOREGROUND, 
    "-sb", CFG_DMENU_COL_SEL_BACKGROUND, "-sf", CFG_DMENU_COL_SEL_FOREGROUND, 
    CFG_DMENU_TOP_BAR ? NULL : "-b", CFG_DMENU_FAST_INPUT ? "-f" : NULL ,CFG_DMENU_CASE_SENSITIVE ? "-i" : NULL, NULL
}; /* flags -b == bottom bar; -f == getkeyboard input first then handle request; */
/* HERE 
 * Keybinds are as clear as possible so just go down and read them if you dont get it go to the function definitions
 * and search up the function in toggle.c
 */
static const char *termcmd[]        = { "st", NULL };
static const char *filemanager[]    = {"thunar", NULL };
static const Key keys[] = 
{
    /*Action            modifier                    key         function            argument */
    { KeyPress,         SUPER,                      XK_n,       UserStats,          {0} },
    { KeyPress,         SUPER,                      XK_d,       SpawnWindow,        {.v = dmenucmd } },
    { KeyPress,         SUPER,                      XK_Return,  SpawnWindow,        {.v = termcmd } },
    { KeyPress,         SUPER,                      XK_e,       SpawnWindow,        {.v = filemanager } },
    { KeyPress,         SUPER,                      XK_b,       ToggleStatusBar,    {0} },
    { KeyPress,         SUPER,                      XK_q,	    View,               {0} },
    { KeyPress,         SUPER|SHIFT,                XK_q,       KillWindow,         {0} },
    { KeyPress,         CTRL|ALT,                   XK_q,	    TerminateWindow,    {0} },
    { KeyPress,         SUPER,                      XK_w,       MaximizeWindow,     {0} },
    { KeyRelease,       SUPER|SHIFT,                XK_p,       Quit,               {0} },
    { KeyPress,         SUPER|CTRL,                 XK_p,       Restart,            {0} },  /* UNSAFE sscanf() */
    { KeyPress,         SUPER,                      XK_z,       SetWindowLayout,    {Tiled} },
    { KeyPress,         SUPER,                      XK_x,       SetWindowLayout,    {Floating} },
    { KeyPress,         SUPER,                      XK_c,       SetWindowLayout,    {Monocle} },
    { KeyPress,         SUPER,                      XK_g,       SetWindowLayout,    {Grid} },
    { KeyPress,         0,                          XK_F11,     ToggleFullscreen,   {0} },
    { KeyPress,         ALT,                        TAB,        AltTab,	            {0} },
    /* multimedia keys */
    { KeyPress,         0, XF86XK_AudioMute,                    SpawnWindow,        {.v = mute_vol } },
    { KeyPress,         0, XF86XK_AudioLowerVolume,             SpawnWindow,        {.v = down_vol } },
    { KeyPress,         0, XF86XK_AudioRaiseVolume,             SpawnWindow,        {.v = up_vol } },
    { KeyPress,         0, XF86XK_MonBrightnessDown,            SpawnWindow,        {.v = dimmer } },
    { KeyPress,         0, XF86XK_MonBrightnessUp,              SpawnWindow,        {.v = brighter } },
    { KeyPress,         0, XF86XK_AudioPlay,                    SpawnWindow,        {.v = pause_vol } },
    { KeyPress,         0, XF86XK_AudioPause,                   SpawnWindow,        {.v = pause_vol } },
    { KeyPress,         0, XF86XK_AudioNext,                    SpawnWindow,        {.v = next_vol } },
    { KeyPress,         0, XF86XK_AudioPrev,                    SpawnWindow,        {.v = prev_vol } },

    TAGKEYS(                        XK_1,                      0)
    TAGKEYS(                        XK_2,                      1)
    TAGKEYS(                        XK_3,                      2)
    TAGKEYS(                        XK_4,                      3)
    TAGKEYS(                        XK_5,                      4)
    TAGKEYS(                        XK_6,                      5)
    TAGKEYS(                        XK_7,                      6)
    TAGKEYS(                        XK_8,                      7)
    TAGKEYS(                        XK_9,                      8)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = 
{
    /*type                  click                event mask      button             function            argument */
    { ButtonPress,        ClkLtSymbol,          0,              LMB,              SetWindowLayout,    {.i = Tiled} },
    { ButtonPress,        ClkLtSymbol,          0,              RMB,              SetWindowLayout,    {.i = Monocle} },
    { ButtonPress,        ClkClientWin,         SUPER,          LMB,              DragWindow,         {0} },
    { ButtonPress,        ClkClientWin,         SUPER,          RMB,              ResizeWindow,       {0} },
    { ButtonPress,        ClkTagBar,            0,              LMB,              View,               {0} },
    { ButtonPress,        ClkTagBar,            SUPER,          LMB,              TagWindow,          {0} },
    { ButtonPress,        ClkTagBar,            SUPER,          RMB,              ToggleTag,          {0} },
};


#endif
