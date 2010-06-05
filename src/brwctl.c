/* xwinctrl.c 
Usage: xwinctrl <wid> <command> <args>
*/
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/Xresource.h>
#include <X11/Xutil.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define _NET_WM_STATE_REMOVE        0    /* remove/unset property */
#define _NET_WM_STATE_ADD           1    /* add/set property */
#define _NET_WM_STATE_TOGGLE        2    /* toggle property  */

int map();
int unmap();
int raise();
int focus();
int has_focus();
int activate();
int current();
int show();
int hide();
int pos(int, int);
int size(int, int, int);
int message(char*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long);
unsigned char *property(Window, Atom, long*, Atom*, int*);

Display *dpy;
Window win;
Window root;

int main(int argc, char **argv)
{ 
  char *cmd;
  int i=0, x=0, y=0, width=0, height=0, hint=0;

  if (NULL==(dpy=XOpenDisplay(NULL))) {
    perror(argv[0]);
    exit(1);
  }
  root = XDefaultRootWindow(dpy);
  
  if (argc < 2) {
    fprintf(stderr, "Usage: xwinctrl <wid> [<cmd> [<args>]...]\n");
    exit(1);
  }

  win = (Window)strtol(argv[1], NULL, 0);
  
  for (i=1; i<argc; i++) {
    cmd = argv[i];    

    if (strcmp(cmd, "map") == 0)
      map();
  
    if (strcmp(cmd, "unmap") == 0)
      unmap();

    if (strcmp(cmd, "hide") == 0)
      unmap();

    if (strcmp(cmd, "raise") == 0)
      raise();

    if (strcmp(cmd, "focus") == 0)
      focus();

    if (strcmp(cmd, "focus?") == 0) {
      if (has_focus())
	exit(0);
      else
	exit(1);
    }

    if (strcmp(cmd, "activate") == 0)
      activate();

    if (strcmp(cmd, "current") == 0)
      current();

    if (strcmp(cmd, "show") == 0)
      show();

    if (strcmp(cmd, "pos") == 0) {
      fprintf(stderr, "%d < %d\n", i+2, argc-1);
      if (i+2 > argc-1) {
	fprintf(stderr, "Usage: pos <x> <y>\n");
	exit(1);
      }
      x = (int)strtol(argv[++i], NULL, 0);
      y = (int)strtol(argv[++i], NULL, 0);
      pos(x,y);
    }

    if (strcmp(cmd, "size") == 0) {
      if (i+2 > argc-1) {
	fprintf(stderr, "Usage: size <w> <h>\n");
	exit(1);
      }
      width = (int)strtol(argv[++i], NULL, 0);
      height = (int)strtol(argv[++i], NULL, 0);
      size(width, height, 0);
    }

    if (strcmp(cmd, "sizeh") == 0) {
      if (i+2 > argc-1) {
	fprintf(stderr, "Usage: sizeh <w> <h>\n");
	exit(1);
      }
      width = (int)strtol(argv[++i], NULL, 0);
      height = (int)strtol(argv[++i], NULL, 0);
      size(width, height, 1);
    }
  }
  
  XCloseDisplay(dpy);
  exit(0);
}

int map() {
  int r;
  r = XMapWindow(dpy, win);
  XFlush(dpy);
  return r;
}

int unmap() {
  int r;
  r = XUnmapWindow(dpy, win);
  XFlush(dpy);
  return r;
}

int raise() {
  int r;
  r = XRaiseWindow(dpy, win);
  XFlush(dpy);
  return r;
}

int focus() {
  int r;
  XSetInputFocus(dpy, win, RevertToParent, CurrentTime);
  XFlush(dpy);
  return r;
}

int has_focus() {
  Window focus_return;
  int revert_to_return;
  XGetInputFocus(dpy, &focus_return, &revert_to_return);
  return (win == (Window)focus_return) ? 1 : 0;
}

int activate() {
  int r;
  r = message("_NET_ACTIVE_WINDOW", 2L, 0, 0, 0, 0);
  return r;
}

int current() {
  long nitems;
  Atom type;
  int size;
  long desktop;
  unsigned char *data;

  data = property(root, XInternAtom(dpy, "_NET_CURRENT_DESKTOP", False), 
		  &nitems, &type, &size);

  if (nitems > 0) {
    desktop = *((long*)data);
  } else {
    desktop = -1;
  }
  free(data);

  return message("_NET_WM_DESKTOP", desktop, 2L, 0, 0, 0);
}

int show() {
  map();
  current();
  raise();
  focus();
  activate();
}

int pos(int x, int y) {
  XWindowChanges c;
  int r;

  c.x = x;
  c.y = y;
  r = XConfigureWindow(dpy, win, CWX | CWY, &c);
  XFlush(dpy);
  return r;
}

int size(int width, int height, int hint) {

  XWindowChanges c;
  XSizeHints hints; 
  long ret;
  int flags;
  int r;
  
  memset(&hints, 0, sizeof(hints));

  c.width = width;
  c.height = height;

  if (hint) {

    XGetWMNormalHints(dpy, win, &hints, &ret);
        
    if (ret & PResizeInc) {
      c.width *= hints.width_inc;
      c.height *= hints.height_inc;
    }

    if (ret & PBaseSize) {
      c.width += hints.base_width;
      c.height += hints.base_height;
    }

  }

  if (c.width > 0)
    flags |= CWWidth;
  if (c.height > 0)
    flags |= CWHeight;

  r = XConfigureWindow(dpy, win, flags, &c);
  XFlush(dpy);
  return r;
}

int message(char *msg, 
	    unsigned long data0, 
	    unsigned long data1, 
	    unsigned long data2, 
	    unsigned long data3,
	    unsigned long data4) {

    XEvent event;
    long mask = SubstructureRedirectMask | SubstructureNotifyMask;
    int r;

    event.xclient.type = ClientMessage;
    event.xclient.serial = 0;
    event.xclient.send_event = True;
    event.xclient.message_type = XInternAtom(dpy, msg, False);
    event.xclient.window = win;
    event.xclient.format = 32;
    event.xclient.data.l[0] = data0;
    event.xclient.data.l[1] = data1;
    event.xclient.data.l[2] = data2;
    event.xclient.data.l[3] = data3;
    event.xclient.data.l[4] = data4;
    
    r = XSendEvent(dpy, root, False, mask, &event);
    return r;
}

unsigned char *property(Window w, Atom atom, long *nitems, 
			Atom *type, int *size) {

  Atom actual_type;
  int actual_format;
  unsigned long _nitems;
  unsigned long nbytes;
  unsigned long bytes_after;
  unsigned char *property;
  int r;

  r = XGetWindowProperty(dpy, w, atom, 0, (~0L), False, 
			 AnyPropertyType, &actual_type,
			 &actual_format, &_nitems, 
			 &bytes_after, &property);

  if (r != Success) {
    fprintf(stderr, "XGetWindowProperty failed.");
    return NULL;
  }

  if (actual_format == 32)
    nbytes = sizeof(long);
  else if (actual_format == 16)
    nbytes = sizeof(short);
  else if (actual_format == 8)
    nbytes = 1;
  else if (actual_format == 0)
    nbytes = 0;

  *nitems = _nitems;
  *type = actual_type;
  *size = actual_format;

  return property;
}
