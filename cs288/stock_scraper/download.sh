#!/bin/bash
function get_stocks(){
  date=$1
  curl -o $date.html http://markets.usatoday.com/custom/usatoday-com/html-mktscreener.asp
  `python hw7.py $date.html`
  `rm $date.*`
}

x=0
while [[ $x -le 60 ]]; do
  date=`(date +"%Y-%m-%d-%H-%M-%s")`
  get_stocks $date
  sleep 3
  x=`expr $x + 1`
done
