# Use weston as host compositor of IVI+IC demo container integration
#
#   Host(weston ivi-shell) ---socket:wayland-host-0-+- IVI container(agl-compositor) --socket:wayland-0-- App(wayland client)
#                                                   +- IC container(agl-compositor) --socket:wayland-0-- App(wayland client)
#
AGL_DEFAULT_WESTONSTART = "/usr/bin/weston --socket=wayland-host-0"
