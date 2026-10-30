/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright (C) 2023 Renesas Electronics Corporation
 */

#ifndef __RZV2N_SOMDEVICES_H
#define __RZV2N_SOMDEVICES_H

#include <asm/arch/renesas.h>

#define CONFIG_REMAKE_ELF

#ifdef CONFIG_SPL
#define CONFIG_SPL_TARGET	"spl/u-boot-spl.scif"
#endif

/* boot option */

#define CONFIG_CMDLINE_TAG
#define CONFIG_SETUP_MEMORY_TAGS
#define CONFIG_INITRD_TAG

/* Generic Interrupt Controller Definitions */
/* RZ/V2N use GIC-v3 */
#define CONFIG_GICV3
#define GICD_BASE	0x14900000
#define GICR_BASE	0x14940000

/* console */
#define CONFIG_SYS_CBSIZE		2048
#define CONFIG_SYS_BARGSIZE		CONFIG_SYS_CBSIZE
#define CONFIG_SYS_BAUDRATE_TABLE	{ 115200, 38400 }

/* PHY needs a longer autoneg timeout */
#define PHY_ANEG_TIMEOUT		20000

/* MEMORY */
#define CONFIG_SYS_INIT_SP_ADDR		CONFIG_SYS_TEXT_BASE

#define DRAM_RSV_SIZE			0x08000000
#define CONFIG_SYS_SDRAM_BASE		(0x40000000 + DRAM_RSV_SIZE)
#define CONFIG_SYS_SDRAM_SIZE		(0x080000000u - DRAM_RSV_SIZE) //total 2GB
#define CONFIG_SYS_LOAD_ADDR		0x58000000
/* Default load address for tfpt,bootp */
#define CONFIG_LOADADDR			CONFIG_SYS_LOAD_ADDR
#define CONFIG_VERY_BIG_RAM
#define CONFIG_MAX_MEM_MAPPED		(0x80000000u - DRAM_RSV_SIZE)


/* SDHI clock freq */
#define CONFIG_SH_SDHI_FREQ		133000000


/* The HF/QSPI layout permits up to 1 MiB large bootloader blob */
#define CONFIG_BOARD_SIZE_LIMIT		1048576

/* ENV setting */
#define CFG_EXTRA_ENV_SETTINGS	\
	"usb_pgood_delay=2000\0" \
	"bootm_size=0x10000000\0" \
	"prodsdbootargs=setenv bootargs rw rootwait earlycon root=/dev/mmcblk1p2 vt.global_cursor_default=0 \0" \
	"prodemmcbootargs=setenv bootargs rw rootwait earlycon root=/dev/mmcblk0p1 vt.global_cursor_default=0 \0" \
	"bootimage=booti 0x48080000 - 0x48000000 \0" \
	"ocaaddr=0xA8000000 \0"     \
	"ocabin=OpenCV_Bin.bin \0"  \
	"codaddr=0xAFD00000 \0"     \
	"codbin=Codec_Bin.bin \0"   \
	"emmcload=ext4load mmc 0:1 ${ocaaddr} boot/${ocabin}; ext4load mmc 0:1 ${codaddr} boot/${codbin};ext4load mmc 0:1 0x48080000 boot/Image;ext4load mmc 0:1 0x48000000 boot/r9a09g056n44-somdevices-C0P1.dtb;run prodemmcbootargs \0" \
	"sd1load=ext4load mmc 1:2 ${ocaaddr} boot/${ocabin}; ext4load mmc 1:2 ${codaddr} boot/${codbin};ext4load mmc 1:2 0x48080000 boot/Image;ext4load mmc 1:2 0x48000000 boot/r9a09g056n44-somdevices-C0P1.dtb;run prodsdbootargs \0" \
	"loadsdbootscript=ext4load mmc 1:2 0x48080000 boot/boot.scr;\0" \
	"loademmcbootscript=ext4load mmc 0:1 0x48080000 boot/boot.scr;\0" \
	"bootemmc= " \
		"if run loademmcbootscript; then " \
			"echo Running bootscript from mmc; " \
		"else " \
			"echo Booting from mmc; " \
			"run emmcload; " \
			"run bootimage; " \
		"fi;\0" \
	"bootcmd_check= " \
		"if mmc dev 1; then " \
			"if run loadsdbootscript; then " \
				"echo Running bootscript from sd; " \
			"else " \
				"if run sd1load; then " \
					"echo Booting from sd; " \
					"run bootimage; " \
				"else " \
					"run bootemmc; "\
				"fi; " \
			"fi; " \
		"else " \
			"run bootemmc; "\
		"fi;\0"

#define CONFIG_BOOTCOMMAND	"run bootcmd_check"

/* For board */
/* Ethernet RAVB */
#define CONFIG_BITBANGMII_MULTI

#endif /* __RZV2N_SOMDEVICES_H */
