// function: RgpSqttParserAdvance @ 00be7c80

/* WARNING: Type propagation algorithm not settling */

undefined8
RgpSqttParserAdvance
          (RgpSqttParser *param_1,RgpSqttToken *param_2,RgpSqttParserPosition *param_3,bool param_4)

{
  RgpSqttParser *pRVar1;
  long *plVar2;
  long lVar3;
  char cVar4;
  byte bVar5;
  char cVar6;
  undefined2 uVar7;
  int iVar8;
  int iVar9;
  uint uVar10;
  byte *pbVar11;
  long lVar12;
  void *pvVar13;
  undefined8 uVar14;
  long *plVar15;
  ulong *puVar16;
  void *pvVar17;
  sbyte sVar18;
  long *plVar19;
  uint uVar20;
  uchar *puVar21;
  RgpSqttTokenRegister *pRVar22;
  size_t sVar23;
  ulong uVar24;
  uint uVar25;
  uint uVar26;
  int iVar27;
  uint uVar28;
  undefined4 uVar29;
  ulong uVar30;
  uchar uVar31;
  ulong uVar32;
  undefined4 uVar33;
  uint uVar34;
  long *plVar35;
  long lVar36;
  ulong uVar37;
  uint *puVar38;
  ulong uVar39;
  
  if (param_2 == (RgpSqttToken *)0x0) {
    return 0x80000000;
  }
  if (param_1 == (RgpSqttParser *)0x0) {
    return 0x80000000;
  }
  if (*(int *)(param_1 + 0xa4) == 2) {
    uVar14 = AdvanceParser2X(param_1,param_2,param_3);
    return uVar14;
  }
  if (*(int *)(param_1 + 0xa4) != 3) {
    return 0x8000000b;
  }
  uVar26 = *(uint *)(param_1 + 0x9c);
  uVar28 = *(uint *)(param_1 + 0x94);
  if (param_3 != (RgpSqttParserPosition *)0x0) {
    *(undefined4 *)(param_3 + 0x10) = *(undefined4 *)(param_1 + 0x28);
    uVar14 = *(undefined8 *)(param_1 + 0x18);
    *(ulong *)(param_3 + 8) = CONCAT44(uVar28,uVar26);
    *(undefined8 *)param_3 = uVar14;
  }
  uVar25 = uVar28 & 1;
  *(long *)(param_1 + 8) = *(long *)(param_1 + 8) + 1;
  if (*(int *)(param_1 + 0x90) < (int)((uVar28 >> 1) + 1 + uVar26 + uVar25)) {
    return 0x80000002;
  }
  pbVar11 = (byte *)((ulong)uVar26 + *(long *)(param_1 + 0x88) + (ulong)(uVar28 >> 1));
  sVar18 = (char)uVar25 * '\x04';
  uVar26 = (int)(uint)*pbVar11 >> sVar18;
  uVar26 = ((uint)pbVar11[(int)uVar25] << sVar18 ^ uVar26) & -uVar25 & 0xfffffff0 ^ uVar26;
  uVar31 = (uchar)uVar26;
  cVar4 = (char)param_2;
  if (2 < *(int *)(param_1 + 0xa8)) {
    uVar26 = DecodeTokenType3_3(uVar31);
    if (uVar26 < 0x72) {
      switch(uVar26) {
      case 1:
        uVar28 = uVar26;
        break;
      case 2:
      case 3:
        uVar28 = 10;
        break;
      case 4:
      case 0xd:
        uVar28 = 0xd;
        break;
      case 5:
        uVar28 = 4;
        break;
      case 6:
      case 0x46:
        uVar28 = 0x11;
        break;
      default:
        uVar28 = 0x16;
        break;
      case 9:
      case 0x71:
        uVar28 = 2;
        break;
      case 0xc:
        uVar28 = 3;
        break;
      case 0x11:
        uVar28 = 0x13;
        break;
      case 0x14:
        uVar28 = 0x10;
        break;
      case 0x15:
        uVar28 = 6;
        break;
      case 0x16:
      case 0x66:
        uVar28 = 0x15;
        break;
      case 0x21:
        uVar28 = 0xf;
        break;
      case 0x31:
        uVar28 = 0x14;
        break;
      case 0x51:
        uVar28 = 0;
        break;
      case 0x61:
        uVar28 = 7;
      }
    }
    else {
      uVar28 = 7;
      if (uVar26 != 0xe1) {
        uVar28 = 0x16;
      }
    }
    *(uint *)param_2 = uVar28;
    UpdateTimerState3_3(param_1,uVar31,param_4);
    lVar12 = **(long **)(*(long *)param_1 + 0xa219a0);
    if ((ulong)(((*(long **)(*(long *)param_1 + 0xa219a0))[1] - lVar12 >> 4) * -0x3333333333333333)
        <= (ulong)(long)*(int *)(param_1 + 0xa0)) {
                    /* WARNING: Subroutine does not return */
      std::__throw_out_of_range_fmt
                ("vector::_M_range_check: __n (which is %zu) >= this->size() (which is %zu)");
    }
    plVar19 = (long *)(lVar12 + (long)*(int *)(param_1 + 0xa0) * 0x50);
    puVar21 = (uchar *)plVar19[6];
    lVar12 = plVar19[2];
    if (puVar21 + (plVar19[4] - lVar12) +
                  (((plVar19[9] - plVar19[5] >> 3) + -1 + (ulong)(plVar19[9] == 0)) * 0x200 -
                  plVar19[7]) == (uchar *)0x3) {
      if (lVar12 == plVar19[4] + -1) {
        operator_delete((void *)plVar19[3],0x200);
        puVar21 = (uchar *)plVar19[6];
        lVar12 = *(long *)(plVar19[5] + 8);
        plVar19[2] = lVar12;
        plVar19[3] = lVar12;
        plVar19[4] = lVar12 + 0x200;
        plVar19[5] = plVar19[5] + 8;
      }
      else {
        lVar12 = lVar12 + 1;
        plVar19[2] = lVar12;
      }
    }
    if (puVar21 == (uchar *)(plVar19[8] + -1)) {
      plVar35 = (long *)plVar19[9];
      plVar2 = (long *)plVar19[5];
      lVar36 = (long)plVar35 - (long)plVar2;
      uVar32 = lVar36 >> 3;
      if (puVar21 + (plVar19[4] - lVar12) +
                    (((uVar32 - 1) + (ulong)(plVar35 == (long *)0x0)) * 0x200 - plVar19[7]) ==
          (uchar *)0x7fffffffffffffff) goto LAB_00bea137;
      uVar24 = plVar19[1];
      if (uVar24 - ((long)plVar35 - *plVar19 >> 3) < 2) {
        lVar12 = uVar32 + 2;
        if ((ulong)(lVar12 * 2) < uVar24) {
          plVar35 = plVar35 + 1;
          plVar15 = (long *)(*plVar19 + (uVar24 - lVar12 >> 1) * 8);
          sVar23 = (long)plVar35 - (long)plVar2;
          if (plVar15 < plVar2) {
            if (plVar2 != plVar35) {
              plVar15 = memmove(plVar15,plVar2,sVar23);
            }
          }
          else if (plVar2 != plVar35) {
            memmove((void *)(((lVar36 + 8) - sVar23) + (long)plVar15),plVar2,sVar23);
          }
        }
        else {
          uVar30 = 1;
          if (uVar24 != 0) {
            uVar30 = uVar24;
          }
          uVar30 = uVar24 + 2 + uVar30;
          if (uVar30 >> 0x3c != 0) goto LAB_00bea028;
          pvVar17 = operator_new(uVar30 * 8);
          pvVar13 = (void *)plVar19[5];
          plVar15 = (long *)((long)pvVar17 + (uVar30 - lVar12 >> 1) * 8);
          if ((void *)(plVar19[9] + 8) != pvVar13) {
            plVar15 = memmove(plVar15,pvVar13,(plVar19[9] + 8) - (long)pvVar13);
          }
          operator_delete((void *)*plVar19,plVar19[1] * 8);
          *plVar19 = (long)pvVar17;
          plVar19[1] = uVar30;
        }
        lVar3 = *plVar15;
        lVar12 = *plVar15;
        plVar35 = (long *)((long)plVar15 + lVar36);
        plVar19[5] = (long)plVar15;
        plVar19[9] = (long)plVar35;
        plVar19[3] = lVar12;
        plVar19[4] = lVar3 + 0x200;
        lVar12 = *plVar35;
        plVar19[7] = *plVar35;
        plVar19[8] = lVar12 + 0x200;
      }
      pvVar13 = operator_new(0x200);
      plVar35[1] = (long)pvVar13;
      *(uchar *)plVar19[6] = uVar31;
      lVar12 = *(long *)(plVar19[9] + 8);
      plVar19[9] = plVar19[9] + 8;
      plVar19[7] = lVar12;
      plVar19[8] = lVar12 + 0x200;
    }
    else {
      *puVar21 = uVar31;
      lVar12 = plVar19[6] + 1;
    }
    pRVar1 = *(RgpSqttParser **)param_1;
    plVar19[6] = lVar12;
    cVar6 = IsEndOfFileSignal(pRVar1);
    if (cVar6 != '\0') goto LAB_00be99c0;
    pRVar22 = *(RgpSqttTokenRegister **)(param_1 + 0x18);
    *(RgpSqttTokenRegister **)(param_1 + 0x10) = pRVar22;
    if (0x71 < uVar26) goto LAB_00be8020;
    if (uVar26 == 0) {
LAB_00be82ec:
                    /* WARNING: Could not recover jumptable at 0x00be82fd. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      uVar14 = (*(code *)(&DAT_00e563f8 + *(int *)(&DAT_00e563f8 + (ulong)uVar26 * 4)))();
      return uVar14;
    }
    switch(uVar26) {
    case 1:
      uVar29 = *(undefined4 *)(param_1 + 0xa0);
      iVar8 = *(int *)(param_1 + 0x90);
      *(RgpSqttTokenRegister **)(param_2 + 8) = pRVar22;
      uVar28 = *(uint *)(param_1 + 0x94);
      iVar27 = *(int *)(param_1 + 0xa4);
      *(undefined4 *)(param_2 + 0x18) = uVar29;
      uVar26 = *(uint *)(param_1 + 0x9c);
      *(uint *)(param_2 + 0x10) = uVar28;
      if (iVar27 < 3) {
        if (iVar8 < (int)(uVar28 + 8 + uVar26)) {
          return 0x80000002;
        }
        uVar32 = *(ulong *)((ulong)uVar26 + *(long *)(param_1 + 0x88) + (long)(int)uVar28);
      }
      else {
        if (iVar8 < (int)((uVar28 >> 1) + 8 + uVar26 + (uVar28 & 1))) {
          return 0x80000002;
        }
        puVar16 = (ulong *)((ulong)uVar26 + *(long *)(param_1 + 0x88) + (ulong)(uVar28 >> 1));
        uVar32 = *puVar16;
        if ((uVar28 & 1) != 0) {
          uVar32 = uVar32 >> 4 | (ulong)(byte)puVar16[1] << 0x3c;
        }
      }
      uVar29 = 0;
      uVar24 = 0xffffffffffffffff;
      if ((uVar32 & 0x80) != 0) {
        uVar29 = 3;
        uVar24 = uVar32 >> 0xc;
      }
      *(ulong *)(param_2 + 0x20) = uVar24;
      iVar8 = *(int *)(param_1 + 0x98);
      uVar26 = 0x10;
      *(undefined4 *)(param_2 + 0x28) = uVar29;
      iVar27 = iVar8 + 3;
      if (-1 < iVar8) {
        iVar27 = iVar8;
      }
      uVar28 = (iVar27 >> 2) + uVar28;
      break;
    case 2:
      goto switchD_00be7fee_caseD_2;
    case 3:
      goto switchD_00be7fee_caseD_3;
    case 4:
      goto switchD_00be7fee_caseD_4;
    case 5:
      uVar28 = *(uint *)(param_1 + 0x94);
      uVar26 = *(uint *)(param_1 + 0x9c);
      if (*(int *)(param_1 + 0xa4) < 3) {
        if (*(int *)(param_1 + 0x90) < (int)(uVar28 + 4 + uVar26)) {
          return 0x80000002;
        }
        uVar26 = *(uint *)((ulong)uVar26 + *(long *)(param_1 + 0x88) + (long)(int)uVar28);
      }
      else {
        iVar8 = (uVar28 & 1) * 4;
        if (*(int *)(param_1 + 0x90) < (int)((uVar28 >> 1) + 4 + uVar26 + iVar8)) {
          return 0x80000002;
        }
        uVar26 = *(uint *)((ulong)uVar26 + *(long *)(param_1 + 0x88) + (ulong)(uVar28 >> 1)) >>
                 (sbyte)iVar8;
      }
      *(RgpSqttTokenRegister **)(param_2 + 8) = pRVar22;
      uVar29 = *(undefined4 *)(param_1 + 0xa0);
      *(uint *)(param_2 + 0x10) = uVar28;
      uVar25 = uVar26 >> 0xf & 0x1f;
      uVar20 = uVar26 >> 0x14 & 7;
      *(ulong *)(param_2 + 0x18) = CONCAT44(uVar26 >> 8,uVar29) & 0x1ffffffff;
      *(ulong *)(param_2 + 0x20) = CONCAT44(uVar26 >> 9,uVar26 >> 0xb) & 0x30000000f;
      iVar8 = *(int *)(param_1 + 0x98);
      *(uint *)(param_2 + 0x30) = uVar20;
      iVar27 = iVar8 + 3;
      if (-1 < iVar8) {
        iVar27 = iVar8;
      }
      uVar28 = (iVar27 >> 2) + uVar28;
      if ((0x12UL >> uVar20 & 1) == 0) {
        *(uint *)(param_2 + 0x28) = uVar25;
        uVar26 = 6;
      }
      else {
        *(uint *)(param_2 + 0x2c) = uVar25;
        uVar26 = 6;
      }
      break;
    case 6:
      uVar14 = ParseShaderData3_3(param_1,(RgpSqttTokenShaderData *)(param_2 + 8),false);
      if ((int)uVar14 != 0) {
        return uVar14;
      }
      iVar8 = *(int *)(param_1 + 0x98);
      uVar26 = 0xe;
      iVar27 = iVar8 + 3;
      if (-1 < iVar8) {
        iVar27 = iVar8;
      }
      uVar28 = (iVar27 >> 2) + *(int *)(param_1 + 0x94);
      break;
    default:
      if (0x71 < uVar26) {
        return 0x80000006;
      }
      goto LAB_00be82ec;
    case 9:
      uVar14 = ParseReg3X(param_1,cVar4 + '\b',pRVar22);
      goto LAB_00be92b9;
    case 0xc:
      iVar8 = *(int *)(param_1 + 0xa4);
      uVar28 = *(uint *)(param_1 + 0x94);
      uVar25 = *(uint *)(param_1 + 0x9c);
      uVar32 = (ulong)uVar25;
      uVar20 = *(uint *)(param_1 + 0x90);
      if (iVar8 < 3) {
        if ((int)uVar20 < (int)(uVar28 + 4 + uVar25)) {
          return 0x80000002;
        }
        uVar34 = *(uint *)(*(long *)(param_1 + 0x88) + uVar32 + (long)(int)uVar28);
      }
      else {
        uVar26 = uVar28 & 1;
        iVar27 = uVar26 * 4;
        if ((int)uVar20 < (int)((uVar28 >> 1) + 4 + uVar25 + iVar27)) {
          return 0x80000002;
        }
        puVar38 = (uint *)(*(long *)(param_1 + 0x88) + uVar32 + (ulong)(uVar28 >> 1));
        uVar34 = *puVar38 >> (sbyte)iVar27;
        uVar34 = (*(int *)((long)puVar38 + (long)iVar27) << (char)uVar26 * '\x1c' ^ uVar34) &
                 -uVar26 & 0xf0000000 ^ uVar34;
      }
      *(RgpSqttTokenRegister **)(param_2 + 8) = pRVar22;
      uVar33 = 2;
      uVar29 = *(undefined4 *)(param_1 + 0xa0);
      *(uint *)(param_2 + 0x10) = uVar28;
      uVar10 = uVar34 >> 0x19;
      uVar26 = uVar10;
      if (0x5e < uVar10) {
        uVar26 = uVar10 - 0x5f;
        uVar33 = 1;
      }
      *(uint *)(param_2 + 0x28) = uVar34 >> 0xf & 0x1f;
      *(undefined4 *)(param_2 + 0x40) = uVar33;
      *(uint *)(param_2 + 0x3c) = uVar26;
      *(ulong *)(param_2 + 0x18) = CONCAT44(uVar34 >> 7,uVar29) & 0x1ffffffff;
      *(ulong *)(param_2 + 0x20) = CONCAT44(uVar34 >> 8,uVar34 >> 10) & 0x30000000f;
      if ((uVar34 & 0x1000000) == 0) {
        *(undefined4 *)(param_2 + 0x2c) = 6;
        *(undefined4 *)(param_2 + 0x38) = 0;
        *(ulong *)(param_2 + 0x30) =
             CONCAT44(uVar34 >> 0x14,((uVar34 & 0x400000) == 0) + 1) & 0x3ffffffff;
      }
      else {
        *(undefined4 *)(param_2 + 0x30) = 0;
        *(undefined4 *)(param_2 + 0x38) = 0;
        *(uint *)(param_2 + 0x34) = uVar34 >> 0x17 & 1;
        switch(uVar34 >> 0x14 & 7) {
        case 0:
          *(undefined4 *)(param_2 + 0x2c) = 0;
          break;
        case 1:
          *(undefined4 *)(param_2 + 0x2c) = 7;
          break;
        case 2:
          *(undefined4 *)(param_2 + 0x2c) = 8;
          break;
        case 3:
          *(undefined4 *)(param_2 + 0x2c) = 9;
          break;
        case 4:
          *(undefined4 *)(param_2 + 0x2c) = 2;
          break;
        case 5:
          *(undefined4 *)(param_2 + 0x2c) = 4;
          break;
        case 6:
          *(undefined4 *)(param_2 + 0x2c) = 6;
          break;
        default:
          *(undefined4 *)(param_2 + 0x2c) = 0xb;
        }
      }
      uVar26 = 8;
      if ((uVar10 - 0x46 < 4) || (*(undefined2 *)(param_2 + 0x50) = 0, (uVar34 & 0x10) == 0)) break;
      if (iVar8 < 3) goto LAB_00bea037;
      if ((int)((uVar28 >> 1) + 6 + uVar25 + (uVar28 & 1)) <= (int)uVar20) {
        lVar12 = uVar32 + *(long *)(param_1 + 0x88) + (ulong)(uVar28 >> 1);
        uVar32 = (ulong)*(byte *)(lVar12 + 5) << 0x28 | (ulong)*(byte *)(lVar12 + 4) << 0x20;
        if ((uVar28 & 1) != 0) {
          uVar32 = (uVar32 | ((ulong)*(byte *)(lVar12 + 6) & 0xf) << 0x30) >> 4;
        }
        goto LAB_00be906a;
      }
LAB_00bea10c:
      iVar8 = *(int *)(param_1 + 0xc0);
      if (iVar8 != 2) {
        uVar25 = 0;
LAB_00be9079:
        if (iVar8 == 3) {
          uVar28 = uVar28 + 2;
          uVar26 = 8;
          param_2[0x4a] = (RgpSqttToken)((byte)(uVar25 >> 7) & 1);
          break;
        }
        if (iVar8 == 1) {
          uVar28 = uVar28 + 4;
          uVar26 = 8;
          param_2[0x4a] = SUB41(uVar25 >> 0xf,0);
          *(ushort *)(param_2 + 0x50) = CONCAT11((char)(uVar25 >> 8),(char)(uVar25 >> 1)) & 0xff7f;
          break;
        }
      }
LAB_00be908b:
      uVar26 = 8;
      uVar28 = uVar28 + *(int *)(param_1 + 0x98) / 4;
      break;
    case 0xd:
      goto switchD_00be7fee_caseD_d;
    case 0x11:
      uVar26 = *(uint *)(param_1 + 0x94);
      uVar28 = *(uint *)(param_1 + 0x9c);
      if (*(int *)(param_1 + 0xa4) < 3) {
        if (*(int *)(param_1 + 0x90) < (int)(uVar26 + 8 + uVar28)) {
          return 0x80000002;
        }
        uVar32 = *(ulong *)((ulong)uVar28 + *(long *)(param_1 + 0x88) + (long)(int)uVar26);
      }
      else {
        if (*(int *)(param_1 + 0x90) < (int)((uVar26 >> 1) + 8 + uVar28 + (uVar26 & 1))) {
          return 0x80000002;
        }
        puVar16 = (ulong *)((ulong)uVar28 + *(long *)(param_1 + 0x88) + (ulong)(uVar26 >> 1));
        uVar32 = *puVar16;
        if ((uVar26 & 1) != 0) {
          uVar32 = uVar32 >> 4 | (ulong)(byte)puVar16[1] << 0x3c;
        }
      }
      *(ulong *)(param_1 + 0xb8) = uVar32;
      iVar8 = 0;
      uVar26 = (uint)(uVar32 >> 0x20);
      *(undefined4 *)(param_2 + 0x18) = *(undefined4 *)(param_1 + 0xa0);
      param_2[0x1c] = (RgpSqttToken)((byte)(uVar26 >> 1) & 3);
      if ((uVar32 >> 0x1c & 7) != 0) {
        iVar8 = 1 << (((byte)(uVar32 >> 0x1c) & 7) - 1 & 0x1f);
      }
      *(int *)(param_2 + 0x20) = iVar8;
      uVar24 = DAT_00e56668;
      *(ushort *)(param_2 + 0x24) = (-(ushort)((uVar32 & 0x8000000) == 0) & 0xff80) + 0x100;
      *(ushort *)(param_2 + 0x26) = CONCAT11((char)(uVar32 >> 0xf),(char)(uVar32 >> 0xd)) & 0xf03;
      param_2[0x28] = (RgpSqttToken)((byte)(uVar32 >> 0x13) & 1);
      *(uint *)(param_2 + 0x2c) = (uint)(uVar32 >> 0x19) & 3;
      *(ulong *)(param_2 + 0x30) =
           uVar24 & ((((((((ulong)(uVar26 >> 8 & 0xff00) | uVar32 >> 0x2f & 0xff) << 8 |
                         uVar32 >> 0x2c & 0xff) << 8 | uVar32 >> 0x2b & 0xff) << 8 |
                       uVar32 >> 0x2a & 0xff) << 8 | uVar32 >> 0x29 & 0xff) << 8 |
                     uVar32 >> 0x25 & 0xff) << 8 | uVar32 >> 0x23 & 0xff);
      *(uint *)(param_2 + 0x38) =
           (uint)(CONCAT11((char)(uVar26 >> 0x12),(char)(uVar26 >> 0x11)) & 0x101) |
           (uVar26 >> 0x13 & 1) << 0x10 | (uVar26 >> 0x14 & 1) << 0x18;
      *(ushort *)(param_2 + 0x3c) = CONCAT11((char)(uVar26 >> 0x16),(char)(uVar26 >> 0x15)) & 0x101;
      bVar5 = (byte)(uVar32 >> 0x38);
      *(ushort *)(param_2 + 0x40) = CONCAT11(bVar5 >> 2,bVar5 >> 1) & 0x101;
      uVar26 = uVar26 >> 0x17 & 3;
      param_2[0x42] = (RgpSqttToken)(bVar5 >> 3 & 1);
      RgpAsicParametersGetDetailedCuIdForShaderEngine(*(undefined8 *)param_1);
      uVar7 = 0x600;
      if (((uVar26 != 2) && (uVar7 = 0x800, uVar26 != 3)) && (uVar7 = 0x400, uVar26 == 1)) {
        uVar7 = 0x500;
      }
      *(undefined2 *)(param_2 + 0x3e) = uVar7;
      *(undefined4 *)(param_1 + 0xc0) = *(undefined4 *)(param_2 + 0x2c);
      goto LAB_00be8660;
    case 0x14:
      goto switchD_00be7fee_caseD_14;
    case 0x15:
      uVar28 = *(uint *)(param_1 + 0x94);
      uVar26 = *(uint *)(param_1 + 0x9c);
      if (*(int *)(param_1 + 0xa4) < 3) {
        if (*(int *)(param_1 + 0x90) < (int)(uVar28 + 4 + uVar26)) {
          return 0x80000002;
        }
        uVar25 = *(uint *)((ulong)uVar26 + *(long *)(param_1 + 0x88) + (long)(int)uVar28);
      }
      else {
        iVar8 = (uVar28 & 1) * 4;
        if (*(int *)(param_1 + 0x90) < (int)((uVar28 >> 1) + 4 + uVar26 + iVar8)) {
          return 0x80000002;
        }
        uVar25 = *(uint *)((ulong)uVar26 + *(long *)(param_1 + 0x88) + (ulong)(uVar28 >> 1)) >>
                 (sbyte)iVar8;
      }
      *(RgpSqttTokenRegister **)(param_2 + 8) = pRVar22;
      uVar29 = *(undefined4 *)(param_1 + 0xa0);
      *(uint *)(param_2 + 0x10) = uVar28;
      uVar32 = CONCAT44(uVar25 >> 8,uVar29);
      uVar24 = CONCAT44(uVar25 >> 9,uVar25 >> 0xb) & 0x30000000f;
      goto LAB_00be87b0;
    case 0x16:
      uVar28 = *(uint *)(param_1 + 0x94);
      uVar29 = *(undefined4 *)(param_1 + 0xa0);
      *(RgpSqttTokenRegister **)(param_2 + 8) = pRVar22;
      iVar8 = *(int *)(param_1 + 0xa4);
      *(undefined4 *)(param_2 + 0x1c) = 0;
      *(undefined4 *)(param_2 + 0x18) = uVar29;
      iVar27 = *(int *)(param_1 + 0x90);
      *(uint *)(param_2 + 0x10) = uVar28;
      uVar26 = *(uint *)(param_1 + 0x9c);
      param_2[0x20] = (RgpSqttToken)0x0;
      if (iVar8 < 3) {
        if (iVar27 < (int)(uVar28 + 6 + uVar26)) {
          return 0x80000002;
        }
        lVar12 = (long)(int)uVar28 + (ulong)uVar26 + *(long *)(param_1 + 0x88);
        uVar32 = (ulong)*(byte *)(lVar12 + 5) << 0x28 | (ulong)*(byte *)(lVar12 + 4) << 0x20 |
                 (ulong)*(byte *)(lVar12 + 3) << 0x18 | (ulong)*(byte *)(lVar12 + 2) << 0x10 |
                 (ulong)*(byte *)(lVar12 + 1) << 8;
      }
      else {
        if (iVar27 < (int)((uVar28 >> 1) + 6 + uVar26 + (uVar28 & 1))) {
          return 0x80000002;
        }
        lVar12 = (ulong)uVar26 + *(long *)(param_1 + 0x88) + (ulong)(uVar28 >> 1);
        uVar24 = (ulong)*(byte *)(lVar12 + 5) << 0x28;
        uVar30 = (ulong)*(byte *)(lVar12 + 4) << 0x20;
        uVar37 = (ulong)*(byte *)(lVar12 + 3) << 0x18;
        uVar39 = (ulong)*(byte *)(lVar12 + 2) << 0x10;
        uVar32 = (ulong)*(byte *)(lVar12 + 1) << 8;
        if ((uVar28 & 1) == 0) {
          uVar32 = uVar24 | uVar30 | uVar37 | uVar39 | uVar32;
        }
        else {
          uVar32 = (uVar24 | uVar30 | uVar37 | uVar39 | uVar32 |
                   ((ulong)*(byte *)(lVar12 + 6) & 0xf) << 0x30) >> 4;
        }
      }
      uVar26 = 0xc;
      *(uint *)(param_2 + 0x24) = (uint)(uVar32 >> 9) & 0x1f;
      param_2[0x33] = (RgpSqttToken)((byte)(uVar32 >> 0x15) & 1);
      *(uint *)(param_2 + 0x28) = (uint)(uVar32 >> 0x16) & 0x1f;
      *(ushort *)(param_2 + 0x30) = CONCAT11((char)(uVar32 >> 0x1b),(char)(uVar32 >> 0xe)) & 0x7f7f;
      uVar25 = (uint)(uVar32 >> 0x20);
      param_2[0x34] = (RgpSqttToken)((byte)(uVar25 >> 2) & 1);
      *(uint *)(param_2 + 0x2c) = uVar25 >> 3 & 0x1f;
      param_2[0x35] = SUB41(uVar25 >> 0xf,0);
      param_2[0x32] = (RgpSqttToken)((byte)(uVar32 >> 0x28) & 0x7f);
      iVar8 = *(int *)(param_1 + 0x98);
      iVar27 = iVar8 + 3;
      if (-1 < iVar8) {
        iVar27 = iVar8;
      }
      uVar28 = (iVar27 >> 2) + uVar28;
      break;
    case 0x21:
      uVar14 = ParseNewPc3X(param_1,cVar4 + '\b',(RgpSqttTokenNewProgramCounter *)pRVar22);
      if ((int)uVar14 != 0) {
        return uVar14;
      }
      iVar8 = *(int *)(param_1 + 0x98);
      uVar26 = 0x12;
      iVar27 = iVar8 + 3;
      if (-1 < iVar8) {
        iVar27 = iVar8;
      }
      uVar28 = (iVar27 >> 2) + *(int *)(param_1 + 0x94);
      break;
    case 0x31:
      uVar14 = ParseUtilCtr3X(param_1,(RgpSqttTokenUtilCtr *)(param_2 + 8));
      if ((int)uVar14 != 0) {
        return uVar14;
      }
      iVar8 = *(int *)(param_1 + 0x98);
      uVar26 = 0xc;
      iVar27 = iVar8 + 3;
      if (-1 < iVar8) {
        iVar27 = iVar8;
      }
      uVar28 = (iVar27 >> 2) + *(int *)(param_1 + 0x94);
      break;
    case 0x46:
      uVar14 = ParseShaderData3_3(param_1,(RgpSqttTokenShaderData *)(param_2 + 8),true);
      iVar8 = (int)uVar14;
      goto joined_r0x00be803b;
    case 0x51:
      goto switchD_00be7fee_caseD_51;
    case 0x61:
      goto switchD_00be7fee_caseD_61;
    case 0x66:
      uVar29 = *(undefined4 *)(param_1 + 0xa0);
      *(RgpSqttTokenRegister **)(param_2 + 8) = pRVar22;
      uVar28 = *(uint *)(param_1 + 0x94);
      iVar8 = *(int *)(param_1 + 0xa4);
      *(undefined4 *)(param_2 + 0x1c) = 0;
      *(undefined4 *)(param_2 + 0x18) = uVar29;
      iVar27 = *(int *)(param_1 + 0x90);
      *(uint *)(param_2 + 0x10) = uVar28;
      uVar26 = *(uint *)(param_1 + 0x9c);
      param_2[0x20] = (RgpSqttToken)0x1;
      if (iVar8 < 3) {
        if (iVar27 < (int)(uVar28 + 4 + uVar26)) {
          return 0x80000002;
        }
        uVar25 = *(uint *)((ulong)uVar26 + *(long *)(param_1 + 0x88) + (long)(int)uVar28);
      }
      else {
        iVar8 = (uVar28 & 1) * 4;
        if (iVar27 < (int)((uVar28 >> 1) + 4 + uVar26 + iVar8)) {
          return 0x80000002;
        }
        uVar25 = *(uint *)((ulong)uVar26 + *(long *)(param_1 + 0x88) + (ulong)(uVar28 >> 1)) >>
                 (sbyte)iVar8;
      }
      uVar26 = 6;
      *(uint *)(param_2 + 0x24) = uVar25 >> 10 & 0x1f;
      param_2[0x33] = (RgpSqttToken)((byte)(uVar25 >> 0x16) & 1);
      param_2[0x30] = (RgpSqttToken)((byte)(uVar25 >> 0xf) & 0x7f);
      iVar8 = *(int *)(param_1 + 0x98);
      iVar27 = iVar8 + 3;
      if (-1 < iVar8) {
        iVar27 = iVar8;
      }
      uVar28 = (iVar27 >> 2) + uVar28;
      break;
    case 0x71:
      uVar14 = ParseRegInitiator3X(param_1,cVar4 + '\b',pRVar22);
LAB_00be92b9:
      iVar8 = (int)uVar14;
      goto joined_r0x00be8658;
    }
    goto LAB_00be8060;
  }
  uVar28 = uVar26 & 0xf;
  if ((char)uVar28 == '\x01') {
    if (uVar31 != 'a') {
      if (uVar31 != 0xe1) {
        uVar39 = (ulong)(uVar26 & 0x7f);
        goto LAB_00be7ffb;
      }
      uVar39 = 0xe1;
      goto switchD_00be8016_caseD_61;
    }
    uVar39 = 0x61;
    uVar29 = 7;
  }
  else {
    uVar39 = (ulong)(uVar26 & 7);
    if ((1 < (byte)((char)(uVar26 & 7) - 2U)) &&
       (uVar39 = (ulong)(uVar26 & 0x1f), 2 < (byte)((char)uVar28 - 4U))) {
      uVar39 = 0;
      uVar29 = 0x16;
      if ((0xf381UL >> uVar28 & 1) == 0) goto LAB_00be7de0;
      uVar39 = (ulong)uVar28;
    }
LAB_00be7ffb:
    uVar29 = (undefined4)uVar39;
    switch(uVar39) {
    default:
      uVar29 = 0x16;
      break;
    case 1:
    case 0xd:
      break;
    case 2:
    case 3:
      uVar29 = 10;
      break;
    case 4:
      uVar29 = 0xd;
      break;
    case 5:
      uVar29 = 4;
      break;
    case 6:
    case 0x16:
      uVar29 = 0x11;
      break;
    case 9:
    case 0x71:
      uVar29 = 2;
      break;
    case 0xc:
      uVar29 = 3;
      break;
    case 0x11:
      uVar29 = 0x13;
      break;
    case 0x14:
      uVar29 = 0x10;
      break;
    case 0x15:
      uVar29 = 6;
      break;
    case 0x21:
      uVar29 = 0xf;
      break;
    case 0x31:
      uVar29 = 0x14;
      break;
    case 0x51:
      uVar29 = 0;
      break;
    case 0x61:
switchD_00be8016_caseD_61:
      uVar29 = 7;
    }
  }
LAB_00be7de0:
  uVar26 = (uint)uVar39;
  *(undefined4 *)param_2 = uVar29;
  UpdateTimerState3X(param_1,uVar31);
  lVar12 = **(long **)(*(long *)param_1 + 0xa219a0);
  if ((ulong)(((*(long **)(*(long *)param_1 + 0xa219a0))[1] - lVar12 >> 4) * -0x3333333333333333) <=
      (ulong)(long)*(int *)(param_1 + 0xa0)) {
                    /* WARNING: Subroutine does not return */
    std::__throw_out_of_range_fmt
              ("vector::_M_range_check: __n (which is %zu) >= this->size() (which is %zu)");
  }
  plVar19 = (long *)(lVar12 + (long)*(int *)(param_1 + 0xa0) * 0x50);
  puVar21 = (uchar *)plVar19[6];
  lVar12 = plVar19[2];
  if (puVar21 + (plVar19[4] - lVar12) +
                (((plVar19[9] - plVar19[5] >> 3) + -1 + (ulong)(plVar19[9] == 0)) * 0x200 -
                plVar19[7]) == (uchar *)0x3) {
    if (lVar12 == plVar19[4] + -1) {
      operator_delete((void *)plVar19[3],0x200);
      puVar21 = (uchar *)plVar19[6];
      lVar12 = *(long *)(plVar19[5] + 8);
      plVar19[2] = lVar12;
      plVar19[3] = lVar12;
      plVar19[4] = lVar12 + 0x200;
      plVar19[5] = plVar19[5] + 8;
    }
    else {
      lVar12 = lVar12 + 1;
      plVar19[2] = lVar12;
    }
  }
  if (puVar21 == (uchar *)(plVar19[8] + -1)) {
    plVar35 = (long *)plVar19[9];
    plVar2 = (long *)plVar19[5];
    lVar36 = (long)plVar35 - (long)plVar2;
    uVar32 = lVar36 >> 3;
    if (puVar21 + (plVar19[4] - lVar12) +
                  (((uVar32 - 1) + (ulong)(plVar35 == (long *)0x0)) * 0x200 - plVar19[7]) ==
        (uchar *)0x7fffffffffffffff) {
LAB_00bea137:
                    /* WARNING: Subroutine does not return */
      std::__throw_length_error("cannot create std::deque larger than max_size()");
    }
    uVar24 = plVar19[1];
    if (uVar24 - ((long)plVar35 - *plVar19 >> 3) < 2) {
      lVar12 = uVar32 + 2;
      if ((ulong)(lVar12 * 2) < uVar24) {
        plVar35 = plVar35 + 1;
        plVar15 = (long *)(*plVar19 + (uVar24 - lVar12 >> 1) * 8);
        sVar23 = (long)plVar35 - (long)plVar2;
        if (plVar15 < plVar2) {
          if (plVar2 != plVar35) {
            plVar15 = memmove(plVar15,plVar2,sVar23);
          }
        }
        else if (plVar2 != plVar35) {
          memmove((void *)(((lVar36 + 8) - sVar23) + (long)plVar15),plVar2,sVar23);
        }
      }
      else {
        uVar30 = 1;
        if (uVar24 != 0) {
          uVar30 = uVar24;
        }
        uVar30 = uVar24 + 2 + uVar30;
        if (uVar30 >> 0x3c != 0) {
LAB_00bea028:
          uVar28 = (uint)uVar24;
          uVar25 = (uint)lVar36;
          uVar20 = (uint)(uVar30 >> 0x3d);
          if (uVar30 >> 0x3d == 0) {
                    /* WARNING: Subroutine does not return */
            std::__throw_bad_alloc();
          }
          std::__throw_bad_array_new_length();
LAB_00bea037:
          if ((int)uVar20 < (int)(uVar28 + 6 + uVar25)) goto LAB_00bea10c;
          lVar12 = uVar32 + *(long *)(param_1 + 0x88) + (long)(int)uVar28;
          uVar32 = (ulong)*(byte *)(lVar12 + 5) << 0x28 | (ulong)*(byte *)(lVar12 + 4) << 0x20;
LAB_00be906a:
          uVar25 = (uint)(uVar32 >> 0x20);
          iVar8 = *(int *)(param_1 + 0xc0);
          if (iVar8 != 2) goto LAB_00be9079;
          if (uVar32 >> 0x20 != 0) {
            uVar28 = uVar28 + 4;
            uVar26 = 8;
            goto LAB_00be8060;
          }
          goto LAB_00be908b;
        }
        pvVar17 = operator_new(uVar30 * 8);
        pvVar13 = (void *)plVar19[5];
        plVar15 = (long *)((long)pvVar17 + (uVar30 - lVar12 >> 1) * 8);
        if ((void *)(plVar19[9] + 8) != pvVar13) {
          plVar15 = memmove(plVar15,pvVar13,(plVar19[9] + 8) - (long)pvVar13);
        }
        operator_delete((void *)*plVar19,plVar19[1] * 8);
        *plVar19 = (long)pvVar17;
        plVar19[1] = uVar30;
      }
      lVar3 = *plVar15;
      lVar12 = *plVar15;
      plVar35 = (long *)((long)plVar15 + lVar36);
      plVar19[5] = (long)plVar15;
      plVar19[9] = (long)plVar35;
      plVar19[3] = lVar12;
      plVar19[4] = lVar3 + 0x200;
      lVar12 = *plVar35;
      plVar19[7] = *plVar35;
      plVar19[8] = lVar12 + 0x200;
    }
    pvVar13 = operator_new(0x200);
    plVar35[1] = (long)pvVar13;
    *(uchar *)plVar19[6] = uVar31;
    lVar12 = *(long *)(plVar19[9] + 8);
    plVar19[9] = plVar19[9] + 8;
    plVar19[7] = lVar12;
    plVar19[8] = lVar12 + 0x200;
  }
  else {
    *puVar21 = uVar31;
    lVar12 = plVar19[6] + 1;
  }
  pRVar1 = *(RgpSqttParser **)param_1;
  plVar19[6] = lVar12;
  cVar6 = IsEndOfFileSignal(pRVar1);
  if (cVar6 != '\0') {
LAB_00be99c0:
    if (param_4 != false) {
      pbVar11 = (byte *)(*(long *)(*(long *)param_1 + 0x7a8) + 0x91589);
      *pbVar11 = *pbVar11 | (byte)(1 << ((byte)*(undefined4 *)(param_1 + 0xa0) & 0x1f));
      return 0x80000003;
    }
    return 0x80000003;
  }
  pRVar22 = *(RgpSqttTokenRegister **)(param_1 + 0x18);
  *(RgpSqttTokenRegister **)(param_1 + 0x10) = pRVar22;
  if (0x71 < uVar26) {
LAB_00be8020:
    if (uVar26 != 0xe1) {
      return 0x80000006;
    }
    uVar14 = ParseEventSync3X(param_1,cVar4 + '\b',(RgpSqttTokenEvent *)pRVar22);
    iVar8 = (int)uVar14;
joined_r0x00be803b:
    if (iVar8 != 0) {
      return uVar14;
    }
    iVar8 = *(int *)(param_1 + 0x98);
    uVar26 = 8;
    iVar27 = iVar8 + 3;
    if (-1 < iVar8) {
      iVar27 = iVar8;
    }
    uVar28 = (iVar27 >> 2) + *(int *)(param_1 + 0x94);
    goto LAB_00be8060;
  }
  if (uVar26 == 0) {
LAB_00be82c2:
                    /* WARNING: Could not recover jumptable at 0x00be82d3. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar14 = (*(code *)((long)&DAT_00e56230 + (long)(int)(&DAT_00e56230)[uVar39]))();
    return uVar14;
  }
  switch(uVar39) {
  case 1:
    iVar8 = *(int *)(param_1 + 0xa8);
    uVar28 = *(uint *)(param_1 + 0x94);
    uVar29 = *(undefined4 *)(param_1 + 0xa0);
    iVar27 = *(int *)(param_1 + 0xa4);
    uVar26 = *(uint *)(param_1 + 0x9c);
    uVar32 = (ulong)uVar26;
    iVar9 = *(int *)(param_1 + 0x90);
    *(RgpSqttTokenRegister **)(param_2 + 8) = pRVar22;
    *(uint *)(param_2 + 0x10) = uVar28;
    *(undefined4 *)(param_2 + 0x18) = uVar29;
    if (iVar8 < 1) {
      if (iVar27 < 3) {
        if (iVar9 < (int)(uVar28 + 8 + uVar26)) {
          return 0x80000002;
        }
        uVar32 = *(ulong *)(uVar32 + *(long *)(param_1 + 0x88) + (long)(int)uVar28);
      }
      else {
        if (iVar9 < (int)((uVar28 >> 1) + 8 + uVar26 + (uVar28 & 1))) {
          return 0x80000002;
        }
        puVar16 = (ulong *)((ulong)uVar26 + *(long *)(param_1 + 0x88) + (ulong)(uVar28 >> 1));
        uVar32 = *puVar16;
        if ((uVar28 & 1) != 0) {
          uVar32 = uVar32 >> 4 | (ulong)(byte)puVar16[1] << 0x3c;
        }
      }
      uVar24 = uVar32 >> 0x10;
      uVar26 = (uint)(uVar32 >> 0xe) & 3;
      *(uint *)(param_2 + 0x28) = uVar26;
    }
    else {
      if (iVar27 < 3) {
        if (iVar9 < (int)(uVar28 + 6 + uVar26)) {
          return 0x80000002;
        }
        lVar12 = (long)(int)uVar28 + uVar32 + *(long *)(param_1 + 0x88);
        uVar32 = (ulong)*(byte *)(lVar12 + 5) << 0x28 | (ulong)*(byte *)(lVar12 + 4) << 0x20 |
                 (ulong)*(byte *)(lVar12 + 3) << 0x18 | (ulong)*(byte *)(lVar12 + 2) << 0x10 |
                 (ulong)*(byte *)(lVar12 + 1) << 8;
      }
      else {
        if (iVar9 < (int)((uVar28 >> 1) + 6 + uVar26 + (uVar28 & 1))) {
          return 0x80000002;
        }
        lVar12 = uVar32 + *(long *)(param_1 + 0x88) + (ulong)(uVar28 >> 1);
        uVar32 = (ulong)*(byte *)(lVar12 + 5) << 0x28 | (ulong)*(byte *)(lVar12 + 4) << 0x20 |
                 (ulong)*(byte *)(lVar12 + 3) << 0x18 | (ulong)*(byte *)(lVar12 + 2) << 0x10 |
                 (ulong)*(byte *)(lVar12 + 1) << 8;
        if ((uVar28 & 1) != 0) {
          uVar32 = (uVar32 | ((ulong)*(byte *)(lVar12 + 6) & 0xf) << 0x30) >> 4;
        }
      }
      uVar24 = uVar32 >> 0xc;
      uVar26 = (uint)(uVar32 >> 8) & 3;
      *(uint *)(param_2 + 0x28) = uVar26;
    }
    if (uVar26 != 2) {
      uVar24 = 0xffffffffffffffff;
    }
    *(ulong *)(param_2 + 0x20) = uVar24;
    goto LAB_00be8d1a;
  case 2:
switchD_00be7fee_caseD_2:
    uVar14 = ParseInst3X(param_1,cVar4 + '\b',(RgpSqttTokenInstruction *)pRVar22);
    if ((int)uVar14 != 0) {
      return uVar14;
    }
    iVar8 = *(int *)(param_1 + 0x98);
    uVar26 = 5;
    iVar27 = iVar8 + 3;
    if (-1 < iVar8) {
      iVar27 = iVar8;
    }
    uVar28 = (iVar27 >> 2) + *(int *)(param_1 + 0x94);
    break;
  case 3:
switchD_00be7fee_caseD_3:
    uVar14 = ParseValuInst3X(param_1,uVar31,(RgpSqttTokenInstruction *)(param_2 + 8));
    iVar8 = (int)uVar14;
    goto joined_r0x00be8595;
  case 4:
switchD_00be7fee_caseD_4:
    uVar14 = ParseImmediate3X(param_1,uVar31,(RgpSqttTokenIssue *)(param_2 + 8));
    iVar8 = (int)uVar14;
    goto joined_r0x00be85ae;
  case 5:
    uVar28 = *(uint *)(param_1 + 0x94);
    uVar25 = *(uint *)(param_1 + 0x9c);
    if (*(int *)(param_1 + 0xa4) < 3) {
      if (*(int *)(param_1 + 0x90) < (int)(uVar28 + 4 + uVar25)) {
        return 0x80000002;
      }
      uVar25 = *(uint *)((ulong)uVar25 + *(long *)(param_1 + 0x88) + (long)(int)uVar28);
    }
    else {
      iVar8 = (uVar28 & 1) * 4;
      if (*(int *)(param_1 + 0x90) < (int)((uVar28 >> 1) + 4 + uVar25 + iVar8)) {
        return 0x80000002;
      }
      uVar25 = *(uint *)((ulong)uVar25 + *(long *)(param_1 + 0x88) + (ulong)(uVar28 >> 1)) >>
               (sbyte)iVar8;
    }
    *(RgpSqttTokenRegister **)(param_2 + 8) = pRVar22;
    uVar29 = *(undefined4 *)(param_1 + 0xa0);
    *(uint *)(param_2 + 0x10) = uVar28;
    *(uint *)(param_2 + 0x28) = uVar25 >> 0xf & 0x1f;
    *(ulong *)(param_2 + 0x18) = CONCAT44(uVar25 >> 8,uVar29) & 0x1ffffffff;
    *(ulong *)(param_2 + 0x20) = CONCAT44(uVar25 >> 9,uVar25 >> 0xb) & 0x300000007;
    iVar8 = *(int *)(param_1 + 0x98);
    iVar27 = iVar8 + 3;
    if (-1 < iVar8) {
      iVar27 = iVar8;
    }
    uVar28 = (iVar27 >> 2) + uVar28;
    break;
  case 6:
    uVar14 = ParseShaderData3_1(param_1,(RgpSqttTokenShaderData *)(param_2 + 8),false);
    if ((int)uVar14 != 0) {
      return uVar14;
    }
    iVar8 = *(int *)(param_1 + 0x98);
    uVar26 = 0xd;
    iVar27 = iVar8 + 3;
    if (-1 < iVar8) {
      iVar27 = iVar8;
    }
    uVar28 = (iVar27 >> 2) + *(int *)(param_1 + 0x94);
    break;
  default:
    if (0x71 < uVar26) {
      return 0x80000006;
    }
    goto LAB_00be82c2;
  case 9:
    uVar14 = ParseReg3X(param_1,cVar4 + '\b',pRVar22);
    iVar8 = (int)uVar14;
    goto joined_r0x00be8658;
  case 0xc:
    iVar8 = *(int *)(param_1 + 0xa4);
    uVar28 = *(uint *)(param_1 + 0x94);
    uVar25 = *(uint *)(param_1 + 0x9c);
    uVar32 = (ulong)uVar25;
    iVar27 = *(int *)(param_1 + 0x90);
    if (iVar8 < 3) {
      if (iVar27 < (int)(uVar28 + 4 + uVar25)) {
        return 0x80000002;
      }
      uVar20 = *(uint *)(*(long *)(param_1 + 0x88) + uVar32 + (long)(int)uVar28);
    }
    else {
      uVar26 = uVar28 & 1;
      iVar9 = uVar26 * 4;
      if (iVar27 < (int)((uVar28 >> 1) + 4 + uVar25 + iVar9)) {
        return 0x80000002;
      }
      puVar38 = (uint *)(*(long *)(param_1 + 0x88) + uVar32 + (ulong)(uVar28 >> 1));
      uVar20 = *puVar38 >> (sbyte)iVar9;
      uVar20 = (*(int *)((long)puVar38 + (long)iVar9) << (char)uVar26 * '\x1c' ^ uVar20) & -uVar26 &
               0xf0000000 ^ uVar20;
    }
    *(RgpSqttTokenRegister **)(param_2 + 8) = pRVar22;
    uVar29 = *(undefined4 *)(param_1 + 0xa0);
    *(uint *)(param_2 + 0x10) = uVar28;
    uVar33 = 2;
    uVar26 = uVar20 >> 0x19;
    if (0xbdffffff < uVar20) {
      uVar26 = uVar26 - 0x5f;
      uVar33 = 1;
    }
    *(uint *)(param_2 + 0x3c) = uVar26;
    *(uint *)(param_2 + 0x28) = uVar20 >> 0xd & 0x1f;
    *(undefined4 *)(param_2 + 0x40) = uVar33;
    *(ulong *)(param_2 + 0x18) = CONCAT44(uVar20 >> 7,uVar29) & 0x1ffffffff;
    *(ulong *)(param_2 + 0x20) = CONCAT44(uVar20 >> 8,uVar20 >> 10) & 0x300000007;
    if ((uVar20 & 0x1000000) == 0) {
      uVar26 = uVar20 >> 0x12 & 7;
      uVar34 = uVar20 >> 0x15 & 3;
      iVar9 = ((uVar20 & 0x800000) == 0) + 1;
      uVar10 = 6;
    }
    else {
      uVar10 = uVar20 >> 0x12 & 0xf;
      uVar26 = 0;
      uVar34 = uVar20 >> 0x16 & 1;
      iVar9 = 0;
    }
    *(uint *)(param_2 + 0x2c) = uVar10;
    *(uint *)(param_2 + 0x38) = uVar26;
    uVar26 = 8;
    *(undefined2 *)(param_2 + 0x50) = 0;
    *(ulong *)(param_2 + 0x30) = CONCAT44(uVar34,iVar9);
    if ((uVar20 & 0x10) == 0) break;
    *(undefined4 *)(param_1 + 0x98) = 0x10;
    if (iVar8 < 3) {
      if (iVar27 < (int)(uVar28 + 6 + uVar25)) goto LAB_00bea122;
      lVar12 = uVar32 + *(long *)(param_1 + 0x88) + (long)(int)uVar28;
      uVar25 = (uint)(((ulong)*(byte *)(lVar12 + 5) << 0x28) >> 0x20) | (uint)*(byte *)(lVar12 + 4);
    }
    else if (iVar27 < (int)((uVar28 >> 1) + 6 + uVar25 + (uVar28 & 1))) {
LAB_00bea122:
      uVar25 = 0;
    }
    else {
      lVar12 = uVar32 + *(long *)(param_1 + 0x88) + (ulong)(uVar28 >> 1);
      uVar25 = (uint)(((ulong)*(byte *)(lVar12 + 5) << 0x28) >> 0x20) | (uint)*(byte *)(lVar12 + 4);
      if ((uVar28 & 1) != 0) {
        uVar25 = (uVar25 | (uint)((((ulong)*(byte *)(lVar12 + 6) & 0xf) << 0x30) >> 0x20)) >> 4;
      }
    }
    uVar28 = uVar28 + 4;
    uVar26 = 8;
    if (*(int *)(param_1 + 0xc0) == 1) {
      *(ushort *)(param_2 + 0x50) = CONCAT11((char)(uVar25 >> 8),(char)(uVar25 >> 1)) & 0xff7f;
    }
    break;
  case 0xd:
switchD_00be7fee_caseD_d:
    uVar14 = ParseImmediateOne3X(param_1,uVar31,(RgpSqttTokenIssue *)(param_2 + 8));
    iVar8 = (int)uVar14;
joined_r0x00be8595:
    if (iVar8 != 0) {
      return uVar14;
    }
    iVar8 = *(int *)(param_1 + 0x98);
    uVar26 = 3;
    iVar27 = iVar8 + 3;
    if (-1 < iVar8) {
      iVar27 = iVar8;
    }
    uVar28 = (iVar27 >> 2) + *(int *)(param_1 + 0x94);
    break;
  case 0x11:
    uVar28 = *(uint *)(param_1 + 0x94);
    uVar26 = *(uint *)(param_1 + 0x9c);
    if (*(int *)(param_1 + 0xa4) < 3) {
      if (*(int *)(param_1 + 0x90) < (int)(uVar28 + 8 + uVar26)) {
        return 0x80000002;
      }
      uVar32 = *(ulong *)((ulong)uVar26 + *(long *)(param_1 + 0x88) + (long)(int)uVar28);
    }
    else {
      if (*(int *)(param_1 + 0x90) < (int)((uVar28 >> 1) + 8 + uVar26 + (uVar28 & 1))) {
        return 0x80000002;
      }
      puVar16 = (ulong *)((ulong)(uVar28 >> 1) + (ulong)uVar26 + *(long *)(param_1 + 0x88));
      uVar32 = *puVar16;
      if ((uVar28 & 1) != 0) {
        uVar32 = uVar32 >> 4 | (ulong)(byte)puVar16[1] << 0x3c;
      }
    }
    *(ulong *)(param_1 + 0xb8) = uVar32;
    iVar8 = 0;
    *(undefined4 *)(param_2 + 0x18) = *(undefined4 *)(param_1 + 0xa0);
    param_2[0x1c] = (RgpSqttToken)((byte)(uint)(uVar32 >> 0x21) & 3);
    if ((uVar32 >> 0x1c & 7) != 0) {
      iVar8 = 1 << (((byte)(uVar32 >> 0x1c) & 7) - 1 & 0x1f);
    }
    *(int *)(param_2 + 0x20) = iVar8;
    uVar26 = 0x10;
    *(ushort *)(param_2 + 0x24) = (-(ushort)((uVar32 & 0x8000000) == 0) & 0xff80) + 0x100;
    *(ushort *)(param_2 + 0x26) = CONCAT11((char)(uVar32 >> 0xf),(char)(uVar32 >> 0xd)) & 0x703;
    uVar25 = (uint)(uVar32 >> 0x19) & 3;
    *(uint *)(param_2 + 0x2c) = uVar25;
    param_2[0x28] = (RgpSqttToken)((byte)(uVar32 >> 0x13) & 1);
    *(uint *)(param_1 + 0xc0) = uVar25;
    iVar8 = *(int *)(param_1 + 0x98);
    iVar27 = iVar8 + 3;
    if (-1 < iVar8) {
      iVar27 = iVar8;
    }
    uVar28 = (iVar27 >> 2) + uVar28;
    break;
  case 0x14:
switchD_00be7fee_caseD_14:
    uVar14 = ParseWaveReady3X(param_1,(RgpSqttTokenWavefrontReady *)(param_2 + 8));
    iVar8 = (int)uVar14;
joined_r0x00be85ae:
    if (iVar8 != 0) {
      return uVar14;
    }
    iVar8 = *(int *)(param_1 + 0xb0) + 8;
    if (iVar8 == 0) {
      return 0x80000006;
    }
    iVar27 = *(int *)(param_1 + 0xb0) + 0xb;
    if (-1 < iVar8) {
      iVar27 = iVar8;
    }
    iVar8 = *(int *)(param_1 + 0x98);
    uVar26 = iVar27 >> 2;
    iVar27 = iVar8 + 3;
    if (-1 < iVar8) {
      iVar27 = iVar8;
    }
    uVar28 = (iVar27 >> 2) + *(int *)(param_1 + 0x94);
    break;
  case 0x15:
    uVar28 = *(uint *)(param_1 + 0x94);
    uVar26 = *(uint *)(param_1 + 0x9c);
    if (*(int *)(param_1 + 0xa4) < 3) {
      if (*(int *)(param_1 + 0x90) < (int)(uVar28 + 4 + uVar26)) {
        return 0x80000002;
      }
      uVar25 = *(uint *)((ulong)uVar26 + *(long *)(param_1 + 0x88) + (long)(int)uVar28);
    }
    else {
      iVar8 = (uVar28 & 1) * 4;
      if (*(int *)(param_1 + 0x90) < (int)((uVar28 >> 1) + 4 + uVar26 + iVar8)) {
        return 0x80000002;
      }
      uVar25 = *(uint *)((ulong)uVar26 + *(long *)(param_1 + 0x88) + (ulong)(uVar28 >> 1)) >>
               (sbyte)iVar8;
    }
    *(RgpSqttTokenRegister **)(param_2 + 8) = pRVar22;
    uVar29 = *(undefined4 *)(param_1 + 0xa0);
    *(uint *)(param_2 + 0x10) = uVar28;
    uVar32 = CONCAT44(uVar25 >> 8,uVar29);
    uVar24 = CONCAT44(uVar25 >> 9,uVar25 >> 0xb) & 0x300000007;
LAB_00be87b0:
    uVar26 = 5;
    *(ulong *)(param_2 + 0x18) = uVar32 & 0x1ffffffff;
    *(ulong *)(param_2 + 0x20) = uVar24;
    *(uint *)(param_2 + 0x28) = uVar25 >> 0xf & 0x1f;
    iVar8 = *(int *)(param_1 + 0x98);
    iVar27 = iVar8 + 3;
    if (-1 < iVar8) {
      iVar27 = iVar8;
    }
    uVar28 = (iVar27 >> 2) + uVar28;
    break;
  case 0x16:
    uVar14 = ParseShaderData3_1(param_1,(RgpSqttTokenShaderData *)(param_2 + 8),true);
    if ((int)uVar14 != 0) {
      return uVar14;
    }
    iVar8 = *(int *)(param_1 + 0x98);
    uVar26 = 7;
    iVar27 = iVar8 + 3;
    if (-1 < iVar8) {
      iVar27 = iVar8;
    }
    uVar28 = (iVar27 >> 2) + *(int *)(param_1 + 0x94);
    break;
  case 0x21:
    uVar14 = ParseNewPc3X(param_1,cVar4 + '\b',(RgpSqttTokenNewProgramCounter *)pRVar22);
    iVar8 = (int)uVar14;
    goto joined_r0x00be8658;
  case 0x31:
    uVar14 = ParseUtilCtr3X(param_1,(RgpSqttTokenUtilCtr *)(param_2 + 8));
    if ((int)uVar14 != 0) {
      return uVar14;
    }
    iVar8 = *(int *)(param_1 + 0xa8);
    uVar28 = *(uint *)(param_1 + 0x94);
LAB_00be8d1a:
    iVar27 = *(int *)(param_1 + 0x98);
    iVar9 = iVar27 + 3;
    if (-1 < iVar27) {
      iVar9 = iVar27;
    }
    uVar28 = (iVar9 >> 2) + uVar28;
    uVar26 = (uint)(iVar8 < 1) * 4 + 0xc;
    break;
  case 0x51:
switchD_00be7fee_caseD_51:
    uVar14 = ParseMisc3X(param_1,cVar4 + '\b',(RgpSqttTokenMisc *)pRVar22);
    iVar8 = (int)uVar14;
    goto joined_r0x00be8509;
  case 0x61:
switchD_00be7fee_caseD_61:
    uVar14 = ParseEvent3X(param_1,cVar4 + '\b',(RgpSqttTokenEvent *)pRVar22);
    iVar8 = (int)uVar14;
joined_r0x00be8509:
    if (iVar8 != 0) {
      return uVar14;
    }
    iVar8 = *(int *)(param_1 + 0x98);
    uVar26 = 6;
    iVar27 = iVar8 + 3;
    if (-1 < iVar8) {
      iVar27 = iVar8;
    }
    uVar28 = (iVar27 >> 2) + *(int *)(param_1 + 0x94);
    break;
  case 0x71:
    uVar14 = ParseRegInitiator3X(param_1,cVar4 + '\b',pRVar22);
    iVar8 = (int)uVar14;
joined_r0x00be8658:
    if (iVar8 != 0) {
      return uVar14;
    }
LAB_00be8660:
    iVar8 = *(int *)(param_1 + 0x98);
    uVar26 = 0x10;
    iVar27 = iVar8 + 3;
    if (-1 < iVar8) {
      iVar27 = iVar8;
    }
    uVar28 = (iVar27 >> 2) + *(int *)(param_1 + 0x94);
  }
LAB_00be8060:
  *(undefined4 *)(param_1 + 0x98) = 0;
  *(uint *)(param_1 + 0x94) = uVar28 + uVar26;
  return 0;
}

