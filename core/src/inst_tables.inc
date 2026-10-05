// Generated from AMD rocprof-trace-decoder (MIT) instruction tables; see re/amd-src. Do not edit by hand.
static Mapped map_inst10_base(int e) {
    using C = InstCat;
    switch (e) {
    case 0: return {C::Salu, 1, false};  // salu
    case 1: return {C::Smem, 1, false};  // smem_rd
    case 2: return {C::Smem, 1, false};  // smem_wr
    case 3: return {C::Jump, 1, false};  // branch_taken
    case 4: return {C::Next, 1, false};  // branch_not_taken
    case 5: return {C::Salu, 1, false};  // jump
    case 6: return {C::Trap, 1, false};  // trap
    case 7: return {C::Salu, 1, false};  // salu_no_exec
    case 8: return {C::Trap, 1, false};  // fatal_halt
    case 9: return {C::Msg, 1, false};  // message
    case 10: return {C::Valu, 1, false};  // valu_1
    case 11: return {C::Valu, 4, false};  // valut_4
    case 12: return {C::Valu, 1, false};  // valub_1
    case 13: return {C::Valu, 2, false};  // valub_2
    case 14: return {C::Valu, 4, false};  // valub_4
    case 15: return {C::Valu, 16, false};  // valub_16
    case 16: return {C::Valu, 1, false};  // valub_dfdp
    case 17: return {C::Valu, 1, false};  // valub_dfdp_derate
    case 18: return {C::Valu, 1, false};  // vinterp
    case 19: return {C::Immed, 1, false};  // barrier
    case 30: return {C::Flat, 1, false};  // flat_rd
    case 31: return {C::Flat, 2, false};  // flat_wr_2
    case 32: return {C::Flat, 3, false};  // flat_wr_3
    case 33: return {C::Flat, 4, false};  // flat_wr_4
    case 34: return {C::Flat, 5, false};  // flat_wr_5
    case 35: return {C::Vmem, 1, false};  // sgmem_rd
    case 36: return {C::Vmem, 1, false};  // sgmem_wr_1
    case 37: return {C::Vmem, 2, false};  // sgmem_wr_2
    case 38: return {C::Vmem, 3, false};  // sgmem_wr_3
    case 39: return {C::Vmem, 4, false};  // sgmem_wr_4
    case 40: return {C::Vmem, 5, false};  // sgmem_wr_5
    case 41: return {C::Lds, 1, false};  // lds_rd
    case 42: return {C::Lds, 1, false};  // lds_wr_1
    case 43: return {C::Lds, 2, false};  // lds_wr_2
    case 44: return {C::Lds, 3, false};  // lds_wr_3
    case 45: return {C::Lds, 4, false};  // lds_wr_4
    case 46: return {C::Lds, 5, false};  // lds_wr_5
    case 47: return {C::Vmem, 1, false};  // buf_rd_1
    case 48: return {C::Vmem, 2, false};  // buf_rd_2
    case 49: return {C::Vmem, 1, false};  // buf_wr_1
    case 50: return {C::Vmem, 2, false};  // buf_wr_2
    case 51: return {C::Vmem, 3, false};  // buf_wr_3
    case 52: return {C::Vmem, 4, false};  // buf_wr_4
    case 53: return {C::Vmem, 5, false};  // buf_wr_5
    case 54: return {C::Vmem, 6, false};  // buf_wr_6
    case 68: return {C::Vmem, 1, false};  // img_rd_1
    case 69: return {C::Vmem, 2, false};  // img_rd_2
    case 70: return {C::Vmem, 3, false};  // img_rd_3
    case 71: return {C::Vmem, 4, false};  // img_rd_4
    case 72: return {C::Vmem, 2, false};  // img_wr_2
    case 73: return {C::Vmem, 3, false};  // img_wr_3
    case 74: return {C::Vmem, 4, false};  // img_wr_4
    case 75: return {C::Vmem, 5, false};  // img_wr_5
    case 76: return {C::Vmem, 6, false};  // img_wr_6
    case 77: return {C::Vmem, 7, false};  // img_wr_7
    case 78: return {C::Vmem, 8, false};  // img_wr_8
    case 55: return {C::Vmem, 1, false};  // img_sample_1
    case 56: return {C::Vmem, 2, false};  // img_sample_2
    case 57: return {C::Vmem, 3, false};  // img_sample_3
    case 58: return {C::Vmem, 4, false};  // img_sample_4
    case 59: return {C::Vmem, 5, false};  // img_sample_5
    case 60: return {C::Vmem, 6, false};  // img_sample_6
    case 61: return {C::Vmem, 7, false};  // img_sample_7
    case 62: return {C::Vmem, 8, false};  // img_sample_8
    case 63: return {C::Vmem, 9, false};  // img_sample_9
    case 64: return {C::Vmem, 10, false};  // img_sample_10
    case 65: return {C::Vmem, 11, false};  // img_sample_11
    case 66: return {C::Vmem, 12, false};  // img_sample_12
    case 103: return {C::Bvh, 8, false};  // raytrace8
    case 104: return {C::Bvh, 9, false};  // raytrace9
    case 105: return {C::Bvh, 11, false};  // raytrace11
    case 106: return {C::Bvh, 12, false};  // raytrace12
    case 110: return {C::Lds, 1, false};  // lds_dir_load
    case 111: return {C::Lds, 1, false};  // lds_param_load
    case 112: return {C::Salu, 1, false};  // subv_loop_begin
    case 113: return {C::Salu, 1, false};  // subv_loop_end
    }
    return {C::None, 0};
}

