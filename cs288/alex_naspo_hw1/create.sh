#!/bin/sh
function create(){    
    open=($dir)
    closed=()
    i=1
    while [[ $i -le $depth ]]; do
        tmp=()        
        for x in ${open[@]}; do
            tmp_open=()
            j=1
            while [[ $j -le $breadth ]]; do
                echo $x/$j 'created'
                `mkdir -p $x/$j`
                tmp=( ${tmp[@]} $x/$j)
                j=`expr $j + 1`                
            done
            tmp_open=(${tmp_open[@]} ${tmp[@]})
        done
        closed=(${closed[@]} ${tmp[@]})
        open=${tmp_open[@]}
        i=`expr $i + 1`
    done
}

function main(){
    local depth=$1 breadth=$2 dir=$3
    create $depth $breadth $dir
}

if [[ $1 && $2 && $3 ]]; then
    main $1 $2 $3
else
    echo Pass depth, breadth and the directory name as parameters respectively
fi