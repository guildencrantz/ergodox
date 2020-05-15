SHELL = /usr/local/bin/zsh

.DEFAULT_GOAL=compile

.PHONY:
docker-build:
	@[ "$$(docker images --format '{{.CreatedAt}}' qmk:latest | xargs -I {} date -j -f '%Y-%m-%d %T %z %Z' '{}' '+%s')" -ge "$$(stat -f '%m' Dockerfile)" ] || docker build -t qmk .

build/ergodox_ez_km.hex: config.h keymap.c rules.mk | docker-build
	docker run --rm -it -u $$(id -u) -v $(CURDIR):/root/qmk_firmware/keyboards/ergodox_ez/keymaps/km -v $(CURDIR)/build:/root/qmk_firmware/.build qmk:latest compile -kb ergodox_ez -km km

compile: build/ergodox_ez_km.hex
