/* See LICENSE file for copyright and license details. */

/* appearance */
static const char font[]            =
  "-*-stlarch-*-*-*-*-16-*-*-*-*-*-*-*"
  ","
  "-*-tamzen-medium-r-*-*-14-*-*-*-*-*-*-*"
  ","
  "-*-fixed-medium-r-*-*-13-*-*-*-*-*-*-*";
static const char normbordercolor[] = "#434443"; /* Zenburn CursorLine */
static const char normbgcolor[]     = "#3f3f3f"; /* Zenburn Normal */
static const char normfgcolor[]     = "#dcdccc"; /* Zenburn Normal */
static const char selbordercolor[]  = "#8cd0d3"; /* Zenburn CursorColumn */
static const char selbgcolor[]      = "#333333"; /* Zenburn DiffChange */
static const char selfgcolor[]      = "#8cd0d3"; /* Zenburn Number */
static const unsigned int borderpx  = 2;         /* border pixel of windows */
static const unsigned int snap      = 32;        /* snap pixel */
static const Bool showbar           = True;      /* False means no bar */
static const Bool topbar            = False;     /* False means bottom bar */
static const unsigned int bottomgap = 16;

/* tagging */

static const char *tags[] = {"","","","","","","","",""};

static const Rule rules[] = {
  /* class,        instance,   title,            tags mask,                           isfloating,  monitor */
  { "XWrits",      NULL,       NULL,             ~0,                                  True,        -1 },
  { NULL,          "DIALOG",   NULL,             0,                                   True,        -1 },
  { NULL/*xev*/,   NULL,       "Event Tester",   0,                                   True,        -1 },
  { "XFontSel",    NULL,       NULL,             0,                                   True,        -1 },
  { "Xmessage",    NULL,       NULL,             0,                                   True,        -1 },
  { "Xmag",        NULL,       NULL,             0,                                   True,        -1 },
  { "XmBDFEdit",   NULL,       NULL,             0,                                   True,        -1 },
  { "Display",     NULL,       NULL,             0,                                   True,        -1 },
  { "Gimp",        NULL,       NULL,             0,                                   True,        -1 },
  { "MPlayer",     NULL,       NULL,             0,                                   True,        -1 },
  { "trayer",      NULL,       NULL,             1,                                   True,        -1 },
  { "Claws-mail",  NULL,       NULL,             1 << 1,   False,       -1 },
  { "Liferea",     NULL,       NULL,             1 << 2,   False,       -1 },
  { "Zim",         NULL,       NULL,             1 << 5,   False,       -1 },
  { "Skype",       NULL,       NULL,             1 << 3,   False,       -1 },
  { "Pidgin",      NULL,       NULL,             1 << 3,   False,       -1 },
  { "rdesktop",    NULL,       NULL,             1 << 8,   False,       -1 },
  { "Vncviewer",   NULL,       NULL,             1 << 8,   False,       -1 },
};

/* layout(s) */
static const float mfact      = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster      = 1;    /* number of clients in master area */
static const Bool resizehints = False; /* True means respect size hints in tiled resizals */

#include "grid.c"
#include "fibonacci.c"
#include "bstack.c"
#include "bstackhoriz.c"

/* first entry is default */
/* no layout function means floating behavior */

static const Layout layouts[] = {{"", tile},{"", NULL},{"", monocle},{"", grid},{"", dwindle},{"", spiral},{"", bstack},{"", bstackhoriz}};

