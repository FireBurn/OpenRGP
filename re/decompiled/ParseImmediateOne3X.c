// function: ParseImmediateOne3X @ 00be60c0

/* ParseImmediateOne3X(RgpSqttParser*, unsigned char, RgpSqttTokenIssue*) */

undefined8 ParseImmediateOne3X(RgpSqttParser *param_1,uchar param_2,RgpSqttTokenIssue *param_3)

{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  undefined8 uVar4;
  uint uVar5;
  
  uVar2 = *(uint *)(param_1 + 0x94);
  uVar5 = *(uint *)(param_1 + 0x9c);
  if (*(int *)(param_1 + 0xa4) < 3) {
    if (*(int *)(param_1 + 0x90) < (int)(uVar2 + 4 + uVar5)) {
      return 0x80000002;
    }
    uVar5 = *(uint *)((ulong)uVar5 + *(long *)(param_1 + 0x88) + (long)(int)uVar2);
  }
  else {
    iVar1 = (uVar2 & 1) * 4;
    if (*(int *)(param_1 + 0x90) < (int)((uVar2 >> 1) + 4 + uVar5 + iVar1)) {
      return 0x80000002;
    }
    uVar5 = *(uint *)((ulong)uVar5 + *(long *)(param_1 + 0x88) + (ulong)(uVar2 >> 1)) >>
            (sbyte)iVar1;
  }
  uVar4 = *(undefined8 *)(param_1 + 0x18);
  *(uint *)(param_3 + 8) = uVar2;
  *(undefined8 *)param_3 = uVar4;
  uVar3 = *(undefined4 *)(param_1 + 0xa0);
  *(undefined4 *)(param_3 + 0x14) = 0;
  *(undefined4 *)(param_3 + 0x10) = uVar3;
  *(undefined1 (*) [16])(param_3 + 0x18) = (undefined1  [16])0x0;
  *(undefined1 (*) [16])(param_3 + 0x28) = (undefined1  [16])0x0;
  *(undefined1 (*) [16])(param_3 + 0x38) = (undefined1  [16])0x0;
  *(undefined1 (*) [16])(param_3 + 0x48) = (undefined1  [16])0x0;
  *(undefined1 (*) [16])(param_3 + 0x58) = (undefined1  [16])0x0;
  *(undefined4 *)(param_3 + (ulong)(uVar5 >> 7 & 0x1f) * 4 + 0x18) = 3;
  return 0;
}

