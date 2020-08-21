/***************************************************************************
 * Project           			:  shakti devt board
 * Name of the file	     		:  link.ld
 * Created date			        :   
 * Brief Description of file    :   linker file
 * Name of Author    	        :  Sathya Narayanan N & Abhinav ramnath
 * Email ID                     :  sathya281@gmail.com

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
  .sdata : {
    __global_pointer$ = . + 0x800;
    *(.srodata.cst16) *(.srodata.cst8) *(.srodata.cst4) *(.srodata.cst2) *(.srodata*)
    *(.sdata .sdata.* .gnu.linkonce.s.*)
  }
  .sbss : {
    __sbss_start = .;
    *(.sbss)
    *(.sbss.*)
    *(.gnu.linkonce.sb.*)
    __sbss_end = .;
 }
  .data : {
    . = ALIGN(4);
    __data_start = .;
    *(.data)
    *(.data.*)
    *(.gnu.linkonce.d.*)
    __data_end = .;
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
  .tdata :
  {
    _tls_data = .;
    *(.tdata.begin)
    *(.tdata)
    *(.tdata.end)
    _tls_end = .;
  }
  .tbss :
  {
    *(.tbss)
    *(.tbss.end)
  }
  . = ALIGN(4);
  _end = .;
  . = 0x1000 + 0x4000 - 0x8;
  _free_space = . - _end;
  _STACK_SIZE = _free_space;
    .stack : {
       _stack_end = .;
       __stack_pointer$ = .;
       _stack = . - _STACK_SIZE;
    }
   . = _stack;
}

