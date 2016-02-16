#ifndef FIFIDER_HARDWARE_HPP
#define FIFIDER_HARDWARE_HPP

/* Defaults */
#define HW_DEF_INTERVAL    28800
#define HW_DEF_PORTION     2

/* Memory */
#define HW_MAGSTR_VAL      "fidev_2"
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
#define HW_BTN_INCR_PIN     1
#define HW_BTN_DECR_PIN     0
#define HW_BTN_SEL_PIN      3

/* Number of digits on display */
#define HW_DISP_DIGITS     5

/* Display digit segment maping */
#define HW_DISP_0   0x7D;
#define HW_DISP_1   0x14;
#define HW_DISP_2   0x6E;
#define HW_DISP_3   0x3E;
#define HW_DISP_4   0x17;
#define HW_DISP_5   0x3B;
#define HW_DISP_6   0x73;
#define HW_DISP_7   0x1C;
#define HW_DISP_8   0x7F;
#define HW_DISP_9   0x1F;

#endif //FIFIDER_HARDWARE_HPP
