# accessing_camera.sh [time in seconds]: Creates the directory "temporary_images",
# takes a photo,
# writes the photo in "temporary_images", waits for the given time,
# then deletes the photo and repeats the steps above again. Deletes "temporary_images" right before exit.

# Note: The termination condition needs to be modified once the rest is done. It should only stop if there
# is nothing to be recognized


#!/usr/bin/env bash

mkdir temporary_images
counter=1
sleep 300
while [ $counter -le 10 ]
do
    fswebcam --no-banner "temporary_images/image.jpg"
    sleep 300
    rm "temporary_images/image.jpg"
    echo $counter  
    ((counter++))
done

rm -r temporary_images
