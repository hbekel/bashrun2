#!/bin/bash

PREFIX=/usr/local
if [[ "$1" =~ ^--prefix=.+ ]]; then
    PREFIX=$(echo $1 | cut -d = -f 2)
    PREFIX=${PREFIX:-/usr/local}
fi

if [[ ! -f $PREFIX/bin/bashrun-remote ]]; then

    echo "bashrun-engine does not seem to be installed in $PREFIX. If you have
previously installed bashrun-engine under a prefix other than $PREFIX,
please use the --prefix option to specify it.
"
    exit 1
fi

rm -v $PREFIX/bin/bashrun-remote
rmdir -v $PREFIX/bin

rm -v $PREFIX/share/bashrun-engine/*
rmdir -v $PREFIX/share/bashrun-engine

echo
echo "bashrun development version has been uninstalled from $PREFIX"
