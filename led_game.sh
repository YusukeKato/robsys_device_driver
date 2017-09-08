#!/bin/sh

sudo echo 2 > /sys/class/gpio/export
sudo echo 3 > /sys/class/gpio/export

sudo echo in > /sys/class/gpio/gpio2/direction
sudo echo in > /sys/class/gpio/gpio3/direction

sudo echo high > /sys/class/gpio/gpio2/direction
sudo echo high > /sys/class/gpio/gpio3/direction

sw1=0
sw2=0
swflag1=0
swflag2=0
plus=1
a=9
led_size=17
slp=0.1
count=0

while :
do
    if [ $a -gt 9 ]; then
        if [ $a = 10 ]; then
            echo a > /dev/myled0
        fi
        if [ $a = 11 ]; then
            echo b > /dev/myled0
        fi
        if [ $a = 12 ]; then
            echo c > /dev/myled0
        fi
        if [ $a = 13 ]; then
            echo d > /dev/myled0
        fi
	if [ $a = 14 ]; then
            echo e > /dev/myled0
        fi
	if [ $a = 15 ]; then
	    echo f > /dev/myled0
	fi
	if [ $a = 16 ]; then
	    echo g > /dev/myled0
	fi
	if [ $a = 17 ]; then
	    echo h > /dev/myled0
	fi
    else
        echo $a > /dev/myled0
    fi
    sleep $slp
    echo 0 > /dev/myled0
    sleep $slp

    a=`expr $a + $plus`

    sw1=$(cat /sys/class/gpio/gpio2/value) 
    sw2=$(cat /sys/class/gpio/gpio3/value)
    if [ $sw1 = 1 -a $a -gt 2 -a $a -lt 5 ]; then
	swflag1=1
    fi
    if [ $sw2 = 1 -a $a -gt 13 -a $a -lt 16 ]; then
	swflag2=1
    fi
    if [ $sw1 = 0 -a $plus = -1 -a $a -lt 3 -a $swflag1 = 1 ]; then
        plus=1
        swflag1=0
    fi
    if [ $sw2 = 0 -a $plus = 1 -a $a -gt 15 -a $swflag2 = 1 ]; then
	plus=-1
	swflag2=0
    fi

    if [ $a -gt $led_size ]; then
	while :
	do
	    echo 1 > /dev/myled0
	    echo 2 > /dev/myled0
	    sleep 0.2
	    echo 0 > /dev/myled0
	    sleep 0.2
	done
    fi
    if [ $a -lt 1 ]; then
        while : 
	do
	    echo g > /dev/myled0
	    echo h > /dev/myled0
	    sleep 0.2
	    echo 0 > /dev/myled0
	    sleep 0.2 
        done
    fi

    count=`expr $count + 1`
    if [ $count -gt 30 ]; then
	slp=0.08
    fi
    if [ $count -gt 60 ]; then
	slp=0.06
    fi
    if [ $count -gt 90 ]; then
	slp=0.04
    fi
    if [ $count -gt 120 ]; then
	slp=0.02
    fi
    if [ $count -gt 150 ]; then
	slp=0.01
    fi
done
