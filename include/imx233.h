/********************************************************
 * @author  Airead Fan <fgh1987168@gmail.com>		*
 * @date    201110月 13 22:47:10 CST			*
 ********************************************************
 *		after studying C 87 days		*
 *		after studying APUE 52 days		*
 *		after studying ARM 5 days		*
 ********************************************************/

/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef SWORD_IMX233_H
#define SWORD_IMX233_H

#define REGS_PINCTRL_BASE_PHYS (0x80018000)
#define REGS_DIGCTL_BASE_PHYS (0x8001C000)
#define REGS_RTC_BASE_PHYS (0x8005C000)
#define REGS_DBGDUART_BASE_PHYS (0x80070000)


/* struct define */
typedef volatile unsigned int REG;
struct REG4{
	REG dat;
	REG set;
	REG clr;
	REG tog;
};
struct REG1{
	REG dat;
	REG pad[3];
};

/* ---------------------------------------------------------- */
struct HW_PINCTRL{
	struct REG4 ctrl __attribute__ ((aligned(0x100)));
	struct REG4 muxsel[8] __attribute__ ((aligned(0x100)));
	struct REG4 drive[15] __attribute__ ((aligned(0x100)));
	struct REG4 pad __attribute__ ((aligned(0x100)));
	struct REG4 pull[4] __attribute__ ((aligned(0x100)));
	struct REG4 dout[3] __attribute__ ((aligned(0x100)));
	struct REG4 din[3] __attribute__ ((aligned(0x100)));
	struct REG4 doe[3] __attribute__ ((aligned(0x100)));
	struct REG4 pin2irq[3] __attribute__ ((aligned(0x100)));
	struct REG4 irqen[3] __attribute__ ((aligned(0x100)));
	struct REG4 irqlevel[3] __attribute__ ((aligned(0x100)));
	struct REG4 irqpol[3] __attribute__ ((aligned(0x100)));
	struct REG4 irqstat[3] __attribute__ ((aligned(0x100)));
};

/* ---------------------------------------------------------- */
struct HW_DIGCTL_AHB_LAYER{
	struct REG1 active_cycles; /* 0x340 */
	struct REG1 data_stalled;   /* 0x350 */
	struct REG1 data_cycles;   /* 0x360 */
};
struct HW_DIGCTL{
	struct REG4 ctrl;	/* 0x000 */
	struct REG4 status;	/* 0x010 */
	struct REG4 hclkcount;	/* 0x020 */
	struct REG4 ramctrl;	/* 0x030 */
	struct REG4 ramrepair;	/* 0x040 */
	struct REG4 romctrl;	/* 0x050 */
	struct REG1 writeonce;	/* 0x060 */
	struct REG4 pad1[2];	/* 0x070-0x080 */
	struct REG1 entropy;	/* 0x090 */
	struct REG1 entropy_latched; /* 0x0A0 */
	struct REG4 sjtagdbg;	     /* 0x0B0 */
	struct REG4 microseconds;   /* 0x0C0 */
	struct REG1 dbgrd;	     /* 0x0D0 */
	struct REG1 dbg;	     /* 0x0E0 */
	struct REG4 ocram_bist_csr;  /* 0x0F0 */
	struct REG4 pad2;	     /* 0x100 */
	struct REG4 ocram_status[14]; /* 0x110-0x1E0 */
	struct REG4 pad3[10];	      /* 0x1F0-0x280 */
	struct REG1 scratch[2];	      /* 0x290-0x2A0 */
	struct REG1 armcache;	      /* 0x2B0 */
	struct REG1 debug_trap_addr_low; /* 0x2C0 */
	struct REG1 debug_trap_addr_high; /* 0x2D0 */
	struct REG4 pad4[2];		  /* 0x2E0-0x2F0 */
	struct REG1 sgtl;		  /* 0x300 */
	struct REG1 chipid;		  /* 0x310 */
	struct REG4 pad5;		  /* 0x320 */
	struct REG1 ahb_stats_select;	  /* 0x330 */
	struct HW_DIGCTL_AHB_LAYER l[4];  /* 0x340-0x3F0 */
	struct REG4 pad6[16];		  /* 0x400-0x4F0 */
	struct REG1 emiclk_delay;	  /* 0x500 */
};

/* ---------------------------------------------------------- */
struct HW_RTC{
	struct REG4 ctrl;
	struct REG4 stat;
	struct REG4 milliseconds;
	struct REG4 seconds;
	struct REG4 alarm;
	struct REG4 watchdog;
	struct REG4 persistent[6];
	struct REG4 debug;
	REG version;
};

/* ---------------------------------------------------------- */
struct HW_DBGUART{
	REG dr;			/* 0x000 */
	REG sr_ecr;		/* 0x004 */
	REG pad1[4];		/* 0x008-0x014 */
	REG fr;			/* 0x018 */
	REG pad2;		/* 0x01C */
	REG ilpr;		/* 0x020 */
	REG ibrd;		/* 0x024 */
	REG fbrd;		/* 0x028 */
	REG lcr_h;		/* 0x02C */
	REG cr;			/* 0x030 */
	REG ifls;		/* 0x034 */
	REG imsc;		/* 0x038 */
	REG ris;		/* 0x03C */
	REG mis;		/* 0x040 */
	REG icr;		/* 0x044 */
	REG macr;		/* 0x048 */
};

#endif
