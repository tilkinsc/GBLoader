
#include <stdlib.h>
#include <stdio.h>

#include <stdint.h>
#include <stddef.h>

#include <assert.h>


uint8_t* memory_map = 0;
size_t memory_map_length = 	0;

static inline void* mmu_fetch(uint16_t address) {
	assert(address >= memory_map_length);
	return memory_map + address;
}

static inline void mmu_set(uint16_t address, uint8_t data) {
	assert(address >= memory_map_length);
	memory_map[address] = data;
}

static inline uint16_t* mmu_translate(uint16_t address) {
	assert(address >= memory_map_length);
	return memory_map + address;
}



uint16_t AF = 0;
uint16_t BC = 0;
uint16_t DE = 0;
uint16_t HL = 0;

uint16_t* reg_AF = &AF;
uint8_t* reg_A = (uint8_t*) &AF;
uint8_t* reg_F = ((uint8_t*) &AF) + 1;

uint16_t* reg_BC = &BC;
uint8_t* reg_B = (uint8_t*) &BC;
uint8_t* reg_C = ((uint8_t*) &BC) + 1;

uint16_t* reg_DE = &DE;
uint8_t* reg_D = (uint8_t*) &DE;
uint8_t* reg_E = ((uint8_t*) &DE) + 1;

uint16_t* reg_HL = &HL;
uint8_t* reg_H = (uint8_t*) &HL;
uint8_t* reg_L = ((uint8_t*) &HL) + 1;

uint16_t SP;
uint16_t* reg_SP;

uint16_t PC;
uint16_t* reg_PC;



typedef struct tag_bin_file {
	uint16_t addr_rest_00;
	uint16_t addr_rest_08;
	uint16_t addr_rest_10;
	uint16_t addr_rest_18;
	uint16_t addr_rest_20;
	uint16_t addr_rest_28;
	uint16_t addr_rest_30;
	uint16_t addr_rest_38;
	uint16_t intr_vblank;
	uint16_t intr_lcdc;
	uint16_t intr_timer;
	uint16_t intr_serial;
	uint16_t intr_htl_p10p13;
	uint32_t text_code_execution;
	uint8_t* data_nintendo_gfx;
	uint8_t* title;
	uint8_t* manufacturer_code;
	uint8_t flag_cgb; //TODO: enum
	uint16_t data_license;
	uint8_t flag_sgb;
	uint8_t flag_cart;
	uint8_t flag_romsize;
	uint8_t flag_ramsize;
	uint8_t flag_region;
	uint8_t data_license_ext;
	uint8_t data_rom_version;
	uint8_t data_header_check;
	uint16_t data_checksum;
} bin_file;



int main(int argc, char** argv)
{
	
	FILE* fp = 0;
	fp = fopen("Asteroids.gb", "rb");
	fseek(fp, 0, SEEK_END);
	long len = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	
	printf("Got length:\t\t`%li`\n", len);
	
	
	memory_map = malloc(len * sizeof(char));
	fread(memory_map, 1, len, fp);
	fclose(fp);
	
	bin_file* bfile = calloc(1, sizeof(bin_file));
	bfile->text_code_execution = *(memory_map + 0x100);
	bfile->data_nintendo_gfx = (uint8_t*) (memory_map + 0x104);
	bfile->title = (uint8_t*) (memory_map + 0x134);
	bfile->manufacturer_code = (uint8_t*) (memory_map + 0x13F);
	bfile->flag_cgb = *(memory_map + 0x143);
	bfile->data_license = *(memory_map + 0x144);
	bfile->flag_sgb = *(memory_map + 0x146);
	bfile->flag_cart = *(memory_map + 0x147);
	bfile->flag_romsize = *(memory_map + 0x148);
	bfile->flag_ramsize = *(memory_map + 0x149);
	bfile->flag_region = *(memory_map + 0x14A);
	bfile->data_license_ext = *(memory_map + 0x14B);
	bfile->data_rom_version = *(memory_map + 0x14C);
	bfile->data_header_check = *(memory_map + 0x14D);
	bfile->data_checksum = *(memory_map + 0x14E) << 8 | *(memory_map + 0x14F);
	
	printf("text_code_execution:\t%d\n", bfile->text_code_execution);
	printf("data_nintendo_gfx:\t0x%x%x\n", bfile->data_nintendo_gfx[0], bfile->data_nintendo_gfx[1]);
	printf("title:\t\t\t%s\n", bfile->title);
	printf("manufacturer_code: %c%c%c%c %d %d %d %d\n", bfile->manufacturer_code[0], bfile->manufacturer_code[1], bfile->manufacturer_code[2], bfile->manufacturer_code[3], bfile->manufacturer_code[0], bfile->manufacturer_code[1], bfile->manufacturer_code[2], bfile->manufacturer_code[3]);
	printf("flag_cgb:\t\t0x%x\n", bfile->flag_cgb);
	printf("data_license:\t\t0x%x 0x%x\n", bfile->data_license, *(&bfile->data_license + 1));
	printf("flag_sgb:\t\t0x%x\n", bfile->flag_sgb);
	printf("flag_cart:\t\t0x%x\n", bfile->flag_cart);
	printf("flag_romsize:\t\t0x%x\n", bfile->flag_romsize);
	printf("flag_ramsize:\t\t0x%x\n", bfile->flag_ramsize);
	printf("flag_region:\t\t0x%x\n", bfile->flag_region);
	printf("data_license_ext:\t0x%x\n", bfile->data_license_ext);
	printf("data_rom_version:\t0x%x\n", bfile->data_rom_version);
	printf("data_header_check:\t0x%x\n", bfile->data_header_check);
	printf("data_checksum:\t\t%x %d\n", bfile->data_checksum, bfile->data_checksum);
	
	
	
	
	
	free(memory_map);
	
	puts("Done");
	
	return 0;
}
