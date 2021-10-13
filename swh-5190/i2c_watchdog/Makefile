# I2C tools for Linux
#
# Copyright (C) 2007-2012  Jean Delvare <jdelvare@suse.de>
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.

DESTDIR	?=
PREFIX	?= /usr/local
bindir	= $(PREFIX)/bin
sbindir	= $(PREFIX)/sbin
mandir	= $(PREFIX)/share/man
man3dir	= $(mandir)/man3
man8dir	= $(mandir)/man8
incdir	= $(PREFIX)/include
libdir	= $(PREFIX)/lib

INSTALL		:= install
INSTALL_DATA	:= $(INSTALL) -m 644
INSTALL_DIR	:= $(INSTALL) -m 755 -d
INSTALL_PROGRAM	:= $(INSTALL) -m 755
LN		:= ln -sf
RM		:= rm -f

CC	?= gcc
AR	?= ar
STRIP	?= strip

CFLAGS		?= -O2
# When debugging, use the following instead
#CFLAGS		:= -O -g
CFLAGS		+= -Wall
SOCFLAGS	:= -fpic -D_REENTRANT $(CFLAGS)

BUILD_DYNAMIC_LIB ?= 1
BUILD_STATIC_LIB ?= 1
USE_STATIC_LIB ?= 1

ifeq ($(USE_STATIC_LIB),1)
BUILD_STATIC_LIB := 1
endif

ifeq ($(BUILD_DYNAMIC_LIB),0)
ifeq ($(BUILD_STATIC_LIB),0)
$(error BUILD_DYNAMIC_LIB and BUILD_STATIC_LIB cannot be disabled at the same time)
else
USE_STATIC_LIB := 1
endif
endif

KERNELVERSION	:= $(shell uname -r)

.PHONY: all strip clean install uninstall

all:

EXTRA	:=
SRCDIRS	:= include lib src $(EXTRA)
include $(SRCDIRS:%=%/Module.mk)
