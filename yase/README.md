# Yase on Le Potato

First, install some prerequisites:

```bash
sudo apt install librtmidi-dev nlohmann-json3-dev libfftw3-dev libasound2-dev
```

Then get the [code](https://github.com/klavins/yase). 

```bash
git clone https://github.com/klavins/yase.git
cd yase/potato
```

Before compiling, edit `potato-defs.mk` and change the line

```txt
ROOT_DIR    := /home/klavins/yase
```
to point to whever you put the yase directory.

Finally, compile yase, and run an example. 

```bash
cd yase
cd potato
mkdir build
make
cd BigSound
make
./bin/big_sound
```