/**
 * watchdog for swh-5190-v2.2
 * Copyright (C) 2019 Mleaf <mleaf90@gmail.com,350983773@qq.com>
 * 微信公众号 《WiFi物联网》
 *
 * mwol is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * mwol is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <sys/ioctl.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <i2c/smbus.h>
#include "i2cbusses.h"
#include "../version.h"


#define I2C_WATCHDOG_NUM "0"
#define I2C_WATCHDOG_ADDR "0x70"
#define I2C_WATCHDOG_STATUS_POS "0x1c"


typedef enum
{
	DISABLE_MCU_WATCHDOG=0,
	ENABLE_MCU_WATCHDOG,
	INVALID_MCU_WATCHDOG,
}WATCHDOG_STATUS_T;

static void help(void) __attribute__ ((noreturn));

static void help(void)
{
	fprintf(stderr,
		"Usage: i2c_watchdog [-f] [MODE]\n"
		"  MODE is one of:\n"
		"    v (show i2c_watchdog version)\n"
		"    s (show i2c watchdog status)\n"
		"    e (enable i2c watchdog)\n"
		"    d (disable i2c watchdog)\n");
	exit(1);
}

static int check_funcs(int file, int size, int pec)
{
	unsigned long funcs;

	/* check adapter functionality */
	if (ioctl(file, I2C_FUNCS, &funcs) < 0) {
		fprintf(stderr, "Error: Could not get the adapter "
			"functionality matrix: %s\n", strerror(errno));
		return -1;
	}

	switch (size) {
	case I2C_SMBUS_BYTE:
		if (!(funcs & I2C_FUNC_SMBUS_WRITE_BYTE)) {
			fprintf(stderr, MISSING_FUNC_FMT, "SMBus send byte");
			return -1;
		}
		break;

	case I2C_SMBUS_BYTE_DATA:
		if (!(funcs & I2C_FUNC_SMBUS_WRITE_BYTE_DATA)) {
			fprintf(stderr, MISSING_FUNC_FMT, "SMBus write byte");
			return -1;
		}
		break;

	case I2C_SMBUS_WORD_DATA:
		if (!(funcs & I2C_FUNC_SMBUS_WRITE_WORD_DATA)) {
			fprintf(stderr, MISSING_FUNC_FMT, "SMBus write word");
			return -1;
		}
		break;

	case I2C_SMBUS_BLOCK_DATA:
		if (!(funcs & I2C_FUNC_SMBUS_WRITE_BLOCK_DATA)) {
			fprintf(stderr, MISSING_FUNC_FMT, "SMBus block write");
			return -1;
		}
		break;
	case I2C_SMBUS_I2C_BLOCK_DATA:
		if (!(funcs & I2C_FUNC_SMBUS_WRITE_I2C_BLOCK)) {
			fprintf(stderr, MISSING_FUNC_FMT, "I2C block write");
			return -1;
		}
		break;
	}

	if (pec
	 && !(funcs & (I2C_FUNC_SMBUS_PEC | I2C_FUNC_I2C))) {
		fprintf(stderr, "Warning: Adapter does "
			"not seem to support PEC\n");
	}

	return 0;
}

static int read_watchdog_status(int fd, int daddress){
	int res;
	res = i2c_smbus_read_byte_data(fd, daddress);
	if (res < 0) {
		printf("Warning - read watchdog status failed\n");
		return -1;
	}
	return res;
}

static int set_watchdog_status(int fd, int daddress, int status){
	int res;
	res = i2c_smbus_write_byte_data(fd, daddress, status);
	if (res < 0){
		printf("Warning - set watchdog status failed:%d\n", status);
		return -1;
	}

	printf("Watchdog has been %s.\n", status?"enabled":"disabled");

	return res;
}

int main(int argc, char *argv[]){
	char *end;

	int res, i2cbus, address, fd;
	int all_addrs = 0;
	int daddress;
	char fd_path[20]={0};
	int pec = 0;

	int force = 0, flags = 0, version = 0, enable = 0, disable = 0, status = 0;

	/* handle (optional) flags first */
	while (1+flags < argc && argv[1+flags][0] == '-') {
		switch (argv[1+flags][1]) {
		case 'v': version = 1; break;
		case 'f': force = 1; break;
		case 's': status = 1; break;
		case 'e': enable = 1; break;
		case 'd': disable = 1; break;
		default:
			fprintf(stderr, "Error: Unsupported option "
				"\"%s\"!\n", argv[1+flags]);
			help();
			exit(1);
		}
		flags++;
	}
	if (version) {
		fprintf(stderr, "i2cset version %s\n", VERSION);
		exit(0);
	}

	i2cbus = lookup_i2c_bus(I2C_WATCHDOG_NUM);
	if (i2cbus < 0){
		fprintf(stderr, "Error: I2cbus invalid!\n");
		exit(1);
	}
	address = parse_i2c_address(I2C_WATCHDOG_ADDR, all_addrs);
	if (address < 0){
		fprintf(stderr, "Error: I2c address invalid!\n");
		exit(1);
	}
	daddress = strtol(I2C_WATCHDOG_STATUS_POS, &end, 0);
	if (*end || daddress < 0 || daddress > 0xff) {
		fprintf(stderr, "Error: Data address invalid!\n");
		exit(1);
	}
	fd = open_i2c_dev(i2cbus, fd_path, sizeof(fd_path), 0);
	if (fd < 0
	 || check_funcs(fd, I2C_SMBUS_BYTE_DATA, pec)
	 || set_slave_addr(fd, address, force))
		exit(1);

	if (pec && ioctl(fd, I2C_PEC, 1) < 0) {
		fprintf(stderr, "Error: Could not set PEC: %s\n",
			strerror(errno));
		close(fd);
		exit(1);
	}

	if(enable){
		set_watchdog_status(fd, daddress, ENABLE_MCU_WATCHDOG);
	}else if(disable){
		set_watchdog_status(fd, daddress, DISABLE_MCU_WATCHDOG);
	}else{
		;
	}
	if(status || argc == 1){
		res = read_watchdog_status(fd, daddress);
		if(res > 0){
			printf("Watchdog enabled!\n");
		}else if(res == 0){
			printf("Watchdog disabled!\n");
		}else{
			fprintf(stderr, "Error: Unknown status:%d.\n", res);
		}
	}

	close(fd);
	return 0;
}
