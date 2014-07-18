cmake_minimum_required(VERSION 2.6)
project(MordorReboot)

find_package(PkgConfig)

pkg_check_modules(GTKMM gtkmm-3.0)

add_subdirectory(source)
