#ifndef CFG_H_
#define CFG_H_

#include "dwm.h"
/* See LICENSE file for copyright and license details.
 * 4 Tab spaces; No tab characters use spaces for tabs
 * Basic overview of dwm => https://ratfactor.com/dwm
 * For more information about xlib (X11)       visit https://x.org/releases/current/doc/libX11/libX11/libX11.html
 * For a quick peak at commonly used functions visit https://tronche.com/gui/x/xlib/
 * Cursors : https://tronche.com/gui/x/xlib/appendix/b/
 * XCursor:  https://man.archlinux.org/man/Xcursor.3
 * EWMH:     https://specifications.freedesktop.org/wm-spec/wm-spec-latest.html
 * XEvent:   https://tronche.com/gui/x/xlib/events/structures.html
 * Document: https://www.x.org/releases/X11R7.5/doc/x11proto/proto.pdf
 */
/* Monitor */
#define CFG_MONITOR_FACT        0.55        /* factor of master area size [0.05..0.95]                          */
#define CFG_MASTER_COUNT        1           /* number of clients in master area                                 */
#define CFG_DEFAULT_LAYOUT      Monocle     /* Default window layout Grid,Tiled,Monocle,Floating;               */
#define CFG_DEFAULT_PREV_LAYOUT Tiled       /* See above; Sets previous layout when starting dwm                */
#define CFG_DEFAULT_TAG_NUM     1           /* Tag number when starting dwm (1-9); 0 for default tag            */

/* Window */
#define CFG_BORDER_PX           0           /* border pixel of windows                                          */
#define CFG_SNAP                15          /* snap window to border in pixels; (NOT RECOMMENDED)0 to disable   */
#define CFG_WIN_RATE            120         /* max refresh rate when resizing, moving windows;  0 to disable    */
#define CFG_HOVER_FOCUS         0           /* 1 on mouse hover focus that window; 0 to disable                 */
#define CFG_RESIZE_BASE_WIDTH   0           /* Minimum size for resizing windows; while respecting sizehints    */
#define CFG_RESIZE_BASE_HEIGHT  0           /* Minimum size for resizing windows; while respecting sizehints    */
#define CFG_RESIZE_IGNORE_HINTS 0           /* (NOT RECOMMENDED)1 Ignore size hints use base(w/h); 0 to disable */
#define CFG_STORE_PID           1           /* 1 store pid in client; 0 to disable, effects below               */
#define CFG_ALLOW_PID_KILL      1           /* Allow PID to be grabbed to Terminate a window ONLY on failure    */
/* Status Bar */
#define WM_NAME                 "dwm.exe"   /* wm name displayed when using X (type neofetch to see this)       */
#define CFG_SHOW_WM_NAME        0           /* 1 Show window manager name at end of status bar; 0 to disable    */
#define CFG_BAR_HEIGHT          0           /* 1 enable specific bar height; 0 use default height               */
#define CFG_TOP_BAR             0           /* 1 show bar on top; 0 for bottom bar                              */
#define CFG_BAR_PADDING         0           /* padding in pixels (both sides)                                   */
#define CFG_ACTIVE_MON          1           /* Show seletected even if no clients in monitor; 0 to disable      */
#define CFG_SHOW_BAR            1           /* 1 to show bar; 0 to disable                                      */
#define CFG_ICON_SHOW           1           /* 1 show icon (mem expensive 0.1-1Mib per window); 0 to disable    */
#define CFG_ICON_SIZE           16          /* icon size                                                        */
#define CFG_ICON_SPACE          2           /* space between icon and title                                     */
#define CFG_SEL_TAG_INDICATOR   1           /* 1 show selected tag even if there are no clients; 0 to disable   */
/* AltTab */
/* To get a KeyCode you can use xev and type a key */
#define CFG_ALT_TAB_SWITCH_KEY      64      /* Hold this key to keep alt-tab active                             */
#define CFG_ALT_TAB_CYCLE_KEY       23      /* Tap this key to focus next client                                */
#define CFG_ALT_TAB_POS_X           1       /* tab position on X axis, 0 = left, 1 = center, 2 = right          */
#define CFG_ALT_TAB_POS_Y           1       /* tab position on Y axis, 0 = bottom, 1 = center, 2 = top          */
#define CFG_ALT_TAB_TEXT_POS_X      1       /* txt position on x axis, 0 = left , 1 = center, 2 = right         */
#define CFG_ALT_TAB_MAX_WIDTH       600     /* MAX tab menu width                                               */
#define CFG_ALT_TAB_MAX_HEIGHT      200     /* MAX tab menu height                                              */
#define CFG_ALT_TAB_MIN_WIDTH       0       /* Add padding if text length is shorter; 0 to disable              */
#define CFG_ALT_TAB_MAP_WINDOWS     1       /* 1 compositor fadding when switching tabs; 0 to disable           */
#define CFG_ALT_TAB_SHOW_PREVIEW    1       /* shows window preview when alt tabbing                            */
#define CFG_ALT_TAB_FIXED_TILE      0       /* 1 alttab moves down client list instead; 0 to disable            */
/* Misc */
#define CFG_MAX_CLIENT_COUNT        256     /* max number of clients (XOrg Default is 256)                      */
#define CFG_RESIZE_HINTS            1       /* 1 means respect size hints in tiled resizals                     */
#define CFG_LOCK_FULLSCREEN         1       /* 1 will force focus on the fullscreen window (Mostly Useless)     */
#define CFG_DECOR_HINTS             1       /* 1 Dont ignore Decoration Hints made by windows; 0 to disable     */
#define CFG_X_VERBOSE_ERRORS        1       /* Show verbose errors at the cost of binary size when xorg exits   */
/* dmenu */
#define CFG_DMENU_TOP_BAR           0       /* 1 show dmenu bar on top; 0 for bottom bar                        */
#define CFG_DMENU_FAST_INPUT        0       /* 1 prioritize input over bar render; 0 to disable                 */
#define CFG_DMENU_CASE_SENSITIVE    1       /* 1 dmenu searches case senstivly; 0 to disable                    */
/* dmenu colours */
#define CFG_DMENU_COL_NORM_BACKGROUND       "#000000" /* dmenu background colour for NON selected items */
#define CFG_DMENU_COL_NORM_FOREGROUND       "#ffffff" /* dmenu text colour for NON selected items       */
#define CFG_DMENU_COL_SEL_BACKGROUND        "#000000" /* dmenu background colour for SELECTED items     */ 
#define CFG_DMENU_COL_SEL_FOREGROUND        "#ffffff" /* dmenu text colour for SELECTED items           */

