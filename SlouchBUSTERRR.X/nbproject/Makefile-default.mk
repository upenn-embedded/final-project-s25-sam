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
SOURCEFILES_QUOTED_IF_SPACED=uart.c ../FreeRTOS/croutine.c ../FreeRTOS/event_groups.c ../FreeRTOS/heap_3.c ../FreeRTOS/hooks.c ../FreeRTOS/library.c ../FreeRTOS/list.c ../FreeRTOS/port.c ../FreeRTOS/queue.c ../FreeRTOS/stream_buffer.c ../FreeRTOS/tasks.c ../FreeRTOS/timers.c main.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/uart.o ${OBJECTDIR}/_ext/2029861983/croutine.o ${OBJECTDIR}/_ext/2029861983/event_groups.o ${OBJECTDIR}/_ext/2029861983/heap_3.o ${OBJECTDIR}/_ext/2029861983/hooks.o ${OBJECTDIR}/_ext/2029861983/library.o ${OBJECTDIR}/_ext/2029861983/list.o ${OBJECTDIR}/_ext/2029861983/port.o ${OBJECTDIR}/_ext/2029861983/queue.o ${OBJECTDIR}/_ext/2029861983/stream_buffer.o ${OBJECTDIR}/_ext/2029861983/tasks.o ${OBJECTDIR}/_ext/2029861983/timers.o ${OBJECTDIR}/main.o
POSSIBLE_DEPFILES=${OBJECTDIR}/uart.o.d ${OBJECTDIR}/_ext/2029861983/croutine.o.d ${OBJECTDIR}/_ext/2029861983/event_groups.o.d ${OBJECTDIR}/_ext/2029861983/heap_3.o.d ${OBJECTDIR}/_ext/2029861983/hooks.o.d ${OBJECTDIR}/_ext/2029861983/library.o.d ${OBJECTDIR}/_ext/2029861983/list.o.d ${OBJECTDIR}/_ext/2029861983/port.o.d ${OBJECTDIR}/_ext/2029861983/queue.o.d ${OBJECTDIR}/_ext/2029861983/stream_buffer.o.d ${OBJECTDIR}/_ext/2029861983/tasks.o.d ${OBJECTDIR}/_ext/2029861983/timers.o.d ${OBJECTDIR}/main.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/uart.o ${OBJECTDIR}/_ext/2029861983/croutine.o ${OBJECTDIR}/_ext/2029861983/event_groups.o ${OBJECTDIR}/_ext/2029861983/heap_3.o ${OBJECTDIR}/_ext/2029861983/hooks.o ${OBJECTDIR}/_ext/2029861983/library.o ${OBJECTDIR}/_ext/2029861983/list.o ${OBJECTDIR}/_ext/2029861983/port.o ${OBJECTDIR}/_ext/2029861983/queue.o ${OBJECTDIR}/_ext/2029861983/stream_buffer.o ${OBJECTDIR}/_ext/2029861983/tasks.o ${OBJECTDIR}/_ext/2029861983/timers.o ${OBJECTDIR}/main.o

# Source Files
SOURCEFILES=uart.c ../FreeRTOS/croutine.c ../FreeRTOS/event_groups.c ../FreeRTOS/heap_3.c ../FreeRTOS/hooks.c ../FreeRTOS/library.c ../FreeRTOS/list.c ../FreeRTOS/port.c ../FreeRTOS/queue.c ../FreeRTOS/stream_buffer.c ../FreeRTOS/tasks.c ../FreeRTOS/timers.c main.c



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
${OBJECTDIR}/uart.o: uart.c  .generated_files/flags/default/d818ac5c1ba5198babf7503b5bda72f424b859d2 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/uart.o.d 
	@${RM} ${OBJECTDIR}/uart.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -I"../FreeRTOS" -I"../FreeRTOS" -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/uart.o.d" -MT "${OBJECTDIR}/uart.o.d" -MT ${OBJECTDIR}/uart.o -o ${OBJECTDIR}/uart.o uart.c 
	
