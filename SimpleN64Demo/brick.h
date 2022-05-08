/*
 * Do not edit this file.  It was automatically generated
 * by "rgb2c" from the file "brick.rgb".
 *
 *   Size: 32 x 32
 *   Number of channels: 4
 *   Number of bits per texel: 16 (G_IM_SIZ_16b)
 *   Format of texel: G_IM_FMT_RGBA
 *
 * Example usage:
 *
 *   gsSPTexture (128, 128, 0, G_TX_RENDERTILE, 1),
 *   gsDPPipeSync (),
 *   gsDPSetCombineMode (G_CC_MODULATERGBA, G_CC_MODULATERGBA),
 *   gsDPSetTexturePersp (G_TP_PERSP),
 *   gsDPSetTextureDetail (G_TD_CLAMP),
 *   gsDPSetTextureLOD (G_TL_TILE),
 *   gsDPSetTextureLUT (G_TT_NONE),
 *   gsDPSetTextureFilter (G_TF_BILERP),
 *   gsDPSetTextureConvert(G_TC_FILT),
 *   gsDPLoadTextureBlock (brick, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0
 *     G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
 *     G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
 */

#if 0 /* Image preview */
  +--------------------------------+
  |%%oo***%%%####%%%%%%#%%%%#%##%%%|
  |,,,,,,,,%,,,,,,,,,,,,,,~*,,,,,,,|
  |,,,,,,,.#,,,,,,,,,,,,,,,*,,,,,,,|
  |,,,,,,,.#,,,,,,,,.,,,,,.o,,,,,,,|
  |.,,,,,,.#,,,,,,,...,,,,,*,,,,,,,|
  |,,,,,,,,#,,,,,,,,,,,,,,,o,,,,,,,|
  |,,,,,,,,#,,,,,,,,,,,,,,,o,,,,,,,|
  |.......~#~,........,...~*,,.....|
  |%#%%%%%%%%%#%%*%%##%%%%%%%%#*%%%|
  |%,,,,,,,,,,,,,,~#,,,,,,,,,,,,,,~|
  |o,,,,,,,,,.,,.,.#,,,,,,,,,.,,,,~|
  |*,...,,,,,.,.,,.#,..,,,,,,.,.,,,|
  |%,,,.,,,,,,,,,,.%,,,,,,,,,,,,,,~|
  |*,,,,,,,,,,,,,..#,,,,,,,,,,,,,.,|
  |%.,,,,,,,,,,...,%,,.,,,,,,,,.,.~|
  |%o+~++++++~+~++o%%o+~~~~++~~+oo%|
  |%%%*%%%**%oo++o*oo*o*%o*%%%%%%*%|
  |,,,.,,,,#,,,.,,,,,,.,,,,%,,.,,,,|
  |,,,,,,,,#,,,,,,,,,,,,,,.%,,.,,,,|
  |,,,,,,,~#,,,,,.,,,,,,,,.#,,,,,,.|
  |.,,,,,,,#,,,,,,,.,,,,,,.#,,,,,,,|
  |,,.,,,,~%,.,,,,,,,,,,,,,%,,,,,,,|
  |,,,,,,,~%,,,,,,,,,,,,,,.%,,,,,,,|
  |,,,,.,,%%,.............+%,.,,,,,|
  |%%#####%%%%####%%%%%%**%%%**%***|
  |*,,,,,,,,,,,,,,~%,,,,,,,,,,,,,,~|
  |%,,,,,,,,,.,,.,,#,,,,,,,,,,,,,,,|
  |%,...,,,,,,,.,,.#,..,,,,,,.,.,,.|
  |%,,,.,,,,,,,,,,,#,,,,,,,,,,,,,,,|
  |%,,,,,,,,,,,,,..%,,,,,,,,,,,,,..|
  |%,,,,,,,,,,,,,..*,,,,,,,,,,,,,,.|
  |%~,,,,,,,,,,,,,+*o+~++++~+~~~~,+|
  +--------------------------------+
#endif

static Gfx brick_C_dummy_aligner1[] = { gsSPEndDisplayList() };

