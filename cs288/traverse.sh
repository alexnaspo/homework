#!/bin/sh
function traverse(){   
    local dir=$1
    open=`ls $dir/`

    for x in ${open[@]}; do
        if [ -d "$dir/$x" ]; then
            echo $dir/$x
            traverse $dir/$x
        else
            echo $dir/$x
        fi        
        count
    done
}

function main(){
    count=0
    local dir=$1
    traverse $dir 

}

function count(){
    count=`expr $count + 1`

}

main $1