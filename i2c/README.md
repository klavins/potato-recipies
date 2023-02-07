I2C Devices With Registers
===

> NOTE: None of this is Potato Specific. It's all just Linux. 

The way you talk to many I2C devices is via registers. These can be set or read from. By setting registers you can turn on and off various parameters of a chip. And by reading registers, you can determine their status. 

In this directory are two programs. One that reads from I2C registers, and one that writes to them. The Linux Kernel describes how to write such code [here](https://docs.kernel.org/i2c/dev-interface.html). Essentially, you open the appropriate `/dev/i2c-*` device and send characters to it. 

Reading
---

You should study the file `read.c` and make sure you understand what it is doing. It uses the following functions:
- `open` from the standard unix library <fcntl.h>
- `ioctl` from the standard unix library <sys/ioctl.h>
- `i2c_smbus_read_byte_data` from the somewhat more modern linix library <<i2c/smbus.h>

The `i2c` development library needs to be installed with

```bash
sudo apt install libi2c-dev
```

Then you can compile and run the code with 

```bash
gcc read.c -li2c -o read
sudo ./read 0x20
```

which should give you the contents of register 20 of whatever device you have hooked up. 

Writing
---

You should also study the `write.c` file. It uses the additional method `i2c_smbus_write_byte_data`. You can compile and run this code with

```bash
gcc write.c -li2c -o write
sudo ./write 0x20 01010101
```

The command will show the contents of register 0x20 before and after writing the byte 01010101. 

By using the `read` and `write` commands you can in principle talk to any I2C device that uses registers, configure it, turn it on and off, etc. 

Device Drivers
===

Many i2c *device drivers* essentially just set and read from registers. In fact, the device at `/dev/i2c-1` is manager by a very simple device driver that is described in the Libretech Overlays (see the main README in this repo). And the `read` and `write` methods above could be seen as *user space* device drivers that make it easier to talk to I2C devices with registers. 

As there may be dozens of such registers, each with its own semantics, it is nice to have a device driver to keep track of things. Most distributions of Linux ship with an enormous list of device drivers. On Le Potato, you can see a list of those involved in sound with:

```bash
ls /lib/modules/6.0.12*/kernel/sound/soc/codecs/
```

In fact, there is one called `snd-soc-pcm186x-i2c`, which is for the PCM1863. 

Modules can be loaded with `modprobe` as in:

```bash
sudo modprobe snd-soc-pcm186x-i2c
```

At the time of this writing I have no idea what this does or how to interact with it. I do notice that loading the driver makes a new `sysfs` entries at:

```bash
/sys/module/snd_soc_pcm186x
/sys/module/snd_soc_pcm186x_i2c
```

As I said, I have no idea how to interact with them. Usually, you write characters to various virtual files in such directories, but I can't find any documentation. 

That said, the code for these drivers is in the Linux Kernel, and can be found in 

```bash
https://github.com/torvalds/linux/tree/master/sound/soc/codecs
```