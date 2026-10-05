// function: RgpSqttParserDataIsValid @ 00be7240

undefined4 RgpSqttParserDataIsValid(long param_1)

{
  uint uVar1;
  
  if (param_1 == 0) {
    return 0;
  }
  uVar1 = *(int *)(param_1 + 0xac) - 6;
  if (10 < uVar1) {
    return CONCAT31((int3)((uint)*(int *)(param_1 + 0x28) >> 8),*(int *)(param_1 + 0x28) != 0);
  }
  return CONCAT31((int3)(uVar1 >> 8),*(int *)(param_1 + 0x58) != 0);
}