${OBJECTDIR}/_ext/2029861983/croutine.o: ../FreeRTOS/croutine.c  .generated_files/flags/default/51b2055fd65b7fdcdb3de5152db5feca009b009a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/2029861983" 
	@${RM} ${OBJECTDIR}/_ext/2029861983/croutine.o.d 
	@${RM} ${OBJECTDIR}/_ext/2029861983/croutine.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -I"../FreeRTOS" -I"../FreeRTOS" -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/_ext/2029861983/croutine.o.d" -MT "${OBJECTDIR}/_ext/2029861983/croutine.o.d" -MT ${OBJECTDIR}/_ext/2029861983/croutine.o -o ${OBJECTDIR}/_ext/2029861983/croutine.o ../FreeRTOS/croutine.c 
	
${OBJECTDIR}/_ext/2029861983/event_groups.o: ../FreeRTOS/event_groups.c  .generated_files/flags/default/d799bc76cdaa144e673687e671c0199a45b7f6bc .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/2029861983" 
	@${RM} ${OBJECTDIR}/_ext/2029861983/event_groups.o.d 
	@${RM} ${OBJECTDIR}/_ext/2029861983/event_groups.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -I"../FreeRTOS" -I"../FreeRTOS" -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/_ext/2029861983/event_groups.o.d" -MT "${OBJECTDIR}/_ext/2029861983/event_groups.o.d" -MT ${OBJECTDIR}/_ext/2029861983/event_groups.o -o ${OBJECTDIR}/_ext/2029861983/event_groups.o ../FreeRTOS/event_groups.c 
	
${OBJECTDIR}/_ext/2029861983/heap_3.o: ../FreeRTOS/heap_3.c  .generated_files/flags/default/97ca1e7e9bfe14b61de831f9ed0d15494f24546f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/2029861983" 
	@${RM} ${OBJECTDIR}/_ext/2029861983/heap_3.o.d 
	@${RM} ${OBJECTDIR}/_ext/2029861983/heap_3.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -I"../FreeRTOS" -I"../FreeRTOS" -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/_ext/2029861983/heap_3.o.d" -MT "${OBJECTDIR}/_ext/2029861983/heap_3.o.d" -MT ${OBJECTDIR}/_ext/2029861983/heap_3.o -o ${OBJECTDIR}/_ext/2029861983/heap_3.o ../FreeRTOS/heap_3.c 
	
${OBJECTDIR}/_ext/2029861983/hooks.o: ../FreeRTOS/hooks.c  .generated_files/flags/default/5aa9c037f6fd7b9b7cbf8c4cb2b7583f059d2df2 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/2029861983" 
	@${RM} ${OBJECTDIR}/_ext/2029861983/hooks.o.d 
	@${RM} ${OBJECTDIR}/_ext/2029861983/hooks.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -I"../FreeRTOS" -I"../FreeRTOS" -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/_ext/2029861983/hooks.o.d" -MT "${OBJECTDIR}/_ext/2029861983/hooks.o.d" -MT ${OBJECTDIR}/_ext/2029861983/hooks.o -o ${OBJECTDIR}/_ext/2029861983/hooks.o ../FreeRTOS/hooks.c 
	
${OBJECTDIR}/_ext/2029861983/library.o: ../FreeRTOS/library.c  .generated_files/flags/default/4d8fe4958bf727add6ce7d22268d3366f1bb43f1 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/2029861983" 
	@${RM} ${OBJECTDIR}/_ext/2029861983/library.o.d 
	@${RM} ${OBJECTDIR}/_ext/2029861983/library.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -I"../FreeRTOS" -I"../FreeRTOS" -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/_ext/2029861983/library.o.d" -MT "${OBJECTDIR}/_ext/2029861983/library.o.d" -MT ${OBJECTDIR}/_ext/2029861983/library.o -o ${OBJECTDIR}/_ext/2029861983/library.o ../FreeRTOS/library.c 
	
