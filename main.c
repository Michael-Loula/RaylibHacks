#include <stdio.h>

#include "raylib/src/raylib.h"

#define W 500
#define H 500
#define TARGET_FPS 60
#define PSIZE 20
#define BIG 100000
#define OBJS 3
int main() {

	InitWindow(W, H, "learn_good");

	SetTargetFPS(TARGET_FPS);
	Rectangle p = { 0 , H - (2 * PSIZE), PSIZE, PSIZE };
	Rectangle floor = { -BIG , H - PSIZE, BIG + W / 2 - PSIZE * 2, BIG };
	Rectangle floor2 = { W / 2 + PSIZE * 2, H - PSIZE, BIG, BIG };
	Rectangle c_box = { 0 };
	Rectangle c_box2 = { 0 };
	//todo: load these from a text file
	Rectangle objs[OBJS] = { { -BIG , H - PSIZE, BIG + W / 2 - PSIZE * 2, BIG }, { W / 2 + PSIZE * 2, H - PSIZE, BIG, BIG }, { W-PSIZE * 2, 0, BIG, BIG} };
	float ppx, ppy, pvx, pvy, pax, pay;
	pay = PSIZE / 4;
	pax = 0;
	pvy = 0;
	pvx = 0;
	int fc = 0;
	bool jump;
	while (!WindowShouldClose())
	{
		//frame counter
		fc = (fc + 1) % TARGET_FPS;
		
		printf("px %f, py %f, pvx %f, pvy %f, pax %f, pay %f\n", p.x, p.y, pvx, pvy, pax, pay);
		
		//save pre-update position
		ppx = p.x;
		ppy = p.y;

		//regular kinematics update
		pay = PSIZE / 4;	
		pvx += pax;
		pvy += pay;
		p.x += pvx;
		p.y += pvy;
		bool jump_buffer = false;

		
		for (int i = 0; i < OBJS; i++) {
			Rectangle o = objs[i];
			if (!CheckCollisionRecs(p, o))
				continue;				
			bool horizontally_aligned = (p.x > o.x && p.x < (o.x + o.width + PSIZE));
			bool vertically_aligned = (p.y > o.y && p.y < (o.y + o.height + PSIZE));
			//todo: more sane partial collision logic
			if (horizontally_aligned && vertically_aligned) {
				p.x = ppx;
				p.y = o.y - PSIZE;
				pvx = 0;
				pvy = 0;
			}
			else if (!horizontally_aligned && vertically_aligned) {
				p.x = ppx;
				pvx = 0;
			}
			else if (horizontally_aligned && !vertically_aligned) {
				p.y = o.y - PSIZE;
				pvy = 0;
				jump = false;
				pvx = pvx * (4/5);
			}
		}
		//ded
		if (p.y > H) {
			p.x = 0;
			p.y = floor.y - PSIZE;
			pvx = 0;
			pvy = 0;
		} 
		if (IsKeyDown(KEY_UP)) {
			if (!jump) {
				jump = true;
				pvy -= PSIZE * 1.5;
			}
		}
		if (IsKeyDown(KEY_RIGHT)) {
			pvx += PSIZE / 4;
		}
		if (IsKeyDown(KEY_LEFT)) {
			pvx -= PSIZE / 4;	
		}
		BeginDrawing();
		ClearBackground(RAYWHITE);
		DrawRectangleRec(p, DARKGRAY);
		for (int i = 0; i < OBJS; i++) {
			DrawRectangleRec(objs[i], DARKGRAY);
		}
		EndDrawing();
	}
	CloseWindow();

	return 0;
}
