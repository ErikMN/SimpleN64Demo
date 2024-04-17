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

COPY setup_n64_toolchain.sh /opt/
COPY init_n64_env.sh /opt/

RUN chmod +x /opt/setup_n64_toolchain.sh && chmod +x /opt/init_n64_env.sh

# Execute setup_n64_toolchain.sh during image build:
RUN /opt/setup_n64_toolchain.sh

# NOTE: to avoid the need to run as root:
RUN chmod -R 555 /opt/n64chain
