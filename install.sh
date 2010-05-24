#!/bin/bash

PREFIX=/usr/local
if [[ "$1" =~ ^--prefix=.+ ]]; then
    PREFIX=$(echo $1 | cut -d = -f 2)
    PREFIX=${PREFIX:-/usr/local}
fi

install -v -d $PREFIX/bin
install -v -m 755 src/bashrun $PREFIX/bin

install -v -d $PREFIX/share/bashrun
install -v -d $PREFIX/share/bashrun/plugins

FILES=(
    actions
    bashrc
    bindings
    bookmarks
    bootstrap
    command
    completion
    config
    core
    defaultrc
    engine
    frontend
    geometry
    globals
    handlers
    modes
    object
    objects
    plugin
    progress
    readline
    registry
    remote
    rules
    terminals
    utils
    window
)

for file in ${FILES[@]}; do
    install -v -m 644 src/$file $PREFIX/share/bashrun
done

PLUGINS=(terminal.rc dropdown.rc)
for file in ${PLUGINS[@]}; do
    install -v -m 644 src/plugins/$file $PREFIX/share/bashrun/plugins
done

BC=/etc/bash_completion
BCDIR=/etc/bash_completion.d

if [[ -f $BC && -d $BCDIR && -w $BCDIR ]]; then
    install -v -m 644 misc/bash_completion $BCDIR/bashrun
fi

echo
echo -e "\e[1;32mbashrun 0.16.0-rc1 has been installed in $PREFIX\e[0m"
