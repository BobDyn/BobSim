FROM openmodelica/openmodelica:v1.26.3-ompython

ENV DEBIAN_FRONTEND=noninteractive
ENV PYTHONUNBUFFERED=1
ENV PIP_NO_CACHE_DIR=1
ENV VIRTUAL_ENV=/opt/venv
ENV PATH="/opt/venv/bin:${PATH}"

WORKDIR /workspace

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