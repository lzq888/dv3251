##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=AX325X
ConfigurationName      :=Debug
WorkspacePath          := "E:\work1\DV3251_UNOS_sdk_release_v1.3\release"
ProjectPath            := "E:\work1\DV3251_UNOS_sdk_release_v1.3\release"
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=yezq
Date                   :=05/30/15
CodeLitePath           :="d:\Program Files\CodeLite"
LinkerName             :=D:/MinGW-4.7.1/bin/arm-elf-ld.exe
SharedObjectLinkerName :=D:/MinGW-4.7.1/bin/arm-elf-gcc.exe
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="AX325X.txt"
PCHCompileFlags        :=
MakeDirCommand         :=makedir
RcCmpOptions           := 
RcCompilerName         :=D:/MinGW-4.7.1/bin/windres.exe 
LinkOptions            :=  -T startup/maskrom.ld -Map Hunter.txt
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). $(IncludeSwitch)D:/MinGW-4.7.1/arm-elf/include $(IncludeSwitch)D:/MinGW-4.7.1/lib/gcc/arm-elf/4.6.0/include 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)c $(LibrarySwitch)gcc $(LibrarySwitch)jpeg $(LibrarySwitch)fs $(LibrarySwitch)usb $(LibrarySwitch)startup $(LibrarySwitch)fat $(LibrarySwitch)sd 
ArLibs                 :=  "c" "gcc" "jpeg" "fs" "usb" "startup" "fat" "sd" 
LibPath                := $(LibraryPathSwitch). $(LibraryPathSwitch)d:/MinGW-4.7.1/lib/gcc/arm-elf/4.6.0 $(LibraryPathSwitch)d:/MinGW-4.7.1/arm-elf/lib $(LibraryPathSwitch)libs 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := D:/MinGW-4.7.1/bin/arm-elf-ar.exe
CXX      := D:/MinGW-4.7.1/bin/arm-elf-g++.exe
CC       := D:/MinGW-4.7.1/bin/arm-elf-gcc.exe
CXXFLAGS :=  -g -O3 -Wall $(Preprocessors)
CFLAGS   :=  -g -O3 -Wall $(Preprocessors)
ASFLAGS  := -c
AS       := D:/MinGW-4.7.1/bin/arm-elf-gcc.exe


##
## User defined environment variables
##
CodeLiteDir:=d:\Program Files (x86)\CodeLite
WXWIN:=C:\wxWidgets-2.9.4
PATH:=$(WXWIN)\lib\gcc_dll;$(PATH)
WXCFG:=gcc_dll\mswu
UNIT_TEST_PP_SRC_DIR:=d:\UnitTest++-1.3
Objects0=$(IntermediateDirectory)/audio_adc_audio_adc.c$(ObjectSuffix) $(IntermediateDirectory)/audio_dac_audio_dac.c$(ObjectSuffix) $(IntermediateDirectory)/common_common.c$(ObjectSuffix) $(IntermediateDirectory)/csi_csi.c$(ObjectSuffix) $(IntermediateDirectory)/csi_csi_isr.c$(ObjectSuffix) $(IntermediateDirectory)/csi_csi_timeinfo.c$(ObjectSuffix) $(IntermediateDirectory)/fat_api_fat_api.c$(ObjectSuffix) $(IntermediateDirectory)/font_font.c$(ObjectSuffix) $(IntermediateDirectory)/gpdma_gpdma.c$(ObjectSuffix) $(IntermediateDirectory)/i2c_i2c.c$(ObjectSuffix) \
	$(IntermediateDirectory)/int_int.c$(ObjectSuffix) $(IntermediateDirectory)/lcd_lcdc.c$(ObjectSuffix) $(IntermediateDirectory)/lcd_osd.c$(ObjectSuffix) $(IntermediateDirectory)/lcd_lcd_driver.c$(ObjectSuffix) $(IntermediateDirectory)/lcd_lcd_interface.c$(ObjectSuffix) $(IntermediateDirectory)/lcd_lcd_tdo24theb2.c$(ObjectSuffix) $(IntermediateDirectory)/lcd_lcd_ili8961.c$(ObjectSuffix) $(IntermediateDirectory)/lcd_lcd_nodisplay.c$(ObjectSuffix) $(IntermediateDirectory)/lcd_lcd_3029.c$(ObjectSuffix) $(IntermediateDirectory)/lcd_lcd_61505.c$(ObjectSuffix) \
	$(IntermediateDirectory)/lcd_lcd_hx8367.c$(ObjectSuffix) $(IntermediateDirectory)/lcd_lcd_7781.c$(ObjectSuffix) $(IntermediateDirectory)/lcd_lcd_ili6480.c$(ObjectSuffix) $(IntermediateDirectory)/lcd_lcd_61505W.c$(ObjectSuffix) $(IntermediateDirectory)/lcd_lcd_3029C.c$(ObjectSuffix) $(IntermediateDirectory)/lcd_lcd_9303.c$(ObjectSuffix) $(IntermediateDirectory)/lcd_lcd_9312.c$(ObjectSuffix) $(IntermediateDirectory)/lcd_lcd_ili9225.c$(ObjectSuffix) $(IntermediateDirectory)/main_main.c$(ObjectSuffix) $(IntermediateDirectory)/menu_menu_display.c$(ObjectSuffix) \
	$(IntermediateDirectory)/menu_menu_struct.c$(ObjectSuffix) $(IntermediateDirectory)/menu_menu_setting.c$(ObjectSuffix) $(IntermediateDirectory)/msg_adkey.c$(ObjectSuffix) $(IntermediateDirectory)/msg_msg.c$(ObjectSuffix) $(IntermediateDirectory)/play_avi_player.c$(ObjectSuffix) $(IntermediateDirectory)/play_gp_fifo.c$(ObjectSuffix) $(IntermediateDirectory)/play_play_picture.c$(ObjectSuffix) $(IntermediateDirectory)/rtc_rtc.c$(ObjectSuffix) $(IntermediateDirectory)/sd_sd_ext.c$(ObjectSuffix) $(IntermediateDirectory)/sensor_sensor.c$(ObjectSuffix) \
	$(IntermediateDirectory)/sensor_sensor_gc0308.c$(ObjectSuffix) $(IntermediateDirectory)/sensor_sensor_nt99140.c$(ObjectSuffix) $(IntermediateDirectory)/sensor_sensor_ov7670.c$(ObjectSuffix) $(IntermediateDirectory)/sensor_sensor_ov9710.c$(ObjectSuffix) 

Objects1=$(IntermediateDirectory)/sensor_sensor_nt99141.c$(ObjectSuffix) $(IntermediateDirectory)/sensor_sensor_bf3925.c$(ObjectSuffix) $(IntermediateDirectory)/sensor_sensor_siv121DS.c$(ObjectSuffix) $(IntermediateDirectory)/sensor_sensor_ov7725.c$(ObjectSuffix) $(IntermediateDirectory)/sensor_sensor_nt99240.c$(ObjectSuffix) $(IntermediateDirectory)/sensor_sensor_siv100B.c$(ObjectSuffix) \
	$(IntermediateDirectory)/startup_spi_boot_cfg.S$(ObjectSuffix) $(IntermediateDirectory)/sys_sys.c$(ObjectSuffix) $(IntermediateDirectory)/timer_timer.c$(ObjectSuffix) $(IntermediateDirectory)/timer_timer_isr.c$(ObjectSuffix) $(IntermediateDirectory)/uart_uart.c$(ObjectSuffix) $(IntermediateDirectory)/spi_spi.c$(ObjectSuffix) $(IntermediateDirectory)/task_task.c$(ObjectSuffix) $(IntermediateDirectory)/task_task_video.c$(ObjectSuffix) $(IntermediateDirectory)/task_task_photo.c$(ObjectSuffix) $(IntermediateDirectory)/task_task_play.c$(ObjectSuffix) \
	$(IntermediateDirectory)/task_task_usb_device.c$(ObjectSuffix) $(IntermediateDirectory)/task_task_holdMode.c$(ObjectSuffix) $(IntermediateDirectory)/tvout_tvout.c$(ObjectSuffix) $(IntermediateDirectory)/led_led.c$(ObjectSuffix) $(IntermediateDirectory)/g_sensor_g_sensor.c$(ObjectSuffix) $(IntermediateDirectory)/g_sensor_g_sensor_dmard07.c$(ObjectSuffix) $(IntermediateDirectory)/g_sensor_g_sensor_gma301a.c$(ObjectSuffix) $(IntermediateDirectory)/g_sensor_g_sensor_null.c$(ObjectSuffix) 



