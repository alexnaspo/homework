#!/bin/sh
function create(){    
    open=($dir)
    closed=()
    i=1
    while [[ $i -le $breadth ]]; do
        tmp=()        
        for x in ${open[@]}; do
            tmp_open=()
            j=1
            while [[ $j -le $depth ]]; do
                echo $x/$j
                #`mkdir $x/$j`
                tmp=( ${tmp[@]} $x/$j)
                j=`expr $j + 1`                
            done
            tmp_open=(${tmp_open[@]} ${tmp[@]})
        done
        closed=(${closed[@]} ${tmp[@]})
        #todo - set closed array HERE
        open=${tmp_open[@]}
        i=`expr $i + 1`
    done
}

function main(){
    local depth=$1 breadth=$2 dir=$3
    create $depth $breadth $dir
}
#todo - catch errors hurrrrr
main $1 $2 $3