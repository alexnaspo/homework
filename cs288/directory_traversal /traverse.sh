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
temp=()    
function traverse_br    eadth(){
    local dir=$1    
    open=(`ls $dir`)
    for x in ${open[@]}; do     
        echo $dir/$x           
        
        if [ -d "$dir/$x" ]; then
            temp+=("$dir/$x")
        fi
    done
    for x in ${open[@]}; do
        if [ -d "$dir/$x" ]; then 
            traverse_breadth $dir/$x
        fi
    done
}

function main(){
    if [ $2 -eq 0 ]; then
        echo depth
        traverse $1
    else
        echo face
        traverse_breadth $1
    fi
}

if [ $1 ]; then
    main $1 $2
else
    echo Pass the directory you want to traverse as the parameter
fi