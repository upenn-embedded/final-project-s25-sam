#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=mkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/SlouchBUSTERRR.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/SlouchBUSTERRR.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../../Downloads/lib/LCD_GFX.c ../../Downloads/lib/ST7735.c ../../Downloads/lib/uart.c ../../Downloads/lib/lsm6ds0.c ../../Downloads/lib/i2c.c ../../Downloads/lib/drv2605.c main.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1843329441/LCD_GFX.o ${OBJECTDIR}/_ext/1843329441/ST7735.o ${OBJECTDIR}/_ext/1843329441/uart.o ${OBJECTDIR}/_ext/1843329441/lsm6ds0.o ${OBJECTDIR}/_ext/1843329441/i2c.o ${OBJECTDIR}/_ext/1843329441/drv2605.o ${OBJECTDIR}/main.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1843329441/LCD_GFX.o.d ${OBJECTDIR}/_ext/1843329441/ST7735.o.d ${OBJECTDIR}/_ext/1843329441/uart.o.d ${OBJECTDIR}/_ext/1843329441/lsm6ds0.o.d ${OBJECTDIR}/_ext/1843329441/i2c.o.d ${OBJECTDIR}/_ext/1843329441/drv2605.o.d ${OBJECTDIR}/main.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1843329441/LCD_GFX.o ${OBJECTDIR}/_ext/1843329441/ST7735.o ${OBJECTDIR}/_ext/1843329441/uart.o ${OBJECTDIR}/_ext/1843329441/lsm6ds0.o ${OBJECTDIR}/_ext/1843329441/i2c.o ${OBJECTDIR}/_ext/1843329441/drv2605.o ${OBJECTDIR}/main.o

# Source Files
SOURCEFILES=../../Downloads/lib/LCD_GFX.c ../../Downloads/lib/ST7735.c ../../Downloads/lib/uart.c ../../Downloads/lib/lsm6ds0.c ../../Downloads/lib/i2c.c ../../Downloads/lib/drv2605.c main.c



CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/SlouchBUSTERRR.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=ATmega328PB
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1843329441/LCD_GFX.o: ../../Downloads/lib/LCD_GFX.c  .generated_files/flags/default/cda3652e8245407dea3de8c19918a41d1a0213e8 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1843329441" 
	@${RM} ${OBJECTDIR}/_ext/1843329441/LCD_GFX.o.d 
	@${RM} ${OBJECTDIR}/_ext/1843329441/LCD_GFX.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -I"../FreeRTOS" -I"../FreeRTOS" -I"../../Downloads/lib" -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/_ext/1843329441/LCD_GFX.o.d" -MT "${OBJECTDIR}/_ext/1843329441/LCD_GFX.o.d" -MT ${OBJECTDIR}/_ext/1843329441/LCD_GFX.o -o ${OBJECTDIR}/_ext/1843329441/LCD_GFX.o ../../Downloads/lib/LCD_GFX.c 
	
${OBJECTDIR}/_ext/1843329441/ST7735.o: ../../Downloads/lib/ST7735.c  .generated_files/flags/default/99dd423432f67fdd73aca836476e217aefb65009 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1843329441" 
	@${RM} ${OBJECTDIR}/_ext/1843329441/ST7735.o.d 
	@${RM} ${OBJECTDIR}/_ext/1843329441/ST7735.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -I"../FreeRTOS" -I"../FreeRTOS" -I"../../Downloads/lib" -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/_ext/1843329441/ST7735.o.d" -MT "${OBJECTDIR}/_ext/1843329441/ST7735.o.d" -MT ${OBJECTDIR}/_ext/1843329441/ST7735.o -o ${OBJECTDIR}/_ext/1843329441/ST7735.o ../../Downloads/lib/ST7735.c 
	
${OBJECTDIR}/_ext/1843329441/uart.o: ../../Downloads/lib/uart.c  .generated_files/flags/default/b0461e209c604ade1130591dd0d2d79370813b0d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1843329441" 
	@${RM} ${OBJECTDIR}/_ext/1843329441/uart.o.d 
	@${RM} ${OBJECTDIR}/_ext/1843329441/uart.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -I"../FreeRTOS" -I"../FreeRTOS" -I"../../Downloads/lib" -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/_ext/1843329441/uart.o.d" -MT "${OBJECTDIR}/_ext/1843329441/uart.o.d" -MT ${OBJECTDIR}/_ext/1843329441/uart.o -o ${OBJECTDIR}/_ext/1843329441/uart.o ../../Downloads/lib/uart.c 
	
${OBJECTDIR}/_ext/1843329441/lsm6ds0.o: ../../Downloads/lib/lsm6ds0.c  .generated_files/flags/default/464d5e5d59ff1238a60565ac6142967d2db5698 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1843329441" 
	@${RM} ${OBJECTDIR}/_ext/1843329441/lsm6ds0.o.d 
	@${RM} ${OBJECTDIR}/_ext/1843329441/lsm6ds0.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -I"../FreeRTOS" -I"../FreeRTOS" -I"../../Downloads/lib" -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/_ext/1843329441/lsm6ds0.o.d" -MT "${OBJECTDIR}/_ext/1843329441/lsm6ds0.o.d" -MT ${OBJECTDIR}/_ext/1843329441/lsm6ds0.o -o ${OBJECTDIR}/_ext/1843329441/lsm6ds0.o ../../Downloads/lib/lsm6ds0.c 
	
