# Build instructions of agl-demo (container version)

### Environment: 
  - AGL UCB Release: Kooky Koi
  - Board: RCar-Gen3 H3 SK (+KF)

### BUGS & TODO

- cannot start agl-compositor on guest with GL renderer

The following is compositor.log on guest
```
[10:26:03.107] EGL_KHR_surfaceless_context available
[10:26:03.239] failed to create context
[10:26:03.239] EGL error state: EGL_BAD_ALLOC (0x3003)
[10:26:03.239] EGL error state: EGL_SUCCESS (0x3000)
[10:26:03.241] Failed to initialize the GL renderer; falling back to pixman.
```
Expectation is like following
```
[03:06:45.165] EGL_KHR_surfaceless_context available
[03:06:45.195] GL version: OpenGL ES 3.2 build 1.11@5516664
[03:06:45.195] GLSL version: OpenGL ES GLSL ES 3.20 build 1.11@5516664
[03:06:45.195] GL vendor: Imagination Technologies
[03:06:45.195] GL renderer: PowerVR Rogue GX6650
```

- cannot launch any Qt apps on guest 

 It looks like same cause of agl-compositor's GL renderer error.


# Setup AGL meta layers

## Download AGL UCB reelase

This agl-demo integration is tested with Kooky Koi. Download AGL UCB release.

e.g.
```
repo init -b koi -u https://gerrit.automotivelinux.org/gerrit/AGL/AGL-repo
repo sync
```

