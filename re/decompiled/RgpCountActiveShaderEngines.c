// function: RgpCountActiveShaderEngines @ 00b464a0

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int RgpCountActiveShaderEngines(void *param_1,uint param_2)

{
  uint uVar1;
  long in_FS_OFFSET;
  uint uVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
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
  if ((int)param_2 < 1) {
    iVar3 = 0;
  }
  else {
    if (param_2 - 1 < 3) {
      uVar1 = 0;
      iVar3 = 0;
    }
    else {
      uVar1 = param_2 >> 2;
      uVar2 = ~-(uint)(local_98[0] == 0) & (uint)DAT_00e39b00;
      uVar4 = ~-(uint)(local_98[1] == 0) & DAT_00e39b00._4_4_;
      uVar5 = ~-(uint)(local_98[2] == 0) & _UNK_00e39b08;
      uVar6 = ~-(uint)(SUB124(SUB1612((undefined1  [16])0x0,4),8) == local_98[3]) & _UNK_00e39b0c;
      if (uVar1 != 1) {
        uVar2 = uVar2 + (local_88 != 0);
        uVar4 = uVar4 + (iStack_84 != 0);
        uVar5 = uVar5 + (iStack_80 != 0);
        uVar6 = uVar6 + (SUB124(SUB1612((undefined1  [16])0x0,4),8) != iStack_7c);
        if (uVar1 != 2) {
          uVar2 = uVar2 + (local_78 != 0);
          uVar4 = uVar4 + (iStack_74 != 0);
          uVar5 = uVar5 + (iStack_70 != 0);
          uVar6 = uVar6 + (SUB124(SUB1612((undefined1  [16])0x0,4),8) != iStack_6c);
          if (uVar1 != 3) {
            uVar2 = uVar2 + (local_68 != 0);
            uVar4 = uVar4 + (iStack_64 != 0);
            uVar5 = uVar5 + (iStack_60 != 0);
            uVar6 = uVar6 + (SUB124(SUB1612((undefined1  [16])0x0,4),8) != iStack_5c);
            if (uVar1 != 4) {
              uVar2 = uVar2 + (local_58 != 0);
              uVar4 = uVar4 + (iStack_54 != 0);
              uVar5 = uVar5 + (iStack_50 != 0);
              uVar6 = uVar6 + (SUB124(SUB1612((undefined1  [16])0x0,4),8) != iStack_4c);
              if (uVar1 != 5) {
                uVar2 = uVar2 + (local_48 != 0);
                uVar4 = uVar4 + (iStack_44 != 0);
                uVar5 = uVar5 + (iStack_40 != 0);
                uVar6 = uVar6 + (SUB124(SUB1612((undefined1  [16])0x0,4),8) != iStack_3c);
                if (uVar1 != 6) {
                  uVar2 = uVar2 + (local_38 != 0);
                  uVar4 = uVar4 + (iStack_34 != 0);
                  uVar5 = uVar5 + (iStack_30 != 0);
                  uVar6 = uVar6 + (SUB124(SUB1612((undefined1  [16])0x0,4),8) != iStack_2c);
                  if (uVar1 != 7) {
                    uVar2 = uVar2 + (local_28 != 0);
                    uVar4 = uVar4 + (iStack_24 != 0);
                    uVar5 = uVar5 + (iStack_20 != 0);
                    uVar6 = uVar6 + (SUB124(SUB1612((undefined1  [16])0x0,4),8) ==
                                    -(uint)(SUB124(SUB1612((undefined1  [16])0x0,4),8) == iStack_1c)
                                    );
                  }
                }
              }
            }
          }
        }
      }
      uVar1 = param_2 & 0xfffffffc;
      iVar3 = uVar2 + uVar5 + uVar4 + uVar6;
      if ((param_2 & 3) == 0) goto LAB_00b46601;
    }
    iVar3 = (iVar3 + 1) - (uint)(local_98[(int)uVar1] == 0);
    if ((int)(uVar1 + 1) < (int)param_2) {
      iVar3 = (iVar3 + 1) - (uint)(local_98[(int)(uVar1 + 1)] == 0);
      if ((int)(uVar1 + 2) < (int)param_2) {
        iVar3 = (iVar3 + 1) - (uint)(local_98[(int)(uVar1 + 2)] == 0);
      }
    }
  }
LAB_00b46601:
  if (local_10 == *(long *)(in_FS_OFFSET + 0x28)) {
    return iVar3;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}

