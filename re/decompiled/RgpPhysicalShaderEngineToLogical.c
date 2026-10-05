// function: RgpPhysicalShaderEngineToLogical @ 00b46320

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint RgpPhysicalShaderEngineToLogical(void *param_1,uint *param_2)

{
  uint uVar1;
  uint uVar2;
  long in_FS_OFFSET;
  uint uVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  int local_98 [4];
  int local_88;
  int iStack_84;
  int iStack_80;
  int iStack_7c;
  int local_78;
  int iStack_74;
  int iStack_70;
  int iStack_6c;
  int local_68;
  int iStack_64;
  int iStack_60;
  int iStack_5c;
  int local_58;
  int iStack_54;
  int iStack_50;
  int iStack_4c;
  int local_48;
  int iStack_44;
  int iStack_40;
  int iStack_3c;
  int local_38;
  int iStack_34;
  int iStack_30;
  int iStack_2c;
  int local_28;
  int iStack_24;
  int iStack_20;
  int iStack_1c;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  memcpy_s(local_98,0x80,param_1,0x80);
  uVar2 = *param_2;
  if ((int)uVar2 < 1) goto LAB_00b46467;
  if (uVar2 - 1 < 3) {
    uVar1 = 0;
    iVar4 = 0;
LAB_00b46436:
    iVar4 = iVar4 + (uint)(local_98[(int)uVar1] == 0);
    if ((int)(uVar1 + 1) < (int)uVar2) {
      iVar4 = iVar4 + (uint)(local_98[(int)(uVar1 + 1)] == 0);
      if ((int)(uVar1 + 2) < (int)uVar2) {
        iVar4 = iVar4 + (uint)(local_98[(int)(uVar1 + 2)] == 0);
      }
    }
  }
  else {
    uVar1 = uVar2 >> 2;
    uVar3 = -(uint)(local_98[0] == 0) & (uint)DAT_00e39b00;
    uVar5 = -(uint)(local_98[1] == 0) & DAT_00e39b00._4_4_;
    uVar6 = -(uint)(local_98[2] == 0) & _UNK_00e39b08;
    uVar7 = -(uint)(SUB124(SUB1612((undefined1  [16])0x0,4),8) == local_98[3]) & _UNK_00e39b0c;
    if (uVar1 != 1) {
      uVar3 = uVar3 + (local_88 == 0);
      uVar5 = uVar5 + (iStack_84 == 0);
      uVar6 = uVar6 + (iStack_80 == 0);
      uVar7 = uVar7 + (SUB124(SUB1612((undefined1  [16])0x0,4),8) == iStack_7c);
      if (uVar1 != 2) {
        uVar3 = uVar3 + (local_78 == 0);
        uVar5 = uVar5 + (iStack_74 == 0);
        uVar6 = uVar6 + (iStack_70 == 0);
        uVar7 = uVar7 + (SUB124(SUB1612((undefined1  [16])0x0,4),8) == iStack_6c);
        if (uVar1 != 3) {
          uVar3 = uVar3 + (local_68 == 0);
          uVar5 = uVar5 + (iStack_64 == 0);
          uVar6 = uVar6 + (iStack_60 == 0);
          uVar7 = uVar7 + (SUB124(SUB1612((undefined1  [16])0x0,4),8) == iStack_5c);
          if (uVar1 != 4) {
            uVar3 = uVar3 + (local_58 == 0);
            uVar5 = uVar5 + (iStack_54 == 0);
            uVar6 = uVar6 + (iStack_50 == 0);
            uVar7 = uVar7 + (SUB124(SUB1612((undefined1  [16])0x0,4),8) == iStack_4c);
            if (uVar1 != 5) {
              uVar3 = uVar3 + (local_48 == 0);
              uVar5 = uVar5 + (iStack_44 == 0);
              uVar6 = uVar6 + (iStack_40 == 0);
              uVar7 = uVar7 + (SUB124(SUB1612((undefined1  [16])0x0,4),8) == iStack_3c);
              if (uVar1 != 6) {
                uVar3 = uVar3 + (local_38 == 0);
                uVar5 = uVar5 + (iStack_34 == 0);
                uVar6 = uVar6 + (iStack_30 == 0);
                uVar7 = uVar7 + (SUB124(SUB1612((undefined1  [16])0x0,4),8) == iStack_2c);
                if (uVar1 != 7) {
                  uVar3 = uVar3 + (local_28 == 0);
                  uVar5 = uVar5 + (iStack_24 == 0);
                  uVar6 = uVar6 + (iStack_20 == 0);
                  uVar7 = uVar7 + (SUB124(SUB1612((undefined1  [16])0x0,4),8) == iStack_1c);
                }
              }
            }
          }
        }
      }
    }
    uVar1 = uVar2 & 0xfffffffc;
    iVar4 = uVar3 + uVar6 + uVar5 + uVar7;
    if ((uVar2 & 3) != 0) goto LAB_00b46436;
  }
  uVar2 = uVar2 - iVar4;
LAB_00b46467:
  if (local_10 == *(long *)(in_FS_OFFSET + 0x28)) {
    return uVar2;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}

