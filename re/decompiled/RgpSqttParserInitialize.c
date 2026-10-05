// function: RgpSqttParserInitialize @ 00be5d40

undefined4
RgpSqttParserInitialize
          (undefined8 param_1,undefined8 *param_2,ulong param_3,undefined8 param_4,int param_5,
          uint param_6,undefined4 param_7,int param_8,int param_9,int param_10,undefined4 param_11,
          undefined4 param_12,undefined4 param_13)

{
  undefined8 uVar1;
  
  if ((param_2 == (undefined8 *)0x0) || (param_3 == 0)) {
    return 0x80000000;
  }
  if ((param_3 & 1) == 0) {
    if ((int)param_6 < 2) {
      return 0x80000002;
    }
    if ((param_6 & 1) == 0) {
      if ((param_8 < 2) || ((param_8 == 2 && (param_9 < 2)))) {
        return 0x80000006;
      }
      if (param_10 < 6) {
        return 0x8000000e;
      }
      if (param_10 < 0x12) {
        *param_2 = param_4;
        uVar1 = DAT_00df22b0;
        param_2[0x11] = param_3;
        *(uint *)(param_2 + 0x12) = param_6 + param_5;
        *(int *)((long)param_2 + 0x9c) = param_5;
        *(undefined4 *)(param_2 + 5) = 0;
        *(undefined4 *)(param_2 + 0xb) = 0;
        *(int *)(param_2 + 0x15) = param_9;
        *(int *)((long)param_2 + 0xac) = param_10;
        *(undefined8 *)((long)param_2 + 0x94) = 0;
        param_2[10] = 0;
        param_2[0x10] = 0;
        param_2[1] = 0;
        param_2[0xc] = 0;
        *(undefined1 *)(param_2 + 0xd) = 0;
        param_2[8] = 0;
        param_2[9] = uVar1;
        param_2[0xe] = param_1;
        param_2[0x14] = CONCAT44(param_8,param_7);
        param_2[0xf] = CONCAT44(param_11,param_11);
        param_2[0x16] = CONCAT44(param_13,param_12);
        *(undefined1 (*) [16])(param_2 + 3) = (undefined1  [16])0x0;
        *(undefined1 (*) [16])(param_2 + 6) = (undefined1  [16])0x0;
        return 0;
      }
      return 0x8000000f;
    }
  }
  return 0x80000001;
}

