

/*
 char font[]  = {
  3,                 // Schriftbreite
   0x00, 0x00, 0x00,  // empty
   0x00, 0x00, 0x00,  // empty
   0x00, 0x00, 0x00,  // empty
   0x00, 0x00, 0x00,  // empty
   0x00, 0x00, 0x00,  // empty
   0x00, 0x00, 0x00,  // empty
   0x00, 0x00, 0x00,  // empty
   0x00, 0x00, 0x00,  // empty
   0x00, 0x00, 0x00,  // empty
   0x00, 0x00, 0x00,  // empty
   0x00, 0x00, 0x00,  // empty
   0x00, 0x00, 0x00,  // empty
   0x00, 0x00, 0x00,  // empty
   0x00, 0x00, 0x00,  // empty
   0x00, 0x00, 0x00,  // empty
   0x00, 0x00, 0x00,  // empty
   0x00, 0x00, 0x00,  // empty
   0x00, 0x00, 0x00,  // empty
   0x00, 0x00, 0x00,  // empty
   0x00, 0x00, 0x00,  // empty
   0x00, 0x00, 0x00,  // empty
   0x00, 0x00, 0x00,  // empty
   0x00, 0x00, 0x00,  // empty
   0x00, 0x00, 0x00,  // empty
   0x00, 0x00, 0x00,  // empty
   0x00, 0x00, 0x00,  // empty
   0x00, 0x00, 0x00,  // empty
   0x00, 0x00, 0x00,  // empty
   0x00, 0x00, 0x00,  // empty
   0x00, 0x00, 0x00,  // empty
   0x00, 0x00, 0x00,  // empty
   0x00, 0x00, 0x00,  // empty
   0x00, 0x00, 0x00,  // sp
   0x00, 0x5e, 0x00,  // ! *
   0x06, 0x00, 0x06,  // " *
   0xff, 0xff, 0xff,  // #
   0x48, 0xd6, 0x24,  // $ *
   0x46, 0x18, 0x62,  // % *
   0xff, 0xff, 0xff,  // &
   0x00, 0x06, 0x00,  // ' *
   0x38, 0x44, 0x82,  // ( *
   0x82, 0x44, 0x38,  // ) *
   0x14, 0x08, 0x3E,  // *
   0x10, 0x38, 0x10,  // + *
   0xa0, 0x60, 0x00,  // , *
   0x10, 0x10, 0x10,  // - *
   0x60, 0x60, 0x00,  // . *
   0x60, 0x18, 0x06,  // / *
   0x7c, 0x42, 0x7c,  // 0 *
   0x44, 0x7e, 0x40,  // 1 *
   0x64, 0x52, 0x4c,  // 2 *
   0x4a, 0x4a, 0x34,  // 3 *
   0x38, 0x24, 0x7e,  // 4 *
   0x4e, 0x4a, 0x32,  // 5 *
   0x3c, 0x4a, 0x32,  // 6 *
   0x62, 0x1a, 0x06,  // 7 *
   0x76, 0x4a, 0x76,  // 8 *
   0x4c, 0x52, 0x3c,  // 9 *
   0x6c, 0x6c, 0x00,  // : *
   0xac, 0x6c, 0x00,  // ; *
   0x10, 0x28, 0x44,  // < *
   0x28, 0x28, 0x28,  // = *
   0x44, 0x28, 0x10,  // > *
   0xFF, 0xFF, 0xFF,  // ?
   0xFF, 0xFF, 0xFF,  // @
   0x7c, 0x12, 0x7c,  // A *
   0x7c, 0x4a, 0x34,  // B *
   0x3c, 0x42, 0x42,  // C *
   0x7e, 0x42, 0x3c,  // D *
   0x7e, 0x4a, 0x42,  // E *
   0x7e, 0x0a, 0x0a,  // F *
   0x3c, 0x52, 0x34,  // G *
   0x7e, 0x08, 0x7e,  // H *
   0x42, 0x7e, 0x42,  // I *
   0x30, 0x40, 0x3e,  // J *
   0x7e, 0x18, 0x66,  // K *
   0x7e, 0x40, 0x40,  // L *
   0x7e, 0x1c, 0x7e,  // M *
   0x7e, 0x02, 0x7e,  // N *
   0x3c, 0x42, 0x3c,  // O *
   0x7e, 0x12, 0x0c,  // P *
   0x7e, 0x62, 0xfe,  // Q *
   0x7e, 0x32, 0x4e,  // R *
   0x44, 0x4a, 0x32,  // S *
   0x02, 0x7e, 0x02,  // T *
   0x7e, 0x40, 0x7e,  // U *
   0x3e, 0x40, 0x3e,  // V *
   0x3e, 0x7c, 0x3e,  // W *
   0x66, 0x18, 0x66,  // X *
   0x0e, 0x70, 0x0e,  // Y *
   0x62, 0x5a, 0x46,  // Z *
   0x00, 0x7e, 0x42,  // [ *
   0x06, 0x18, 0x60,  // backslash *
   0x42, 0x7e, 0x00,  // ] *
   0x04, 0x02, 0x04,  // ^ *
   0x40, 0x40, 0x40,  // _ *
   0x00, 0x02, 0x04,  // ` *
   0x74, 0x54, 0x78,  // a *
   0x7e, 0x48, 0x30,  // b *
   0x38, 0x44, 0x44,  // c *
   0x30, 0x48, 0x7e,  // d *
   0x38, 0x54, 0x48,  // e *
   0x7c, 0x0a, 0x02,  // f *
   0x98, 0xa4, 0x7c,  // g *
   0x7e, 0x08, 0x70,  // h *
   0x48, 0x7a, 0x40,  // i *
   0x88, 0xfa, 0x00,  // j *
   0x7e, 0x18, 0x64,  // k *
   0x3e, 0x40, 0x40,  // l *
   0x7c, 0x38, 0x7c,  // m *
   0x7C, 0x04, 0x78,  // n *
   0x38, 0x44, 0x38,  // o *
   0xFc, 0x24, 0x18,  // p *
   0x18, 0x24, 0xfc,  // q *
   0x78, 0x04, 0x04,  // r *
   0x48, 0x54, 0x24,  // s *
   0x04, 0x3e, 0x44,  // t *
   0x7C, 0x40, 0x7C,  // u *
   0x3c, 0x40, 0x3c,  // v *
   0x3c, 0x78, 0x3c,  // w *
   0x6c, 0x10, 0x6c,  // x *
   0x9c, 0xa0, 0x7c,  // y *
   0x64, 0x54, 0x4c,  // z *
   0xFF, 0xFF, 0xFF,  // A
   0xFF, 0xFF, 0xFF,  // O
   0xFF, 0xFF, 0xFF,  // U
   0xFF, 0xFF, 0xFF,  // a
   0xFF, 0xFF, 0xFF,  // o
   0xFF, 0xFF, 0xFF,  // u
   0xFF, 0xFF, 0xFF,  // ß
   0xfc, 0x40, 0x7c,  // µ *
   0xFF, 0xFF, 0xFF,  // <
   0xFF, 0xFF, 0xFF,  // >
};
*/

char font[]  = {
  3, 
  0xF8, 0x88, 0xF8, 0x00, 0x00,  //0
  0x00, 0x00, 0xF8, 0x00, 0x00,  //1
  0xE8, 0xA8, 0xB8, 0x00, 0x00,  //2
  0xA8, 0xA8, 0xF8, 0x00, 0x00,  //3
  0x38, 0x20, 0xF8, 0x00, 0x00,  //4
  0xB8, 0xA8, 0xE8, 0x00, 0x00,  //5
  0xF8, 0xA8, 0xE8, 0x00, 0x00,  //6
  0x08, 0x08, 0xF8, 0x00, 0x00,  //7
  0xF8, 0xA8, 0xF8, 0x00, 0x00,  //8
  0xB8, 0xA8, 0xF8, 0x00, 0x00,  //9
};


