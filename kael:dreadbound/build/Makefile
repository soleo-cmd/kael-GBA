DEVKITARM = /opt/devkitpro/devkitARM
CC = $(DEVKITARM)/bin/arm-none-eabi-gcc
LD = $(DEVKITARM)/bin/arm-none-eabi-ld
OBJCOPY = $(DEVKITARM)/bin/arm-none-eabi-objcopy
TARGET = KaelGame
SOURCES = ../src/main.c
OBJECTS = $(SOURCES:.c=.o)
CFLAGS = -mthumb -mthumb-interwork -Wall -O2 -I$(DEVKITARM)/arm-none-eabi/include -I/opt/devkitpro/libgba/include
LDFLAGS = -mthumb -mthumb-interwork
all: $(TARGET).gba
$(TARGET).gba: $(TARGET).elf
	$(OBJCOPY) -O binary $< $@
$(TARGET).elf: $(OBJECTS)
	$(LD) $(LDFLAGS) -o $@ $^ -L/opt/devkitpro/libgba/lib -lgba
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f $(OBJECTS) $(TARGET).elf $(TARGET).gba
	