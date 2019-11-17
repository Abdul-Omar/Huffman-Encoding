#!/usr/bin/env bash
echo "Building reference solution..."

if [ ! -d "build_refsol" ]; then
    meson build_refsol --default-library=static
fi

ninja -C build_refsol
