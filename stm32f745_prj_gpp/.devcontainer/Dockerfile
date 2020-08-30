FROM ubuntu:20.04

RUN useradd -ms /bin/bash user

RUN apt update

#lib
RUN apt install -y usbutils
RUN apt install -y libncurses5

#Util
RUN apt install -y nano
RUN apt install -y wget 

#make prj
RUN apt install -y make
RUN apt install -y cmake

RUN apt install -y git

#STM32-Debug
RUN apt install -y stlink-tools
RUN apt install -y openocd

#GCC-ARM
RUN wget https://developer.arm.com/-/media/Files/downloads/gnu-rm/9-2020q2/gcc-arm-none-eabi-9-2020-q2-update-x86_64-linux.tar.bz2 -O gcc-arm-none-eabi.tar.bz2
RUN mkdir opt/gcc-arm-none-eabi && tar xjfv gcc-arm-none-eabi.tar.bz2 -C opt/gcc-arm-none-eabi --strip-components 1
RUN rm gcc-arm-none-eabi.tar.bz2
ENV PATH="/opt/gcc-arm-none-eabi/bin:${PATH}"
