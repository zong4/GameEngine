FROM ubuntu:latest

RUN apt-get update && su - && apt-get install -y sudo

RUN sudo apt update && sudo apt-get install -y git
RUN git clone https://github.com/zong4/GameEngine
RUN cd GameEngine

RUN sudo apt-get update && sudo apt-get install -y software-properties-common
RUN sudo apt-get update && sudo add-apt-repository ppa:xmake-io/xmake
RUN sudo apt update && sudo apt install xmake

RUN sudo source run.sh