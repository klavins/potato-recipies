# Getting Adafruit's Stemma Qt Rotary Encoders

To make sure i2c is working, I connected one of Adafruit's Stemma Qt Rotary Encoders to pins 3 and 5 on the Potato. That's not enought to get them to work though. These little boards use the Seesaw chip, which is programmed to send and receive specific commands over i2c. We can use Adafruit's Circuit Python to interact with the encoder. The file `rotary.py` in this directory shows how.

Before it can be used, we need to install some tools:

```bash
sudo apt install python3-pip
sudo pip3 install adafruit-seesaw
sudo pip3 install adafruit-circuitpython-seesaw
sudo pip3 install gpiod
```

Then you should be able to run

```bash
sudo python3 rotary.py
```

and see the value of the encoder printed on the screen. 