FROM archlinux:20200505

RUN pacman -Suy;                                                                                             \
    pacman -S --noconfirm git python python-pip python-setuptools libffi                                     \
                          arm-none-eabi-gcc avrdude dfu-programmer                                           \
                          dfu-util make diffutils avr-libc;                                                  \
    pacman -U --noconfirm https://archive.archlinux.org/packages/a/avr-gcc/avr-gcc-8.3.0-1-x86_64.pkg.tar.xz

RUN python3 -m pip install qmk

RUN qmk setup -y && chmod -R ugo+rwX /root/qmk_firmware

WORKDIR /root/qmk_firmware

ENTRYPOINT ["qmk"]
