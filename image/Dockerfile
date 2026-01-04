FROM ubuntu:24.04

RUN apt update && apt install -y pypy3 vim tmux make g++ time unzip

RUN echo "alias cp='cp -i'" >> /root/.profile
COPY ./code/Basic/vimrc /root/.vimrc
COPY ./image/init.sh /root/init.sh

COPY ./code/Basic/Makefile /opt/
COPY ./code/Basic/z.cpp /opt/

CMD /root/init.sh
