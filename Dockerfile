FROM ubuntu:latest

# Install necessary packages
RUN apt-get update && apt-get install -y \
    sudo \
    g++ \
    curl \
    git \
    software-properties-common && \
    rm -rf /var/lib/apt/lists/*  # Clean up the apt cache to reduce image size

# Add the xmake repository and install xmake
RUN add-apt-repository ppa:xmake-io/xmake && \
    apt-get update && \
    apt-get install -y xmake && \
    rm -rf /var/lib/apt/lists/*

# Clone the repository
RUN git clone https://github.com/zong4/GameEngine

# Set the working directory
WORKDIR /GameEngine

# Run the script
CMD ["bash", "./script/setup_xmake.sh"]