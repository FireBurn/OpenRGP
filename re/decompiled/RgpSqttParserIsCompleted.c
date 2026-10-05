// function: RgpSqttParserIsCompleted @ 00bea320

bool RgpSqttParserIsCompleted(long param_1)

{
  int iVar1;
  long in_FS_OFFSET;
  bool bVar2;
  undefined1 auStack_b8 [32];
  undefined1 local_98 [120];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  bVar2 = false;
  if (param_1 != 0) {
    iVar1 = RgpSqttParserAdvance(param_1,local_98,auStack_b8,0);
    RgpSqttParserSetPosition(param_1,auStack_b8,0);
    bVar2 = iVar1 != 0;
  }
  if (local_20 == *(long *)(in_FS_OFFSET + 0x28)) {
    return bVar2;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}

