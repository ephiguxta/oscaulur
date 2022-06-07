// reiniciando o lcd
void lcd_reset(void);

// initializando a comunicação
void lcd_initialize(void);

// enviando um nibble por vez
void byte_slice(uint8_t data, uint8_t mode);

// escrevendo um caractere no display
void write_char(uint8_t data);

// escrevendo um agrupado de caracteres, vulgo texto
void write_string(uint8_t text[16]);

// habilitando inserção de comando ou dado
void data_or_cmd(uint8_t data, uint8_t mode);

// salta cursor para determinada posição
void cursor_addr(uint8_t addr);
