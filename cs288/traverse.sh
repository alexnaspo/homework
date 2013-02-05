#!/bin/sh
function traverse(){   
    local dir=$1
    open=`ls $dir/`
    
    for x in ${open[@]}; do
        echo $dir/$x
        if [ -d "$dir/$x" ]; then            
            traverse $dir/$x        
        fi        
    done
}

function main(){
    traverse $1
}

main $1
