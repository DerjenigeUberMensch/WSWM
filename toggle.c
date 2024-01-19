/* user functions */

#include "toggle.h"
void
tester(const Arg *arg)
{
}


void
FocusMonitor(const Arg *arg)
{
    Monitor *m;

    if (!mons->next) return;
    if ((m = dirtomon(arg->i)) == selmon) return;
    unfocus(selmon->sel, 0);
    selmon = m;
    focus(NULL);
}
void
FocusNextWindow(const Arg *arg) {
	Monitor *m;
	Client *c;
	m = selmon;
	c = m->sel;

	if (arg->i) {
		if (c->next)
			c = c->next;
		else
			c = m->clients;
	} else {
		Client *last = c;
		if (last == m->clients)
			last = NULL;
		for (c = m->clients; c->next != last; c = c->next);
	}; /* prevent 0 division errors */
	focus(c);
}

void
ChangeMasterWindow(const Arg *arg)
{
    selmon->nmaster = MAX(selmon->nmaster + arg->i, 0);
    arrange(selmon);
}

void
KillWindow(const Arg *arg)
{
    killclient(selmon->sel, GRACEFUL);
}
void
TerminateWindow(const Arg *arg)
{
    killclient(selmon->sel, SAFEDESTROY);
}
void
DragWindow(const Arg *arg) /* movemouse */
{
    int x, y, ocx, ocy, nx, ny;
    Client *c;
    Monitor *m;
    XEvent ev;
    Time lasttime;

    const float frametime = 1000 / (CFG_WIN_RATE + !CFG_WIN_RATE); /* prevent 0 division errors */

    c = selmon->sel;
    if (!c) return;
    if (c->isfullscreen) return; /* no support moving fullscreen windows by mouse */
    restack(selmon);
    if (!c->isfloating || selmon->lt[selmon->sellt]->arrange) ToggleFloating(NULL);
    if (XGrabPointer(dpy, root, False, MOUSEMASK, GrabModeAsync, GrabModeAsync,
                     None, cursor[CurMove]->cursor, CurrentTime) != GrabSuccess) return;
    if (!getrootptr(&x, &y)) return;
    lasttime = 0;
    ocx = c->x;
    ocy = c->y;
    do {
        XMaskEvent(dpy, MOUSEMASK|ExposureMask|SubstructureRedirectMask, &ev);
        switch(ev.type) {
        case ConfigureRequest:
        case Expose:
        case MapRequest:
            handler[ev.type](&ev);
            break;
        case MotionNotify:
            if(CFG_WIN_RATE != 0)
            {
                if ((ev.xmotion.time - lasttime) <= frametime) continue;
                lasttime = ev.xmotion.time;
            }
            nx = ocx + (ev.xmotion.x - x);
            ny = ocy + (ev.xmotion.y - y);
            if (abs(selmon->wx - nx) < CFG_SNAP)
                nx = selmon->wx;
            else if (abs((selmon->wx + selmon->ww) - (nx + WIDTH(c))) < CFG_SNAP)
                nx = selmon->wx + selmon->ww - WIDTH(c);
            if (abs(selmon->wy - ny) < CFG_SNAP)
                ny = selmon->wy;
            resize(c, nx, ny, c->w, c->h, 1);
            break;
        }
    } while (ev.type != ButtonRelease);
    if(clientdocked(c))
    {
        /* maxmize stuff */
        c->ismax = 1;
        c->oldx += CFG_SNAP;
        c->oldy += CFG_SNAP;
    }
    else c->ismax = 0;
    XUngrabPointer(dpy, CurrentTime);
    if ((m = recttomon(c->x, c->y, c->w, c->h)) != selmon) {
        sendmon(c, m);
        selmon = m;
        focus(NULL);
    }
    restack(selmon);
}


void 
Restart(const Arg *arg)
{
    savesession();
    restart();
}
void
Quit(const Arg *arg)
{
    savesession();
    quit();
}

