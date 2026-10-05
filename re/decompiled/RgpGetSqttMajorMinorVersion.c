// function: RgpGetSqttMajorMinorVersion @ 00b3b960

undefined8 RgpGetSqttMajorMinorVersion(undefined4 param_1,undefined4 *param_2,undefined4 *param_3)

{
  if ((param_2 != (undefined4 *)0x0) && (param_3 != (undefined4 *)0x0)) {
    switch(param_1) {
    case 5:
      *param_2 = 2;
      *param_3 = 2;
      return 0;
    case 6:
      *param_2 = 2;
      *param_3 = 3;
      return 0;
    case 7:
      *param_2 = 3;
      *param_3 = 0;
      return 0;
    default:
      return 0x8000000b;
    case 0xb:
      *param_2 = 3;
      *param_3 = 2;
      return 0;
    case 0xc:
      *param_2 = 3;
      *param_3 = 3;
      return 0;
    }
  }
  return 0x80000000;
}

