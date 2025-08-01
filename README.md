# gr4-block-tutorial

This repo is designed to show how to create simple blocks in GR4

## Setup

```
cd gr4-block-tutorial
docker run -it -v `pwd`:/code ghcr.io/mormj/gr4-oot-env:latest bash # this defaults to the /code directory
meson setup build
cd build
ninja
ninja test
```

