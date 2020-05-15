SHELL = /usr/local/bin/zsh

.DEFAULT_GOAL=compile

.PHONY:
docker-build:
	@$(eval _MD5 := $(shell md5sum Dockerfile | awk '{ print $$1 }')) 
	@[ "$$(docker images qmk:$(_MD5) | wc -l)" -eq 2 ] || docker build -t qmk:$(_MD5) .

build/ergodox_ez_km.hex: config.h keymap.c rules.mk | docker-build
	docker run --rm -it -u $$(id -u) -v $(CURDIR):/root/qmk_firmware/keyboards/ergodox_ez/keymaps/km -v $(CURDIR)/build:/root/qmk_firmware/.build qmk:$(_MD5) compile -kb ergodox_ez -km km

compile: build/ergodox_ez_km.hex
