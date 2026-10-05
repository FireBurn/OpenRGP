// function: RgpEventProcessorAddEvent @ 00b6d250

/* RgpEventProcessorAddEvent(RgpEventProcessor*, RgpSqttStage, bool, RgpSqttEventType,
   RgpSqttSyncEventType, unsigned long) */

undefined8
RgpEventProcessorAddEvent
          (long param_1,uint param_2,char param_3,int param_4,int param_5,undefined8 param_6)

{
  int *piVar1;
  uint uVar2;
  long lVar3;
  ulong uVar4;
  
  if (param_1 == 0) {
    return 0x80000000;
  }
  if (10 < param_2) {
    return 0x80000007;
  }
  if (param_3 == '\0') {
    if (param_4 == 0xb) {
      piVar1 = (int *)(param_1 + 0x84810 + (long)(int)param_2 * 4);
      *piVar1 = *piVar1 + 1;
      return 0;
    }
  }
  else {
    if (param_5 - 1U < 2) {
      piVar1 = (int *)(param_1 + 0x847a0 + (long)(int)param_2 * 4);
      *piVar1 = *piVar1 + 1;
      return 0;
    }
    if (param_5 == 0) {
      uVar2 = *(uint *)(param_1 + 4 + ((long)(int)param_2 + 0x211dc) * 4);
      *(uint *)(param_1 + 4 + ((long)(int)param_2 + 0x211dc) * 4) = uVar2 + 1;
      if ((param_2 - 7 < 3) || (param_2 == 0)) {
        lVar3 = **(long **)(param_1 + 0x84768);
        uVar4 = (*(long **)(param_1 + 0x84768))[1] - lVar3 >> 2;
        if (uVar2 < uVar4) {
          if (uVar4 <= (ulong)(long)(int)uVar2) {
                    /* WARNING: Subroutine does not return */
            std::__throw_out_of_range_fmt
                      ("vector::_M_range_check: __n (which is %zu) >= this->size() (which is %zu)");
          }
          uVar4 = (ulong)*(int *)(lVar3 + (long)(int)uVar2 * 4);
          lVar3 = **(long **)(param_1 + 0x84858);
          if (uVar4 < (ulong)(((*(long **)(param_1 + 0x84858))[1] - lVar3 >> 3) *
                             -0x71c71c71c71c71c7)) {
            lVar3 = *(long *)(lVar3 + uVar4 * 0x48);
            if (lVar3 != 0) {
              *(undefined8 *)(lVar3 + 0x210) = param_6;
            }
            return 0;
          }
                    /* WARNING: Subroutine does not return */
          std::__throw_out_of_range_fmt
                    ("vector::_M_range_check: __n (which is %zu) >= this->size() (which is %zu)");
        }
      }
    }
  }
  return 0;
}

