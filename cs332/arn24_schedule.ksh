#!/bin/ksh
# Alexander Naspo
# CS 332
file="./processes.txt"
i=0
cat $file | while IFS=': \;' read -r f1 f2 f3 f4 f5 f6  
do 
  integer id[i]="$f2"
  integer at[i]="$f4" #arrival time
  integer et[i]="$f6" #exec time 
  typeset -E servicetime[i]="$f6" #service time for final calculations
  integer rt[i]=0 #run time so far
  integer current[i]=i
  ((i++))
done
currTime=0
util=0 #for calculation of processor utilization

#FCFS 
if [[ ${1} = "FCFS" ]]; then   
  process=0
  while [[ ${current[@]} ]]; do
    #while there are processes still left
    for y in ${current[@]}; do
      #loop through avail processes
      if (( at[$y] <= currTime )); then
        #check to see if the process has arrived
        process=$y
        schedule[$currTime]=${id[$process]}
        #process ran successfully, increment and decrement required variables
        (( currTime++ ))
        (( et[$process]-- ))
        (( util++ ))
        if(( et[$process] == 0 )); then
          #if the process has completed, unset from array
          ft[$process]=$currTime
          unset current[$process]
        fi
        break
      else
        schedule[$currTime]="NONE"
        (( currTime++ ))
        break
      fi
    done
  done

#SRT
elif [[ ${1} = "SRT" ]]; then
  shortest=0
  while [[ ${current[@]} ]]; do
    #while there are processes still left
    if(( et[$shortest] == 0 )); then
      #if the process has completed, unset from array
      ft[$shortest]=$currTime
      unset current[$shortest]
      for x in ${current[@]}; do
        #set shortest to first index in array of current processes
        shortest=$x
        break
      done
    fi
    if (( ${#current[@]} == 0 )); then
      #if the final process was finished kill the while loop
      break
    fi
    for y in ${current[@]}; do
      #loop through processes that are still available
      if (( at[$y] <= currTime )); then
        #has this process arrived yet?
        if (( et[$y] < et[$shortest] )); then
          #set shortest process index
          shortest=$y            
        fi
      fi
    done

    if (( et[$shortest] >= 0 )); then #solves issue with last time slice
      if (( at[$shortest] <= $currTime )); then
        schedule[$currTime]=${id[$shortest]}
        (( util++ ))
        (( et[$shortest]-- ))
      else
        schedule[$currTime]="NONE"
      fi      
      (( currTime++ ))
    fi
  done

else 
  echo "Please supply one of the two following parameters"
  print "\tFCFC to implement the First Come first Serve Algorithm"
  print "\tSRT to implement the Shortest Remaining Time Algorithm"
  return
fi
#print results

currTime=0

for x in ${schedule[@]}; do

  print "Current Time: $currTime"
  print "\tProcess ID: $x"
  (( currTime++ ))
done
#calculate stats
let total=${#id[@]}-1
for y in {0..$total}; do
  let turnaround=${ft[$y]}-${at[$y]}
  let servicetime=${servicetime[$y]}
  let TrTs=$(($turnaround/servicetime))
  echo "======================"
  echo "Process ID: ${id[$y]}"
  echo "Turnaround Time: $turnaround"
  echo "Tr/Ts: $TrTs"
  echo "======================"
done

typeset -E currTime=$currTime #floating point
let throughput=$((total/currTime)) 
let util=$(((util/currTime) * 100))
echo "Processor Calcuations:"
print "\tThroughput: $throughput" 
print "\tProcessor Utilization:$util%" 
