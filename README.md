# Potato Recipes

* Installing the right version of Linux (This Readme)
* [Installing Yase](yase)
* [Manipulating GPIOs](gpio)
* [Using i2c with Adafruit's Rotary Encoders](adafruit-rotary)
* [Using I2C registers](i2c)
* [Toward a Smaller Linux Image](small-linux)
* [Links to Useful Potato Things](links.md)

# Installing Linux

## Which Distro To Use

For our purposes, we need a Linux Kernel that was built for the Potato and that was compiled with Device Tree Support. The only one I've found that works is the [Ubuntu 22.04 Distro](https://distro.libre.computer/ci/ubuntu/22.04/) by Libre. I tried the "server" distro, but for some reason the cloud-init step didn't work. So then I tried the Desktop Server:

> [ubuntu-22.04.1-preinstalled-desktop-arm64+aml-s905x-cc.img.xz](https://distro.libre.computer/ci/ubuntu/22.04/ubuntu-22.04.1-preinstalled-desktop-arm64%2Baml-s905x-cc.img.xz)

***Note***: My Potato will not boot with any USB devices plugged in. So I plug them once it is done booting. 

This distro seems to have what we need, which you can tell by doing

```bash
ls /sys/kernel/config/
```

which includes a directory called `device-tree`. Awesome.

[TODO: Try the base server and add only the apt packages we need.]

[TODO: Build our own distro.]

## Don't Use the Desktop

The first time you log in, you'll get the Ubuntu GUI Desktop thing. The itty bitty Potato can't handle all its compute requirements. So the first theng to do after you make an account is open a terminal, and type

```bash
sudo init 3
```

This will put you in console mode. Whew. So much more responsive.
We want to make this permanent, so that every time we boot we go to the console. To do this just log in and do

```bash
sudo systemctl set-default multi-user.target
```
## SSH

I like to ssh into the potato so I don't need to plug in the monitor and keyboard all the time. And I can use my laptop which is way more convenient. To do this, do:

```bash
sudo apt install  openssh-server
```

Which installs and enables ssh. You an check your IP address with

```bash
hostname -I
```

For me this shows my potatos IP address on my local home network as 192.168.86.26. 
As long as your laptop is on the same network, you can ssh in with:

```bash
ssh username@192168.86.26
```

I like to open several sessions. One for editing files, one for running commands, and one for looking around. 


## How to Get i2c Working

The Potato has two i2c channels. One is called i2c-ao and is on pins 3 and 5. The other is called i2c-b, and is on pins 27 and 28. By default, these are not exposed to Linux. You can see that if you do

```bash
ls /dev/i2c*
```

which will only show `i2c-0`, which I believe is for the HDMI port. 

Do add the other two, we can use the [recipe](https://github.com/libre-computer-project/libretech-overlays) from LibreTech as follows:

```bash
git clone https://github.com/libre-computer-project/libretech-overlays.git
cd libretech-overlays
make
sudo cp -r overlays/*.dtbo /lib/firmware
sudo ./overlay.sh add libretech-cc-i2c-ao
sudo ./overlay.sh add libretech-cc-i2c-b
```

Now if you look in `/dev` you will see `/dev/i2c-0`,  `/dev/i2c-1`, and  `/dev/i2c-2`. You can see what these devices are with

```bash
i2cdetect -l 
```

which for me shows shows

```txt
i2c-0	unknown   	DesignWare HDMI                 	N/A
i2c-1	unknown   	Meson I2C adapter               	N/A
i2c-2	unknown   	Meson I2C adapter               	N/A
```

The i2c channels 1 and 2 are the two Potato i2c channels!

***TODO***: With this setup you need to rerun the `sudo ./overlay.sh add` commands ever time you reboot. But there is certainly a way to configure that to happen on reboot. 

## Showing Attached I2C Devices

First, attach one or more i2C devices:
```bash
Power      Potato Pin 1
Ground     Potato Pin 6
SDA        Potato Pin 3
SCL        Potato Pin 5
```
You could also use pins 27 and 28 for SDA and SCL respectively.

Now, you can run the command

```bash
sudo i2cdetect -y 1
```

to show the addresses your devices got. For example, I connected four [Adafruit Stemma Qt Encoders](https://www.adafruit.com/product/4991), which with a different soldered address. The above command shows:

```txt
     0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f
00:                         -- -- -- -- -- -- -- -- 
10: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
20: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
30: -- -- -- -- -- -- 36 37 38 -- 3a -- -- -- -- -- 
40: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
50: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
60: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
70: -- -- -- -- -- -- -- --  
```