${OBJECTDIR}/_ext/1843329441/i2c.o: ../../Downloads/lib/i2c.c  .generated_files/flags/default/b74cb2c902b9eea0cbc6a6380645f558121825f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1843329441" 
	@${RM} ${OBJECTDIR}/_ext/1843329441/i2c.o.d 
	@${RM} ${OBJECTDIR}/_ext/1843329441/i2c.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -I"../FreeRTOS" -I"../FreeRTOS" -I"../../Downloads/lib" -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/_ext/1843329441/i2c.o.d" -MT "${OBJECTDIR}/_ext/1843329441/i2c.o.d" -MT ${OBJECTDIR}/_ext/1843329441/i2c.o -o ${OBJECTDIR}/_ext/1843329441/i2c.o ../../Downloads/lib/i2c.c 
	
${OBJECTDIR}/_ext/1843329441/drv2605.o: ../../Downloads/lib/drv2605.c  .generated_files/flags/default/122748082f3a43cdc008b4d05124ba9b1513de72 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1843329441" 
	@${RM} ${OBJECTDIR}/_ext/1843329441/drv2605.o.d 
	@${RM} ${OBJECTDIR}/_ext/1843329441/drv2605.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -I"../FreeRTOS" -I"../FreeRTOS" -I"../../Downloads/lib" -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/_ext/1843329441/drv2605.o.d" -MT "${OBJECTDIR}/_ext/1843329441/drv2605.o.d" -MT ${OBJECTDIR}/_ext/1843329441/drv2605.o -o ${OBJECTDIR}/_ext/1843329441/drv2605.o ../../Downloads/lib/drv2605.c 
	
${OBJECTDIR}/main.o: main.c  .generated_files/flags/default/3d25e32f978894bad9f949948a54fc2e12e36c3a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -I"../FreeRTOS" -I"../FreeRTOS" -I"../../Downloads/lib" -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/main.o.d" -MT "${OBJECTDIR}/main.o.d" -MT ${OBJECTDIR}/main.o -o ${OBJECTDIR}/main.o main.c 
	
else
${OBJECTDIR}/_ext/1843329441/LCD_GFX.o: ../../Downloads/lib/LCD_GFX.c  .generated_files/flags/default/3660d5d83c10e1fc8ce7cc976078659a0520db19 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1843329441" 
	@${RM} ${OBJECTDIR}/_ext/1843329441/LCD_GFX.o.d 
	@${RM} ${OBJECTDIR}/_ext/1843329441/LCD_GFX.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -I"../FreeRTOS" -I"../FreeRTOS" -I"../../Downloads/lib" -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/_ext/1843329441/LCD_GFX.o.d" -MT "${OBJECTDIR}/_ext/1843329441/LCD_GFX.o.d" -MT ${OBJECTDIR}/_ext/1843329441/LCD_GFX.o -o ${OBJECTDIR}/_ext/1843329441/LCD_GFX.o ../../Downloads/lib/LCD_GFX.c 
	
${OBJECTDIR}/_ext/1843329441/ST7735.o: ../../Downloads/lib/ST7735.c  .generated_files/flags/default/576abd70bc9f896ff787eaca1236e32301b53ade .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1843329441" 
	@${RM} ${OBJECTDIR}/_ext/1843329441/ST7735.o.d 
	@${RM} ${OBJECTDIR}/_ext/1843329441/ST7735.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -I"../FreeRTOS" -I"../FreeRTOS" -I"../../Downloads/lib" -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/_ext/1843329441/ST7735.o.d" -MT "${OBJECTDIR}/_ext/1843329441/ST7735.o.d" -MT ${OBJECTDIR}/_ext/1843329441/ST7735.o -o ${OBJECTDIR}/_ext/1843329441/ST7735.o ../../Downloads/lib/ST7735.c 
	
${OBJECTDIR}/_ext/1843329441/uart.o: ../../Downloads/lib/uart.c  .generated_files/flags/default/fdbd06495874c1b145257399afc77b750ee3b3d2 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1843329441" 
	@${RM} ${OBJECTDIR}/_ext/1843329441/uart.o.d 
	@${RM} ${OBJECTDIR}/_ext/1843329441/uart.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -I"../FreeRTOS" -I"../FreeRTOS" -I"../../Downloads/lib" -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/_ext/1843329441/uart.o.d" -MT "${OBJECTDIR}/_ext/1843329441/uart.o.d" -MT ${OBJECTDIR}/_ext/1843329441/uart.o -o ${OBJECTDIR}/_ext/1843329441/uart.o ../../Downloads/lib/uart.c 
	
