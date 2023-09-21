rm -r -f KernelBuild2
mkdir KernelBuild2
cp linux-5.19.9.tar.xz KernelBuild2/linux-5.19.9.tar.xz
cd KernelBuild2
tar -xvf linux-5.19.9.tar.xz
cd linux-5.19.9
make mrproper
cp ../../configFile ./.config
make -j$(nproc)