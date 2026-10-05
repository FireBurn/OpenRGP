// function: RgpSqttGetRealTimeClockMask @ 00be7300

undefined8 RgpSqttGetRealTimeClockMask(undefined8 param_1)

{
  undefined8 uVar1;
  long in_FS_OFFSET;
  int local_18;
  int local_14;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  local_18 = 0;
  local_14 = 0;
  RgpGetSqttMajorMinorVersion(param_1,&local_18,&local_14);
  uVar1 = 0xffffffffffff;
  if ((((local_18 != 2) && (uVar1 = 0, local_18 == 3)) && (uVar1 = 0xffffffffffff, local_14 != 0))
     && (uVar1 = 0xfffffffff, local_14 != 2)) {
    uVar1 = 0xfffffffffffff;
  }
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return uVar1;
}

