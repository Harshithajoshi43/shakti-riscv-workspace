/***************************************************************************
 * Project           			:  shakti devt board
 * Name of the file	     		:  link.ld
 * Created date			        :   
 * Brief Description of file    :   linker file

 Copyright (C) 2020  IIT Madras. All rights reserved.

// check LICENSE.iitm

 ***************************************************************************/

OUTPUT_ARCH( "riscv" )
ENTRY(_start)

SECTIONS
{
  . = 0x1000;

  .text.init : { *(.text.init) }

  .text : { *(.text) }

 .rodata : {
       __rodata_start = .;
       *(.rodata)
       *(.rodata.*)
       *(.gnu.linkonce.r.*)
       __rodata_end = .;
 }

  .data : { 
 . = ALIGN(4);
     __data_start = .;
     *(.data)
     *(.data.*)
     *(.gnu.linkonce.d.*)
     __data_end = .;
 }

  .sdata : {
    *(.srodata.cst16) *(.srodata.cst8) *(.srodata.cst4) *(.srodata.cst2) *(.srodata*)
    *(.sdata .sdata.* .gnu.linkonce.s.*)
  }

  .sbss : {
    *(.sbss .sbss.* .gnu.linkonce.sb.*)
    *(.scommon)
  }

 .bss : {
       . = ALIGN(4);
       __bss_start = .;
       *(.bss)
       *(.bss.*)
       *(.gnu.linkonce.b.*)
       *(COMMON)
       . = ALIGN(4);
       __bss_end = .;
    }

  _end = .;
}
