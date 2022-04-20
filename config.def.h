/* See LICENSE file for copyright and license details. */

#define TERMCLASS "St"
#define MODKEY Mod4Mask

/* appearance */
static unsigned int borderpx  = 1;        /* border pixel of windows */
static unsigned int snap      = 32;       /* snap pixel */
static int showbar            = 1;        /* 0 means no bar */
static int topbar             = 1;        /* 0 means bottom bar */
static char font[]            = "monospace 10";
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const Gap default_gap        = {.isgap = 1, .realgap = 10, .gappx = 10};

static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;   	/* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */

/* default base16-gruvbox theme */
static char col_base00[]      = "#1d2021";
static char col_base01[]      = "#3c3836";
static char col_base02[]      = "#504945";
static char col_base04[]      = "#bdae93";
static char col_base0C[]      = "#8ec07c";
static char col_base0D[]      = "#83a598";
static char *colors[][3]      = {
  [SchemeNorm] = { col_base04, col_base01, col_base02 },
  [SchemeSel]  = { col_base00, col_base0D, col_base0C },
};

typedef struct {
	const char *name;
	const void *cmd;
} Sp;

const char *spcmd1[] = {"st", "-n", "spterm", "-g", "100x34", NULL };
const char *spcmd2[] = {"st", "-n", "spfm", "-g", "120x34", "-e", "nnn", "-c", NULL };
const char *spcmd3[] = {"st", "-n", "spcalc", "-f", "monospace:size=16", "-g", "50x20", "-e", "bc", "-ql", NULL };
const char *spcmd4[] = {"st", "-n", "sphtop", "-g", "150x34", "-e", "htop", NULL };
static Sp scratchpads[] = {
	/* name          cmd  */
	{"spterm",   spcmd1},
	{"spfm",     spcmd2},
	{"spcalc",   spcmd3},
	{"sphtop",   spcmd4},
};
static const XPoint stickyicon[]    = { {0,0}, {4,0}, {4,8}, {2,6}, {0,8}, {0,0} }; /* represents the icon as an array of vertices */
static const XPoint stickyiconbb    = {4,8};	/* defines the bottom right corner of the polygon's bounding box (speeds up scaling) */

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class            instance         title             tags mask   isfloating  isterminal   noswallow   monitor */
	{ TERMCLASS,        NULL,            NULL,             0,          0,          1,           0,          -1 },
	{ NULL,		         "spterm",	       NULL,		         SPTAG(0),	 1,			     1,           1,          -1 },
	{ NULL,		         "spfm",		       NULL,		         SPTAG(1),	 1,			     1,           1,          -1 },
	{ NULL,		         "spcalc",	       NULL,		         SPTAG(2),	 1,			     1,           1,          -1 },
	{ NULL,		         "sphtop",	       NULL,		         SPTAG(3),	 1,			     1,           1,          -1 },
	{ NULL,             NULL,           "Event Tester",    0,          0,          0,           1,          -1 }, /* xev */
};

/* layout(s) */
static float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static int nmaster     = 1;    /* number of clients in master area */
static int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/*
 * Xresources preferences to load at startup
 */
ResourcePref resources[] = {
    { "color0",       STRING,   &col_base00 },
    { "color10",      STRING,   &col_base01 },
    { "color11",      STRING,   &col_base02 },
    { "color12",      STRING,   &col_base04 },
    { "color6",       STRING,   &col_base0C },
    { "color4",       STRING,   &col_base0D },

		{ "borderpx",     INTEGER,  &borderpx },
		{ "snap",         INTEGER,  &snap },
		{ "showbar",      INTEGER,  &showbar },
		{ "topbar",       INTEGER,  &topbar },
		{ "nmaster",      INTEGER,  &nmaster },
		{ "resizehints",  INTEGER,  &resizehints },
		{ "mfact",      	FLOAT,    &mfact },
};


static Key keys[] = {
	/* modifier                     key           function        argument */
	{ 0,                            0,             NULL,         {0} },

  /* scratchpads becaouse it crashs dwm with ipc */
	{ MODKEY|ShiftMask,            	XK_Return,    togglescratch,  {.ui = 0 } },
	{ MODKEY|ShiftMask,            	XK_n,         togglescratch,  {.ui = 1 } },
	{ MODKEY|ShiftMask,            	XK_m,         togglescratch,  {.ui = 2 } },
	{ MODKEY|ShiftMask,            	XK_h,         togglescratch,  {.ui = 3 } },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button1,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

void
viewall(const Arg *arg)
{
	view(&((Arg){ .ui = ~0 }));
}

static const char *ipcsockpath = "/tmp/dwm.sock";
static IPCCommand ipccommands[] = {
  IPCCOMMAND(  view,                1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  toggleview,          1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  tag,                 1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  toggletag,           1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  tagmon,              1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  focusmon,            1,      {ARG_TYPE_SINT}   ),
  IPCCOMMAND(  focusstack,          1,      {ARG_TYPE_SINT}   ),
  IPCCOMMAND(  zoom,                1,      {ARG_TYPE_NONE}   ),
  IPCCOMMAND(  togglefullscr,       1,      {ARG_TYPE_NONE}   ),
  IPCCOMMAND(  togglesticky,        1,      {ARG_TYPE_NONE}   ),
  IPCCOMMAND(  incnmaster,          1,      {ARG_TYPE_SINT}   ),
  IPCCOMMAND(  killclient,          1,      {ARG_TYPE_SINT}   ),
  IPCCOMMAND(  togglefloating,      1,      {ARG_TYPE_NONE}   ),
  IPCCOMMAND(  setmfact,            1,      {ARG_TYPE_FLOAT}  ),
  IPCCOMMAND(  setlayoutsafe,       1,      {ARG_TYPE_PTR}    ),
  IPCCOMMAND(  viewall,             1,      {ARG_TYPE_NONE}   ),
  IPCCOMMAND(  setgaps,             1,      {ARG_TYPE_SINT}   ),
	IPCCOMMAND(  togglescratch,       1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  quit,                1,      {ARG_TYPE_NONE}   )
};

