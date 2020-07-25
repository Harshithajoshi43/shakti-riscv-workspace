#######################
HW Grand Challenge 2020
#######################

This repo contains 3 major SoCs that can be used by participants of the HW GC-2020

The summary of the 3 Socs is present below. Details of each is available in the README of the
respective folders.

E32-A35
^^^^^^^
- A 32-bit E-class 3 stage in order core supporting RV32IMACUN extension
- 2 pmp regions
- 2 cycle HW multiplier
- 32 cycle HW divider
- BRAM memory of 128KBytes
- ROM of 4KBytes
- 6 PWM controllers
- 2 SPI controllers
- 3 UART controllers
- 2 I2C controllers
- 32 GPIOs
- Platform level interrupt controller (PLIC)
- XADC from Xilinx
- PinMux
- Arduino compatible pin assignments
- Core local interrupt controler (CLINT)
- JTAG based debugger

E32-A100
^^^^^^^^
- A 32-bit E-class 3 stage in order core supporting RV32IMACUN extension
- 2 pmp regions
- 2 cycle HW multiplier
- 32 cycle HW divider
- DDR memory of 256MBytes
- ROM of 4KBytes
- 6 PWM controllers
- 2 SPI controllers
- 3 UART controllers
- 2 I2C controllers
- 32 GPIOs
- Platform level interrupt controller
- XADC from Xilinx
- PinMux
- Arduino compatible pin assignments
- Core local interrupt controler (CLINT)
- JTAG based debugger

C64-A100
^^^^^^^^
- A 64-bit C-class 6 stage in order core supporting RV64IMACSU extension
- 2 pmp regions
- 2 cycle HW multiplier
- 32 cycle HW divider
- DDR memory of 256MBytes
- ROM of 4KBytes
- 6 PWM controllers
- 2 SPI controllers
- 3 UART controllers
- 2 I2C controllers
- 32 GPIOs
- Platform level interrupt controller
- XADC from Xilinx
- PinMux
- Arduino compatible pin assignments
- Core local interrupt controler (CLINT)
- JTAG based debugger

* **Memory MAP**:
Following is the SoC Config for Aadronyx. Base and bound addresses are inclusive.

=======  ============  =============
Config   base-address  bound-address
=======  ============  =============
Debug    'h0000_0010   'h0000_001F
BootRAM  'h0000_1000   'h0000_2FFF
UART0    'h0001_1300   'h0000_1340
UART1    'h0001_1400   'h0000_1440
SPI0     'h0002_0000   'h0002_00FF
SPI1     'h0002_0100   'h0002_01FF
PWM0     'h0003_0000   'h0003_00FF
PWM1     'h0003_0100   'h0003_01FF
PWM2     'h0003_0200   'h0003_02FF
PWM3     'h0003_0300   'h0003_03FF
PWM4     'h0003_0400   'h0003_04FF
PWM5     'h0003_0500   'h0003_05FF
I2C      'h0004_0000   'h0004_00FF
PLIC     'h0C00_0000   'h0C01_001F
GPIO     'h0004_0200   'h0004_02FF
XADC     'h0004_1000   'h0004_1400
Clint    'h0200_0000   'h020B_FFFF
BRAM     'h8000_0000   'h87FF_FFFF
=======  ============  =============

Requirements
------------

1. **Vivado 2017** or above should be used
2. ``vivado`` command should be available in your ``$PATH`` variable.
3. ``bsc`` command should be available in your ``$PATH`` variable.
4. ``riscv-openocd`` should be installed in your system.
5. ``miniterm`` should be installed.

Quick Start (default Config) :: Get started with an Arty A7 35t
---------------------------------------------------------------

Programming the Board
^^^^^^^^^^^^^^^^^^^^^

[A] Generating your own mcs file (recommended)
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
If you are modifying the RTL this is the recommended approach

.. code-block:: yaml

 $ git clone https://gitlab.com/shaktiproject/cores/shakti-soc.git
 $ cd shakti-soc/fpga/boards/artya7-35t/e-class
 $ make quick_build_xilinx
 # Please Disconnect and Reconnect and Reset The Arty Board !

Connecting to the Target
^^^^^^^^^^^^^^^^^^^^^^^^
Please make sure you are using the 32-bit toolchain available `here
<https://gitlab.com/shaktiproject/software/shakti-tools/>`_. 
(This toolchain contains the ``openocd`` binary which has been tweaked for our bscan2e based JTAG
protocol)

In a New Terminal window

.. code-block:: yaml

  $ openocd -f shakti-arty.cfg

In yet Another Terminal window

.. code-block:: yaml

  $ riscv32-unknown-elf-gdb -x gdb.script

Launch UART Console

.. code-block:: yaml

  $ sudo miniterm /dev/ttyUSB1 19200

On pressing the ``reset-button`` on the board the UART console should display the following:

.. code-block:: yaml

                                       ./((*
                                   ,(((((,
                               *((((((,
                          ./(((((((,
                      ./((((((((*
                   *(((((((((/
               .(((((((((((,
            ,((((((((((((/
          ((((((((((((((/
         .((((((((((((((/
             *(((((((((((.
                  /(((((((.
                ,.     *(((/
                    *((,     ,/.
                      ((((((/.
                       ((((((((((/
                        (((((((((((((/
                        ((((((((((((((.
                       ((((((((((((/
                     *((((((((((*
                   ((((((((((.
                /((((((((*
             *(((((((,
          *((((((.
      .(((((.
  ./(((*
  .
                    SHAKTI PROCESSORS


Reporting Issues
^^^^^^^^^^^^^^^^
While reporting issues with this board/build please make sure to mark the issues with the ``arty-a7-35t`` label
