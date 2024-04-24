DOCKER_IMG := n64_tool_chain_img
DOCKER := $(shell command -v docker 2> /dev/null)
OS := $(shell uname)
APT := $(shell command -v apt 2> /dev/null)
DNF := $(shell command -v dnf 2> /dev/null)

SHELL := $(shell which sh)
d := $(CURDIR)

.PHONY: build init_n64_env setup_n64_toolchain

# Run Docker cmd with provided image:
# https://dzone.com/articles/docker-x11-client-via-ssh
DOCKER_CMD := docker run --rm -it \
              -w $(d) \
              -u $(shell id -u):$(shell id -g) \
              -v $(d):$(d) \
              -v /etc/passwd:/etc/passwd:ro \
              -v /etc/group:/etc/group:ro \
              --net=host \
              -e DISPLAY \
              -v $(HOME)/.Xauthority:/root/.Xauthority:rw

# Print help:
.PHONY: help
help:
	@echo "Available targets:"
	@echo "  dockersetup    : Setup n64chain using Docker"
	@echo "  dockerbuild    : Build the N64 apps using Docker"
	@echo "  dockerrun      : Log in to the Docker image"
	@echo "  dockerlist     : List Docker image"
	@echo "  deps           : Install Linux host dependencies for Debian/Ubuntu/Fedora"
	@echo "  hostsetup      : Setup n64chain for host"
	@echo "  manual         : Open the online N64 manual"
	@echo "  clean          : Clean build artifacts"

# Check that Docker is installed:
.PHONY: checkdocker
checkdocker:
ifndef DOCKER
	$(error Please install Docker first!)
endif

# Setup n64chain using Docker:
.PHONY: dockersetup
dockersetup: checkdocker
	@docker build -t $(DOCKER_IMG) .

# Build the N64 apps using Docker:
.PHONY: dockerbuild
dockerbuild: checkdocker
	@$(DOCKER_CMD) $(DOCKER_IMG) ./build.sh

# Log in to the Docker image:
.PHONY: dockerrun
dockerrun: checkdocker
	@$(DOCKER_CMD) $(DOCKER_IMG)

# List Docker image:
.PHONY: dockerlist
dockerlist: checkdocker
	@docker image list $(DOCKER_IMG)

# Install host dependencies:
.PHONY: deps
deps:
ifeq ($(OS), Linux)
ifdef APT
	@echo "*** Installing host dependencies using APT"
	@sudo apt install -y `cat ./pkg/debian_dependencies.txt`
else ifdef DNF
	@echo "*** Installing host dependencies using DNF"
	@sudo dnf install -y `cat ./pkg/fedora_dependencies.txt`
else
	$(error This system does not support APT or DNF)
endif
else
	$(error $(OS) is not supported)
endif

# Setup n64chain for host:
.PHONY: hostsetup
hostsetup: checkdocker
ifeq ($(OS), Linux)
	@./setup_n64_toolchain.sh
else
	$(error $(OS) is not supported)
endif

# Open the online N64 manual:
.PHONY: manual
manual:
ifeq ($(OS), Linux)
	@xdg-open https://ultra64.ca/files/documentation/online-manuals/man-v5-2/allman52/ > /dev/null 2>&1
else
	@echo "https://ultra64.ca/files/documentation/online-manuals/man-v5-2/allman52/"
endif

# Clean build artifacts:
.PHONY: clean
clean:
	$(MAKE) -C SimpleN64Demo clean
	$(MAKE) -C SimpleN64DemoNusys clean
