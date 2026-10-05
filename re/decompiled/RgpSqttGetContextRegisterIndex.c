// function: RgpSqttGetContextRegisterIndex @ 00be6310

ushort RgpSqttGetContextRegisterIndex(ushort param_1,byte param_2,int param_3)

{
  ushort uVar1;
  
  uVar1 = (ushort)param_2;
  if (param_3 < 0xe) {
    uVar1 = param_1 >> 10 & 7;
  }
  return uVar1;
}

