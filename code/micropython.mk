
USERMODULES_DIR := $(USERMOD_DIR)

# Add all C files to SRC_USERMOD.
SRC_USERMOD += $(USERMODULES_DIR)/ufont_rectangle.c
SRC_USERMOD += $(USERMODULES_DIR)/ufont_seven_segment.c
SRC_USERMOD += $(USERMODULES_DIR)/ufont_renderer.c
SRC_USERMOD += $(USERMODULES_DIR)/ufont.c
CFLAGS_USERMOD += -I$(USERMODULES_DIR)