#include "r_type_funcs.h"
#include "instruction_utils.h"
#include "../io.h"
#include <stdio.h>

void instruction_add(emulator_t* emulator, uint8_t* instruction) {
  uint8_t rm, shamt, rn, rd;
  get_r_format_params(instruction, &rm, &shamt, &rn, &rd);
  //printf("ADD called: X%d = X%d + X%d with shamt %d.\n", rd, rn, rm, shamt);
  int64_t result = get_reg(emulator, rm) + get_reg(emulator, rn);
  set_reg(emulator, rd, result);
}

void instruction_adds(emulator_t* emulator, uint8_t* instruction) {
  uint8_t rm, shamt, rn, rd;
  get_r_format_params(instruction, &rm, &shamt, &rn, &rd);
  //printf("ADDS called: X%d = X%d + X%d with shamt %d.\n", rd, rn, rm, shamt);
  int64_t result = get_reg(emulator, rm) + get_reg(emulator, rn);
  set_condition_codes(emulator, result);
  set_reg(emulator, rd, result);
}

void instruction_sub(emulator_t* emulator, uint8_t* instruction) {
  uint8_t rm, shamt, rn, rd;
  get_r_format_params(instruction, &rm, &shamt, &rn, &rd);
  //printf("SUB called: X%d = X%d - X%d with shamt %d.\n", rd, rn, rm, shamt);
  int64_t result = get_reg(emulator, rm) - get_reg(emulator, rn);
  set_reg(emulator, rd, result);
}

void instruction_subs(emulator_t* emulator, uint8_t* instruction) {
  uint8_t rm, shamt, rn, rd;
  get_r_format_params(instruction, &rm, &shamt, &rn, &rd);
  //printf("SUBS called: X%d = X%d - X%d with shamt %d.\n", rd, rn, rm, shamt);
  int64_t result = get_reg(emulator, rm) - get_reg(emulator, rn);
  set_condition_codes(emulator, result);
  set_reg(emulator, rd, result);
}

void instruction_and(emulator_t* emulator, uint8_t* instruction) {
  uint8_t rm, shamt, rn, rd;
  get_r_format_params(instruction, &rm, &shamt, &rn, &rd);
  //printf("AND called: X%d = X%d & X%d with shamt %d.\n", rd, rn, rm, shamt);
  int64_t result = get_reg(emulator, rm) & get_reg(emulator, rn);
  set_reg(emulator, rd, result);
}

void instruction_ands(emulator_t* emulator, uint8_t* instruction) {
  uint8_t rm, shamt, rn, rd;
  get_r_format_params(instruction, &rm, &shamt, &rn, &rd);
  //printf("ANDS called: X%d = X%d & X%d with shamt %d.\n", rd, rn, rm, shamt);
  int64_t result = get_reg(emulator, rm) & get_reg(emulator, rn);
  set_condition_codes(emulator, result);
  set_reg(emulator, rd, result);
}

void instruction_orr(emulator_t* emulator, uint8_t* instruction) {
  uint8_t rm, shamt, rn, rd;
  get_r_format_params(instruction, &rm, &shamt, &rn, &rd);
  //printf("ORR called: X%d = X%d | X%d with shamt %d.\n", rd, rn, rm, shamt);
  int64_t result = get_reg(emulator, rm) | get_reg(emulator, rn);
  set_reg(emulator, rd, result);
}

void instruction_eor(emulator_t* emulator, uint8_t* instruction) {
  uint8_t rm, shamt, rn, rd;
  get_r_format_params(instruction, &rm, &shamt, &rn, &rd);
  //printf("EOR called: X%d = X%d ^ X%d with shamt %d.\n", rd, rn, rm, shamt);
  int64_t result = get_reg(emulator, rm) ^ get_reg(emulator, rn);
  set_reg(emulator, rd, result);
}

void instruction_br(emulator_t* emulator, uint8_t* instruction) {
  uint8_t rm, shamt, rn, rd;
  get_r_format_params(instruction, &rm, &shamt, &rn, &rd);
  
}

void instruction_prnl(emulator_t* emulator, uint8_t* instruction) {
  print_line("");
}

void instruction_prnt(emulator_t* emulator, uint8_t* instruction) {
  uint8_t rm, shamt, rn, rd;
  get_r_format_params(instruction, &rm, &shamt, &rn, &rd);
  print_register(rd, emulator->registers[rd]);
}

void instruction_dump(emulator_t* emulator, uint8_t* instruction) {
  print_line("Registers:");
  for (int i = 0; i < 32; i++) {
    print_register(i, emulator->registers[i]);
  }
  print_line("");
  print_line("Stack:");
  hexdump(emulator->stack, STACK_SIZE);
  print_line("");
  print_line("Main Memory:");
  hexdump(emulator->memory, MEM_SIZE);
  //TODO: compile machine code into assembly for some godforsaken reason
}

void instruction_halt(emulator_t* emulator, uint8_t* instruction) {
  instruction_dump(emulator, instruction);
  //TODO: change handle allocated memory before exit
  exit(0);
}