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

# BobLib and the Modelica Standard Library are loaded from
# _0_Utils/external/ at runtime through the mounted repository.
#
# This avoids relying on libraries.openmodelica.org during Docker builds
# or user simulation runs.

CMD ["/bin/bash"]