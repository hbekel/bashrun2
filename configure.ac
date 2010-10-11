#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.65])
AC_INIT([bashrun2], [0.1.0], [h.bekel@googlemail.com], [], [http://bashrun.sourceforge.net])
AM_INIT_AUTOMAKE(bashrun2, 0.1.0)

# Checks for programs.
AC_PROG_SED
AC_PROG_AWK
AC_PROG_CC

# Checks for libraries.
AC_CHECK_LIB(X11, XOpenDisplay,
  LIBS="$LIBS -lX11",
  AC_MSG_ERROR([Could not find XOpenDisplay in -lX11.])
)

# Arguments for setting the default terminal command line templates
AC_ARG_WITH(terminal,
  [AS_HELP_STRING([--with-terminal=TEMPLATE], [the default terminal or terminal command template used to launch new bashrun sessions with (+mode * --terminal, default='xterm')])],
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
  [AS_HELP_STRING([--with-exec-terminal=TEMPLATE], [the default terminal or terminal command template used to launch console applications with (+terminal (default|notify) --command, default='xterm)])],
  [ac_with_exec_terminal="$withval"],
  [ac_with_exec_terminal='xterm'])
AC_SUBST(ac_with_exec_terminal)

# Create Makefiles
AC_OUTPUT(Makefile src/Makefile etc/Makefile man/Makefile)

AC_OUTPUT
