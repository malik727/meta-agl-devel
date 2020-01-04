#!/bin/sh

export XDG_RUNTIME_DIR=/run/platform/display
export WAYLAND_DISPLAY=wayland-0

/usr/bin/LayerManagerControl set screen 1 render order 9000
/usr/bin/LayerManagerControl set layer 9000 render order 1