Objects=$(Objects0) $(Objects1) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	@echo $(Objects1) >> $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

PostBuild:
	@echo Executing Post Build commands ...
	arm-elf-objdump -d $(IntermediateDirectory)/$(ProjectName) >./Hunter.lst
	arm-elf-objcopy -O binary $(IntermediateDirectory)/$(ProjectName) output/file/Hunter.bin
	arm-elf-objcopy -j .bootsec -O binary $(IntermediateDirectory)/$(ProjectName) output/file/BootSect.bin
	.\output\MakeSPIBin.exe
	@echo Done

$(IntermediateDirectory)/.d:
	@$(MakeDirCommand) "./Debug"

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/audio_adc_audio_adc.c$(ObjectSuffix): audio_adc/audio_adc.c $(IntermediateDirectory)/audio_adc_audio_adc.c$(DependSuffix)
	$(CC) $(SourceSwitch) "E:/work1/DV3251_UNOS_sdk_release_v1.3/release/audio_adc/audio_adc.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/audio_adc_audio_adc.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/audio_adc_audio_adc.c$(DependSuffix): audio_adc/audio_adc.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/audio_adc_audio_adc.c$(ObjectSuffix) -MF$(IntermediateDirectory)/audio_adc_audio_adc.c$(DependSuffix) -MM "audio_adc/audio_adc.c"

$(IntermediateDirectory)/audio_adc_audio_adc.c$(PreprocessSuffix): audio_adc/audio_adc.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/audio_adc_audio_adc.c$(PreprocessSuffix) "audio_adc/audio_adc.c"

$(IntermediateDirectory)/audio_dac_audio_dac.c$(ObjectSuffix): audio_dac/audio_dac.c $(IntermediateDirectory)/audio_dac_audio_dac.c$(DependSuffix)
	$(CC) $(SourceSwitch) "E:/work1/DV3251_UNOS_sdk_release_v1.3/release/audio_dac/audio_dac.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/audio_dac_audio_dac.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/audio_dac_audio_dac.c$(DependSuffix): audio_dac/audio_dac.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/audio_dac_audio_dac.c$(ObjectSuffix) -MF$(IntermediateDirectory)/audio_dac_audio_dac.c$(DependSuffix) -MM "audio_dac/audio_dac.c"

$(IntermediateDirectory)/audio_dac_audio_dac.c$(PreprocessSuffix): audio_dac/audio_dac.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/audio_dac_audio_dac.c$(PreprocessSuffix) "audio_dac/audio_dac.c"

$(IntermediateDirectory)/common_common.c$(ObjectSuffix): common/common.c $(IntermediateDirectory)/common_common.c$(DependSuffix)
	$(CC) $(SourceSwitch) "E:/work1/DV3251_UNOS_sdk_release_v1.3/release/common/common.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/common_common.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/common_common.c$(DependSuffix): common/common.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/common_common.c$(ObjectSuffix) -MF$(IntermediateDirectory)/common_common.c$(DependSuffix) -MM "common/common.c"

$(IntermediateDirectory)/common_common.c$(PreprocessSuffix): common/common.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/common_common.c$(PreprocessSuffix) "common/common.c"

$(IntermediateDirectory)/csi_csi.c$(ObjectSuffix): csi/csi.c $(IntermediateDirectory)/csi_csi.c$(DependSuffix)
	$(CC) $(SourceSwitch) "E:/work1/DV3251_UNOS_sdk_release_v1.3/release/csi/csi.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/csi_csi.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/csi_csi.c$(DependSuffix): csi/csi.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/csi_csi.c$(ObjectSuffix) -MF$(IntermediateDirectory)/csi_csi.c$(DependSuffix) -MM "csi/csi.c"

$(IntermediateDirectory)/csi_csi.c$(PreprocessSuffix): csi/csi.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/csi_csi.c$(PreprocessSuffix) "csi/csi.c"

$(IntermediateDirectory)/csi_csi_isr.c$(ObjectSuffix): csi/csi_isr.c $(IntermediateDirectory)/csi_csi_isr.c$(DependSuffix)
	$(CC) $(SourceSwitch) "E:/work1/DV3251_UNOS_sdk_release_v1.3/release/csi/csi_isr.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/csi_csi_isr.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/csi_csi_isr.c$(DependSuffix): csi/csi_isr.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/csi_csi_isr.c$(ObjectSuffix) -MF$(IntermediateDirectory)/csi_csi_isr.c$(DependSuffix) -MM "csi/csi_isr.c"

$(IntermediateDirectory)/csi_csi_isr.c$(PreprocessSuffix): csi/csi_isr.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/csi_csi_isr.c$(PreprocessSuffix) "csi/csi_isr.c"

$(IntermediateDirectory)/csi_csi_timeinfo.c$(ObjectSuffix): csi/csi_timeinfo.c $(IntermediateDirectory)/csi_csi_timeinfo.c$(DependSuffix)
	$(CC) $(SourceSwitch) "E:/work1/DV3251_UNOS_sdk_release_v1.3/release/csi/csi_timeinfo.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/csi_csi_timeinfo.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/csi_csi_timeinfo.c$(DependSuffix): csi/csi_timeinfo.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/csi_csi_timeinfo.c$(ObjectSuffix) -MF$(IntermediateDirectory)/csi_csi_timeinfo.c$(DependSuffix) -MM "csi/csi_timeinfo.c"

$(IntermediateDirectory)/csi_csi_timeinfo.c$(PreprocessSuffix): csi/csi_timeinfo.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/csi_csi_timeinfo.c$(PreprocessSuffix) "csi/csi_timeinfo.c"

$(IntermediateDirectory)/fat_api_fat_api.c$(ObjectSuffix): fat_api/fat_api.c $(IntermediateDirectory)/fat_api_fat_api.c$(DependSuffix)
	$(CC) $(SourceSwitch) "E:/work1/DV3251_UNOS_sdk_release_v1.3/release/fat_api/fat_api.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/fat_api_fat_api.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/fat_api_fat_api.c$(DependSuffix): fat_api/fat_api.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/fat_api_fat_api.c$(ObjectSuffix) -MF$(IntermediateDirectory)/fat_api_fat_api.c$(DependSuffix) -MM "fat_api/fat_api.c"

$(IntermediateDirectory)/fat_api_fat_api.c$(PreprocessSuffix): fat_api/fat_api.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/fat_api_fat_api.c$(PreprocessSuffix) "fat_api/fat_api.c"

$(IntermediateDirectory)/font_font.c$(ObjectSuffix): font/font.c $(IntermediateDirectory)/font_font.c$(DependSuffix)
	$(CC) $(SourceSwitch) "E:/work1/DV3251_UNOS_sdk_release_v1.3/release/font/font.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/font_font.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/font_font.c$(DependSuffix): font/font.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/font_font.c$(ObjectSuffix) -MF$(IntermediateDirectory)/font_font.c$(DependSuffix) -MM "font/font.c"

$(IntermediateDirectory)/font_font.c$(PreprocessSuffix): font/font.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/font_font.c$(PreprocessSuffix) "font/font.c"

$(IntermediateDirectory)/gpdma_gpdma.c$(ObjectSuffix): gpdma/gpdma.c $(IntermediateDirectory)/gpdma_gpdma.c$(DependSuffix)
	$(CC) $(SourceSwitch) "E:/work1/DV3251_UNOS_sdk_release_v1.3/release/gpdma/gpdma.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/gpdma_gpdma.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/gpdma_gpdma.c$(DependSuffix): gpdma/gpdma.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/gpdma_gpdma.c$(ObjectSuffix) -MF$(IntermediateDirectory)/gpdma_gpdma.c$(DependSuffix) -MM "gpdma/gpdma.c"

$(IntermediateDirectory)/gpdma_gpdma.c$(PreprocessSuffix): gpdma/gpdma.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/gpdma_gpdma.c$(PreprocessSuffix) "gpdma/gpdma.c"

