FROM gitpod/workspace-full
RUN sudo apt-get update && \
    sudo apt-get install -y gcc-aarch64-linux-gnu