Mapped map_inst10(int e, int dprate, int) {
    Mapped m = map_inst10_base(e);
    if (e >= 12 && e <= 17) m.cycles *= dprate;
    return m;
}

static Mapped map_inst11_base(int e) {
    using C = InstCat;
    switch (e) {
    case 0: return {C::Salu, 1, false};  // salu
    case 1: return {C::Smem, 1, false};  // smem_rd
    case 2: return {C::Smem, 1, false};  // smem_wr
    case 3: return {C::Jump, 1, false};  // branch_taken
    case 4: return {C::Next, 1, false};  // branch_not_taken
    case 5: return {C::Salu, 1, false};  // jump
    case 6: return {C::Trap, 1, false};  // trap
    case 7: return {C::Salu, 1, false};  // salu_no_exec
    case 8: return {C::Trap, 1, false};  // fatal_halt
    case 9: return {C::Msg, 1, false};  // message
    case 11: return {C::Valu, 4, false};  // valut_4
    case 12: return {C::Valu, 1, false};  // valub_1
    case 13: return {C::Valu, 2, false};  // valub_2
    case 14: return {C::Valu, 4, false};  // valub_4
    case 16: return {C::Valu, 1, false};  // valub_dfdp
    case 17: return {C::Valu, 1, false};  // valub_dfdp_derate
    case 18: return {C::Valu, 1, false};  // vinterp
    case 19: return {C::Immed, 1, false};  // barrier
    case 28: return {C::Flat, 2, false};  // flat_rd_2
    case 29: return {C::Flat, 3, false};  // flat_wr_3
    case 30: return {C::Flat, 4, false};  // flat_wr_4
    case 31: return {C::Flat, 5, false};  // flat_wr_5
    case 32: return {C::Flat, 6, false};  // flat_wr_6
    case 33: return {C::Vmem, 1, false};  // sgmem_rd_1
    case 34: return {C::Vmem, 2, false};  // sgmem_rd_2
    case 35: return {C::Vmem, 1, false};  // sgmem_wr_1
    case 36: return {C::Vmem, 2, false};  // sgmem_wr_2
    case 37: return {C::Vmem, 3, false};  // sgmem_wr_3
    case 38: return {C::Vmem, 4, false};  // sgmem_wr_4
    case 39: return {C::Vmem, 5, false};  // sgmem_wr_5
    case 40: return {C::Vmem, 6, false};  // sgmem_wr_6
    case 41: return {C::Lds, 1, false};  // lds_rd
    case 42: return {C::Lds, 1, false};  // lds_wr_1
    case 43: return {C::Lds, 2, false};  // lds_wr_2
    case 44: return {C::Lds, 3, false};  // lds_wr_3
    case 45: return {C::Lds, 4, false};  // lds_wr_4
    case 46: return {C::Lds, 5, false};  // lds_wr_5
    case 47: return {C::Vmem, 1, false};  // buf_rd_1
    case 48: return {C::Vmem, 2, false};  // buf_rd_2
    case 49: return {C::Vmem, 1, false};  // buf_wr_1
    case 50: return {C::Vmem, 2, false};  // buf_wr_2
    case 51: return {C::Vmem, 3, false};  // buf_wr_3
    case 52: return {C::Vmem, 4, false};  // buf_wr_4
    case 53: return {C::Vmem, 5, false};  // buf_wr_5
    case 54: return {C::Vmem, 6, false};  // buf_wr_6
    case 55: return {C::Vmem, 1, false};  // img_sample_1
    case 56: return {C::Vmem, 2, false};  // img_sample_2
    case 57: return {C::Vmem, 3, false};  // img_sample_3
    case 58: return {C::Vmem, 4, false};  // img_sample_4
    case 59: return {C::Vmem, 5, false};  // img_sample_5
    case 60: return {C::Vmem, 6, false};  // img_sample_6
    case 61: return {C::Vmem, 7, false};  // img_sample_7
    case 62: return {C::Vmem, 8, false};  // img_sample_8
    case 63: return {C::Vmem, 9, false};  // img_sample_9
    case 64: return {C::Vmem, 10, false};  // img_sample_10
    case 65: return {C::Vmem, 11, false};  // img_sample_11
    case 66: return {C::Vmem, 12, false};  // img_sample_12
    case 68: return {C::Vmem, 1, false};  // img_rd_1
    case 69: return {C::Vmem, 2, false};  // img_rd_2
    case 70: return {C::Vmem, 3, false};  // img_rd_3
    case 71: return {C::Vmem, 4, false};  // img_rd_4
    case 72: return {C::Vmem, 2, false};  // img_wr_2
    case 73: return {C::Vmem, 3, false};  // img_wr_3
    case 74: return {C::Vmem, 4, false};  // img_wr_4
    case 75: return {C::Vmem, 5, false};  // img_wr_5
    case 76: return {C::Vmem, 6, false};  // img_wr_6
    case 77: return {C::Vmem, 7, false};  // img_wr_7
    case 78: return {C::Vmem, 8, false};  // img_wr_8
    case 103: return {C::Bvh, 8, false};  // raytrace8
    case 104: return {C::Bvh, 9, false};  // raytrace9
    case 105: return {C::Bvh, 11, false};  // raytrace11
    case 106: return {C::Bvh, 12, false};  // raytrace12
    case 110: return {C::Lds, 1, false};  // lds_dir_load
    case 111: return {C::Lds, 1, false};  // lds_param_load
    case 112: return {C::Salu, 1, false};  // subv_loop_begin
    case 113: return {C::Salu, 1, false};  // subv_loop_end
    case 114: return {C::Salu, 1, false};  // salu_wr_exec
    case 115: return {C::Valu, 1, false};  // valu1_wr_exec
    case 116: return {C::Valu, 2, false};  // valu_b2_wr_exec
    case 117: return {C::Salu, 1, false};  // rfe
    case 118: return {C::Lds, 6, false};  // lds_bvh_6
    case 80: return {C::Lds, 1, true};  // lds_other_simd_1
    case 81: return {C::Lds, 2, true};  // lds_other_simd_2
    case 82: return {C::Lds, 3, true};  // lds_other_simd_3
    case 83: return {C::Lds, 4, true};  // lds_other_simd_4
    case 84: return {C::Lds, 5, true};  // lds_other_simd_5
    case 119: return {C::Lds, 6, true};  // lds_other_simd_6
    case 85: return {C::Flat, 2, true};  // flat_other_simd_2
    case 86: return {C::Flat, 3, true};  // flat_other_simd_3
    case 87: return {C::Flat, 4, true};  // flat_other_simd_4
    case 88: return {C::Flat, 5, true};  // flat_other_simd_5
    case 89: return {C::Flat, 6, true};  // flat_other_simd_6
    case 90: return {C::Vmem, 1, true};  // vmem_other_simd_1
    case 91: return {C::Vmem, 2, true};  // vmem_other_simd_2
    case 92: return {C::Vmem, 3, true};  // vmem_other_simd_3
    case 93: return {C::Vmem, 4, true};  // vmem_other_simd_4
    case 94: return {C::Vmem, 5, true};  // vmem_other_simd_5
    case 95: return {C::Vmem, 6, true};  // vmem_other_simd_6
    case 96: return {C::Vmem, 7, true};  // vmem_other_simd_7
    case 97: return {C::Vmem, 8, true};  // vmem_other_simd_8
    case 98: return {C::Vmem, 9, true};  // vmem_other_simd_9
    case 99: return {C::Vmem, 10, true};  // vmem_other_simd_10
    case 100: return {C::Vmem, 11, true};  // vmem_other_simd_11
    case 101: return {C::Vmem, 12, true};  // vmem_other_simd_12
    }
    return {C::None, 0};
}

Mapped map_inst11(int e, int dprate, int) {
    Mapped m = map_inst11_base(e);
    if (m.cat == InstCat::None && (e == 10 || e == 15)) return {InstCat::Valu, dprate};
    return m;
}
