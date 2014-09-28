/*
 * Driver for Allwinner Pulse Width Modulation Controller
 *
 * Copyright (C) 2014 Allwinner
 *
 * Licensed under GPLv2.
 */

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/platform_device.h>
#include <linux/leds.h>
#include <linux/err.h>
#include <asm/io.h>
#include <linux/module.h>

#define DRVNAME "sunxi-pwm"

struct pwm_led {
	struct led_classdev	cdev;
	unsigned int entire_cycles;
	unsigned int active_cycles;
	unsigned int step_cycles;
	unsigned int step;
};

static void sunxi_led_brightness(struct led_classdev *cdev, enum led_brightness b)
{
	struct pwm_led *led;

	/* update the duty cycle for the *next* period */
	led = container_of(cdev, struct pwm_led, cdev);
	pwm_channel_writel(&led->pwmc, PWM_CUPD, led->mult * (unsigned) b);
}

static int __devinit sunxi_pwm_probe(struct platform_device *pdev)
{
	struct pwm_led *led;
	int i;
	int status;

	led = kzalloc(sizeof(*leds), GFP_KERNEL);
	if (!led)
		return -ENOMEM;

	led->cdev.name = "sunxi-led";
	led->cdev.brightness = LED_OFF;
	led->cdev.brightness_set = sunxi_led_brightness;
	led->cdev.default_trigger = "default-on"

	/* Hand it over to the LED framework */
	status = led_classdev_register(&pdev->dev, &led->cdev);
	if (status < 0) {
		printk(KERN_ERR "led register failed\n")
		goto err;
	}

	platform_set_drvdata(pdev, led);
	return 0;

err:
	kfree(led);
	return status;
}

static struct platform_driver sunxi_pwm_driver = {
	.probe	= sunxi_pwm_probe,
	.remove	= sunxi_pwm_remove,
	.driver	= {
		.name	= DRVNAME,
		.owner	= THIS_MODULE,
	},
};

static struct platform_device *pdev;
static int __init sunxi_pwm_init(void)
{
	int ret;

	ret = platform_driver_register(&sunxi_pwm_driver);
	if (ret < 0)
		goto out;

	pdev = platform_device_register_simple(DRVNAME, -1, NULL, 0);
	if (IS_ERR(pdev)) {
		ret = PTR_ERR(pdev);
		platform_driver_unregister(&sunxi_pwm_driver);
		goto out;
	}

	return 0;
out:
	printk(KERN_ERR "init sunxi pwm failed\n");
	return ret;
}

static void __exit sunxi_pwm_exit(void)
{
	platform_device_unregister(pdev);
	platform_driver_unregister(&sunxi_pwm_driver);
}

module_init(sunxi_pwm_init);
module_exit(sunxi_pwm_exit);

MODULE_AUTHOR("Allwinner");
MODULE_DESCRIPTION("Allwinner soc pwm driver");
MODULE_LICENSE("GPL");

