#include "preferences.h"

#include <stdint.h>
#include <string.h>
#include <sdk/os/file.h>
#include <sdk/os/debug.h>
#include "../helpers/fileio.h"
#include "../helpers/ini.h"
#include "../helpers/functions.h"
#include "../helpers/macros.h"
#include "error.h"
#include "emulator.h"

#define CONFIG_VAR_CONSTANT             "C_"

#define CONFIG_INI_SECTION_NAME         "Cfg"
#define CONFIG_INI_INTERLACE_ENABLE_KEY "interl_en"
#define CONFIG_INI_FRAMESKIP_ENABLE_KEY "fs_en"
#define CONFIG_INI_FRAMESKIP_AMOUNT_KEY "fs_am"
#define CONFIG_INI_EMU_SPEED_KEY        "emu_spd"
#define CONFIG_INI_OVERCLOCK_ENABLE_KEY "oclk_en"
#define CONFIG_INI_SELECTED_PALETTE_KEY "sel_pal"

char *get_rom_config_var_name(emu_preferences *preferences, char *name_buffer)
{
  char *str = preferences->current_rom_name;

  // Check if this rom has a name
  if (strcmp(preferences->current_rom_name, "") == 0) 
  {
    str = preferences->current_filename;
  } 

	strcpy(name_buffer, CONFIG_VAR_CONSTANT);
  itoa_leading_zeros(
    hash_string(str, 0xFFFFFF), 
    name_buffer + (sizeof(CONFIG_VAR_CONSTANT) - 1),
    16,
    6
  );

  return name_buffer;
}

struct gb_s *set_config_defaults(struct gb_s *gb)
{
  emu_preferences *prefs = (emu_preferences *)(gb->direct.priv);
  
  set_interlacing(gb, DEFAULT_INTERLACE_ENABLE);
  set_frameskip(gb, DEFAULT_FRAMESKIP_ENABLE, DEFAULT_FRAMESKIP_AMOUNT);
  set_emu_speed(gb, DEFAULT_EMU_SPEED);
  set_overclock(gb, DEFAULT_OVERCLOCK_ENABLE);

  prefs->config.selected_palette = DEFAULT_SELECTED_PALETTE;

  return gb;
}

uint8_t process_config_ini(char *ini_string, uint32_t len, struct gb_s *gb)
{
  emu_preferences *prefs = (emu_preferences *)(gb->direct.priv);

  ini_file file;
  ini_parse(ini_string, len, &file);

  ini_section *section = find_section(&file, CONFIG_INI_SECTION_NAME);

  if (!section)
  {
    free_ini_file(&file);
    return 1;
  }

  ini_key *interl_en = find_key(section, CONFIG_INI_INTERLACE_ENABLE_KEY);
  ini_key *fs_en = find_key(section, CONFIG_INI_FRAMESKIP_ENABLE_KEY);
  ini_key *fs_amount = find_key(section, CONFIG_INI_FRAMESKIP_AMOUNT_KEY);
  ini_key *emu_speed = find_key(section, CONFIG_INI_EMU_SPEED_KEY);
  ini_key *oclk_en = find_key(section, CONFIG_INI_OVERCLOCK_ENABLE_KEY);
  ini_key *sel_pal = find_key(section, CONFIG_INI_SELECTED_PALETTE_KEY);

  if (fs_en && fs_amount)
  {
    set_frameskip(gb, fs_en->value_int, fs_amount->value_int);
  }

  if (interl_en)
  {
    set_interlacing(gb, interl_en->value_int);
  }

  if (emu_speed)
  {
    set_emu_speed(gb, emu_speed->value_int);
  }

  if (oclk_en)
  {
    set_overclock(gb, oclk_en->value_int);
  }

  if (sel_pal)
  {
    prefs->config.selected_palette = sel_pal->value_int;
  }

  free_ini_file(&file);
  
  return 0;
}

char *create_config_ini(rom_config *config, char *ini_string, uint32_t len)
{
  ini_file file;
  file.section_count = 0;
  file.sections_size = 0;
  file.sections = nullptr;

  ini_section *config_section = add_section(&file, CONFIG_INI_SECTION_NAME);
  
  if (!config_section)
  {
    free_ini_file(&file);
    return nullptr;
  }
  
  if (!add_key(
    config_section, 
    CONFIG_INI_INTERLACE_ENABLE_KEY,
    INI_TYPE_INT,
    config->interlacing_enabled
  )) 
  {
    free_ini_file(&file);
    return nullptr;
  }
  
  if (!add_key(
    config_section, 
    CONFIG_INI_FRAMESKIP_ENABLE_KEY,
    INI_TYPE_INT,
    config->frameskip_enabled
  )) 
  {
    free_ini_file(&file);
    return nullptr;
  }
  
  if (!add_key(
    config_section, 
    CONFIG_INI_FRAMESKIP_AMOUNT_KEY,
    INI_TYPE_INT,
    config->frameskip_amount
  )) 
  {
    free_ini_file(&file);
    return nullptr;
  }

  if (!add_key(
    config_section, 
    CONFIG_INI_EMU_SPEED_KEY,
    INI_TYPE_INT,
    config->emulation_speed
  )) 
  {
    free_ini_file(&file);
    return nullptr;
  }

  if (!add_key(
    config_section, 
    CONFIG_INI_OVERCLOCK_ENABLE_KEY,
    INI_TYPE_INT,
    config->overclock_enabled
  )) 
  {
    free_ini_file(&file);
    return nullptr;
  }
  
  if (!add_key(
    config_section, 
    CONFIG_INI_SELECTED_PALETTE_KEY,
    INI_TYPE_INT,
    config->selected_palette
  )) 
  {
    free_ini_file(&file);
    return nullptr;
  }

  ini_write(&file, ini_string, len);
  free_ini_file(&file);

  return ini_string;
}

uint8_t load_rom_config(struct gb_s *gb)
{
  emu_preferences *preferences = (emu_preferences *)(gb->direct.priv);

  uint32_t size;
  char *ini_string;
  char var_name[MAX_FILENAME_LEN];

	get_rom_config_var_name(preferences, var_name);
  set_config_defaults(gb);

  if (read_mcs(MCS_DIRECTORY, var_name, (void **)&ini_string, &size) == 0)
  {
    if (process_config_ini(ini_string, size, gb) == 0)
    {
      return 0;
    }
  }

  // Restore defaults if read failed
  set_config_defaults(gb);
  return 1;
}

uint8_t save_rom_config(struct gb_s *gb)
{
  emu_preferences *preferences = (emu_preferences *)(gb->direct.priv);

  char var_name[MAX_FILENAME_LEN];
  char ini_string[INI_MAX_CONTENT_LEN];

  get_rom_config_var_name(preferences, var_name);
  
  if (!create_config_ini(&(preferences->config), ini_string, INI_MAX_CONTENT_LEN)) 
  {
    return 1;
  }

  uint32_t size = align_val(strlen(ini_string), 4);

  return write_mcs(MCS_DIRECTORY, var_name, ini_string, size);
}
