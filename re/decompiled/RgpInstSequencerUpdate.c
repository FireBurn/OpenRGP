// function: RgpInstSequencerUpdate @ 004e0823

/* RgpInstSequencerUpdate(RgpInstSequencer*, RgpSqttParser&, RgpInstructionIssue*, RgpSqttStage,
   int, RgpSqttTokenInstruction const*) [clone .cold] */

void RgpInstSequencerUpdate(void)

{
  vector<RgpEventInstructionBranchData,std::allocator<RgpEventInstructionBranchData>>
  *in_stack_00000008;
  void *in_stack_00000020;
  vector<RgpEventInstructionBranchData,std::allocator<RgpEventInstructionBranchData>>
  *in_stack_00000028;
  
  std::vector<RgpEventInstructionBranchData,std::allocator<RgpEventInstructionBranchData>>::~vector
            (in_stack_00000008);
  operator_delete(in_stack_00000020,0x28);
  std::vector<RgpEventInstructionBranchData,std::allocator<RgpEventInstructionBranchData>>::~vector
            (in_stack_00000028);
                    /* WARNING: Subroutine does not return */
  _Unwind_Resume();
}

