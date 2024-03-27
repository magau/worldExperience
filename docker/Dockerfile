FROM ubuntu:20.04
#FROM ubuntu:22.04
#FROM docker_x11:latest

ENV DEBIAN_FRONTEND noninteractive

#COPY ./of/scripts/linux/debian/install_dependencies.sh /tmp/install_dependencies.sh
#COPY ./of /of

USER root

RUN apt update && apt -y upgrade && apt install -yf

RUN apt install -y make wget curl vim\
 x11-apps lsb-core update-notifier

RUN wget https://openframeworks.cc/versions/v0.11.2/of_v0.11.2_linux64gcc6_release.tar.gz

RUN mkdir /of &&\
 tar -xvf of_v0.11.2_linux64gcc6_release.tar.gz  -C /of --strip-components 1 &&\
 rm of_v0.11.2_linux64gcc6_release.tar.gz

RUN sed -ri "s/(libboost-[^\$]*)([^ ]*)/\1\2 libboost-regex\2/"\
 /of/scripts/linux/ubuntu/install_dependencies.sh &&\
 /of/scripts/linux/ubuntu/install_dependencies.sh -y

RUN sed -i "s/apt-get install/apt-get install -y/g"\
 /of/scripts/linux/ubuntu/install_codecs.sh &&\
 /of/scripts/linux/ubuntu/install_codecs.sh

RUN  apt install -y libxi-dev libxcursor-dev\
 libxinerama-dev libharfbuzz-dev alsa-utils
# && apt-get clean \
# && rm -rf /var/lib/apt/lists/*

RUN sed -i 's@"cairo.h"@"cairo/cairo.h"@g'\
 /of/libs/openFrameworks/graphics/ofCairoRenderer.h &&\
 cd /of/scripts/linux && ./compileOF.sh

#OSC Connection is currently done through port 12345 
EXPOSE 12345/udp

WORKDIR /of/apps

CMD bash
