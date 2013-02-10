#!/bin/sh
function traverse(){
    local dir=$1
    open=`ls $dir/`

    for x in ${open[@]}; do
        echo $dir/$x
        #if $dir/$x is a directory, send it to traverse
        if [ -d "$dir/$x" ]; then 
            traverse $dir/$x  
        fi
    done
}

function main(){
    traverse $1
}

if [ $1 ]; then
    main $1
else
    echo Pass the directory you want to traverse as the parameter
fi