unsigned short brick[] = {
  0xd631, 0x7295, 0x48c9, 0x4949, 0x410b, 0x598d, 0x494b, 0x494b, 0x3909, 0x498d, 0x498d, 0x51cf, 0x498d, 0x498d,
  0x414d, 0x8319, 0xcdef, 0xaca3, 0x831b, 0x6251, 0x7b19, 0x831b, 0x835b, 0x8b9d, 0x7a95, 0x8297, 0x5a11, 0x5a11,
  0x520f, 0x59d1, 0x49cf, 0x92d7, 0xe673, 0x7803, 0x7803, 0x7041, 0x7003, 0x8003, 0x7843, 0x8843, 0x7801, 0x8043,
  0x7003, 0x8001, 0x6843, 0x8001, 0x6003, 0x3083, 0xcdaf, 0x7003, 0x8041, 0x7003, 0x7803, 0x8803, 0x7043, 0x8803,
  0x7801, 0x8043, 0x7003, 0x8041, 0x6003, 0x7803, 0x6841, 0x3887, 0xe675, 0x7041, 0x7803, 0x6803, 0x7003, 0x7043,
  0x7801, 0x9043, 0x8001, 0x8003, 0x7803, 0x7043, 0x7045, 0x6843, 0x5803, 0x3087, 0xe6b3, 0x7803, 0x7801, 0x6843,
  0x7003, 0x7845, 0x7803, 0x9803, 0x8001, 0x8001, 0x7843, 0x7045, 0x7043, 0x6803, 0x5843, 0x3887, 0xde31, 0x6803,
  0x7003, 0x6841, 0x6801, 0xa803, 0x7801, 0x8801, 0x7001, 0x7803, 0x7001, 0x8043, 0x8001, 0x7803, 0x7003, 0x30c7,
  0xf739, 0x6803, 0x7003, 0x7801, 0x7001, 0x8045, 0x8883, 0x9001, 0x6801, 0x7803, 0x8001, 0x8003, 0x8843, 0x7003,
  0x7801, 0x38c9, 0xe675, 0x8801, 0x5001, 0x5803, 0x6001, 0x7043, 0x7001, 0x9801, 0x7043, 0x8803, 0x8001, 0x7001,
  0x5841, 0x8003, 0x8803, 0x3085, 0xef39, 0x8803, 0x5001, 0x6003, 0x9801, 0x8045, 0x9043, 0x8801, 0x7803, 0x7801,
  0x5801, 0x7003, 0x5801, 0x8001, 0x8043, 0x3887, 0xeeb5, 0x6845, 0x8001, 0x8003, 0x9043, 0x6803, 0x7803, 0x9043,
  0x9003, 0x8083, 0x6003, 0x7001, 0x7803, 0x6003, 0x7003, 0x38c7, 0xef79, 0x7005, 0x8001, 0x8043, 0xa003, 0x8043,
  0x9005, 0xa043, 0x8803, 0x8083, 0x7803, 0x7001, 0x7003, 0x6843, 0x6803, 0x38c9, 0xddef, 0x7043, 0x7801, 0x7885,
  0x8885, 0x8085, 0x8845, 0x9043, 0x8085, 0x7843, 0x8887, 0x8843, 0x7801, 0x6045, 0x7885, 0x7a13, 0xdeb3, 0x7843,
  0x7843, 0x8043, 0x8085, 0x8845, 0x88c5, 0x9803, 0x8885, 0x7843, 0x8045, 0x8043, 0x7843, 0x6045, 0x7883, 0x6a13,
  0xd631, 0xdeb5, 0xef39, 0xf77b, 0xef39, 0xf77b, 0xf73b, 0xe6f7, 0xde71, 0xd633, 0xe6f5, 0xffbd, 0xf7bd, 0xf77b,
  0xf77d, 0xe6f5, 0xde73, 0xe6f7, 0xce31, 0xcdf1, 0xde73, 0xce2f, 0xcdaf, 0xde73, 0xe6f7, 0xd673, 0xcdef, 0xce31,
  0xd631, 0xc5ef, 0xcdef, 0xc5ad, 0x4087, 0x40c5, 0x40c7, 0x5109, 0x3887, 0x38c5, 0x590b, 0xe6f7, 0xe673, 0x494b,
  0x3843, 0x1843, 0x2041, 0x1843, 0x1843, 0x3087, 0x30c7, 0x3883, 0x1803, 0x3085, 0x2043, 0x3043, 0x2843, 0x735b,
  0xe6f7, 0x714b, 0x4085, 0x38c9, 0x3107, 0x40c9, 0x4107, 0x4909, 0x6803, 0x7043, 0x8001, 0x7843, 0x7003, 0x8003,
  0x8003, 0x7295, 0xde2f, 0x8003, 0x7803, 0x8043, 0x8003, 0x9003, 0x8803, 0x8003, 0x7003, 0x7803, 0x7843, 0x7801,
  0x7003, 0x8043, 0x8803, 0x3087, 0xe673, 0x8001, 0x7043, 0x8001, 0x8003, 0x9805, 0x8803, 0x8803, 0x7043, 0x8005,
  0x5801, 0x6843, 0x7043, 0x8001, 0x7841, 0x59cf, 0xf6f7, 0x7043, 0x5003, 0x8041, 0x6803, 0x6801, 0x7843, 0x7805,
  0x7003, 0x8003, 0x7043, 0x7043, 0x7041, 0x8003, 0x8003, 0x38c7, 0xddef, 0x7043, 0x8883, 0x7803, 0x6001, 0x7841,
  0x7003, 0x7805, 0x6001, 0x7003, 0x6843, 0x6843, 0x7043, 0x6801, 0x7043, 0x514b, 0xef39, 0x8043, 0x7801, 0x6843,
  0x8041, 0x8803, 0x8801, 0x7801, 0x6003, 0x7001, 0x6803, 0x7043, 0x6883, 0x7003, 0x6801, 0x3085, 0xf77b, 0x8043,
  0x7843, 0x7841, 0x7003, 0x8803, 0x8001, 0x7001, 0x7003, 0x7041, 0x7803, 0x8003, 0x8043, 0x7801, 0x8001, 0x59d1,
  0xffbb, 0x9003, 0x8881, 0x8041, 0xa801, 0x8001, 0x6801, 0x7003, 0x7841, 0x7843, 0x7801, 0x8003, 0x8003, 0x7801,
  0x8041, 0x3087, 0xffbd, 0x9041, 0x8043, 0x8041, 0x7841, 0x7801, 0x7001, 0x5003, 0x8041, 0x8843, 0x8841, 0x7003,
  0x7001, 0x7001, 0x8041, 0x494b, 0xff7b, 0x8003, 0x6841, 0x7001, 0x6841, 0x7043, 0x8041, 0x7041, 0x8001, 0x8841,
  0x8043, 0x7001, 0x7001, 0x7001, 0x8803, 0x2883, 0xeef7, 0x8001, 0x7001, 0x6041, 0x6803, 0x7041, 0x8041, 0x8043,
  0x7803, 0x7801, 0x8803, 0x6803, 0x7801, 0x8041, 0x6801, 0x514b, 0xf739, 0x6885, 0x7801, 0x7001, 0x6803, 0x7801,
  0x7003, 0x7841, 0x7803, 0x7801, 0x8803, 0x6801, 0x7801, 0x8003, 0x7001, 0x50c7, 0xde71, 0x7001, 0x7803, 0x6001,
  0x7001, 0x7801, 0x6843, 0x7801, 0xef37, 0xe675, 0xde73, 0xd5ad, 0xeeb7, 0xeef5, 0xd5ef, 0xc5ad, 0xcdad, 0xe673,
  0xc4a5, 0xac63, 0x82d5, 0x9ad7, 0xc4a7, 0xc4e7, 0xbca3, 0xbca5, 0xbce9, 0xac1f, 0xc4a5, 0xd631, 0xbca5, 0xcdad,
  0xe739, 0xeeb5, 0xe6b5, 0xde73, 0xde31, 0xddef, 0xcd6b, 0xe673, 0xde73, 0x9c21, 0x839d, 0x6ad7, 0x7319, 0x7b9d,
  0x7b5d, 0x6b17, 0x6b19, 0x735b, 0x6ad7, 0x7b9f, 0x6295, 0x6b19, 0x83dd, 0xace7, 0xde33, 0xd671, 0xa4e7, 0x7b5b,
  0x5a55, 0x62d7, 0x62d7, 0x6ad7, 0x835b, 0x7bdd, 0x5a95, 0x6ad9, 0x7b9d, 0x9421, 0xa4a5, 0xdeb5, 0xde31, 0x5801,
  0x7003, 0x7803, 0x7001, 0x7805, 0x7041, 0x8003, 0x7801, 0x7841, 0x6003, 0x7001, 0x6043, 0x6001, 0x5801, 0x40c9,
  0xe6f7, 0x7045, 0x7801, 0x6003, 0x7041, 0x8003, 0x7043, 0x8803, 0x6801, 0x7843, 0x6801, 0x8003, 0x6041, 0x8003,
  0x5801, 0x6a53, 0xd5ad, 0x7803, 0x7801, 0x6843, 0x7803, 0x7003, 0x7843, 0xa801, 0x7801, 0x8803, 0x7803, 0x6843,
  0x7045, 0x6803, 0x5843, 0x4045, 0xef79, 0x7845, 0x7801, 0x7001, 0x7005, 0x7843, 0x7803, 0x8803, 0x7801, 0x8043,
  0x7803, 0x7043, 0x7045, 0x6843, 0x5803, 0x40c7, 0xd5ef, 0x7003, 0x7003, 0x6801, 0x6803, 0x6041, 0x8045, 0x8801,
  0x7001, 0x7803, 0x7803, 0x8843, 0x7801, 0x7003, 0x7803, 0x3085, 0xeef7, 0x6803, 0x7803, 0x7003, 0x7801, 0x8043,
  0x8085, 0x9801, 0x7801, 0x7001, 0x8003, 0x8003, 0x8043, 0x7001, 0x7803, 0x59d1, 0xc52b, 0x8803, 0x5801, 0x5801,
  0x5843, 0x7843, 0x8003, 0x8801, 0x7043, 0x8001, 0x4801, 0x7001, 0x5803, 0x7801, 0x8803, 0x2843, 0xf73b, 0x8003,
  0x5801, 0x5843, 0x7003, 0x8085, 0x8003, 0xa041, 0x7003, 0x7001, 0x4801, 0x6803, 0x5841, 0x8001, 0x8003, 0x514b,
  0xbca5, 0x7005, 0x8001, 0x8843, 0x9003, 0x8045, 0x9003, 0x9043, 0x8803, 0x8843, 0x6801, 0x6801, 0x7003, 0x6003,
  0x7003, 0x2845, 0xffbd, 0x7043, 0x7803, 0x8003, 0x9041, 0x8045, 0x9003, 0x9803, 0x9043, 0x8085, 0x5001, 0x7001,
  0x7003, 0x6843, 0x6805, 0x59cf, 0xe673, 0x7003, 0x7841, 0x8085, 0x8045, 0x8885, 0x8885, 0x8803, 0x8883, 0x7803,
  0x8085, 0x8803, 0x7043, 0x7043, 0x7845, 0x698d, 0xef7b, 0x80c7, 0x7843, 0x7843, 0x8885, 0x8045, 0x88c5, 0x9845,
  0x8085, 0x8041, 0x8047, 0x9043, 0x7043, 0x7043, 0x7885, 0x6a11, 0xde73, 0xef7b, 0xd631, 0xcdf1, 0xde73, 0xdeb5,
  0xd631, 0xe6f7, 0xe6f5, 0xde75, 0xde73, 0xef37, 0xe6b7, 0xe6f5, 0xd5ef, 0xcdf1, 0xe6f5, 0xe73b, 0xef39, 0xdeb3,
  0xdeb7, 0xce2f, 0xd631, 0xe633, 0xdeb3, 0xde33, 0xde73, 0xef39, 0xc56b, 0xe6f7, 0xde73, 0xe6f7, 0x3043, 0x2803,
  0x3841, 0x3843, 0x3001, 0x3001, 0x4043, 0x6a13, 0xfffd, 0x9109, 0x7043, 0x4001, 0x4845, 0x4801, 0x4003, 0x4841,
  0x5803, 0x4043, 0x5001, 0x6043, 0x6001, 0x4001, 0x5003, 0x7295, 0xcdab, 0x790b, 0x5885, 0x4845, 0x3043, 0x3801,
  0x4043, 0x4843, 0x7803, 0x7843, 0x8043, 0x8003, 0x7003, 0x7843, 0x9003, 0x3109, 0xf77d, 0x8041, 0x7003, 0x8003,
  0x7801, 0x9003, 0x8045, 0x8801, 0x7803, 0x7803, 0x7843, 0x8003, 0x7003, 0x7803, 0x8843, 0x38c7, 0xbc65, 0x8041,
  0x7803, 0x8041, 0x7803, 0x9003, 0x9003, 0x8803, 0x6803, 0x8845, 0x7043, 0x7041, 0x7003, 0x8001, 0x8043, 0x30c9,
  0xf739, 0x7043, 0x8883, 0x8043, 0x6801, 0x6803, 0x7003, 0x7003, 0x6803, 0x7043, 0x6801, 0x7043, 0x7043, 0x8001,
  0x7803, 0x4109, 0xc4a5, 0x7043, 0x8883, 0x7803, 0x7001, 0x7843, 0x7003, 0x7803, 0x6003, 0x7841, 0x8001, 0x7043,
  0x7043, 0x6841, 0x7003, 0x3085, 0xef39, 0x8003, 0x7041, 0x8043, 0x8043, 0x8803, 0x8001, 0x7803, 0x6801, 0x6001,
  0x6003, 0x7043, 0x6843, 0x6841, 0x7003, 0x4949, 0xbce7, 0x8003, 0x6843, 0x8043, 0x7803, 0x7801, 0x7841, 0x7803,
  0x7843, 0x7041, 0x7803, 0x8003, 0x8003, 0x7801, 0x8041, 0x2085, 0xf73b, 0x9043, 0x8841, 0x8081, 0x9001, 0x8801,
  0x7801, 0x7803, 0x7841, 0x6003, 0x6801, 0x8003, 0x8003, 0x8041, 0x7801, 0x3887, 0xb39d, 0x9001, 0x8083, 0x8041,
  0x7041, 0x7801, 0x7801, 0x7803, 0x8041, 0x8843, 0x8841, 0x7003, 0x7801, 0x7001, 0x8801, 0x2885, 0xef39, 0x8001,
  0x7041, 0x6801, 0x8841, 0x8801, 0x7841, 0x8043, 0x8041, 0x8841, 0x8841, 0x7003, 0x7801, 0x6801, 0x8801, 0x414b,
  0xcce7, 0x8001, 0x7041, 0x7043, 0x6801, 0x7041, 0x8043, 0x8041, 0x7801, 0x8003, 0x8045, 0x6801, 0x8043, 0x8001,
  0x7843, 0x598d, 0xde73, 0x78c7, 0x7843, 0x7043, 0x7001, 0x7843, 0x6803, 0x8043, 0x8003, 0x7801, 0x8005, 0x7041,
  0x7803, 0x8041, 0x7003, 0x7a93, 0xcd6b, 0x6843, 0x7843, 0x7001, 0x6801, 0x8003, 0x6843, 0x8043, 0xd631, 0xd5ef,
  0xace7, 0xa4a3, 0xbd6b, 0xc56b, 0xbd6b, 0xde73, 0xd673, 0xe6f7, 0xef39, 0xf779, 0xef39, 0xeef9, 0xde71, 0xeef7,
  0xeef7, 0xe6b5, 0xe6f7, 0xe6b7, 0xef37, 0xde33, 0xde71, 0xe6f7, 0xdeb5, 0xef39, 0xeeb7, 0xef7b, 0xf77b, 0xe6b5,
  0xe6f5, 0xddf1,
};
