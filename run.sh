# source scripts/setup_vulkan.sh

xmake clean --all
xmake f -m debug
xmake build
xmake run