$(IntermediateDirectory)/i2c_i2c.c$(ObjectSuffix): i2c/i2c.c $(IntermediateDirectory)/i2c_i2c.c$(DependSuffix)
	$(CC) $(SourceSwitch) "E:/work1/DV3251_UNOS_sdk_release_v1.3/release/i2c/i2c.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/i2c_i2c.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/i2c_i2c.c$(DependSuffix): i2c/i2c.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/i2c_i2c.c$(ObjectSuffix) -MF$(IntermediateDirectory)/i2c_i2c.c$(DependSuffix) -MM "i2c/i2c.c"

$(IntermediateDirectory)/i2c_i2c.c$(PreprocessSuffix): i2c/i2c.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/i2c_i2c.c$(PreprocessSuffix) "i2c/i2c.c"

$(IntermediateDirectory)/int_int.c$(ObjectSuffix): int/int.c $(IntermediateDirectory)/int_int.c$(DependSuffix)
	$(CC) $(SourceSwitch) "E:/work1/DV3251_UNOS_sdk_release_v1.3/release/int/int.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/int_int.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/int_int.c$(DependSuffix): int/int.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/int_int.c$(ObjectSuffix) -MF$(IntermediateDirectory)/int_int.c$(DependSuffix) -MM "int/int.c"

$(IntermediateDirectory)/int_int.c$(PreprocessSuffix): int/int.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/int_int.c$(PreprocessSuffix) "int/int.c"

$(IntermediateDirectory)/lcd_lcdc.c$(ObjectSuffix): lcd/lcdc.c $(IntermediateDirectory)/lcd_lcdc.c$(DependSuffix)
	$(CC) $(SourceSwitch) "E:/work1/DV3251_UNOS_sdk_release_v1.3/release/lcd/lcdc.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/lcd_lcdc.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/lcd_lcdc.c$(DependSuffix): lcd/lcdc.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/lcd_lcdc.c$(ObjectSuffix) -MF$(IntermediateDirectory)/lcd_lcdc.c$(DependSuffix) -MM "lcd/lcdc.c"

$(IntermediateDirectory)/lcd_lcdc.c$(PreprocessSuffix): lcd/lcdc.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/lcd_lcdc.c$(PreprocessSuffix) "lcd/lcdc.c"

$(IntermediateDirectory)/lcd_osd.c$(ObjectSuffix): lcd/osd.c $(IntermediateDirectory)/lcd_osd.c$(DependSuffix)
	$(CC) $(SourceSwitch) "E:/work1/DV3251_UNOS_sdk_release_v1.3/release/lcd/osd.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/lcd_osd.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/lcd_osd.c$(DependSuffix): lcd/osd.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/lcd_osd.c$(ObjectSuffix) -MF$(IntermediateDirectory)/lcd_osd.c$(DependSuffix) -MM "lcd/osd.c"

$(IntermediateDirectory)/lcd_osd.c$(PreprocessSuffix): lcd/osd.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/lcd_osd.c$(PreprocessSuffix) "lcd/osd.c"

$(IntermediateDirectory)/lcd_lcd_driver.c$(ObjectSuffix): lcd/lcd_driver.c $(IntermediateDirectory)/lcd_lcd_driver.c$(DependSuffix)
	$(CC) $(SourceSwitch) "E:/work1/DV3251_UNOS_sdk_release_v1.3/release/lcd/lcd_driver.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/lcd_lcd_driver.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/lcd_lcd_driver.c$(DependSuffix): lcd/lcd_driver.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/lcd_lcd_driver.c$(ObjectSuffix) -MF$(IntermediateDirectory)/lcd_lcd_driver.c$(DependSuffix) -MM "lcd/lcd_driver.c"

$(IntermediateDirectory)/lcd_lcd_driver.c$(PreprocessSuffix): lcd/lcd_driver.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/lcd_lcd_driver.c$(PreprocessSuffix) "lcd/lcd_driver.c"

$(IntermediateDirectory)/lcd_lcd_interface.c$(ObjectSuffix): lcd/lcd_interface.c $(IntermediateDirectory)/lcd_lcd_interface.c$(DependSuffix)
	$(CC) $(SourceSwitch) "E:/work1/DV3251_UNOS_sdk_release_v1.3/release/lcd/lcd_interface.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/lcd_lcd_interface.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/lcd_lcd_interface.c$(DependSuffix): lcd/lcd_interface.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/lcd_lcd_interface.c$(ObjectSuffix) -MF$(IntermediateDirectory)/lcd_lcd_interface.c$(DependSuffix) -MM "lcd/lcd_interface.c"

$(IntermediateDirectory)/lcd_lcd_interface.c$(PreprocessSuffix): lcd/lcd_interface.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/lcd_lcd_interface.c$(PreprocessSuffix) "lcd/lcd_interface.c"

$(IntermediateDirectory)/lcd_lcd_tdo24theb2.c$(ObjectSuffix): lcd/lcd_tdo24theb2.c $(IntermediateDirectory)/lcd_lcd_tdo24theb2.c$(DependSuffix)
	$(CC) $(SourceSwitch) "E:/work1/DV3251_UNOS_sdk_release_v1.3/release/lcd/lcd_tdo24theb2.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/lcd_lcd_tdo24theb2.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/lcd_lcd_tdo24theb2.c$(DependSuffix): lcd/lcd_tdo24theb2.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/lcd_lcd_tdo24theb2.c$(ObjectSuffix) -MF$(IntermediateDirectory)/lcd_lcd_tdo24theb2.c$(DependSuffix) -MM "lcd/lcd_tdo24theb2.c"

$(IntermediateDirectory)/lcd_lcd_tdo24theb2.c$(PreprocessSuffix): lcd/lcd_tdo24theb2.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/lcd_lcd_tdo24theb2.c$(PreprocessSuffix) "lcd/lcd_tdo24theb2.c"

$(IntermediateDirectory)/lcd_lcd_ili8961.c$(ObjectSuffix): lcd/lcd_ili8961.c $(IntermediateDirectory)/lcd_lcd_ili8961.c$(DependSuffix)
	$(CC) $(SourceSwitch) "E:/work1/DV3251_UNOS_sdk_release_v1.3/release/lcd/lcd_ili8961.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/lcd_lcd_ili8961.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/lcd_lcd_ili8961.c$(DependSuffix): lcd/lcd_ili8961.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/lcd_lcd_ili8961.c$(ObjectSuffix) -MF$(IntermediateDirectory)/lcd_lcd_ili8961.c$(DependSuffix) -MM "lcd/lcd_ili8961.c"

$(IntermediateDirectory)/lcd_lcd_ili8961.c$(PreprocessSuffix): lcd/lcd_ili8961.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/lcd_lcd_ili8961.c$(PreprocessSuffix) "lcd/lcd_ili8961.c"

$(IntermediateDirectory)/lcd_lcd_nodisplay.c$(ObjectSuffix): lcd/lcd_nodisplay.c $(IntermediateDirectory)/lcd_lcd_nodisplay.c$(DependSuffix)
	$(CC) $(SourceSwitch) "E:/work1/DV3251_UNOS_sdk_release_v1.3/release/lcd/lcd_nodisplay.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/lcd_lcd_nodisplay.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/lcd_lcd_nodisplay.c$(DependSuffix): lcd/lcd_nodisplay.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/lcd_lcd_nodisplay.c$(ObjectSuffix) -MF$(IntermediateDirectory)/lcd_lcd_nodisplay.c$(DependSuffix) -MM "lcd/lcd_nodisplay.c"

$(IntermediateDirectory)/lcd_lcd_nodisplay.c$(PreprocessSuffix): lcd/lcd_nodisplay.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/lcd_lcd_nodisplay.c$(PreprocessSuffix) "lcd/lcd_nodisplay.c"

$(IntermediateDirectory)/lcd_lcd_3029.c$(ObjectSuffix): lcd/lcd_3029.c $(IntermediateDirectory)/lcd_lcd_3029.c$(DependSuffix)
	$(CC) $(SourceSwitch) "E:/work1/DV3251_UNOS_sdk_release_v1.3/release/lcd/lcd_3029.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/lcd_lcd_3029.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/lcd_lcd_3029.c$(DependSuffix): lcd/lcd_3029.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/lcd_lcd_3029.c$(ObjectSuffix) -MF$(IntermediateDirectory)/lcd_lcd_3029.c$(DependSuffix) -MM "lcd/lcd_3029.c"

$(IntermediateDirectory)/lcd_lcd_3029.c$(PreprocessSuffix): lcd/lcd_3029.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/lcd_lcd_3029.c$(PreprocessSuffix) "lcd/lcd_3029.c"

