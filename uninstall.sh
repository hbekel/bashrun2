#!/bin/bash

PREFIX=/usr/local
if [[ "$1" =~ ^--prefix=.+ ]]; then
    PREFIX=$(echo $1 | cut -d = -f 2)
    PREFIX=${PREFIX:-/usr/local}
fi

if [[ ! -f $PREFIX/bin/bashrun ]]; then

    echo "Bashrun does not seem to be installed in $PREFIX. If you have
previously installed bashrun under a prefix other than $PREFIX,
please use the --prefix option to uninstall the previous installation.
"
    exit 1
fi

rm -v $PREFIX/bin/bashrun
rmdir -v $PREFIX/bin

rm -r -v ${XDG_CONFIG_DIRS:-/etc/xdg}/bashrun/

rm -v $PREFIX/share/bashrun/*
rmdir -v $PREFIX/share/bashrun

BC=/etc/bash_completion.d/bashrun
[[ -f $BC && -w $BC ]] && rm -v $BC 

rm -v $PREFIX/share/man/man1/bashrun.1

echo
echo -e "\e[1;32mBashrun 1.0.0-rc1 has been uninstalled from $PREFIX\e[0m"
