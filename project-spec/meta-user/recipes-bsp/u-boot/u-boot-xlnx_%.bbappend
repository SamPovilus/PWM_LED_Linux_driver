FILESEXTRAPATHS:prepend := "${THISDIR}/files:"

SRC_URI:append = " file://platform-top.h file://bsp.cfg"
SRC_URI += "file://user_2023-09-18-14-36-00.cfg \
            file://user_2023-09-18-14-57-00.cfg \
            file://user_2023-09-18-15-40-00.cfg \
            "

