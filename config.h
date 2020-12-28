/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const unsigned int gappx     = 10;        /* gaps between windows */
static const int topbar             = 0;        /* 0 means bottom bar */
/*  Display modes of the tab bar: never shown, always shown, shown only in  */
/*  monocle mode in the presence of several windows.                        */
/*  Modes after showtab_nmodes are disabled.                                */
enum showtab_modes { showtab_never, showtab_auto, showtab_nmodes, showtab_always};
static const int showtab			= showtab_auto;        /* Default tab bar show mode */
static const int toptab				= True;               /* False means bottom tab bar */
//static const char *fonts[]          = { "Hack:style=Regular:pixelsize=14" };
static const char *fonts[]          = {"Hack Nerd Font:style=Regular:pixelsize=10:antialias=true:hinting=true" };
static const char dmenufont[]       = "Hack Nerd Font:style=Regular:pixelsize=10";
//static const char col_gray1[]       = "#2e3440";
static const char col_gray1[]       = "#70A9A1";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#d8dee9";
static const char col_gray4[]       = "#CFE0C3";
static const char col_cyan[]        = "#A833B9";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray2, col_gray1 },
	[SchemeSel]  = { col_gray4, col_gray1,  col_gray4  },
	[SchemeStatus]  = { col_gray3, col_cyan,  "#000000"  }, // Statusbar right {text,background,not used but cannot be empty}
	[SchemeTagsSel]  = { "#ffffff", col_gray1,  "#000000"  }, // Tagbar left selected {text,background,not used but cannot be empty}
	[SchemeTagsNorm]  = { col_gray4, col_gray1,  "#000000"  }, // Tagbar left unselected {text,background,not used but cannot be empty}
	[SchemeInfoSel]  = { col_gray2, col_gray4,  "#000000"  }, // infobar middle  selected {text,background,not used but cannot be empty}
	[SchemeInfoNorm]  = { col_gray3, col_gray4,  "#000000"  }, // infobar middle  unselected {text,background,not used but cannot be empty}
 };


/* tagging */
static const char *tags[] = { "1:", "2:", "3:", "4:辶", "5:", "6:", "7:", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      		instance     	 title       tags mask     isfloating   monitor */
	{ "Firefox",  		NULL,        	 NULL,       1 << 1,       0,           -1 },
	{ NULL, 		"music",     	 "ncmpcpp",  1 << 2,       0,           -1 },
	{ "Alacritty",      	"Alacritty",   	 NULL,       1 << 0,       0,           -1 },
	{ "Alacritty", 		"float", 	 "temporary",0,            1,           -1 },
	{ "mpv",      		"xv",        	 NULL,       1 << 3,       1,           -1 },
	{ "libreoffice",	NULL,	 	 NULL,       1 << 4,       0,           -1 },
	{ "qBittorrent", 	"qbittorrent",	 NULL,       1 << 5,       0,           -1 },
	{ "VirtualBox Manager",	"Virtualbox Manager",	 NULL,       1 << 6,       0,   -1 },
	{ "VirtualBox Machine",	"Virtualbox Machine",	 NULL,       1 << 6,       0,   -1 },
	{ "Sxiv", 		"sxiv",	 	 "sxiv",       0,            1,         -1 },
	{ NULL, 		NULL,	 	 "pulsemixer",       0,            1,         -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

#include "fibonacci.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
 	{ "[@]",      spiral },
 	{ "[\\]",      dwindle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define ALTKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray2, "-sb", col_gray1, "-sf", col_gray2, "-b", "-p", "Dango: " , "-i", NULL };
static const char *termcmd[]  = { "st", NULL };
#include "unfloat.c"
static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY, 	                XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_w,      tabmode,        {-1} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_g, 	   zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_r,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY|ShiftMask,             XK_r,      setlayout,      {.v = &layouts[4]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
//	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY|ShiftMask, 		XK_space,  unfloatvisible, {0} },
	{ MODKEY|ShiftMask, 		XK_t,      unfloatvisible, {.v = &layouts[1]} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -1 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{MODKEY|ShiftMask,             XK_q,      quit,           {1} },
	{MODKEY|ControlMask|ShiftMask, XK_q,      quit,           {0} }, 
/*------------------------CustomeKey--------------------------*/
	{0,XF86XK_AudioMute,	 	spawn, SHCMD("pactl set-sink-mute @DEFAULT_SINK@ toggle")},
	{0,XF86XK_AudioLowerVolume,	spawn, SHCMD("pactl set-sink-volume @DEFAULT_SINK@ -5%")},
	{0,XF86XK_AudioRaiseVolume,	spawn, SHCMD("pactl set-sink-volume @DEFAULT_SINK@ +5%")},
	{0,XF86XK_Launch1,		spawn, SHCMD("st -e pulsemixer")},
	{0,XF86XK_MonBrightnessUp,	spawn, SHCMD("xbacklight -inc 5%")},
	{0,XF86XK_MonBrightnessDown,	spawn, SHCMD("xbacklight -dec 5%")},
	{0,XF86XK_AudioPlay,		spawn, SHCMD("mpc toggle")},
	{0,XF86XK_AudioNext,		spawn, SHCMD("mpc next")},
	{0,XF86XK_AudioPrev,		spawn, SHCMD("mpc prev")},
//	{0,XF86XK_AudioLowerVolume,	spawn, SHCMD("mixer vol -5")},
//	{0,XF86XK_AudioRaiseVolume,	spawn, SHCMD("mixer vol +5")},
	{MODKEY|ShiftMask,	 	XK_m, spawn , SHCMD("st -T 'ncmpcpp' -t 'music' -e $HOME/.local/dot/myscript/ncmpcpp.sh")}, 
	{MODKEY|ShiftMask,     	        XK_Return, spawn, SHCMD("alacritty --class float,Alacritty -t temporary")          },
	{MODKEY|ShiftMask,     	        XK_w, spawn, SHCMD("firefox -p")},
	{MODKEY|ShiftMask,     	        XK_f, spawn, SHCMD("alacritty --class float,Alacritty -t temporary -e lf")},
	{MODKEY|ALTKEY,	 		XK_s, spawn , SHCMD("sxiv -t $HOME/.local/dot/wals")}, 
	{MODKEY|ALTKEY,     	        XK_y, spawn, SHCMD("$HOME/.local/dot/myscript/getmp3.sh")},
	{MODKEY|ALTKEY,     	        XK_p, spawn, SHCMD("$HOME/.local/dot/myscript/picom.sh")},
	{MODKEY|ALTKEY,     	        XK_o, spawn, SHCMD("SUDO_ASKPASS=$HOME/.local/dot/myscript/dpass.sh sudo -A $HOME/.local/dot/myscript/openvpn.sh")},
	{MODKEY|ALTKEY,     	        XK_F9, spawn, SHCMD("$HOME/.local/dot/myscript/redshift.sh")          },

};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ ClkTabBar,            0,              Button1,        focuswin,       {0} },
};

