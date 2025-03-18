source scripts/setup_vulkan.sh

xmake f -m debug
xmake clean --all
xmake build
xmake run