/* key definitions */
#define MODKEY Mod4Mask
#define ALTKEY Mod1Mask
#define TAGKEYS(KEY,TAG)																								\
  { MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
  { MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
  { MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
  { MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/bash", "-c", cmd, NULL } }

/* commands */
static const char *dmenucmd[] = { "/usr/bin/dmenu_run", "-fn", font, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };

static const char *termcmd[] = { "urxvt", NULL };
static const char *browser_cmd[] = { "google-chrome", NULL };
static const char *filer_cmd[] = { "nautilus", NULL };
static const char *editor_cmd[] = { "emacs-24.0.92 -nw -l ~/.emacs.d/min-init.el", NULL };
static const char *lockcmd[]       = { "slock", NULL };
static const char *suspendcmd[]    = { "dbus-send", "--system", "--print-reply", "--dest=org.freedesktop.UPower", "/org/freedesktop/UPower",
"org.freedesktop.UPower.Suspend", NULL };
static const char *hibernatecmd[]  = { "dbus-send", "--system", "--print-reply", "--dest=org.freedesktop.UPower", "/org/freedesktop/UPower",
"org.freedesktop.UPower.Hibernate", NULL };
static const char *rebootcmd[]     = { "dbus-send", "--system", "--print-reply", "--dest=org.freedesktop.ConsoleKit", "/org/freedesktop/ConsoleKit/Manager",
"org.freedesktop.ConsoleKit.Manager.Restart", NULL };
static const char *shutdowncmd[]   = { "dbus-send", "--system", "--print-reply", "--dest=org.freedesktop.ConsoleKit", "/org/freedesktop/ConsoleKit/Manager",
"org.freedesktop.ConsoleKit.Manager.Stop", NULL };

#include "movestack.c"
#include "shiftview.c"
static Key keys[] = {
  /* modifier,                     key,               function,        argument */
  { MODKEY,                        XK_e,              spawn,           {.v = dmenucmd } },
  { MODKEY,                        XK_x,              spawn,           {.v = termcmd } },
  { MODKEY,                        XK_k,              spawn,           {.v = browser_cmd } },
  { MODKEY,                        XK_j,              spawn,           {.v = filer_cmd } },
  { MODKEY,                        XK_q,              spawn,           {.v = editor_cmd } },
	{ ControlMask|ALTKEY,            XK_l,              spawn,      		 {.v = lockcmd } },
	{ ControlMask|ALTKEY,						 XK_s,							spawn,					 {.v = suspendcmd } },
	{ ControlMask|ALTKEY,						 XK_h,							spawn,					 {.v = hibernatecmd } },
	{ ControlMask|ALTKEY,						 XK_r,							spawn,					 {.v = rebootcmd } },
	{ ControlMask|ALTKEY,						 XK_q,							spawn,					 {.v = shutdowncmd } },
	{ MODKEY|ShiftMask,							 XK_m,							togglebar,	     {0} },
  { MODKEY,                        XK_n,              focusstack,      {.i = +1 } },
  { MODKEY,                        XK_t,              focusstack,      {.i = -1 } },
  { MODKEY|ControlMask,            XK_n,              movestack,       {.i = +1 } },
  { MODKEY|ControlMask,            XK_t,              movestack,       {.i = -1 } },
  { MODKEY,                        XK_i,              incnmaster,      {.i = +1 } },
  { MODKEY,                        XK_u,              incnmaster,      {.i = -1 } },
  { MODKEY|ControlMask,            XK_h,              setmfact,        {.f = -0.05} },
  { MODKEY|ControlMask,            XK_s,              setmfact,        {.f = +0.05} },
  { MODKEY,                        XK_Return,         zoom,            {0} },
  { MODKEY,                        XK_o,              view,            {0} },
  { MODKEY,                        XK_z,              setlayout,       {.v = &layouts[1]} },
  { MODKEY,                        XK_g,              setlayout,       {.v = &layouts[3]} },
  { MODKEY,                        XK_c,              setlayout,       {.v = &layouts[5]} },
  { MODKEY,                        XK_r,              setlayout,       {.v = &layouts[4]} },
  { MODKEY,                        XK_l,              setlayout,       {.v = &layouts[0]} },
  { MODKEY,                        XK_m,              setlayout,       {.v = &layouts[2]} },
  { MODKEY,                        XK_w,              setlayout,       {.v = &layouts[6]} },
  { MODKEY,                        XK_v,              setlayout,       {.v = &layouts[7]} },
  { MODKEY,                        XK_space,          setlayout,       {0} },
  { MODKEY|ShiftMask,              XK_space,          togglefloating,  {0} },
  { MODKEY,                        XK_0,              view,            {.ui = ~0 } },
  { MODKEY|ControlMask,            XK_0,              view,            {.ui = 0 } },
  { MODKEY|ShiftMask,              XK_0,              tag,             {.ui = ~0 } },
  { MODKEY|ControlMask|ShiftMask,  XK_0,              tag,             {.ui = 0 } },/*TODO*/
  { MODKEY,                        XK_Delete,         killclient,      {0} },
  { MODKEY,                        XK_bracketleft,    focusmon,        {.i = -1 } },
  { MODKEY,                        XK_bracketright,   focusmon,        {.i = +1 } },
  { MODKEY|ShiftMask,              XK_bracketleft,    tagmon,          {.i = -1 } },
  { MODKEY|ShiftMask,              XK_bracketright,   tagmon,          {.i = +1 } },
  { MODKEY,                        XK_comma,          shiftview,       {.i = -1 } },
  { MODKEY,                        XK_period,         shiftview,       {.i = +1 } },
  /* Resize windows */
  { ALTKEY,                        XK_Down,           moveresize,      {.v = (int []){ 0, 25, 0, 0 }}},
  { ALTKEY,                        XK_Up,             moveresize,      {.v = (int []){ 0, -25, 0, 0 }}},
  { ALTKEY,                        XK_Right,          moveresize,      {.v = (int []){ 25, 0, 0, 0 }}},
  { ALTKEY,                        XK_Left,           moveresize,      {.v = (int []){ -25, 0, 0, 0 }}},
  { ALTKEY|ShiftMask,              XK_Down,           moveresize,      {.v = (int []){ 0, 0, 0, 25 }}},
  { ALTKEY|ShiftMask,              XK_Up,             moveresize,      {.v = (int []){ 0, 0, 0, -25 }}},
  { ALTKEY|ShiftMask,              XK_Right,          moveresize,      {.v = (int []){ 0, 0, 25, 0 }}},
  { ALTKEY|ShiftMask,              XK_Left,           moveresize,      {.v = (int []){ 0, 0, -25, 0 }}},
  TAGKEYS(XK_1,                    0)
  TAGKEYS(XK_2,                    1)
  TAGKEYS(XK_3,                    2)
  TAGKEYS(XK_4,                    3)
  TAGKEYS(XK_5,                    4)
  TAGKEYS(XK_6,                    5)
  TAGKEYS(XK_7,                    6)
  TAGKEYS(XK_8,                    7)
  TAGKEYS(XK_9,                    8)
  { MODKEY|ControlMask,            XK_BackSpace,      quit,            {0} },
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
  /* click,         event mask,   button,    function,        argument */
  { ClkLtSymbol,    0,            Button1,   setlayout,       {0} },
  { ClkLtSymbol,    0,            Button3,   setlayout,       {.v = &layouts[1]} },
  { ClkWinTitle,    0,            Button2,   zoom,            {0} },
  { ClkStatusText,  0,            Button2,   spawn,           {.v = termcmd } },
  { ClkClientWin,   MODKEY,       Button1,   movemouse,       {0} },
  { ClkClientWin,   MODKEY,       Button2,   togglefloating,  {0} },
  { ClkClientWin,   MODKEY,       Button3,   resizemouse,     {0} },
  { ClkTagBar,      0,            Button1,   view,            {0} },
  { ClkTagBar,      0,            Button3,   toggleview,      {0} },
  { ClkTagBar,      MODKEY,       Button1,   tag,             {0} },
  { ClkTagBar,      MODKEY,       Button3,   toggletag,       {0} },
};
