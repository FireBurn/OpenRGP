// function: RgpSqttGetWaveEndTokenSize @ 00be72e0

undefined8 RgpSqttGetWaveEndTokenSize(int param_1)

{
  undefined8 uVar1;
  
  uVar1 = 2;
  if ((param_1 != 2) && (uVar1 = 0, param_1 == 3)) {
    uVar1 = 0x14;
  }
  return uVar1;
}