void
ResizeWindow(const Arg *arg) /* resizemouse */
{
    /* rcurx, rcury     old x/y Pos for root cursor
     * ocw/och          old client width/height
     * nw/nh            new width/height
     * ocx/ocy          old client posX/posY
     * nx/ny            new posX/posY
     * horiz/vert       check if top left/bottom left of screen
     * di,dui,dummy     holder vars to pass check (useless aside from check)
     * basew            Minimum client request size (wont go smaller)
     * baseh            See above
     */
    int rcurx, rcury;
    int ocw, och;
    int nw, nh;
    int ocx, ocy;
    int nx, ny;
    int horiz, vert;
    int basew, baseh;
    const float frametime = 1000 / (CFG_WIN_RATE + !CFG_WIN_RATE); /*prevent 0 division errors */

    unsigned int dui;
    Window dummy;

    Client *c;
    Monitor *m;
    XEvent ev;
    Time lasttime = 0;
    c = selmon->sel;

    /* client checks */
    if (!c || c->isfullscreen) return;/* no support resizing fullscreen windows by mouse */
    if (XGrabPointer(dpy, root, False, MOUSEMASK, GrabModeAsync, GrabModeAsync,
                     None, cursor[CurResize]->cursor, CurrentTime) != GrabSuccess) return;
    if (!XQueryPointer (dpy, c->win, &dummy, &dummy, &rcurx, &rcury, &nx, &ny, &dui)) return;
    if (!c->isfloating || selmon->lt[selmon->sellt]->arrange) ToggleFloating(NULL);
    restack(selmon);
    ocw = c->w;
    och = c->h;
    ocx = c->x;
    ocy = c->y;

    horiz = nx < c->w >> 1 ? -1 : 1;
    vert  = ny < c->h >> 1 ? -1 : 1;
    basew = MAX(c->minw, CFG_RESIZE_BASE_WIDTH);
    baseh = MAX(c->minh, CFG_RESIZE_BASE_HEIGHT);
    do {
        XMaskEvent(dpy, MOUSEMASK|ExposureMask|SubstructureRedirectMask, &ev);
        switch(ev.type)
        {
        case ConfigureRequest:
        case Expose:
        case MapRequest: handler[ev.type](&ev); break;
        case MotionNotify:
            if(CFG_WIN_RATE != 0)
            {
                if ((ev.xmotion.time - lasttime) <= frametime)
                    continue;
                lasttime = ev.xmotion.time;
            }
            /* calculate */
            nw = ocw + horiz * (ev.xmotion.x - rcurx); 
            nh = och + vert * (ev.xmotion.y - rcury);
            /* clamp */
            nw = MAX(nw, basew); nh = MAX(nh, baseh);
            /* calculate */
            /* flip sign if -1 else default to 0 */
            nx = ocx + !~horiz * (ocw - nw);
            ny = ocy + !~vert  * (och - nh);

            resize(c, nx, ny, nw, nh, 1);
            break;
        }
    } while (ev.type != ButtonRelease);
    /* add if w + x > monx || w + x < 0 resize */
    if(c->w + c->bw > c->mon->ww)
        MaximizeWindowHorizontal(NULL);
    if(c->h + c->bw + bh * c->mon->showbar > c->mon->wh)
        MaximizeWindowVertical(NULL);
    if(clientdocked(c))
    {
        /* maxmize stuff */
        c->ismax = 1;
        c->oldx += CFG_SNAP;
        c->oldy += CFG_SNAP;
    }
    else c->ismax = 0;

    XUngrabPointer(dpy, CurrentTime);
    while (XCheckMaskEvent(dpy, EnterWindowMask, &ev));
    if ((m = recttomon(c->x, c->y, c->w, c->h)) != selmon) {
        sendmon(c, m);
        selmon = m;
        focus(NULL);
    }
    restack(selmon);
}

void
SetWindowLayout(const Arg *arg)
{
    Monitor *m;
    m = selmon;

    if(!m) return;
    setclientlayout(m, arg->i);
    if (m->sel) arrange(m);
    else drawbar(m);
}

/* arg > 1.0 will set mfact absolutely */
void
SetMonitorFact(const Arg *arg)
{
    float f;

    if (!arg || !selmon->lt[selmon->sellt]->arrange) return;
    f = arg->f < 1.0 ? arg->f + selmon->mfact : arg->f - 1.0;
    if (f < 0.05 || f > 0.95) return;
    selmon->mfact = f;
    arrange(selmon);
}

void
SpawnWindow(const Arg *arg)
{
    if (fork() == 0) {
        if (dpy)
            close(ConnectionNumber(dpy));
        setsid();
        execvp(((char **)arg->v)[0], (char **)arg->v);
        die("FATAL ERROR: EXECVP '%s' FAILED:", ((char **)arg->v)[0]);
    }
}
void
MaximizeWindow(const Arg *arg) 
{
    maximize(selmon->wx, selmon->wy, selmon->ww - 2 * CFG_BORDER_PX, selmon->wh - 2 * CFG_BORDER_PX);
}


void
MaximizeWindowVertical(const Arg *arg) {
    maximize(selmon->sel->x, selmon->wy, selmon->sel->w, selmon->wh - 2 * CFG_BORDER_PX);
    selmon->sel->ismax = 0; /* no such thing as vertmax being fully maxed */
}

