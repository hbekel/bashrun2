#define _NET_WM_STATE_REMOVE 0
#define _NET_WM_STATE_ADD 1
#define _NET_WM_STATE_TOGGLE 2

static int map();
static int unmap();
static int is_mapped();
static int raise();
static int focus();
static int has_focus();
static Window get_focused();
static int activate();
static int current();
static int show();
static int pos(int, int);
static int size(int, int, int);
static int state(char*, char*);
static int get_class();
static int search_window(char*, Window);
static int message(Window, char*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long);
static unsigned char *property(Window, Atom, long*, Atom*, int*);
static int bad_window(Display*, XErrorEvent*);

Display *dpy;
Window win;
char *classname;
Window root;
