# GPIOs

GPIOs on Le Potato are accessible through two `/dev` entries:

```txt
/dev/gpiochip0
/dev/gpiochip1
```

The C library to use to work with these is [gpio.h](https://github.com/torvalds/linux/blob/master/include/asm-generic/gpio.h) which is part of the Linux Kernel. By far the most straightfoward way to access GPIOs is to is the standard UNIX [ioctl](https://man7.org/linux/man-pages/man2/ioctl.2.html) function, which is used to access character devices in `/dev`. You open them with `open`, manipulate them with `ioctl` and close them with `close`. The <gpio.h> header defines some types (gpiohandle_request and gpiohandle_data) and flags (GPIOHANDLE_REQUEST_OUTPUT and GPIOHANDLE_SET_LINE_VALUES_IOCTL) you can use.

A very simple example is `blink.c` in this directory, which was adapted from Dany LE's [post on the subject](https://blog.lxsang.me/post/id/33). Compile blink.c with 

```bash
gcc blink.c -o blink
```

And then connect something like an LED with a resistor, or an oscilloscope probe, from a ground pin to a GPIO pin of your choice. To understand which pins do what, look at the [Potato Pin Out](https://docs.google.com/spreadsheets/d/1U3z0Gb8HUEfCIMkvqzmhMpJfzRqjPXq7mFLC-hvbKlE/edit#gid=0). There are pins numbered in the 400s and 500s. The ones in the 500s are accessible via `/dev/gpiochip0` and the appropriate offset. So, for example, to make pin 507 blink, you do run `blink` with

```bash
sudo ./blink /dev/gpiochip0 7
```

The pins in the 400s are accsible via `/dev/gpiochip1`. 