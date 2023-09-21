rm -r -f KernelBuild1
mkdir KernelBuild1
cp linux-5.19.9.tar.xz KernelBuild1/linux-5.19.9.tar.xz
cd KernelBuild1
tar -xvf linux-5.19.9.tar.xz
cd linux-5.19.9
make mrproper
cp ../../configFile ./.config
make -j$(nproc)