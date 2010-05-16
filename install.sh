#!/bin/bash

PREFIX=/usr/local
if [[ "$1" =~ ^--prefix=.+ ]]; then
    PREFIX=$(echo $1 | cut -d = -f 2)
    PREFIX=${PREFIX:-/usr/local}
fi

install -v -d $PREFIX/bin
install -v -m 755 src/bashrun $PREFIX/bin

install -v -d $PREFIX/share/bashrun

FILES=(
    actions
    bashrc
    bindings
    bookmarks
    command
    completion
    config
    core
    engine
    frontend
    geometry
    globals
    handlers
    modes
    object
    objects
    progress
    readline
    registry
    remote
    rules
    simple
    terminals
    utils
    window
)

for file in ${FILES[@]}; do
    install -v -m 644 src/$file $PREFIX/share/bashrun
done
echo
echo -e "\033[1;32mbashrun development version has been installed in $PREFIX\033[0m"
