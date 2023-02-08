# INSTALL PACKAGES

apt install -y nano \
               openssh-server \
               build-essential \
               librtmidi-dev \
               nlohmann-json3-dev \
               libfftw3-dev libasound2-dev \
               libi2c-dev \
               python3-pip \
               alsa-base \
               alsa-tools \
               pulseaudio 

# START PULSE AUDIO (For now this will need to be done every time you boot up)

pulseaudio --start 

# GET I2C OVERLAYS

git clone https://github.com/libre-computer-project/libretech-overlays.git
cd libretech-overlays
make
cp -r overlays/*.dtbo /lib/firmware

# INSTALL OVERLAYS (For now this will need to be done every time you boot up)

./overlay.sh add libretech-cc-i2c-ao
./overlay.sh add libretech-cc-i2c-b
cd ~
