#include <psx.h>
#include <stdio.h>

unsigned int prim_list[0x4000];

/* here we will save gamepad state */
unsigned short padbuf;

volatile int display_is_old = 1;
volatile int time_counter = 0;
int dbuf = 0;

int hx = 0, hy = 0;

void prog_vblank_handler() {
  display_is_old = 1;
  time_counter++;
}

int main() {
  PSX_Init();
  GsInit();
  GsSetList(prim_list);
  GsClearMem();
  GsSetVideoMode(320, 240, VMODE_PAL);
  GsLoadFont(768, 0, 768, 256);
  SetVBlankHandler(prog_vblank_handler);

  while (1) {
    if (display_is_old) {
      dbuf = !dbuf;
      GsSetDispEnvSimple(0, dbuf ? 0 : 256);
      GsSetDrawEnvSimple(0, dbuf ? 256 : 0, 320, 240);

      GsSortCls(0, 0, 0);

      /* get the gamepad state */
      PSX_ReadPad(&padbuf, NULL);

      /* change coords according to which gamepad button was pressed */
      if (padbuf & PAD_LEFT) hx--;
      if (padbuf & PAD_RIGHT) hx++;
      if (padbuf & PAD_UP) hy--;
      if (padbuf & PAD_DOWN) hy++;

      /* display text with changes coords */
      GsPrintFont(hx, hy, "Hello world from PSX");

      GsDrawList();
      while (GsIsDrawing())
        ;

      display_is_old = 0;
    }
  }

  return 0;
}
