// function: RgpSqttGetSizeFromInstructionType @ 00be6360

char RgpSqttGetSizeFromInstructionType(int param_1)

{
  return (-(param_1 - 0x11U < 2) & 4U) + 4;
}

