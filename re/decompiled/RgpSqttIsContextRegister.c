// function: RgpSqttIsContextRegister @ 00be62e0

uint RgpSqttIsContextRegister(undefined2 param_1,int param_2)

{
  ulong uVar1;
  ushort uVar2;
  
  uVar2 = 0xa3ff;
  if (param_2 < 0x11) {
    uVar2 = 0xbfff;
  }
  uVar1 = RgpSqttGetContextRegisterBaseAddress(param_1);
  return (uint)CONCAT71((int7)(uVar1 >> 8),0x9fff < (ushort)uVar1) &
         (uint)CONCAT71((int7)((uVar1 & 0xffffffff) >> 8),(ushort)(uVar1 & 0xffffffff) <= uVar2);
}

