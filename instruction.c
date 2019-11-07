#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "tree.h"
#include "opcodes.h"

int get_param(uint8_t* instruction, short offset, short length) {
  int temp = 0;
  instruction += offset / 8;
  offset = 7 - (offset % 8);
  for (int i = 0; i < length; i++) {
    temp *= 2;
    if (offset < 0) {
      offset = 7;
      instruction++;
    }
    temp += (*instruction >> offset--) & 1;
  }
  return temp;
}

void get_r_format_params(uint8_t* instruction, uint8_t* rm, uint8_t* shamt, uint8_t* rn, uint8_t* rd) {
  *rm = get_param(instruction, 11, 5);
  *shamt = get_param(instruction, 16, 6);
  *rn = get_param(instruction, 22, 5);
  *rd = get_param(instruction, 27, 5);
}

void get_d_format_params(uint8_t* instruction, uint16_t* address, uint8_t* op2, uint8_t* rn, uint8_t* rt) {
  *address = get_param(instruction, 11, 9);
  *op2 = get_param(instruction, 20, 2);
  *rn = get_param(instruction, 22, 5);
  *rt = get_param(instruction, 27, 5);
}

void get_i_format_params(uint8_t* instruction, uint16_t* immediate, uint8_t* rn, uint8_t* rd) {
  *immediate = get_param(instruction, 10, 12);
  *rn = get_param(instruction, 22, 5);
  *rd = get_param(instruction, 27, 5);
}

void placeholder(uint16_t* registers, uint8_t* instruction) {
  return;
}

void instruction_add(uint16_t* registers, uint8_t* instruction) {
  uint8_t rm, shamt, rn, rd;
  get_r_format_params(instruction, &rm, &shamt, &rn, &rd);
  printf("ADD called: X%d = X%d + X%d with shamt %d.\n", rd, rn, rm, shamt);
}

void instruction_addi(uint16_t* registers, uint8_t* instruction) {
  uint8_t rn, rd;
  uint16_t immediate;
  get_i_format_params(instruction, &immediate, &rn, &rd);
  printf("ADDI called: X%d = X%d + #%d.\n", rd, rn, immediate);
}

void instruction_adds(uint16_t* registers, uint8_t* instruction) {
  uint8_t rm, shamt, rn, rd;
  get_r_format_params(instruction, &rm, &shamt, &rn, &rd);
  printf("ADDS called: X%d = X%d + X%d with shamt %d.\n", rd, rn, rm, shamt);
}

void instruction_addis(uint16_t* registers, uint8_t* instruction) {
  uint8_t rn, rd;
  uint16_t immediate;
  get_i_format_params(instruction, &immediate, &rn, &rd);
  printf("ADDIS called: X%d = X%d + #%d.\n", rd, rn, immediate);
}

void instruction_sub(uint16_t* registers, uint8_t* instruction) {
  uint8_t rm, shamt, rn, rd;
  get_r_format_params(instruction, &rm, &shamt, &rn, &rd);
  printf("SUB called: X%d = X%d - X%d with shamt %d.\n", rd, rn, rm, shamt);
}

void instruction_subi(uint16_t* registers, uint8_t* instruction) {
  uint8_t rn, rd;
  uint16_t immediate;
  get_i_format_params(instruction, &immediate, &rn, &rd);
  printf("SUBI called: X%d = X%d - #%d.\n", rd, rn, immediate);
}

void instruction_subs(uint16_t* registers, uint8_t* instruction) {
  uint8_t rm, shamt, rn, rd;
  get_r_format_params(instruction, &rm, &shamt, &rn, &rd);
  printf("SUBS called: X%d = X%d - X%d with shamt %d.\n", rd, rn, rm, shamt);
}

void instruction_subis(uint16_t* registers, uint8_t* instruction) {
  uint8_t rn, rd;
  uint16_t immediate;
  get_i_format_params(instruction, &immediate, &rn, &rd);
  printf("SUBIS called: X%d = X%d - #%d.\n", rd, rn, immediate);
}

void instruction_and(uint16_t* registers, uint8_t* instruction) {
  uint8_t rm, shamt, rn, rd;
  get_r_format_params(instruction, &rm, &shamt, &rn, &rd);
  printf("AND called: X%d = X%d & X%d with shamt %d.\n", rd, rn, rm, shamt);
}

void instruction_andi(uint16_t* registers, uint8_t* instruction) {
  uint8_t rn, rd;
  uint16_t immediate;
  get_i_format_params(instruction, &immediate, &rn, &rd);
  printf("ANDI called: X%d = X%d & #%d.\n", rd, rn, immediate);
}

void instruction_ands(uint16_t* registers, uint8_t* instruction) {
  uint8_t rm, shamt, rn, rd;
  get_r_format_params(instruction, &rm, &shamt, &rn, &rd);
  printf("ANDS called: X%d = X%d & X%d with shamt %d.\n", rd, rn, rm, shamt);
}

void instruction_andis(uint16_t* registers, uint8_t* instruction) {
  uint8_t rn, rd;
  uint16_t immediate;
  get_i_format_params(instruction, &immediate, &rn, &rd);
  printf("ANDIS called: X%d = X%d & #%d.\n", rd, rn, immediate);
}

tree_t* init_opcode_tree() {
  tree_t* t = malloc(sizeof(tree_t)); 
  tree_init(t);
  
  tree_insert(t, "01010100", placeholder);
  tree_insert(t, OP_ADD, instruction_add);
  tree_insert(t, OP_ADDI, instruction_addi);
  tree_insert(t, OP_ADDS, instruction_adds);
  tree_insert(t, OP_ADDIS, instruction_addis);
  tree_insert(t, OP_SUB, instruction_sub);
  tree_insert(t, OP_SUBI, instruction_subi);
  tree_insert(t, OP_SUBS, instruction_subs);
  tree_insert(t, OP_SUBIS, instruction_subis);
  tree_insert(t, OP_AND, instruction_and);
  tree_insert(t, OP_ANDI, instruction_andi);
  tree_insert(t, OP_ANDS, instruction_ands);
  tree_insert(t, OP_ANDIS, instruction_andis);

  return t;
}

short run_instruction(tree_t* opcode_tree, uint8_t* instruction, uint16_t* registers) {
  void (*instruction_handler)(uint16_t*, uint8_t*) = get_value_op(opcode_tree, instruction);
  if (!instruction_handler) {
    return -1;
  }
  instruction_handler(registers, instruction);
  return 0;
}