$(IntermediateDirectory)/lcd_lcd_61505.c$(ObjectSuffix): lcd/lcd_61505.c $(IntermediateDirectory)/lcd_lcd_61505.c$(DependSuffix)
	$(CC) $(SourceSwitch) "E:/work1/DV3251_UNOS_sdk_release_v1.3/release/lcd/lcd_61505.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/lcd_lcd_61505.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/lcd_lcd_61505.c$(DependSuffix): lcd/lcd_61505.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/lcd_lcd_61505.c$(ObjectSuffix) -MF$(IntermediateDirectory)/lcd_lcd_61505.c$(DependSuffix) -MM "lcd/lcd_61505.c"

$(IntermediateDirectory)/lcd_lcd_61505.c$(PreprocessSuffix): lcd/lcd_61505.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/lcd_lcd_61505.c$(PreprocessSuffix) "lcd/lcd_61505.c"

$(IntermediateDirectory)/lcd_lcd_hx8367.c$(ObjectSuffix): lcd/lcd_hx8367.c $(IntermediateDirectory)/lcd_lcd_hx8367.c$(DependSuffix)
	$(CC) $(SourceSwitch) "E:/work1/DV3251_UNOS_sdk_release_v1.3/release/lcd/lcd_hx8367.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/lcd_lcd_hx8367.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/lcd_lcd_hx8367.c$(DependSuffix): lcd/lcd_hx8367.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/lcd_lcd_hx8367.c$(ObjectSuffix) -MF$(IntermediateDirectory)/lcd_lcd_hx8367.c$(DependSuffix) -MM "lcd/lcd_hx8367.c"

$(IntermediateDirectory)/lcd_lcd_hx8367.c$(PreprocessSuffix): lcd/lcd_hx8367.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/lcd_lcd_hx8367.c$(PreprocessSuffix) "lcd/lcd_hx8367.c"

$(IntermediateDirectory)/lcd_lcd_7781.c$(ObjectSuffix): lcd/lcd_7781.c $(IntermediateDirectory)/lcd_lcd_7781.c$(DependSuffix)
	$(CC) $(SourceSwitch) "E:/work1/DV3251_UNOS_sdk_release_v1.3/release/lcd/lcd_7781.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/lcd_lcd_7781.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/lcd_lcd_7781.c$(DependSuffix): lcd/lcd_7781.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/lcd_lcd_7781.c$(ObjectSuffix) -MF$(IntermediateDirectory)/lcd_lcd_7781.c$(DependSuffix) -MM "lcd/lcd_7781.c"

$(IntermediateDirectory)/lcd_lcd_7781.c$(PreprocessSuffix): lcd/lcd_7781.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/lcd_lcd_7781.c$(PreprocessSuffix) "lcd/lcd_7781.c"

$(IntermediateDirectory)/lcd_lcd_ili6480.c$(ObjectSuffix): lcd/lcd_ili6480.c $(IntermediateDirectory)/lcd_lcd_ili6480.c$(DependSuffix)
	$(CC) $(SourceSwitch) "E:/work1/DV3251_UNOS_sdk_release_v1.3/release/lcd/lcd_ili6480.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/lcd_lcd_ili6480.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/lcd_lcd_ili6480.c$(DependSuffix): lcd/lcd_ili6480.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/lcd_lcd_ili6480.c$(ObjectSuffix) -MF$(IntermediateDirectory)/lcd_lcd_ili6480.c$(DependSuffix) -MM "lcd/lcd_ili6480.c"

$(IntermediateDirectory)/lcd_lcd_ili6480.c$(PreprocessSuffix): lcd/lcd_ili6480.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/lcd_lcd_ili6480.c$(PreprocessSuffix) "lcd/lcd_ili6480.c"

$(IntermediateDirectory)/lcd_lcd_61505W.c$(ObjectSuffix): lcd/lcd_61505W.c $(IntermediateDirectory)/lcd_lcd_61505W.c$(DependSuffix)
	$(CC) $(SourceSwitch) "E:/work1/DV3251_UNOS_sdk_release_v1.3/release/lcd/lcd_61505W.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/lcd_lcd_61505W.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/lcd_lcd_61505W.c$(DependSuffix): lcd/lcd_61505W.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/lcd_lcd_61505W.c$(ObjectSuffix) -MF$(IntermediateDirectory)/lcd_lcd_61505W.c$(DependSuffix) -MM "lcd/lcd_61505W.c"

$(IntermediateDirectory)/lcd_lcd_61505W.c$(PreprocessSuffix): lcd/lcd_61505W.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/lcd_lcd_61505W.c$(PreprocessSuffix) "lcd/lcd_61505W.c"

$(IntermediateDirectory)/lcd_lcd_3029C.c$(ObjectSuffix): lcd/lcd_3029C.c $(IntermediateDirectory)/lcd_lcd_3029C.c$(DependSuffix)
	$(CC) $(SourceSwitch) "E:/work1/DV3251_UNOS_sdk_release_v1.3/release/lcd/lcd_3029C.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/lcd_lcd_3029C.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/lcd_lcd_3029C.c$(DependSuffix): lcd/lcd_3029C.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/lcd_lcd_3029C.c$(ObjectSuffix) -MF$(IntermediateDirectory)/lcd_lcd_3029C.c$(DependSuffix) -MM "lcd/lcd_3029C.c"

$(IntermediateDirectory)/lcd_lcd_3029C.c$(PreprocessSuffix): lcd/lcd_3029C.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/lcd_lcd_3029C.c$(PreprocessSuffix) "lcd/lcd_3029C.c"

$(IntermediateDirectory)/lcd_lcd_9303.c$(ObjectSuffix): lcd/lcd_9303.c $(IntermediateDirectory)/lcd_lcd_9303.c$(DependSuffix)
	$(CC) $(SourceSwitch) "E:/work1/DV3251_UNOS_sdk_release_v1.3/release/lcd/lcd_9303.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/lcd_lcd_9303.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/lcd_lcd_9303.c$(DependSuffix): lcd/lcd_9303.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/lcd_lcd_9303.c$(ObjectSuffix) -MF$(IntermediateDirectory)/lcd_lcd_9303.c$(DependSuffix) -MM "lcd/lcd_9303.c"

$(IntermediateDirectory)/lcd_lcd_9303.c$(PreprocessSuffix): lcd/lcd_9303.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/lcd_lcd_9303.c$(PreprocessSuffix) "lcd/lcd_9303.c"

$(IntermediateDirectory)/lcd_lcd_9312.c$(ObjectSuffix): lcd/lcd_9312.c $(IntermediateDirectory)/lcd_lcd_9312.c$(DependSuffix)
	$(CC) $(SourceSwitch) "E:/work1/DV3251_UNOS_sdk_release_v1.3/release/lcd/lcd_9312.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/lcd_lcd_9312.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/lcd_lcd_9312.c$(DependSuffix): lcd/lcd_9312.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/lcd_lcd_9312.c$(ObjectSuffix) -MF$(IntermediateDirectory)/lcd_lcd_9312.c$(DependSuffix) -MM "lcd/lcd_9312.c"

$(IntermediateDirectory)/lcd_lcd_9312.c$(PreprocessSuffix): lcd/lcd_9312.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/lcd_lcd_9312.c$(PreprocessSuffix) "lcd/lcd_9312.c"

$(IntermediateDirectory)/lcd_lcd_ili9225.c$(ObjectSuffix): lcd/lcd_ili9225.c $(IntermediateDirectory)/lcd_lcd_ili9225.c$(DependSuffix)
	$(CC) $(SourceSwitch) "E:/work1/DV3251_UNOS_sdk_release_v1.3/release/lcd/lcd_ili9225.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/lcd_lcd_ili9225.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/lcd_lcd_ili9225.c$(DependSuffix): lcd/lcd_ili9225.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/lcd_lcd_ili9225.c$(ObjectSuffix) -MF$(IntermediateDirectory)/lcd_lcd_ili9225.c$(DependSuffix) -MM "lcd/lcd_ili9225.c"

$(IntermediateDirectory)/lcd_lcd_ili9225.c$(PreprocessSuffix): lcd/lcd_ili9225.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/lcd_lcd_ili9225.c$(PreprocessSuffix) "lcd/lcd_ili9225.c"

