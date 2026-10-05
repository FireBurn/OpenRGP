// function: RgpSqttParserGetSqttDataSize @ 00be72c0

int RgpSqttParserGetSqttDataSize(long param_1)

{
  int iVar1;
  
  iVar1 = 0;
  if (param_1 != 0) {
    iVar1 = *(int *)(param_1 + 0x90) - *(int *)(param_1 + 0x9c);
  }
  return iVar1;
}

