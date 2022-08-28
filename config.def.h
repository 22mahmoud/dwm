/* See LICENSE file for copyright and license details. */

#define TERMCLASS "St"
#define MODKEY Mod4Mask

/* appearance */
static unsigned int borderpx  = 1;        /* border pixel of windows */
static unsigned int snap      = 32;       /* snap pixel */
static int showbar            = 1;        /* 0 means no bar */
static int topbar             = 1;        /* 0 means bottom bar */
static char font[]            = "monospace 10";
static int showvacant         = 0;
static int showtitle          = 1;
static const int vertpad            = 10;       /* vertical padding of bar */
static const int sidepad            = 10;       /* horizontal padding of bar */
static const int horizpadbar        = 15;        /* horizontal padding for statusbar */
static const int vertpadbar         = 10;        /* vertical padding for statusbar */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const Gap default_gap        = {.isgap = 1, .realgap = 10, .gappx = 10};

static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;   	/* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const unsigned int systrayiconsize = 20; /* systray icon size in px */
static const int showsystray        = 1;     /* 0 means no systray */

/* 
 * Theme colors
 * use base16 as guide line for theming
 * default: base16 gruvbox dark hard
 * */
static char col_base00[]  = "#1d2021"; /* Default Background */
static char col_base01[]  = "#3c3836"; /* Lighter Background (Used for status bars, line number and folding marks) */
static char col_base02[]  = "#504945"; /* Selection Background */
static char col_base03[]  = "#665c54"; /* Comments, Invisibles, Line Highlighting */
static char col_base04[]  = "#bdae93"; /* Dark Foreground (Used for status bars) */
static char col_base05[]  = "#d5c4a1"; /* Default Foreground, Caret, Delimiters, Operators */
static char col_base06[]  = "#ebdbb2"; /* Light Foreground (Not often used) */
static char col_base07[]  = "#fbf1c7"; /* Light Background (Not often used) */
static char col_base08[]  = "#fb4934"; /* Variables, XML Tags, Markup Link Text, Markup Lists, Diff Deleted */
static char col_base09[]  = "#fe8019"; /* Integers, Boolean, Constants, XML Attributes, Markup Link Url */
static char col_base0A[]  = "#fabd2f"; /* Classes, Markup Bold, Search Text Background */
static char col_base0B[]  = "#b8bb26"; /* Strings, Inherited Class, Markup Code, Diff Inserted */
static char col_base0C[]  = "#8ec07c"; /* Support, Regular Expressions, Escape Characters, Markup Quotes */
static char col_base0D[]  = "#83a598"; /* Functions, Methods, Attribute IDs, Headings */
static char col_base0E[]  = "#d3869b"; /* Keywords, Storage, Selector, Markup Italic, Diff Changed */
static char col_base0F[]  = "#d65d0e"; /* Deprecated, Opening/Closing Embedded Language Tags, e.g. <?php ?> */
static char *colors[][3]      = {
  /* C(Name,              bg,           fg,           border    ), */
    C(SchemeNorm,         col_base04,   col_base00,   col_base02),
    C(SchemeSel,          col_base04,   col_base00,   col_base0C),

    C(SchemeTitle,        col_base04,   col_base00,   col_base0C),
    C(SchemeTitleFloat,   col_base04,   col_base00,   col_base0C),

    C(SchemeBar,          col_base04,   col_base01,   col_base00),
    C(SchemeTag,          col_base04,   col_base00,   col_base00),

    C(SchemeTag1,         col_base0A,   col_base00,   col_base00),
    C(SchemeTag2,         col_base0B,   col_base00,   col_base00),
    C(SchemeTag3,         col_base0C,   col_base00,   col_base00),
    C(SchemeTag4,         col_base0D,   col_base00,   col_base00),
    C(SchemeTag5,         col_base0E,   col_base00,   col_base00),
    C(SchemeTag6,         col_base0F,   col_base00,   col_base00),
    C(SchemeTag7,         col_base08,   col_base00,   col_base00),
    C(SchemeTag8,         col_base09,   col_base00,   col_base00),
    C(SchemeTag9,         col_base0C,   col_base00,   col_base00),
};

