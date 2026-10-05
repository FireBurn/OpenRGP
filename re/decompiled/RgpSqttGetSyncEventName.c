// function: RgpSqttGetSyncEventName @ 00ba8080

char * RgpSqttGetSyncEventName(int param_1)

{
  char *pcVar1;
  
  pcVar1 = "DRAW_DONE";
  if (((param_1 != 1) && (pcVar1 = "FLUSH_DFSM", param_1 != 2)) &&
     (pcVar1 = "Unknown", param_1 == 0)) {
    pcVar1 = "MARKER";
  }
  return pcVar1;
}

