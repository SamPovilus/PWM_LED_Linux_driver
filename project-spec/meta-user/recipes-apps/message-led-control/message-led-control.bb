#
# This file is the message-led-control recipe.
#

SUMMARY = "Simple message-led-control application"
SECTION = "PETALINUX/apps"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI = "file://message-led-control.c \
	   file://Makefile \
	   file://pwm.h\
		  "


S = "${WORKDIR}"

do_compile() {
	     oe_runmake
}

do_install() {
	     install -d ${D}${bindir}
	     install -m 0755 message-led-control ${D}${bindir}
}
