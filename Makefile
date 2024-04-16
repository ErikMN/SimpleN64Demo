DOCKER_IMG := n64_tool_chain_img
DOCKER := $(shell command -v docker 2> /dev/null)
DIR := $(shell pwd)

# Run Docker cmd with provided image:
DOCKER_CMD := docker run --rm -i -t \
              -w $(DIR) \
              -u $(shell id -u):$(shell id -g) \
              -v $(DIR):$(DIR) \
              -v /etc/passwd:/etc/passwd \
              -v /etc/group:/etc/group \

# Print help:
.PHONY: help
help:
	@echo "Available targets:"
	@echo "  setup          : Create the Docker image $(DOCKER_IMG)"
	@echo "  build          : Build the N64 toolchain in this directory"

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

# Build the N64 toolchain:
.PHONY: build
build: checkdocker setup
	@$(DOCKER_CMD) $(DOCKER_IMG) ./setup_n64_toolchain.sh
