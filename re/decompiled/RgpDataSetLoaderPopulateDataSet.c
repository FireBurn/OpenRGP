// function: RgpDataSetLoaderPopulateDataSet @ 00b4b0a0

int RgpDataSetLoaderPopulateDataSet
              (RgpDataSetLoader *param_1,char param_2,RgpDataSet *param_3,string *param_4,
              bool param_5)

{
  RgpWavefrontProcessor *pRVar1;
  undefined1 *puVar2;
  RgpDataSetLoader *pRVar3;
  RgpDataSet RVar4;
  RgpDataSetLoader RVar5;
  int iVar6;
  undefined8 uVar7;
  undefined1 **ppuVar8;
  undefined1 **ppuVar9;
  RgpEvent *pRVar10;
  undefined8 uVar11;
  undefined1 auVar12 [16];
  undefined1 auVar13 [16];
  undefined1 auVar14 [16];
  undefined1 auVar15 [16];
  undefined1 auVar16 [16];
  undefined1 auVar17 [16];
  undefined1 auVar18 [16];
  undefined1 auVar19 [16];
  undefined1 auVar20 [16];
  undefined1 auVar21 [16];
  undefined1 auVar22 [16];
  undefined1 auVar23 [16];
  undefined1 auVar24 [16];
  undefined1 auVar25 [16];
  undefined1 auVar26 [16];
  float fVar27;
  char cVar28;
  undefined1 uVar29;
  int iVar30;
  undefined4 uVar31;
  int iVar32;
  ulong uVar33;
  long lVar34;
  undefined8 uVar35;
  ulong uVar36;
  void *pvVar37;
  long *plVar38;
  size_t sVar39;
  size_t __size;
  size_t __size_00;
  size_t __size_01;
  size_t __size_02;
  code *pcVar40;
  size_t __size_03;
  size_t __size_04;
  size_t __size_05;
  size_t __size_06;
  void *pvVar41;
  ulong uVar42;
  long *plVar43;
  size_t __size_07;
  RgpDataSet *pRVar44;
  uint uVar45;
  long lVar46;
  ulong uVar47;
  undefined8 *puVar48;
  ulong *extraout_RDX;
  size_t __n;
  RgpDataSetLoader *pRVar49;
  RgpEventProcessor *pRVar50;
  RgpDataSetLoader *pRVar51;
  undefined1 **ppuVar52;
  size_t sVar53;
  long lVar54;
  int iVar55;
  int iVar56;
  long lVar57;
  RgpDataSetLoader *pRVar58;
  undefined1 **ppuVar59;
  RgpEventProcessor *pRVar60;
  RgpEventProcessor *pRVar61;
  undefined8 *puVar62;
  RgpDataSetLoader *pRVar63;
  undefined4 *puVar64;
  undefined8 *puVar65;
  undefined8 *puVar66;
  RgpDataSet *pRVar67;
  undefined8 *puVar68;
  long lVar69;
  undefined1 *puVar70;
  int iVar71;
  undefined1 *puVar72;
  int iVar73;
  RgpDataSetLoader *pRVar74;
  long lVar75;
  undefined4 *puVar76;
  RgpDataSetLoader *pRVar77;
  int iVar78;
  int iVar79;
  int iVar80;
  RgpDataSet *pRVar81;
  long in_FS_OFFSET;
  byte bVar82;
  float fVar83;
  undefined1 auVar84 [16];
  undefined1 auVar85 [16];
  undefined1 auVar86 [16];
  undefined1 auVar87 [16];
  undefined1 auVar88 [16];
  undefined1 auVar89 [16];
  double local_2498;
  ulong local_2440;
  RgpDataSet *local_2438;
  ulong local_23d0;
  undefined4 local_23c0;
  undefined4 uStack_23bc;
  RgpDataSet *local_23b8;
  ulong local_23b0;
  long local_23a8;
  undefined1 local_23a0 [16];
  undefined1 local_2390 [16];
  undefined1 local_2378 [8];
  ulong uStack_2370;
  undefined1 local_2368 [8];
  undefined8 uStack_2360;
  undefined1 local_2358 [6];
  undefined1 uStack_2352;
  undefined1 uStack_2351;
  ulong uStack_2350;
  undefined1 local_2348 [16];
  char local_2336;
  undefined1 local_2308 [16];
  ulong local_22f8;
  undefined4 uStack_22f0;
  undefined4 uStack_22ec;
  undefined4 uStack_22e8;
  undefined4 uStack_22e4;
  ulong uStack_22e0;
  undefined1 local_22d8 [16];
  undefined8 local_22c8 [1024];
  RgpDataSetLoader local_2c8;
  undefined4 local_2c4;
  undefined8 local_2c0;
  undefined8 uStack_2b8;
  undefined8 local_2b0;
  undefined8 uStack_2a8;
  undefined8 local_2a0;
  undefined8 uStack_298;
  undefined8 local_290;
  undefined8 uStack_288;
  undefined1 *local_280;
  undefined8 uStack_278;
  undefined8 local_270;
  undefined8 uStack_268;
  undefined8 local_260;
  undefined8 uStack_258;
  undefined8 local_250;
  RgpDataSetLoader *local_248;
  undefined8 local_240;
  undefined8 local_238;
  undefined8 local_228;
  undefined8 uStack_220;
  RgpDataSetLoader local_218 [8];
  undefined1 *local_210;
  undefined8 local_208;
  undefined8 local_200;
  undefined1 local_1f8 [16];
  undefined1 local_1e8 [16];
  undefined1 *local_1d8;
  undefined8 local_1d0;
  undefined8 local_1c8;
  undefined1 local_1c0 [16];
  undefined1 local_1b0 [16];
  RgpDataSetLoader *local_1a0;
  undefined8 local_198;
  undefined8 local_190;
  undefined1 local_188 [16];
  undefined1 local_178 [16];
  undefined1 *local_168;
  undefined8 local_160;
  undefined8 local_158;
  undefined1 local_150 [16];
  undefined1 local_140 [16];
  undefined1 *local_130;
  undefined8 local_128;
  undefined8 local_120;
  undefined1 local_118 [16];
  undefined1 local_108 [16];
  void *local_f8;
  long lStack_f0;
  undefined1 local_e8 [16];
  undefined1 local_d8 [16];
  undefined1 local_c8 [16];
  undefined1 local_b8 [16];
  undefined8 local_a8;
  undefined8 local_a0;
  undefined8 uStack_98;
  undefined8 local_90;
  undefined8 uStack_88;
  undefined8 local_80;
  undefined8 uStack_78;
  undefined4 local_70;
  undefined8 local_68;
  undefined8 uStack_60;
  undefined8 local_58;
  undefined8 local_50;
  undefined4 local_48;
  long local_40;
  
  bVar82 = 0;
  local_40 = *(long *)(in_FS_OFFSET + 0x28);
  if ((param_1 == (RgpDataSetLoader *)0x0) || (param_3 == (RgpDataSet *)0x0)) {
    iVar30 = -0x80000000;
    goto LAB_00b4d2ab;
  }
  uVar33 = RgpGetClockFrequency();
  lVar34 = RgpGetCurrentTimestamp();
  *(RgpDataSet **)(param_1 + 0x7a8) = param_3;
  if (*(int *)(param_1 + 0x7a0) != 0) {
    local_2498 = DAT_00df22b0;
    if ((*(ulong *)(param_1 + 0x150) != 0) && (*(ulong *)(param_1 + 0x160) != 0)) {
      local_2498 = (double)*(ulong *)(param_1 + 0x150) / (double)*(ulong *)(param_1 + 0x160);
    }
    iVar30 = RgpCountActiveShaderEngines(param_1 + 0x1d6,*(undefined4 *)(param_1 + 0x118));
    if (iVar30 == 0) {
      RgpPrint(
              "Invalid profile: Active CU mask indicates no shader engines are active. Profile cannot be loaded."
              );
      iVar30 = -0x7ffffffa;
      goto LAB_00b4d2ab;
    }
    iVar32 = *(int *)(param_1 + 0x118);
    pRVar49 = param_1 + 0x180878;
    pRVar77 = param_1 + 0x64c;
    if (0 < iVar32) {
      iVar55 = 0;
      do {
        if (*(int *)(pRVar77 + 0x1c) != 0) {
          if (iVar30 == iVar32) {
            iVar32 = *(int *)pRVar77;
          }
          else {
            iVar32 = RgpPhysicalShaderEngineToLogical(param_1 + 0x1d6,pRVar77);
            if (iVar32 == 0) {
              *(undefined4 *)(param_1 + 0x7a4) = 0;
            }
          }
          *(int *)(pRVar77 + -4) = iVar32;
          local_23c0 = 0;
          *(int *)(param_1 + (long)iVar32 * 4 + 0x2d8) = *(int *)(pRVar77 + 0x20);
          local_23b8 = (RgpDataSet *)((ulong)local_23b8 & 0xffffffff00000000);
          RgpGetSqttMajorMinorVersion(*(int *)(pRVar77 + 0x1c),&local_23c0,&local_23b8);
          RgpSqttParserInitialize
                    (local_2498,pRVar49,*(undefined8 *)(pRVar77 + 4),param_1,0,
                     (int)*(undefined8 *)(pRVar77 + 0xc) - (int)*(undefined8 *)(pRVar77 + 4),
                     *(int *)(pRVar77 + -4),local_23c0,(ulong)local_23b8 & 0xffffffff,
                     *(undefined4 *)(param_1 + 0x104),0,*(undefined4 *)(param_1 + 0x124),
                     *(undefined4 *)(param_1 + 0x130));
          if (*(int *)(param_1 + 0x798) < 0) {
            iVar30 = -0x7ffffff2;
            goto LAB_00b4d2ab;
          }
          if (1 < *(int *)(param_1 + 0x798)) {
            iVar30 = -0x7ffffff1;
            goto LAB_00b4d2ab;
          }
          iVar32 = *(int *)(param_1 + 0x118);
        }
        iVar55 = iVar55 + 1;
        pRVar49 = pRVar49 + 200;
        pRVar77 = pRVar77 + 0x38;
      } while (iVar55 < iVar32);
    }
  }
  memcpy_s(param_3,0x310,param_1,0x310);
  memcpy_s(param_3 + 0x310,0x58,param_1 + 0x310,0x58);
  memcpy_s(param_3 + 0x368,0x228,param_1 + 0x368,0x228);
  memcpy_s(param_3 + 0x590,0x30,param_1 + 0x590,0x30);
  pRVar67 = *(RgpDataSet **)(param_1 + 0x5c0);
  pRVar81 = (RgpDataSet *)(param_1 + 0x5d0);
  pRVar44 = *(RgpDataSet **)(param_3 + 0x5c0);
  if (pRVar67 == pRVar81) {
    if (param_3 + 0x5c0 != (RgpDataSet *)(param_1 + 0x5c0)) {
      sVar39 = *(size_t *)(param_1 + 0x5c8);
      lVar69 = 0;
      if (sVar39 != 0) {
        if (sVar39 == 1) {
          *pRVar44 = *(RgpDataSet *)(param_1 + 0x5d0);
          lVar69 = *(long *)(param_1 + 0x5c8);
          pRVar44 = *(RgpDataSet **)(param_3 + 0x5c0);
        }
        else {
          memcpy(pRVar44,pRVar67,sVar39);
          lVar69 = *(long *)(param_1 + 0x5c8);
          pRVar44 = *(RgpDataSet **)(param_3 + 0x5c0);
        }
      }
      *(long *)(param_3 + 0x5c8) = lVar69;
      pRVar44[lVar69] = (RgpDataSet)0x0;
      pRVar67 = *(RgpDataSet **)(param_1 + 0x5c0);
    }
  }
  else {
    uVar35 = *(undefined8 *)(param_1 + 0x5c8);
    if (pRVar44 == param_3 + 0x5d0) {
      *(RgpDataSet **)(param_3 + 0x5c0) = pRVar67;
      *(undefined8 *)(param_3 + 0x5c8) = uVar35;
      *(undefined8 *)(param_3 + 0x5d0) = *(undefined8 *)(param_1 + 0x5d0);
    }
    else {
      *(RgpDataSet **)(param_3 + 0x5c0) = pRVar67;
      uVar7 = *(undefined8 *)(param_3 + 0x5d0);
      *(undefined8 *)(param_3 + 0x5c8) = uVar35;
      *(undefined8 *)(param_3 + 0x5d0) = *(undefined8 *)(param_1 + 0x5d0);
      if (pRVar44 != (RgpDataSet *)0x0) {
        *(RgpDataSet **)(param_1 + 0x5c0) = pRVar44;
        *(undefined8 *)(param_1 + 0x5d0) = uVar7;
        pRVar67 = pRVar44;
        goto LAB_00b4b3a3;
      }
    }
    *(RgpDataSet **)(param_1 + 0x5c0) = pRVar81;
    pRVar67 = pRVar81;
  }
LAB_00b4b3a3:
  *(undefined8 *)(param_1 + 0x5c8) = 0;
  *pRVar67 = (RgpDataSet)0x0;
  pRVar67 = *(RgpDataSet **)(param_1 + 0x5e0);
  pRVar44 = *(RgpDataSet **)(param_3 + 0x5e0);
  pRVar81 = (RgpDataSet *)(param_1 + 0x5f0);
  if (pRVar67 == pRVar81) {
    if ((RgpDataSet *)(param_1 + 0x5e0) != param_3 + 0x5e0) {
      sVar39 = *(size_t *)(param_1 + 0x5e8);
      lVar69 = 0;
      if (sVar39 != 0) {
        if (sVar39 == 1) {
          *pRVar44 = *(RgpDataSet *)(param_1 + 0x5f0);
          lVar69 = *(long *)(param_1 + 0x5e8);
          pRVar44 = *(RgpDataSet **)(param_3 + 0x5e0);
        }
        else {
          memcpy(pRVar44,pRVar67,sVar39);
          lVar69 = *(long *)(param_1 + 0x5e8);
          pRVar44 = *(RgpDataSet **)(param_3 + 0x5e0);
        }
      }
      *(long *)(param_3 + 0x5e8) = lVar69;
      pRVar44[lVar69] = (RgpDataSet)0x0;
      pRVar67 = *(RgpDataSet **)(param_1 + 0x5e0);
    }
  }
  else {
    uVar35 = *(undefined8 *)(param_1 + 0x5e8);
    if (pRVar44 == param_3 + 0x5f0) {
      *(RgpDataSet **)(param_3 + 0x5e0) = pRVar67;
      *(undefined8 *)(param_3 + 0x5e8) = uVar35;
      *(undefined8 *)(param_3 + 0x5f0) = *(undefined8 *)(param_1 + 0x5f0);
    }
    else {
      *(RgpDataSet **)(param_3 + 0x5e0) = pRVar67;
      uVar7 = *(undefined8 *)(param_3 + 0x5f0);
      *(undefined8 *)(param_3 + 0x5e8) = uVar35;
      *(undefined8 *)(param_3 + 0x5f0) = *(undefined8 *)(param_1 + 0x5f0);
      if (pRVar44 != (RgpDataSet *)0x0) {
        *(RgpDataSet **)(param_1 + 0x5e0) = pRVar44;
        *(undefined8 *)(param_1 + 0x5f0) = uVar7;
        pRVar67 = pRVar44;
        goto LAB_00b4b434;
      }
    }
    *(RgpDataSet **)(param_1 + 0x5e0) = pRVar81;
    pRVar67 = pRVar81;
  }
LAB_00b4b434:
  *(undefined8 *)(param_1 + 0x5e8) = 0;
  *pRVar67 = (RgpDataSet)0x0;
  pRVar67 = *(RgpDataSet **)(param_1 + 0x600);
  pRVar44 = *(RgpDataSet **)(param_3 + 0x600);
  pRVar81 = (RgpDataSet *)(param_1 + 0x610);
  if (pRVar67 == pRVar81) {
    if ((RgpDataSet *)(param_1 + 0x600) != param_3 + 0x600) {
      sVar39 = *(size_t *)(param_1 + 0x608);
      lVar69 = 0;
      if (sVar39 != 0) {
        if (sVar39 == 1) {
          *pRVar44 = *(RgpDataSet *)(param_1 + 0x610);
          lVar69 = *(long *)(param_1 + 0x608);
          pRVar44 = *(RgpDataSet **)(param_3 + 0x600);
        }
        else {
          memcpy(pRVar44,pRVar67,sVar39);
          lVar69 = *(long *)(param_1 + 0x608);
          pRVar44 = *(RgpDataSet **)(param_3 + 0x600);
        }
      }
      *(long *)(param_3 + 0x608) = lVar69;
      pRVar44[lVar69] = (RgpDataSet)0x0;
      pRVar67 = *(RgpDataSet **)(param_1 + 0x600);
    }
  }
  else {
    uVar35 = *(undefined8 *)(param_1 + 0x608);
    if (pRVar44 == param_3 + 0x610) {
      *(RgpDataSet **)(param_3 + 0x600) = pRVar67;
      *(undefined8 *)(param_3 + 0x608) = uVar35;
      *(undefined8 *)(param_3 + 0x610) = *(undefined8 *)(param_1 + 0x610);
    }
    else {
      *(RgpDataSet **)(param_3 + 0x600) = pRVar67;
      uVar7 = *(undefined8 *)(param_3 + 0x610);
      *(undefined8 *)(param_3 + 0x608) = uVar35;
      *(undefined8 *)(param_3 + 0x610) = *(undefined8 *)(param_1 + 0x610);
      if (pRVar44 != (RgpDataSet *)0x0) {
        *(RgpDataSet **)(param_1 + 0x600) = pRVar44;
        *(undefined8 *)(param_1 + 0x610) = uVar7;
        pRVar67 = pRVar44;
        goto LAB_00b4b4c2;
      }
    }
    *(RgpDataSet **)(param_1 + 0x600) = pRVar81;
    pRVar67 = pRVar81;
  }
LAB_00b4b4c2:
  *(undefined8 *)(param_1 + 0x608) = 0;
  *pRVar67 = (RgpDataSet)0x0;
  *(undefined8 *)(param_3 + 0x620) = *(undefined8 *)(param_1 + 0x620);
  memset(param_3 + 0x2ae0,0,0x69000);
  *(undefined8 *)(param_3 + 0x91398) = 0;
  *(undefined8 *)(param_3 + 0x91480) = 0;
  puVar68 = (undefined8 *)((ulong)(param_3 + 0x913a0) & 0xfffffffffffffff8);
  for (uVar42 = (ulong)(((int)(param_3 + 0x91398) -
                        (int)(undefined8 *)((ulong)(param_3 + 0x913a0) & 0xfffffffffffffff8)) +
                        0xf0U >> 3); uVar42 != 0; uVar42 = uVar42 - 1) {
    *puVar68 = 0;
    puVar68 = puVar68 + (ulong)bVar82 * -2 + 1;
  }
  *(undefined8 *)(param_3 + 0x91490) = 0;
  *(undefined4 *)(param_3 + 0x91498) = 0;
  lVar69 = *(long *)(param_3 + 0x678);
  *(undefined8 *)(param_3 + 0x91488) = 0;
  uVar42 = (ulong)*(int *)(param_1 + 0x114);
  lVar46 = lVar69 - *(long *)(param_3 + 0x670) >> 4;
  uVar47 = lVar46 * -0x5555555555555555;
  if (uVar47 < uVar42) {
    std::
    vector<std::map<unsigned_long,double,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const,double>>>,std::allocator<std::map<unsigned_long,double,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const,double>>>>>
    ::_M_default_append((vector<std::map<unsigned_long,double,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const,double>>>,std::allocator<std::map<unsigned_long,double,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const,double>>>>>
                         *)(param_3 + 0x670),uVar42 + lVar46 * 0x5555555555555555);
    uVar42 = (ulong)*(int *)(param_1 + 0x114);
  }
  else if ((uVar42 < uVar47) &&
          (lVar57 = *(long *)(param_3 + 0x670) + uVar42 * 0x30, lVar46 = lVar57, lVar69 != lVar57))
  {
    do {
      pvVar37 = *(void **)(lVar46 + 0x10);
      while (pvVar37 != (void *)0x0) {
        std::
        _Rb_tree<unsigned_long,std::pair<unsigned_long_const,double>,std::_Select1st<std::pair<unsigned_long_const,double>>,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const,double>>>
        ::_M_erase(*(_Rb_tree_node **)((long)pvVar37 + 0x18));
        pvVar41 = *(void **)((long)pvVar37 + 0x10);
        operator_delete(pvVar37,0x30);
        pvVar37 = pvVar41;
      }
      lVar46 = lVar46 + 0x30;
    } while (lVar69 != lVar46);
    *(long *)(param_3 + 0x678) = lVar57;
    uVar42 = (ulong)*(int *)(param_1 + 0x114);
  }
  lVar69 = *(long *)(param_3 + 0x690);
  lVar46 = lVar69 - *(long *)(param_3 + 0x688) >> 4;
  uVar47 = lVar46 * -0x5555555555555555;
  if (uVar47 < uVar42) {
    std::
    vector<std::map<unsigned_long,double,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const,double>>>,std::allocator<std::map<unsigned_long,double,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const,double>>>>>
    ::_M_default_append((vector<std::map<unsigned_long,double,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const,double>>>,std::allocator<std::map<unsigned_long,double,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const,double>>>>>
                         *)(param_3 + 0x688),uVar42 + lVar46 * 0x5555555555555555);
  }
  else if ((uVar47 - uVar42 != 0) &&
          (lVar57 = *(long *)(param_3 + 0x688) + uVar42 * 0x30, lVar46 = lVar57, lVar69 != lVar57))
  {
    do {
      pvVar37 = *(void **)(lVar46 + 0x10);
      while (pvVar37 != (void *)0x0) {
        std::
        _Rb_tree<unsigned_long,std::pair<unsigned_long_const,double>,std::_Select1st<std::pair<unsigned_long_const,double>>,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const,double>>>
        ::_M_erase(*(_Rb_tree_node **)((long)pvVar37 + 0x18));
        pvVar41 = *(void **)((long)pvVar37 + 0x10);
        operator_delete(pvVar37,0x30);
        pvVar37 = pvVar41;
      }
      lVar46 = lVar46 + 0x30;
    } while (lVar69 != lVar46);
    *(long *)(param_3 + 0x690) = lVar57;
  }
  iVar30 = *(int *)(param_1 + 0x7a0);
  *(undefined8 *)(param_3 + 0x6a0) = DAT_00dfb558;
  if (iVar30 != 0) {
    RgpDataSetAllocationProfileInitialize
              (param_1 + 0xa219b8,param_3,*(undefined4 *)(param_1 + 0x368),
               *(undefined4 *)(param_1 + 0x580),*(undefined4 *)(param_1 + 0x798));
    param_1[0xbc8860] = (RgpDataSetLoader)0x0;
    *(RgpDataSetLoader **)(param_1 + 0xa219d0) = param_1 + 0x9b1100;
LAB_00b4d970:
    do {
      lVar69 = (long)*(int *)(param_1 + 0x180870);
      puVar68 = (undefined8 *)local_2308;
      for (lVar46 = 0x12; lVar46 != 0; lVar46 = lVar46 + -1) {
        *puVar68 = 0;
        puVar68 = puVar68 + (ulong)bVar82 * -2 + 1;
      }
      pRVar49 = param_1 + lVar69 * 200 + 0x180878;
      do {
        while( true ) {
          do {
            iVar30 = RgpSqttParserAdvance
                               (pRVar49,(RgpSqttToken *)local_2378,
                                (_Hashtable<int,std::pair<int_const,std::unordered_set<int,std::hash<int>,std::equal_to<int>,std::allocator<int>>>,std::allocator<std::pair<int_const,std::unordered_set<int,std::hash<int>,std::equal_to<int>,std::allocator<int>>>>,std::__detail::_Select1st,std::equal_to<int>,std::hash<int>,std::__detail::_Mod_range_hashing,std::__detail::_Default_ranged_hash,std::__detail::_Prime_rehash_policy,std::__detail::_Hashtable_traits<false,false,true>>
                                 *)&local_23b8,0);
            if (iVar30 == -0x7ffffffa) {
              iVar30 = -0x7ffffffa;
              goto LAB_00b4d2ab;
            }
            if ((iVar30 != 0) ||
               (uVar45 = *(uint *)(param_1 + lVar69 * 200 + 0x18090c),
               iVar30 = RgpSqttParserGetSqttDataSize(pRVar49), (uint)(iVar30 * 2) < uVar45)) {
              cVar28 = RgpSqttParserIsCompleted(pRVar49);
              if (cVar28 != '\0') goto LAB_00b4db80;
              iVar30 = *(int *)(param_1 + 0x114);
              goto LAB_00b4db9b;
            }
            if (((local_2378._0_4_ == 0x13) && (0xd < *(int *)(param_1 + 0x104))) &&
               ((int)uStack_2360 == 0)) {
              lVar46 = *(long *)(param_1 + 0x7a8);
              *(ulong *)(lVar46 + 0x6ac) = (ulong)CONCAT14(uStack_2360._4_1_,local_2358._0_4_);
              *(undefined1 *)(lVar46 + 0x9158a) = uStack_2352;
              *(undefined1 *)(*(long *)(param_1 + 0x7a8) + 0x9158c) = (undefined1)uStack_2350;
              *(undefined1 *)(*(long *)(param_1 + 0x7a8) + 0x9158b) = uStack_2351;
              if (0x10 < *(int *)(param_1 + 0x104)) {
                *(bool *)(*(long *)(param_1 + 0x7a8) + 0x91564) = local_2336 != '\0';
              }
            }
            cVar28 = RgpSqttParserDataIsValid(pRVar49);
          } while (cVar28 == '\0');
          uVar42 = *(ulong *)(param_3 + 0x91488);
          if (*(ulong *)(param_3 + 0x91488) < *(ulong *)(param_1 + lVar69 * 200 + 0x180890)) {
            uVar42 = *(ulong *)(param_1 + lVar69 * 200 + 0x180890);
          }
          RVar5 = param_1[0xbc8860];
          *(ulong *)(param_3 + 0x91488) = uVar42;
          if (RVar5 != (RgpDataSetLoader)0x0) break;
          cVar28 = (anonymous_namespace)::SqttTokenHandlerForProfile
                             (param_1,(RgpSqttToken *)local_2378);
          if (cVar28 != '\0') goto LAB_00b4da40;
        }
        cVar28 = (anonymous_namespace)::TokenProcessor(param_1,(RgpSqttToken *)local_2378);
      } while (cVar28 == '\0');
LAB_00b4da40:
      RgpSqttParserSetPosition
                (pRVar49,(_Hashtable<int,std::pair<int_const,std::unordered_set<int,std::hash<int>,std::equal_to<int>,std::allocator<int>>>,std::allocator<std::pair<int_const,std::unordered_set<int,std::hash<int>,std::equal_to<int>,std::allocator<int>>>>,std::__detail::_Select1st,std::equal_to<int>,std::hash<int>,std::__detail::_Mod_range_hashing,std::__detail::_Default_ranged_hash,std::__detail::_Prime_rehash_policy,std::__detail::_Hashtable_traits<false,false,true>>
                          *)&local_23b8,local_2308);
      iVar30 = *(int *)(param_1 + 0x114);
      iVar32 = *(int *)(param_1 + 0x180870);
      if (0 < iVar30) {
        pRVar77 = param_1 + 0x180878;
        iVar55 = 0;
        do {
          if (iVar32 != iVar55) {
            cVar28 = RgpSqttParserIsCompleted(pRVar77);
            if (cVar28 == '\0') goto LAB_00b4db80;
            iVar30 = *(int *)(param_1 + 0x114);
          }
          iVar55 = iVar55 + 1;
          pRVar77 = pRVar77 + 200;
        } while (iVar55 < iVar30);
      }
      RgpSqttParserRecoverPosition(pRVar49,local_2308);
    } while( true );
  }
  uVar35 = *(undefined8 *)(param_1 + 0x9b10e0);
  *(undefined8 *)(param_3 + 0x2ad0) = *(undefined8 *)(param_1 + 0x9b10d8);
  *(undefined8 *)(param_3 + 0x2ad8) = uVar35;
  uVar35 = *(undefined8 *)(param_1 + 0x9b10f0);
  *(undefined8 *)(param_3 + 0x6bae0) = *(undefined8 *)(param_1 + 0x9b10e8);
  *(undefined8 *)(param_3 + 0x6bae8) = uVar35;
  *(undefined8 *)(param_3 + 0x6baf0) = *(undefined8 *)(param_1 + 0x9b10f8);
LAB_00b4b6bd:
  RgpApiPsoDbPopulate(*(RgpApiPsoDatabase **)(param_1 + 0x9b10f8),
                      *(RgpCodeObjectDatabase **)(param_1 + 0x9b10e8));
  RgpIsaDatabasePopulate(*(undefined8 *)(param_1 + 0x9b10d8));
  RgpCodeObjectDatabase::Populate(*(RgpCodeObjectDatabase **)(param_1 + 0x9b10e8),param_3);
  iVar30 = RgpCodeObjDBMatchLoaderEvents
                     (*(RgpCodeObjectDatabase **)(param_1 + 0x9b10e8),
                      *(RgpLoaderEventDatabase **)(param_1 + 0x9b10f0));
  if (iVar30 != 0) {
    RgpSpmDataProvider::GetSpmDatabase(*(RgpSpmDataProvider **)(param_1 + 0x9b10e0));
  }
  RgpCodeObjDbPopulateActiveLoaderEvents
            (*(undefined8 *)(param_1 + 0x9b10f0),*(undefined4 *)(param_3 + 0x368));
  pvVar37 = *(void **)(param_3 + 0xa80);
  uVar35 = *(undefined8 *)(param_1 + 0x630);
  lVar69 = *(long *)(param_3 + 0xa90);
  *(undefined8 *)(param_3 + 0xa80) = *(undefined8 *)(param_1 + 0x628);
  *(undefined8 *)(param_3 + 0xa88) = uVar35;
  *(undefined8 *)(param_3 + 0xa90) = *(undefined8 *)(param_1 + 0x638);
  *(undefined8 *)(param_1 + 0x638) = 0;
  *(undefined1 (*) [16])(param_1 + 0x628) = (undefined1  [16])0x0;
  if (pvVar37 != (void *)0x0) {
    operator_delete(pvVar37,lVar69 - (long)pvVar37);
  }
  *(undefined8 *)(param_3 + 0xaa0) = 0;
  *(undefined8 *)(param_3 + 0x2a98) = 0;
  puVar68 = (undefined8 *)((ulong)(param_3 + 0xaa8) & 0xfffffffffffffff8);
  uVar42 = (ulong)(((int)(param_3 + 0xaa0) - (int)puVar68) + 0x2000U >> 3);
  for (; uVar42 != 0; uVar42 = uVar42 - 1) {
    *puVar68 = 0;
    puVar68 = puVar68 + (ulong)bVar82 * -2 + 1;
  }
  *(undefined4 *)(param_3 + 0x2aa0) = 0;
  lVar69 = *(long *)(param_3 + 0xa80);
  lVar46 = *(long *)(param_3 + 0xa88);
  if (lVar69 != lVar46) {
    lVar57 = 0;
LAB_00b4b7d3:
    do {
      lVar75 = *(long *)(lVar69 + 0x10);
      iVar30 = (int)lVar57;
      if (iVar30 != 0) {
        pRVar81 = param_3 + 0xaa0;
        do {
          if (*(long *)pRVar81 == lVar75) {
            lVar69 = lVar69 + 0x50;
            if (lVar46 == lVar69) goto LAB_00b4b80b;
            goto LAB_00b4b7d3;
          }
          pRVar81 = pRVar81 + 8;
        } while (pRVar81 != param_3 + 0xaa8 + (ulong)(iVar30 - 1) * 8);
      }
      lVar69 = lVar69 + 0x50;
      *(int *)(param_3 + 0x2aa0) = iVar30 + 1;
      *(long *)(param_3 + lVar57 * 8 + 0xaa0) = lVar75;
      lVar57 = (long)(iVar30 + 1);
    } while (lVar46 != lVar69);
  }
LAB_00b4b80b:
  param_3[0x6bb88] = *(RgpDataSet *)(param_1 + 0x640);
  RVar4 = *(RgpDataSet *)(param_1 + 0x641);
  *(undefined4 *)(param_3 + 0x648) = 0;
  param_3[0x6bb89] = RVar4;
  param_3[0x6a8] = *(RgpDataSet *)(param_1 + 0x7b0);
  RVar4 = *(RgpDataSet *)(param_1 + 0x7b1);
  *(undefined4 *)(param_3 + 0x650) = 0;
  param_3[0x6a9] = RVar4;
  if ((RgpDataSet *)(param_1 + 0xc397e0) != param_3 + 0x91568) {
    pRVar81 = *(RgpDataSet **)(param_3 + 0x91568);
    uVar42 = *(ulong *)(param_1 + 0xc397e8);
    if (pRVar81 == param_3 + 0x91578) {
      uVar47 = 0xf;
    }
    else {
      uVar47 = *(ulong *)(param_3 + 0x91578);
    }
    if (uVar47 < uVar42) {
      if ((long)uVar42 < 0) {
                    /* WARNING: Subroutine does not return */
        std::__throw_length_error("basic_string::_M_create");
      }
      uVar47 = uVar47 * 2;
      uVar36 = uVar42;
      if (((uVar42 < uVar47) && (uVar36 = uVar47, (long)uVar47 < 0)) || ((long)(uVar36 + 1) < 0)) {
                    /* WARNING: Subroutine does not return */
        std::__throw_bad_alloc();
      }
      pRVar81 = operator_new(uVar36 + 1);
      if (param_3 + 0x91578 != *(RgpDataSet **)(param_3 + 0x91568)) {
        operator_delete(*(RgpDataSet **)(param_3 + 0x91568),*(long *)(param_3 + 0x91578) + 1);
      }
      *(RgpDataSet **)(param_3 + 0x91568) = pRVar81;
      *(ulong *)(param_3 + 0x91578) = uVar36;
    }
    if (uVar42 != 0) {
      if (uVar42 == 1) {
        *pRVar81 = **(RgpDataSet **)(param_1 + 0xc397e0);
        pRVar81 = *(RgpDataSet **)(param_3 + 0x91568);
      }
      else {
        memcpy(pRVar81,*(RgpDataSet **)(param_1 + 0xc397e0),uVar42);
        pRVar81 = *(RgpDataSet **)(param_3 + 0x91568);
      }
    }
    *(ulong *)(param_3 + 0x91570) = uVar42;
    pRVar81[uVar42] = (RgpDataSet)0x0;
  }
  RgpSpmDataProvider::Populate(*(RgpSpmDataProvider **)(param_1 + 0x9b10e0),param_3);
  if (*(int *)(param_1 + 0x7a0) != 0) {
    iVar30 = 0;
    RgpInstSequencerInitialize(*(RgpInstSequencer **)(param_1 + 0x9b1160),param_3,param_1);
    do {
      iVar32 = 0;
      do {
        iVar55 = iVar32 + 1;
        RgpEventProcessorInitialize
                  (param_1 + (long)(*(int *)(param_1 + 0x130) * iVar30 + iVar32) * 0x860d0 +
                             0x180d28,param_1,iVar30,iVar32,*(undefined4 *)(param_1 + 0x368),
                   *(undefined4 *)(param_1 + 0x798),*(undefined4 *)(param_1 + 0x79c));
        iVar32 = iVar55;
      } while (iVar55 != 4);
      iVar30 = iVar30 + 1;
    } while (iVar30 != 3);
    iVar30 = RgpAsicParametersGetTotalFrontendPipes(param_1);
    pRVar1 = (RgpWavefrontProcessor *)(param_1 + 0x7c96e8);
    pRVar60 = (RgpEventProcessor *)(param_1 + 0x180d28);
    RgpWavefrontProcessorInitialize(pRVar1,param_1,pRVar60,iVar30);
    if (0 < *(int *)(param_1 + 0x114)) {
      pRVar49 = param_1 + 0x180878;
      local_2440 = 0;
      local_2438 = param_3 + 0x91398;
      do {
        lVar69 = **(long **)(param_1 + 0xa219a0);
        iVar32 = (int)local_2440;
        uVar42 = ((*(long **)(param_1 + 0xa219a0))[1] - lVar69 >> 4) * -0x3333333333333333;
        if (uVar42 < local_2440 || uVar42 - local_2440 == 0) {
                    /* WARNING: Subroutine does not return */
          std::__throw_out_of_range_fmt
                    ("vector::_M_range_check: __n (which is %zu) >= this->size() (which is %zu)",
                     local_2440);
        }
        lVar69 = lVar69 + local_2440 * 0x50;
        uVar35 = *(undefined8 *)(lVar69 + 0x20);
        puVar68 = *(undefined8 **)(lVar69 + 0x28);
        lVar46 = *(long *)(lVar69 + 0x48);
        uVar7 = *(undefined8 *)(lVar69 + 0x10);
        uVar11 = *(undefined8 *)(lVar69 + 0x18);
        puVar48 = puVar68;
        while (puVar48 = puVar48 + 1, puVar48 < (undefined8 *)(lVar46 + 8U)) {
          operator_delete((void *)*puVar48,0x200);
        }
        *(undefined8 *)(lVar69 + 0x30) = uVar7;
        *(undefined8 *)(lVar69 + 0x38) = uVar11;
        *(undefined8 *)(lVar69 + 0x40) = uVar35;
        *(undefined8 **)(lVar69 + 0x48) = puVar68;
        if (((5 < *(int *)(param_1 + 0x104)) &&
            (local_23c0 = 0, *(int *)(param_1 + 0x104) - 6U < 0xb)) &&
           (1 < *(int *)(param_1 + 0x114))) {
          local_23b8 = (RgpDataSet *)0x0;
          GetRtTimestampStartingDeltaFromShaderEngine0(param_1,iVar32,&local_23b8,&local_23c0);
          RgpSqttParserSetTimestampSkipCount(pRVar49,local_23c0);
          RgpSqttParserSetRTTimestampStartDelta(pRVar49,local_23b8);
          RgpPrint("Using SE0 as reference (Strategy #3) Shader engine: %d rt timestamps skipped: %d \t Delta applied: %lu"
                   ,iVar32,local_23c0,local_23b8);
        }
        *(undefined4 *)(local_2438 + 8) = *(undefined4 *)(pRVar49 + 0x7c);
        uVar31 = RgpSqttParserGetSqttDataSize(pRVar49);
        *(undefined4 *)(local_2438 + 4) = uVar31;
        *(undefined4 *)local_2438 = *(undefined4 *)(pRVar49 + 0xa0);
        *(undefined8 *)(local_2438 + 0x10) =
             *(undefined8 *)
              (param_1 + (long)(iVar32 * 0x8000 + *(int *)(pRVar49 + 0x7c)) * 8 + 0x7c8);
        pRVar61 = pRVar60;
        if (0 < iVar30) {
          do {
            pRVar50 = pRVar61 + 0x860d0;
            RgpEventProcessorReset(pRVar61);
            pRVar61 = pRVar50;
          } while ((RgpEventProcessor *)(param_1 + (ulong)(iVar30 - 1) * 0x860d0 + 0x206df8) !=
                   pRVar50);
        }
        iVar55 = 0;
        do {
          iVar79 = 0;
          do {
            if (iVar32 != 0) {
              pRVar51 = local_218;
              *(undefined4 *)(param_1 + 0x9b10d0) = 0;
              lVar69 = (long)(iVar55 * *(int *)(param_1 + 0x130) + iVar79);
              lVar57 = lVar69 * 0x860d0;
              *(undefined8 *)(param_1 + lVar57 + 0x205530) = 0;
              memset((RgpSqttToken *)local_2308,0,0x22c8);
              local_210 = local_1e8 + 8;
              local_1d8 = local_1b0 + 8;
              pRVar74 = (RgpDataSetLoader *)(local_178 + 8);
              local_168 = local_140 + 8;
              local_130 = local_108 + 8;
              local_1e8 = (undefined1  [16])0x0;
              local_1b0 = (undefined1  [16])0x0;
              local_178 = (undefined1  [16])0x0;
              local_140 = (undefined1  [16])0x0;
              local_108 = (undefined1  [16])0x0;
              local_240 = 1;
              local_238 = 0;
              local_228 = 0x3f800000;
              uStack_220 = 0;
              local_208 = 1;
              local_200 = 0;
              local_1f8._0_12_ = ZEXT412(0x3f800000) << 0x40;
              local_1f8._12_4_ = 0;
              local_1d0 = 1;
              local_1c8 = 0;
              local_1c0._0_12_ = ZEXT412(0x3f800000) << 0x40;
              local_1c0._12_4_ = 0;
              local_198 = 1;
              local_190 = 0;
              local_188._0_12_ = ZEXT412(0x3f800000) << 0x40;
              local_188._12_4_ = 0;
              local_160 = 1;
              local_158 = 0;
              local_150._0_12_ = ZEXT412(0x3f800000) << 0x40;
              local_150._12_4_ = 0;
              local_128 = 1;
              local_120 = 0;
              local_118._0_12_ = ZEXT412(0x3f800000) << 0x40;
              local_118._12_4_ = 0;
              local_e8 = (undefined1  [16])0x0;
              local_d8 = (undefined1  [16])0x0;
              local_c8 = (undefined1  [16])0x0;
              local_b8 = (undefined1  [16])0x0;
              local_248 = pRVar51;
              local_1a0 = pRVar74;
              std::_Deque_base<RgpCommandBuffer*,std::allocator<RgpCommandBuffer*>>::
              _M_initialize_map((ulong)&local_f8);
              pRVar3 = param_1 + lVar57 + 0x2031c0;
              *(undefined8 *)(param_1 + lVar57 + 0x2031c0) = local_2308._0_8_;
              *(undefined8 *)(param_1 + lVar57 + 0x2031c8) = local_2308._8_8_;
              *(ulong *)(param_1 + lVar57 + 0x2031c8 + 8) = local_22f8;
              *(undefined4 *)(param_1 + lVar57 + 0x2031d8) = uStack_22f0;
              *(ulong *)(param_1 + lVar57 + 0x2031dc) = CONCAT44(uStack_22e8,uStack_22ec);
              *(ulong *)(param_1 + lVar57 + 0x2031e8) = uStack_22e0;
              *(undefined4 *)(param_1 + lVar57 + 0x2031f0) = local_22d8._0_4_;
              *(undefined8 *)(param_1 + lVar57 + 0x2031f4) = local_22d8._4_8_;
              pRVar77 = pRVar3 + 0x20f0;
              *(undefined4 *)(param_1 + lVar57 + 0x2031fc) = local_22d8._12_4_;
              puVar68 = local_22c8;
              pRVar58 = param_1 + lVar57 + 0x203200;
              for (lVar46 = 0x400; lVar46 != 0; lVar46 = lVar46 + -1) {
                *(undefined8 *)pRVar58 = *puVar68;
                puVar68 = puVar68 + (ulong)bVar82 * -2 + 1;
                pRVar58 = pRVar58 + (ulong)bVar82 * -0x10 + 8;
              }
              *(undefined8 *)(param_1 + lVar57 + 0x205208) = local_2c0;
              *(undefined8 *)(param_1 + lVar57 + 0x205210) = uStack_2b8;
              param_1[lVar57 + 0x205200] = local_2c8;
              *(undefined8 *)(param_1 + lVar57 + 0x205218) = local_2b0;
              *(undefined8 *)(param_1 + lVar57 + 0x205220) = uStack_2a8;
              *(undefined4 *)(param_1 + lVar57 + 0x205204) = local_2c4;
              *(undefined8 *)(param_1 + lVar57 + 0x205228) = local_2a0;
              *(undefined8 *)(param_1 + lVar57 + 0x205230) = uStack_298;
              *(undefined8 *)(param_1 + lVar57 + 0x205238) = local_290;
              *(undefined8 *)(param_1 + lVar57 + 0x205240) = uStack_288;
              *(undefined1 **)(param_1 + lVar57 + 0x205248) = local_280;
              *(undefined8 *)(param_1 + lVar57 + 0x205250) = uStack_278;
              *(undefined8 *)(param_1 + lVar57 + 0x205278) = local_250;
              pRVar58 = pRVar3 + 0x2198;
              *(undefined8 *)(param_1 + lVar57 + 0x205258) = local_270;
              *(undefined8 *)(param_1 + lVar57 + 0x205260) = uStack_268;
              *(undefined8 *)(param_1 + lVar57 + 0x205268) = local_260;
              *(undefined8 *)(param_1 + lVar57 + 0x205270) = uStack_258;
              do {
                if (pRVar51 + -0x30 != pRVar77 + -0x30) {
                  puVar68 = *(undefined8 **)(pRVar77 + -0x20);
                  while (puVar68 != (undefined8 *)0x0) {
                    puVar48 = (undefined8 *)*puVar68;
                    operator_delete(puVar68,0x18);
                    puVar68 = puVar48;
                  }
                  if (*(RgpDataSetLoader **)(pRVar77 + -0x30) != pRVar77) {
                    operator_delete(*(RgpDataSetLoader **)(pRVar77 + -0x30),
                                    *(long *)(pRVar77 + -0x28) << 3);
                  }
                  uVar35 = *(undefined8 *)(pRVar51 + -8);
                  pRVar63 = *(RgpDataSetLoader **)(pRVar51 + -0x30);
                  *(undefined8 *)(pRVar77 + -0x10) = *(undefined8 *)(pRVar51 + -0x10);
                  *(undefined8 *)(pRVar77 + -8) = uVar35;
                  if (pRVar51 == pRVar63) {
                    *(undefined8 *)pRVar77 = *(undefined8 *)pRVar51;
                    pRVar63 = pRVar77;
                  }
                  uVar42 = *(ulong *)(pRVar51 + -0x28);
                  lVar46 = *(long *)(pRVar51 + -0x20);
                  *(RgpDataSetLoader **)(pRVar77 + -0x30) = pRVar63;
                  uVar35 = *(undefined8 *)(pRVar51 + -0x18);
                  *(ulong *)(pRVar77 + -0x28) = uVar42;
                  *(long *)(pRVar77 + -0x20) = lVar46;
                  *(undefined8 *)(pRVar77 + -0x18) = uVar35;
                  if (lVar46 != 0) {
                    *(RgpDataSetLoader **)(pRVar63 + ((ulong)*(uint *)(lVar46 + 8) % uVar42) * 8) =
                         pRVar77 + -0x20;
                  }
                  *(undefined8 *)(pRVar51 + -8) = 0;
                  *(undefined8 *)(pRVar51 + -0x28) = 1;
                  *(undefined8 *)pRVar51 = 0;
                  *(RgpDataSetLoader **)(pRVar51 + -0x30) = pRVar51;
                  *(undefined8 *)(pRVar51 + -0x20) = 0;
                  *(undefined8 *)(pRVar51 + -0x18) = 0;
                }
                pRVar51 = pRVar51 + 0x38;
                pRVar77 = pRVar77 + 0x38;
              } while (pRVar58 != pRVar77);
              do {
                if (pRVar74 + -0x30 != pRVar58 + -0x30) {
                  puVar68 = *(undefined8 **)(pRVar58 + -0x20);
                  while (puVar68 != (undefined8 *)0x0) {
                    puVar48 = (undefined8 *)*puVar68;
                    operator_delete(puVar68,0x20);
                    puVar68 = puVar48;
                  }
                  if (*(RgpDataSetLoader **)(pRVar58 + -0x30) != pRVar58) {
                    operator_delete(*(RgpDataSetLoader **)(pRVar58 + -0x30),
                                    *(long *)(pRVar58 + -0x28) << 3);
                  }
                  uVar35 = *(undefined8 *)(pRVar74 + -8);
                  pRVar77 = *(RgpDataSetLoader **)(pRVar74 + -0x30);
                  *(undefined8 *)(pRVar58 + -0x10) = *(undefined8 *)(pRVar74 + -0x10);
                  *(undefined8 *)(pRVar58 + -8) = uVar35;
                  if (pRVar74 == pRVar77) {
                    *(undefined8 *)pRVar58 = *(undefined8 *)pRVar74;
                    pRVar77 = pRVar58;
                  }
                  uVar42 = *(ulong *)(pRVar74 + -0x28);
                  lVar46 = *(long *)(pRVar74 + -0x20);
                  *(RgpDataSetLoader **)(pRVar58 + -0x30) = pRVar77;
                  uVar35 = *(undefined8 *)(pRVar74 + -0x18);
                  *(ulong *)(pRVar58 + -0x28) = uVar42;
                  *(long *)(pRVar58 + -0x20) = lVar46;
                  *(undefined8 *)(pRVar58 + -0x18) = uVar35;
                  if (lVar46 != 0) {
                    *(RgpDataSetLoader **)(pRVar77 + ((ulong)*(uint *)(lVar46 + 8) % uVar42) * 8) =
                         pRVar58 + -0x20;
                  }
                  *(undefined8 *)(pRVar74 + -8) = 0;
                  *(undefined8 *)(pRVar74 + -0x28) = 1;
                  *(undefined8 *)pRVar74 = 0;
                  *(RgpDataSetLoader **)(pRVar74 + -0x30) = pRVar74;
                  *(undefined8 *)(pRVar74 + -0x20) = 0;
                  *(undefined8 *)(pRVar74 + -0x18) = 0;
                }
                pRVar74 = pRVar74 + 0x38;
                pRVar58 = pRVar58 + 0x38;
              } while (pRVar3 + 0x2240 != pRVar58);
              lVar57 = *(long *)(pRVar3 + 0x2238);
              auVar17 = *(undefined1 (*) [16])(pRVar3 + 0x2230);
              auVar15 = *(undefined1 (*) [16])(pRVar3 + 0x2230);
              pvVar37 = *(void **)(pRVar3 + 0x2210);
              uVar7 = *(undefined8 *)(pRVar3 + 0x2240);
              uVar11 = *(undefined8 *)(pRVar3 + 0x2248);
              lVar46 = *(long *)(pRVar3 + 0x2218);
              uVar35 = *(undefined8 *)(pRVar3 + 0x2250);
              lVar75 = *(long *)(pRVar3 + 0x2258);
              auVar16 = *(undefined1 (*) [16])(pRVar3 + 0x2220);
              auVar14 = *(undefined1 (*) [16])(pRVar3 + 0x2220);
              *(undefined8 *)(pRVar3 + 0x2240) = local_c8._0_8_;
              *(undefined8 *)(pRVar3 + 0x2248) = local_c8._8_8_;
              *(void **)(pRVar3 + 0x2210) = local_f8;
              *(long *)(pRVar3 + 0x2218) = lStack_f0;
              local_f8 = pvVar37;
              lStack_f0 = lVar46;
              *(undefined8 *)(pRVar3 + 0x2220) = local_e8._0_8_;
              *(undefined8 *)(pRVar3 + 0x2228) = local_e8._8_8_;
              *(undefined8 *)(pRVar3 + 0x2230) = local_d8._0_8_;
              *(undefined8 *)(pRVar3 + 0x2238) = local_d8._8_8_;
              *(undefined8 *)(pRVar3 + 0x2250) = local_b8._0_8_;
              *(undefined8 *)(pRVar3 + 0x2258) = local_b8._8_8_;
              local_e8 = auVar14;
              local_d8 = auVar15;
              local_b8._0_8_ = uVar35;
              local_b8._8_8_ = lVar75;
              local_c8._0_8_ = uVar7;
              local_c8._8_8_ = uVar11;
              for (puVar68 = (undefined8 *)(lVar57 + 8); puVar68 < (undefined8 *)(lVar75 + 8);
                  puVar68 = puVar68 + 1) {
                operator_delete((void *)*puVar68,0x200);
              }
              lVar69 = lVar69 * 0x860d0;
              local_c8 = auVar16;
              *(undefined8 *)(param_1 + lVar69 + 0x205420) = local_a8;
              *(undefined4 *)(param_1 + lVar69 + 0x205458) = local_70;
              *(undefined8 *)(param_1 + lVar69 + 0x205428) = local_a0;
              *(undefined8 *)(param_1 + lVar69 + 0x205430) = uStack_98;
              *(undefined8 *)(param_1 + lVar69 + 0x205438) = local_90;
              *(undefined8 *)(param_1 + lVar69 + 0x205440) = uStack_88;
              *(undefined8 *)(param_1 + lVar69 + 0x205448) = local_80;
              *(undefined8 *)(param_1 + lVar69 + 0x205450) = uStack_78;
              *(undefined8 *)(param_1 + lVar69 + 0x205470) = local_58;
              *(undefined8 *)(param_1 + lVar69 + 0x205460) = local_68;
              *(undefined8 *)(param_1 + lVar69 + 0x205460 + 8) = uStack_60;
              local_b8 = auVar17;
              *(undefined8 *)(param_1 + lVar69 + 0x205478) = local_50;
              *(undefined4 *)(param_1 + lVar69 + 0x205480) = local_48;
              if (local_f8 != (void *)0x0) {
                for (puVar68 = (undefined8 *)local_d8._8_8_; puVar68 < (undefined8 *)(lVar57 + 8);
                    puVar68 = puVar68 + 1) {
                  operator_delete((void *)*puVar68,0x200);
                }
                operator_delete(local_f8,lStack_f0 * 8);
              }
              ppuVar59 = &local_130;
              ppuVar52 = &local_1d8;
              do {
                while( true ) {
                  puVar68 = (undefined8 *)ppuVar59[2];
                  while (puVar68 != (undefined8 *)0x0) {
                    puVar48 = (undefined8 *)*puVar68;
                    operator_delete(puVar68,0x20);
                    puVar68 = puVar48;
                  }
                  memset(*ppuVar59,0,(long)ppuVar59[1] * 8);
                  ppuVar8 = (undefined1 **)*ppuVar59;
                  ppuVar59[3] = (undefined1 *)0x0;
                  ppuVar59[2] = (undefined1 *)0x0;
                  ppuVar9 = ppuVar59 + 1;
                  if (ppuVar8 == ppuVar59 + 6) break;
                  ppuVar59 = ppuVar59 + -7;
                  operator_delete(ppuVar8,(long)*ppuVar9 << 3);
                  if (ppuVar52 == ppuVar59) goto LAB_00b4c4cc;
                }
                ppuVar59 = ppuVar59 + -7;
              } while (ppuVar52 != ppuVar59);
LAB_00b4c4cc:
              do {
                while( true ) {
                  puVar68 = (undefined8 *)ppuVar52[2];
                  while (puVar68 != (undefined8 *)0x0) {
                    puVar48 = (undefined8 *)*puVar68;
                    operator_delete(puVar68,0x18);
                    puVar68 = puVar48;
                  }
                  memset(*ppuVar52,0,(long)ppuVar52[1] * 8);
                  ppuVar9 = (undefined1 **)*ppuVar52;
                  ppuVar59 = ppuVar52 + 1;
                  ppuVar52[3] = (undefined1 *)0x0;
                  ppuVar52[2] = (undefined1 *)0x0;
                  if (ppuVar9 == ppuVar52 + 6) break;
                  ppuVar52 = ppuVar52 + -7;
                  operator_delete(ppuVar9,(long)*ppuVar59 << 3);
                  if (&local_280 == ppuVar52) goto LAB_00b4c546;
                }
                ppuVar52 = ppuVar52 + -7;
              } while (&local_280 != ppuVar52);
LAB_00b4c546:
              RgpInstrumentationProcessorInitialize
                        (pRVar3,param_1,iVar55,iVar79,*(undefined4 *)(param_1 + 0x368),
                         *(undefined4 *)(param_1 + 0x798),*(undefined4 *)(param_1 + 0x79c));
            }
            iVar79 = iVar79 + 1;
          } while (iVar79 != 4);
          iVar55 = iVar55 + 1;
        } while (iVar55 != 3);
        while (iVar55 = RgpSqttParserAdvance(pRVar49,(RgpSqttToken *)local_2308,0,1), iVar55 == 0) {
          uVar35 = *(undefined8 *)(pRVar49 + 8);
          *(undefined8 *)(param_1 + 0xc39718) = *(undefined8 *)pRVar49;
          *(undefined8 *)(param_1 + 0xc39720) = uVar35;
          uVar35 = *(undefined8 *)(pRVar49 + 0x18);
          *(undefined8 *)(param_1 + 0xc39728) = *(undefined8 *)(pRVar49 + 0x10);
          *(undefined8 *)(param_1 + 0xc39730) = uVar35;
          uVar35 = *(undefined8 *)(pRVar49 + 0x28);
          *(undefined8 *)(param_1 + 0xc39738) = *(undefined8 *)(pRVar49 + 0x20);
          *(undefined8 *)(param_1 + 0xc39740) = uVar35;
          uVar35 = *(undefined8 *)(pRVar49 + 0x38);
          *(undefined8 *)(param_1 + 0xc39748) = *(undefined8 *)(pRVar49 + 0x30);
          *(undefined8 *)(param_1 + 0xc39750) = uVar35;
          uVar35 = *(undefined8 *)(pRVar49 + 0x48);
          *(undefined8 *)(param_1 + 0xc39758) = *(undefined8 *)(pRVar49 + 0x40);
          *(undefined8 *)(param_1 + 0xc39760) = uVar35;
          uVar35 = *(undefined8 *)(pRVar49 + 0x58);
          *(undefined8 *)(param_1 + 0xc39768) = *(undefined8 *)(pRVar49 + 0x50);
          *(undefined8 *)(param_1 + 0xc39770) = uVar35;
          uVar35 = *(undefined8 *)(pRVar49 + 0x68);
          *(undefined8 *)(param_1 + 0xc39778) = *(undefined8 *)(pRVar49 + 0x60);
          *(undefined8 *)(param_1 + 0xc39780) = uVar35;
          uVar35 = *(undefined8 *)(pRVar49 + 0x78);
          *(undefined8 *)(param_1 + 0xc39788) = *(undefined8 *)(pRVar49 + 0x70);
          *(undefined8 *)(param_1 + 0xc39790) = uVar35;
          uVar35 = *(undefined8 *)(pRVar49 + 0x88);
          *(undefined8 *)(param_1 + 0xc39798) = *(undefined8 *)(pRVar49 + 0x80);
          *(undefined8 *)(param_1 + 0xc397a0) = uVar35;
          uVar35 = *(undefined8 *)(pRVar49 + 0x98);
          *(undefined8 *)(param_1 + 0xc397a8) = *(undefined8 *)(pRVar49 + 0x90);
          *(undefined8 *)(param_1 + 0xc397b0) = uVar35;
          uVar35 = *(undefined8 *)(pRVar49 + 0xa8);
          *(undefined8 *)(param_1 + 0xc397b8) = *(undefined8 *)(pRVar49 + 0xa0);
          *(undefined8 *)(param_1 + 0xc397c0) = uVar35;
          uVar35 = *(undefined8 *)(pRVar49 + 0xb8);
          *(undefined8 *)(param_1 + 0xc397c8) = *(undefined8 *)(pRVar49 + 0xb0);
          *(undefined8 *)(param_1 + 0xc397d0) = uVar35;
          *(undefined8 *)(param_1 + 0xc397d8) = *(undefined8 *)(pRVar49 + 0xc0);
          uVar45 = *(uint *)(pRVar49 + 0x94);
          iVar55 = RgpSqttParserGetSqttDataSize(pRVar49);
          if ((uint)(iVar55 * 2) < uVar45) break;
          cVar28 = RgpSqttParserDataIsValid(pRVar49);
          if (cVar28 != '\0') {
            if (param_1[0xbc8860] == (RgpDataSetLoader)0x0) {
              (anonymous_namespace)::SqttTokenHandlerForProfile(param_1,(RgpSqttToken *)local_2308);
            }
            else {
              (anonymous_namespace)::TokenProcessor(param_1,(RgpSqttToken *)local_2308);
            }
          }
        }
        if ((iVar32 == 0) && (param_2 != '\0')) {
          RgpSpmDataProvider::MapRTTimestampsToSClk
                    (*(RgpSpmDataProvider **)(param_1 + 0x1808e8),
                     *(undefined8 *)(param_1 + 0x9b10e0),*(undefined8 *)(param_1 + 0x1808c8),
                     *(undefined8 *)(param_1 + 0x1808d8),*(undefined4 *)(param_1 + 0x7a0));
        }
        if (pRVar49[0x68] == (RgpDataSetLoader)0x0) {
          *(undefined8 *)(local_2438 + 0x18) = 0;
        }
        else {
          *(undefined8 *)(local_2438 + 0x18) = *(undefined8 *)(pRVar49 + 0x60);
        }
        pRVar77 = pRVar49 + 0xc0;
        local_2440 = local_2440 + 1;
        pRVar49 = pRVar49 + 200;
        *(undefined4 *)(local_2438 + 0x20) = *(undefined4 *)pRVar77;
        local_2438 = local_2438 + 0x28;
      } while ((int)local_2440 < *(int *)(param_1 + 0x114));
    }
    if (iVar30 < 1) {
      *(int *)(param_3 + 0x650) = *(int *)(param_3 + 0x650) << 2;
      RgpWavefrontProcessorEnd(pRVar1);
    }
    else {
      iVar32 = *(int *)(param_3 + 0x650) + *(int *)(param_1 + 0x2055a0);
      *(int *)(param_3 + 0x650) = iVar32;
      iVar32 = iVar32 + *(int *)(param_1 + 0x2055a4);
      *(int *)(param_3 + 0x650) = iVar32;
      iVar32 = iVar32 + *(int *)(param_1 + 0x2055a8);
      *(int *)(param_3 + 0x650) = iVar32;
      iVar32 = iVar32 + *(int *)(param_1 + 0x2055ac);
      *(int *)(param_3 + 0x650) = iVar32;
      if (iVar30 != 1) {
        iVar55 = *(int *)(param_1 + 0x28b670);
        *(int *)(param_3 + 0x650) = iVar32 + iVar55;
        iVar32 = iVar32 + iVar55 + *(int *)(param_1 + 0x28b674);
        *(int *)(param_3 + 0x650) = iVar32;
        iVar32 = iVar32 + *(int *)(param_1 + 0x28b678);
        *(int *)(param_3 + 0x650) = iVar32;
        iVar32 = iVar32 + *(int *)(param_1 + 0x28b67c);
        *(int *)(param_3 + 0x650) = iVar32;
        if (iVar30 != 2) {
          iVar55 = *(int *)(param_1 + 0x311740);
          *(int *)(param_3 + 0x650) = iVar32 + iVar55;
          iVar32 = iVar32 + iVar55 + *(int *)(param_1 + 0x311744);
          *(int *)(param_3 + 0x650) = iVar32;
          iVar32 = iVar32 + *(int *)(param_1 + 0x311748);
          *(int *)(param_3 + 0x650) = iVar32;
          iVar32 = iVar32 + *(int *)(param_1 + 0x31174c);
          *(int *)(param_3 + 0x650) = iVar32;
          if (iVar30 != 3) {
            iVar55 = *(int *)(param_1 + 0x397810);
            *(int *)(param_3 + 0x650) = iVar32 + iVar55;
            iVar32 = iVar32 + iVar55 + *(int *)(param_1 + 0x397814);
            *(int *)(param_3 + 0x650) = iVar32;
            iVar32 = iVar32 + *(int *)(param_1 + 0x397818);
            *(int *)(param_3 + 0x650) = iVar32;
            iVar32 = iVar32 + *(int *)(param_1 + 0x39781c);
            *(int *)(param_3 + 0x650) = iVar32;
            if (iVar30 != 4) {
              iVar55 = *(int *)(param_1 + 0x41d8e0);
              *(int *)(param_3 + 0x650) = iVar32 + iVar55;
              iVar32 = iVar32 + iVar55 + *(int *)(param_1 + 0x41d8e4);
              *(int *)(param_3 + 0x650) = iVar32;
              iVar32 = iVar32 + *(int *)(param_1 + 0x41d8e8);
              *(int *)(param_3 + 0x650) = iVar32;
              iVar32 = iVar32 + *(int *)(param_1 + 0x41d8ec);
              *(int *)(param_3 + 0x650) = iVar32;
              if (iVar30 != 5) {
                iVar55 = *(int *)(param_1 + 0x4a39b0);
                *(int *)(param_3 + 0x650) = iVar32 + iVar55;
                iVar32 = iVar32 + iVar55 + *(int *)(param_1 + 0x4a39b4);
                *(int *)(param_3 + 0x650) = iVar32;
                iVar32 = iVar32 + *(int *)(param_1 + 0x4a39b8);
                *(int *)(param_3 + 0x650) = iVar32;
                iVar32 = iVar32 + *(int *)(param_1 + 0x4a39bc);
                *(int *)(param_3 + 0x650) = iVar32;
                if (iVar30 != 6) {
                  iVar55 = *(int *)(param_1 + 0x529a80);
                  *(int *)(param_3 + 0x650) = iVar32 + iVar55;
                  iVar32 = iVar32 + iVar55 + *(int *)(param_1 + 0x529a84);
                  *(int *)(param_3 + 0x650) = iVar32;
                  iVar32 = iVar32 + *(int *)(param_1 + 0x529a88);
                  *(int *)(param_3 + 0x650) = iVar32;
                  iVar32 = iVar32 + *(int *)(param_1 + 0x529a8c);
                  *(int *)(param_3 + 0x650) = iVar32;
                  if (iVar30 != 7) {
                    iVar55 = *(int *)(param_1 + 0x5afb50);
                    *(int *)(param_3 + 0x650) = iVar32 + iVar55;
                    iVar32 = iVar32 + iVar55 + *(int *)(param_1 + 0x5afb54);
                    *(int *)(param_3 + 0x650) = iVar32;
                    iVar32 = iVar32 + *(int *)(param_1 + 0x5afb58);
                    *(int *)(param_3 + 0x650) = iVar32;
                    iVar32 = iVar32 + *(int *)(param_1 + 0x5afb5c);
                    *(int *)(param_3 + 0x650) = iVar32;
                    if (iVar30 != 8) {
                      iVar55 = *(int *)(param_1 + 0x635c20);
                      *(int *)(param_3 + 0x650) = iVar32 + iVar55;
                      iVar32 = iVar32 + iVar55 + *(int *)(param_1 + 0x635c24);
                      *(int *)(param_3 + 0x650) = iVar32;
                      iVar32 = iVar32 + *(int *)(param_1 + 0x635c28);
                      *(int *)(param_3 + 0x650) = iVar32;
                      iVar32 = iVar32 + *(int *)(param_1 + 0x635c2c);
                      *(int *)(param_3 + 0x650) = iVar32;
                      if (iVar30 != 9) {
                        iVar55 = *(int *)(param_1 + 0x6bbcf0);
                        *(int *)(param_3 + 0x650) = iVar32 + iVar55;
                        iVar32 = iVar32 + iVar55 + *(int *)(param_1 + 0x6bbcf4);
                        *(int *)(param_3 + 0x650) = iVar32;
                        iVar32 = iVar32 + *(int *)(param_1 + 0x6bbcf8);
                        *(int *)(param_3 + 0x650) = iVar32;
                        iVar32 = iVar32 + *(int *)(param_1 + 0x6bbcfc);
                        *(int *)(param_3 + 0x650) = iVar32;
                        if (iVar30 != 10) {
                          iVar55 = *(int *)(param_1 + 0x741dc0);
                          *(int *)(param_3 + 0x650) = iVar32 + iVar55;
                          iVar32 = iVar32 + iVar55 + *(int *)(param_1 + 0x741dc4);
                          *(int *)(param_3 + 0x650) = iVar32;
                          iVar32 = iVar32 + *(int *)(param_1 + 0x741dc8);
                          *(int *)(param_3 + 0x650) = iVar32;
                          iVar32 = iVar32 + *(int *)(param_1 + 0x741dcc);
                          *(int *)(param_3 + 0x650) = iVar32;
                          if (iVar30 != 0xb) {
                            iVar55 = *(int *)(param_1 + 0x7c7e90);
                            *(int *)(param_3 + 0x650) = iVar32 + iVar55;
                            iVar32 = iVar32 + iVar55 + *(int *)(param_1 + 0x7c7e94);
                            *(int *)(param_3 + 0x650) = iVar32;
                            iVar32 = iVar32 + *(int *)(param_1 + 0x7c7e98);
                            *(int *)(param_3 + 0x650) = iVar32;
                            iVar32 = iVar32 + *(int *)(param_1 + 0x7c7e9c);
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
      *(int *)(param_3 + 0x650) = iVar32 << 2;
      RgpWavefrontProcessorEnd(pRVar1);
      do {
        pRVar61 = pRVar60 + 0x860d0;
        RgpEventProcessorEnd(pRVar60);
        pRVar60 = pRVar61;
      } while (pRVar61 != (RgpEventProcessor *)(param_1 + (ulong)(iVar30 - 1) * 0x860d0 + 0x206df8))
      ;
    }
    RgpInstSequencerEnd(*(RgpInstSequencer **)(param_1 + 0x9b1160));
    uVar35 = *(undefined8 *)(param_1 + 0xbc8ef8);
    pvVar37 = *(void **)(param_3 + 0x2ab8);
    *(undefined8 *)(param_3 + 0x2ab8) = *(undefined8 *)(param_1 + 0xbc8ef0);
    *(undefined8 *)(param_3 + 0x2ac0) = uVar35;
    lVar69 = *(long *)(param_3 + 0x2ac8);
    *(undefined8 *)(param_3 + 0x2ac8) = *(undefined8 *)(param_1 + 0xbc8f00);
    *(undefined8 *)(param_1 + 0xbc8f00) = 0;
    *(undefined1 (*) [16])(param_1 + 0xbc8ef0) = (undefined1  [16])0x0;
    if (pvVar37 != (void *)0x0) {
      operator_delete(pvVar37,lVar69 - (long)pvVar37);
    }
    uVar42 = (ulong)*(uint *)(param_3 + 0x648);
    if ((int)*(uint *)(param_3 + 0x648) < 1) {
      *(undefined8 *)(param_3 + 0x628) = 0;
    }
    else {
      lVar69 = 0;
      uVar47 = 0;
      do {
        puVar68 = (undefined8 *)(*(long *)(param_3 + 0x630) + lVar69 * 0x28);
        pRVar10 = (RgpEvent *)*puVar68;
        uVar35 = RgpEventGetMinimumTimestamp(pRVar10);
        uVar36 = RgpEventGetMaximumTimestamp(pRVar10);
        uVar45 = *(uint *)(param_3 + 0x648);
        uVar42 = (ulong)uVar45;
        if (uVar47 < uVar36) {
          uVar47 = uVar36;
        }
        lVar69 = lVar69 + 1;
        puVar68[2] = uVar35;
        puVar68[3] = uVar36;
      } while ((int)lVar69 < (int)uVar45);
      _local_2378 = (undefined1  [16])0x0;
      *(ulong *)(param_3 + 0x628) = uVar47;
      _local_2368 = (undefined1  [16])0x0;
      _local_2358 = (undefined1  [16])0x0;
      local_2348 = (undefined1  [16])0x0;
      local_2308 = (undefined1  [16])0x0;
      local_22f8 = 0;
      uStack_22f0 = 0;
      uStack_22ec = 0;
      uStack_22e8 = 0;
      uStack_22e4 = 0;
      uStack_22e0 = 0;
      local_22d8 = (undefined1  [16])0x0;
      if (0 < (int)uVar45) {
        lVar46 = 0;
        lVar69 = 0;
        do {
          pRVar10 = *(RgpEvent **)(*(long *)(param_3 + 0x630) + lVar46 * 0x28);
          iVar30 = *(int *)(pRVar10 + 0x21c);
          if ((0 < iVar30) && (iVar32 = *(int *)(param_3 + 0x128), 0 < iVar32)) {
            uVar42 = *(ulong *)(pRVar10 + 0x120);
            uVar45 = 0;
            if ((ulong)local_2378 <= uVar42) {
              uVar45 = (uint)(uVar42 <= (ulong)local_2308._0_8_);
            }
            if (iVar32 != 1) {
              if (uStack_2370 <= uVar42) {
                uVar45 = (uVar45 + 1) - (uint)((ulong)local_2308._8_8_ < uVar42);
              }
              if (iVar32 != 2) {
                if ((ulong)local_2368 <= uVar42) {
                  uVar45 = (uVar45 + 1) - (uint)(local_22f8 < uVar42);
                }
                if (iVar32 != 3) {
                  if (uStack_2360 <= uVar42) {
                    uVar45 = (uVar45 + 1) - (uint)(CONCAT44(uStack_22ec,uStack_22f0) < uVar42);
                  }
                  if (iVar32 != 4) {
                    if (_local_2358 <= uVar42) {
                      uVar45 = (uVar45 + 1) - (uint)(CONCAT44(uStack_22e4,uStack_22e8) < uVar42);
                    }
                    if (iVar32 != 5) {
                      if ((uVar42 < uStack_2350) || (uStack_22e0 < uVar42)) {
                        if (iVar32 != 6) goto LAB_00b4d2dd;
                      }
                      else {
                        uVar45 = uVar45 + 1;
                        if (iVar32 != 6) {
LAB_00b4d2dd:
                          if ((ulong)local_2348._0_8_ <= uVar42) {
                            uVar45 = (uVar45 + 1) - (uint)((ulong)local_22d8._0_8_ < uVar42);
                          }
                          if ((iVar32 != 7) && ((ulong)local_2348._8_8_ <= uVar42)) {
                            uVar45 = (uVar45 + 1) - (uint)((ulong)local_22d8._8_8_ < uVar42);
                          }
                        }
                        uVar47 = uVar42 - lVar69;
                        if ((uVar42 - *(long *)(local_2308 + (long)iVar30 * 8) < 5000 &&
                             1000 < uVar47) && (uVar45 == 6)) {
                          uVar42 = 0x32;
                          if (0x31 < (long)uVar47) {
                            uVar42 = uVar47;
                          }
                          *(ulong *)(pRVar10 + 0x228) = uVar42 - 0x32;
                        }
                      }
                    }
                  }
                }
              }
            }
          }
          uVar42 = *(ulong *)(local_2378 + (long)iVar30 * 8);
          uVar47 = RgpEventGetMinimumTimestamp(pRVar10);
          if (uVar47 < uVar42) {
            lVar69 = (long)*(int *)(pRVar10 + 0x21c);
            uVar35 = *(undefined8 *)(local_2378 + lVar69 * 8);
          }
          else {
            uVar35 = RgpEventGetMinimumTimestamp(pRVar10);
            lVar69 = (long)*(int *)(pRVar10 + 0x21c);
          }
          uVar42 = *(ulong *)(local_2308 + lVar69 * 8);
          *(undefined8 *)(local_2378 + lVar69 * 8) = uVar35;
          uVar47 = RgpEventGetMaximumTimestamp(pRVar10);
          if (uVar42 <= uVar47) {
            uVar35 = RgpEventGetMaximumTimestamp(pRVar10);
            *(undefined8 *)(local_2308 + (long)*(int *)(pRVar10 + 0x21c) * 8) = uVar35;
          }
          lVar69 = *(long *)(pRVar10 + 0x120);
          uVar42 = (ulong)*(uint *)(param_3 + 0x648);
          lVar46 = lVar46 + 1;
        } while ((int)lVar46 < (int)*(uint *)(param_3 + 0x648));
      }
    }
    uVar45 = (uint)uVar42;
    if (((uVar45 != 0) && (uVar47 = (ulong)(int)uVar45, uVar47 == (uVar47 & 0x1fffffffffffffff))) &&
       (puVar68 = malloc(uVar47 * 8), puVar68 != (undefined8 *)0x0)) {
      if (0 < (int)uVar45) {
        puVar48 = *(undefined8 **)(param_3 + 0x630);
        if ((puVar68 < puVar48 + uVar47 * 5 + -4 && puVar48 < puVar68 + uVar47) ||
           (uVar45 - 1 < 0xf)) {
          puVar62 = puVar68;
          do {
            uVar35 = *puVar48;
            puVar65 = puVar62 + 1;
            puVar48 = puVar48 + 5;
            *puVar62 = uVar35;
            puVar62 = puVar65;
          } while (puVar68 + uVar42 != puVar65);
        }
        else {
          puVar62 = puVar48;
          puVar65 = puVar68;
          do {
            uVar35 = *puVar62;
            uVar7 = puVar62[5];
            puVar66 = puVar65 + 2;
            puVar62 = puVar62 + 10;
            *puVar65 = uVar35;
            puVar65[1] = uVar7;
            puVar65 = puVar66;
          } while (puVar66 != puVar68 + (uVar42 & 0xfffffffffffffffe));
          if ((uVar42 & 1) != 0) {
            puVar68[uVar45 & 0xfffffffe] = puVar48[(ulong)(uVar45 & 0xfffffffe) * 5];
          }
        }
      }
      qsort(puVar68,uVar47,8,(anonymous_namespace)::EventDurationComparisonFunc);
      lVar69 = 0;
      if (0 < *(int *)(param_3 + 0x648)) {
        do {
          *(int *)(puVar68[lVar69] + 0x218) = (int)lVar69;
          lVar69 = lVar69 + 1;
        } while ((int)lVar69 < *(int *)(param_3 + 0x648));
      }
      free(puVar68);
    }
    (anonymous_namespace)::ProcessQueueTimings(param_3);
    iVar30 = RgpAsicParametersGetTotalFrontendPipes(param_3);
    *(undefined8 *)(param_3 + 0x778) = 0;
    *(undefined8 *)(param_3 + 0x830) = 0;
    puVar68 = (undefined8 *)((ulong)(param_3 + 0x780) & 0xfffffffffffffff8);
    for (uVar42 = (ulong)(((int)param_3 -
                          (int)(undefined8 *)((ulong)(param_3 + 0x780) & 0xfffffffffffffff8)) +
                          0x838U >> 3); uVar42 != 0; uVar42 = uVar42 - 1) {
      *puVar68 = 0;
      puVar68 = puVar68 + (ulong)bVar82 * -2 + 1;
    }
    param_3[0x64c] = (RgpDataSet)(0 < *(int *)(param_3 + 0x2ab0));
    if (*(int *)(param_3 + 0x2ab0) < 1) {
      if (0 < iVar30) goto LAB_00b4cd6c;
    }
    else {
      lVar69 = 0;
      do {
        lVar46 = lVar69 + 1;
        lVar69 = lVar69 * 0x30 + *(long *)(param_3 + 0x2aa8);
        iVar32 = RgpAsicParametersGetFrontendPipelineIndex
                           (param_3,*(undefined4 *)(lVar69 + 0x20),*(undefined4 *)(lVar69 + 0x24));
        *(int *)(param_3 + (long)iVar32 * 0x10 + 0x780) =
             *(int *)(param_3 + (long)iVar32 * 0x10 + 0x780) + 1;
        lVar69 = lVar46;
      } while ((int)lVar46 < *(int *)(param_3 + 0x2ab0));
      if (iVar30 < 1) {
        if (*(int *)(param_3 + 0x2ab0) < 1) goto LAB_00b4d18b;
LAB_00b4cfba:
        lVar69 = *(long *)(param_3 + 0x2aa8);
        lVar46 = 0;
        do {
          lVar75 = lVar46 + 1;
          lVar46 = lVar46 * 0x30;
          iVar32 = RgpAsicParametersGetFrontendPipelineIndex
                             (param_3,*(undefined4 *)(lVar69 + lVar46 + 0x20),
                              *(undefined4 *)(lVar69 + lVar46 + 0x24));
          lVar57 = (long)iVar32;
          lVar69 = *(long *)(param_3 + 0x2aa8);
          iVar32 = *(int *)(local_2378 + lVar57 * 4);
          uVar35 = ((undefined8 *)(lVar69 + lVar46))[1];
          puVar48 = (undefined8 *)((long)iVar32 * 0x30 + *(long *)(param_3 + lVar57 * 0x10 + 0x778))
          ;
          *puVar48 = *(undefined8 *)(lVar69 + lVar46);
          puVar48[1] = uVar35;
          puVar68 = (undefined8 *)(lVar69 + 0x10 + lVar46);
          uVar35 = puVar68[1];
          puVar48[2] = *puVar68;
          puVar48[3] = uVar35;
          puVar68 = (undefined8 *)(lVar69 + 0x20 + lVar46);
          uVar35 = puVar68[1];
          puVar48[4] = *puVar68;
          puVar48[5] = uVar35;
          *(int *)(local_2378 + lVar57 * 4) = iVar32 + 1;
          lVar46 = lVar75;
        } while ((int)lVar75 < *(int *)(param_3 + 0x2ab0));
        puVar68 = (undefined8 *)local_2308;
        for (lVar69 = 0x100; lVar69 != 0; lVar69 = lVar69 + -1) {
          *puVar68 = 0;
          puVar68 = puVar68 + (ulong)bVar82 * -2 + 1;
        }
        if (iVar30 < 1) goto LAB_00b4d18b;
      }
      else {
LAB_00b4cd6c:
        if (0 < *(int *)(param_3 + 0x780)) {
          pvVar37 = malloc((long)*(int *)(param_3 + 0x780) * 0x30);
          *(void **)(param_3 + 0x778) = pvVar37;
        }
        auVar21._12_4_ = 0;
        auVar21._0_12_ = stack0xffffffffffffdc8c;
        _local_2378 = auVar21 << 0x20;
        if (iVar30 != 1) {
          if (0 < *(int *)(param_3 + 0x790)) {
            pvVar37 = malloc((long)*(int *)(param_3 + 0x790) * 0x30);
            *(void **)(param_3 + 0x788) = pvVar37;
          }
          local_2378._4_4_ = 0;
          if (iVar30 != 2) {
            if (0 < *(int *)(param_3 + 0x7a0)) {
              pvVar37 = malloc((long)*(int *)(param_3 + 0x7a0) * 0x30);
              *(void **)(param_3 + 0x798) = pvVar37;
            }
            uStack_2370._0_4_ = 0;
            if (iVar30 != 3) {
              if (0 < *(int *)(param_3 + 0x7b0)) {
                pvVar37 = malloc((long)*(int *)(param_3 + 0x7b0) * 0x30);
                *(void **)(param_3 + 0x7a8) = pvVar37;
              }
              uStack_2370._4_4_ = 0;
              if (iVar30 != 4) {
                if (0 < *(int *)(param_3 + 0x7c0)) {
                  pvVar37 = malloc((long)*(int *)(param_3 + 0x7c0) * 0x30);
                  *(void **)(param_3 + 0x7b8) = pvVar37;
                }
                auVar22._12_4_ = 0;
                auVar22._0_12_ = stack0xffffffffffffdc9c;
                _local_2368 = auVar22 << 0x20;
                if (iVar30 != 5) {
                  if (0 < *(int *)(param_3 + 2000)) {
                    pvVar37 = malloc((long)*(int *)(param_3 + 2000) * 0x30);
                    *(void **)(param_3 + 0x7c8) = pvVar37;
                  }
                  local_2368._4_4_ = 0;
                  if (iVar30 != 6) {
                    if (0 < *(int *)(param_3 + 0x7e0)) {
                      pvVar37 = malloc((long)*(int *)(param_3 + 0x7e0) * 0x30);
                      *(void **)(param_3 + 0x7d8) = pvVar37;
                    }
                    uStack_2360._0_4_ = 0;
                    if (iVar30 != 7) {
                      if (0 < *(int *)(param_3 + 0x7f0)) {
                        pvVar37 = malloc((long)*(int *)(param_3 + 0x7f0) * 0x30);
                        *(void **)(param_3 + 0x7e8) = pvVar37;
                      }
                      uStack_2360._4_4_ = 0;
                      if (iVar30 != 8) {
                        if (0 < *(int *)(param_3 + 0x800)) {
                          pvVar37 = malloc((long)*(int *)(param_3 + 0x800) * 0x30);
                          *(void **)(param_3 + 0x7f8) = pvVar37;
                        }
                        auVar23._12_4_ = 0;
                        auVar23._0_12_ = stack0xffffffffffffdcac;
                        _local_2358 = auVar23 << 0x20;
                        if (iVar30 != 9) {
                          if (0 < *(int *)(param_3 + 0x810)) {
                            pvVar37 = malloc((long)*(int *)(param_3 + 0x810) * 0x30);
                            *(void **)(param_3 + 0x808) = pvVar37;
                          }
                          stack0xffffffffffffdcac = 0;
                          if (iVar30 != 10) {
                            if (0 < *(int *)(param_3 + 0x820)) {
                              pvVar37 = malloc((long)*(int *)(param_3 + 0x820) * 0x30);
                              *(void **)(param_3 + 0x818) = pvVar37;
                            }
                            uStack_2350._0_4_ = 0;
                            if (iVar30 != 0xb) {
                              if (0 < *(int *)(param_3 + 0x830)) {
                                pvVar37 = malloc((long)*(int *)(param_3 + 0x830) * 0x30);
                                *(void **)(param_3 + 0x828) = pvVar37;
                              }
                              uStack_2350._4_4_ = 0;
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
        if (0 < *(int *)(param_3 + 0x2ab0)) goto LAB_00b4cfba;
        puVar68 = (undefined8 *)local_2308;
        for (lVar69 = 0x100; lVar69 != 0; lVar69 = lVar69 + -1) {
          *puVar68 = 0;
          puVar68 = puVar68 + (ulong)bVar82 * -2 + 1;
        }
      }
      uVar47 = 0;
      iVar32 = 0;
      pRVar81 = param_3 + 0x6b8;
      uVar42 = 0;
      do {
        iVar55 = *(int *)(pRVar81 + 8);
        if ((0 < iVar55) && (iVar79 = *(int *)(pRVar81 + 200), 0 < iVar79)) {
          iVar78 = 0;
          iVar73 = 0;
          iVar56 = 0;
          iVar71 = 0;
          iVar80 = iVar78;
          do {
            lVar69 = (long)iVar80 * 0x418 + *(long *)pRVar81;
            lVar46 = (long)iVar78 * 0x30 + *(long *)(pRVar81 + 0xc0);
            if (*(ulong *)(lVar69 + 0x120) <= *(ulong *)(lVar46 + 0x10)) goto LAB_00b4d0f9;
            iVar6 = *(int *)(lVar46 + 8);
            iVar78 = iVar78 + 1;
            iVar71 = iVar71 + 1;
            if (iVar6 != 3) {
              if (iVar6 == 2) {
                if (iVar56 != 0) {
                  iVar56 = iVar56 + -1;
                  lVar46 = (long)iVar56;
                  local_23d0 = *(ulong *)(local_2308 + lVar46 * 8);
                  uVar47 = (ulong)*(uint *)(local_2308 + lVar46 * 8);
                  uVar42 = (ulong)(byte)local_2308[lVar46 * 8 + 4];
                }
                goto LAB_00b4d388;
              }
              if (iVar6 == 1) {
                iVar32 = iVar32 + 1;
                goto LAB_00b4d845;
              }
              if (iVar6 != 4) goto LAB_00b4d388;
LAB_00b4d161:
              if (iVar78 < iVar79) goto LAB_00b4d16b;
LAB_00b4d39f:
              if (iVar80 < iVar55) {
                lVar69 = *(long *)pRVar81;
                uVar45 = iVar55 - iVar80;
                uVar31 = (undefined4)uVar47;
                uVar29 = (undefined1)uVar42;
                if (uVar45 - 1 < 0xf) goto LAB_00b4d5b0;
                lVar46 = (long)iVar80 * 0x418;
                puVar70 = (undefined1 *)(lVar69 + 0x300 + lVar46);
                puVar2 = puVar70 + 0x4180;
                puVar68 = (undefined8 *)(lVar69 + 0x2e8 + lVar46);
                puVar64 = (undefined4 *)(lVar69 + 0x2f0 + lVar46);
                puVar72 = puVar2;
                while( true ) {
                  *puVar64 = uVar31;
                  puVar64[0x106] = uVar31;
                  puVar64[0x20c] = uVar31;
                  puVar64[0x312] = uVar31;
                  puVar64[0x418] = uVar31;
                  puVar64[0x51e] = uVar31;
                  puVar64[0x624] = uVar31;
                  puVar64[0x72a] = uVar31;
                  puVar64[0x830] = uVar31;
                  puVar64[0x936] = uVar31;
                  puVar64[0xa3c] = uVar31;
                  puVar64[0xb42] = uVar31;
                  puVar64[0xc48] = uVar31;
                  puVar64[0xd4e] = uVar31;
                  puVar64[0xe54] = uVar31;
                  puVar64[0xf5a] = uVar31;
                  *puVar70 = uVar29;
                  puVar70[0x418] = uVar29;
                  puVar70[0x830] = uVar29;
                  puVar70[0xc48] = uVar29;
                  puVar70[0x1060] = uVar29;
                  puVar70[0x1478] = uVar29;
                  puVar70[0x1890] = uVar29;
                  puVar70[0x1ca8] = uVar29;
                  puVar70[0x20c0] = uVar29;
                  puVar70[0x24d8] = uVar29;
                  puVar70[0x28f0] = uVar29;
                  puVar70[0x2d08] = uVar29;
                  puVar70[0x3120] = uVar29;
                  puVar70[0x3538] = uVar29;
                  puVar70[0x3950] = uVar29;
                  puVar70[0x3d68] = uVar29;
                  *puVar68 = 0;
                  puVar68[0x83] = 0;
                  puVar68[0x106] = 0;
                  puVar68[0x189] = 0;
                  puVar68[0x20c] = 0;
                  puVar68[0x28f] = 0;
                  puVar68[0x312] = 0;
                  puVar68[0x395] = 0;
                  puVar68[0x418] = 0;
                  puVar68[0x49b] = 0;
                  puVar68[0x51e] = 0;
                  puVar68[0x5a1] = 0;
                  puVar68[0x624] = 0;
                  puVar68[0x6a7] = 0;
                  puVar68[0x72a] = 0;
                  puVar68[0x7ad] = 0;
                  if (puVar2 + (ulong)((uVar45 >> 4) - 1) * 0x4180 == puVar72) break;
                  puVar68 = puVar68 + 0x830;
                  puVar64 = puVar64 + 0x1060;
                  puVar70 = puVar72;
                  puVar72 = puVar72 + 0x4180;
                }
                iVar80 = iVar80 + (uVar45 & 0xfffffff0);
                if ((uVar45 & 0xfffffff0) != uVar45) {
LAB_00b4d5b0:
                  lVar57 = (long)iVar80 * 0x418;
                  lVar46 = lVar69 + lVar57;
                  *(undefined4 *)(lVar46 + 0x2f0) = uVar31;
                  *(undefined1 *)(lVar46 + 0x300) = uVar29;
                  *(undefined8 *)(lVar46 + 0x2e8) = 0;
                  if (iVar80 + 1 < iVar55) {
                    lVar46 = lVar69 + 0x418 + lVar57;
                    *(undefined4 *)(lVar46 + 0x2f0) = uVar31;
                    *(undefined1 *)(lVar46 + 0x300) = uVar29;
                    *(undefined8 *)(lVar46 + 0x2e8) = 0;
                    if (iVar80 + 2 < iVar55) {
                      lVar46 = lVar69 + 0x830 + lVar57;
                      *(undefined4 *)(lVar46 + 0x2f0) = uVar31;
                      *(undefined1 *)(lVar46 + 0x300) = uVar29;
                      *(undefined8 *)(lVar46 + 0x2e8) = 0;
                      if (iVar80 + 3 < iVar55) {
                        lVar46 = lVar69 + 0xc48 + lVar57;
                        *(undefined4 *)(lVar46 + 0x2f0) = uVar31;
                        *(undefined1 *)(lVar46 + 0x300) = uVar29;
                        *(undefined8 *)(lVar46 + 0x2e8) = 0;
                        if (iVar80 + 4 < iVar55) {
                          lVar46 = lVar69 + 0x1060 + lVar57;
                          *(undefined4 *)(lVar46 + 0x2f0) = uVar31;
                          *(undefined1 *)(lVar46 + 0x300) = uVar29;
                          *(undefined8 *)(lVar46 + 0x2e8) = 0;
                          if (iVar80 + 5 < iVar55) {
                            lVar46 = lVar69 + 0x1478 + lVar57;
                            *(undefined4 *)(lVar46 + 0x2f0) = uVar31;
                            *(undefined1 *)(lVar46 + 0x300) = uVar29;
                            *(undefined8 *)(lVar46 + 0x2e8) = 0;
                            if (iVar80 + 6 < iVar55) {
                              lVar46 = lVar69 + 0x1890 + lVar57;
                              *(undefined4 *)(lVar46 + 0x2f0) = uVar31;
                              *(undefined1 *)(lVar46 + 0x300) = uVar29;
                              *(undefined8 *)(lVar46 + 0x2e8) = 0;
                              if (iVar80 + 7 < iVar55) {
                                lVar46 = lVar69 + 0x1ca8 + lVar57;
                                *(undefined4 *)(lVar46 + 0x2f0) = uVar31;
                                *(undefined1 *)(lVar46 + 0x300) = uVar29;
                                *(undefined8 *)(lVar46 + 0x2e8) = 0;
                                if (iVar80 + 8 < iVar55) {
                                  lVar46 = lVar69 + 0x20c0 + lVar57;
                                  *(undefined4 *)(lVar46 + 0x2f0) = uVar31;
                                  *(undefined1 *)(lVar46 + 0x300) = uVar29;
                                  *(undefined8 *)(lVar46 + 0x2e8) = 0;
                                  if (iVar80 + 9 < iVar55) {
                                    lVar46 = lVar69 + 0x24d8 + lVar57;
                                    *(undefined4 *)(lVar46 + 0x2f0) = uVar31;
                                    *(undefined1 *)(lVar46 + 0x300) = uVar29;
                                    *(undefined8 *)(lVar46 + 0x2e8) = 0;
                                    if (iVar80 + 10 < iVar55) {
                                      lVar46 = lVar69 + 0x28f0 + lVar57;
                                      *(undefined4 *)(lVar46 + 0x2f0) = uVar31;
                                      *(undefined1 *)(lVar46 + 0x300) = uVar29;
                                      *(undefined8 *)(lVar46 + 0x2e8) = 0;
                                      if (iVar80 + 0xb < iVar55) {
                                        lVar46 = lVar69 + 0x2d08 + lVar57;
                                        *(undefined4 *)(lVar46 + 0x2f0) = uVar31;
                                        *(undefined1 *)(lVar46 + 0x300) = uVar29;
                                        *(undefined8 *)(lVar46 + 0x2e8) = 0;
                                        if (iVar80 + 0xc < iVar55) {
                                          lVar46 = lVar69 + 0x3120 + lVar57;
                                          *(undefined4 *)(lVar46 + 0x2f0) = uVar31;
                                          *(undefined1 *)(lVar46 + 0x300) = uVar29;
                                          *(undefined8 *)(lVar46 + 0x2e8) = 0;
                                          if (iVar80 + 0xd < iVar55) {
                                            lVar46 = lVar69 + 0x3538 + lVar57;
                                            *(undefined4 *)(lVar46 + 0x2f0) = uVar31;
                                            *(undefined1 *)(lVar46 + 0x300) = uVar29;
                                            *(undefined8 *)(lVar46 + 0x2e8) = 0;
                                            if (iVar80 + 0xe < iVar55) {
                                              lVar57 = lVar69 + 0x3950 + lVar57;
                                              *(undefined4 *)(lVar57 + 0x2f0) = uVar31;
                                              *(undefined1 *)(lVar57 + 0x300) = uVar29;
                                              *(undefined8 *)(lVar57 + 0x2e8) = 0;
                                            }
                                          }
                                        }
                                      }
                                    }
                                  }
                                }
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
              break;
            }
LAB_00b4d845:
            if (iVar56 < 0x100) {
              lVar57 = (long)iVar56;
              iVar56 = iVar56 + 1;
              *(ulong *)(local_2308 + lVar57 * 8) =
                   uVar47 | local_23d0 & 0xffffff0000000000 | (uVar42 & 0xff) << 0x20;
            }
            local_23d0 = (anonymous_namespace)::GetUserMarkerColor
                                   (param_3,(RgpUserMarker *)(ulong)*(uint *)(lVar46 + 0x18));
            uVar47 = local_23d0 & 0xffffffff;
            uVar42 = local_23d0 >> 0x20;
            if (*(ulong *)(lVar69 + 0x120) <= *(ulong *)(lVar46 + 0x10)) {
LAB_00b4d0f9:
              *(char *)(lVar69 + 0x300) = (char)uVar42;
              if (iVar71 == 0) {
                iVar73 = 0;
              }
              iVar80 = iVar80 + 1;
              *(int *)(lVar69 + 0x2e8) = iVar73;
              *(ulong *)(lVar69 + 0x2ec) = CONCAT44((int)uVar47,iVar71);
              for (; iVar32 != 0; iVar32 = iVar32 + -1) {
                if (iVar56 != 0) {
                  iVar56 = iVar56 + -1;
                  lVar69 = (long)iVar56;
                  local_23d0 = *(ulong *)(local_2308 + lVar69 * 8);
                  uVar47 = (ulong)*(uint *)(local_2308 + lVar69 * 8);
                  uVar42 = (ulong)(byte)local_2308[lVar69 * 8 + 4];
                }
              }
              iVar71 = 0;
              iVar73 = iVar78;
              goto LAB_00b4d161;
            }
LAB_00b4d388:
            if (iVar78 == *(int *)(pRVar81 + 200)) goto LAB_00b4d0f9;
            if (iVar79 <= iVar78) goto LAB_00b4d39f;
LAB_00b4d16b:
          } while (iVar80 < iVar55);
        }
        pRVar81 = pRVar81 + 0x10;
      } while (param_3 + (ulong)(iVar30 - 1) * 0x10 + 0x6c8 != pRVar81);
    }
LAB_00b4d18b:
    if ((*(int *)(param_3 + 0x91560) < 4) && (iVar30 = *(int *)(param_3 + 0x648), 0 < iVar30)) {
      lVar69 = 0;
      do {
        pRVar10 = *(RgpEvent **)(*(long *)(param_3 + 0x630) + lVar69 * 0x28);
        if ((pRVar10 != (RgpEvent *)0x0) && (*(int *)(pRVar10 + 0x14) != 2)) {
          cVar28 = RgpEventIsIndirectMulti
                             (*(undefined4 *)(param_3 + 0x368),*(undefined4 *)(pRVar10 + 0x1c));
          if ((cVar28 != '\0') &&
             ((0 < *(int *)(pRVar10 + 0x314) || (0 < *(int *)(pRVar10 + 0x318))))) {
            lVar46 = RgpEventGetMinimumTimestamp(pRVar10);
            *(long *)(pRVar10 + 0x120) = lVar46 + -1;
          }
          iVar30 = *(int *)(param_3 + 0x648);
        }
        lVar69 = lVar69 + 1;
      } while ((int)lVar69 < iVar30);
    }
    param_3[0x64d] = (RgpDataSet)(0 < *(int *)(param_1 + 0x2031dc));
    if ((8 < *(int *)(param_1 + 0x104)) && (0 < *(int *)(param_3 + 0x648))) {
      lVar69 = 0;
      do {
        pRVar10 = *(RgpEvent **)(*(long *)(param_3 + 0x630) + lVar69 * 0x28);
        lVar46 = RgpEventGetLoaderEventForSqttStage(pRVar10,6);
        if (((((*(int *)(pRVar10 + 0x14) != 2) &&
              (cVar28 = RgpEventIsRayTracing(pRVar10,3), lVar46 != 0)) && (cVar28 == '\0')) &&
            ((*(long *)(lVar46 + 0x38) != 0 || (*(long *)(lVar46 + 0x30) != 0)))) &&
           (lVar46 = *(long *)(lVar46 + 8), lVar46 != 0)) {
          uVar45 = 0;
          if (0 < *(int *)(pRVar10 + 0x54)) {
            uVar45 = *(uint *)(lVar46 + 0xe8) & 1;
          }
          if ((0 < *(int *)(pRVar10 + 0x58)) && ((*(byte *)(lVar46 + 0xe8) & 2) != 0)) {
            uVar45 = uVar45 | 2;
          }
          if ((0 < *(int *)(pRVar10 + 0x5c)) && ((*(byte *)(lVar46 + 0xe8) & 4) != 0)) {
            uVar45 = uVar45 | 4;
          }
          if ((0 < *(int *)(pRVar10 + 0x60)) && ((*(byte *)(lVar46 + 0xe8) & 8) != 0)) {
            uVar45 = uVar45 | 8;
          }
          if ((0 < *(int *)(pRVar10 + 100)) && ((*(byte *)(lVar46 + 0xe8) & 0x10) != 0)) {
            uVar45 = uVar45 | 0x10;
          }
          if ((0 < *(int *)(pRVar10 + 0x68)) && ((*(byte *)(lVar46 + 0xe8) & 0x20) != 0)) {
            uVar45 = uVar45 | 0x20;
          }
          if ((0 < *(int *)(pRVar10 + 0x6c)) && ((*(byte *)(lVar46 + 0xe8) & 0x40) != 0)) {
            uVar45 = uVar45 | 0x40;
          }
          if ((0 < *(int *)(pRVar10 + 0x70)) && ((*(byte *)(lVar46 + 0xe8) & 0x80) != 0)) {
            uVar45 = uVar45 | 1;
          }
          if ((0 < *(int *)(pRVar10 + 0x74)) && ((*(byte *)(lVar46 + 0xe9) & 1) != 0)) {
            uVar45 = uVar45 | 1;
          }
          if ((0 < *(int *)(pRVar10 + 0x78)) && ((*(byte *)(lVar46 + 0xe9) & 2) != 0)) {
            uVar45 = uVar45 | 1;
          }
          if ((0 < *(int *)(pRVar10 + 0x7c)) && ((*(byte *)(lVar46 + 0xe9) & 4) != 0)) {
            uVar45 = uVar45 | 0x400;
          }
          *(uint *)(pRVar10 + 0x408) = uVar45;
        }
        lVar69 = lVar69 + 1;
      } while ((int)lVar69 < *(int *)(param_3 + 0x648));
    }
    *(undefined4 *)(param_3 + 0x91560) = *(undefined4 *)(param_1 + 0x79c);
  }
  (anonymous_namespace)::LoadShaderDebugInfo(param_4,param_5,param_3);
  lVar69 = RgpGetCurrentTimestamp();
  auVar12._8_8_ = 0;
  auVar12._0_8_ = uVar33;
  auVar13._8_8_ = 0;
  auVar13._0_8_ = (lVar69 - lVar34) * 1000000;
  RgpPrint("RGP data set loaded in %lums.",
           SUB168((auVar13 / auVar12 >> 3 & (undefined1  [16])0x1fffffffffffffff) /
                  (undefined1  [16])0x7d,0));
  iVar30 = 0;
LAB_00b4d2ab:
  if (local_40 == *(long *)(in_FS_OFFSET + 0x28)) {
    return iVar30;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
LAB_00b4db80:
  iVar30 = *(int *)(param_1 + 0x114);
  *(int *)(param_1 + 0x180870) = (*(int *)(param_1 + 0x180870) + 1) % iVar30;
LAB_00b4db9b:
  if (iVar30 < 1) goto LAB_00b4dbf1;
  iVar30 = 0;
  pRVar49 = param_1 + 0x180878;
  while (cVar28 = RgpSqttParserIsCompleted(pRVar49), cVar28 != '\0') {
    iVar30 = iVar30 + 1;
    pRVar49 = pRVar49 + 200;
    if (*(int *)(param_1 + 0x114) <= iVar30) {
      if (0 < *(int *)(param_1 + 0x114)) {
        iVar30 = 0;
        pRVar49 = param_1 + 0x180878;
        do {
          iVar30 = iVar30 + 1;
          RgpSqttParserReset(pRVar49);
          pRVar49 = pRVar49 + 200;
        } while (iVar30 < *(int *)(param_1 + 0x114));
      }
      goto LAB_00b4dbf1;
    }
  }
  goto LAB_00b4d970;
LAB_00b4dbf1:
  puVar64 = *(undefined4 **)(param_1 + 0xa21b80);
  puVar76 = *(undefined4 **)(param_1 + 0xa21b78);
  lVar69 = *(long *)(param_1 + 0x9b10f8);
  if (puVar76 != puVar64) {
    do {
      plVar38 = (long *)RgpDataSetLoaderGetSqttPayload(param_1,*puVar76,puVar76[1]);
      if (plVar38 != (long *)0x0) {
        memcpy_s(&local_23c0,8,(void *)(*plVar38 + 4),8);
        uVar42 = CONCAT44(uStack_23bc,local_23c0);
        uVar47 = uVar42 % *(ulong *)(lVar69 + 0x38);
        plVar38 = *(long **)(*(long *)(lVar69 + 0x30) + uVar47 * 8);
        if (plVar38 != (long *)0x0) {
          plVar38 = (long *)*plVar38;
          uVar36 = plVar38[1];
          do {
            if (uVar42 == uVar36) goto LAB_00b4dd28;
            plVar38 = (long *)*plVar38;
          } while ((plVar38 != (long *)0x0) &&
                  (uVar36 = plVar38[1], uVar47 == uVar36 % *(ulong *)(lVar69 + 0x38)));
        }
        plVar38 = operator_new(0x10);
        *plVar38 = 0;
        plVar38[1] = CONCAT44(uStack_23bc,local_23c0);
        local_23b8 = *(RgpDataSet **)(lVar69 + 0x58);
                    /* try { // try from 00b4dcef to 00b4dcf3 has its CatchHandler @ 00b4fef1 */
        cVar28 = std::__detail::_Prime_rehash_policy::_M_need_rehash
                           (lVar69 + 0x50,*(ulong *)(lVar69 + 0x38),*(ulong *)(lVar69 + 0x48));
        if (cVar28 != '\0') {
                    /* try { // try from 00b4f472 to 00b4f476 has its CatchHandler @ 00b4fef1 */
          std::
          _Hashtable<unsigned_long,unsigned_long,std::allocator<unsigned_long>,std::__detail::_Identity,std::equal_to<unsigned_long>,std::hash<unsigned_long>,std::__detail::_Mod_range_hashing,std::__detail::_Default_ranged_hash,std::__detail::_Prime_rehash_policy,std::__detail::_Hashtable_traits<false,true,true>>
          ::_M_rehash(lVar69 + 0x30,extraout_RDX);
          uVar47 = uVar42 % *(ulong *)(lVar69 + 0x38);
        }
        local_2498 = (double)(uVar47 * 8);
        lVar46 = *(long *)(lVar69 + 0x30);
        plVar43 = (long *)((long)local_2498 + lVar46);
        if ((long *)*plVar43 == (long *)0x0) {
          *plVar38 = *(long *)(lVar69 + 0x40);
          *(long **)(lVar69 + 0x40) = plVar38;
          if (*plVar38 != 0) {
            *(long **)(lVar46 + (*(ulong *)(*plVar38 + 8) % *(ulong *)(lVar69 + 0x38)) * 8) =
                 plVar38;
          }
          *plVar43 = lVar69 + 0x40;
        }
        else {
          *plVar38 = *(long *)*plVar43;
          *(long **)*plVar43 = plVar38;
        }
        *(long *)(lVar69 + 0x48) = *(long *)(lVar69 + 0x48) + 1;
      }
LAB_00b4dd28:
      puVar76 = puVar76 + 2;
    } while (puVar64 != puVar76);
    if (*(long *)(param_1 + 0xa21b80) != *(long *)(param_1 + 0xa21b78)) {
      *(long *)(param_1 + 0xa21b80) = *(long *)(param_1 + 0xa21b78);
    }
  }
  param_1[0xbc8860] = (RgpDataSetLoader)0x1;
  *(int *)(param_1 + 0xa21b6c) =
       (int)(*(long *)(param_1 + 0x630) - *(long *)(param_1 + 0x628) >> 4) * -0x33333333;
  auVar14._8_8_ = 0;
  auVar14._0_8_ = (long)*(int *)(param_1 + 0xa219d8);
  sVar39 = SUB168(auVar14 * ZEXT816(0x18),0);
  if (SUB168(auVar14 * ZEXT816(0x18),8) == 0) {
    *(undefined8 *)(param_1 + 0xbc8868) = 0;
    if (sVar39 != 0) {
      if (*(code **)(param_1 + 0xa219a8) == (code *)0x0) {
        pvVar37 = malloc(sVar39);
      }
      else {
        pvVar37 = (void *)(**(code **)(param_1 + 0xa219a8))(sVar39);
      }
      if (pvVar37 != (void *)0x0) {
        memset(pvVar37,0,sVar39);
        iVar30 = RgpAllocLinearBufferInitialize(param_1 + 0xbc8870,pvVar37,sVar39);
        if (iVar30 == 0) {
          *(void **)(param_1 + 0xbc8868) = pvVar37;
        }
      }
    }
    auVar15._8_8_ = 0;
    auVar15._0_8_ = (long)*(int *)(param_1 + 0xa21a30);
    __size = SUB168(auVar15 * ZEXT816(0x2e88),0);
    if (SUB168(auVar15 * ZEXT816(0x2e88),8) == 0) {
      *(undefined8 *)(param_1 + 0xbc89b0) = 0;
      if (__size != 0) {
        if (*(code **)(param_1 + 0xa219a8) == (code *)0x0) {
          pvVar37 = malloc(__size);
        }
        else {
          pvVar37 = (void *)(**(code **)(param_1 + 0xa219a8))(__size);
        }
        if (pvVar37 != (void *)0x0) {
          memset(pvVar37,0,__size);
          iVar30 = RgpAllocLinearBufferInitialize(param_1 + 0xbc89b8,pvVar37,__size);
          if (iVar30 == 0) {
            *(void **)(param_1 + 0xbc89b0) = pvVar37;
          }
        }
      }
      auVar16._8_8_ = 0;
      auVar16._0_8_ = (long)*(int *)(param_1 + 0xa21a34);
      __size_00 = SUB168(auVar16 * ZEXT816(0x170),0);
      if (SUB168(auVar16 * ZEXT816(0x170),8) == 0) {
        *(undefined8 *)(param_1 + 0xbc89d0) = 0;
        if (__size_00 != 0) {
          if (*(code **)(param_1 + 0xa219a8) == (code *)0x0) {
            pvVar37 = malloc(__size_00);
          }
          else {
            pvVar37 = (void *)(**(code **)(param_1 + 0xa219a8))(__size_00);
          }
          if (pvVar37 != (void *)0x0) {
            memset(pvVar37,0,__size_00);
            iVar30 = RgpAllocLinearBufferInitialize(param_1 + 0xbc89d8,pvVar37,__size_00);
            if (iVar30 == 0) {
              *(void **)(param_1 + 0xbc89d0) = pvVar37;
            }
          }
        }
        auVar17._8_8_ = 0;
        auVar17._0_8_ = (long)*(int *)(param_1 + 0xa21b38);
        __size_01 = SUB168(auVar17 * ZEXT816(0xc),0);
        if (SUB168(auVar17 * ZEXT816(0xc),8) == 0) {
          *(undefined8 *)(param_1 + 0xbc8d68) = 0;
          if (__size_01 != 0) {
            if (*(code **)(param_1 + 0xa219a8) == (code *)0x0) {
              pvVar37 = malloc(__size_01);
            }
            else {
              pvVar37 = (void *)(**(code **)(param_1 + 0xa219a8))(__size_01);
            }
            if (pvVar37 != (void *)0x0) {
              memset(pvVar37,0,__size_01);
              iVar30 = RgpAllocLinearBufferInitialize(param_1 + 0xbc8d70,pvVar37,__size_01);
              if (iVar30 == 0) {
                *(void **)(param_1 + 0xbc8d68) = pvVar37;
              }
            }
          }
          iVar32 = *(int *)(param_1 + 0xa21b6c);
          auVar18._8_8_ = 0;
          auVar18._0_8_ = (long)*(int *)(param_1 + 0xa21b70);
          __size_02 = SUB168(auVar18 * ZEXT816(0x30),0);
          if (SUB168(auVar18 * ZEXT816(0x30),8) == 0) {
            pcVar40 = *(code **)(param_1 + 0xa219a8);
            *(undefined8 *)(param_1 + 0xbc8eb0) = 0;
            if (__size_02 != 0) {
              if (pcVar40 == (code *)0x0) {
                pvVar37 = malloc(__size_02);
              }
              else {
                pvVar37 = (void *)(*pcVar40)(__size_02);
              }
              if (pvVar37 != (void *)0x0) {
                memset(pvVar37,0,__size_02);
                iVar30 = RgpAllocLinearBufferInitialize(param_1 + 0xbc8eb8,pvVar37,__size_02);
                if (iVar30 == 0) {
                  *(void **)(param_1 + 0xbc8eb0) = pvVar37;
                }
              }
              pcVar40 = *(code **)(param_1 + 0xa219a8);
            }
            local_2440 = (ulong)*(uint *)(param_1 + 0xa21a98);
            *(undefined8 *)(param_1 + 0xbc8ed0) = 0;
            __size_07 = local_2440 * 0x2440;
            if (__size_07 == 0) {
LAB_00b4e074:
              local_2440 = local_2440 * 0x418;
              if (pcVar40 == (code *)0x0) goto LAB_00b4f2d8;
              pvVar37 = (void *)(*pcVar40)(local_2440);
            }
            else {
              if (pcVar40 != (code *)0x0) {
                pvVar37 = (void *)(*pcVar40)(__size_07);
                if (pvVar37 != (void *)0x0) goto LAB_00b4e038;
LAB_00b4e066:
                local_2440 = (ulong)*(uint *)(param_1 + 0xa21a98);
                pcVar40 = *(code **)(param_1 + 0xa219a8);
                goto LAB_00b4e074;
              }
              pvVar37 = malloc(__size_07);
              if (pvVar37 != (void *)0x0) {
LAB_00b4e038:
                memset(pvVar37,0,__size_07);
                iVar30 = RgpAllocLinearBufferInitialize(param_1 + 0xbc8ed8,pvVar37,__size_07);
                if (iVar30 == 0) {
                  *(void **)(param_1 + 0xbc8ed0) = pvVar37;
                }
                goto LAB_00b4e066;
              }
              local_2440 = local_2440 * 0x418;
LAB_00b4f2d8:
              pvVar37 = malloc(local_2440);
            }
            *(void **)(param_1 + 0xbc8888) = pvVar37;
            if (pvVar37 != (void *)0x0) {
              memset(pvVar37,0,local_2440);
              lVar69 = 0;
              lVar46 = 0;
              pRVar49 = param_1 + 0xbc8890;
              do {
                iVar55 = *(int *)(param_1 + lVar69 + 0xa21a38);
                lVar57 = *(long *)(param_1 + 0xbc8888) + lVar46;
                iVar30 = RgpAllocLinearBufferInitialize(pRVar49,lVar57,(long)iVar55 * 0x418);
                if (iVar30 != 0) goto LAB_00b4d2ab;
                lVar46 = lVar46 + (long)iVar55 * 0x418;
                pRVar49 = pRVar49 + 0x18;
                *(long *)(param_3 + lVar69 * 4 + 0x6b8) = lVar57;
                *(undefined4 *)(param_3 + lVar69 * 4 + 0x6c0) = 0;
                lVar69 = lVar69 + 4;
              } while (lVar69 != 0x30);
              auVar14 = *(undefined1 (*) [16])(param_1 + 0xa21b3c);
              auVar15 = *(undefined1 (*) [16])(param_1 + 0xa21b4c);
              pRVar49 = param_1 + 0xa21b3c;
              auVar16 = *(undefined1 (*) [16])(param_1 + 0xa21b5c);
              auVar88._0_8_ = CONCAT44(-(uint)(auVar14._8_4_ < 0),auVar14._8_4_);
              auVar88._8_4_ = auVar14._12_4_;
              auVar88._12_4_ = -(uint)(auVar14._12_4_ < SUB124(SUB1612((undefined1  [16])0x0,4),8));
              auVar84._0_8_ = auVar14._0_8_;
              auVar84._8_4_ = auVar14._4_4_;
              auVar84._12_4_ = -(uint)(auVar14._4_4_ < 0);
              auVar89._0_8_ = auVar15._0_8_;
              auVar89._8_4_ = auVar15._4_4_;
              auVar89._12_4_ = -(uint)(auVar15._4_4_ < 0);
              auVar86._0_8_ = CONCAT44(-(uint)(auVar15._8_4_ < 0),auVar15._8_4_);
              auVar86._8_4_ = auVar15._12_4_;
              auVar86._12_4_ = -(uint)(auVar15._12_4_ < SUB124(SUB1612((undefined1  [16])0x0,4),8));
              auVar85._0_8_ = auVar16._0_8_;
              auVar85._8_4_ = auVar16._4_4_;
              auVar85._12_4_ = -(uint)(auVar16._4_4_ < 0);
              auVar87._0_8_ = CONCAT44(-(uint)(auVar16._8_4_ < 0),auVar16._8_4_);
              auVar87._8_4_ = auVar16._12_4_;
              auVar87._12_4_ = -(uint)(auVar16._12_4_ < SUB124(SUB1612((undefined1  [16])0x0,4),8));
              lVar69 = CONCAT44(-(uint)(auVar14._0_4_ < 0),auVar14._0_4_) + auVar88._0_8_ +
                       auVar86._0_8_ + CONCAT44(-(uint)(auVar15._0_4_ < 0),auVar15._0_4_) +
                       CONCAT44(-(uint)(auVar16._0_4_ < 0),auVar16._0_4_) + auVar87._0_8_ +
                       auVar84._8_8_ + auVar88._8_8_ + auVar86._8_8_ + auVar89._8_8_ +
                       auVar85._8_8_ + auVar87._8_8_;
              __size_03 = lVar69 * 0xc;
              if (*(code **)(param_1 + 0xa219a8) == (code *)0x0) {
                pvVar37 = malloc(__size_03);
              }
              else {
                pvVar37 = (void *)(**(code **)(param_1 + 0xa219a8))(__size_03);
              }
              *(void **)(param_1 + 0xbc8d88) = pvVar37;
              memset(pvVar37,0,__size_03);
              pRVar77 = param_1 + 0xbc8d90;
              lVar46 = 0;
              do {
                iVar55 = *(int *)pRVar49;
                iVar30 = RgpAllocLinearBufferInitialize
                                   (pRVar77,*(long *)(param_1 + 0xbc8d88) + lVar46,
                                    (long)iVar55 * 0xc);
                if (iVar30 != 0) goto LAB_00b4d2ab;
                lVar46 = lVar46 + (long)iVar55 * 0xc;
                pRVar49 = pRVar49 + 4;
                pRVar77 = pRVar77 + 0x18;
              } while (pRVar77 != param_1 + 0xbc8eb0);
              *(undefined8 *)(param_1 + 0xbc8b18) = 0;
              auVar19._8_8_ = 0;
              auVar19._0_8_ = (long)*(int *)(param_1 + 0xa21acc);
              __size_04 = SUB168(auVar19 * ZEXT816(0x58),0);
              if (SUB168(auVar19 * ZEXT816(0x58),8) != 0) goto LAB_00b4f491;
              if (*(code **)(param_1 + 0xa219a8) == (code *)0x0) {
                pvVar37 = malloc(__size_04);
              }
              else {
                pvVar37 = (void *)(**(code **)(param_1 + 0xa219a8))(__size_04,4);
              }
              *(void **)(param_1 + 0xbc8b18) = pvVar37;
              if (pvVar37 != (void *)0x0) {
                lVar46 = 0;
                pRVar49 = param_1 + 0xbc8b20;
                lVar57 = 0;
                while( true ) {
                  iVar55 = *(int *)(param_1 + lVar57 + 0xa21a9c);
                  lVar75 = (long)pvVar37 + lVar46;
                  iVar30 = RgpAllocLinearBufferInitialize(pRVar49,lVar75,(long)iVar55 * 0x58);
                  if (iVar30 != 0) break;
                  lVar46 = lVar46 + (long)iVar55 * 0x58;
                  *(long *)(param_3 + lVar57 * 4 + 0x838) = lVar75;
                  pRVar49 = pRVar49 + 0x18;
                  *(undefined4 *)(param_3 + lVar57 * 4 + 0x840) = 0;
                  lVar57 = lVar57 + 4;
                  if (lVar57 == 0x30) {
                    iVar55 = *(int *)(param_1 + 0xa21b00);
                    *(undefined8 *)(param_1 + 0xbc8c40) = 0;
                    __size_05 = (long)iVar55 * 0x10;
                    if (*(code **)(param_1 + 0xa219a8) == (code *)0x0) {
                      pvVar37 = malloc(__size_05);
                    }
                    else {
                      pvVar37 = (void *)(**(code **)(param_1 + 0xa219a8))(__size_05,8);
                    }
                    *(void **)(param_1 + 0xbc8c40) = pvVar37;
                    if (pvVar37 == (void *)0x0) goto LAB_00b4f2a5;
                    lVar57 = 0;
                    pRVar49 = param_1 + 0xbc8c48;
                    lVar46 = 0;
                    goto LAB_00b4e3dd;
                  }
                  pvVar37 = *(void **)(param_1 + 0xbc8b18);
                }
                goto LAB_00b4d2ab;
              }
            }
LAB_00b4f2a5:
            iVar30 = -0x7ffffff7;
            goto LAB_00b4d2ab;
          }
        }
      }
    }
  }
LAB_00b4f491:
  iVar30 = -0x7ffffffe;
  goto LAB_00b4d2ab;
LAB_00b4e3dd:
  iVar79 = *(int *)(param_1 + lVar46 + 0xa21ad0);
  lVar75 = (long)pvVar37 + lVar57;
  iVar30 = RgpAllocLinearBufferInitialize(pRVar49,lVar75,(long)iVar79 * 0x10);
  if (iVar30 != 0) goto LAB_00b4d2ab;
  lVar57 = lVar57 + (long)iVar79 * 0x10;
  *(long *)(param_3 + lVar46 * 4 + 0x8f8) = lVar75;
  pRVar49 = pRVar49 + 0x18;
  *(undefined4 *)(param_3 + lVar46 * 4 + 0x900) = 0;
  lVar46 = lVar46 + 4;
  if (lVar46 == 0x30) {
    *(undefined8 *)(param_1 + 0xbc89f0) = 0;
    auVar20._8_8_ = 0;
    auVar20._0_8_ = (long)*(int *)(param_1 + 0xa21b34);
    __size_06 = SUB168(auVar20 * ZEXT816(0x38),0);
    if (SUB168(auVar20 * ZEXT816(0x38),8) != 0) goto LAB_00b4f491;
    if (*(code **)(param_1 + 0xa219a8) == (code *)0x0) {
      pvVar37 = malloc(__size_06);
    }
    else {
      pvVar37 = (void *)(**(code **)(param_1 + 0xa219a8))(__size_06,8);
    }
    *(void **)(param_1 + 0xbc89f0) = pvVar37;
    if (pvVar37 == (void *)0x0) goto LAB_00b4f2a5;
    lVar46 = 0;
    pRVar49 = param_1 + 0xbc89f8;
    lVar57 = 0;
    goto LAB_00b4e4be;
  }
  pvVar37 = *(void **)(param_1 + 0xbc8c40);
  goto LAB_00b4e3dd;
LAB_00b4e4be:
  iVar79 = *(int *)(param_1 + lVar57 + 0xa21b04);
  lVar75 = (long)pvVar37 + lVar46;
  iVar30 = RgpAllocLinearBufferInitialize(pRVar49,lVar75,(long)iVar79 * 0x38);
  if (iVar30 != 0) goto LAB_00b4d2ab;
  lVar46 = lVar46 + (long)iVar79 * 0x38;
  *(long *)(param_3 + lVar57 * 4 + 0x9b8) = lVar75;
  pRVar49 = pRVar49 + 0x18;
  *(undefined4 *)(param_3 + lVar57 * 4 + 0x9c0) = 0;
  lVar57 = lVar57 + 4;
  if (lVar57 != 0x30) goto LAB_00b4e4b7;
  uVar35 = *(undefined8 *)(param_1 + 0x9b10d8);
  pRVar81 = (RgpDataSet *)(local_2390 + 8);
  *(undefined4 *)(param_3 + 0xa78) = *(undefined4 *)(param_1 + 0xa21b34);
  uVar7 = *(undefined8 *)(param_1 + 0x9b10e0);
  local_23b0 = 1;
  *(undefined4 *)(param_3 + 0xa98) = *(undefined4 *)(param_1 + 0xa21b6c);
  local_23a8 = 0;
  *(undefined8 *)(param_3 + 0x2aa8) = *(undefined8 *)(param_1 + 0xbc8eb0);
  uVar31 = *(undefined4 *)(param_1 + 0xa21b70);
  *(undefined8 *)(param_3 + 0x2ad0) = uVar35;
  *(undefined8 *)(param_3 + 0x2ad8) = uVar7;
  uVar35 = *(undefined8 *)(param_1 + 0x9b10e8);
  *(undefined4 *)(param_3 + 0x2ab0) = uVar31;
  uVar7 = *(undefined8 *)(param_1 + 0x9b10f0);
  *(undefined8 *)(param_3 + 0x6bae0) = uVar35;
  *(undefined8 *)(param_3 + 0x6bae8) = uVar7;
  *(undefined8 *)(param_3 + 0x6baf0) = *(undefined8 *)(param_1 + 0x9b10f8);
  local_23a0._0_12_ = ZEXT412(0x3f800000) << 0x40;
  local_23a0._12_4_ = 0;
  local_2390 = (undefined1  [16])0x0;
  local_23b8 = pRVar81;
  std::__detail::
  _Hashtable_alloc<std::allocator<std::__detail::_Hash_node<std::pair<int_const,RgpEventInstructionInfo>,false>>>
  ::_M_deallocate_nodes(*(_Hash_node **)(param_3 + 0x914b0));
  if (*(RgpDataSet **)(param_3 + 0x914a0) != param_3 + 0x914d0) {
    operator_delete(*(RgpDataSet **)(param_3 + 0x914a0),*(long *)(param_3 + 0x914a8) * 8);
  }
  *(undefined8 *)(param_3 + 0x914c0) = local_23a0._8_8_;
  *(undefined8 *)(param_3 + 0x914c8) = local_2390._0_8_;
  if (local_23b8 == pRVar81) {
    *(undefined8 *)(param_3 + 0x914d0) = local_2390._8_8_;
    local_23b8 = param_3 + 0x914d0;
  }
  *(RgpDataSet **)(param_3 + 0x914a0) = local_23b8;
  *(ulong *)(param_3 + 0x914a8) = local_23b0;
  *(long *)(param_3 + 0x914b0) = local_23a8;
  *(undefined8 *)(param_3 + 0x914b8) = local_23a0._0_8_;
  if (local_23a8 != 0) {
    *(RgpDataSet **)(local_23b8 + ((ulong)(long)*(int *)(local_23a8 + 8) % local_23b0) * 8) =
         param_3 + 0x914b0;
  }
  local_23b0 = 1;
  local_2390 = ZEXT816(0);
  local_23a8 = 0;
  auVar24._8_8_ = 0;
  auVar24._0_8_ = local_23a0._8_8_;
  local_23a0 = auVar24 << 0x40;
  local_23b8 = pRVar81;
  std::__detail::
  _Hashtable_alloc<std::allocator<std::__detail::_Hash_node<std::pair<int_const,RgpEventInstructionInfo>,false>>>
  ::_M_deallocate_nodes((_Hash_node *)0x0);
  memset(local_23b8,0,local_23b0 * 8);
  auVar25._8_8_ = 0;
  auVar25._0_8_ = local_23a0._8_8_;
  local_23a0 = auVar25 << 0x40;
  local_23a8 = 0;
  if (local_23b8 != pRVar81) {
    operator_delete(local_23b8,local_23b0 << 3);
  }
  local_2390 = (undefined1  [16])0x0;
  local_23b0 = 1;
  local_23a8 = 0;
  local_23a0._0_12_ = ZEXT412(0x3f800000) << 0x40;
  local_23a0._12_4_ = 0;
  local_23b8 = pRVar81;
  puVar68 = *(undefined8 **)(param_3 + 0x914e8);
  while (puVar68 != (undefined8 *)0x0) {
    puVar48 = (undefined8 *)*puVar68;
    puVar62 = (undefined8 *)puVar68[4];
    while (puVar62 != (undefined8 *)0x0) {
      puVar65 = (undefined8 *)*puVar62;
      operator_delete(puVar62,0x10);
      puVar62 = puVar65;
    }
    memset((void *)puVar68[2],0,puVar68[3] * 8);
    puVar68[5] = 0;
    puVar68[4] = 0;
    if ((undefined8 *)puVar68[2] != puVar68 + 8) {
      operator_delete((undefined8 *)puVar68[2],puVar68[3] << 3);
    }
    operator_delete(puVar68,0x48);
    puVar68 = puVar48;
  }
  if (*(RgpDataSet **)(param_3 + 0x914d8) != param_3 + 0x91508) {
    operator_delete(*(RgpDataSet **)(param_3 + 0x914d8),*(long *)(param_3 + 0x914e0) << 3);
  }
  *(undefined8 *)(param_3 + 0x914f8) = local_23a0._8_8_;
  *(undefined8 *)(param_3 + 0x91500) = local_2390._0_8_;
  if (local_23b8 == pRVar81) {
    *(undefined8 *)(param_3 + 0x91508) = local_2390._8_8_;
    local_23b8 = param_3 + 0x91508;
  }
  *(RgpDataSet **)(param_3 + 0x914d8) = local_23b8;
  *(ulong *)(param_3 + 0x914e0) = local_23b0;
  *(long *)(param_3 + 0x914e8) = local_23a8;
  *(undefined8 *)(param_3 + 0x914f0) = local_23a0._0_8_;
  if (local_23a8 != 0) {
    *(RgpDataSet **)(local_23b8 + ((ulong)(long)*(int *)(local_23a8 + 8) % local_23b0) * 8) =
         param_3 + 0x914e8;
  }
  local_23b0 = 1;
  local_2390 = ZEXT816(0);
  local_23a8 = 0;
  auVar26._8_8_ = 0;
  auVar26._0_8_ = local_23a0._8_8_;
  local_23a0 = auVar26 << 0x40;
  local_23b8 = pRVar81;
  std::
  _Hashtable<int,std::pair<int_const,std::unordered_set<int,std::hash<int>,std::equal_to<int>,std::allocator<int>>>,std::allocator<std::pair<int_const,std::unordered_set<int,std::hash<int>,std::equal_to<int>,std::allocator<int>>>>,std::__detail::_Select1st,std::equal_to<int>,std::hash<int>,std::__detail::_Mod_range_hashing,std::__detail::_Default_ranged_hash,std::__detail::_Prime_rehash_policy,std::__detail::_Hashtable_traits<false,false,true>>
  ::~_Hashtable((_Hashtable<int,std::pair<int_const,std::unordered_set<int,std::hash<int>,std::equal_to<int>,std::allocator<int>>>,std::allocator<std::pair<int_const,std::unordered_set<int,std::hash<int>,std::equal_to<int>,std::allocator<int>>>>,std::__detail::_Select1st,std::equal_to<int>,std::hash<int>,std::__detail::_Mod_range_hashing,std::__detail::_Default_ranged_hash,std::__detail::_Prime_rehash_policy,std::__detail::_Hashtable_traits<false,false,true>>
                 *)&local_23b8);
  local_2390 = (undefined1  [16])0x0;
  local_23b0 = 1;
  local_23a8 = 0;
  local_23a0._0_12_ = ZEXT412(0x3f800000) << 0x40;
  local_23a0._12_4_ = 0;
  local_23b8 = pRVar81;
  puVar68 = *(undefined8 **)(param_3 + 0x91520);
  while (puVar68 != (undefined8 *)0x0) {
    pvVar37 = (void *)puVar68[2];
    puVar48 = (undefined8 *)*puVar68;
    if (pvVar37 != (void *)0x0) {
      operator_delete(pvVar37,puVar68[4] - (long)pvVar37);
    }
    operator_delete(puVar68,0x28);
    puVar68 = puVar48;
  }
  if (*(RgpDataSet **)(param_3 + 0x91510) != param_3 + 0x91540) {
    operator_delete(*(RgpDataSet **)(param_3 + 0x91510),*(long *)(param_3 + 0x91518) << 3);
  }
  *(undefined8 *)(param_3 + 0x91530) = local_23a0._8_8_;
  *(undefined8 *)(param_3 + 0x91538) = local_2390._0_8_;
  pRVar44 = local_23b8;
  if (local_23b8 == pRVar81) {
    *(undefined8 *)(param_3 + 0x91540) = local_2390._8_8_;
    pRVar44 = param_3 + 0x91540;
  }
  *(RgpDataSet **)(param_3 + 0x91510) = pRVar44;
  *(ulong *)(param_3 + 0x91518) = local_23b0;
  *(long *)(param_3 + 0x91520) = local_23a8;
  *(undefined8 *)(param_3 + 0x91528) = local_23a0._0_8_;
  if (local_23a8 != 0) {
    *(RgpDataSet **)(pRVar44 + ((ulong)(long)*(int *)(local_23a8 + 8) % local_23b0) * 8) =
         param_3 + 0x91520;
  }
  puVar68 = *(undefined8 **)(param_3 + 0x91548);
  lVar46 = *(long *)(param_3 + 0x91558);
  *(undefined8 *)(param_3 + 0x91558) = 0;
  puVar48 = *(undefined8 **)(param_3 + 0x91550);
  *(undefined1 (*) [16])(param_3 + 0x91548) = (undefined1  [16])0x0;
  for (puVar62 = puVar68; puVar62 != puVar48; puVar62 = puVar62 + 3) {
    while (pvVar37 = (void *)*puVar62, pvVar37 != (void *)0x0) {
      plVar38 = puVar62 + 2;
      puVar62 = puVar62 + 3;
      operator_delete(pvVar37,*plVar38 - (long)pvVar37);
      if (puVar48 == puVar62) goto LAB_00b4f38d;
    }
  }
LAB_00b4f38d:
  if (puVar68 != (undefined8 *)0x0) {
    operator_delete(puVar68,lVar46 - (long)puVar68);
  }
  *(undefined4 *)(param_3 + 0x6ac) = 0;
  uVar47 = (long)**(int **)(param_3 + 0x6bae8) * 0x188 + (long)**(int **)(param_3 + 0x6baf0) * 0x18
           + *(long *)(*(long *)(param_3 + 0x6bae0) + 0x58);
  uVar42 = 0;
  pRVar49 = param_1 + 0xba2e50;
  do {
    iVar30 = *(int *)pRVar49;
    if (iVar30 < 0) {
LAB_00b4f40f:
      iVar30 = -0x7ffffffa;
      goto LAB_00b4d2ab;
    }
    pRVar49 = pRVar49 + 4;
    uVar42 = uVar42 + (long)iVar30;
  } while (pRVar49 != param_1 + 0xbb5a50);
  if (0xaaaaaaaaaaaaaaa < uVar42) goto LAB_00b4f40f;
  if (uVar42 * 0x18 != 0) {
    pvVar37 = calloc(uVar42 * 0x18,1);
    *(void **)(param_1 + 0xbc8f08) = pvVar37;
    if (pvVar37 != (void *)0x0) {
      pRVar49 = param_1 + 0xbc8f10;
      lVar46 = 0;
      lVar57 = 0;
      local_2498 = 0.0;
      do {
        iVar30 = *(int *)(param_1 + lVar57 + 0xba2e50);
        lVar75 = *(long *)(param_1 + 0xbc8f08);
        *(double *)(param_3 + lVar57 * 2 + 0x6bb98) = local_2498;
        lVar54 = (long)iVar30 * 0x18;
        local_2498 = (double)((long)local_2498 + (long)iVar30);
        iVar30 = RgpAllocLinearBufferInitialize(pRVar49,lVar75 + lVar46,lVar54);
        if (iVar30 != 0) goto LAB_00b4d2ab;
        lVar57 = lVar57 + 4;
        lVar46 = lVar46 + lVar54;
        pRVar49 = pRVar49 + 0x18;
      } while (lVar57 != 0x12c00);
      goto LAB_00b4f4fb;
    }
    goto LAB_00b4f2a5;
  }
  *(undefined8 *)(param_1 + 0xbc8f08) = 0;
LAB_00b4f4fb:
  uVar35 = *(undefined8 *)(param_1 + 0xbc8f08);
  lVar46 = *(long *)(param_1 + 0x7a8);
  *(undefined8 *)(param_3 + 0x6bb90) = uVar35;
  *(undefined8 *)(lVar46 + 0x6bb90) = uVar35;
  puVar68 = *(undefined8 **)(param_3 + 0x660);
  uVar42 = (ulong)*(int *)(param_1 + 0x114);
  lVar46 = (long)puVar68 - *(long *)(param_3 + 0x658) >> 3;
  uVar36 = lVar46 * -0x5555555555555555;
  if (uVar36 < uVar42) {
    std::
    vector<std::vector<unsigned_long,std::allocator<unsigned_long>>,std::allocator<std::vector<unsigned_long,std::allocator<unsigned_long>>>>
    ::_M_default_append((vector<std::vector<unsigned_long,std::allocator<unsigned_long>>,std::allocator<std::vector<unsigned_long,std::allocator<unsigned_long>>>>
                         *)(param_3 + 0x658),uVar42 + lVar46 * 0x5555555555555555);
  }
  else if ((uVar42 < uVar36) &&
          (puVar62 = (undefined8 *)(*(long *)(param_3 + 0x658) + uVar42 * 0x18), puVar48 = puVar62,
          puVar68 != puVar62)) {
    do {
      while (pvVar37 = (void *)*puVar48, pvVar37 != (void *)0x0) {
        puVar65 = puVar48 + 3;
        operator_delete(pvVar37,puVar48[2] - (long)pvVar37);
        puVar48 = puVar65;
        if (puVar68 == puVar65) goto LAB_00b4f591;
      }
      puVar48 = puVar48 + 3;
    } while (puVar68 != puVar48);
LAB_00b4f591:
    *(undefined8 **)(param_3 + 0x660) = puVar62;
  }
  plVar38 = *(long **)(param_3 + 0x660);
  for (plVar43 = *(long **)(param_3 + 0x658); plVar43 != plVar38; plVar43 = plVar43 + 3) {
    pvVar37 = (void *)*plVar43;
    uVar42 = (ulong)*(uint *)(param_1 + 0xa21a98);
    if ((ulong)(plVar43[2] - (long)pvVar37 >> 3) < uVar42) {
      sVar53 = plVar43[1] - (long)pvVar37;
      if (uVar42 == 0) {
        pvVar41 = (void *)0x0;
        __n = sVar53;
      }
      else {
        pvVar41 = operator_new(uVar42 * 8);
        pvVar37 = (void *)*plVar43;
        __n = plVar43[1] - (long)pvVar37;
      }
      if (0 < (long)__n) {
        memmove(pvVar41,pvVar37,__n);
        pvVar37 = (void *)*plVar43;
      }
      if (pvVar37 != (void *)0x0) {
        operator_delete(pvVar37,plVar43[2] - (long)pvVar37);
      }
      plVar43[2] = (long)((long)pvVar41 + uVar42 * 8);
      *plVar43 = (long)pvVar41;
      plVar43[1] = sVar53 + (long)pvVar41;
    }
  }
  pvVar37 = *(void **)(param_3 + 0x630);
  lVar46 = *(long *)(param_3 + 0x640);
  *(undefined1 (*) [16])(param_3 + 0x630) = (undefined1  [16])0x0;
  *(undefined8 *)(param_3 + 0x640) = 0;
  if (pvVar37 != (void *)0x0) {
    operator_delete(pvVar37,lVar46 - (long)pvVar37);
  }
  uVar42 = (ulong)*(uint *)(param_1 + 0xa21a98);
  pvVar37 = *(void **)(param_3 + 0x630);
  if ((ulong)((*(long *)(param_3 + 0x640) - (long)pvVar37 >> 3) * -0x3333333333333333) < uVar42) {
    lVar46 = *(long *)(param_3 + 0x638);
    pvVar41 = (void *)0x0;
    lVar57 = lVar46 - (long)pvVar37;
    if (uVar42 != 0) {
      pvVar41 = operator_new(uVar42 * 0x28);
      pvVar37 = *(void **)(param_3 + 0x630);
      lVar46 = *(long *)(param_3 + 0x638);
    }
    if (lVar46 - (long)pvVar37 < 1) {
      if (pvVar37 != (void *)0x0) {
        uVar36 = *(long *)(param_3 + 0x640) - (long)pvVar37;
        goto LAB_00b4fca6;
      }
    }
    else {
      memmove(pvVar41,pvVar37,lVar46 - (long)pvVar37);
      uVar36 = *(long *)(param_3 + 0x640) - (long)pvVar37;
LAB_00b4fca6:
      operator_delete(pvVar37,uVar36);
    }
    *(void **)(param_3 + 0x640) = (void *)((long)pvVar41 + uVar42 * 0x28);
    *(void **)(param_3 + 0x630) = pvVar41;
    *(long *)(param_3 + 0x638) = lVar57 + (long)pvVar41;
  }
  lVar46 = (long)iVar32 * 0x50;
  RgpPrint("------------ Memory Allocations Report for Data Set: ------------");
  uVar42 = __size + sVar39 + __size_00 + __size_01 + __size_02 + __size_07 + __size_04 + __size_05 +
           __size_06 + lVar46 + uVar47 + __size_03 + local_2440;
  fVar27 = (float)uVar42;
  RgpPrint((double)(((float)local_2440 / fVar27) * DAT_00df9350),
           "Events         : %10d @ %7zu, (%10zu Bytes) [%f%%].",*(undefined4 *)(param_1 + 0xa21a98)
           ,0x418);
  if ((long)__size < 0) {
    fVar83 = (float)(__size >> 1) + (float)(__size >> 1);
  }
  else {
    fVar83 = (float)(long)__size;
  }
  RgpPrint((double)((fVar83 / fVar27) * DAT_00df9350),
           "Graphics State : %10d @ %7zu, (%10zu Bytes) [%f%%].",*(undefined4 *)(param_1 + 0xa21a30)
           ,0x2e88,__size);
  if ((long)__size_00 < 0) {
    fVar83 = (float)(__size_00 >> 1) + (float)(__size_00 >> 1);
  }
  else {
    fVar83 = (float)(long)__size_00;
  }
  RgpPrint((double)((fVar83 / fVar27) * DAT_00df9350),
           "Compute State  : %10d @ %7zu, (%10zu Bytes) [%f%%].",*(undefined4 *)(param_1 + 0xa21a34)
           ,0x170,__size_00);
  RgpPrint((double)(((float)__size_07 / fVar27) * DAT_00df9350),
           "Register State : %10d @ %7zu, (%10zu Bytes) [%f%%].",*(undefined4 *)(param_1 + 0xa21a98)
           ,0x2440);
  if ((long)sVar39 < 0) {
    fVar83 = (float)(sVar39 >> 1) + (float)(sVar39 >> 1);
  }
  else {
    fVar83 = (float)(long)sVar39;
  }
  RgpPrint((double)((fVar83 / fVar27) * DAT_00df9350),
           "Wavefronts     : %10d @ %7zu, (%10zu Bytes) [%f%%].",*(undefined4 *)(param_1 + 0xa219d8)
           ,0x18,sVar39);
  if ((long)__size_04 < 0) {
    fVar83 = (float)(__size_04 >> 1) + (float)(__size_04 >> 1);
  }
  else {
    fVar83 = (float)(long)__size_04;
  }
  RgpPrint((double)((fVar83 / fVar27) * DAT_00df9350),
           "Barriers       : %10d @ %7zu, (%10zu Bytes) [%f%%].",*(undefined4 *)(param_1 + 0xa21acc)
           ,0x58,__size_04);
  if ((long)__size_05 < 0) {
    fVar83 = (float)(((long)iVar55 & 0xfffffffffffffffU) << 3);
    fVar83 = fVar83 + fVar83;
  }
  else {
    fVar83 = (float)(long)__size_05;
  }
  RgpPrint((double)((fVar83 / fVar27) * DAT_00df9350),
           "Layout Trans.  : %10d @ %7zu, (%10zu Bytes) [%f%%].",*(undefined4 *)(param_1 + 0xa21b00)
           ,0x10,__size_05);
  if ((long)__size_06 < 0) {
    fVar83 = (float)(__size_06 >> 1) + (float)(__size_06 >> 1);
  }
  else {
    fVar83 = (float)(long)__size_06;
  }
  RgpPrint((double)((fVar83 / fVar27) * DAT_00df9350),
           "Command Buffers: %10d @ %7zu, (%10zu Bytes) [%f%%].",*(undefined4 *)(param_1 + 0xa21b34)
           ,0x38,__size_06);
  if ((long)__size_01 < 0) {
    fVar83 = (float)(__size_01 >> 1) + (float)(__size_01 >> 1);
  }
  else {
    fVar83 = (float)(long)__size_01;
  }
  RgpPrint((double)((fVar83 / fVar27) * DAT_00df9350),
           "Context Ops    : %10d @ %7zu, (%10zu Bytes) [%f%%].",*(undefined4 *)(param_1 + 0xa21b38)
           ,0xc,__size_01);
  if ((long)__size_03 < 0) {
    fVar83 = (float)(__size_03 >> 1) + (float)(__size_03 >> 1);
  }
  else {
    fVar83 = (float)(long)__size_03;
  }
  RgpPrint((double)((fVar83 / fVar27) * DAT_00df9350),
           "Persistent Ops : %10d @ %7zu, (%10zu Bytes) [%f%%].",lVar69,0xc,__size_03);
  if (lVar46 < 0) {
    fVar83 = (float)(((long)iVar32 * 5 & 0xfffffffffffffffU) << 3);
    fVar83 = fVar83 + fVar83;
  }
  else {
    fVar83 = (float)lVar46;
  }
  RgpPrint((double)((fVar83 / fVar27) * DAT_00df9350),
           "Queue Timings: : %10d @ %7zu, (%10zu Bytes) [%f%%].",*(undefined4 *)(param_1 + 0xa21b6c)
           ,0x50,lVar46);
  if ((long)__size_02 < 0) {
    fVar83 = (float)(__size_02 >> 1) + (float)(__size_02 >> 1);
  }
  else {
    fVar83 = (float)(long)__size_02;
  }
  RgpPrint((double)((fVar83 / fVar27) * DAT_00df9350),
           "User Events    : %10d @ %7zu, (%10zu Bytes) [%f%%].",*(undefined4 *)(param_1 + 0xa21b70)
           ,0x30,__size_02);
  RgpPrint((double)(((float)uVar47 / fVar27) * DAT_00df9350),
           "Pipeline Info  : %10d                Bytes  [%f%%].",uVar47);
  RgpPrint("Data Set Size* : %10d @ %7zu, (%10zu Bytes) [%f%%].",1,0x915a8,0x915a8);
  RgpPrint("Total Malloc   : %10zd Bytes.",uVar42);
  RgpPrint("Total Size     : %10zd Bytes (%10zd MB).",uVar42 + 0x915a8,uVar42 + 0x915a8 >> 0x14);
  RgpPrint("-----------------------------------------------------------------\n");
  lVar69 = *(long *)(param_1 + 0x7a8);
  uVar35 = *(undefined8 *)(param_1 + 0x9b10d8);
  *(undefined8 *)(lVar69 + 0x6bb38) = *(undefined8 *)(param_1 + 0xbc8868);
  uVar7 = *(undefined8 *)(param_1 + 0x9b10e0);
  *(undefined8 *)(lVar69 + 0x6bb40) = *(undefined8 *)(param_1 + 0xbc8888);
  *(undefined8 *)(lVar69 + 0x6bb48) = *(undefined8 *)(param_1 + 0xbc89b0);
  *(undefined8 *)(lVar69 + 0x6bb50) = *(undefined8 *)(param_1 + 0xbc89d0);
  *(undefined8 *)(lVar69 + 0x6bb58) = *(undefined8 *)(param_1 + 0xbc89f0);
  *(undefined8 *)(lVar69 + 0x6bb80) = *(undefined8 *)(param_1 + 0xbc8ed0);
  *(undefined8 *)(lVar69 + 0x6bb60) = *(undefined8 *)(param_1 + 0xbc8b18);
  *(undefined8 *)(lVar69 + 0x6bb68) = *(undefined8 *)(param_1 + 0xbc8c40);
  *(undefined8 *)(lVar69 + 0x6bb70) = *(undefined8 *)(param_1 + 0xbc8d68);
  *(undefined8 *)(lVar69 + 0x6bb78) = *(undefined8 *)(param_1 + 0xbc8d88);
  uVar11 = *(undefined8 *)(param_1 + 0xbc8eb0);
  *(undefined8 *)(lVar69 + 0x2ad0) = uVar35;
  *(undefined8 *)(lVar69 + 0x2ad8) = uVar7;
  *(undefined8 *)(lVar69 + 0x2aa8) = uVar11;
  goto LAB_00b4b6bd;
LAB_00b4e4b7:
  pvVar37 = *(void **)(param_1 + 0xbc89f0);
  goto LAB_00b4e4be;
}