${OBJECTDIR}/_ext/2029861983/list.o: ../FreeRTOS/list.c  .generated_files/flags/default/15c0bca30cfd86cecfae78da00307d4ad66d55b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/2029861983" 
	@${RM} ${OBJECTDIR}/_ext/2029861983/list.o.d 
	@${RM} ${OBJECTDIR}/_ext/2029861983/list.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -I"../FreeRTOS" -I"../FreeRTOS" -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/_ext/2029861983/list.o.d" -MT "${OBJECTDIR}/_ext/2029861983/list.o.d" -MT ${OBJECTDIR}/_ext/2029861983/list.o -o ${OBJECTDIR}/_ext/2029861983/list.o ../FreeRTOS/list.c 
	
${OBJECTDIR}/_ext/2029861983/port.o: ../FreeRTOS/port.c  .generated_files/flags/default/9979ecdaea150cee4636cc3f06e28731b6c02345 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/2029861983" 
	@${RM} ${OBJECTDIR}/_ext/2029861983/port.o.d 
	@${RM} ${OBJECTDIR}/_ext/2029861983/port.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -I"../FreeRTOS" -I"../FreeRTOS" -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/_ext/2029861983/port.o.d" -MT "${OBJECTDIR}/_ext/2029861983/port.o.d" -MT ${OBJECTDIR}/_ext/2029861983/port.o -o ${OBJECTDIR}/_ext/2029861983/port.o ../FreeRTOS/port.c 
	
${OBJECTDIR}/_ext/2029861983/queue.o: ../FreeRTOS/queue.c  .generated_files/flags/default/cc9c67055323ea52a710416497c5aa56449e9b82 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/2029861983" 
	@${RM} ${OBJECTDIR}/_ext/2029861983/queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/2029861983/queue.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -I"../FreeRTOS" -I"../FreeRTOS" -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/_ext/2029861983/queue.o.d" -MT "${OBJECTDIR}/_ext/2029861983/queue.o.d" -MT ${OBJECTDIR}/_ext/2029861983/queue.o -o ${OBJECTDIR}/_ext/2029861983/queue.o ../FreeRTOS/queue.c 
	
${OBJECTDIR}/_ext/2029861983/stream_buffer.o: ../FreeRTOS/stream_buffer.c  .generated_files/flags/default/f53caec56da88867b638fb6077544a119bad3dd6 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/2029861983" 
	@${RM} ${OBJECTDIR}/_ext/2029861983/stream_buffer.o.d 
	@${RM} ${OBJECTDIR}/_ext/2029861983/stream_buffer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -I"../FreeRTOS" -I"../FreeRTOS" -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/_ext/2029861983/stream_buffer.o.d" -MT "${OBJECTDIR}/_ext/2029861983/stream_buffer.o.d" -MT ${OBJECTDIR}/_ext/2029861983/stream_buffer.o -o ${OBJECTDIR}/_ext/2029861983/stream_buffer.o ../FreeRTOS/stream_buffer.c 
	
${OBJECTDIR}/_ext/2029861983/tasks.o: ../FreeRTOS/tasks.c  .generated_files/flags/default/39ad72e86d3d550940a83cc889449fdc46975f35 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/2029861983" 
	@${RM} ${OBJECTDIR}/_ext/2029861983/tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/2029861983/tasks.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -I"../FreeRTOS" -I"../FreeRTOS" -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/_ext/2029861983/tasks.o.d" -MT "${OBJECTDIR}/_ext/2029861983/tasks.o.d" -MT ${OBJECTDIR}/_ext/2029861983/tasks.o -o ${OBJECTDIR}/_ext/2029861983/tasks.o ../FreeRTOS/tasks.c 
	
