#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.65])
AC_INIT([bashrun], [1.0.0rc1], [h.bekel@googlemail.com], [], [http://bashrun.sourceforge.net])
AM_INIT_AUTOMAKE(bashrun, 1.0.0rc1)

# Checks for programs.
AC_PROG_SED
AC_PROG_AWK
AC_PROG_CC

# Checks for libraries.
AC_CHECK_LIB(X11, XOpenDisplay,
  LIBS="$LIBS -lX11",
  AC_MSG_ERROR([Could not find XOpenDisplay in -lX11.])
)

# Arguments for setting the default terminal command lines

AC_ARG_WITH(terminal,
  [AS_HELP_STRING([--with-terminal=TEMPLATE], [the default terminal command template used to launch new bashrun sessions with (+mode * --terminal, default='xterm -g %g -n %n %o -e %*')])],
  [
    ac_with_terminal="$withval"
    ac_with_terminal_name="$(echo "$withval" | awk '{ print $1 }')"
    ],
    
  [
    ac_with_terminal='xterm -g %g -n %n %o -e %*'
    ac_with_terminal_name='xterm'
  ])
AC_SUBST(ac_with_terminal)
AC_SUBST(ac_with_terminal_name)

AC_ARG_WITH(exec-terminal,
  [AS_HELP_STRING([--with-exec-terminal=TEMPLATE], [the default terminal command template used to launch console applications with (+terminal (default|notify) --command, default='xterm -g %g -e bash -c %@')])],
  [ac_with_exec_terminal="$withval"],
  [ac_with_exec_terminal='xterm -g %g -e bash -c %@'])
AC_SUBST(ac_with_exec_terminal)

# Create Makefiles
AC_OUTPUT(Makefile src/Makefile etc/Makefile man/Makefile)

AC_OUTPUT
