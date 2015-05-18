#ifndef _LCD_CFG_H_
#define _LCD_CFG_H_

#include "lcd_driver.h"

#ifndef BIT
#define BIT(x) (1<<(x))
#endif

#ifndef BITS
#define BITS(b,v) ((v)<<(b))
#endif

#define	LCD_WIDTH	tvout_get_w()
#define	LCD_HEIGHT	tvout_get_h()



/////////////////////////////////////////////////////////////////////////////////

// LCD
#define LCD_CFG                 LCDCON0
#define LCD_CFG_RGB             LCDCON1
#define LCD_CFG_RGB_SHF         LCDCON2
#define LCD_CFG_OUT_CLK         LCDCON3
#define LCD_CFG_DATA_IO         LCDCON4
#define LCD_CFG_DATA_HI         LCDCON5
#define LCD_CFG_CLK_TIM         LCDCON6
#define LCD_VS_RISING           LCDCON7
#define LCD_HS_RISING           LCDCON8
#define LCD_DE_RISING           LCDCON9
#define LCD_VS_FALLING          LCDCON10
#define LCD_HS_FALLING          LCDCON11
#define LCD_DE_FALLING          LCDCON12
#define LCD_DE_START            LCDCON13
#define LCD_DE_END              LCDCON14
#define LCD_CFG_EMI             LCDCON15
#define LCD_CFG_SPI             LCDCON16
#define LCD_SPI_BAUD            LCDCON17
#define LCD_DATA                LCDCON18
#define LCD_VIDEO_X0            LCDCON19
#define LCD_VIDEO_Y0            LCDCON20
#define LCD_VIDEO_X1            LCDCON21
#define LCD_VIDEO_Y1            LCDCON22
#define LCD_OSD1_X0             LCDCON23
#define LCD_OSD1_Y0             LCDCON24
#define LCD_OSD1_X1             LCDCON25
#define LCD_OSD1_Y1             LCDCON26
#define LCD_OSD2_X0             LCDCON27
#define LCD_OSD2_Y0             LCDCON28
#define LCD_OSD2_X1             LCDCON29
#define LCD_OSD2_Y1             LCDCON30
#define LCD_OSD3_X0             LCDCON31
#define LCD_OSD3_Y0             LCDCON32
#define LCD_OSD3_X1             LCDCON33
#define LCD_OSD3_Y1             LCDCON34
#define LCD_LINE_PIXELS         LCDCON35
#define LCD_FRAME_LINES         LCDCON36
#define LCD_OSD1_ALPHA          LCDCON37
#define LCD_OSD2_ALPHA          LCDCON38
#define LCD_OSD3_ALPHA          LCDCON39
#define LCD_BG_RED              LCDCON40
#define LCD_BG_GREEN            LCDCON41
#define LCD_BG_BLUE             LCDCON42
#define LCD_OSD1_ADDR           LCDCON43
#define LCD_OSD2_ADDR           LCDCON44
#define LCD_OSD3_ADDR           LCDCON45
#define LCD_VIDEO_ADDR          LCDCON46
#define LCD_YUV2RGB             LCDCON47
#define LCD_VIDEO_SPAN          LCDCON48
#define LCD_SCALE_WSTEP         LCDCON49
#define LCD_SCALE_WREM          LCDCON50
#define LCD_SCALE_HSTEP         LCDCON51
#define LCD_SCALE_HREM          LCDCON52
#define LCD_SCALE_WDEST         LCDCON53
#define LCD_SCALE_HDEST         LCDCON54
#define LCD_SCALE_WSRC          LCDCON55
#define LCD_SCALE_HSRC          LCDCON56
#define LCD_PND                 LCDCON57
#define LCD_LINE_DCLKS          LCDCON58
#define LCD_CFG_BURST           LCDCON59
#define LCD_DMA_INTERVAL        LCDCON60
#define LCD_WRBACK_ADDR         LCDCON61

/////////////////////////////////////////////////////////////////////////////////

// LCD_CFG
#define BIT_LCD_EN              0
#define BIT_LCD_IF              1
#define BITS_LCD_IF             2
#define BIT_OSD1_EN             3
#define BIT_OSD2_EN             4
#define BIT_OSD3_EN             5
#define BIT_VIDEO_EN            6
#define BIT_WRITE_BACK_EN       7
#define BIT_HOLD_DISP_EN        8
#define BIT_ODD_FIRST           9
#define BIT_FPND_IE             10
#define BIT_WRITE_BACK_IE       11
#define BIT_BUF_EMPTY_IE        12
#define BIT_FRAME_RESET_EN      13
#define BIT_WB_8_KICK           14

// LCD_CFG_RGB
#define BIT_LCD_CFG_RW          0
#define BIT_LCD_CFG_GW          3
#define BIT_LCD_CFG_BW          6
#define BIT_LCD_CFG_OO          9
#define BIT_LCD_CFG_EO          12
#define WIDTH_LCD_CFG_RGB       3

// LCD_CFG_RGB_SHF
#define BIT_RGB_EXPAND_WIDTH    0
#define BIT_RGB_EXPAND_LOC      5
#define BIT_RGB_SHIFT_WIDTH     10

