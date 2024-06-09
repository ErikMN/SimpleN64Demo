FROM ubuntu:noble

COPY pkg/debian_dependencies.txt /opt/

RUN apt-get update && \
  xargs -a /opt/debian_dependencies.txt apt-get install -y -f --no-install-recommends && \
  apt-get clean && rm -rf /var/lib/apt/lists/*

COPY setup_n64_toolchain.sh /opt/
COPY init_n64_env.sh /opt/

RUN chmod +x /opt/setup_n64_toolchain.sh && chmod +x /opt/init_n64_env.sh

# Execute setup_n64_toolchain.sh during image build:
RUN /opt/setup_n64_toolchain.sh

# NOTE: to avoid the need to run as root:
RUN chmod -R 555 /opt/n64chain