$(IntermediateDirectory)/main_main.c$(ObjectSuffix): main/main.c $(IntermediateDirectory)/main_main.c$(DependSuffix)
	$(CC) $(SourceSwitch) "E:/work1/DV3251_UNOS_sdk_release_v1.3/release/main/main.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main_main.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main_main.c$(DependSuffix): main/main.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main_main.c$(ObjectSuffix) -MF$(IntermediateDirectory)/main_main.c$(DependSuffix) -MM "main/main.c"

$(IntermediateDirectory)/main_main.c$(PreprocessSuffix): main/main.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main_main.c$(PreprocessSuffix) "main/main.c"

$(IntermediateDirectory)/menu_menu_display.c$(ObjectSuffix): menu/menu_display.c $(IntermediateDirectory)/menu_menu_display.c$(DependSuffix)
	$(CC) $(SourceSwitch) "E:/work1/DV3251_UNOS_sdk_release_v1.3/release/menu/menu_display.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/menu_menu_display.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/menu_menu_display.c$(DependSuffix): menu/menu_display.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/menu_menu_display.c$(ObjectSuffix) -MF$(IntermediateDirectory)/menu_menu_display.c$(DependSuffix) -MM "menu/menu_display.c"

$(IntermediateDirectory)/menu_menu_display.c$(PreprocessSuffix): menu/menu_display.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/menu_menu_display.c$(PreprocessSuffix) "menu/menu_display.c"

$(IntermediateDirectory)/menu_menu_struct.c$(ObjectSuffix): menu/menu_struct.c $(IntermediateDirectory)/menu_menu_struct.c$(DependSuffix)
	$(CC) $(SourceSwitch) "E:/work1/DV3251_UNOS_sdk_release_v1.3/release/menu/menu_struct.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/menu_menu_struct.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/menu_menu_struct.c$(DependSuffix): menu/menu_struct.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/menu_menu_struct.c$(ObjectSuffix) -MF$(IntermediateDirectory)/menu_menu_struct.c$(DependSuffix) -MM "menu/menu_struct.c"

$(IntermediateDirectory)/menu_menu_struct.c$(PreprocessSuffix): menu/menu_struct.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/menu_menu_struct.c$(PreprocessSuffix) "menu/menu_struct.c"

$(IntermediateDirectory)/menu_menu_setting.c$(ObjectSuffix): menu/menu_setting.c $(IntermediateDirectory)/menu_menu_setting.c$(DependSuffix)
	$(CC) $(SourceSwitch) "E:/work1/DV3251_UNOS_sdk_release_v1.3/release/menu/menu_setting.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/menu_menu_setting.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/menu_menu_setting.c$(DependSuffix): menu/menu_setting.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/menu_menu_setting.c$(ObjectSuffix) -MF$(IntermediateDirectory)/menu_menu_setting.c$(DependSuffix) -MM "menu/menu_setting.c"

$(IntermediateDirectory)/menu_menu_setting.c$(PreprocessSuffix): menu/menu_setting.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/menu_menu_setting.c$(PreprocessSuffix) "menu/menu_setting.c"

$(IntermediateDirectory)/msg_adkey.c$(ObjectSuffix): msg/adkey.c $(IntermediateDirectory)/msg_adkey.c$(DependSuffix)
	$(CC) $(SourceSwitch) "E:/work1/DV3251_UNOS_sdk_release_v1.3/release/msg/adkey.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/msg_adkey.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/msg_adkey.c$(DependSuffix): msg/adkey.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/msg_adkey.c$(ObjectSuffix) -MF$(IntermediateDirectory)/msg_adkey.c$(DependSuffix) -MM "msg/adkey.c"

$(IntermediateDirectory)/msg_adkey.c$(PreprocessSuffix): msg/adkey.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/msg_adkey.c$(PreprocessSuffix) "msg/adkey.c"

$(IntermediateDirectory)/msg_msg.c$(ObjectSuffix): msg/msg.c $(IntermediateDirectory)/msg_msg.c$(DependSuffix)
	$(CC) $(SourceSwitch) "E:/work1/DV3251_UNOS_sdk_release_v1.3/release/msg/msg.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/msg_msg.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/msg_msg.c$(DependSuffix): msg/msg.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/msg_msg.c$(ObjectSuffix) -MF$(IntermediateDirectory)/msg_msg.c$(DependSuffix) -MM "msg/msg.c"

$(IntermediateDirectory)/msg_msg.c$(PreprocessSuffix): msg/msg.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/msg_msg.c$(PreprocessSuffix) "msg/msg.c"

$(IntermediateDirectory)/play_avi_player.c$(ObjectSuffix): play/avi_player.c $(IntermediateDirectory)/play_avi_player.c$(DependSuffix)
	$(CC) $(SourceSwitch) "E:/work1/DV3251_UNOS_sdk_release_v1.3/release/play/avi_player.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/play_avi_player.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/play_avi_player.c$(DependSuffix): play/avi_player.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/play_avi_player.c$(ObjectSuffix) -MF$(IntermediateDirectory)/play_avi_player.c$(DependSuffix) -MM "play/avi_player.c"

$(IntermediateDirectory)/play_avi_player.c$(PreprocessSuffix): play/avi_player.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/play_avi_player.c$(PreprocessSuffix) "play/avi_player.c"

$(IntermediateDirectory)/play_gp_fifo.c$(ObjectSuffix): play/gp_fifo.c $(IntermediateDirectory)/play_gp_fifo.c$(DependSuffix)
	$(CC) $(SourceSwitch) "E:/work1/DV3251_UNOS_sdk_release_v1.3/release/play/gp_fifo.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/play_gp_fifo.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/play_gp_fifo.c$(DependSuffix): play/gp_fifo.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/play_gp_fifo.c$(ObjectSuffix) -MF$(IntermediateDirectory)/play_gp_fifo.c$(DependSuffix) -MM "play/gp_fifo.c"

$(IntermediateDirectory)/play_gp_fifo.c$(PreprocessSuffix): play/gp_fifo.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/play_gp_fifo.c$(PreprocessSuffix) "play/gp_fifo.c"

$(IntermediateDirectory)/play_play_picture.c$(ObjectSuffix): play/play_picture.c $(IntermediateDirectory)/play_play_picture.c$(DependSuffix)
	$(CC) $(SourceSwitch) "E:/work1/DV3251_UNOS_sdk_release_v1.3/release/play/play_picture.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/play_play_picture.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/play_play_picture.c$(DependSuffix): play/play_picture.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/play_play_picture.c$(ObjectSuffix) -MF$(IntermediateDirectory)/play_play_picture.c$(DependSuffix) -MM "play/play_picture.c"

$(IntermediateDirectory)/play_play_picture.c$(PreprocessSuffix): play/play_picture.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/play_play_picture.c$(PreprocessSuffix) "play/play_picture.c"

$(IntermediateDirectory)/rtc_rtc.c$(ObjectSuffix): rtc/rtc.c $(IntermediateDirectory)/rtc_rtc.c$(DependSuffix)
	$(CC) $(SourceSwitch) "E:/work1/DV3251_UNOS_sdk_release_v1.3/release/rtc/rtc.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/rtc_rtc.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/rtc_rtc.c$(DependSuffix): rtc/rtc.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/rtc_rtc.c$(ObjectSuffix) -MF$(IntermediateDirectory)/rtc_rtc.c$(DependSuffix) -MM "rtc/rtc.c"

$(IntermediateDirectory)/rtc_rtc.c$(PreprocessSuffix): rtc/rtc.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/rtc_rtc.c$(PreprocessSuffix) "rtc/rtc.c"

$(IntermediateDirectory)/sd_sd_ext.c$(ObjectSuffix): sd/sd_ext.c $(IntermediateDirectory)/sd_sd_ext.c$(DependSuffix)
	$(CC) $(SourceSwitch) "E:/work1/DV3251_UNOS_sdk_release_v1.3/release/sd/sd_ext.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/sd_sd_ext.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/sd_sd_ext.c$(DependSuffix): sd/sd_ext.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/sd_sd_ext.c$(ObjectSuffix) -MF$(IntermediateDirectory)/sd_sd_ext.c$(DependSuffix) -MM "sd/sd_ext.c"

$(IntermediateDirectory)/sd_sd_ext.c$(PreprocessSuffix): sd/sd_ext.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/sd_sd_ext.c$(PreprocessSuffix) "sd/sd_ext.c"

