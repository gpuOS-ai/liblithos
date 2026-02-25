# liblithos

Interpose the CUDA Driver API.

In its current state, this code supports CUDA 10.2 and only interposes
_cuInit_().

## Quick Start

```sh
make test
```

On Ubuntu, you may need to `make CUDA_PATH=/usr/local/cuda`.

## Next Steps

- [ ] To support later versions of CUDA, interpose _cuGetProcAddress_()
- [ ] Later versions of CUDA provide type definitions for each interface,
      making a type-safe _interpose_() macro possible
