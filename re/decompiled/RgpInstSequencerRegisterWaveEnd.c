// function: RgpInstSequencerRegisterWaveEnd @ 00b94f80

/* RgpInstSequencerRegisterWaveEnd(RgpInstSequencer*, int, unsigned int, RgpSqttStage, unsigned
   long, unsigned long*) */

undefined8
RgpInstSequencerRegisterWaveEnd
          (long param_1,int param_2,int param_3,int param_4,undefined8 param_5,long *param_6)

{
  RgpInstSeqSlot *pRVar1;
  long lVar2;
  char cVar3;
  int iVar4;
  long lVar5;
  undefined8 uVar6;
  AmdGpuDisContext *pAVar7;
  undefined2 uVar8;
  long lVar9;
  long in_FS_OFFSET;
  ulong local_60;
  undefined8 local_58;
  undefined8 uStack_50;
  undefined4 local_48;
  undefined2 local_44;
  byte local_42;
  undefined1 local_41;
  long local_40;
  
  local_40 = *(long *)(in_FS_OFFSET + 0x28);
  if (param_1 == 0) {
    uVar6 = 0x80000000;
    goto LAB_00b95000;
  }
  if ((param_6 == (long *)0x0) || (lVar5 = (long)param_2, 0x4aff < param_2)) {
    uVar6 = 0x80000006;
    goto LAB_00b95000;
  }
  iVar4 = *(int *)(*(long *)(param_1 + 8) + 0x104);
  if (iVar4 < 7) {
LAB_00b94fdc:
    uVar6 = 0;
  }
  else {
    lVar9 = lVar5 * 0x128;
    lVar2 = param_1 + lVar9;
    if ((param_3 == *(int *)(lVar2 + 0x10)) && (param_4 == *(int *)(lVar2 + 0x14))) {
      pRVar1 = (RgpInstSeqSlot *)(param_1 + 0x10 + lVar9);
      cVar3 = RgpInstSequencerIfSlotContainsInstructions(pRVar1);
      if (cVar3 != '\0') {
        cVar3 = RgpEventInstStateIsInstructionEnd
                          (*(long *)(lVar2 + 0x60) + 0x3b8,*(undefined4 *)(lVar2 + 0x14),
                           *(undefined4 *)(lVar2 + 0x18),*(undefined8 *)(lVar2 + 0x20),
                           *(undefined8 *)(lVar2 + 0x30));
        if (cVar3 != '\0') {
          uVar8 = 0xffff;
          if (iVar4 < 0x10) {
            uVar8 = 9;
          }
          pAVar7 = (AmdGpuDisContext *)(*(long *)(*(long *)(lVar2 + 0x30) + 8) + 0xd8);
          iVar4 = RgpIsaGetPcAddressFromLocation
                            (pAVar7,*(ulong *)(lVar2 + 0x20),(long)*(int *)(lVar2 + 0x18),
                             (ulong *)&local_58);
          local_41 = *(undefined1 *)(lVar2 + 0x38);
          uStack_50 = 0xffffffffffffffff;
          if (iVar4 == 0) {
            uStack_50 = local_58;
          }
          local_48 = 0;
          local_42 = *(byte *)(lVar2 + 0x130) & 0x7f;
          local_58 = param_5;
          local_44 = uVar8;
          RgpInstSequencerAppendSlotTrace(pRVar1,(RgpInstSeqTraceEntry *)&local_58);
          *(int *)(lVar2 + 0x28) = *(int *)(lVar2 + 0x28) + 1;
          if (*(int *)(lVar2 + 0x18) == *(int *)(lVar2 + 0x3c) + -1) {
            local_60 = 0xffffffffffffffff;
            iVar4 = RgpIsaGetBranchNext(pAVar7,*(ulong *)(lVar2 + 0x20),&local_60);
            if (iVar4 != 0) {
              local_60 = 0xffffffffffffffff;
            }
            lVar2 = param_1 + lVar5 * 0x128;
            *(ulong *)(lVar2 + 0x20) = local_60;
            *(undefined4 *)(lVar2 + 0x18) = 0;
            RgpIsaGetBlockSize(pAVar7,local_60,(uint *)(param_1 + 0x3c + lVar9));
          }
          else {
            *(int *)(lVar2 + 0x18) = *(int *)(lVar2 + 0x18) + 1;
          }
        }
        goto LAB_00b94fdc;
      }
    }
    uVar6 = 0x80000006;
  }
  lVar2 = *(long *)(param_1 + 0x68 + lVar5 * 0x128);
  lVar5 = lVar2 + -1;
  if (lVar2 == 0) {
    lVar5 = 0;
  }
  *param_6 = lVar5;
LAB_00b95000:
  if (local_40 == *(long *)(in_FS_OFFSET + 0x28)) {
    return uVar6;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}

