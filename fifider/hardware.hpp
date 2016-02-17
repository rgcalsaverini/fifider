#ifndef FIFIDER_HARDWARE_HPP
#define FIFIDER_HARDWARE_HPP

/* Defaults */
#define HW_DEF_INTERVAL    28800
#define HW_DEF_PORTION     2
#define HW_SAVE_INTERVAL   30
#define HW_DSP_TIMEOUT     5000
#define HW_MAX_INTERVAL    172800
#define HW_MIN_INTERVAL    1800
#define HW_MAX_PORTION     15
#define HW_MIN_PORTION     1

/* Memory */
#define HW_MAGSTR_VAL      "fidev_5"
#define HW_MAGSTR_LEN      7
#define HW_MAGSTR_ADDR     0x10
#define HW_ETA_ADDR        0x30
#define HW_PORTION_ADDR    0x40
#define HW_INTERVAL_ADDR   0x50
#define HW_ETA_BITS        3
#define HW_INTERVAL_BITS   3
#define HW_PORTION_BITS    1

/* Shift Register */
#define HW_SR_CLOCK_PIN     4
#define HW_SR_DATA_PIN      2
#define HW_SR_LATCH_PIN     7

/* Buttons */
#define HW_BTN_INCR_PIN     8
#define HW_BTN_DECR_PIN     5
#define HW_BTN_SEL_PIN      3

/* Number of digits on display */
#define HW_DISP_DIGITS     5

/* Display digit segment maping */
#define HW_DISP_0   0b01111101;
#define HW_DISP_1   0b00010100;
#define HW_DISP_2   0b01101110;
#define HW_DISP_3   0b00111110;
#define HW_DISP_4   0b00010111;
#define HW_DISP_5   0b00111011;
#define HW_DISP_6   0b01110011;
#define HW_DISP_7   0b00011100;
#define HW_DISP_8   0b01111111;
#define HW_DISP_9   0b00011111;

#endif //FIFIDER_HARDWARE_HPP
