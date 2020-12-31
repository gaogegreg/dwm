/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Fira Code:size=14" };
static const char dmenufont[]       = "Fira Code:size=14";
//background colour
static const char col_gray1[]       = "#000000";
//inactive window border colour
static const char col_gray2[]       = "#7320D2";
//font color
static const char col_gray3[]       = "#7320D2";
//current tag and current window font colour
static const char col_gray4[]       = "#00AD00";
//top bar bacground colour and active window border colour
static const char col_cyan[]        = "#000000";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_cyan },
	[SchemeSel]  = { col_gray4, col_cyan,  col_gray2  },
	[SchemeTitle]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "", "", "", "", "", "", "", "", "" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       6 << 6,       0,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "",      tile },    /* first entry is default */
	{ "",      NULL },    /* no layout function means floating behavior */
	{ "",      monocle },
};

#define TERMINAL "st"
/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *astrill[]  = { "astrill", NULL };
static const char *homepage[]  = { "homepage.sh", NULL };
static const char *pwm[]  = { "pwm2.0", NULL };
static const char *bookmarks[]  = { "bookmark.sh", NULL };
static const char *bright20[]  = { "bright20", NULL };
static const char *bright40[]  = { "bright40", NULL };
static const char *bright60[]  = { "bright60", NULL };
static const char *bright80[]  = { "bright80", NULL };
static const char *screenshot[]  = { "screenshot", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,             		XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_i,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,	             	XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY, 	            	XK_n, 	   spawn,	   SHCMD(TERMINAL " -e nnn -e")},
	{ MODKEY, 	            	XK_4, 	   spawn,	   SHCMD(TERMINAL " -e nnn -e")},
	{ MODKEY, 	            	XK_v, 	   spawn,	   {.v = astrill } },
	{ 0, 	        		0x1008ff13,  spawn,	   SHCMD("volumeup.sh; pkill -RTMIN+10 dwmblocks") },
	{ 0, 	        		0x1008ff11,  spawn,	   SHCMD("volumedown.sh; pkill -RTMIN+10 dwmblocks") },
	{ 0, 	        		0x1008ff12,  spawn,	   SHCMD("mute.sh; pkill -RTMIN+10 dwmblocks") },
/*	{ 0, 	        		0x1008ffb2,  spawn,	   {.v = micmute } },*/
	{ 0, 	        		0x1008ff02,  spawn,	   {.v = bright40 } },
	{ MODKEY, 	        	0x1008ff02,  spawn,	   {.v = bright80 } },
	{ 0, 	        		0x1008ff03,  spawn,	   {.v = bright20 } },
	{ MODKEY, 	        	0x1008ff03,  spawn,	   {.v = bright60 } },
	{ MODKEY, 	        	XK_s, 	     spawn,	   {.v = screenshot } },
	{ MODKEY, 	            	XK_2, 	   spawn,	   {.v = homepage } },
	{ MODKEY, 	            	XK_p, 	   spawn,	   {.v = pwm } },
	{ MODKEY|Mod4Mask, 	        XK_b, 	   spawn,	   {.v = bookmarks } },
	{ MODKEY|ControlMask,           XK_h, 	   shiftview,       {.i = -1 } },
	{ MODKEY|ControlMask,           XK_l, 	   shiftview,       {.i = +1 } },
	{ MODKEY|ControlMask,           XK_Left,   shiftview,       {.i = -1 } },
	{ MODKEY|ControlMask,           XK_Right,  shiftview,       {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_s,      quit,           {0} },
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
};

