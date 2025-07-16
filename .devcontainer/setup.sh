#!/bin/bash
sudo apt-get update && sudo apt-get install -y build-essential wget git unzip
wget https://github.com/devkitPro/pacman/releases/download/v1.0.2/devkitpro-pacman.amd64.deb
sudo dpkg -i devkitpro-pacman.amd64.deb
sudo dkp-pacman -Syu
sudo dkp-pacman -S gba-dev --noconfirm
echo 'export DEVKITPRO=/opt/devkitpro' >> ~/.bashrc
echo 'export DEVKITARM=/opt/devkitpro/devkitARM' >> ~/.bashrc
source ~/.bashrc
