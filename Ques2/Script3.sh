rm -r -f KernelBuild3
mkdir KernelBuild3
cp linux-5.19.9.tar.xz KernelBuild3/linux-5.19.9.tar.xz
cd KernelBuild3
tar -xvf linux-5.19.9.tar.xz
cd linux-5.19.9
make mrproper
cp ../../configFile ./.config
make -j$(nproc)