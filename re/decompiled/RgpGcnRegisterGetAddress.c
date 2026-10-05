// function: RgpGcnRegisterGetAddress @ 00ba8530

undefined2 RgpGcnRegisterGetAddress(int param_1,int param_2)

{
  undefined2 uVar1;
  
  uVar1 = 0;
  if (param_2 - 3U < 0xf) {
    uVar1 = *(undefined2 *)("E0E0T0" + (long)(int)(param_1 * 0xf + (param_2 - 3U)) * 2);
  }
  return uVar1;
}

