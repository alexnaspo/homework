#!/bin/csh
set dirs=( $argv[3-$#argv] )
set num_files=0
while ( $#dirs > 0 )
    set fi=1
    set thisdir=$dirs[1]
    set files=( $thisdir/* )
    echo "Working on directory ${thisdir}"
    /etc/chown $1 $files
    chgrp $2 $files
    while ( $fi <= $#files )
        @ numfiles++
        set thisfile=$files[$fi]
        if ( -d $thisfile ) then
            set x=`ls -ld $thisfile | colrm 2`
            if ( X$x == Xl ) then
                echo "[link  ${thisfile}]"
            else
                echo "[found ${thisfile}]"
                set dirs=( $dirs $thisfile )
            endif
        endif
        @ fi++
        end
    set dirs=( $dirs[2-$#dirs] )
end
echo "${numfiles} seen"