void
MaximizeWindowHorizontal(const Arg *arg) {
    maximize(selmon->wx, selmon->sel->y, selmon->ww - 2 * CFG_BORDER_PX, selmon->sel->h);
    selmon->sel->ismax = 0; /* no such thing as horzmax being fully maxed */
}
void
AltTab(const Arg *arg)
{
    Monitor *m;
    Client *c;
    int grabbed;
    int listindex;
    int kcodecycle;
    int kcodeswitch;
    struct timespec ts = { .tv_sec = 0, .tv_nsec = 1000000 };

    m = selmon;
    m->altsnext = NULL;
    m->altTabN  = 0;
    m->nTabs    = 0;
    grabbed     = 0;
    listindex   = 0;
    kcodecycle  = CFG_ALT_TAB_CYCLE_KEY;
    kcodeswitch = CFG_ALT_TAB_SWITCH_KEY;
    for(c = m->clients; c; c = c->next) m->nTabs += !!ISVISIBLE(c);
    if(!(m->nTabs > 0)) return;

    m->altsnext = (Client **) malloc(m->nTabs * sizeof(Client *));
    /* add clients to list */
    for(c = m->stack; c; c = c->snext) !!ISVISIBLE(c) ? m->altsnext[listindex++] = c : NULL;

    drawtab(m->nTabs, 1, m);

    for (int i = 0; i < 1000; i++) 
    {
        if (XGrabKeyboard(dpy, DefaultRootWindow(dpy), True, GrabModeAsync, GrabModeAsync, CurrentTime) == GrabSuccess)
        {
            grabbed = 1;
            break;
        }
        nanosleep(&ts, NULL);
    }
    XEvent event;
    alttab();

    while (grabbed) 
    {
        XNextEvent(dpy, &event);
        switch(event.type)
        {case KeyPress:   if(event.xkey.keycode == kcodecycle) alttab();    break;
         case KeyRelease: if(event.xkey.keycode == kcodeswitch)grabbed = 0; break;
        }
    }

    alttabend(); /* end the alt-tab functionality */
    XUngrabKeyboard(dpy, CurrentTime);
}

void
TagWindow(const Arg *arg)
{
    if (selmon->sel && arg->ui & TAGMASK) 
    {
        selmon->sel->tags = arg->ui & TAGMASK;
        focus(NULL);
        arrange(selmon);
    }
}

void
TagMonitor(const Arg *arg)
{
    if (!selmon->sel || !mons->next) return;
    sendmon(selmon->sel, dirtomon(arg->i));
}

void
ToggleStatusBar(const Arg *arg)
{
    selmon->showbar = !selmon->showbar;
    updatebarpos(selmon);
    XMoveResizeWindow(dpy, selmon->barwin, selmon->wx, selmon->by, selmon->ww, bh);
    arrange(selmon);
}

void
ToggleFloating(const Arg *arg)
{
    Client *c; 
    int togglefloat;

    c = selmon->sel;
    togglefloat = 0;
    if (!c) return;
    if (c->isfullscreen) return; /* no support for fullscreen windows */
    togglefloat = !selmon->sel->isfloating || selmon->sel->isfixed;
    if(togglefloat)
    {
        c->isfloating = togglefloat;
        resize(c, c->x, c->y, c->w, c->h, 0);
    }
    arrange(selmon);
}

void
ToggleFullscreen(const Arg *arg)
{
    Client *c;
    Monitor *m;
    int winmode; /* if fullscreen or not */

    m = selmon;
    if(!m->sel) return; /* no client focused */
    m->isfullscreen = !m->isfullscreen;
    winmode = m->isfullscreen;
    for (c = m->clients; c; c = c->next)
    {
        if(!ISVISIBLE(c)) continue;
        setfullscreen(c, winmode);
    }
    focus(m->sel);
    restack(m);
}

void
ToggleTag(const Arg *arg)
{
    unsigned int newtags;

    if (!selmon->sel) return;
    newtags = selmon->sel->tags ^ (arg->ui & TAGMASK);
    if (newtags) {
        selmon->sel->tags = newtags;
        focus(NULL);
        arrange(selmon);
    }
}

void
ToggleView(const Arg *arg)
{
    unsigned int newtagset = selmon->tagset[selmon->seltags] ^ (arg->ui & TAGMASK);

    if (newtagset) {
        selmon->tagset[selmon->seltags] = newtagset;
        focus(NULL);
        arrange(selmon);
    }
}

void
View(const Arg *arg)
{
    if ((arg->ui & TAGMASK) == selmon->tagset[selmon->seltags]) return;
    selmon->seltags ^= 1; /* toggle sel tagset */
    if (arg->ui & TAGMASK)
        selmon->tagset[selmon->seltags] = arg->ui & TAGMASK;
    focus(NULL);
    arrange(selmon);
}

void
Zoom(const Arg *arg)
{
    Client *c = selmon->sel;

    if (!selmon->lt[selmon->sellt]->arrange || !c || c->isfloating) return;
    if (c == nexttiled(selmon->clients) && !(c = nexttiled(c->next))) return;
    pop(c);
}
