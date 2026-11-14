
module vsd_shakti_top (
    input  wire clk,
    input  wire reset_n,

    input  wire uart_rx,
    output wire uart_tx,

    output wire led_green,
    output wire led_blue,
    output wire led_red
);

    // ==================================================
    // SHAKTI GPIO signals used for RGB LED
    // ==================================================

    wire gpio_7_out;
    wire gpio_7_outen;

    wire gpio_8_out;
    wire gpio_8_outen;

    wire gpio_14_out;
    wire gpio_14_outen;

    // ==================================================
    // SHAKTI SoC
    // ==================================================

    mkSoc soc_inst (

        // Clock and reset
        .CLK_tck_clk (1'b0),
        .RST_N_trst  (1'b1),
        .CLK         (clk),
        .RST_N       (reset_n),

        // ---------------- SPI ----------------
        .spi0_io_miso_dat (1'b1),
        .spi0_io_mosi     (),
        .spi0_io_sclk     (),
        .spi0_io_nss      (),

        // ---------------- UART 0 ----------------
        .uart0_io_SIN     (uart_rx),
        .uart0_io_SOUT    (uart_tx),
        .uart0_io_SOUT_EN (),

        // ---------------- I2C 0 ----------------
        .i2c0_out_scl_out    (),
        .i2c0_out_scl_in_in  (1'b1),
        .i2c0_out_scl_out_en (),
        .i2c0_out_sda_out    (),
        .i2c0_out_sda_in_in  (1'b1),
        .i2c0_out_sda_out_en (),

        // ---------------- I2C 1 ----------------
        .i2c1_out_scl_out    (),
        .i2c1_out_scl_in_in  (1'b1),
        .i2c1_out_scl_out_en (),
        .i2c1_out_sda_out    (),
        .i2c1_out_sda_in_in  (1'b1),
        .i2c1_out_sda_out_en (),

        // ---------------- XADC ----------------
        .xadc_master_awvalid          (),
        .xadc_master_awaddr           (),
        .xadc_master_awprot           (),
        .xadc_master_awsize           (),
        .xadc_master_m_awready_awready(1'b0),

        .xadc_master_wvalid           (),
        .xadc_master_wdata            (),
        .xadc_master_wstrb            (),
        .xadc_master_m_wready_wready  (1'b0),

        .xadc_master_m_bvalid_bvalid  (1'b0),
        .xadc_master_m_bvalid_bresp   (2'b00),
        .xadc_master_bready           (),

        .xadc_master_arvalid          (),
        .xadc_master_araddr           (),
        .xadc_master_arprot           (),
        .xadc_master_arsize           (),
        .xadc_master_m_arready_arready(1'b0),

        .xadc_master_m_rvalid_rvalid  (1'b0),
        .xadc_master_m_rvalid_rresp   (2'b00),
        .xadc_master_m_rvalid_rdata   (32'b0),
        .xadc_master_rready           (),

        // ---------------- IO CELL INPUTS ----------------
        .iocell_io_io7_cell_in_in  (1'b0),
        .iocell_io_io8_cell_in_in  (1'b0),
        .iocell_io_io9_cell_in_in  (1'b0),
        .iocell_io_io10_cell_in_in (1'b0),
        .iocell_io_io12_cell_in_in (1'b0),
        .iocell_io_io13_cell_in_in (1'b0),
        .iocell_io_io16_cell_in_in (1'b0),
        .iocell_io_io17_cell_in_in (1'b0),
        .iocell_io_io18_cell_in_in (1'b0),
        .iocell_io_io19_cell_in_in (1'b0),
        .iocell_io_io20_cell_in_in (1'b0),

        // IO cell outputs unused
        .iocell_io_io7_cell_out     (),
        .iocell_io_io7_cell_outen   (),
        .iocell_io_io8_cell_out     (),
        .iocell_io_io8_cell_outen   (),
        .iocell_io_io9_cell_out     (),
        .iocell_io_io9_cell_outen   (),
        .iocell_io_io10_cell_out    (),
        .iocell_io_io10_cell_outen  (),
        .iocell_io_io12_cell_out    (),
        .iocell_io_io12_cell_outen  (),
        .iocell_io_io13_cell_out    (),
        .iocell_io_io13_cell_outen  (),
        .iocell_io_io16_cell_out    (),
        .iocell_io_io16_cell_outen  (),
        .iocell_io_io17_cell_out    (),
        .iocell_io_io17_cell_outen  (),
        .iocell_io_io18_cell_out    (),
        .iocell_io_io18_cell_outen  (),
        .iocell_io_io19_cell_out    (),
        .iocell_io_io19_cell_outen  (),
        .iocell_io_io20_cell_out    (),
        .iocell_io_io20_cell_outen  (),

        // ---------------- GPIO INPUTS ----------------
        .gpio_4_in  (1'b0),
        .gpio_7_in  (1'b0),
        .gpio_8_in  (1'b0),
        .gpio_14_in (1'b0),
        .gpio_15_in (1'b0),
        .gpio_16_in (1'b0),
        .gpio_17_in (1'b0),
        .gpio_18_in (1'b0),
        .gpio_19_in (1'b0),
        .gpio_20_in (1'b0),
        .gpio_21_in (1'b0),
        .gpio_22_in (1'b0),
        .gpio_23_in (1'b0),
        .gpio_24_in (1'b0),
        .gpio_25_in (1'b0),
        .gpio_26_in (1'b0),
        .gpio_27_in (1'b0),
        .gpio_28_in (1'b0),
        .gpio_29_in (1'b0),
        .gpio_30_in (1'b0),
        .gpio_31_in (1'b0),

        // ---------------- GPIO OUTPUTS ----------------
        .gpio_4_out  (),
        .gpio_7_out  (gpio_7_out),
        .gpio_8_out  (gpio_8_out),
        .gpio_14_out (gpio_14_out),
        .gpio_15_out (),
        .gpio_16_out (),
        .gpio_17_out (),
        .gpio_18_out (),
        .gpio_19_out (),
        .gpio_20_out (),
        .gpio_21_out (),
        .gpio_22_out (),
        .gpio_23_out (),
        .gpio_24_out (),
        .gpio_25_out (),
        .gpio_26_out (),
        .gpio_27_out (),
        .gpio_28_out (),
        .gpio_29_out (),
        .gpio_30_out (),
        .gpio_31_out (),

        // ---------------- GPIO OUTPUT ENABLES ----------------
        .gpio_4_outen  (),
        .gpio_7_outen  (gpio_7_outen),
        .gpio_8_outen  (gpio_8_outen),
        .gpio_14_outen (gpio_14_outen),
        .gpio_15_outen (),
        .gpio_16_outen (),
        .gpio_17_outen (),
        .gpio_18_outen (),
        .gpio_19_outen (),
        .gpio_20_outen (),
        .gpio_21_outen (),
        .gpio_22_outen (),
        .gpio_23_outen (),
        .gpio_24_outen (),
        .gpio_25_outen (),
        .gpio_26_outen (),
        .gpio_27_outen (),
        .gpio_28_outen (),
        .gpio_29_outen (),
        .gpio_30_outen (),
        .gpio_31_outen (),

        // ---------------- JTAG ----------------
        .wire_tms_tms_in       (1'b0),
        .wire_tdi_tdi_in       (1'b0),
        .wire_capture_capture_in (1'b0),
        .wire_run_test_run_test_in (1'b0),
        .wire_sel_sel_in       (1'b0),
        .wire_shift_shift_in   (1'b0),
        .wire_update_update_in (1'b0),
        .wire_tdo              (),

        // ---------------- INTERRUPTS ----------------
        .ext_interrupts_i (2'b00)
    );

    // ==================================================
    // GPIO output-enable gating
    // ==================================================

    wire green_pwm = gpio_7_out & gpio_7_outen;
    wire blue_pwm  = gpio_8_out & gpio_8_outen;
    wire red_pwm   = gpio_14_out & gpio_14_outen;

    // ==================================================
    // VSDSquadron FM RGB LED driver
    // ==================================================

    SB_RGBA_DRV RGB_DRIVER (
        .RGBLEDEN (1'b1),

        .RGB0PWM  (green_pwm),
        .RGB1PWM  (blue_pwm),
        .RGB2PWM  (red_pwm),

        .CURREN   (1'b1),

        .RGB0     (led_green),
        .RGB1     (led_blue),
        .RGB2     (led_red)
    );

    defparam RGB_DRIVER.RGB0_CURRENT = "0b000001";
    defparam RGB_DRIVER.RGB1_CURRENT = "0b000001";
    defparam RGB_DRIVER.RGB2_CURRENT = "0b000001";

endmodule

