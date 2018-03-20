FROM alekzonder/archlinux-yaourt:latest

ENV TERM xterm
ENV MAKEFLAGS j9
RUN pacman -S gcc clang clang-tools-extra cmake ninja --noconfirm 
RUN sudo -u yaourt yaourt -S cpprestsdk-git --noconfirm

RUN pacman -S gtest gmock git --noconfirm
RUN sudo -u yaourt yaourt -S libcurlpp spdlog-git --noconfirm