${OBJECTDIR}/_ext/2029861983/timers.o: ../FreeRTOS/timers.c  .generated_files/flags/default/e3a05396c800c6f9299a701ac2bc736346ee8dff .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/2029861983" 
	@${RM} ${OBJECTDIR}/_ext/2029861983/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/2029861983/timers.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -I"../FreeRTOS" -I"../FreeRTOS" -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/_ext/2029861983/timers.o.d" -MT "${OBJECTDIR}/_ext/2029861983/timers.o.d" -MT ${OBJECTDIR}/_ext/2029861983/timers.o -o ${OBJECTDIR}/_ext/2029861983/timers.o ../FreeRTOS/timers.c 
	
${OBJECTDIR}/main.o: main.c  .generated_files/flags/default/4a5a87ebbbc9d2f51bde9983d8770e65bebdda3f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -I"../FreeRTOS" -I"../FreeRTOS" -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/main.o.d" -MT "${OBJECTDIR}/main.o.d" -MT ${OBJECTDIR}/main.o -o ${OBJECTDIR}/main.o main.c 
	
else
${OBJECTDIR}/uart.o: uart.c  .generated_files/flags/default/a826f1996111a5c0136651ac5d44fec515b2c03a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/uart.o.d 
	@${RM} ${OBJECTDIR}/uart.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -I"../FreeRTOS" -I"../FreeRTOS" -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/uart.o.d" -MT "${OBJECTDIR}/uart.o.d" -MT ${OBJECTDIR}/uart.o -o ${OBJECTDIR}/uart.o uart.c 
	
${OBJECTDIR}/_ext/2029861983/croutine.o: ../FreeRTOS/croutine.c  .generated_files/flags/default/1f85e3d4e63318f6fe70c408da94e2179317c794 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/2029861983" 
	@${RM} ${OBJECTDIR}/_ext/2029861983/croutine.o.d 
	@${RM} ${OBJECTDIR}/_ext/2029861983/croutine.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -I"../FreeRTOS" -I"../FreeRTOS" -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/_ext/2029861983/croutine.o.d" -MT "${OBJECTDIR}/_ext/2029861983/croutine.o.d" -MT ${OBJECTDIR}/_ext/2029861983/croutine.o -o ${OBJECTDIR}/_ext/2029861983/croutine.o ../FreeRTOS/croutine.c 
	
${OBJECTDIR}/_ext/2029861983/event_groups.o: ../FreeRTOS/event_groups.c  .generated_files/flags/default/fe169c13104798fa3f1129c9425eb3e2235eab1e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/2029861983" 
	@${RM} ${OBJECTDIR}/_ext/2029861983/event_groups.o.d 
	@${RM} ${OBJECTDIR}/_ext/2029861983/event_groups.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -I"../FreeRTOS" -I"../FreeRTOS" -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/_ext/2029861983/event_groups.o.d" -MT "${OBJECTDIR}/_ext/2029861983/event_groups.o.d" -MT ${OBJECTDIR}/_ext/2029861983/event_groups.o -o ${OBJECTDIR}/_ext/2029861983/event_groups.o ../FreeRTOS/event_groups.c 
	
${OBJECTDIR}/_ext/2029861983/heap_3.o: ../FreeRTOS/heap_3.c  .generated_files/flags/default/1b034c468c65d3469c1132a509c04307271b6310 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/2029861983" 
	@${RM} ${OBJECTDIR}/_ext/2029861983/heap_3.o.d 
	@${RM} ${OBJECTDIR}/_ext/2029861983/heap_3.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -I"../FreeRTOS" -I"../FreeRTOS" -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/_ext/2029861983/heap_3.o.d" -MT "${OBJECTDIR}/_ext/2029861983/heap_3.o.d" -MT ${OBJECTDIR}/_ext/2029861983/heap_3.o -o ${OBJECTDIR}/_ext/2029861983/heap_3.o ../FreeRTOS/heap_3.c 
	