${OBJECTDIR}/_ext/1843329441/lsm6ds0.o: ../../Downloads/lib/lsm6ds0.c  .generated_files/flags/default/38cad5d71a9121f5cd29e283839994f118ac2b77 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1843329441" 
	@${RM} ${OBJECTDIR}/_ext/1843329441/lsm6ds0.o.d 
	@${RM} ${OBJECTDIR}/_ext/1843329441/lsm6ds0.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -I"../FreeRTOS" -I"../FreeRTOS" -I"../../Downloads/lib" -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/_ext/1843329441/lsm6ds0.o.d" -MT "${OBJECTDIR}/_ext/1843329441/lsm6ds0.o.d" -MT ${OBJECTDIR}/_ext/1843329441/lsm6ds0.o -o ${OBJECTDIR}/_ext/1843329441/lsm6ds0.o ../../Downloads/lib/lsm6ds0.c 
	
${OBJECTDIR}/_ext/1843329441/i2c.o: ../../Downloads/lib/i2c.c  .generated_files/flags/default/3eab7f0c20acb78923fe85e440ff01f1fdb5011f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1843329441" 
	@${RM} ${OBJECTDIR}/_ext/1843329441/i2c.o.d 
	@${RM} ${OBJECTDIR}/_ext/1843329441/i2c.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -I"../FreeRTOS" -I"../FreeRTOS" -I"../../Downloads/lib" -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/_ext/1843329441/i2c.o.d" -MT "${OBJECTDIR}/_ext/1843329441/i2c.o.d" -MT ${OBJECTDIR}/_ext/1843329441/i2c.o -o ${OBJECTDIR}/_ext/1843329441/i2c.o ../../Downloads/lib/i2c.c 
	
${OBJECTDIR}/_ext/1843329441/drv2605.o: ../../Downloads/lib/drv2605.c  .generated_files/flags/default/523afa459b092f7f6f6359be1795312cbe85d45c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1843329441" 
	@${RM} ${OBJECTDIR}/_ext/1843329441/drv2605.o.d 
	@${RM} ${OBJECTDIR}/_ext/1843329441/drv2605.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -I"../FreeRTOS" -I"../FreeRTOS" -I"../../Downloads/lib" -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/_ext/1843329441/drv2605.o.d" -MT "${OBJECTDIR}/_ext/1843329441/drv2605.o.d" -MT ${OBJECTDIR}/_ext/1843329441/drv2605.o -o ${OBJECTDIR}/_ext/1843329441/drv2605.o ../../Downloads/lib/drv2605.c 
	
${OBJECTDIR}/main.o: main.c  .generated_files/flags/default/130c27c2730399f900a412152aae1491383b4b4a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -I"../FreeRTOS" -I"../FreeRTOS" -I"../../Downloads/lib" -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/main.o.d" -MT "${OBJECTDIR}/main.o.d" -MT ${OBJECTDIR}/main.o -o ${OBJECTDIR}/main.o main.c 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/SlouchBUSTERRR.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -Wl,-Map=${DISTDIR}/SlouchBUSTERRR.X.${IMAGE_TYPE}.map  -D__DEBUG=1  -DXPRJ_default=$(CND_CONF)  -Wl,--defsym=__MPLAB_BUILD=1   -mdfp="${DFP_DIR}/xc8"   -gdwarf-2 -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -I"../FreeRTOS" -I"../FreeRTOS" -I"../../Downloads/lib" -Wall -gdwarf-3 -mno-const-data-in-progmem     $(COMPARISON_BUILD) -Wl,--memorysummary,${DISTDIR}/memoryfile.xml -o ${DISTDIR}/SlouchBUSTERRR.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  -o ${DISTDIR}/SlouchBUSTERRR.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -Wl,--start-group  -Wl,-lm -Wl,--end-group  -Wl,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1
	@${RM} ${DISTDIR}/SlouchBUSTERRR.X.${IMAGE_TYPE}.hex 
	
	
else
${DISTDIR}/SlouchBUSTERRR.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -Wl,-Map=${DISTDIR}/SlouchBUSTERRR.X.${IMAGE_TYPE}.map  -DXPRJ_default=$(CND_CONF)  -Wl,--defsym=__MPLAB_BUILD=1   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -I"../FreeRTOS" -I"../FreeRTOS" -I"../../Downloads/lib" -Wall -gdwarf-3 -mno-const-data-in-progmem     $(COMPARISON_BUILD) -Wl,--memorysummary,${DISTDIR}/memoryfile.xml -o ${DISTDIR}/SlouchBUSTERRR.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  -o ${DISTDIR}/SlouchBUSTERRR.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -Wl,--start-group  -Wl,-lm -Wl,--end-group 
	${MP_CC_DIR}/avr-objcopy -O ihex "${DISTDIR}/SlouchBUSTERRR.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}" "${DISTDIR}/SlouchBUSTERRR.X.${IMAGE_TYPE}.hex"
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${OBJECTDIR}
	${RM} -r ${DISTDIR}

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(wildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
