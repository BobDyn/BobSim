FROM openmodelica/openmodelica:latest

# Install Python 3.14
RUN apt-get update && apt-get install -y \
    software-properties-common \
    && add-apt-repository ppa:deadsnakes/ppa \
    && apt-get update && apt-get install -y \
    python3.14 \
    python3.14-dev \
    python3.14-distutils \
    curl \
    && curl -sS https://bootstrap.pypa.io/get-pip.py | python3.14 \
    && apt-get clean

# Set python3.14 as default
RUN update-alternatives --install /usr/bin/python python /usr/bin/python3.14 1

# Install Python dependencies
RUN pip install \
    pyyaml \
    scipy \
    pandas \
    pyarrow

# Install Modelica 3.2.3 at build time
RUN omc -e 'installPackage(Modelica, "3.2.3+maint.om", exactMatch=true);'

# Working directory inside container
WORKDIR /doe

CMD ["/bin/bash"]