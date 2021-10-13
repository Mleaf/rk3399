# I2C watchdog for Linux
#
# Copyright (C) 2021 mleaf <mleaf90@gmail.com>
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.

I2C_DIR	:= src

I2C_CFLAGS	+= -Wstrict-prototypes -Wshadow -Wpointer-arith -Wcast-qual \
		   -Wcast-align -Wwrite-strings -Wnested-externs -Winline \
		   -W -Wundef -Wmissing-prototypes -Iinclude
ifeq ($(USE_STATIC_LIB),1)
I2C_LDFLAGS	+= $(LIB_DIR)/$(LIB_STLIBNAME)
else
I2C_LDFLAGS	+= -L$(LIB_DIR) -li2c
endif

I2C_TARGETS	:= i2c_watchdog

#
# Programs
#

$(I2C_DIR)/i2c_watchdog: $(I2C_DIR)/i2c_watchdog.o $(I2C_DIR)/i2cbusses.o $(LIB_DEPS)
	$(CC) $(LDFLAGS) -o $@ $^ $(I2C_LDFLAGS)

#
# Objects
#

$(I2C_DIR)/i2c_watchdog.o: $(I2C_DIR)/i2c_watchdog.c $(I2C_DIR)/i2cbusses.h version.h $(INCLUDE_DIR)/i2c/smbus.h
	$(CC) $(CFLAGS) $(I2C_CFLAGS) -c $< -o $@

$(I2C_DIR)/i2cbusses.o: $(I2C_DIR)/i2cbusses.c $(I2C_DIR)/i2cbusses.h
	$(CC) $(CFLAGS) $(I2C_CFLAGS) -c $< -o $@

#
# Commands
#

all-i2c: $(addprefix $(I2C_DIR)/,$(I2C_TARGETS))

strip-i2c: $(addprefix $(I2C_DIR)/,$(I2C_TARGETS))
	$(STRIP) $(addprefix $(I2C_DIR)/,$(I2C_TARGETS))

clean-i2c:
	$(RM) $(addprefix $(I2C_DIR)/,*.o $(I2C_TARGETS))

install-i2c: $(addprefix $(I2C_DIR)/,$(I2C_TARGETS))
	$(INSTALL_DIR) $(DESTDIR)$(sbindir) $(DESTDIR)$(man8dir)
	for program in $(I2C_TARGETS) ; do \
	$(INSTALL_PROGRAM) $(I2C_DIR)/$$program $(DESTDIR)$(sbindir) ; \
	$(INSTALL_DATA) $(I2C_DIR)/$$program.8 $(DESTDIR)$(man8dir) ; done

uninstall-i2c:
	for program in $(I2C_TARGETS) ; do \
	$(RM) $(DESTDIR)$(sbindir)/$$program ; \
	$(RM) $(DESTDIR)$(man8dir)/$$program.8 ; done

all: all-i2c

strip: strip-i2c

clean: clean-i2c

install: install-i2c

uninstall: uninstall-i2c
