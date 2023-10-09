## Commands

` petalinux-build -c message-led-control -x compile && scp ./build/tmp/work/cortexa72-cortexa53-xilinx-linux/message-led-control/1.0-r0/message-led-control petalinux@messagebasedled:~`


`petalinux-build -c pwm -x compile && scp ./build/tmp/work/zynqmp_generic_xczu1cg-xilinx-linux/pwm/1.0-r0/pwm.ko petalinux@messagebasedled:~/`