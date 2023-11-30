# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/Users/eSpark/espv4/esp-idf/components/bootloader/subproject"
  "D:/VScode_Projects/test-led/build/bootloader"
  "D:/VScode_Projects/test-led/build/bootloader-prefix"
  "D:/VScode_Projects/test-led/build/bootloader-prefix/tmp"
  "D:/VScode_Projects/test-led/build/bootloader-prefix/src/bootloader-stamp"
  "D:/VScode_Projects/test-led/build/bootloader-prefix/src"
  "D:/VScode_Projects/test-led/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "D:/VScode_Projects/test-led/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
