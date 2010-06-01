AC_DEFUN([BR_WHICH],
[
AC_MSG_CHECKING([for $1])

which=$(which "$1")		 

if test x$which = x; then
   AC_MSG_ERROR([ bashrun requires $1 to be installed])
fi

AC_MSG_RESULT([$which])
])


