// function: RgpSqttGetIssueTypeName @ 00ba80c0

char * RgpSqttGetIssueTypeName(uint param_1)

{
  char *pcVar1;
  
  pcVar1 = "INST";
  if (param_1 != 2) {
    if (param_1 < 3) {
      pcVar1 = "STALL";
      if (param_1 == 0) {
        pcVar1 = "NULL";
      }
      return pcVar1;
    }
    pcVar1 = "Unknown";
    if (param_1 == 3) {
      pcVar1 = "IMM";
    }
  }
  return pcVar1;
}

