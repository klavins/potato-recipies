A Smaller Linux Distribution
===

***NOTE: This doesn't work yet. I can't get sound out of the Potato. I don't quite understand how to install and activate all the sound drivers.***

The desktop distribution described in the main README is huge and has way more than we need. The base on the other hand is small, but has hardliy anything in it. So here's a way to add to the base only what we need.

Get the Base Distribution
---

Start by putting this stribution on an SD card an logging in as `root` with password `root`.

> https://distro.libre.computer/ci/ubuntu/22.10/ubuntu-22.10-preinstalled-base-arm64%2Baml-s905x-cc.img.xz

Get the Install Script
---

Next, install `git`, so you can get the code in this directory.

```bash
apt update
apt install git
```

Then clone this repo

```bash
git clone https://github.com/klavins/potato-recipies.git
cd potato-recipes/small-linux
```

Run the install script
---

Now you can run the following command to install all the extras we will need

```bash
source install.sh
```

Go get some coffee, this will take a while.

Get ssh Working
---

Once you are done, you might want to be able to ssh into your Potato. To do this, edit the sshd config file wiht

```bash
nano /etc/ssh/sshd_config
```

and edit the `PermitRootLogin` line to

```bash
PermitRootLogin yes
```

and do

```bash
service ssh restart
```