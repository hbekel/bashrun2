#!/bin/bash

PREFIX=/usr/local
if [[ "$1" =~ ^--prefix=.+ ]]; then
    PREFIX=$(echo $1 | cut -d = -f 2)
    PREFIX=${PREFIX:-/usr/local}
fi

install -v -d $PREFIX/bin
install -v -m 755 src/bashrun-remote $PREFIX/bin

install -v -d $PREFIX/share/bashrun-engine

FILES=(
    actions
    bindings
    bookmarks
    command
    engine
    globals
    handlers
    object
    objects
    readline
    remote
    signals
    source
    utils
)

for file in ${FILES[@]}; do
    install -v -m 644 $file $PREFIX/share/bashrun-engine
done
echo
echo -e "\033[1;32mbashrun-engine development version has been installed in $PREFIX\033[0m"