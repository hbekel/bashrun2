#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.65])
AC_INIT([bashrun2], [0.2.4], [h.bekel@googlemail.com], [], [https://github.com/hbekel/bashrun2])
AM_INIT_AUTOMAKE

# Checks for programs.
AC_PROG_SED
AC_PROG_AWK
AC_PROG_CC

# Make sure headers and libs are found on BSD as well.
CFLAGS="-I/usr/local/include $CFLAGS"
CPPFLAGS="-I/usr/local/include $CPPFLAGS"
LDFLAGS="-L/usr/local/lib $LDFLAGS"

# Checks for headers.
AC_CHECK_HEADER(X11/Xlib.h,,
  AC_MSG_ERROR([Could not find X11/Xlib.h])
)

# Checks for libraries.
AC_CHECK_LIB(X11, XOpenDisplay,
  LIBS="$LIBS -lX11",
  AC_MSG_ERROR([Could not find XOpenDisplay in -lX11.])
)

# Arguments for setting the default terminal command line templates
AC_ARG_WITH(terminal,
  [AS_HELP_STRING([--with-terminal=TERMINAL], [the default terminal for bashrun])],
  [
    ac_with_terminal="$withval"
    ac_with_terminal_name="$withval"
    ],
    
  [
    ac_with_terminal='xterm'
    ac_with_terminal_name='xterm'
  ])
AC_SUBST(ac_with_terminal)
AC_SUBST(ac_with_terminal_name)

AC_ARG_WITH(exec-terminal,
  [AS_HELP_STRING([--with-exec-terminal=TERMINAL], [the default terminal to launch console applications in])],
  [ac_with_exec_terminal="$withval"],
  [ac_with_exec_terminal='xterm'])
AC_SUBST(ac_with_exec_terminal)

# Create Makefiles
AC_OUTPUT(Makefile src/Makefile etc/Makefile man/Makefile)

AC_OUTPUT
