/*
 * input test driver for Linux
 */

/*
 *  Copyright (c) 2014 ZengYajian
 *
 *  Just a input framwork test
 *  by ZengYajian
 */

/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#include <linux/slab.h>
#include <linux/module.h>
#include <linux/input.h>
#include <linux/init.h>
#include <linux/delay.h>

#define DRIVER_DESC	"Input Test driver"

MODULE_AUTHOR("ZengYajian <ZengYajian@gmail.com>");
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");

#define SKBD_KEY_MASK	0x7f
#define SKBD_RELEASE	0x80

static unsigned char skbd_keycode[128] = {
	KEY_1, KEY_2, KEY_3, KEY_Z, KEY_4, KEY_5, KEY_6, KEY_7,
	0, KEY_Q, KEY_W, KEY_E, KEY_R, KEY_T, KEY_Y, KEY_GRAVE,
	KEY_X, KEY_A, KEY_S, KEY_D, KEY_F, KEY_G, KEY_H, KEY_SPACE,
	KEY_CAPSLOCK, KEY_TAB, KEY_LEFTCTRL, 0, 0, 0, 0, 0,
	0, 0, 0, KEY_LEFTALT, 0, 0, 0, 0,
	0, 0, 0, 0, KEY_C, KEY_V, KEY_B, KEY_N,
	KEY_MINUS, KEY_EQUAL, KEY_BACKSPACE, KEY_HOME, KEY_8, KEY_9, KEY_0, KEY_ESC,
	KEY_LEFTBRACE, KEY_RIGHTBRACE, KEY_BACKSLASH, KEY_END, KEY_U, KEY_I, KEY_O, KEY_P,
	KEY_APOSTROPHE, KEY_ENTER, KEY_PAGEUP,0, KEY_J, KEY_K, KEY_L, KEY_SEMICOLON,
	KEY_SLASH, KEY_UP, KEY_PAGEDOWN, 0,KEY_M, KEY_COMMA, KEY_DOT, KEY_INSERT,
	KEY_DELETE, KEY_LEFT, KEY_DOWN, KEY_RIGHT,  0, 0, 0,
	KEY_LEFTSHIFT, KEY_RIGHTSHIFT, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5, KEY_F6, KEY_F7,
	KEY_F8, KEY_F9, KEY_F10, KEY_F11, KEY_F12, 0, 0, 0
};

static struct input_dev *input_dev;
static int __init input_test_init(void)
{
	int err = -ENOMEM;
	int i;

	input_dev = input_allocate_device();
	if (!input_dev)
		goto fail;

	input_dev->name = "Input-Test";
	input_dev->phys = "Bogon";
	input_dev->id.bustype = BUS_HOST;
	input_dev->id.vendor = 0x0001;
	input_dev->id.product = 0x0001;
	input_dev->id.version = 0x0100;
	input_dev->dev.parent = NULL;

	input_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_REP);
	input_dev->keycode = skbd_keycode;
	input_dev->keycodesize = sizeof(unsigned char);
	input_dev->keycodemax = ARRAY_SIZE(skbd_keycode);
	for (i = 0; i < ARRAY_SIZE(skbd_keycode); i++)
		set_bit(skbd_keycode[i], input_dev->keybit);
	clear_bit(0, input_dev->keybit);

	err = input_register_device(input_dev);
	if (err)
		goto err_register;

	printk(KERN_ERR "++ period %d\n", input_dev->rep[REP_PERIOD]);
	printk(KERN_ERR "++ delay  %d\n", input_dev->rep[REP_DELAY]);

	return 0;

err_register:
	input_free_device(input_dev);
fail:
	return err;
}

static void __exit input_test_exit(void)
{
	printk(KERN_ERR "-- period %d\n", input_dev->rep[REP_PERIOD]);
	printk(KERN_ERR "-- delay  %d\n", input_dev->rep[REP_DELAY]);
	input_unregister_device(input_dev);
}

module_init(input_test_init);
module_exit(input_test_exit);
