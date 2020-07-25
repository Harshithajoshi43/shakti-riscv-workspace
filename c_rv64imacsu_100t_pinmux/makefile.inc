
VERILOGDIR:=build/hw/verilog

BSVBUILDDIR:=build/hw/intermediate

BSVOUTDIR:=bin

BSCCMD:=bsc -u -verilog -elab -vdir build/hw/verilog -bdir build/hw/intermediate -info-dir build/hw/intermediate +RTS -K40000M -RTS -check-assert  -keep-fires -opt-undetermined-vals -remove-false-rules -remove-empty-rules -remove-starved-rules -remove-dollar -unspecified-to X -show-schedule -show-module-use  -suppress-warnings G0010:T0054:G0020:G0024:G0023:G0096:G0036:G0117:G0015

BSC_DEFINES:=Addr_space=25 RV64 ibuswidth=64 dbuswidth=64 resetpc=4096 paddr=32 vaddr=64 causesize=6 CORE_AXI4 iesize=2 desize=1 dtvec_base=0 bscan2e atomic compressed muldiv MULSTAGES=1 DIVSTAGES=32 user supervisor asidwidth=9 itlbsize=2 dtlbsize=2 sv39 bpu gshare btbdepth=32 bhtdepth=512 histlen=8 histbits=5 rasdepth=8 bpureset=1 bpu_ras iwords=4 iblocks=16 iways=1 isets=64 ifbsize=2 icache_onehot=0 icache icachereset=1 ifence irepl=0 dwords=8 dblocks=8 dways=1 dsets=64 dfbsize=2 dsbsize=2 dcache_onehot=0 dcache dcachereset=1 drepl=0 debug counters_grp4=0 counters_grp5=0 counters_grp6=0 counters_grp7=0 counters_size=0

BSVINCDIR:=.:%/Libraries:c-class/src:c-class/src/predictors:c-class/src/m_ext:c-class/src/fpu/:c-class/src/m_ext/multiplier_designs:c-class/src/csr:c-class/src/csr/daisy_chain:fabrics/axi4:fabrics/axi4lite:fabrics/bridges:caches_mmu/src/dcache/:caches_mmu/src/icache_1rw/:caches_mmu/src/tlbs:caches_mmu/src/pmp:common_bsv/:common_verilog/bsvwrappers/:devices/bootrom:devices/pwm:devices/uart_v2:devices/clint:devices/bram:devices/riscvDebug013:devices/jtagdtm/:devices/err_slave/:devices/gpio/:devices/plic/:devices/i2c/:devices/spi/

BS_VERILOG_LIB:=/software/open-bsc/lib/Verilog/

TOP_MODULE:=mSoc

TOP_DIR:=./

TOP_FILE:=Soc.bsv

XLEN:=64

TOP_BIN=Soc.bo

ISA=RV64IMACSU

FPGA=xc7a100tcsg324-1

SYNTHTOP=fpga_top

BSCAN2E=enable

include depends.mk
