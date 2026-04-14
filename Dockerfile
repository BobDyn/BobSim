FROM openmodelica/openmodelica:v1.26.3-ompython

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    software-properties-common \
    tzdata \
    && add-apt-repository ppa:deadsnakes/ppa \
    && apt-get update && apt-get install -y \
    python3.14 \
    python3.14-dev \
    curl \
    && curl -sS https://bootstrap.pypa.io/get-pip.py | python3.14 \
    && apt-get clean

RUN update-alternatives --install /usr/bin/python python /usr/bin/python3.14 1

RUN pip install \
    pyyaml \
    scipy \
    pandas \
    pyarrow \
    numpy \
    matplotlib

# Write and run a .mos script to install Modelica standard library
# omc treats files ending in .mos as scripting files, not Modelica source
RUN printf 'updatePackageIndex();\ninstallPackage(Modelica, "3.2.3+maint.om", exactMatch=true);\ngetErrorString();\n' > /tmp/setup.mos \
    && omc /tmp/setup.mos \
    && rm /tmp/setup.mos
