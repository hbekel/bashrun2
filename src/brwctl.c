/* brwctl.c: simple window control utility for bashrun */

#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/Xresource.h>
#include <X11/Xutil.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <brwctl.h>

int main(int argc, char **argv)
{ 
  char *cmd;
  int x=0, y=0, ret=0;
  unsigned int width=0, height=0, bw=0, depth=0, i=0, start=1;
  XErrorHandler error_handler;
  
  if (NULL==(dpy=XOpenDisplay(NULL))) {
    perror(argv[0]);
    exit(1);
  }
  root = XDefaultRootWindow(dpy);
  
  if (argc == 1) {
    exit(0);
  }

  if (!isdigit(argv[1][0])) { // search for class->res_name

    ret = search_window(argv[1], root);
    if (ret == 0) { // found a window
      if (argc == 2) { // no more commands?
	printf("%d\n", (int)win);
	exit(ret);
      }
      // start at arg 2
      start=2;
    }
    else { // no window found
      if (strcmp(argv[1], "focused") == 0) {
	printf("%d\n", (int)get_focused());
	exit(0);
      }
      exit(ret);
    }
  }
  else {

    win = (Window)strtol(argv[1], NULL, 0);
  
    /* check if the window exists... */
    error_handler = XSetErrorHandler(bad_window);
    XGetGeometry(dpy, win, &root, &x, &y, &width, &height, &bw, &depth);
    XFlush(dpy);
    (void)XSetErrorHandler(error_handler);
  }

  for (i=start; i<argc; i++) {
    cmd = argv[i];    

    if (strcmp(cmd, "class?") == 0) {
      get_class();
      exit(0);
    }

    if (strcmp(cmd, "map") == 0)
      map();
  
    if (strcmp(cmd, "unmap") == 0)
      unmap();

    if (strcmp(cmd, "mapped?") == 0)
      is_mapped();

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
    
    if (strcmp(cmd, "state") == 0) {
      if (i+2 > argc-1) {
	fprintf(stderr, "Usage: state <add|remove|toggle> <property>\n");
	exit(1);
      }
      state(argv[i+1], argv[i+2]);
    }
  }
  exit(ret);
}

static int map() {
  int r;
  r = XMapWindow(dpy, win);
  XFlush(dpy);
  return r;
}

static int unmap() {
  int r;
  r = XUnmapWindow(dpy, win);
  XFlush(dpy);
  return r;
}

static int is_mapped() {
    XWindowAttributes a;
    XGetWindowAttributes(dpy, win, &a);
    exit(a.map_state == IsUnmapped ? 1 : 0);
}

static int raise() {
  int r;
  r = XRaiseWindow(dpy, win);
  XFlush(dpy);
  return r;
}

static int focus() {
  int r;
  r = XSetInputFocus(dpy, win, RevertToParent, CurrentTime);
  XFlush(dpy);
  return r;
}

static Window get_focused() {
  Window focus_return;
  int revert_to_return;
  XGetInputFocus(dpy, &focus_return, &revert_to_return);
  return (Window)focus_return;
}

static int has_focus() {
  return (win == get_focused()) ? 1 : 0;
}

static int activate() {
  int r;
  r = message(win, "_NET_ACTIVE_WINDOW", 2L, 0, 0, 0, 0);
  return r;
}

static int current() {
  long nitems=0;
  Atom type;
  int size=0;
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

  return message(win, "_NET_WM_DESKTOP", desktop, 2L, 0, 0, 0);
}

static int show() {
  map();
  current();
  raise();
  activate();
  focus();
  return 0;
}

static int pos(int x, int y) {
  XWindowChanges c;
  int r;

  c.x = x;
  c.y = y;
  r = XConfigureWindow(dpy, win, CWX | CWY, &c);
  XFlush(dpy);
  return r;
}

static int size(int width, int height, int hint) {

  XWindowChanges c;
  XSizeHints hints; 
  long ret;
  int flags=0;
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

static int state(char *action_str, char *prop_str) {
  int r = 0;
  int i;
  unsigned long action;
  Atom prop_atom;
  char prop_name[512];

  for(i=0; i<strlen(prop_str); i++) {
    prop_str[i] = toupper(prop_str[i]);
  }
  
  if (strcmp(action_str, "add") == 0) {
    action = _NET_WM_STATE_ADD;
  }
  else if (strcmp(action_str, "remove") == 0) {
    action = _NET_WM_STATE_REMOVE;
  }
  else if (strcmp(action_str, "toggle") == 0) {
    action = _NET_WM_STATE_TOGGLE;
  }
  else {
    exit(1);
  }
  
  if(strcmp(prop_str, "modal") == 0)
    XSetTransientForHint(dpy, win, root);

  snprintf(prop_name, 15+strlen(prop_str), "_NET_WM_STATE_%s", prop_str);

  prop_atom = XInternAtom(dpy, prop_name, False);

  r = message(win, "_NET_WM_STATE", action, (unsigned long)prop_atom, 0, 0, 0);

  return r;
}

static int message(Window w, char *msg,
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
    event.xclient.window = w;
    event.xclient.format = 32;
    event.xclient.data.l[0] = data0;
    event.xclient.data.l[1] = data1;
    event.xclient.data.l[2] = data2;
    event.xclient.data.l[3] = data3;
    event.xclient.data.l[4] = data4;
    
    r = XSendEvent(dpy, root, False, mask, &event);
    XSync(dpy, False);
    return r;
}

static int get_class() {
  XClassHint *class = XAllocClassHint();
  XGetClassHint(dpy, win, class);
  
  printf("%s %s\n", class->res_name, class->res_class);
  XFree(class);
  return 0;
}

static int search_window (char *classname, Window w) {
  Window unused;
  Window *children;
  Window current;
  XClassHint *class = XAllocClassHint();
  unsigned int length, i;

  if (!XQueryTree(dpy, w, &unused, &unused, &children, &length))
    return 0;
  
  for (i = 0; i < length; i++) {
    current = children[i];

    if (search_window(classname, current) == 0) {
      XFree(children);
      XFree(class);
      return 0;
    }
    else {
      XGetClassHint(dpy, current, class);      
      if (class->res_name != NULL) {

	// FIXME: check if WM_STATE is defined to determine whether it's a toplevel window !
	// printf("0x%x = %s, %s\n", (unsigned int)current, class->res_name, class->res_class);

	if (strcmp(classname, class->res_name) == 0) {
	  win = current;
	  XFree(children);
	  XFree(class);
	  return 0;
	}
      }
    }
  }
  XFree(children);
  XFree(class);
  return 1;
}

static unsigned char *property(Window w, Atom atom, long *nitems, 
			Atom *type, int *size) {

  Atom actual_type;
  int actual_format;
  unsigned long _nitems;
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

  *nitems = _nitems;
  *type = actual_type;
  *size = actual_format;

  return property;
}

static int bad_window(Display *d, XErrorEvent *e) {
  exit(1);
}
