// function: RgpSqttGetStageName @ 00ba7bd0

char * RgpSqttGetStageName(undefined4 param_1)

{
  switch(param_1) {
  case 0:
    return "PS";
  case 1:
  case 10:
    return "VS";
  case 2:
    return "GS";
  case 3:
    return "ES";
  case 4:
    return "HS";
  case 5:
    return "LS";
  case 6:
    return "CS";
  case 7:
    return "PS1";
  case 8:
    return "PS2";
  case 9:
    return "PS3";
  default:
    return "Unknown";
  }
}