$(IntermediateDirectory)/sensor_sensor.c$(ObjectSuffix): sensor/sensor.c $(IntermediateDirectory)/sensor_sensor.c$(DependSuffix)
	$(CC) $(SourceSwitch) "E:/work1/DV3251_UNOS_sdk_release_v1.3/release/sensor/sensor.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/sensor_sensor.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/sensor_sensor.c$(DependSuffix): sensor/sensor.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/sensor_sensor.c$(ObjectSuffix) -MF$(IntermediateDirectory)/sensor_sensor.c$(DependSuffix) -MM "sensor/sensor.c"

$(IntermediateDirectory)/sensor_sensor.c$(PreprocessSuffix): sensor/sensor.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/sensor_sensor.c$(PreprocessSuffix) "sensor/sensor.c"

$(IntermediateDirectory)/sensor_sensor_gc0308.c$(ObjectSuffix): sensor/sensor_gc0308.c $(IntermediateDirectory)/sensor_sensor_gc0308.c$(DependSuffix)
	$(CC) $(SourceSwitch) "E:/work1/DV3251_UNOS_sdk_release_v1.3/release/sensor/sensor_gc0308.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/sensor_sensor_gc0308.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/sensor_sensor_gc0308.c$(DependSuffix): sensor/sensor_gc0308.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/sensor_sensor_gc0308.c$(ObjectSuffix) -MF$(IntermediateDirectory)/sensor_sensor_gc0308.c$(DependSuffix) -MM "sensor/sensor_gc0308.c"

$(IntermediateDirectory)/sensor_sensor_gc0308.c$(PreprocessSuffix): sensor/sensor_gc0308.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/sensor_sensor_gc0308.c$(PreprocessSuffix) "sensor/sensor_gc0308.c"

$(IntermediateDirectory)/sensor_sensor_nt99140.c$(ObjectSuffix): sensor/sensor_nt99140.c $(IntermediateDirectory)/sensor_sensor_nt99140.c$(DependSuffix)
	$(CC) $(SourceSwitch) "E:/work1/DV3251_UNOS_sdk_release_v1.3/release/sensor/sensor_nt99140.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/sensor_sensor_nt99140.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/sensor_sensor_nt99140.c$(DependSuffix): sensor/sensor_nt99140.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/sensor_sensor_nt99140.c$(ObjectSuffix) -MF$(IntermediateDirectory)/sensor_sensor_nt99140.c$(DependSuffix) -MM "sensor/sensor_nt99140.c"

$(IntermediateDirectory)/sensor_sensor_nt99140.c$(PreprocessSuffix): sensor/sensor_nt99140.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/sensor_sensor_nt99140.c$(PreprocessSuffix) "sensor/sensor_nt99140.c"

$(IntermediateDirectory)/sensor_sensor_ov7670.c$(ObjectSuffix): sensor/sensor_ov7670.c $(IntermediateDirectory)/sensor_sensor_ov7670.c$(DependSuffix)
	$(CC) $(SourceSwitch) "E:/work1/DV3251_UNOS_sdk_release_v1.3/release/sensor/sensor_ov7670.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/sensor_sensor_ov7670.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/sensor_sensor_ov7670.c$(DependSuffix): sensor/sensor_ov7670.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/sensor_sensor_ov7670.c$(ObjectSuffix) -MF$(IntermediateDirectory)/sensor_sensor_ov7670.c$(DependSuffix) -MM "sensor/sensor_ov7670.c"

$(IntermediateDirectory)/sensor_sensor_ov7670.c$(PreprocessSuffix): sensor/sensor_ov7670.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/sensor_sensor_ov7670.c$(PreprocessSuffix) "sensor/sensor_ov7670.c"

$(IntermediateDirectory)/sensor_sensor_ov9710.c$(ObjectSuffix): sensor/sensor_ov9710.c $(IntermediateDirectory)/sensor_sensor_ov9710.c$(DependSuffix)
	$(CC) $(SourceSwitch) "E:/work1/DV3251_UNOS_sdk_release_v1.3/release/sensor/sensor_ov9710.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/sensor_sensor_ov9710.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/sensor_sensor_ov9710.c$(DependSuffix): sensor/sensor_ov9710.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/sensor_sensor_ov9710.c$(ObjectSuffix) -MF$(IntermediateDirectory)/sensor_sensor_ov9710.c$(DependSuffix) -MM "sensor/sensor_ov9710.c"

$(IntermediateDirectory)/sensor_sensor_ov9710.c$(PreprocessSuffix): sensor/sensor_ov9710.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/sensor_sensor_ov9710.c$(PreprocessSuffix) "sensor/sensor_ov9710.c"

$(IntermediateDirectory)/sensor_sensor_nt99141.c$(ObjectSuffix): sensor/sensor_nt99141.c $(IntermediateDirectory)/sensor_sensor_nt99141.c$(DependSuffix)
	$(CC) $(SourceSwitch) "E:/work1/DV3251_UNOS_sdk_release_v1.3/release/sensor/sensor_nt99141.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/sensor_sensor_nt99141.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/sensor_sensor_nt99141.c$(DependSuffix): sensor/sensor_nt99141.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/sensor_sensor_nt99141.c$(ObjectSuffix) -MF$(IntermediateDirectory)/sensor_sensor_nt99141.c$(DependSuffix) -MM "sensor/sensor_nt99141.c"

$(IntermediateDirectory)/sensor_sensor_nt99141.c$(PreprocessSuffix): sensor/sensor_nt99141.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/sensor_sensor_nt99141.c$(PreprocessSuffix) "sensor/sensor_nt99141.c"

$(IntermediateDirectory)/sensor_sensor_bf3925.c$(ObjectSuffix): sensor/sensor_bf3925.c $(IntermediateDirectory)/sensor_sensor_bf3925.c$(DependSuffix)
	$(CC) $(SourceSwitch) "E:/work1/DV3251_UNOS_sdk_release_v1.3/release/sensor/sensor_bf3925.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/sensor_sensor_bf3925.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/sensor_sensor_bf3925.c$(DependSuffix): sensor/sensor_bf3925.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/sensor_sensor_bf3925.c$(ObjectSuffix) -MF$(IntermediateDirectory)/sensor_sensor_bf3925.c$(DependSuffix) -MM "sensor/sensor_bf3925.c"

$(IntermediateDirectory)/sensor_sensor_bf3925.c$(PreprocessSuffix): sensor/sensor_bf3925.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/sensor_sensor_bf3925.c$(PreprocessSuffix) "sensor/sensor_bf3925.c"

$(IntermediateDirectory)/sensor_sensor_siv121DS.c$(ObjectSuffix): sensor/sensor_siv121DS.c $(IntermediateDirectory)/sensor_sensor_siv121DS.c$(DependSuffix)
	$(CC) $(SourceSwitch) "E:/work1/DV3251_UNOS_sdk_release_v1.3/release/sensor/sensor_siv121DS.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/sensor_sensor_siv121DS.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/sensor_sensor_siv121DS.c$(DependSuffix): sensor/sensor_siv121DS.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/sensor_sensor_siv121DS.c$(ObjectSuffix) -MF$(IntermediateDirectory)/sensor_sensor_siv121DS.c$(DependSuffix) -MM "sensor/sensor_siv121DS.c"

$(IntermediateDirectory)/sensor_sensor_siv121DS.c$(PreprocessSuffix): sensor/sensor_siv121DS.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/sensor_sensor_siv121DS.c$(PreprocessSuffix) "sensor/sensor_siv121DS.c"

$(IntermediateDirectory)/sensor_sensor_ov7725.c$(ObjectSuffix): sensor/sensor_ov7725.c $(IntermediateDirectory)/sensor_sensor_ov7725.c$(DependSuffix)
	$(CC) $(SourceSwitch) "E:/work1/DV3251_UNOS_sdk_release_v1.3/release/sensor/sensor_ov7725.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/sensor_sensor_ov7725.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/sensor_sensor_ov7725.c$(DependSuffix): sensor/sensor_ov7725.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/sensor_sensor_ov7725.c$(ObjectSuffix) -MF$(IntermediateDirectory)/sensor_sensor_ov7725.c$(DependSuffix) -MM "sensor/sensor_ov7725.c"

