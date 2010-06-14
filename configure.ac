#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.65])
AC_INIT([bashrun], [1.0.0rc1], [h.bekel@googlemail.com])
AM_INIT_AUTOMAKE(bashrun, 1.0.0rc1)

# Checks for programs.
AC_PROG_SED
AC_PROG_CC

# Checks for libraries.
AC_CHECK_LIB(X11, XOpenDisplay,
  LIBS="$LIBS -lX11",
  AC_MSG_ERROR([Could not find XOpenDisplay in -lX11.])
)

# Create Makefiles
AC_OUTPUT(Makefile src/Makefile etc/Makefile man/Makefile)

AC_OUTPUT
