#!/bin/sh

function create(){
    local depth=$1 breadth=$2 seed=$3
    open=(seed)
    i=1
    count=0
    tmp_open=()
    while [[ $i -le $breadth ]]; do
        tmp=()
        
        for x in ${open[@]}; do
            tmp_open=()
            j=1
            while [[ $j -le $depth ]]; do
                # echo $count
                echo $x/$j
                tmp=( ${tmp[@]} $x/$j)
                j=`expr $j + 1`
                count=`expr $count + 1`       
            done
            tmp_open=(${tmp_open[@]} ${tmp[@]})
        done
        open=${tmp_open[@]}
        i=`expr $i + 1`
    done
}

function main(){
create $1 $2 $3

}

main $1 $2 $3