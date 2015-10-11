#!/bin/sh
# This shell script simply copies required SFML dylibs/frameworks into the application bundle frameworks folder.
# If you're using static libraries (which is not recommended) you should remove this script from your project.

# Are we building a project that uses frameworks or dylibs?
case "$SFML_BINARY_TYPE" in
    DYLIBS)
        frameworks="false"
        ;;
    *)
        frameworks="true"
        ;;
esac

# Echoes to stderr
error () # $* message to display
{
    echo $* 1>&2
    exit 2
}

assert () # $1 is a boolean, $2...N is an error message
{
    if [ $# -lt 2 ]
    then
        error "Internal error in assert : not enough args"
    fi

    if [ $1 -ne 0 ]
    then
        shift
        error "$*"
    fi
}

force_remove () # $@ is some paths
{
    test $# -ge 1
    assert $? "force_remove() requires at least one parameter"
    rm -fr $@
    assert $? "couldn't remove $@"
}

copy () # $1 is a source, $2 is a destination
{
    test $# -eq 2
    assert $? "copy() requires two parameters"
    ditto "$1" "$2"
    assert $? "couldn't copy $1 to $2"
}

require () # $1 is a SFML module like 'system' or 'audio'
{
    dest="$BUILT_PRODUCTS_DIR/$PRODUCT_NAME.app/Contents/Frameworks"

    if [ -z "$1" ]
    then
        error "require() requires one parameter!"
    else
        # clean potentially old stuff
        force_remove "$dest/libsfml-$1"*
        force_remove "$dest/sfml-$1.framework"

        # copy SFML libraries
        if [ "$frameworks" = "true" ]
        then
            source="/Library/Frameworks/sfml-$1.framework"
            target="sfml-$1.framework"
        elif [ "$SFML_LINK_DYLIBS_SUFFIX" = "-d" ]
        then
            source="/usr/local/lib/libsfml-$1-d.dylib"
            target="`readlink $source`"
        else
            source="/usr/local/lib/libsfml-$1.dylib"
            target="`readlink $source`"
        fi

        copy "$source" "$dest/$target"

        # copy extra dependencies
        if [ "$1" = "audio" ]
        then
            # copy sndfile framework too
            copy "/Library/Frameworks/sndfile.framework" "$dest/sndfile.framework"
        elif [ "$1" = "graphics" ]
        then
            # copy freetype framework too
            copy "/Library/Frameworks/freetype.framework" "$dest/freetype.framework"
        fi
    fi
}

if [ -n "$SFML_SYSTEM" ]
then
    require "system"
fi

if [ -n "$SFML_AUDIO" ]
then
    require "audio"
fi

if [ -n "$SFML_NETWORK" ]
then
    require "network"
fi

if [ -n "$SFML_WINDOW" ]
then
    require "window"
fi

if [ -n "$SFML_GRAPHICS" ]
then
    require "graphics"
fi

                
