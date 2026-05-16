FROM openmodelica/openmodelica:v1.26.3-ompython

ENV DEBIAN_FRONTEND=noninteractive
ENV PYTHONUNBUFFERED=1
ENV PIP_NO_CACHE_DIR=1
ENV VIRTUAL_ENV=/opt/venv
ENV PATH="/opt/venv/bin:${PATH}"

WORKDIR /workspace

# Add OpenModelica apt repository explicitly.
# The base image has omc installed, but may not keep the apt source enabled,
# which prevents installing optional packages like libomccpp.
RUN apt-get update && apt-get install -y --no-install-recommends \
    ca-certificates \
    curl \
    gnupg \
    && curl -fsSL https://build.openmodelica.org/apt/openmodelica.asc | \
        gpg --dearmor -o /usr/share/keyrings/openmodelica-keyring.gpg \
    && . /etc/os-release \
    && OM_CODENAME="${VERSION_CODENAME:-${UBUNTU_CODENAME}}" \
    && echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/openmodelica-keyring.gpg] https://build.openmodelica.org/apt ${OM_CODENAME} stable" \
        > /etc/apt/sources.list.d/openmodelica.list \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

RUN apt-get update && apt-get install -y --no-install-recommends \
    make \
    git \
    curl \
    ca-certificates \
    tzdata \
    python3 \
    python3-pip \
    python3-dev \
    python3-venv \
    python-is-python3 \
    # libomccpp \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

COPY requirements.txt /tmp/requirements.txt

RUN python3 -m venv "${VIRTUAL_ENV}" \
    && python -m pip install --upgrade pip \
    && python -m pip install -r /tmp/requirements.txt

# Pre-download the OpenModelica package index with a longer curl timeout.
# This avoids relying on OpenModelica's shorter internal curl timeout.
RUN mkdir -p /root/.openmodelica/libraries \
    && curl -L \
        --retry 10 \
        --retry-delay 5 \
        --connect-timeout 60 \
        --max-time 600 \
        -o /root/.openmodelica/libraries/index.json \
        https://libraries.openmodelica.org/index/v1/index.json

# Install the Modelica Standard Library version expected by BobLib.
# The package index has already been cached above.
RUN printf '\
installPackage(Complex, "3.2.3+maint.om", exactMatch=true);\n\
installPackage(ModelicaServices, "3.2.3+maint.om", exactMatch=true);\n\
installPackage(Modelica, "3.2.3+maint.om", exactMatch=true);\n\
getErrorString();\n' > /tmp/setup.mos \
    && omc /tmp/setup.mos \
    && rm /tmp/setup.mos

CMD ["/bin/bash"]