// LCD_CFG_OUT_CLK
#define BIT_VSYNC_EN            0
#define BIT_HSYNC_EN            1
#define BIT_DE_EN               2
#define BIT_DCLK_EN             3
#define BIT_VSYNC_INV           4
#define BIT_HSYNC_INV           5
#define BIT_DE_INV              6
#define BIT_DCLK_INV            7

// LCD_CFG_DATA_IO
#define BIT_D0_7_OEN            0
#define BIT_DATA_INV            8
#define BIT_DATA_DLY            9

// LCD_CFG_CLK_TIM
#define BIT_VSYNC_INACT_AT      0
#define BIT_VSYNC_UP_NEG_EDGE   5
#define BIT_HSYNC_UP_NEG_EDGE   6
#define BIT_DE_UP_NEG_EDGE      7
#define BIT_CLKDIV              8
#define BIT_DIV2_DUTY           14
#define BIT_HOLDCLK_EN          15
#define BIT_SLOWDNCLK_EN        16
#define BIT_SLOWDNCNT_EN        17
#define BIT_VIDEO_SLOWDN_C_EN   22
#define BIT_OSD_SLOWDN_C_EN     23

// LCD_YUV2RGB
#define BIT_WARP_EN             0
#define BIT_WARP_K              1
#define BIT_ROTATEMODE          4
#define BIT_MIRROR              5
#define BIT_UV_MINUS_0          7
#define BIT_Y_MINUS_0           8
#define BIT_YCbCr               9

// RGB_STATUS
#define BIT_RGB_DONE            0
#define BIT_RGB_ORDER           1
#define RGB_STATUS_RGB          0
#define RGB_STATUS_BGR          1
#define RGB_STATUS_GRB          2
#define RGB_STATUS_BRG          3
#define RGB_STATUS_GBR          4
#define RGB_STATUS_RBG          5

// LCD_PND
#define BIT_FRAME_DONE          0
#define BIT_EMI_SPI_BUSY        1
#define BIT_WRITE_BACK_DONE     2
#define BIT_FIFO_EMPTY          3

// LCD_CFG_EMI
#define BIT_CS_PR              0
#define BIT_WR_PR              6
#define BIT_WR_FR              9
#define BIT_CS_INV             12
#define BIT_WR_INV             13
#define BIT_CS_OEN             14
#define BIT_DATACTRL_MODE      15

// LCD_CFG_SPI
#define BIT_SPI_ID_ST           0
#define BIT_SPI_SMP_SEL         1
#define BIT_SPI_1DW             2
#define BIT_SPI_1DW_DIR         3
#define BIT_SPI_9BITEN          4
#define BIT_SPI_9BIT            5

// LCD_SPI_BAUD 
#define BIT_SPI_BAUD            0

/////////////////////////////////////////////////////////////////////////////////

 // LCD_CFG
#define LCD_IF_EMI              0
#define LCD_IF_SPI              1
#define LCD_IF_RGB              2
#define LCD_IF_TV               3

// LCD_CFG_RGB
#define ORDER_RGB               0
#define ORDER_RBG               1
#define ORDER_GRB               2
#define ORDER_GBR               3
#define ORDER_BRG               4
#define ORDER_BGR               5

// LCD_YUV2RGB
#define MIRROR_NONE             0
#define MIRROR_VERTICAL         1
#define MIRROR_HORIZONTAL       2
#define MIRROR_VER_HOR          3
#define ROTATE_NONE             0
#define ROTATE_180              1





#if(LCD_USE == LCD_NO_DISPLAY)
    #include  "lcd_nodisplay.h"
#elif(LCD_USE == LCD_TDO24THEB2)
    #include  "lcd_tdo24theb2.h"
#elif(LCD_USE == LCD_ILI8961)
    #include  "lcd_ili8961.h"
#elif(LCD_USE == LCD_3029)
    #include  "lcd_3029.h"
#elif(LCD_USE == LCD_61505)
    #include  "lcd_61505.h"
#elif(LCD_USE == LCD_HX8367)
    #include  "lcd_hx8367.h"
#elif(LCD_USE == LCD_7781)
    #include  "lcd_7781.h"
#elif(LCD_USE == LCD_HX8312)
    #include  "lcd_hx8312.h"
#elif(LCD_USE == LCD_ILI6480)
    #include  "lcd_ili6480.h"
#elif(LCD_USE == LCD_3029C)
    #include  "lcd_3029C.h"
#elif(LCD_USE == LCD_61505W)
    #include  "lcd_61505W.h"
#elif(LCD_USE == LCD_9303)
    #include  "lcd_9303.h"
#elif(LCD_USE == LCD_9312)
    #include  "lcd_9312.h"
#elif(LCD_USE == LCD_ILI9225)
    #include  "lcd_ili9225.h"
#endif
 


extern unsigned int gImage_palette[];
extern BOOL volatile blcd_FrameEnd_Flag;
extern BOOL volatile blcd_writeback_Flag;


#endif
