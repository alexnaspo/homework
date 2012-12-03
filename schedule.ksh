#!/bin/ksh
file="/Users/Alex/CompSci/homework/processes.txt"
IFS=': \;'
i=0
if [[ ${1} = "FCFS" ]]; then   
  while read -r f1 f2 f3 f4 f5 f6  
    do 
      integer id[i]="$f2"
      integer at[i]="$f4"
      integer et[i]="$f6"

      ((i++))
    done <"$file"
  i=0
  currTime=0
  for x in ${id[@]}
  do
    for c in {1..${et[$i]}}
      do
          print "Current Time: $currTime"
          print "\tProcess Id: $x"
          ((currTime++))
          integer ft[i]=$currTime
      done
    print "================="
    let finishTime=${ft[$i]}
    let arrivalTime=${at[$i]}
    typeset -E serviceTime=${et[$i]}
    let Turnaround=finishTime-arrivalTime
    let TrTs=$((Turnaround/serviceTime))
    print "Turnaround Time: $Turnaround"
    print "Tr/Ts: $TrTs"
    print "Throughput:"
    print "Processor Util:" 
    print "================="
    ((i++))
  done
elif [[ ${1} = "SRT" ]]; then
  file="/Users/Alex/CompSci/homework/processes.txt"
  IFS=': \;'
  i=0
  while read -r f1 f2 f3 f4 f5 f6  
    do 
      integer id[i]="$f2"
      integer at[i]="$f4" #arrival time
      integer et[i]="$f6" #exec time 
      integer rt[i]=0 #run time so far
      integer current[i]=i

      ((i++))
    done <"$file"

  integer curr_index=0
  integer currTime=0
  let totalProcesses=${#at[@]}
  let totalProcesses=totalProcesses-1
  let totalRunTime=0
  for x in ${et[@]}; do
    let totalRunTime+=$x

  done 

  
    currTime=0
    shortest=0
    
    while [[ ${current[@]} ]]; do

      echo "${current[@]} current proccess"
      echo "$currTime current time"
      if(( et[$shortest] == 0 )); then
        

        unset current[$shortest]
        let next=shortest+1
        echo "CURRENT index ZERO ${current[1]}"
        
        for x in ${current[@]}; do
          shortest=$x
          break
        done
        # echo "SHORTEST ${et[$shortest]}"
      fi
      echo "====================="
      echo "====================="
      for y in ${current[@]}; do

        echo "current program ID: ${id[$y]}"
        if (( at[$y] <= currTime )); then
          
          # echo "${et[$y]} <= et[$shortest] "
          if (( et[$y] <= et[$shortest] )); then
            shortest=$y
            #check if is this the last element in the for lopp
            #add element to array

           
              # print "\t\tcurrent time: $currTime"
              # print "\t\t\tcurrent process: ${id[$shortest]}"

              


          fi
        fi
      done
      echo "ID:${id[$shortest]} ET:${et[$shortest]} "
       schedule[$currTime]=$y
            (( et[$shortest]-- ))
            (( currTime++ ))
            

    done


    # for c in ${schedule[@]}; do
    #   echo "${id[c]}"
    # done

    # for y in ${current[@]}; do
    #   if (( rt[$y] < et[$y] )); then
    #     #if the program is not finished, keep going
    #     if (( at[$y] < $currTime )); then
    #       #if the program is in que, keep going
    #       let diff=et[$y]-rt[$y]
    #       let currDiff=et[$curr_index]-rt[$curr_index]          
    #       if (( et[$y] <= et[$curr_index] )); then #is this broken?
    #         curr_index=$y
    #       fi
    #     fi
    #   else
    #     #echo "${id[$y]} RAN ${rt[$y]} out of ${et[$y]} seconds"
        
    #     unset current[$y]
    #   fi
    # done
  
  
  
    # echo "================================="
    
    # ((rt[$curr_index]++))
    # print "\t\tcurrent time: $i"
    # print "\t\t\tcurrent process: ${id[$curr_index]}"
    # echo "================================="
  

  
else 
  echo "Please supply FCFS or SRT as an arg"
fi