$(IntermediateDirectory)/sensor_sensor_ov7725.c$(PreprocessSuffix): sensor/sensor_ov7725.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/sensor_sensor_ov7725.c$(PreprocessSuffix) "sensor/sensor_ov7725.c"

$(IntermediateDirectory)/sensor_sensor_nt99240.c$(ObjectSuffix): sensor/sensor_nt99240.c $(IntermediateDirectory)/sensor_sensor_nt99240.c$(DependSuffix)
	$(CC) $(SourceSwitch) "E:/work1/DV3251_UNOS_sdk_release_v1.3/release/sensor/sensor_nt99240.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/sensor_sensor_nt99240.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/sensor_sensor_nt99240.c$(DependSuffix): sensor/sensor_nt99240.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/sensor_sensor_nt99240.c$(ObjectSuffix) -MF$(IntermediateDirectory)/sensor_sensor_nt99240.c$(DependSuffix) -MM "sensor/sensor_nt99240.c"

$(IntermediateDirectory)/sensor_sensor_nt99240.c$(PreprocessSuffix): sensor/sensor_nt99240.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/sensor_sensor_nt99240.c$(PreprocessSuffix) "sensor/sensor_nt99240.c"

$(IntermediateDirectory)/sensor_sensor_siv100B.c$(ObjectSuffix): sensor/sensor_siv100B.c $(IntermediateDirectory)/sensor_sensor_siv100B.c$(DependSuffix)
	$(CC) $(SourceSwitch) "E:/work1/DV3251_UNOS_sdk_release_v1.3/release/sensor/sensor_siv100B.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/sensor_sensor_siv100B.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/sensor_sensor_siv100B.c$(DependSuffix): sensor/sensor_siv100B.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/sensor_sensor_siv100B.c$(ObjectSuffix) -MF$(IntermediateDirectory)/sensor_sensor_siv100B.c$(DependSuffix) -MM "sensor/sensor_siv100B.c"

$(IntermediateDirectory)/sensor_sensor_siv100B.c$(PreprocessSuffix): sensor/sensor_siv100B.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/sensor_sensor_siv100B.c$(PreprocessSuffix) "sensor/sensor_siv100B.c"

