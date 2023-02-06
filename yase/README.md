# Yase on Le Potato

Note: Somehow the sound coming from the stero headphone jack is linked to the HDMI driver. So if you log in using using the default console (not just ssh) with a keyboard, then sound will work. But if you are not only logged in through ssh, then you won't get any sound. What I have been doing is logging in with the keyboard and a monitor, and then unplugging the keyboard and monitor (for convenience), and running yase through ssh. 

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
make
cd BigSound
make
./bin/big_sound
```

Note that I recently updated yase/potato so that:
- The Makefile makes the directories build and lib
- The example Makefiles point to `../potato_defs.mk` instead of `../defs.mk`.

NOTE: On my Potato, I only get sound from the headphone jack if I am logged into the console (not via ssh). Although you can log in, disconnect the HDMI and keyboard, and then use yase from ssh to hear sound from the jack. 