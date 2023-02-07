# INSTALL PACKAGES

apt install -y nano \
               openssh-server \
               build-essential \
               librtmidi-dev \
               nlohmann-json3-dev \
               libfftw3-dev libasound2-dev \
               libi2c-dev \
               python3-pip \

# SOUND TOOLS

apt install -y  alsa-base \
                alsa-tools \
                pulseaudio 
                
pulseaudio --start 

# INSTALL I2C OVERLAYS

git clone https://github.com/libre-computer-project/libretech-overlays.git
cd libretech-overlays
make
cp -r overlays/*.dtbo /lib/firmware
./overlay.sh add libretech-cc-i2c-ao
./overlay.sh add libretech-cc-i2c-b
cd ~
