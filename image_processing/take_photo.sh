# take_photo.sh [directory_name]: script for collecting data, takes a photo each 2 seconds and
# writes it into specified directory

#!/usr/bin/env bash

counter=1

while [ $counter -le 15 ]
do
    fswebcam -r 224x224 --no-banner "$1/image$(date +%s.%n).jpg" # resolution should match the specified input size
    echo $counter
    sleep 2
    ((counter++))
done
