# install pico sdk files
install:
	git clone https://github.com/raspberrypi/openocd.git --branch rp2040 --depth=1 --no-single
	git clone https://github.com/raspberrypi/pico-examples.git --depth=1
	git clone https://github.com/raspberrypi/pico-sdk.git --depth=1;cd pico-sdk;git submodule update --init
	git clone https://github.com/raspberrypi/pico-project-generator.git --depth=1
	git clone https://github.com/raspberrypi/picotool.git --depth=1
	git clone https://github.com/raspberrypi/picoprobe.git --depth=1

# update pico sdk files
update:
	cd pico-sdk;git pull;git submodule update

# create group for access
create_group:
	groups
	sudo groupadd plugdev
	sudo usermod -a -G plugdev `whoami`

# create acess for usb
access_usb:
	@echo"cd into openocd folder first"
	sudo cp ./openocd/contrib/60-openocd.rules /etc/udev/rules.d/
	sudo udevadm control --reload  



help:
	@echo"install      = install pico sdk files"
	@echo"udpate       = update the pico sdk files"
	@echo"create_group = create group for access"
	@echo"access_usb   = copy rules for access to the usb"