cf. [2 Downloading AGL Software](https://docs.automotivelinux.org/en/master/#0_Getting_Started/2_Building_AGL_Image/2_Downloading_AGL_Software/).


## Patch agl-demo container integration

Patches are uploaded as [sandbox branch](https://gerrit.automotivelinux.org/gerrit/gitweb?p=AGL/meta-agl-devel.git;a=shortlog;h=refs/heads/sandbox/ruke47/ces2020_koi) of `meta-agl-devel`, and following commits are mandatory (need to be merged).

```
Projects Overview
meta-agl-devel
* agl-container-demo                ( 9 commits, Mon Mar 1 03:29:06 2021 +0900)
                                      - 027840e0 agl-container: init AGL container integration
                                      - 2e5bef8d agl-container: init LXC
                                      - 22519b0e agl-container-demo: init AGL container demo
                                      - 0d92b2b4 agl-container-demo: setup DNS of host
                                      - d4a9977d agl-container-demo: setup wayland compositors
                                      - 23a5e2ad agl-container-demo: setup passthrough device of IVI
                                      - 36972cf4 agl-container-demo: simple container manager, lxc-launcher
                                      - 01a1ee90 agl-container-demo: Remove title and border
                                      - e273e5cc Hack
```

e.g.
```
repo start agl-container-demo meta-agl-devel
cd meta-agl-devel
git merge agl/sandbox/ruke47/ces2020_koi
```

# AGL Demo Host environment
## Setup agl-demo host

Initialize build environment of agl-demo host.
Mandatory AGL feature is `agl-container-demo-host`.

e.g.
```
source meta-agl/scripts/aglsetup.sh -m h3ulcb -b agl-demo-host agl-container-demo-host
```

## Build agl-demo host

Recommended build target is `agl-image-weston`.

e.g.
```
bitbake agl-image-weston
```

# AGL Demo Guest environment
## Setup agl-demo guest

Initialize build environment of agl-demo guest.
Mandatory AGL feature is `agl-container-demo-guest`.

e.g.
```
source meta-agl/script/aglsetup.sh -m h3ulcb -b agl-demo-guest agl-container-demo-guest
```

## Setup multiconfig

Add following line to `conf/local.conf` to enable multiconfig.

```
BBMULTICONFIG = "ivi ic"
```

Create `multiconfig/` directory under `conf/` and 2 config files of agl-demo-ivi and agl-demo-ic.

```
conf/
├── bblayers.conf
├── local.conf
└── multiconfig
    ├── ic.conf
    └── ivi.conf
```

`ic.conf`
```
TMPDIR = "${TOPDIR}/tmp_ic"
AGL_FEATURES_append = " agl-demo-ic"
```

`ivi.conf`
```
TMPDIR = "${TOPDIR}/tmp_ivi"
AGL_FEATURES_append = " agl-demo-ivi"
```

## Build agl-demo host

Build ivi demo image (`agl-demo-platform`) and ic demo image (`agl-cluster-demo-platform`).

```
bitbake mc:ivi:agl-demo-platform mc:ic:agl-cluster-demo-platform
```

## Create bootable SDCard for R-Car H3SK

Create 3 partitions like this.
```
Device         Boot    Start      End  Sectors  Size Id Type
/dev/mmcblk0p1          8192  2292143  2283952  1.1G 83 Linux
/dev/mmcblk0p2       2293760 22773759 20480000  9.8G 83 Linux
/dev/mmcblk0p3      22773760 43253759 20480000  9.8G 83 Linux
```

It is convenient to label each partition.

e.g.
```
NAME        LABEL
mmcblk0     
├─mmcblk0p1 root
├─mmcblk0p2 agl-ivi
└─mmcblk0p3 agl-ic
```

## Write all rootfs to SDCard

Extract each tar.xz of rootfs with `--xattrs-include='*'`, `--numeric-owner`, `--preserve-permissions`, and `--preserve-order`.

e.g.
```
sudo tar --xattrs-include='*' --extract --numeric-owner --preserve-permissions --preserve-order --totals --directory=${Your_SDCARD_PATH} --file=${Your_ROOTFS}
```

e.g.
```
$ cd agl-demo-host
$ 
$ cd ../agl-demo-guest
$ sudo tar --xattrs-include='*' --extract --numeric-owner --preserve-permissions --preserve-order --totals --directory=/media/agl/agl-ivi --file=tmp_ivi/deploy/images/h3ulcb/agl-demo-platform-h3ulcb.tar.xz
Total bytes read: 1187031040 (1.2GiB, 55MiB/s)
$ sudo tar --xattrs-include='*' --extract --numeric-owner --preserve-permissions --preserve-order --totals --directory=/media/agl/agl-ic --file=tmp_ic/deploy/images/h3ulcb/agl-cluster-demo-platform-h3ulcb.tar.xz
Total bytes read: 905512960 (864MiB, 48MiB/s)
```

## Boot R-Car H3 SK

After boot H3SK, create mount points for rootfs of guests.

e.g.
```
h3ulcb:~# ls /dev/disk/by-label/
agl-ic agl-ivi root
h3ulcb:~# mkdir -p /var/local/containers/agl-ic
h3ulcb:~# mkdir -p /var/local/containers/agl-ivi
h3ulcb:~# mount /dev/disk/by-label/agl-ic /var/local/containers/agl-ic
h3ulcb:~# mount /dev/disk/by-label/agl-ivi /var/local/containers/agl-ivi
```

# Launch agl-demo on lxc container

## Option 1. using lxc-launcher

To launch fullset of CES2020 demo, using lxc-launcher is recommended.

Set proper lxc-launcher config.

```
h3ulcb:~# cd /etc/lxc
h3ulcb:/etc/lxc# rm runlxc.conf
h3ulcb:/etc/lxc# ln -s runlxc.rcar3-example.conf runlxc.conf
h3ulcb:/etc/lxc# cd
```

Then, run lxc-launcher.

```
h3ulcb:~# systemctrl restart lxc-network
h3ulcb:~# export XDG_RUNTIME_DIR=/run/platform/display
h3ulcb:~# export WAYLAND_DISPLAY=wayland-host-0
h3ulcb:~# /usr/bin/runlxc 
```

Sometime race condition happens between weston and lxc-network and it blocks
`lxc-start`. To prevent this, restart lxc-network before 
starting guest image.

## Option 2. debug each lxc container image

If you know about ivi-shell well, you would better to continue with it.
If not, using desktop shell as host weston's shell is better.

To switch desktop shell, modify weston.conf directory on target board.

Example of using desktop shell instead of ivi-shell
```
[core]
#shell=ivi-shell.so
backend=drm-backend.so
#require-input=false
#modules=systemd-notify.so,ivi-controller.so
modules=systemd-notify.so
```