/* NOT FULLY IMPLEMENTED (DONT REMOVE) */
#define CFG_AUTO_TIME_ZONE          1       /* Get System time instead of time set below                        */
#define CFG_TIME_ZONE               "Country/City" /* see https://wiki.archlinux.org/title/System_time          */
/* caveats
 * CFG_MAX_CLIENT_COUNT may limit your client count lower than usual when using a compositor.
 * FAST_INPUT feels janky
 */
/* make vars static to avoid linker errs cause these are consts and we need sizeof()*/
static const char *fonts[]      =   {"monospace:size=12" };
static const char dmenufont[]   =   {"monospace:size=12"};

/* COLOURS */
#define COL_BLACK       "#000000"
#define COL_WHITE       "#ffffff"
#define COL_GREY        "#C0C0C0"
#define COL_RED         "#ff0000"
#define COL_PINK        "#FF00FF"
#define COL_BLUE        "#0000FF"
#define COL_YELLOW      "#FFFF00"

/* static char col_term_blue[]   = "#ecffff"; */
static char *colors[][3] =
{
    /*					        fg         bg          border   */
    [SchemeNorm]            = { COL_WHITE, COL_BLACK, COL_WHITE}, /* Scheme normal */
    [SchemeSel]             = { COL_WHITE, COL_BLACK, COL_WHITE}, /* Scheme Selected*/
    [SchemeUrgent]          = { COL_BLUE,  COL_RED,   COL_BLUE }, /* NOT USED */
    [SchemeWarn]            = { COL_WHITE, COL_YELLOW,COL_WHITE}, /* NOT USED */

    [SchemeAltTab]          = { COL_WHITE, COL_BLACK, COL_BLACK},
    [SchemeAltTabSelect]    = { COL_BLACK, COL_WHITE, COL_WHITE},

    [SchemeBarTabActive]    = { COL_BLACK, COL_WHITE, COL_WHITE}, /* Scheme Normal   */
    [SchemeBarTabInactive]  = { COL_WHITE, COL_BLACK, COL_BLACK}, /* Scheme Selected */
    [SchemeTagActive]       = { COL_BLACK, COL_WHITE, COL_WHITE}, /* Scheme Selected */

};
/* appearance */
/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
static const char *tagcols[][2] = {
    /* fg       bg */
    {COL_WHITE, COL_BLACK},
    {COL_WHITE, COL_BLACK},
    {COL_WHITE, COL_BLACK},
    {COL_WHITE, COL_BLACK},
    {COL_WHITE, COL_BLACK},
    {COL_WHITE, COL_BLACK},
    {COL_WHITE, COL_BLACK},
    {COL_WHITE, COL_BLACK},
    {COL_WHITE, COL_BLACK},
};
static const Rule rules[] =
{
    /* xprop(1):
     *	WM_CLASS(STRING) = instance, class
     *	WM_NAME(STRING) = title
     */
    /* class      instance    title       tags mask     isfloating   monitor */
    { "Gimp",     NULL,       NULL,       0,            1,           -1 },
};

/* layout(s) */

static const Layout layouts[] =
{
    /* symbol     arrange function */
    [Tiled]     = { "[T]",      tile            },
    [Floating]  = { "[F]",      NULL            },
    [Monocle]   = { "[M]",      monocle         },
    [Grid]      = { "[G]",      grid            },
};

#endif


/* Any version past v3.0.0 IS BLOATWARE USER DISCRETION IS ADVICED */ 
/* DEBUGGING
 * Stuff you need gdb xephyr
 * sudo pacman -S gdb xorg-server-xephyr
 *
 *
 * first make sure its compiled in DEBUG using config.mk
 *
 * run this command: Xephyr :1 -ac -resizeable -screen 680x480 &
 * set the display to the one you did for Xephyr in this case we did 1 so
 * run this command: export DISPLAY=:1
 * now you are mostly done
 * run this command: gdb dwm
 * you get menu
 * run this command: lay split
 * you get layout and stuff
 * 
 * now basic gdb stuff
 * break or b somefunction # this sets a break point for whatever function AKA stop the code from running till we say so
 * next or n # this moves to the next line of logic code (logic code is current code line)
 * step or s # this moves to the next line of code (code being actual code so functions no longer exist instead we just go there)
 * ctrl-l # this resets the window thing which can break sometimes (not sure why it hasnt been fixed but ok)
 * skip somefunction # this tries to skip a function if it can but ussualy is worthless (AKA I dont know how to use it)(skip being not show to you but it does run in the code)
 *
 * after your done
 * run this command: exit
 * you have succesfully used gdb wow
 * 
 */
