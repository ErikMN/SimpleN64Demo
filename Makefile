DOCKER_IMG := n64_tool_chain_img
DOCKER := $(shell command -v docker 2> /dev/null)

SHELL := $(shell which sh)
d := $(CURDIR)

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
	@echo "  setup          : Create the Docker image $(DOCKER_IMG)"
	@echo "  build          : Build the N64 apps"
	@echo "  dockerrun      : Log in to the Docker image"
	@echo "  dockerlist     : List Docker image"
	@echo "  clean          : Clean build artifacts"

# Check that Docker is installed:
.PHONY: checkdocker
checkdocker:
ifndef DOCKER
	$(error Please install Docker first!)
endif

# Create Docker image to build in:
.PHONY: setup
setup: checkdocker
	@docker build -t $(DOCKER_IMG) .

# Build the N64 apps:
.PHONY: build
build:
	@$(DOCKER_CMD) $(DOCKER_IMG) ./build.sh

# Run docker image:
.PHONY: dockerrun
dockerrun: checkdocker
	@$(DOCKER_CMD) $(DOCKER_IMG)

# List Docker image:
.PHONY: dockerlist
dockerlist: checkdocker
	@docker image list $(DOCKER_IMG)

# Clean build artifacts:
.PHONY: clean
clean:
	$(MAKE) -C SimpleN64Demo clean
	$(MAKE) -C SimpleN64DemoNusys clean
