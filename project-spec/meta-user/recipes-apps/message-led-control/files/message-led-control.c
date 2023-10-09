/*
# Copyright 2021 Xilinx Inc.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
*/

/*
* ioctl.c - the process to use ioctl's to control the kernel module
*
* Until now we could have used cat for input and output. But now
* we need to do ioctl's, which require writing our own process.
*/
/*
* device specifics, such as ioctl numbers and the
* major device file.
*/
#include "pwm.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h> /* open */
#include <unistd.h> /* exit */
#include <sys/ioctl.h> /* ioctl */
/*
* Functions for the ioctl calls
*/
void ioctl_ON_LED(int file_desc)
{
	int ret_val;
	ret_val = ioctl(file_desc, IOCTL_ON_LED, NULL);
	if (ret_val < 0)
	{
		printf("ioctl_ON_LED failed:%d\n", ret_val);
		exit(-1);
	}
}
void ioctl_OFF_LED(int file_desc)
{
	int ret_val;
	ret_val = ioctl(file_desc, IOCTL_STOP_LED,NULL);
	if (ret_val < 0)
	{
		printf("ioctl_OFF_LED failed:%d\n", ret_val);
		exit(-1);
	}
}

void ioctl_led_brightness(int file_desc, led_brightness_struct led_brightness)
{
	int ret_val;
	ret_val = ioctl(file_desc, IOCTL_LED_CONTROL,&led_brightness);
	if (ret_val < 0)
	{
		printf("ioctl_led_brightness failed:%d\n", ret_val);
		exit(-1);
	}
}

/*
* Main - Call the ioctl functions
*/
int main(int argc, char* argv[])
{
	int Choice;
	int exitflag=1;
	int file_desc;
	led_brightness_struct lbrightness;

	printf("################################ \n\r");
	printf("      Blink LED Application 0.4  \n\r");
	printf("################################ \n\r");
	file_desc = open(argv[1], O_RDWR | O_SYNC);
	if (file_desc < 0) 
	{
		printf("Can't open device file: %s\n", argv[1]);
		exit(-1);
	}
	while (exitflag)
	{
		printf("************************************************ \n\r");
		printf("Press '1' to Start Blink LED TEST \n\r");
		printf("Press '0' to Stop Blink LED TEST \n\r");
		printf("************************************************ \n\r");
		scanf("%d",&Choice);
		printf("Choice  :: %d \n\r",Choice);
		if(Choice == 1)
		{
			ioctl_ON_LED(file_desc);
			exitflag	= 1;
		}
		else if (0 == Choice )
		{
			ioctl_OFF_LED(file_desc);
			exitflag	= 1;
		}
		else if (2 == Choice )
		{
			printf("enter \"red,green,blue\" brightness between 0 and 255\r\n");
			scanf("%d,%d,%d",&lbrightness.red,&lbrightness.green,&lbrightness.blue);
			printf("Setting red to %d green to %d blue to %d\r\n",lbrightness.red,lbrightness.green,lbrightness.blue);
			ioctl_led_brightness(file_desc,lbrightness);

		}
		else
		{
			exitflag	= 0;

		}
	}

	close(file_desc);
	printf("################################ \n\r");
	printf("      Bye Blink LED Application  \n\r");
	printf("################################ \n\r");
	return 0;
}

