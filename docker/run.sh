#!/usr/bin/env bash

HPATH=$(dirname $PWD)
CPATH=/of/apps/myApps/worldExperience
XAUTH=/tmp/.docker.xauth
XSOCK=/tmp/.X11-unix/
HPULSE=/run/user/$(id -u)/pulse
CPULSE=/run/pulse

touch $XAUTH
xauth nlist $DISPLAY | sed -e 's/^..../ffff/' | xauth -f $XAUTH nmerge -


xhost +local:docker

docker run -ti \
    --privileged \
    --device /dev/dri:/dev/dri \
    --publish 12345:12345/udp \
    --volume "$XSOCK:$XSOCK:ro" \
    --volume "$XAUTH:$XAUTH" \
    --volume "$HPATH:$CPATH" \
    --volume "$HPULSE:$CPULSE" \
    --env "XAUTHORITY=$XAUTH" \
    --env "DISPLAY" \
    --name of-test \
    --rm \
    openframeworks-x11