static char termcol0[] = "#1d2021"; /* black   */
static char termcol1[] = "#fb4934"; /* red     */
static char termcol2[] = "#b8bb26"; /* green   */
static char termcol3[] = "#fabd2f"; /* yellow  */
static char termcol4[] = "#83a598"; /* blue    */
static char termcol5[] = "#d3869b"; /* magenta */
static char termcol6[] = "#8ec07c"; /* cyan    */
static char termcol7[] = "#d5c4a1"; /* white   */
static char termcol8[]  = "#665c54"; /* black   */
static char termcol9[]  = "#fb4934"; /* red     */
static char termcol10[] = "#b8bb26"; /* green   */
static char termcol11[] = "#fabd2f"; /* yellow  */
static char termcol12[] = "#d3869b"; /* blue    */
static char termcol13[] = "#d3869b"; /* magenta */
static char termcol14[] = "#8ec07c"; /* cyan    */
static char termcol15[] = "#fbf1c7"; /* white   */
static char *termcolor[] = {
  termcol0,
  termcol1,
  termcol2,
  termcol3,
  termcol4,
  termcol5,
  termcol6,
  termcol7,
  termcol8,
  termcol9,
  termcol10,
  termcol11,
  termcol12,
  termcol13,
  termcol14,
  termcol15,
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
static const char *tags[] = { "", "", "", "" , "", "", "", "", "" };
static const char *tagsalt[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
static const int momentaryalttags = 0; /* 1 means alttags will show only when key is held down*/

static const int tagschemes[] = {
  SchemeTag1, SchemeTag2, SchemeTag3,
  SchemeTag4, SchemeTag5, SchemeTag6,
  SchemeTag7, SchemeTag8, SchemeTag9
};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	RULE(.class = TERMCLASS, .isterminal = 1, .noswallow = 1),

	SCRATCH_RULE(.instance = "spterm", .tags = SPTAG(0)),
	SCRATCH_RULE(.instance = "spfm",   .tags = SPTAG(1)),
	SCRATCH_RULE(.instance = "spcalc", .tags = SPTAG(2)),
	SCRATCH_RULE(.instance = "sphtop", .tags = SPTAG(3)),

	RULE(.class = "qutebrowser", .tags = 1 << 0, .noswallow = 1),
  RULE(.title = "mpv", .tags = 1 << 4),
  RULE(.title = "neomuttTerm", .tags = 1 << 5),
  RULE(.title = "newsboatTerm", .tags = 1 << 6),
  RULE(.class = "TelegramDesktop", .tags = 1 << 7),
  RULE(.class = "Slack", .tags = 1 << 7),
  RULE(.class = "discord", .tags = 1 << 7),
  RULE(.title = "Discord Updater", .tags = 1 << 7, .isfloating = 1),
  RULE(.class = "Spotify", .tags = 1 << 8),

  RULE(.class = "Steam", .tags = 1 << 3),
  RULE(.title = "Steam", .tags = 1 << 3),
  RULE(.class = "Steam", .title = "Friends List", .isfloating = 1, .tags = 1 << 3),
  RULE(.class = "Bottles", .tags = 1 << 3),

  RULE(.title = "Event Tester", .isfloating = 1, .noswallow = 1),
};

/* layout(s) */
static float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static int nmaster     = 1;    /* number of clients in master area */
static int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

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
    { "color1",       STRING,   &col_base08 },
    { "color2",       STRING,   &col_base0B },
    { "color3",       STRING,   &col_base0A },
    { "color4",       STRING,   &col_base0D },
    { "color5",       STRING,   &col_base0E },
    { "color6",       STRING,   &col_base0C },
    { "color7",       STRING,   &col_base05 },
    { "color8",       STRING,   &col_base03 },
    { "color9",       STRING,   &col_base09 },
    { "color10",      STRING,   &col_base01 },
    { "color11",      STRING,   &col_base02 },
    { "color12",      STRING,   &col_base04 },
    { "color13",      STRING,   &col_base06 },
    { "color14",      STRING,   &col_base0F },
    { "color15",      STRING,   &col_base07 },

    { "color0",       STRING,  &termcol0    },
    { "color1",       STRING,  &termcol1    },
    { "color2",       STRING,  &termcol2    },
    { "color3",       STRING,  &termcol3    },
    { "color4",       STRING,  &termcol4    },
    { "color5",       STRING,  &termcol5    },
    { "color6",       STRING,  &termcol6    },
    { "color7",       STRING,  &termcol7    },
    { "color8",       STRING,  &termcol8    },
    { "color1",       STRING,  &termcol9    },
    { "color2",       STRING,  &termcol10   },
    { "color3",       STRING,  &termcol11   },
    { "color4",       STRING,  &termcol12   },
    { "color5",       STRING,  &termcol13   },
    { "color6",       STRING,  &termcol14   },
    { "color15",      STRING,  &termcol15   },
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
static const Button buttons[] = {
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
  IPCCOMMAND(  view,                  1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  toggleview,            1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  tag,                   1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  toggletag,             1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  tagmon,                1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  focusmon,              1,      {ARG_TYPE_SINT}   ),
  IPCCOMMAND(  focusstack,            1,      {ARG_TYPE_SINT}   ),
  IPCCOMMAND(  zoom,                  1,      {ARG_TYPE_NONE}   ),
  IPCCOMMAND(  togglefullscreen,      1,      {ARG_TYPE_NONE}   ),
  IPCCOMMAND(  togglefakefullscreen,  1,      {ARG_TYPE_NONE}   ),
  IPCCOMMAND(  togglesticky,          1,      {ARG_TYPE_NONE}   ),
  IPCCOMMAND(  incnmaster,            1,      {ARG_TYPE_SINT}   ),
  IPCCOMMAND(  killclient,            1,      {ARG_TYPE_SINT}   ),
  IPCCOMMAND(  togglefloating,        1,      {ARG_TYPE_NONE}   ),
  IPCCOMMAND(  setmfact,              1,      {ARG_TYPE_FLOAT}  ),
  IPCCOMMAND(  setlayoutsafe,         1,      {ARG_TYPE_PTR}    ),
  IPCCOMMAND(  viewall,               1,      {ARG_TYPE_NONE}   ),
  IPCCOMMAND(  setgaps,               1,      {ARG_TYPE_SINT}   ),
	IPCCOMMAND(  togglescratch,         1,      {ARG_TYPE_UINT}   ),
	IPCCOMMAND(  xrdb,                  1,      {ARG_TYPE_NONE}   ),
  IPCCOMMAND(  quit,                  1,      {ARG_TYPE_NONE}   ),
  IPCCOMMAND(  togglealttag,          1,      {ARG_TYPE_NONE}   )
};

