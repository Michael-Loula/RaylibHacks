#include <stdio.h>

#include "raylib/src/raylib.h"

#define W 500
#define H 500
#define TARGET_FPS 60
#define PSIZE 20
#define BIG 100000
int main() {

	InitWindow(W, H, "learn_good");

	SetTargetFPS(TARGET_FPS);
	Rectangle p = { 0 , H - (2 * PSIZE), PSIZE, PSIZE };
	Rectangle floor = { -BIG , H - PSIZE, BIG + W / 2 - PSIZE * 2, BIG };
	Rectangle floor2 = { W / 2 + PSIZE * 2, H - PSIZE, BIG, BIG };
	Rectangle c_box = { 0 };
	Rectangle c_box2 = { 0 };
	bool fcol = false;
	bool fcol2 = false;
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

		//horizontal bounds checking
		if (p.x > W - PSIZE || p.x < 0) {
			p.x = ppx;
			pvx = 0;
		}

		if (CheckCollisionRecs(p, floor) || CheckCollisionRecs(p, floor2)) {
			bool horizontally_aligned = (ppx > floor.x && ppx < (floor.x + floor.width)) || (ppx > floor2.x && ppx < (floor2.x + floor2.width));
			bool vertically_aligned = (ppy > floor.y && ppy < (floor.y + floor.height));	
			if (horizontally_aligned && vertically_aligned) {
				//hax
				p.x = ppx;
				p.y = floor.y - PSIZE;
				pvx = 0;
				pvy = 0;
				printf("g\n");
			}
			else if (!horizontally_aligned && vertically_aligned) {
				p.x = ppx;
				pvx = 0;
				printf("h\n");
			}
			else if (horizontally_aligned && !vertically_aligned) {
				pvy = 0;
				p.y = floor.y - PSIZE;
				jump = false;
				printf("v\n");
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
				pvy -= 2 * PSIZE;
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
		DrawRectangleRec(floor, DARKGRAY);
		DrawRectangleRec(floor2, DARKGRAY);
		EndDrawing();
	}
	CloseWindow();

	return 0;
}