${OBJECTDIR}/_ext/2029861983/hooks.o: ../FreeRTOS/hooks.c  .generated_files/flags/default/9e79e9c8721d67f2b93732259dc45d9243d31c3a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/2029861983" 
	@${RM} ${OBJECTDIR}/_ext/2029861983/hooks.o.d 
	@${RM} ${OBJECTDIR}/_ext/2029861983/hooks.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -I"../FreeRTOS" -I"../FreeRTOS" -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/_ext/2029861983/hooks.o.d" -MT "${OBJECTDIR}/_ext/2029861983/hooks.o.d" -MT ${OBJECTDIR}/_ext/2029861983/hooks.o -o ${OBJECTDIR}/_ext/2029861983/hooks.o ../FreeRTOS/hooks.c 
	
${OBJECTDIR}/_ext/2029861983/library.o: ../FreeRTOS/library.c  .generated_files/flags/default/c76173d39f3f593dd44e6fb97930577698cece2a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/2029861983" 
	@${RM} ${OBJECTDIR}/_ext/2029861983/library.o.d 
	@${RM} ${OBJECTDIR}/_ext/2029861983/library.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -I"../FreeRTOS" -I"../FreeRTOS" -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/_ext/2029861983/library.o.d" -MT "${OBJECTDIR}/_ext/2029861983/library.o.d" -MT ${OBJECTDIR}/_ext/2029861983/library.o -o ${OBJECTDIR}/_ext/2029861983/library.o ../FreeRTOS/library.c 
	
${OBJECTDIR}/_ext/2029861983/list.o: ../FreeRTOS/list.c  .generated_files/flags/default/a435291c38959c0e8abc1e281be54ff70a9ea06c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/2029861983" 
	@${RM} ${OBJECTDIR}/_ext/2029861983/list.o.d 
	@${RM} ${OBJECTDIR}/_ext/2029861983/list.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -I"../FreeRTOS" -I"../FreeRTOS" -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/_ext/2029861983/list.o.d" -MT "${OBJECTDIR}/_ext/2029861983/list.o.d" -MT ${OBJECTDIR}/_ext/2029861983/list.o -o ${OBJECTDIR}/_ext/2029861983/list.o ../FreeRTOS/list.c 
	
${OBJECTDIR}/_ext/2029861983/port.o: ../FreeRTOS/port.c  .generated_files/flags/default/fc36ca3679d39b5e24a7d3731dbde8bc75a62476 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/2029861983" 
	@${RM} ${OBJECTDIR}/_ext/2029861983/port.o.d 
	@${RM} ${OBJECTDIR}/_ext/2029861983/port.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -I"../FreeRTOS" -I"../FreeRTOS" -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/_ext/2029861983/port.o.d" -MT "${OBJECTDIR}/_ext/2029861983/port.o.d" -MT ${OBJECTDIR}/_ext/2029861983/port.o -o ${OBJECTDIR}/_ext/2029861983/port.o ../FreeRTOS/port.c 
	
${OBJECTDIR}/_ext/2029861983/queue.o: ../FreeRTOS/queue.c  .generated_files/flags/default/5c708b29805d575a434b23b2a5e2b7ce6b70693d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/2029861983" 
	@${RM} ${OBJECTDIR}/_ext/2029861983/queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/2029861983/queue.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -I"../FreeRTOS" -I"../FreeRTOS" -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/_ext/2029861983/queue.o.d" -MT "${OBJECTDIR}/_ext/2029861983/queue.o.d" -MT ${OBJECTDIR}/_ext/2029861983/queue.o -o ${OBJECTDIR}/_ext/2029861983/queue.o ../FreeRTOS/queue.c 
	
${OBJECTDIR}/_ext/2029861983/stream_buffer.o: ../FreeRTOS/stream_buffer.c  .generated_files/flags/default/5e636b94f2a97168c7e9fb698a4476291d3acd9b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/2029861983" 
	@${RM} ${OBJECTDIR}/_ext/2029861983/stream_buffer.o.d 
	@${RM} ${OBJECTDIR}/_ext/2029861983/stream_buffer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -I"../FreeRTOS" -I"../FreeRTOS" -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/_ext/2029861983/stream_buffer.o.d" -MT "${OBJECTDIR}/_ext/2029861983/stream_buffer.o.d" -MT ${OBJECTDIR}/_ext/2029861983/stream_buffer.o -o ${OBJECTDIR}/_ext/2029861983/stream_buffer.o ../FreeRTOS/stream_buffer.c 
	
