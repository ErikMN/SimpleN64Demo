FROM ubuntu:latest

RUN apt-get update && \
  apt-get install -y -f --no-install-recommends \
  git \
  ca-certificates \
  wget \
  build-essential \
  libmpfr-dev \
  libmpc-dev \
  libgmp-dev \
  flex \
  bison \
  texinfo \
  p7zip-full \
  cmake \
  libgl1-mesa-dev \
  libopenal-dev && \
  apt-get clean && \
  rm -rf /var/lib/apt/lists/*
