#ifndef FIFIDER_HARDWARE_HPP
#define FIFIDER_HARDWARE_HPP

/* Basic configs */
#define HW_DEF_INTERVAL    28800   /* (s) Default interval value*/
#define HW_MAX_INTERVAL    172800  /* (s) Max interval value*/
#define HW_MIN_INTERVAL    1800    /* (s) Min interval value*/
#define HW_DEF_PORTION     2       /* (turns) Default portion value */
#define HW_MAX_PORTION     15      /* (s) Max portion value*/
#define HW_MIN_PORTION     1       /* (s) Min portion value*/
#define HW_DSP_TIMEOUT     4500    /* (s) Cycle back to ETA display after this long without user interaction */
#define HW_SAVE_INTERVAL   1200    /* (s) Save after this much time to EEPROM */
#define HW_SAVE_ON_SEL     false   /* Save when the select button is pressed */
#define HW_SAVE_ON_RES     true    /* Save when the ETA is reset is pressed */
#define HW_HOLD_INCR1      300     /* First delay between increments when holding buttons */
#define HW_HOLD_INCR2      100     /* Second delay between increments when holding buttons */
#define HW_HOLD_INC_CNT    5       /* Number of increments on 1 before jumping to 2 */

/* Memory */
#define HW_MAGSTR_VAL      "FDV_003" /* Magic string to ID that memory is initialized  */
#define HW_MAGSTR_LEN      7         /* Length of the magic string */
#define HW_MAGSTR_ADDR     0x4       /* Address of the magic string */
#define HW_ETA_ADDR        0x50      /* Address of the ETA */
#define HW_PORTION_ADDR    0x70      /* Address of the interval*/
#define HW_INTERVAL_ADDR   0x90      /* Address of the interval */
#define HW_ETA_BYTES        4         /* How many bytes to store the ETA in */
#define HW_INTERVAL_BYTES   4         /* How many bytes to store the interval in */
#define HW_PORTION_BYTES    1         /* How many bytes to store the portion in */

/* Shift Register */
#define HW_SR_CLOCK_PIN     4  /* Clock pin of the shift register */
#define HW_SR_DATA_PIN      2  /* Data pin of the shift register */
#define HW_SR_LATCH_PIN     7  /* Latch pin of the shift register */

/* Buttons */
#define HW_BTN_INCR_PIN     8  /* Pin of the increment button */
#define HW_BTN_DECR_PIN     5  /* Pin of the decrement button */
#define HW_BTN_SEL_PIN      3  /* Pin of the select button */

/* Number of digits on display */
#define HW_DISP_DIGITS     5  /* Number of serial components of the display */

#endif //FIFIDER_HARDWARE_HPP
