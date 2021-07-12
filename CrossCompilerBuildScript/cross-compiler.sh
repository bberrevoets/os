#!/bin/bash

if [ "$#" -ne 1 ]; then
  export TARGET=i686-elf
else
  export TARGET=$1
fi

sudo apt install gnu-efi grub-common xorriso g++ make nasm libgmp3-dev libmpfr-dev libisl-dev libmpc-dev texinfo qemu-system-x86-xen -y

cd "$(dirname "$0")"

mkdir out
cd out

mkdir src
cd src

wget https://ftp.gnu.org/gnu/binutils/binutils-2.33.1.tar.xz
wget https://ftp.gnu.org/gnu/gcc/gcc-9.2.0/gcc-9.2.0.tar.xz

echo "Unpacking binutils..."
tar -xf binutils-2.33.1.tar.xz
echo "Unpacking gcc..."
tar -xf gcc-9.2.0.tar.xz

export PREFIX="$HOME/opt/cross"
export PATH="$PREFIX/bin:$PATH"

mkdir build-binutils
cd build-binutils
../binutils-2.33.1/configure --target=$TARGET --prefix="$PREFIX" --with-sysroot --disable-nls --disable-werror
make -j $(nproc)
make install

cd ..
mkdir build-gcc
cd build-gcc
../gcc-9.2.0/configure --target=$TARGET --prefix="$PREFIX" --disable-nls --enable-languages=c,c++ --without-headers
make -j $(nproc) all-gcc
make -j $(nproc) all-target-libgcc
make install-gcc
make install-target-libgcc

cd ../../..
rm -rf out/

LINE='export PATH=/home/bert/opt/cross/bin:$PATH # Cross Script Builder'
FILE='/home/bert/.bashrc'
grep -xqF -- "$LINE" "$FILE" || echo "$LINE" >> "$FILE"
