FROM openmodelica/openmodelica:v1.27.1-ompython

ENV DEBIAN_FRONTEND=noninteractive
ENV PYTHONUNBUFFERED=1
ENV PIP_NO_CACHE_DIR=1
ENV VIRTUAL_ENV=/opt/venv
ENV PATH="/opt/venv/bin:${PATH}"

WORKDIR /workspace

# The pinned base image supplies omc. No additional OpenModelica apt packages are needed.
RUN rm /etc/apt/sources.list.d/openmodelica.list \
    && apt-get update && apt-get install -y --no-install-recommends \
    ca-certificates \
    curl \
    git \
    software-properties-common \
    tzdata \
    && add-apt-repository -y ppa:deadsnakes/ppa \
    && apt-get update && apt-get install -y --no-install-recommends \
    python3.11 \
    python3.11-dev \
    python3.11-venv \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

COPY requirements.txt /tmp/requirements.txt

RUN python3.11 -m venv "${VIRTUAL_ENV}" \
    && python -m pip install --upgrade pip \
    && python -m pip install -r /tmp/requirements.txt

# Pre-download the OpenModelica package index with a longer curl timeout.
# This avoids relying on OpenModelica's shorter internal curl timeout.
RUN mkdir -p /root/.openmodelica/libraries \
    && curl -fL \
        --retry-connrefused \
        --retry 10 \
        --retry-delay 5 \
        --connect-timeout 60 \
        --max-time 600 \
        -o /root/.openmodelica/libraries/index.json \
        https://libraries.openmodelica.org/index/v1/index.json

# Install the Modelica libraries expected by BobLib.
# The package index has already been cached above.
RUN printf '\
installPackage(Modelica, "4.1.0", exactMatch=true);\n\
installPackage(VehicleInterfaces, "2.0.2", exactMatch=true);\n\
getErrorString();\n' > /tmp/setup.mos \
    && omc /tmp/setup.mos \
    && rm /tmp/setup.mos

RUN git config --global --add safe.directory /workspace \
    && git config --global --add safe.directory /workspace/engines/boblib

CMD ["/bin/bash"]
