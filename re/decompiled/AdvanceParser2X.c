// function: AdvanceParser2X @ 00be6380

/* AdvanceParser2X(RgpSqttParser*, RgpSqttToken*, RgpSqttParserPosition*) */

undefined8
AdvanceParser2X(RgpSqttParser *param_1,RgpSqttToken *param_2,RgpSqttParserPosition *param_3)

{
  int iVar1;
  undefined4 uVar2;
  undefined8 uVar3;
  uint6 uVar4;
  uint6 uVar5;
  short sVar6;
  uint uVar7;
  int iVar8;
  uint uVar9;
  undefined4 uVar10;
  ulong uVar11;
  ushort *puVar12;
  long lVar13;
  RgpSqttToken *pRVar14;
  RgpSqttToken *pRVar15;
  ushort uVar16;
  uint uVar17;
  uint uVar18;
  int iVar19;
  long lVar20;
  uint uVar21;
  RgpSqttToken RVar22;
  uint uVar23;
  uint *puVar24;
  ushort uVar25;
  uint uVar26;
  int iVar27;
  byte *pbVar28;
  undefined1 auVar29 [16];
  
  if (param_2 == (RgpSqttToken *)0x0 || param_1 == (RgpSqttParser *)0x0) {
    return 0x80000000;
  }
  uVar17 = *(uint *)(param_1 + 0x9c);
  uVar21 = *(uint *)(param_1 + 0x94);
  if (param_3 != (RgpSqttParserPosition *)0x0) {
    *(undefined4 *)(param_3 + 0x10) = *(undefined4 *)(param_1 + 0x28);
    uVar3 = *(undefined8 *)(param_1 + 0x18);
    *(ulong *)(param_3 + 8) = CONCAT44(uVar21,uVar17);
    *(undefined8 *)param_3 = uVar3;
  }
  iVar19 = *(int *)(param_1 + 0xa4);
  iVar1 = *(int *)(param_1 + 0x90);
  if (iVar19 < 3) {
    if (iVar1 < (int)(uVar21 + 2 + uVar17)) {
      return 0x80000002;
    }
    lVar20 = (ulong)uVar17 + *(long *)(param_1 + 0x88);
    uVar18 = (uint)*(ushort *)((int)uVar21 + lVar20);
  }
  else {
    uVar7 = uVar21 & 1;
    iVar27 = uVar7 * 2;
    if (iVar1 < (int)((uVar21 >> 1) + 2 + uVar17 + iVar27)) {
      return 0x80000002;
    }
    lVar20 = (ulong)uVar17 + *(long *)(param_1 + 0x88);
    puVar12 = (ushort *)((ulong)(uVar21 >> 1) + lVar20);
    uVar18 = (int)(uint)*puVar12 >> (char)uVar7 * '\x04';
    uVar18 = ((uint)*(ushort *)((long)puVar12 + (long)iVar27) <<
              ((char)iVar27 + (char)uVar7) * '\x04' ^ uVar18) & -uVar7 & 0xfffff000 ^ uVar18;
  }
  iVar27 = *(int *)(param_1 + 0x28);
  uVar7 = uVar18 & 0xf;
  uVar10 = *(undefined4 *)(CSWTCH_421 + (ulong)uVar7 * 4);
  uVar16 = (ushort)uVar18;
  if ((uVar18 & 0xf) == 0) {
    if (uVar16 >> 0xd == 1) {
      iVar8 = 2;
      uVar18 = uVar21;
      if (iVar19 < 3) {
        while (uVar18 = uVar18 + iVar8, (int)(uVar18 + 2 + uVar17) <= iVar1) {
          uVar25 = *(ushort *)((int)uVar18 + lVar20);
          if ((uVar25 & 0xf) == 1) {
            if ((int)(uVar18 + 8 + uVar17) <= iVar1) {
              pbVar28 = (byte *)(lVar20 + 2 + (long)(int)uVar18);
              uVar11 = (ulong)pbVar28[5] << 0x28 | (ulong)pbVar28[4] << 0x20 | (ulong)*pbVar28 |
                       (ulong)pbVar28[3] << 0x18 | (ulong)pbVar28[2] << 0x10 |
                       (ulong)pbVar28[1] << 8;
              goto LAB_00be64e7;
            }
            break;
          }
          iVar8 = *(int *)(CSWTCH_425 + (ulong)(uVar25 & 0xf) * 4);
        }
      }
      else {
        while( true ) {
          uVar18 = uVar18 + iVar8;
          uVar26 = uVar18 >> 1;
          uVar23 = uVar18 & 1;
          if (iVar1 < (int)(uVar23 * 2 + uVar26 + 2 + uVar17)) break;
          uVar9 = (int)(uint)*(ushort *)((ulong)uVar26 + lVar20) >> (char)uVar23 * '\x04';
          if (((ushort)uVar9 & 0xf) == 1) {
            if ((int)(uVar26 + 8 + uVar17 + uVar23) <= iVar1) {
              pbVar28 = (byte *)((ulong)(uVar26 + 2) + lVar20);
              uVar11 = (ulong)pbVar28[5] << 0x28 | (ulong)pbVar28[4] << 0x20 | (ulong)*pbVar28 |
                       (ulong)pbVar28[3] << 0x18 | (ulong)pbVar28[2] << 0x10 |
                       (ulong)pbVar28[1] << 8;
              if (uVar23 != 0) {
                uVar11 = (uVar11 | ((ulong)pbVar28[6] & 0xf) << 0x30) >> 4;
              }
LAB_00be64e7:
              if (iVar27 == 0) {
                *(ulong *)(param_1 + 0x20) = uVar11;
                *(undefined4 *)(param_1 + 0x28) = 1;
                *(undefined8 *)(param_1 + 0x18) = 0;
                *(undefined4 *)param_2 = uVar10;
              }
              else {
                *(ulong *)(param_1 + 0x18) = uVar11 - *(long *)(param_1 + 0x20);
                *(undefined4 *)param_2 = uVar10;
              }
              goto LAB_00be6505;
            }
            break;
          }
          iVar8 = *(int *)(CSWTCH_425 + (ulong)(uVar9 & 0xf) * 4);
        }
      }
    }
    else {
      *(ulong *)(param_1 + 0x18) = *(long *)(param_1 + 0x18) + (ulong)(uVar16 >> 2 & 0x3fc);
    }
    *(undefined4 *)param_2 = uVar10;
    if (iVar27 != 0) {
LAB_00be6505:
      uVar3 = *(undefined8 *)(param_1 + 0x18);
      *(uint *)(param_2 + 0x10) = uVar17 + uVar21;
      *(undefined8 *)(param_2 + 8) = uVar3;
      uVar10 = *(undefined4 *)(param_1 + 0xa0);
      *(uint *)(param_2 + 0x20) = uVar16 >> 0xc & 1;
      *(undefined4 *)(param_2 + 0x18) = uVar10;
      *(uint *)(param_2 + 0x1c) = (uint)(uVar16 >> 0xd);
    }
    goto LAB_00be66f2;
  }
  if (uVar7 == 1) {
    *(undefined4 *)param_2 = 1;
    if (iVar27 != 0) {
      *(undefined8 *)(param_2 + 8) = *(undefined8 *)(param_1 + 0x18);
      *(uint *)(param_2 + 0x10) = uVar17 + uVar21;
      if (iVar19 < 3) {
        if (iVar1 < (int)(uVar17 + uVar21 + 8)) {
          return 0x80000002;
        }
        pbVar28 = (byte *)(lVar20 + 2 + (long)(int)uVar21);
        uVar11 = (ulong)pbVar28[5] << 0x28 | (ulong)pbVar28[4] << 0x20 | (ulong)*pbVar28 |
                 (ulong)pbVar28[3] << 0x18 | (ulong)pbVar28[2] << 0x10 | (ulong)pbVar28[1] << 8;
      }
      else {
        if (iVar1 < (int)((uVar21 >> 1) + 8 + uVar17 + (uVar21 & 1))) {
          return 0x80000002;
        }
        pbVar28 = (byte *)((ulong)((uVar21 >> 1) + 2) + lVar20);
        uVar11 = (ulong)pbVar28[5] << 0x28 | (ulong)pbVar28[4] << 0x20 | (ulong)*pbVar28 |
                 (ulong)pbVar28[3] << 0x18 | (ulong)pbVar28[2] << 0x10 | (ulong)pbVar28[1] << 8;
        if ((uVar21 & 1) != 0) {
          uVar11 = (uVar11 | ((ulong)pbVar28[6] & 0xf) << 0x30) >> 4;
        }
      }
      *(ulong *)(param_2 + 0x20) = uVar11;
      uVar10 = *(undefined4 *)(param_1 + 0xa0);
      *(undefined4 *)(param_2 + 0x28) = 0;
      *(undefined4 *)(param_2 + 0x18) = uVar10;
    }
    goto LAB_00be66f2;
  }
  lVar13 = (ulong)((uVar16 >> 4 & 1) << 2) + *(long *)(param_1 + 0x18);
  *(long *)(param_1 + 0x18) = lVar13;
  *(undefined4 *)param_2 = uVar10;
  if (iVar27 == 0) goto switchD_00be66be_caseD_0;
  RVar22 = (RgpSqttToken)0x0;
  switch(uVar16 & 0xf) {
  case 2:
    if (iVar19 < 3) {
      if (iVar1 < (int)(uVar17 + uVar21 + 4)) {
        return 0x80000002;
      }
      uVar25 = *(ushort *)((int)uVar21 + lVar20 + 2);
      if (iVar1 < (int)(uVar17 + uVar21 + 8)) {
        return 0x80000002;
      }
      uVar18 = *(uint *)((int)uVar21 + lVar20 + 4);
    }
    else {
      uVar23 = uVar21 & 1;
      iVar27 = (uVar21 >> 1) + uVar17;
      iVar19 = uVar23 * 2;
      if (iVar1 < iVar27 + 4 + iVar19) {
        return 0x80000002;
      }
      lVar20 = (ulong)(uVar21 >> 1) + lVar20;
      iVar8 = uVar23 * 4;
      uVar25 = (ushort)((int)(uint)*(ushort *)(lVar20 + 2) >> (sbyte)iVar8);
      uVar25 = (*(short *)(lVar20 + 2 + (long)iVar19) << ((char)iVar19 + (char)uVar23) * '\x04' ^
               uVar25) & -(short)uVar23 & 0xf000 ^ uVar25;
      if (iVar1 < iVar27 + 8 + iVar8) {
        return 0x80000002;
      }
      uVar18 = *(uint *)(lVar20 + 4) >> (sbyte)iVar8;
      uVar18 = (*(int *)(lVar20 + 4 + (long)iVar8) << (char)uVar23 * '\x1c' ^ uVar18) & -uVar23 &
               0xf0000000 ^ uVar18;
    }
    *(long *)(param_2 + 8) = lVar13;
    uVar10 = *(undefined4 *)(param_1 + 0xa0);
    *(uint *)(param_2 + 0x10) = uVar17 + uVar21;
    *(uint *)(param_2 + 0x2c) = uVar18;
    *(ushort *)(param_2 + 0x28) = uVar25;
    *(undefined4 *)(param_2 + 0x30) = 0;
    *(ulong *)(param_2 + 0x18) = (ulong)CONCAT24(uVar16 >> 7,uVar10) & 0x3ffffffff;
    *(uint *)(param_2 + 0x20) = uVar16 >> 5 & 3;
    *(undefined4 *)(param_2 + 0x24) = 0;
    *(uint *)(param_2 + 0x38) = uVar16 >> 9 & 1;
    *(uint *)(param_2 + 0x34) = (uint)(uVar16 >> 0xf);
    break;
  case 3:
    if (iVar19 < 3) {
      if (iVar1 < (int)(uVar17 + uVar21 + 4)) {
        return 0x80000002;
      }
      uVar18 = *(uint *)((int)uVar21 + lVar20);
    }
    else {
      uVar23 = uVar21 & 1;
      iVar19 = uVar23 * 4;
      if (iVar1 < (int)((uVar21 >> 1) + 4 + uVar17 + iVar19)) {
        return 0x80000002;
      }
      puVar24 = (uint *)((ulong)(uVar21 >> 1) + lVar20);
      uVar18 = *puVar24 >> (sbyte)iVar19;
      uVar18 = (*(int *)((long)puVar24 + (long)iVar19) << (char)uVar23 * '\x1c' ^ uVar18) & -uVar23
               & 0xf0000000 ^ uVar18;
    }
    *(long *)(param_2 + 8) = lVar13;
    uVar10 = *(undefined4 *)(param_1 + 0xa0);
    *(uint *)(param_2 + 0x10) = uVar17 + uVar21;
    uVar17 = uVar18 >> 0x10;
    if ((uVar18 & 0x100000) == 0) {
      uVar23 = 6;
      uVar26 = uVar17 & 3;
      iVar19 = ((int)uVar17 >> 2 & 3U) + 1;
    }
    else {
      uVar23 = uVar17 & 7;
      iVar19 = 0;
      uVar26 = uVar18 >> 0x13 & 1;
    }
    *(uint *)(param_2 + 0x28) = uVar18 >> 10 & 0xf;
    *(uint *)(param_2 + 0x3c) = uVar18 >> 0x16 & 0x7f;
    *(uint *)(param_2 + 0x2c) = uVar23;
    *(undefined4 *)(param_2 + 0x40) = 0;
    *(ulong *)(param_2 + 0x18) = CONCAT44(uVar18 >> 5,uVar10) & 0x1ffffffff;
    *(ulong *)(param_2 + 0x20) = CONCAT44(uVar18 >> 0xe,uVar18 >> 6) & 0x30000000f;
    *(ulong *)(param_2 + 0x30) = CONCAT44(uVar26,iVar19);
    break;
  case 4:
    *(long *)(param_2 + 8) = lVar13;
    uVar10 = *(undefined4 *)(param_1 + 0xa0);
    *(uint *)(param_2 + 0x10) = uVar17 + uVar21;
    uVar4 = CONCAT24(uVar16 >> 5,uVar10);
    uVar5 = CONCAT24(uVar16 >> 0xe,(uint)(uVar16 >> 6));
    goto LAB_00be6e1d;
  case 5:
    if (iVar19 < 3) {
      if (iVar1 < (int)(uVar17 + uVar21 + 8)) {
        return 0x80000002;
      }
      uVar18 = *(uint *)(lVar20 + 4 + (long)(int)uVar21);
    }
    else {
      uVar23 = uVar21 & 1;
      iVar19 = uVar23 * 4;
      if (iVar1 < (int)((uVar21 >> 1) + 8 + uVar17 + iVar19)) {
        return 0x80000002;
      }
      puVar24 = (uint *)((ulong)((uVar21 >> 1) + 4) + lVar20);
      uVar18 = *puVar24 >> (sbyte)iVar19;
      uVar18 = (*(int *)((long)puVar24 + (long)iVar19) << (char)uVar23 * '\x1c' ^ uVar18) & -uVar23
               & 0xf0000000 ^ uVar18;
    }
    *(long *)(param_2 + 8) = lVar13;
    uVar10 = *(undefined4 *)(param_1 + 0xa0);
    *(uint *)(param_2 + 0x10) = uVar17 + uVar21;
    *(ushort *)(param_2 + 0x28) = uVar16 >> 9;
    *(uint *)(param_2 + 0x2c) = uVar18;
    *(uint *)(param_2 + 0x20) = uVar16 >> 5 & 3;
    *(undefined4 *)(param_2 + 0x24) = 1;
    *(undefined8 *)(param_2 + 0x30) = 0x100000001;
    *(undefined4 *)(param_2 + 0x38) = 0;
    *(ulong *)(param_2 + 0x18) = (ulong)CONCAT24(uVar16 >> 7,uVar10) & 0x3ffffffff;
    break;
  case 6:
    *(long *)(param_2 + 8) = lVar13;
    *(uint *)(param_2 + 0x10) = uVar17 + uVar21;
    uVar4 = CONCAT24(uVar16 >> 5,*(undefined4 *)(param_1 + 0xa0));
    uVar5 = CONCAT24(uVar16 >> 0xe,(uint)(uVar16 >> 6));
LAB_00be6e1d:
    auVar29._0_8_ = (ulong)uVar4 & 0x1ffffffff;
    auVar29._8_6_ = uVar5 & 0xffff0000000f;
    auVar29._14_2_ = 0;
    *(undefined1 (*) [16])(param_2 + 0x18) = auVar29;
    *(uint *)(param_2 + 0x28) = uVar16 >> 10 & 0xf;
    break;
  case 7:
    *(long *)(param_2 + 8) = lVar13;
    uVar10 = *(undefined4 *)(param_1 + 0xa0);
    *(uint *)(param_2 + 0x10) = uVar17 + uVar21;
    uVar17 = (uint)(uVar16 >> 6);
    if ((uVar18 & 0x200) == 0) {
      uVar18 = uVar17 & 7;
      iVar19 = 0;
      uVar23 = 0;
    }
    else {
      uVar18 = 6;
      uVar23 = uVar17 & 3;
      iVar19 = ((int)(uVar17 & 0xf) >> 2) + 1;
    }
    *(int *)(param_2 + 0x2c) = iVar19;
    *(uint *)(param_2 + 0x30) = uVar23;
    *(uint *)(param_2 + 0x28) = uVar18;
    *(undefined4 *)(param_2 + 0x20) = 0;
    *(ulong *)(param_2 + 0x18) = (ulong)CONCAT24(uVar16 >> 5,uVar10) & 0x1ffffffff;
    if (uVar16 >> 10 == 0x35) {
LAB_00be6cf5:
      *(undefined4 *)(param_2 + 0x24) = 0;
      RVar22 = (RgpSqttToken)0x1;
    }
    else {
      *(uint *)(param_2 + 0x24) = (uint)(uVar16 >> 10);
    }
    goto LAB_00be6a5e;
  case 8:
    *(long *)(param_2 + 8) = lVar13;
    uVar10 = *(undefined4 *)(param_1 + 0xa0);
    *(uint *)(param_2 + 0x10) = uVar17 + uVar21;
    *(undefined4 *)(param_2 + 0x28) = 6;
    *(uint *)(param_2 + 0x24) = (uint)(uVar16 >> 10);
    *(ulong *)(param_2 + 0x18) = (ulong)CONCAT24(uVar16 >> 5,uVar10) & 0x1ffffffff;
    *(undefined4 *)(param_2 + 0x20) = 2;
    *(ulong *)(param_2 + 0x2c) =
         (ulong)CONCAT24(uVar16 >> 6,((int)(uVar16 >> 6 & 0xf) >> 2) + 1) & 0x3ffffffff;
    if (uVar16 >> 10 == 0x35) goto LAB_00be6cf5;
LAB_00be6a5e:
    param_2[0x34] = RVar22;
    *(undefined4 *)(param_2 + 0x38) = 0;
    break;
  case 9:
    *(long *)(param_2 + 8) = lVar13;
    uVar10 = *(undefined4 *)(param_1 + 0xa0);
    *(uint *)(param_2 + 0x10) = uVar17 + uVar21;
    *(undefined4 *)(param_2 + 0x20) = 1;
    *(ulong *)(param_2 + 0x18) = (ulong)CONCAT24(uVar16 >> 5,uVar10) & 0x1ffffffff;
    *(uint *)(param_2 + 0x28) = uVar16 >> 7 & 7;
    *(uint *)(param_2 + 0x24) = (uint)(uVar16 >> 10);
    *(undefined8 *)(param_2 + 0x2c) = DAT_00dfb978;
    if (uVar16 >> 10 == 0x35) {
      *(undefined4 *)(param_2 + 0x24) = 0;
      param_2[0x34] = (RgpSqttToken)0x1;
    }
    else {
      param_2[0x34] = (RgpSqttToken)0x0;
    }
    break;
  case 10:
    if (iVar19 < 3) {
      iVar19 = uVar21 + uVar17 + 4;
    }
    else {
      iVar19 = uVar17 + 4 + (uVar21 >> 1) + (uVar21 & 1) * 2;
    }
    if (iVar1 < iVar19) {
      return 0x80000002;
    }
    *(long *)(param_2 + 8) = lVar13;
    uVar10 = *(undefined4 *)(param_1 + 0xa0);
    *(uint *)(param_2 + 0x10) = uVar21 + uVar17;
    *(ulong *)(param_2 + 0x18) = (ulong)CONCAT24(uVar16 >> 9,uVar10) & 0x3ffffffff;
    *(uint *)(param_2 + 0x20) = uVar16 >> 5 & 0xf;
    uVar10 = RgpSqttParseGetGenericInstruction2_x((uint)(uVar16 >> 0xb));
    *(ushort *)(param_2 + 0x2c) = uVar16 >> 0xb;
    *(undefined4 *)(param_2 + 0x28) = uVar10;
    uVar10 = RgpSqttGetSizeFromInstructionType(uVar10);
    *(undefined2 *)(param_2 + 0x2e) = 0;
    uVar21 = *(uint *)(param_1 + 0x94);
    *(undefined4 *)(param_2 + 0x24) = uVar10;
    break;
  case 0xb:
    if (iVar19 < 3) {
      if (iVar1 < (int)(uVar17 + uVar21 + 8)) {
        return 0x80000002;
      }
      pbVar28 = (byte *)(lVar20 + 2 + (long)(int)uVar21);
      uVar11 = (ulong)pbVar28[5] << 0x28 | (ulong)pbVar28[4] << 0x20 | (ulong)*pbVar28 |
               (ulong)pbVar28[3] << 0x18 | (ulong)pbVar28[2] << 0x10 | (ulong)pbVar28[1] << 8;
    }
    else {
      if (iVar1 < (int)((uVar21 >> 1) + 8 + uVar17 + (uVar21 & 1))) {
        return 0x80000002;
      }
      pbVar28 = (byte *)((ulong)((uVar21 >> 1) + 2) + lVar20);
      uVar11 = (ulong)pbVar28[5] << 0x28 | (ulong)pbVar28[4] << 0x20 | (ulong)*pbVar28 |
               (ulong)pbVar28[3] << 0x18 | (ulong)pbVar28[2] << 0x10 | (ulong)pbVar28[1] << 8;
      if ((uVar21 & 1) != 0) {
        uVar11 = (uVar11 | ((ulong)pbVar28[6] & 0xf) << 0x30) >> 4;
      }
    }
    *(long *)(param_2 + 8) = lVar13;
    uVar10 = *(undefined4 *)(param_1 + 0xa0);
    *(uint *)(param_2 + 0x10) = uVar17 + uVar21;
    *(ulong *)(param_2 + 0x18) = (ulong)CONCAT24(uVar16 >> 9,uVar10) & 0x3ffffffff;
    *(uint *)(param_2 + 0x20) = uVar16 >> 5 & 0xf;
    *(ulong *)(param_2 + 0x28) = uVar11 * 4 & 0xffffffffffff | (ulong)(uVar16 >> 0xe);
    break;
  case 0xd:
    if (iVar19 < 3) {
      if (iVar1 < (int)(uVar17 + uVar21 + 4)) {
        return 0x80000002;
      }
      uVar23 = (uint)*(ushort *)(lVar20 + 2 + (long)(int)uVar21);
    }
    else {
      uVar26 = uVar21 & 1;
      iVar19 = uVar26 * 2;
      if (iVar1 < (int)((uVar21 >> 1) + 4 + uVar17 + iVar19)) {
        return 0x80000002;
      }
      puVar12 = (ushort *)((ulong)((uVar21 >> 1) + 2) + lVar20);
      uVar23 = (int)(uint)*puVar12 >> (char)uVar26 * '\x04';
      uVar23 = ((uint)*(ushort *)((long)puVar12 + (long)iVar19) <<
                ((char)iVar19 + (char)uVar26) * '\x04' ^ uVar23) & -uVar26 & 0xfffff000 ^ uVar23;
    }
    *(long *)(param_2 + 8) = lVar13;
    uVar10 = *(undefined4 *)(param_1 + 0xa0);
    uVar18 = uVar23 << 0x10 | uVar18 & 0xffff;
    *(uint *)(param_2 + 0x10) = uVar17 + uVar21;
    *(ulong *)(param_2 + 0x18) = CONCAT44(uVar18 >> 5,uVar10) & 0x3ffffffff;
    *(undefined1 (*) [16])(param_2 + 0x20) = (undefined1  [16])0x0;
    *(undefined1 (*) [16])(param_2 + 0x30) = (undefined1  [16])0x0;
    *(undefined1 (*) [16])(param_2 + 0x40) = (undefined1  [16])0x0;
    *(undefined1 (*) [16])(param_2 + 0x50) = (undefined1  [16])0x0;
    *(undefined1 (*) [16])(param_2 + 0x60) = (undefined1  [16])0x0;
    iVar19 = *(int *)(param_1 + 0xb0);
    if (0 < iVar19) {
      pRVar14 = param_2 + 0x20;
      uVar17 = uVar18 >> 8;
      do {
        pRVar15 = pRVar14 + 4;
        *(uint *)pRVar14 = uVar17 & 3;
        pRVar14 = pRVar15;
        uVar17 = uVar17 >> 2;
      } while (param_2 + (ulong)(iVar19 - 1) * 4 + 0x24 != pRVar15);
    }
    uVar21 = *(uint *)(param_1 + 0x94);
  default:
switchD_00be66be_caseD_0:
    break;
  case 0xf:
    if (iVar19 < 3) {
      if (iVar1 < (int)(uVar17 + uVar21 + 6)) {
        return 0x80000002;
      }
      uVar18 = *(uint *)(lVar20 + 2 + (long)(int)uVar21);
    }
    else {
      uVar23 = uVar21 & 1;
      iVar19 = uVar23 * 4;
      if (iVar1 < (int)((uVar21 >> 1) + 6 + uVar17 + iVar19)) {
        return 0x80000002;
      }
      puVar24 = (uint *)((ulong)((uVar21 >> 1) + 2) + lVar20);
      uVar18 = *puVar24 >> (sbyte)iVar19;
      uVar18 = (*(int *)((long)puVar24 + (long)iVar19) << (char)uVar23 * '\x1c' ^ uVar18) & -uVar23
               & 0xf0000000 ^ uVar18;
    }
    *(long *)(param_2 + 8) = lVar13;
    uVar10 = *(undefined4 *)(param_1 + 0xa0);
    *(uint *)(param_2 + 0x10) = uVar17 + uVar21;
    uVar2 = *(undefined4 *)(param_1 + 0xac);
    *(undefined4 *)(param_2 + 0x18) = uVar10;
    *(uint *)(param_2 + 0x2c) = uVar18;
    sVar6 = RgpGcnRegisterGetAddress(0x209,uVar2);
    *(undefined4 *)(param_2 + 0x24) = 1;
    *(undefined4 *)(param_2 + 0x38) = 0;
    *(ushort *)(param_2 + 0x28) = (uVar16 >> 9) + sVar6;
    *(undefined8 *)(param_2 + 0x30) = 0x100000000;
    *(ulong *)(param_2 + 0x1c) =
         (ulong)(CONCAT24(uVar16 >> 5,(uint)(uVar16 >> 7)) & 0xffff00000003) & 0x3ffffffff;
    uVar21 = *(uint *)(param_1 + 0x94);
  }
LAB_00be66f2:
  *(uint *)(param_1 + 0x94) = uVar21 + *(int *)(CSWTCH_425 + (ulong)uVar7 * 4);
  return 0;
}

