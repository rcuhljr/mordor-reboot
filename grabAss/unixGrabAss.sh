#!/bin/bash


MOUNTED_CD_DIRECTORY=$1 #Assumes that the target directory is supplied
MORDOR_ROOT=$2 #assumes relative path

## Where the important assets live on the mordor CD
SCREEN_SAVER=${MOUNTED_CD_DIRECTORY}/SSAVER.WIP
SOUNDS=${MOUNTED_CD_DIRECTORY}/WAVES.WIP
ASSETS=${MOUNTED_CD_DIRECTORY}/MORDOR.WIP

## Where the important assets go
ASSET_ROOT=${MORDOR_ROOT}/assets
IMAGES=${ASSET_ROOT}/images
MUSIC=${ASSET_ROOT}/music
SFX=${ASSET_ROOT}/sound_effects
GAME_DAT=${ASSET_ROOT}/source_game_data


## Verify the contents of the directory are what the contents of the
## directory should be
test_mordor_contents () # No args
{
    for WIP_FILE in $SCREEN_SAVER $SOUNDS $ASSETS
    do
        if [ -e $WIP_FILE ]
        then
            echo "Found $WIP_FILE where I expected it to be"
        else
            echo "$WIP_FILE is missing.  Maybe you've got a bad iso, or maybe you pointed me at the wrong directory."
            exit 1
        fi
    done
}

## Unpack the wip into the target directory
unpack_wip () # wip_path destination_path
{
    echo "Unpacking $1 to $2"
    echo "tar -xvf $1 -C $2"
    tar -xvf $1 -C $2
}

## make sure destination directory exists
ensure_dest_dir () #dest_dir
{
    if [ -e $1 ]
    then
        if [ -d $1 ]
        then
            echo "$1 exists and is a directory. I'll unpack files here, overwriting existing contents."
        else
            echo "$1 exists and is not a directory.  I can't unpack files here."
            exit 1
        fi
    else
        echo "$1 doesn't exist, creating it so I can unpack contents into it."
        echo "mkdir $1"
        mkdir $1
    fi
}


## main
if [ -d $MOUNTED_CD_DIRECTORY ]
then
    # Verify WIPs exist where I think they should be.
    test_mordor_contents

    # Make sure you have a place to unpack the data
    for destination in $ASSET_ROOT $IMAGES $MUSIC $SFX $GAME_DAT
    do
        ensure_dest_dir $destination
    done

    unpack_wip $SCREEN_SAVER $IMAGES 
    unpack_wip $ASSETS $GAME_DAT
    unpack_wip $SOUNDS $SFX
    echo "Sound WIP has effects, music.  Moving effect to proper location."
    for tune in ${GAME_DAT}/*.MID
    do
        echo "Moving $tune to ${MUSIC}.."
        echo "mv $tune ${MUSIC}/"
        mv $tune ${MUSIC}/
    done
    
else
    echo "$MOUNTED_CD_DIRECTORY isn't a proper directory. You need to point me at the directory where the MORDOR image is mounted!"
    exit 1
fi

#EOF