${OBJECTDIR}/_ext/2029861983/tasks.o: ../FreeRTOS/tasks.c  .generated_files/flags/default/2b5c3be891ec80ecc3bd7447200377a957d864ef .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/2029861983" 
	@${RM} ${OBJECTDIR}/_ext/2029861983/tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/2029861983/tasks.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -I"../FreeRTOS" -I"../FreeRTOS" -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/_ext/2029861983/tasks.o.d" -MT "${OBJECTDIR}/_ext/2029861983/tasks.o.d" -MT ${OBJECTDIR}/_ext/2029861983/tasks.o -o ${OBJECTDIR}/_ext/2029861983/tasks.o ../FreeRTOS/tasks.c 
	
${OBJECTDIR}/_ext/2029861983/timers.o: ../FreeRTOS/timers.c  .generated_files/flags/default/8e5895fe13466cd7fe9aa357fdc1d733fd4d3eba .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/2029861983" 
	@${RM} ${OBJECTDIR}/_ext/2029861983/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/2029861983/timers.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -I"../FreeRTOS" -I"../FreeRTOS" -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/_ext/2029861983/timers.o.d" -MT "${OBJECTDIR}/_ext/2029861983/timers.o.d" -MT ${OBJECTDIR}/_ext/2029861983/timers.o -o ${OBJECTDIR}/_ext/2029861983/timers.o ../FreeRTOS/timers.c 
	
${OBJECTDIR}/main.o: main.c  .generated_files/flags/default/909a547037bba7aa46385f70f4c4f2754665fd02 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -I"../FreeRTOS" -I"../FreeRTOS" -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/main.o.d" -MT "${OBJECTDIR}/main.o.d" -MT ${OBJECTDIR}/main.o -o ${OBJECTDIR}/main.o main.c 
	
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
	${MP_CC} $(MP_EXTRA_LD_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -Wl,-Map=${DISTDIR}/SlouchBUSTERRR.X.${IMAGE_TYPE}.map  -D__DEBUG=1  -DXPRJ_default=$(CND_CONF)  -Wl,--defsym=__MPLAB_BUILD=1   -mdfp="${DFP_DIR}/xc8"   -gdwarf-2 -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -I"../FreeRTOS" -I"../FreeRTOS" -Wall -gdwarf-3 -mno-const-data-in-progmem     $(COMPARISON_BUILD) -Wl,--memorysummary,${DISTDIR}/memoryfile.xml -o ${DISTDIR}/SlouchBUSTERRR.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  -o ${DISTDIR}/SlouchBUSTERRR.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -Wl,--start-group  -Wl,-lm -Wl,--end-group  -Wl,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1
	@${RM} ${DISTDIR}/SlouchBUSTERRR.X.${IMAGE_TYPE}.hex 
	
	
else
${DISTDIR}/SlouchBUSTERRR.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -Wl,-Map=${DISTDIR}/SlouchBUSTERRR.X.${IMAGE_TYPE}.map  -DXPRJ_default=$(CND_CONF)  -Wl,--defsym=__MPLAB_BUILD=1   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -I"../FreeRTOS" -I"../FreeRTOS" -Wall -gdwarf-3 -mno-const-data-in-progmem     $(COMPARISON_BUILD) -Wl,--memorysummary,${DISTDIR}/memoryfile.xml -o ${DISTDIR}/SlouchBUSTERRR.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  -o ${DISTDIR}/SlouchBUSTERRR.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -Wl,--start-group  -Wl,-lm -Wl,--end-group 
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