$(IntermediateDirectory)/startup_spi_boot_cfg.S$(ObjectSuffix): startup/spi_boot_cfg.S $(IntermediateDirectory)/startup_spi_boot_cfg.S$(DependSuffix)
	$(AS) "E:/work1/DV3251_UNOS_sdk_release_v1.3/release/startup/spi_boot_cfg.S" $(ASFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/startup_spi_boot_cfg.S$(ObjectSuffix) -I$(IncludePath)
$(IntermediateDirectory)/startup_spi_boot_cfg.S$(DependSuffix): startup/spi_boot_cfg.S
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/startup_spi_boot_cfg.S$(ObjectSuffix) -MF$(IntermediateDirectory)/startup_spi_boot_cfg.S$(DependSuffix) -MM "startup/spi_boot_cfg.S"

$(IntermediateDirectory)/startup_spi_boot_cfg.S$(PreprocessSuffix): startup/spi_boot_cfg.S
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/startup_spi_boot_cfg.S$(PreprocessSuffix) "startup/spi_boot_cfg.S"

$(IntermediateDirectory)/sys_sys.c$(ObjectSuffix): sys/sys.c $(IntermediateDirectory)/sys_sys.c$(DependSuffix)
	$(CC) $(SourceSwitch) "E:/work1/DV3251_UNOS_sdk_release_v1.3/release/sys/sys.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/sys_sys.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/sys_sys.c$(DependSuffix): sys/sys.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/sys_sys.c$(ObjectSuffix) -MF$(IntermediateDirectory)/sys_sys.c$(DependSuffix) -MM "sys/sys.c"

$(IntermediateDirectory)/sys_sys.c$(PreprocessSuffix): sys/sys.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/sys_sys.c$(PreprocessSuffix) "sys/sys.c"

$(IntermediateDirectory)/timer_timer.c$(ObjectSuffix): timer/timer.c $(IntermediateDirectory)/timer_timer.c$(DependSuffix)
	$(CC) $(SourceSwitch) "E:/work1/DV3251_UNOS_sdk_release_v1.3/release/timer/timer.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/timer_timer.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/timer_timer.c$(DependSuffix): timer/timer.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/timer_timer.c$(ObjectSuffix) -MF$(IntermediateDirectory)/timer_timer.c$(DependSuffix) -MM "timer/timer.c"

$(IntermediateDirectory)/timer_timer.c$(PreprocessSuffix): timer/timer.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/timer_timer.c$(PreprocessSuffix) "timer/timer.c"

$(IntermediateDirectory)/timer_timer_isr.c$(ObjectSuffix): timer/timer_isr.c $(IntermediateDirectory)/timer_timer_isr.c$(DependSuffix)
	$(CC) $(SourceSwitch) "E:/work1/DV3251_UNOS_sdk_release_v1.3/release/timer/timer_isr.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/timer_timer_isr.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/timer_timer_isr.c$(DependSuffix): timer/timer_isr.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/timer_timer_isr.c$(ObjectSuffix) -MF$(IntermediateDirectory)/timer_timer_isr.c$(DependSuffix) -MM "timer/timer_isr.c"

$(IntermediateDirectory)/timer_timer_isr.c$(PreprocessSuffix): timer/timer_isr.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/timer_timer_isr.c$(PreprocessSuffix) "timer/timer_isr.c"

$(IntermediateDirectory)/uart_uart.c$(ObjectSuffix): uart/uart.c $(IntermediateDirectory)/uart_uart.c$(DependSuffix)
	$(CC) $(SourceSwitch) "E:/work1/DV3251_UNOS_sdk_release_v1.3/release/uart/uart.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/uart_uart.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/uart_uart.c$(DependSuffix): uart/uart.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/uart_uart.c$(ObjectSuffix) -MF$(IntermediateDirectory)/uart_uart.c$(DependSuffix) -MM "uart/uart.c"

$(IntermediateDirectory)/uart_uart.c$(PreprocessSuffix): uart/uart.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/uart_uart.c$(PreprocessSuffix) "uart/uart.c"

$(IntermediateDirectory)/spi_spi.c$(ObjectSuffix): spi/spi.c $(IntermediateDirectory)/spi_spi.c$(DependSuffix)
	$(CC) $(SourceSwitch) "E:/work1/DV3251_UNOS_sdk_release_v1.3/release/spi/spi.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/spi_spi.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/spi_spi.c$(DependSuffix): spi/spi.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/spi_spi.c$(ObjectSuffix) -MF$(IntermediateDirectory)/spi_spi.c$(DependSuffix) -MM "spi/spi.c"

$(IntermediateDirectory)/spi_spi.c$(PreprocessSuffix): spi/spi.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/spi_spi.c$(PreprocessSuffix) "spi/spi.c"

$(IntermediateDirectory)/task_task.c$(ObjectSuffix): task/task.c $(IntermediateDirectory)/task_task.c$(DependSuffix)
	$(CC) $(SourceSwitch) "E:/work1/DV3251_UNOS_sdk_release_v1.3/release/task/task.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/task_task.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/task_task.c$(DependSuffix): task/task.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/task_task.c$(ObjectSuffix) -MF$(IntermediateDirectory)/task_task.c$(DependSuffix) -MM "task/task.c"

$(IntermediateDirectory)/task_task.c$(PreprocessSuffix): task/task.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/task_task.c$(PreprocessSuffix) "task/task.c"

$(IntermediateDirectory)/task_task_video.c$(ObjectSuffix): task/task_video.c $(IntermediateDirectory)/task_task_video.c$(DependSuffix)
	$(CC) $(SourceSwitch) "E:/work1/DV3251_UNOS_sdk_release_v1.3/release/task/task_video.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/task_task_video.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/task_task_video.c$(DependSuffix): task/task_video.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/task_task_video.c$(ObjectSuffix) -MF$(IntermediateDirectory)/task_task_video.c$(DependSuffix) -MM "task/task_video.c"

$(IntermediateDirectory)/task_task_video.c$(PreprocessSuffix): task/task_video.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/task_task_video.c$(PreprocessSuffix) "task/task_video.c"

$(IntermediateDirectory)/task_task_photo.c$(ObjectSuffix): task/task_photo.c $(IntermediateDirectory)/task_task_photo.c$(DependSuffix)
	$(CC) $(SourceSwitch) "E:/work1/DV3251_UNOS_sdk_release_v1.3/release/task/task_photo.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/task_task_photo.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/task_task_photo.c$(DependSuffix): task/task_photo.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/task_task_photo.c$(ObjectSuffix) -MF$(IntermediateDirectory)/task_task_photo.c$(DependSuffix) -MM "task/task_photo.c"

$(IntermediateDirectory)/task_task_photo.c$(PreprocessSuffix): task/task_photo.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/task_task_photo.c$(PreprocessSuffix) "task/task_photo.c"

$(IntermediateDirectory)/task_task_play.c$(ObjectSuffix): task/task_play.c $(IntermediateDirectory)/task_task_play.c$(DependSuffix)
	$(CC) $(SourceSwitch) "E:/work1/DV3251_UNOS_sdk_release_v1.3/release/task/task_play.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/task_task_play.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/task_task_play.c$(DependSuffix): task/task_play.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/task_task_play.c$(ObjectSuffix) -MF$(IntermediateDirectory)/task_task_play.c$(DependSuffix) -MM "task/task_play.c"

$(IntermediateDirectory)/task_task_play.c$(PreprocessSuffix): task/task_play.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/task_task_play.c$(PreprocessSuffix) "task/task_play.c"

$(IntermediateDirectory)/task_task_usb_device.c$(ObjectSuffix): task/task_usb_device.c $(IntermediateDirectory)/task_task_usb_device.c$(DependSuffix)
	$(CC) $(SourceSwitch) "E:/work1/DV3251_UNOS_sdk_release_v1.3/release/task/task_usb_device.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/task_task_usb_device.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/task_task_usb_device.c$(DependSuffix): task/task_usb_device.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/task_task_usb_device.c$(ObjectSuffix) -MF$(IntermediateDirectory)/task_task_usb_device.c$(DependSuffix) -MM "task/task_usb_device.c"

$(IntermediateDirectory)/task_task_usb_device.c$(PreprocessSuffix): task/task_usb_device.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/task_task_usb_device.c$(PreprocessSuffix) "task/task_usb_device.c"

$(IntermediateDirectory)/task_task_holdMode.c$(ObjectSuffix): task/task_holdMode.c $(IntermediateDirectory)/task_task_holdMode.c$(DependSuffix)
	$(CC) $(SourceSwitch) "E:/work1/DV3251_UNOS_sdk_release_v1.3/release/task/task_holdMode.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/task_task_holdMode.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/task_task_holdMode.c$(DependSuffix): task/task_holdMode.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/task_task_holdMode.c$(ObjectSuffix) -MF$(IntermediateDirectory)/task_task_holdMode.c$(DependSuffix) -MM "task/task_holdMode.c"

$(IntermediateDirectory)/task_task_holdMode.c$(PreprocessSuffix): task/task_holdMode.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/task_task_holdMode.c$(PreprocessSuffix) "task/task_holdMode.c"

$(IntermediateDirectory)/tvout_tvout.c$(ObjectSuffix): tvout/tvout.c $(IntermediateDirectory)/tvout_tvout.c$(DependSuffix)
	$(CC) $(SourceSwitch) "E:/work1/DV3251_UNOS_sdk_release_v1.3/release/tvout/tvout.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/tvout_tvout.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/tvout_tvout.c$(DependSuffix): tvout/tvout.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/tvout_tvout.c$(ObjectSuffix) -MF$(IntermediateDirectory)/tvout_tvout.c$(DependSuffix) -MM "tvout/tvout.c"

$(IntermediateDirectory)/tvout_tvout.c$(PreprocessSuffix): tvout/tvout.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/tvout_tvout.c$(PreprocessSuffix) "tvout/tvout.c"

$(IntermediateDirectory)/led_led.c$(ObjectSuffix): led/led.c $(IntermediateDirectory)/led_led.c$(DependSuffix)
	$(CC) $(SourceSwitch) "E:/work1/DV3251_UNOS_sdk_release_v1.3/release/led/led.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/led_led.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/led_led.c$(DependSuffix): led/led.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/led_led.c$(ObjectSuffix) -MF$(IntermediateDirectory)/led_led.c$(DependSuffix) -MM "led/led.c"

$(IntermediateDirectory)/led_led.c$(PreprocessSuffix): led/led.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/led_led.c$(PreprocessSuffix) "led/led.c"

$(IntermediateDirectory)/g_sensor_g_sensor.c$(ObjectSuffix): g_sensor/g_sensor.c $(IntermediateDirectory)/g_sensor_g_sensor.c$(DependSuffix)
	$(CC) $(SourceSwitch) "E:/work1/DV3251_UNOS_sdk_release_v1.3/release/g_sensor/g_sensor.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/g_sensor_g_sensor.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/g_sensor_g_sensor.c$(DependSuffix): g_sensor/g_sensor.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/g_sensor_g_sensor.c$(ObjectSuffix) -MF$(IntermediateDirectory)/g_sensor_g_sensor.c$(DependSuffix) -MM "g_sensor/g_sensor.c"

$(IntermediateDirectory)/g_sensor_g_sensor.c$(PreprocessSuffix): g_sensor/g_sensor.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/g_sensor_g_sensor.c$(PreprocessSuffix) "g_sensor/g_sensor.c"

$(IntermediateDirectory)/g_sensor_g_sensor_dmard07.c$(ObjectSuffix): g_sensor/g_sensor_dmard07.c $(IntermediateDirectory)/g_sensor_g_sensor_dmard07.c$(DependSuffix)
	$(CC) $(SourceSwitch) "E:/work1/DV3251_UNOS_sdk_release_v1.3/release/g_sensor/g_sensor_dmard07.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/g_sensor_g_sensor_dmard07.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/g_sensor_g_sensor_dmard07.c$(DependSuffix): g_sensor/g_sensor_dmard07.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/g_sensor_g_sensor_dmard07.c$(ObjectSuffix) -MF$(IntermediateDirectory)/g_sensor_g_sensor_dmard07.c$(DependSuffix) -MM "g_sensor/g_sensor_dmard07.c"

$(IntermediateDirectory)/g_sensor_g_sensor_dmard07.c$(PreprocessSuffix): g_sensor/g_sensor_dmard07.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/g_sensor_g_sensor_dmard07.c$(PreprocessSuffix) "g_sensor/g_sensor_dmard07.c"

$(IntermediateDirectory)/g_sensor_g_sensor_gma301a.c$(ObjectSuffix): g_sensor/g_sensor_gma301a.c $(IntermediateDirectory)/g_sensor_g_sensor_gma301a.c$(DependSuffix)
	$(CC) $(SourceSwitch) "E:/work1/DV3251_UNOS_sdk_release_v1.3/release/g_sensor/g_sensor_gma301a.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/g_sensor_g_sensor_gma301a.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/g_sensor_g_sensor_gma301a.c$(DependSuffix): g_sensor/g_sensor_gma301a.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/g_sensor_g_sensor_gma301a.c$(ObjectSuffix) -MF$(IntermediateDirectory)/g_sensor_g_sensor_gma301a.c$(DependSuffix) -MM "g_sensor/g_sensor_gma301a.c"

$(IntermediateDirectory)/g_sensor_g_sensor_gma301a.c$(PreprocessSuffix): g_sensor/g_sensor_gma301a.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/g_sensor_g_sensor_gma301a.c$(PreprocessSuffix) "g_sensor/g_sensor_gma301a.c"

$(IntermediateDirectory)/g_sensor_g_sensor_null.c$(ObjectSuffix): g_sensor/g_sensor_null.c $(IntermediateDirectory)/g_sensor_g_sensor_null.c$(DependSuffix)
	$(CC) $(SourceSwitch) "E:/work1/DV3251_UNOS_sdk_release_v1.3/release/g_sensor/g_sensor_null.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/g_sensor_g_sensor_null.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/g_sensor_g_sensor_null.c$(DependSuffix): g_sensor/g_sensor_null.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/g_sensor_g_sensor_null.c$(ObjectSuffix) -MF$(IntermediateDirectory)/g_sensor_g_sensor_null.c$(DependSuffix) -MM "g_sensor/g_sensor_null.c"

$(IntermediateDirectory)/g_sensor_g_sensor_null.c$(PreprocessSuffix): g_sensor/g_sensor_null.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/g_sensor_g_sensor_null.c$(PreprocessSuffix) "g_sensor/g_sensor_null.c"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


