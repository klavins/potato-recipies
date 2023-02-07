A Smaller Linux Distribution
===

The descktop distribution described in the main README is huge and has way more than we need. The base on the other hand is amll, but has hardliy anything. So here's a way to add to the base only what we need.

Start by putting this stribution on an SD card an logging in as `root` with password `root`.

> https://distro.libre.computer/ci/ubuntu/22.10/ubuntu-22.10-preinstalled-base-arm64%2Baml-s905x-cc.img.xz

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

Now you can run the following command to install all the extras we will need

```bash
source install.sh
```

Go get some coffee, this will take a while.