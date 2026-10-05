// function: ParseImmediate3X @ 00be5fb0

/* ParseImmediate3X(RgpSqttParser*, unsigned char, RgpSqttTokenIssue*) */

undefined8 ParseImmediate3X(RgpSqttParser *param_1,uchar param_2,RgpSqttTokenIssue *param_3)

{
  uint uVar1;
  undefined4 uVar2;
  int iVar3;
  undefined8 uVar4;
  uint *puVar5;
  RgpSqttTokenIssue *pRVar6;
  uint uVar7;
  uint uVar8;
  
  uVar1 = *(uint *)(param_1 + 0x94);
  uVar8 = *(uint *)(param_1 + 0x9c);
  if (*(int *)(param_1 + 0xa4) < 3) {
    if (*(int *)(param_1 + 0x90) < (int)(uVar1 + 4 + uVar8)) {
      return 0x80000002;
    }
    uVar8 = *(uint *)((ulong)uVar8 + *(long *)(param_1 + 0x88) + (long)(int)uVar1);
  }
  else {
    uVar7 = uVar1 & 1;
    iVar3 = uVar7 * 4;
    if (*(int *)(param_1 + 0x90) < (int)((uVar1 >> 1) + 4 + uVar8 + iVar3)) {
      return 0x80000002;
    }
    puVar5 = (uint *)((ulong)uVar8 + *(long *)(param_1 + 0x88) + (ulong)(uVar1 >> 1));
    uVar8 = *puVar5 >> (sbyte)iVar3;
    uVar8 = (*(int *)((long)puVar5 + (long)iVar3) << (char)uVar7 * '\x1c' ^ uVar8) & -uVar7 &
            0xf0000000 ^ uVar8;
  }
  uVar4 = *(undefined8 *)(param_1 + 0x18);
  *(uint *)(param_3 + 8) = uVar1;
  uVar8 = uVar8 >> 8;
  *(undefined8 *)param_3 = uVar4;
  uVar2 = *(undefined4 *)(param_1 + 0xa0);
  *(undefined1 (*) [16])(param_3 + 0x18) = (undefined1  [16])0x0;
  *(undefined4 *)(param_3 + 0x10) = uVar2;
  pRVar6 = param_3 + 0x18;
  *(undefined4 *)(param_3 + 0x14) = 0;
  *(undefined1 (*) [16])(param_3 + 0x28) = (undefined1  [16])0x0;
  *(undefined1 (*) [16])(param_3 + 0x38) = (undefined1  [16])0x0;
  *(undefined1 (*) [16])(param_3 + 0x48) = (undefined1  [16])0x0;
  *(undefined1 (*) [16])(param_3 + 0x58) = (undefined1  [16])0x0;
  iVar3 = *(int *)(param_1 + 0xb0);
  if (0 < iVar3) {
    do {
      if ((uVar8 & 1) != 0) {
        *(undefined4 *)pRVar6 = 3;
      }
      pRVar6 = pRVar6 + 4;
      uVar8 = uVar8 >> 1;
    } while (pRVar6 != param_3 + (ulong)(iVar3 - 1) * 4 + 0x1c);
  }
  return 0;
}

